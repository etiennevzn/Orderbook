#include <iostream>
#include "Orderbook.cpp"

int main(){
    //Most basic test, advanced are in the OrderbookTest folder
    Orderbook orderbook;
    const OrderId orderId = 1;
    orderbook.AddOrder(std::make_shared<Order>(OrderType::GoodTillCancel, orderId, Side::Buy, 100, 10));
    std::cout<< orderbook.Size() <<std::endl;
    orderbook.CancelOrder(orderId);
    std::cout<< orderbook.Size() <<std::endl;
    return 0;
}