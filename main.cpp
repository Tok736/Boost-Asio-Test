
#include "Client.h"
#include "Host.h"


int main() {
    try {
        int port = 5512;
        boost::asio::io_context io_context;
        server s(io_context, port);
        io_context.run();
    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
