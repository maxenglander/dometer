namespace dometer::config {
    const char * SCHEMA = R"SCHEMA(
    {
      "$schema": "http://json-schema.org/draft-04/schema#",
      "id": "https://github.com/maxenglander/dometer/tree/v0.1.0/config/schema.json",
      "title": "Dometer Config Schema",
      "type": "object",
      "properties": {
        "apiVersion": {
          "type": "string",
          "enum": ["v0"],
          "default": "v0"
        },
        "dns": {
          "type": "object",
          "properties": {
            "resolver": {
              "type": "object",
              "properties": {
                "type": {
                  "type": "string",
                  "enum": ["libresolv"],
                  "default": "libresolv"
                },
                "libresolv": {
                  "type": "object",
                  "properties": {
                    "function": {
                      "type": "string",
                      "enum": ["query", "search"],
                      "default": "query"
                    }
                  },
                  "required": ["function"]
                }
              },
              "anyOf": [
                {
                  "properties": {
                    "type": { "const": "libresolv" }
                  },
                  "required": ["libresolv"]
                }
              ],
              "required": [
                "type"
              ]
            },
            "server": {
              "type": "object",
              "properties": {
                "transport": {
                  "type": "object",
                  "properties": {
                    "bindAddress": {
                      "type": "string",
                      "default": "0.0.0.0:5353"
                    },
                    "maxConnections": {
                      "type": "integer",
                      "multipleOf": 1.0,
                      "minimum": 0,
                      "default": 100
                    }
                  },
                  "required": [
                    "bindAddress",
                    "maxConnections"
                  ]
                }
              },
              "required": [
                "transport"
              ]
            }
          },
          "required": [
            "resolver",
            "server"
          ]
        },
        "metrics": {
          "properties": {
            "handlers": {
              "type": "array",
              "items": {
                "type": "object",
                "properties": {
                  "type": {
                    "type": "string",
                    "enum": ["prometheus"]
                  },
                  "prometheus": {
                    "properties": {
                      "maxTimeSeries": {
                        "type": "integer",
                        "multipleOf": 1.0,
                        "default": 10000,
                        "minimum": 0
                      },
                      "transports": {
                        "type": "array",
                        "items": {
                          "type": "object",
                          "properties": {
                            "type": {
                              "type": "string",
                              "enum": ["pull"]
                            },
                            "exposer": {
                              "type": "object",
                              "properties": {
                                "bindAddress": {
                                  "type": "string",
                                  "default": "0.0.0.0:9090"
                                },
                                "metricsPath": {
                                  "type": "string",
                                  "default": "/metrics"
                                },
                                "numThreads": {
                                  "type": "integer",
                                  "multipleOf": 1.0,
                                  "minimum": 2,
                                  "default": 2
                                }
                              },
                              "required": [
                                "bindAddress",
                                "metricsPath",
                                "numThreads"
                              ]
                            }
                          },
                          "required": ["type"],
                          "anyOf": [
                            {
                              "properties": {
                                "type": { "const": "pull" }
                              },
                              "required": ["exposer"]
                            }
                          ]
                        },
                        "minItems": 1
                      }
                    },
                    "type": "object",
                    "required": [
                      "maxTimeSeries",
                      "transports"
                    ]
                  }
                },
                "required": [
                  "type"
                ],
                "anyOf": [
                  {
                    "properties": {
                      "type": { "const": "prometheus" }
                    },
                    "required": ["prometheus"]
                  }
                ]
              },
              "minItems": 1
            }
          },
          "type": "object",
          "required": [
            "handlers"
          ]
        }
      },
      "required": [
        "apiVersion",
        "dns",
        "metrics"
      ]
    }
    )SCHEMA";
}
