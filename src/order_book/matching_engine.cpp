#include "order_book/matching_engine.hpp"
#include <sched.h> // For CPU pinning

MatchingEngine::MatchingEngine() : running_(false) {
    // Pin thread to core 0 for determinism
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(0, &cpuset);
    sched_setaffinity(0, sizeof(cpuset), &cpuset);
}

MatchingEngine::~MatchingEngine() { stop(); }

void MatchingEngine::start() {
    running_ = true;
    worker_ = std::thread(&MatchingEngine::worker_thread, this);
}

void MatchingEngine::stop() {
    running_ = false;
    if (worker_.joinable()) worker_.join();
}

void MatchingEngine::submit_order(const Order& order) {
    order_queue_.push(order);
}

void MatchingEngine::worker_thread() {
    Order order;
    while (running_) {
        if (order_queue_.pop(order)) {
            if (order_book_.match_orders(const_cast<Order&>(order))) {
                // Order filled, notify client (simplified)
            } else {
                order_book_.add_order(order);
            }
        }
    }
}