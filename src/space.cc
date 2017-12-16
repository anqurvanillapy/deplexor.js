#include "space.h"

#include "common.h"
#include "retno.h"

namespace deplexor {

void
space::brdcst(const std::string& src, brdcst_cb_t cb)
{
	brdcst_fn_(src, cb);
}

retno_t
space::brdcst_sync(const std::string& src)
{
	std::promise<retno_t> prom;
	auto fut = prom.get_future();

	brdcst(src, [&prom](retno_t ret) {
		prom.set_value(ret);
	});

	return fut.get();
}

} /* namespace deplexor */
