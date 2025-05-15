#include "order_book/order_book.hpp"

void OrderBook::add_order(const Order& order) {
    orders_[order.order_id] = order;
    if (order.type == OrderType::BUY) {
        bids_[order.price].push_back(order);
    } else {
        asks_[order.price].push_back(order);
    }
}

void OrderBook::cancel_order(uint64_t order_id) {
    auto it = orders_.find(order_id);
    if (it != orders_.end()) {
        it->second.status = OrderStatus::CANCELED;
        // Remove from bids/asks (simplified, requires price lookup in production)
    }
}

bool OrderBook::match_orders(Order& new_order) {
    if (new_order.type == OrderType::BUY) {
        auto ask_it = asks_.begin();
        while (ask_it != asks_.end() && new_order.quantity > 0 && new_order.price >= ask_it->first) {
            auto& orders = ask_it->second;
            for (auto& ask : orders) {
                if (ask.status != OrderStatus::PENDING) continue;
                uint32_t matched_qty = std::min(new_order.quantity, ask.quantity);
                new_order.quantity -= matched_qty;
                ask.quantity -= matched_qty;
                if (new_order.quantity == 0) new_order.status = OrderStatus::FILLED;
                if (ask.quantity == 0) ask.status = OrderStatus::FILLED;
            }
            ask_it = asks_.erase(ask_it);
        }
    } else {
        // Similar logic for SELL orders matching against bids
    }
    return new_order.status == OrderStatus::FILLED;
}