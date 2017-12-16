#pragma once

#include "common.h"
#include "cowork.h"

namespace deplexor {

#define RETNO_DEF(symbol, ...) DEPLEX_RETNO_##symbol

enum retno_t : uint32_t {
	RETNO_DEF(SUCCESS,          "Success"),
	RETNO_DEF(UNDEFINED,        "Undefined"),
	RETNO_DEF(TIMEOUT,          "Request timed out"),
	RETNO_DEF(RTERR,            "Deplex runtime error"),
	RETNO_DEF(BRDCST_ERR,       "Failed to broadcast code in space"),
	RETNO_DEF(SPACE_INIT_ERR,   "Space init error"),
	RETNO_DEF(V8_INIT_ERR,      "Failed to init v8"),
};

struct result_t {
	retno_t retno;
	std::string err;
	std::string retval;
	mutable std::unique_ptr<cowork::cowork_ctx> cw_ctx;
};

} /* namespace deplexor */
