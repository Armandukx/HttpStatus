#pragma once
#include <array>
#include <string_view>
#include <algorithm>

namespace HttpStatus {

    struct StatusEntry {
        int code;
        std::string_view reason;
    };

    /// @brief Compile-time sorted array of HTTP status codes and their phrases.
    inline const std::array<StatusEntry, 64> kStatusTable = { 
        {
            {0, "No Response / Unknown Error"},
            {100, "Continue"}, {101, "Switching Protocols"}, {102, "Processing"}, {103, "Early Hints"},
            {200, "OK"}, {201, "Created"}, {202, "Accepted"}, {203, "Non-Authoritative Information"},
            {204, "No Content"}, {205, "Reset Content"}, {206, "Partial Content"}, {207, "Multi-Status"},
            {208, "Already Reported"}, {226, "IM Used"}, {300, "Multiple Choices"},
            {301, "Moved Permanently"}, {302, "Found"}, {303, "See Other"}, {304, "Not Modified"},
            {305, "Use Proxy"}, {307, "Temporary Redirect"}, {308, "Permanent Redirect"},
            {400, "Bad Request"}, {401, "Unauthorized"}, {402, "Payment Required"}, {403, "Forbidden"},
            {404, "Not Found"}, {405, "Method Not Allowed"}, {406, "Not Acceptable"},
            {407, "Proxy Authentication Required"}, {408, "Request Timeout"}, {409, "Conflict"},
            {410, "Gone"}, {411, "Length Required"}, {412, "Precondition Failed"},
            {413, "Payload Too Large"}, {414, "URI Too Long"}, {415, "Unsupported Media Type"},
            {416, "Range Not Satisfiable"}, {417, "Expectation Failed"}, {418, "I'm a teapot"},
            {421, "Misdirected Request"}, {422, "Unprocessable Entity"}, {423, "Locked"},
            {424, "Failed Dependency"}, {425, "Too Early"}, {426, "Upgrade Required"},
            {428, "Precondition Required"}, {429, "Too Many Requests"},
            {431, "Request Header Fields Too Large"}, {451, "Unavailable For Legal Reasons"},
            {500, "Internal Server Error"}, {501, "Not Implemented"}, {502, "Bad Gateway"},
            {503, "Service Unavailable"}, {504, "Gateway Timeout"}, {505, "HTTP Version Not Supported"},
            {506, "Variant Also Negotiates"}, {507, "Insufficient Storage"}, {508, "Loop Detected"},
            {510, "Not Extended"}, {511, "Network Authentication Required"},
        } 
    };

    /// @brief Returns the reason phrase for a given HTTP status code.
    /// @param code HTTP status code (e.g. 404)
    /// @return Corresponding reason phrase or "Unknown HTTP Status Code"
    inline std::string_view GetReasonPhrase(int code) {
        auto it = std::lower_bound(kStatusTable.begin(), kStatusTable.end(), code,
            [](const StatusEntry& entry, int value) {
                return entry.code < value;
            });

        if (it != kStatusTable.end() && it->code == code)
            return it->reason;

        return "Unknown HTTP Status Code";
    }

    /// @brief Returns true if code is informational (1xx)
    inline constexpr bool IsInformational(int code) { return code >= 100 && code < 200; }

    /// @brief Returns true if code indicates success (2xx)
    inline constexpr bool IsSuccess(int code) { return code >= 200 && code < 300; }

    /// @brief Returns true if code indicates redirection (3xx)
    inline constexpr bool IsRedirection(int code) { return code >= 300 && code < 400; }

    /// @brief Returns true if code indicates client error (4xx)
    inline constexpr bool IsClientError(int code) { return code >= 400 && code < 500; }

    /// @brief Returns true if code indicates server error (5xx)
    inline constexpr bool IsServerError(int code) { return code >= 500 && code < 600; }

    /// @brief Returns true if code is any error (client or server)
    inline constexpr bool IsError(int code) {
        return IsClientError(code) || IsServerError(code);
    }

} // namespace HttpStatus
