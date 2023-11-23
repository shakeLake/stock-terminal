#ifndef CLIENT_HPP_
#define CLIENT_HPP_

// from www.boost.org
#include "root_certificates.hpp"

#include "session.hpp"

class Client
{
private:
    net::io_context io_c;
    ssl::context ctx;

public:
    Client() = delete;
    Client(std::string& /*api key*/);

    ~Client();

};

#endif /* CLIENT_HPP */