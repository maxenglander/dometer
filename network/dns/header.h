#pragma once

namespace Dometer::Network::Dns {
    struct Header {
        const bool response;
        const int rcode;
    };
}
