#include "parser.hpp"

std::vector<NewsItem> JsonParser::ReadNews(std::string path)
{
	cin.open(path);
	buffer << cin.rdbuf();
	cin.close();

	ptree pt;

	json_parser::read_json(buffer, pt);

	int size = pt.get<int>("items");
	std::vector<NewsItem> news;
	news.resize(size);

	int i = 0;
	for (auto& item : pt.get_child("feed"))
	{
		news[i].title = item.second.get<std::string>("title");
		news[i].url = item.second.get<std::string>("url");
		news[i].summary = item.second.get<std::string>("summary");
		i += 1;
	}

	return news;
}

auto GetTimeStamp = [](std::string time) -> double
					{
						std::tm t {};
						std::istringstream iss(time);
						
						iss >> std::get_time(&t, "%Y-%m-%d");

						std::time_t time_stamp = mktime(&t);
						
						return static_cast<double>(time_stamp);
					};

std::vector<TimeSeries> JsonParser::ReadTimeSeries(std::string path)
{
	cin.open(path);
	buffer << cin.rdbuf();
	cin.close();

	ptree pt;

	json_parser::read_json(buffer, pt);

	std::vector<TimeSeries> ts;

	std::array<double, 5> arr;
	for (auto& item : pt.get_child("Monthly Time Series"))
	{
		TimeSeries buf;
		buf.timestamp = GetTimeStamp(item.first);

		int i = 0;
		for (auto& sitem : item.second)
			arr[i++] = sitem.second.get_value<double>(); 

		buf.open   = arr[0];
		buf.high   = arr[1];
		buf.low    = arr[2];
		buf.close  = arr[3];
		buf.volume = arr[4];

		ts.push_back(buf);
	}

	return ts;
}