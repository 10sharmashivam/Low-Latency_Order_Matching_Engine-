#pragma once

#include "order_book/order_book.hpp"
#include "utils/lock_free_queue.hpp"
#include <thread>

class MatchingEngine {
public:
    MatchingEngine();
    ~MatchingEngine();
    void start();
    void stop();
    void submit_order(const Order& order);

private:
    void worker_thread();

    OrderBook order_book_;
    LockFreeQueue<Order, 1024> order_queue_;
    std::thread worker_;
    bool running_;
};