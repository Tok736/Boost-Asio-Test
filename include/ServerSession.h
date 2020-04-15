#ifndef BOOST_ASIO_TEST_SESSION_H
#define BOOST_ASIO_TEST_SESSION_H

#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class session {
private:
    tcp::socket socket_;
    enum { max_length = 1024 };
    char data_[max_length];
    void handle_read(const boost::system::error_code& error, size_t bytes_transferred) {
        if (!error) {
            boost::asio::async_write(socket_,
                                     boost::asio::buffer(data_, bytes_transferred),
                                     boost::bind(&session::handle_write, this,
                                                 boost::asio::placeholders::error));
        }
        else {
            delete this;
        }
    }
    void handle_write(const boost::system::error_code& error) {
        if (!error) {
            socket_.async_read_some(boost::asio::buffer(data_, max_length),
                                    boost::bind(&session::handle_read, this,
                                                boost::asio::placeholders::error,
                                                boost::asio::placeholders::bytes_transferred));
        }
        else {
            delete this;
        }
    }
public:
    session(boost::asio::io_context& io_context): socket_(io_context) { }
    tcp::socket& socket() {
        return socket_;
    }
    void start() {
        socket_.async_read_some(boost::asio::buffer(data_, max_length),
                                boost::bind(&session::handle_read, this,
                                            boost::asio::placeholders::error,
                                            boost::asio::placeholders::bytes_transferred));
    }
};

#endif //BOOST_ASIO_TEST_SESSION_H
