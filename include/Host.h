#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <map>
#include <memory>
#include <thread>
#include <utility>

#include "ServerSession.h"


using boost::asio::ip::tcp;

class Server {
private:
    typedef boost::system::error_code errorCode;
    typedef std::shared_ptr<Session> sessionPtr;

    std::map<std::string, sessionPtr> sessions;
    sessionPtr testSession;
    std::shared_ptr<boost::asio::io_context> context;
    std::shared_ptr<tcp::acceptor> acceptor;

    void startAccept() {
        sessionPtr newSession = std::make_shared<Session>(*context);
        acceptor->async_accept(newSession->socket(),
                               [newSession, this](const boost::system::error_code& error) {
                                   handleAccept(newSession, error);
        });
    }
    void handleAccept(sessionPtr newSession, const errorCode& error) {
        if (!error) {
            testSession = std::move(newSession);
//            sessions.emplace("Player", temp);
            testSession->run();
//            sessions["Player"]->run();
            startAccept();
        }
        else {

        }
    }
public:
    Server(short port) {
        context = std::make_shared<boost::asio::io_context>();
        acceptor = std::make_shared<tcp::acceptor>(*context, tcp::endpoint(tcp::v4(), port));
    }
    void run() {
        startAccept();
        std::thread thread([this]() {
            this->context->run();
        });
        thread.detach();
    }
    void stop() {
        context->stop();
    }
};

