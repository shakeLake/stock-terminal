#ifndef NEWSCLASS_HPP_
#define NEWSCLASS_HPP_

#include <string>

class NewsItem
{
public:
    std::string title;
    std::string summary;
    std::string url;

public:
    NewsItem() = default;
    ~NewsItem() = default;

};

#endif /* NEWSCLASS_HPP_ */