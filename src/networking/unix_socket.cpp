#include "networking/unix_socket.hpp"
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <stdexcept>

/**
 * @brief Constructor for UnixSocketServer.
 *
 * Creates a Unix domain socket and binds it to the given path.
 * If the socket already exists, it is removed.
 * The socket is then set to listen with a backlog of 10.
 *
 * If any of the socket operations fail, a std::runtime_error is thrown.
 *
 * @param socket_path The path to bind the socket to.
 */
UnixSocketServer::UnixSocketServer(const std::string& socket_path) : socket_path_(socket_path) {
    server_fd_ = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_fd_ == -1) throw std::runtime_error("Socket creation failed");

    struct sockaddr_un addr = {};
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, socket_path.c_str(), sizeof(addr.sun_path) - 1);
    unlink(socket_path.c_str()); // Remove existing socket
    if (bind(server_fd_, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
        throw std::runtime_error("Bind failed");
    }
    if (listen(server_fd_, 10) == -1) throw std::runtime_error("Listen failed");
}

/**
 * @brief Destructor for UnixSocketServer.
 *
 * Closes the server file descriptor and unlinks the socket path,
 * ensuring cleanup of resources associated with the Unix domain socket.
 */

UnixSocketServer::~UnixSocketServer() {
    close(server_fd_);
    unlink(socket_path_.c_str());
}

/**
 * @brief Starts the Unix domain socket server.
 *
 * Creates an epoll instance and adds the server file descriptor to it.
 * Then, it enters an infinite loop, waiting for incoming connections
 * and processing them.
 *
 * When a new connection is accepted, the client file descriptor is
 * added to the epoll instance for monitoring.
 *
 * When a client sends a message, it is processed (simplified, just echoed
 * back) and the client file descriptor is removed from the epoll instance
 * if the client has disconnected.
 */
void UnixSocketServer::run() {
    int epoll_fd = epoll_create1(0);
    if (epoll_fd == -1) throw std::runtime_error("Epoll creation failed");

    struct epoll_event ev = {};
    ev.events = EPOLLIN;
    ev.data.fd = server_fd_;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_fd_, &ev);

    struct epoll_event events[10];
    while (true) {
        int nfds = epoll_wait(epoll_fd, events, 10, -1);
        for (int i = 0; i < nfds; ++i) {
            if (events[i].data.fd == server_fd_) {
                int client_fd = accept(server_fd_, nullptr, nullptr);
                ev.events = EPOLLIN;
                ev.data.fd = client_fd;
                epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, &ev);
            } else {
                char buffer[1024];
                ssize_t bytes = read(events[i].data.fd, buffer, sizeof(buffer));
                if (bytes <= 0) {
                    epoll_ctl(epoll_fd, EPOLL_CTL_DEL, events[i].data.fd, nullptr);
                    close(events[i].data.fd);
                } else {
                    // Process FIX message (simplified)
                    write(events[i].data.fd, buffer, bytes); // Echo back
                }
            }
        }
    }
}