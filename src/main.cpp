#include "order_book/matching_engine.hpp"
#include "networking/unix_socket.hpp"

/**
 * @brief Entry point of the order matching engine application.
 *
 * Initializes and starts the MatchingEngine to handle order processing.
 * Sets up a Unix domain socket server to listen for incoming FIX messages
 * and process client connections.
 *
 * The server runs indefinitely, handling incoming connections and messages.
 *
 * @return Exit status of the application.
 */

int main() {
    MatchingEngine engine;
    engine.start();

    UnixSocketServer server("/tmp/order_engine.sock");
    server.run();

    return 0;
}