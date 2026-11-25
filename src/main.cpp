//
// Created by Sebastian Sobczyński on 23/11/2026.
//

#include <iostream>
#include <thread>
#include "pipeline/event.h"
#include "pipeline/thread_safe_queue.h"


int main() {
    pipeline::ThreadSafeQueue<pipeline::Event> queue;

    std::jthread consumer([&queue]() {
        while (auto event = queue.pop()) {
            std::cout << "[Consumer] Event id: " << event->id << " Source: " << event->source << std::endl;
        }
        std::cout << "Consumer queue drained. Exiting cleanly." << std::endl;
    });

    std::jthread producer([&queue]() {
        for (u_int64_t i = 1; i <= 5; ++i) {
            queue.push(pipeline::Event{
                i,
                pipeline::Severity::Info,
                "network_module",
                "Packet received: #" + std::to_string(i)
            });
        }
        queue.stop();
    });

    return 0;
}