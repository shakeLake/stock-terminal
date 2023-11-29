#ifndef JSONPARSER_HPP_
#define JSONPARSER_HPP_

#include <boost/json/basic_parser_impl.hpp>
#include <boost/json.hpp>
#include <boost/json/src.hpp>
#include <iostream>

using namespace boost::json;

class JsonParser
{
private:
    parser jsonparser;
    value jv;

public:
    JsonParser() = delete;

    JsonParser(std::string);
    ~JsonParser() = default;

    std::string Get(std::string);

};

#endif /* JSONPARSER_HPP_ */