#include "space.h"

namespace deplexor {

void
space::brdcst(const std::string& src, brdcst_cb_t cb)
{
	brdcst_fn_(src, cb);
}

} /* namespace deplexor */
