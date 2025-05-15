#pragma once

#include "order.hpp"
#include <map>
#include <unordered_map>

class OrderBook {
public:
    void add_order(const Order& order);
    void cancel_order(uint64_t order_id);
    bool match_orders(Order& new_order); // Returns true if order is fully/partially filled

private:
    std::map<double, std::vector<Order>, std::greater<>> bids_; // Price -> Orders (descending)
    std::map<double, std::vector<Order>> asks_;                 // Price -> Orders (ascending)
    std::unordered_map<uint64_t, Order> orders_;               // Order ID -> Order
};