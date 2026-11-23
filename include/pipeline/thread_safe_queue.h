//
// Created by Sebastian Sobczyński on 23/11/2026.
//

#pragma once

#include <condition_variable>
#include <mutex>
#include <optional>
#include <queue>
#include <utility>

namespace pipeline {

    template <typename T>
    class ThreadSafeQueue {
    public:
        ThreadSafeQueue() = default;
        ~ThreadSafeQueue() = default;

        ThreadSafeQueue(const ThreadSafeQueue&) = delete;
        ThreadSafeQueue& operator=(const ThreadSafeQueue&) = delete;
        ThreadSafeQueue(ThreadSafeQueue&&) = delete;
        ThreadSafeQueue& operator=(ThreadSafeQueue&&) = delete;

        void push(T item) {
            {
                std::lock_guard<std::mutex> lock(mutex_);
                if (stopped_) {
                    return;
                }
                queue_.push(std::move(item));
            }
            cv_.notify_one();
        }

        [[nodiscard]] std::optional<T> pop() {
            std::unique_lock<std::mutex> lock(mutex_);

            cv_.wait(lock, [this] {
                return !queue_.empty() || stopped_;
            });

            if (queue_.empty()) {
                return std::nullopt;
            }

            T item = std::move(queue_.front());
            queue_.pop();
            return item;
        }

        void stop() {
            {
                std::lock_guard<std::mutex> lock(mutex_);
                stopped_ = true;
            }
            cv_.notify_all();
        }

        [[nodiscard]] bool empty() const {
            std::lock_guard<std::mutex> lock(mutex_);
            return queue_.empty();
        }

    private:
        mutable std::mutex mutex_;
        std::condition_variable cv_;
        std::queue<T> queue_;
        bool stopped_{false};
    };

}