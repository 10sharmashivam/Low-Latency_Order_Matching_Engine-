# Low-Latency Order Matching Engine

A high-performance order matching engine designed for financial markets, built with C++20 and optimized for low-latency operations.

## Features

- **High-Performance Order Matching**: Implements a fast and efficient order matching algorithm
- **Lock-Free Data Structures**: Utilizes lock-free queues for concurrent operations
- **Unix Socket Communication**: Fast IPC using Unix domain sockets
- **Modern C++**: Built with C++20 features and best practices
- **Optimized Build**: Compiler optimizations enabled for maximum performance

## Tech Stack

### Core Technologies
- **Programming Languages**:
  - C++20 (Core Engine)
  - Python 3.x (Testing & Utilities)
- **Build System**: CMake 3.16+
- **Containerization**: Docker & Docker Compose

### Dependencies
- **C++ Dependencies**:
  - yaml-cpp: Configuration management and parsing
  - pthread: POSIX threads for concurrent operations
  - Standard Library: C++20 STL features
- **Python Dependencies**:
  - Standard Library: socket, time

### Development & Build Tools
- **Compiler**: GCC/Clang with C++20 support
- **Optimization Flags**:
  - `-O3`: Maximum optimization level
  - `-march=native`: CPU-specific optimizations
- **Version Control**: Git

### Architecture Components
- **Core Engine**: C++20-based order matching system
- **Testing & Utilities**: Python-based order injector and testing tools
- **Concurrency**: Lock-free data structures and queues
- **IPC**: Unix Domain Sockets for inter-process communication
- **Configuration**: YAML-based configuration system
- **Testing**: Unit testing framework (planned)

### Deployment
- **Containerization**: Docker-based deployment
- **Environment**: Linux-based systems
- **Build Process**: Multi-stage Docker builds

## Project Structure

```
├── include/           # Header files
│   ├── order_book/   # Order book related headers
│   ├── networking/   # Network communication headers
│   └── utils/        # Utility functions and data structures
├── src/              # Source files
│   ├── order_book/   # Order book implementation
│   ├── networking/   # Network communication implementation
│   └── utils/        # Utility implementations
├── tests/            # Test files
├── config/           # Configuration files
└── scripts/          # Build and utility scripts
```

## Requirements

- C++20 compatible compiler
- CMake 3.16 or higher
- yaml-cpp library
- pthread library

## Building the Project

```bash
mkdir build
cd build
cmake ..
make
```

## Usage

After building, run the order matching engine:

```bash
./order_engine
```

## Performance Considerations

- The engine is compiled with `-O3` optimization level
- Uses native CPU architecture optimizations (`-march=native`)
- Implements lock-free data structures for concurrent operations
- Utilizes Unix domain sockets for fast IPC

