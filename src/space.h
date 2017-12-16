#pragma once

#include "common.h"
#include "result.h"

namespace deplexor {

using brdcst_cb_t = std::function<void(retno_t)>;
using brdcst_fn_t = std::function<void(const std::string&, brdcst_cb_t)>;

class space {
public:
/*
	explicit space(const std::string& id, const std::string& settings = "")
		: id_{id}
	{

	}
*/

	const std::string&  id() const { return id_; }
	void                brdcst(const std::string& src, brdcst_cb_t cb);
	retno_t             brdcst_sync(const std::string& src);
private:
	std::string id_;
	brdcst_fn_t brdcst_fn_;
};

} /* namepsace deplexor */
