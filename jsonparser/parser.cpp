#include "parser.hpp"

std::vector<NewsItem> JsonParser::ReadNews(std::string path)
{
    cin.open(path);
    buffer << cin.rdbuf();
    cin.close();

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