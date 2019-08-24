#pragma once

namespace DnsTelemeter::Network::Dns {
    struct Header {
        const bool response;
        const int rcode;
    };
}
