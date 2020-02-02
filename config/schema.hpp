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
          "enum": ["v0.1.0"],
          "default": "v0.1.0"
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
                    "address": {
                      "type": "string",
                      "default": "udp://0.0.0.0:5353"
                    },
                    "maxConnections": {
                      "type": "number",
                      "minimum": 0,
                      "default": 100
                    }
                  },
                  "required": [
                    "address",
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
        }
      },
      "required": [
        "apiVersion",
        "dns"
      ]
    }
    )SCHEMA";
}
