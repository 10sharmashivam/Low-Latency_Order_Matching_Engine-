#include "utils/lock_free_queue.hpp"

// Explicit template instantiation for common types
template class LockFreeQueue<int, 1024>; // Example instantiation