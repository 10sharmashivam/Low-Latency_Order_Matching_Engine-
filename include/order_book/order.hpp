#pragma once

#include <cstdint>
#include <string>

enum class OrderType { BUY, SELL };
enum class OrderStatus { PENDING, FILLED, CANCELED };

struct Order {
    uint64_t order_id;
    OrderType type;
    double price;
    uint32_t quantity;
    OrderStatus status;
    std::string client_id;
};