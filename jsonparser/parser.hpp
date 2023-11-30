#ifndef JSONPARSER_HPP_
#define JSONPARSER_HPP_

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <iostream>

using namespace boost::property_tree;

class JsonParser
{
public:
    JsonParser() = delete;

    JsonParser(std::string);
    ~JsonParser() = default;

};

#endif /* JSONPARSER_HPP_ */