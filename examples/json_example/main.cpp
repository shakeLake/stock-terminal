#include "../../jsonparser/parser.hpp"
#include <fstream>

int main()
{
	std::ifstream cin("fl.json");
	std::stringstream buffer;
	buffer << cin.rdbuf();
	cin.close();

	// std::string str = buffer.str();

	ptree pt;
	json_parser::read_json(buffer, pt);

	int test = pt.get<int>("items");
	std::cout << test << std::endl;

	// authors
	for (auto& item : pt.get_child("feed"))
	{
		for (auto& sitem : item.second.get_child("authors"))
		{
			std::string tst = sitem.second.get_value<std::string>();
			std::cout << tst << std::endl;
		}
	}

	// titles
	std::vector<std::string> r;
	for (auto& item : pt.get_child("feed"))
		r.push_back(item.second.get<std::string>("title"));
	
	for (int i = 0; i < r.size(); ++i)
		std::cout << "Title: " << r[i] << '\n' << std::endl;

	return 0;
}