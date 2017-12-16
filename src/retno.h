#pragma once

#define RETNO_DEF(symbol, ...) DEPLEX_RETNO_##symbol

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef enum retno_t {
	RETNO_DEF(SUCCESS,          "Success"),
	RETNO_DEF(UNDEFINED,        "Undefined"),
	RETNO_DEF(TIMEOUT,          "Deplex runtime error"),
	RETNO_DEF(RTERR,            "Deplex runtime error"),
	RETNO_DEF(BRDCST_ERR,       "Failed to broadcast code in space"),
	RETNO_DEF(SPACE_INIT_ERR,   "Space init error"),
	RETNO_DEF(V8_INIT_ERR,      "Failed to broadcast code in space"),
} retno_t;

#ifdef __cplusplus
}
#endif /* __cplusplus */
