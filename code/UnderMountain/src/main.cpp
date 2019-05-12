#include <boost/asio/strand.hpp>

#include "http_request.h"
#include "listener.h"

namespace net = boost::asio;            // from <boost/asio.hpp>

#define SERVER_PORT 8080
#define ADDRESS "0.0.0.0"
#define STATIC_ROOT "static"

int main(int argc, char *argv[]) {

    auto const address = net::ip::make_address(ADDRESS);
    auto const port = static_cast<unsigned short>(SERVER_PORT);
    auto const doc_root = std::make_shared<std::string>(STATIC_ROOT);
    auto const threads = 2;

    // The io_context is required for all I/O
    net::io_context ioc{threads};

    // Create and launch a listening port
    std::make_shared<listener>(
            ioc,
            tcp::endpoint{address, port},
            doc_root
    )->run();

    // Run the I/O service on the requested number of threads
    std::vector<std::thread> v;
    v.reserve(threads - 1);
    for (auto i = threads - 1; i > 0; --i)
        v.emplace_back(
                [&ioc] {
                    ioc.run();
                });
    ioc.run();

    return EXIT_SUCCESS;
}