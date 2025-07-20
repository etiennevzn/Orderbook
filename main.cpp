#include <iostream>
#include "Orderbook.cpp"

int main() {
    Orderbook orderbook;
    
    // Add a buy order
    auto buyOrder = std::make_shared<Order>(
        OrderType::GoodTillCancel,
        1001,                    // Order ID
        Side::Buy,
        Price{100},              // Price: $100
        Quantity{50}             // Quantity: 50 shares
    );
    
    auto trades = orderbook.AddOrder(buyOrder);
    
    // Add a matching sell order
    auto sellOrder = std::make_shared<Order>(
        OrderType::GoodTillCancel,
        1002,
        Side::Sell,
        Price{100},
        Quantity{30}
    );
    
    trades = orderbook.AddOrder(sellOrder);
    
    // Check orderbook state
    //Expected : 
    //Orders in book: 1
    //Trades executed: 1
    std::cout << "Orders in book: " << orderbook.Size() << std::endl;
    std::cout << "Trades executed: " << trades.size() << std::endl;
    
    return 0;
}