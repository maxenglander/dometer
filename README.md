Dometer
=======

## Flows

Network entities and interactions.

```
                           |------------------------------|
                           | Dometer                      |
                           | |--------------------------| |
                           | | UDP server               | |
|--------|                 | |--------------------------| |
| Client ==> UDP datagram ==>|[rx/tx datagram]          | |
|        <== UDP datagram <==|                          | |     
|--------|                 | |-------------||-----------| |
                           |               ||             |
                           | |-------------||-----------| |
                           | | DNS parser               | |
                           | |--------------------------| |
                           | |[parse datagram]          | |
                           | |-------------||-----------| |
                           |               ||             |
                           | |-------------||-----------| |
                           | | DNS resolver (libresolv) | |
                           | |--------------------------| |                |----------|
                           | |[resolve query]           ==> UDP datagram ==> Upstream | 
                           | |                          <== UDP datagram <==          |
                           | |--------------------------| |                |----------|
                           |------------------------------|
```

Simplified sequence.

```
UDP datagram ==> UDP server ==> DNS parser ==> DNS resolver ==> upstream
UDP datagram <== UDP server <== DNS parser <== DNS resolver <== upstream
```

## Interfaces

```
std::expected<std::vector<uint8_t>, dometer::util::Error>
dometer::dns::Resolver::resolve(dometer::dns::Type qtype,
                                dometer::dns::Class qclass,
                                std::string qname);

std::expected<dometer:dns::message::Message, dometer::util::Error>
dometer::dns::Message::parse(std::vector<uint8_t>);
```

## Events

- `dometer::dns::message::Parse`
- `dometer::dns::message::ParseError`
- `dometer::dns::resolver::Resolve`
- `dometer::dns::resolver::ResolveError`
- `dometer::dns::server::Receive`
- `dometer::dns::server::ReceiveError`
- `dometer::dns::server::Send`
- `dometer::dns::server::SendError`

## Metrics

There are a number of things we could conceivably represent with metrics:
 - The number of messages (queries) received from downstream
 - The in/validity of messages received from downstream
 - The size of messages received from downstream
 - The number of messages (queries) forwarded to upstream
 - The size of messages forwarded to downstream
 - The number of messages (replies) received from upstream
 - The in/validity of messages received from upstream
 - The size of messages (replies) received from upstream
 - The latency between queries sent by proxy to upstream,
   and replies received by proxy from upstream
 - The latency between queries received by the proxy from
   downstream, and replies sent by the proxy to upstream
 - The number and types of network errors that have occurred,
   such as DNS lookup timeouts, host-level errors, etc.

The goal is to represent the most important pieces of information,
in a format and with naming that is clear, compact, and consistent.

### External examples

- [Envoy UDP listener](https://www.envoyproxy.io/docs/envoy/latest/configuration/listeners/udp_filters/udp_proxy)
- [CoreDNS metrics](https://github.com/coredns/coredns/tree/master/plugin/metrics)

### Terminology

- message: a single DNS message, usually a single UDP packet
- query: a single DNS message with the QR flag set to 0
- reply: a single DNS message with the QR flag set to 1
- resolver: the proxy's DNS resolver
- server: the proxy's UDP server
- session: a query-reply message sequence

### Metrics

#### `dometer_dns_parse_error`

Count of DNS parse errors.

Example:

```
dometer_dns_parse_error{
}
```

Drawbacks:
- Low context: don't know if this was a response or a reply

#### `dometer_dns_lookup_duration_seconds`

Example:

```
dometer_dns_lookup_duration_seconds{
  err="-|TIMEOUT|...",
  qclass="-|IN",
  qtype="-|A|MX|...",
  qname="-|a.b.com|...",
  rcode="-|FORMERR|NOERROR|NXDOMAIN|..."
} = <double> 
```

#### `dometer_dns_lookups_total`

Count of DNS lookup attempts.

Incremented whenever the proxy forwards an incoming request to
an upstream server via the configured DNS resolver.

Example:

```
dometer_dns_lookups_total{
  err="-|TIMEOUT|...",
  qclass="-|IN",
  qtype="-|A|MX|...",
  qname="-|a.b.com|...",
  rcode="-|FORMERR|NOERROR|NXDOMAIN|..."
} = <uint64> 
```
