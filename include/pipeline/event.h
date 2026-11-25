//
// Created by Sebastian Sobczyński on 23/11/2026.
//

#pragma once
#include <chrono>
#include <variant>
#include <string>

namespace pipeline {
    enum class Severity {
        Info,
        Warning,
        Error,
        Critical
    };
    using Payload = std::variant<int, double, std::string>;

    struct Event {
        uint64_t id;
        Severity severity;
        std::chrono::steady_clock::time_point timestamp;
        std::string source;
        Payload data;

        Event(uint64_t id, Severity severity, Payload data, std::string source) :
            id(id), severity(severity), timestamp(std::chrono::steady_clock::now()), source(std::move(source)), data(std::move(data)) {}
    };
}
