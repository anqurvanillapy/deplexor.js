#pragma once

#include "common.h"
#include "retno.h"

namespace deplexor {

using brdcst_cb_t = std::function<void(retno_t)>;
using brdcst_fn_t = std::function<void(const std::string&, brdcst_cb_t)>;

class space {
public:
	const std::string& id() const { return id_; }
	void brdcst(const std::string& src, brdcst_cb_t cb);
private:
	std::string id_;
	brdcst_fn_t brdcst_fn_;
};

} /* namepsace deplexor */
