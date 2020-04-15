#ifndef BOOST_ASIO_TEST_HOST_H
#define BOOST_ASIO_TEST_HOST_H

#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

#include "ServerSession.h"

using boost::asio::ip::tcp;

class server {
private:
    boost::asio::io_context& io_context_;
    tcp::acceptor acceptor_;

    void start_accept() {
        session* new_session = new session(io_context_);
        acceptor_.async_accept(new_session->socket(),
                               boost::bind(&server::handle_accept, this, new_session,
                                           boost::asio::placeholders::error));
    }
    void handle_accept(session* new_session, const boost::system::error_code& error) {
        if (!error) {
            new_session->start();
        }
        else {
            delete new_session;
        }

        start_accept();
    }
public:
    server(boost::asio::io_context& io_context, short port) : io_context_(io_context), acceptor_(io_context, tcp::endpoint(tcp::v4(), port))
    {
        start_accept();
    }
};

#endif //BOOST_ASIO_TEST_HOST_H
