#include "include/api.hpp"

APICall::APICall(std::string api, std::string ticker, std::string& cmd)
{
	apiKey = api;
	target = ticker;
	command = cmd;
}

std::string APICall::GetTicker()
{
	return target;
}

std::string APICall::GetTargetName()
{
	return command;
}

std::string APICall::TIME_SERIES_DAILY(std::string symbol)
{
	std::string target =	"/query?function=TIME_SERIES_DAILY&symbol=" 
							+ symbol 
							+ "&outputsize=full"
							+ "&apikey="
							+ apiKey;

	return target;
}

std::string APICall::NEWS_SENTIMENT(std::string ticker)
{
	std::string target =	"/query?function=NEWS_SENTIMENT&tickers=" 
							+ ticker 
							+ "&apikey="
							+ apiKey;

	return target;
}

std::string APICall::STOCK_PRICE(std::string ticker)
{
	std::string target = "/v8/finance/chart/"
						 + ticker
						 + R"(?region=US&lang=en-US&includePrePost=false&interval=2m&useYfid=true&range=1d&corsDomain=finance.yahoo.com&.tsrc=finance)";

	return target;
}

// std::string APICall::TIME_SERIES_INTRADAY(std::string symbol, 
// 										  std::string interval)
// {
// 	std::string target =	"/query?function=TIME_SERIES_INTRADAY&symbol=" 
// 							+ symbol 
// 							+ "&interval=" 
// 							+ interval 
// 							+ "min&apikey="
// 							+ apiKey;

// 	return target;
// }
// std::string APICall::CURRENCY_EXCHANGE_RATE(std::string first, 
// 											std::string second)
// {
// 	std::string target =	"/query?function=CURRENCY_EXCHANGE_RATE&from_currency=" 
// 							+ first 
// 							+ "&to_currency="
// 							+ second
// 							+ "&apikey="
// 							+ apiKey;

// 	return target;
// }