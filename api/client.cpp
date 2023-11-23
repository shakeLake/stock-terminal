#include "include/client.hpp"

Client::Client(std::string& api_key)
{
    ssl::context ctx {ssl::context::tlsv12_client};
    load_root_certificates(ctx);
    ctx.set_verify_mode(ssl::verify_peer);

    std::make_shared<Session>(net::make_strand(io_c),ctx)->run("www.alphavantage.co",
                                                                "443");
}

~Client::Client()
{
    // stop here
    io_c.run();
}