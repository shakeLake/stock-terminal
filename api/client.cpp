#include "include/client.hpp"

Client::Client() : ctx(ssl::context::tlsv12_client)
{
	load_root_certificates(ctx);
	ctx.set_verify_mode(ssl::verify_peer);

	api = new APICall("JSADHCT02WL4A3Y1");
	std::make_shared<Session>(net::make_strand(io_c), ctx, api)->Run();
}

Client::~Client()
{
	// stop here
	io_c.run();
}