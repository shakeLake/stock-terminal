#include "../../jsonparser/parser.hpp"
#include <fstream>

int main()
{
    // std::ifstream cin("fl.json");
    // std::stringstream buffer;
    // buffer << cin.rdbuf();

    // std::string str = buffer.str();

    ptree pt;
    json_parser::read_json("fl.json", pt);

    std::vector<std::string> r;
    for (auto& item : pt.get_child("feed.authors"))
        r.push_back(item.second.get_value<std::string>());

    for (auto i : r)
        std::cout << i << std::endl;

    // JsonParser test(str);

    return 0;
}