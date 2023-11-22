#ifndef CLIENT_HPP_
#define CLIENT_HPP_

class Client
{
private:
    net::io_context io_c;
    ssk::context ctx;

public:
    Client() = delete;
    Client(std::string& /*api key*/);

    ~Client() = default;

};

#endif /* CLIENT_HPP */