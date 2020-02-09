namespace dometer::config {
    struct Config {
        std::string apiVersion;
        Dns dns;
        Metrics metrics;
    }
}
