#include "include/session.hpp"

Session::Session(net::any_io_executor ex,
                 ssl::context& ctx) : resolver_(ex), stream_(ex, ctx)
{
    host = "www.alphavantage.co";
    port = "443";

    req_.version(11);
    req_.method(http::verb::get);
    // req_.target("TARGET");
    req_.set(http::field::host, host);
    req_.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
}


void Session::Run()
{
    // set SNI hostname
    if (! SSL_set_tlsext_host_name(stream_.native_handle(), &host))
    {
        beast::error_code ec{static_cast<int>(::ERR_get_error()), net::error::get_ssl_category()};

        std::cerr << ec.message() << '\n';        
        return;
    }


    resolver_.async_resolve(host,
                            port,
                            beast::bind_front_handler(
                                &Session::OnResolve,
                                shared_from_this()
                            ));
}

void Session::OnResolve(beast::error_code ec,
                        tcp::resolver::results_type results)
{
    if (ec)
    {
        std::cerr << "OnResolve: " << ec.message() << '\n';
        return;
    }

    beast::get_lowest_layer(stream_).expires_after(std::chrono::seconds(30));

    beast::get_lowest_layer(stream_).async_connect(results,
                                                    beast::bind_front_handler(
                                                        &Session::OnConnect,
                                                        shared_from_this()
                                                    ));
}

void Session::OnConnect(beast::error_code ec, tcp::resolver::results_type::endpoint_type)
{
    if (ec)
    {
        std::cerr << "OnConnect: " << ec.message() << '\n';
        return;
    }

    stream_.async_handshake(ssl::stream_base::client,
                            beast::bind_front_handler(
                                &Session::OnHandshake,
                                shared_from_this()
                            ));
}

void Session::OnHandshake(beast::error_code ec)
{
    if (ec)
    {
        std::cerr << "OnHandshake: " << ec.message() << '\n';
        return;
    }

    beast::get_lowest_layer(stream_).expires_after(std::chrono::seconds(30));
}