#ifndef BOOST_ASIO_TEST_SESSION_H
#define BOOST_ASIO_TEST_SESSION_H

#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <vector>

#include "ThreadSafeQueue.h"

using boost::asio::ip::tcp;

class Session {
private:
    typedef boost::system::error_code errorCode;
    tcp::socket socket_;
    enum { max_length = 1024 };
    char data_[max_length];
    ThreadSafeQueue<std::string> _queue;

    void handleRead(const errorCode& error, size_t bytes) {
        if (!error) {
            std::string temp(data_);
            write(temp, bytes);
        }
    }

    void handleWrite(const errorCode& error, size_t) {
        if (!error) {
            socket_.async_read_some(boost::asio::buffer(data_, max_length),
                                    [this](const errorCode& error, size_t bytes) {
                this->handleRead(error, bytes);
            });
        }
    }

    void read() {
        if (isConnected()) {
            socket_.async_read_some(boost::asio::buffer(data_, max_length),
                                    [this](const errorCode& error, size_t bytes) {
                                        this->handleRead(error, bytes);
                                    });
        }
    }
    void write(std::string data, size_t bytes) {
        if (isConnected()) {
            boost::asio::async_write(socket_,
                                     boost::asio::buffer(data, bytes),
                                     [this](const errorCode& error, size_t bytes) {
                                         this->handleWrite(error, bytes);
                                     });
        }
    }
public:
    Session(boost::asio::io_context& io_context) : socket_(io_context) {}
    tcp::socket& socket() {
        return socket_;
    }
    bool isConnected() {
        return socket_.is_open();
    }
    std::vector<std::string> getAll() {
        return _queue.popAll();
    }
    void run() {
        read();
    }
};


#endif //BOOST_ASIO_TEST_SESSION_H
