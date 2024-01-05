#ifndef SESSION_HPP_
#define SESSION_HPP_

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/strand.hpp>

#include <iostream>
#include <fstream>

#include "api.hpp"

namespace beast = boost::beast;		 // from <boost/beast.hpp>
namespace http = beast::http;		   // from <boost/beast/http.hpp>
namespace net = boost::asio;			// from <boost/asio.hpp>
namespace ssl = boost::asio::ssl;	   // from <boost/asio/ssl.hpp>
using tcp = boost::asio::ip::tcp;	   // from <boost/asio/ip/tcp.hpp>

class Session : public std::enable_shared_from_this<Session>
{
private:
	std::string host;
	std::string port;

	APICall* api_call;

	tcp::resolver resolver_;
	beast::ssl_stream<beast::tcp_stream> stream_;
	beast::flat_buffer buffer_;
	http::request<http::empty_body> req_;
	http::response<http::string_body> res_;

private:
	void OnResolve(beast::error_code,
					tcp::resolver::results_type /*results*/);

	void OnConnect(beast::error_code,
					tcp::resolver::results_type::endpoint_type /*endpoint*/);

	void OnHandshake(beast::error_code);

	void OnWrite(beast::error_code,
				 std::size_t /*bytes transferred*/);

	void OnRead(beast::error_code,
				std::size_t /*bytes transferred*/);

	void OnShutdown(beast::error_code);

	void WriteData();

public:
	Session(net::any_io_executor /*io*/,
			ssl::context& /*ssl context*/,
			APICall* /*api*/);
	
	~Session() = default;

	void Run();

};

#endif /* SESSION_HPP_ */