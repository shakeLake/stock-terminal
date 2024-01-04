#ifndef JSONPARSER_HPP_
#define JSONPARSER_HPP_

#include "newsclass.hpp"

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace boost::property_tree;

class JsonParser
{
private:
    ptree pt;

    std::ifstream cin;
    std::stringstream buffer;

public:
    JsonParser() = default;
    ~JsonParser() = default;

    std::vector<NewsItem> ReadNews(std::string);
    void ReadTimeSeries();

};

#endif /* JSONPARSER_HPP_ */