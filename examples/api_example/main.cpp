#include "../../api/include/client.hpp"

int main()
{
	using GET = Client;
	GET cli("AAPL", "NEWS_SENTIMENT");

	return 0;
}