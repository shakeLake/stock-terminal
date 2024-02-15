#include "../../api/include/client.hpp"

int main()
{
	using GET = Client;
	GET cli("AAPL", "STOCK_PRICE");

	return 0;
}