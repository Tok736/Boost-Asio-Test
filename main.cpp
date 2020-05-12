
#include <iostream>

#include "Client.h"
#include "Host.h"

using boost::asio::ip::tcp;

enum { max_length = 1024 };

int main() {

    char answer;
    std::cout << "h - Host, c - client: ";
    std::cin >> answer;

    switch (answer) {
        case 'h': {

            using namespace std; // For atoi.
            int port = 5000;
            Server s(port);

            bool running = true;
            int answ;
            std::cout << "1 - run, 2 - stop, 3 - exit" << std::endl;
            while (running) {
                std::cin >> answ;
                switch (answ) {
                    case 1: {
                        s.run();
                        std::cout << "Running" << std::endl;
                        break;
                    }
                    case 2: {
                        s.stop();
                        std::cout << "Stopped" << std::endl;
                        break;
                    }
                    case 3: {
                        s.stop();
                        running = false;
                        std::cout << "Exited" << std::endl;
                        break;
                    }
                }
            }
            break;
        }
        case 'c':
            try
            {
                boost::asio::io_context io_context;

                const char* host = "127.0.0.1";
                const char* port = "5000";

                tcp::resolver resolver(io_context);
                tcp::resolver::results_type endpoints =
                        resolver.resolve(tcp::v4(), host, port);

                tcp::socket s(io_context);
                boost::asio::connect(s, endpoints);

                using namespace std; // For strlen.
                std::cout << "Enter message: ";
                char request[max_length];
                std::cin.getline(request, max_length);
                std::cin.getline(request, max_length);
                size_t request_length = strlen(request);
                boost::asio::write(s, boost::asio::buffer(request, request_length));

                char reply[max_length];
                size_t reply_length = boost::asio::read(s,
                                                        boost::asio::buffer(reply, request_length));
                std::cout << "Reply is: ";
                std::cout.write(reply, reply_length);
                std::cout << "\n";
            }
            catch (std::exception& e)
            {
                std::cerr << "Exception: " << e.what() << "\n";
            }



            break;
    }

    return 0;
}

