#include "include/client.hpp"

Client::Client(std::string api_key) : ctx(ssl::context::tlsv12_client)
{
    std::cout << api_key << std::endl;

    load_root_certificates(ctx);
    ctx.set_verify_mode(ssl::verify_peer);

    std::make_shared<Session>(net::make_strand(io_c), ctx)->Run();
}

Client::~Client()
{
    // stop here
    io_c.run();
}