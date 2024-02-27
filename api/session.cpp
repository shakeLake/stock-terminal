#include "include/session.hpp"

Session::Session(net::any_io_executor ex,
				 ssl::context& ctx,
				 APICall* api) : resolver_(ex), stream_(ex, ctx)
{
	api_call = api;

	host = "www.alphavantage.co";
	port = "443";

	req_.version(11);
	req_.method(http::verb::get);

	if (api_call->GetTargetName() == "NEWS_SENTIMENT")
		req_.target(api_call->NEWS_SENTIMENT(api_call->GetTicker()));
	else if (api_call->GetTargetName() == "TIME_SERIES")
		req_.target(api_call->TIME_SERIES(api_call->GetTicker()));
	else if (api_call->GetTargetName() == "STOCK_PRICE")
	{
		req_.target(api_call->STOCK_PRICE(api_call->GetTicker()));
		host = "query1.finance.yahoo.com";
	}
	else
		std::cerr << "Target Error" << '\n';

	req_.set(http::field::host, host);
	req_.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
}


void Session::Run()
{
	// set SNI hostname
	if (! SSL_set_tlsext_host_name(stream_.native_handle(), host.c_str()))
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

	beast::get_lowest_layer(stream_).expires_after(std::chrono::seconds(5));

	http::async_write(stream_, req_, 
						beast::bind_front_handler(
							&Session::OnWrite,
							shared_from_this()
						));
}

void Session::OnWrite(beast::error_code ec,
					  std::size_t bytes_transfered)
{
	boost::ignore_unused(bytes_transfered);

	if (ec)
	{
		std::cerr << ec.message() << std::endl;
		return;
	}

	http::async_read(stream_, buffer_, res_, 
					beast::bind_front_handler(
						&Session::OnRead, 
						shared_from_this()
					));
}

auto ReadPrice = [](std::string ticker)
{
	std::stringstream buffer;

	std::ifstream cin;
	cin.open("BUFFER");
	buffer << cin.rdbuf();
	cin.close();

	ptree pt;
	json_parser::read_json(buffer, pt);
	std::string price = pt.get<std::string>("chart.result..meta.regularMarketPrice");

	std::ofstream out("prices", std::ifstream::app);
	out << ticker + ' ' + price + '\n';
	out.close();
};

void Session::WriteData()
{
	std::string name;
	std::ofstream out;

	if (api_call->GetTargetName() == "STOCK_PRICE")
	{
		name = "BUFFER";
		out.open(name);
		out << res_.body();
		out.close();

		ReadPrice(api_call->GetTicker());
	}
	else
	{
		name = api_call->GetTargetName() + "_" + api_call->GetTicker() + ".json";						
		out.open(name);
		out << res_.body();
		out.close();
	}
}

void Session::OnRead(beast::error_code ec, 
					 std::size_t bytes_transfered)
{
	boost::ignore_unused(bytes_transfered);

	if (ec)
	{
		std::cerr << ec.message() << std::endl;
		return;
	}

	WriteData();

	stream_.async_shutdown(beast::bind_front_handler(
								&Session::OnShutdown,
								shared_from_this()
							));
}

void Session::OnShutdown(beast::error_code ec)
{
	if (ec == net::error::eof)
		ec = {};

	if (ec)
	{
		std::cerr << ec.message() << '\n';
		return;
	}
}