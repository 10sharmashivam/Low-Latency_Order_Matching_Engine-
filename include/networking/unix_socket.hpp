#pragma once

#include <string>

class UnixSocketServer {
public:
    UnixSocketServer(const std::string& socket_path);
    ~UnixSocketServer();
    void run();

private:
    int server_fd_;
    std::string socket_path_;
};