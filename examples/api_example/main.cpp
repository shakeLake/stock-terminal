#include "../../api/include/client.hpp"

int main()
{
	using GET = Client;
	GET cli("AAPL", "TIME_SERIES_DAILY");

	return 0;
}