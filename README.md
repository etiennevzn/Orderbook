# Orderbook Implementation

A modern, thread-safe orderbook implementation in C++20 for financial trading systems.

## Features

- **Multiple Order Types Support:**
  - GoodTillCancel (GTC)
  - FillAndKill (FAK)  
  - FillOrKill (FOK)
  - Market Orders
  - GoodForDay (GFD)

- **High Performance:**
  - Optimized price-time priority matching
  - Memory-efficient design

- **Complete Order Management:**
  - Add orders
  - Modify existing orders
  - Cancel orders
  - Real-time order matching

- **Comprehensive Testing:**
  - Parameterized unit tests with Google Test
  - File-based test scenarios
  - Automated CI-ready test suite

## Architecture

```
├── Core Classes:
│   ├── Orderbook     - Main orderbook engine
│   ├── Order         - Individual order representation  
│   ├── Trade         - Trade execution details
│   └── OrderModify   - Order modification operations
│
├── Order Types:
│   ├── GoodTillCancel - Remains until filled or canceled
│   ├── FillAndKill   - Fill partially, cancel remainder
│   ├── FillOrKill    - Fill completely or cancel entirely
│   ├── GoodForDay    - Valid until end of trading day (Pruning managed by a thread)
│   └── Market        - Execute at best available price
│
└── Data Structures:
    ├── Price-Time Priority Queue
    ├── Fast Order Lookup (O(1))
    └── Efficient Price Level Management
```

## Build Requirements

- **C++20** compatible compiler (MSVC 19.29+, GCC 10+, Clang 12+)
- **CMake 3.12+**
- **Git** (for Google Test dependency)

## Quick Start

### 1. Clone the Repository
```bash
git clone https://github.com/your-username/orderbook.git
cd orderbook
```

### 2. Setup Google Test
```bash
cd OrderbookTest
git submodule add https://github.com/google/googletest.git googletest
```

### 3. Build and Run Tests
```bash
mkdir build && cd build
cmake ..
cmake --build . --config Release

# Copy test files to build directory (choose your platform)
cp -r ../TestFiles ./TestFiles                                    # Linux/Mac
xcopy ..\TestFiles .\TestFiles /E /I                             # Windows CMD
Copy-Item -Path ..\TestFiles -Destination .\TestFiles -Recurse   # PowerShell

# Run the test suite
./Release/mytests.exe    # Windows
./mytests               # Linux/Mac
```

## Usage Example

```cpp
#include "Orderbook.h"
#include "Order.h"

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
    std::cout << "Orders in book: " << orderbook.Size() << std::endl;
    std::cout << "Trades executed: " << trades.size() << std::endl;
    
    return 0;
}
```

## Testing

The project includes comprehensive test coverage with file-based test scenarios:

```
OrderbookTest/
├── mytests.cpp              # Main test suite
├── TestFiles/               # Test scenario files
│   ├── Match_GoodTillCancel.txt
│   ├── Match_FillAndKill.txt
│   ├── Match_FillOrKill_Hit.txt
│   ├── Match_FillOrKill_Miss.txt
│   ├── Cancel_Success.txt
│   ├── Modify_Side.txt
│   └── Match_Market.txt
└── CMakeLists.txt
```

### Test File Format
```
A B GoodTillCancel 100 10 1001    # Add Buy GTC order: $100, qty 10, ID 1001
A S GoodTillCancel 100 5  1002    # Add Sell GTC order: $100, qty 5, ID 1002
M 1001 B 101 10                   # Modify order 1001: new price $101
C 1002                            # Cancel order 1002
R 1 1 0                           # Expected result: 1 total, 1 bid, 0 ask
```

### Run Specific Tests
```bash
# Run all tests
./Release/mytests.exe

# Run with verbose output
./Release/mytests.exe --gtest_verbose

# List all test cases
./Release/mytests.exe --gtest_list_tests
```
## Configuration

### Compiler Options
- **C++20 Standard:** Required for `std::format`, `std::from_chars`
- **Runtime Library:** Dynamic linking (`/MD` on MSVC)
- **Optimization:** Release builds recommended for performance

## Performance Characteristics

| Operation | Time Complexity | Description |
|-----------|----------------|-------------|
| Add Order | O(log n) | Insert into price-time priority structure |
| Cancel Order | O(1) | Direct lookup and removal |
| Modify Order | O(log n) | Cancel + Add operation |
| Match Orders | O(m) | Where m = number of matched orders |
| Get Order Info | O(1) | Direct access to order levels |

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
