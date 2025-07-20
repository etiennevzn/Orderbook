#pragma once

#include "Order.h"

class OrderModify{
public:
    OrderModify(OrderId orderId, Side side, Price price, Quantity quantity):
        orderId_(orderId),
        side_(side),
        price_(price),
        quantity_(quantity)
    {}

    OrderId GetOrderId() const {return orderId_;}
    Side GetSide() const {return side_;}
    Price GetPrice() const {return price_;}
    Quantity GetQuantity() const {return quantity_;}

    OrderPointer ToOrderPointer(OrderType type) const { //type not necessary right now because the only type of order we can relly modify here is GoodTillCancel
                                                        //however adding type just to future-proof the code in case I add mode order types
        return std::make_shared<Order>(type, GetOrderId(), GetSide(), GetPrice(), GetQuantity()); 
    }

private:
    OrderId orderId_;
    Side side_;
    Price price_;
    Quantity quantity_;
};
