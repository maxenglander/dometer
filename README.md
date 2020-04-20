# dometer

`dometer` is a DNS proxy that emits telemetry.

## Platforms

`dometer` has been built and tested on the following platforms:

 * Mac OS
 * Ubuntu
 
## Building

In order to build `dometer`, the following dependencies are required:

 * Bazel >= 2.2.0
 * CMake >= 3.16.2
 * envsubst >= 0.20.2

```
dometer $ bazel build //dometer/cli:main
```

## Configuration

`dometer` is configured through a JSON file, e.g.:

```
dometer $ ./bazel-bin/dometer/cli/main --config dometer/config/config.json.sample
```

See the [configuration JSON schema](./dometer/config/schema.json) for a description
of the available options, or the [sample configuration file](./dometer/config/config.json.sample)
for an example configuration.

## Components

### DNS

`dometer` DNS component accepts and resolves incoming DNS requests.

#### Server

The `dometer` DNS server listens for incoming UDP DNS requests.

#### Resolver

`dometer` resolves incoming DNS requests using one resolver library. The following
resolver libraries can be selected:

 * `libresolv`

##### `libresolv`

The `libresolv` resolver library uses the BIND-compatible resolver library native
to the host platform. It can be configured to use one of the following resolver
function:

 * `query`
 * `search`

**query**

The `query` function will use the `res_query(3)` resolver routine.

**search**

The `search` function will use the `res_search(3)` resolver routine.

### Metrics

`dometer` collects metrics on DNS resolution attempts and replies for each
incoming DNS request.

The following metrics are collected:

| Name | Type | Unit | Description |
| :---- | :---- | :---- | :----------- |
| `dometer_dns_lookup_duration` | histogram | seconds | The duration of DNS resolutions attempted by `dometer`. |

#### Handlers

`dometer` emits collected metrics using one or more configured handlers.
Currently, the following handlers are supported:

 * `prometheus`

##### `prometheus`

The `prometheus` handler emits metrics as Prometheus time-series. By default, it
exposes metrics through an HTTP server serving requests at `http://0.0.0.0:9090/metrics`.

**Format**

It emits metric data in the following format:

```
dometer_dns_lookup_duration_seconds_count{
  error="-|NOERROR|CONNREFUSED|...",
  qclass="IN",
  qname=".*",
  qtype="A|MX|...",
  rcode="-|NOERROR|NXDOMAIN|...",
  [additional_labels]
} <count>
dometer_dns_lookup_duration_seconds_sum{
  error="-|NOERROR|CONNREFUSED|...",
  qclass="IN",
  qname=".*",
  qtype="A|MX|...",
  rcode="-|NOERROR|NXDOMAIN|...",
  [additional_labels]
} <seconds>
dometer_dns_lookup_duration_seconds_bucket{
  error="-|NOERROR|CONNREFUSED|...",
  qclass="IN",
  qname=".*",
  qtype="A|MX|...",
  rcode="-|NOERROR|NXDOMAIN|...",
  [additional_labels],
  le="<seconds>"
} <count>
```

**Maximum time-series**

Because the possible combinations of domains and record types that can be
requested through `dometer` is potentially unbounded, the Prometheus metric
handler tracks time-series with an LRU cache. This LRU cache will evict the
least recently used time-series when new time-series data would result in the
cache storing more than the user-defined maximum number of time-series.

A Prometheus time-series is a unique combination of:
 
  * Time-series name (e.g. `dometer_dns_lookup_duration_bucket`)
  * A set of labels and their values (e.g. `{error="-",rcode="NXDOMAIN",...}`)

The following Prometheus time-series are distinct, even though they were
generated or updated by the same DNS request to `dometer`:

```
dometer_dns_lookup_duration_seconds_bucket{
  error="-",qclass="IN",qname="hello.world",qtype="A",rcode="NXDOMAIN",le="0.1"
} 1
dometer_dns_lookup_duration_seconds_bucket{
  error="-",qclass="IN",qname="hello.world",qtype="A",rcode="NXDOMAIN",le="1.0"
} 0
```

The number of time-series generated or updated by a single DNS request to
`dometer` is a function of the metric type and other metric options. For
example, a Prometheus histogram metric generates a time series for the total
count of collected observations, the sum of collected observations, and a
time-series for each bucket in the histogram.

## Usage

The only supported way at present to use `dometer` is through the command-line.

### CLI

`dometer` is started from the command-line.

```
dometer $ ./bazel-bin/dometer/cli/main
Dometer.

Usage:
  dometer --config=<path>
  dometer --help

Options:
  --config=<file>  Supply configuration file [default: /etc/dometer/config.json].
  --help           Show this help message.
```

## Testing

In order to test `dometer`, the following dependencies are required:

 * Bazel >= 2.2.0
 * CMake >= 3.16.2
 * envsubst >= 0.20.2

```
dometer $ bazel test ... 
```

## API Stability

No guarantees are made about the stability of any part of `dometer`, including:

 * The name and shape of emitted metrics
 * The command-line interface

## Quality

No guarantees or assertions are made about the performance, reliability, or
safety of this software. Use at your own risk.

## Inspiration and motivation

`dometer` is inspired by Envoy and CoreDNS.

- [Envoy UDP listener](https://www.envoyproxy.io/docs/envoy/latest/configuration/listeners/udp_filters/udp_proxy)
- [CoreDNS metrics](https://github.com/coredns/coredns/tree/master/plugin/metrics)

I was motivated to create `dometer` as a personal learning project, and because
I ran into several DNS-related issues at work where a tool like `dometer` would
have been useful for debugging.
