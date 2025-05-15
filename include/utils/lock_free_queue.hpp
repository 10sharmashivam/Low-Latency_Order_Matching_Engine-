#pragma once

#include <atomic>
#include <cstddef>
#include <stdexcept>

template <typename T, size_t Capacity>
class LockFreeQueue {
public:
    LockFreeQueue() : head_(0), tail_(0) {}

    /**
     * Attempts to add an item to the queue.
     *
     * @param item The item to be added to the queue.
     * @return true if the item was successfully added, false if the queue is full.
     */

    /**
     * Attempts to add an item to the queue.
     *
     * @param item The item to be added to the queue.
     * @return true if the item was successfully added, false if the queue is full.
     *
     * This function is lock-free but not wait-free. If the queue is full, it will return false rather than blocking.
     */
    bool push(const T& item) {
        size_t current_tail = tail_.load(std::memory_order_relaxed);
        size_t next_tail = (current_tail + 1) % Capacity;

        if (next_tail == head_.load(std::memory_order_acquire)) {
            return false; // Queue is full
        }

        buffer_[current_tail] = item;
        tail_.store(next_tail, std::memory_order_release);
        return true;
    }

    /**
     * Attempts to remove an item from the queue.
     *
     * @param item A reference to the variable where the removed item will be stored.
     * @return true if an item was successfully removed, false if the queue is empty.
     *
     * This function is lock-free but not wait-free. If the queue is empty, it will return false rather than blocking.
     */

    bool pop(T& item) {
        size_t current_head = head_.load(std::memory_order_relaxed);
        if (current_head == tail_.load(std::memory_order_acquire)) {
            return false; // Queue is empty
        }

        item = buffer_[current_head];
        head_.store((current_head + 1) % Capacity, std::memory_order_release);
        return true;
    }

    /**
     * Returns true if the queue is empty, false otherwise.
     *
     * This function is lock-free but not wait-free. If the queue is empty, it will return true rather than blocking.
     */
    bool empty() const {
        return head_.load(std::memory_order_acquire) == tail_.load(std::memory_order_acquire);
    }

private:
    alignas(64) std::atomic<size_t> head_; // Cache line alignment
    alignas(64) std::atomic<size_t> tail_;
    T buffer_[Capacity];
};