#ifndef SESSION_HPP_
#define SESSION_HPP_

class Session : public std::enable_shared_from_this<Session>
{
private:
    tcp::resolver resolver_;
    beast::ssl_stream<beast::tcp_stream> stream_;
    beast::flat_buffer buffer_;
    http::request<http::empty_body> req_;
    http::response<http::string_body> res_;

private:
    void Run(std::string& /*host*/,
             std::string& /*port*/,
             std::string& /*target*/
             int /*version*/)

    void OnResolve(beast::error_code,
                    tcp::resolver::results_type /*results*/);

    void OnConnect(beast::error_code,
                    tcp::resolver::results_type::endpoint_type /*endpoint*/);

    void OnHandshake(beast::error_code);

    void OnWrite(beast::error_code,
                std::size_t /*bytes transferred*/);

    void OnRead(beast::error_code,
                std::size_t /*bytes transferred*/)

    void OnShutdown(beast::error_code)

public:
    Session(net::any_io_executor /*io*/,
            ssl::context& /*ssl context*/);

};

#endif /* SESSION_HPP_ */