#pragma once
#include <atomic>
#include <vector>
#include <optional>

namespace engine
{

    template <typename T>
    class LockFreeQueue
    {
    private:
        std::vector<T> buffer;
        size_t capacity;
        std::atomic<size_t> head{0}; // Read index
        std::atomic<size_t> tail{0}; // Write index

    public:
        explicit LockFreeQueue(size_t size) : buffer(size), capacity(size) {}

        // Called by OrderBook (Producer) - Non-blocking
        bool push(const T &item)
        {
            size_t current_tail = tail.load(std::memory_order_relaxed);
            size_t next_tail = (current_tail + 1) % capacity;

            // Check if full (next tail would overwrite head)
            if (next_tail == head.load(std::memory_order_acquire))
            {
                return false;
            }

            buffer[current_tail] = item;
            tail.store(next_tail, std::memory_order_release);
            return true;
        }

        // Called by Logger Thread (Consumer)
        std::optional<T> pop()
        {
            size_t current_head = head.load(std::memory_order_relaxed);

            if (current_head == tail.load(std::memory_order_acquire))
            {
                return std::nullopt; // Empty
            }

            T item = buffer[current_head];
            head.store((current_head + 1) % capacity, std::memory_order_release);
            return item;
        }
    };

}