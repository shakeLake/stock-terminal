#ifndef API_HPP_
#define API_HPP_

#include <string>

class APICall
{
private:
	std::string apiKey;
	std::string target;
	std::string command;

public:
	// Core Stock API
	// std::string TIME_SERIES_INTRADAY(std::string /*symbol*/, 
	// 								  std::string /*interval*/);

	// cryptocurrencies
	// std::string CURRENCY_EXCHANGE_RATE(std::string /* first */, 
	// 								   std::string /* second */);

	// Core Stock API
	std::string TIME_SERIES_DAILY(std::string /*symbol*/);

	// Alpha Intelligence
	std::string NEWS_SENTIMENT(std::string /*ticker*/);

public:
	APICall(std::string /* api key */,
			std::string /* ticker */,
			std::string& /* command */);

	APICall() = delete;
	~APICall() = default;

	std::string GetTicker();
	std::string GetTargetName();

};

#endif /* API_HPP_ */