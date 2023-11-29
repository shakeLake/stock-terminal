#include "parser.hpp"

JsonParser::JsonParser(std::string str)
{
    jsonparser.reset();
    jsonparser.write(str);
    jv = jsonparser.release();
    
    std::cout << jv << std::endl;
}