#pragma once

#include <iostream>
#include <sstream>
#include <v8.h>

#include "utils_v8.h"

#define IGNORE_EXPR_RET(expr) do {  \
		auto _ = (expr);            \
		(void)_;                    \
	} while (0)

static constexpr size_t MAX_ASSERT_SIZE = 512;

#define RT_ASSERT(expr, format, ...) do {                                   \
	if (!(expr)) {                                                          \
		char buf[MAX_ASSERT_SIZE];                                          \
		int siz = snprintf(buf, MAX_ASSERT_SIZE, format, ##__VA_ARGS__);    \
		if (siz >= 0) {                                                     \
			std::cerr << "Deplexor assertion failed: `" << #expr << "' in " \
					  << __FILE__ << ", line " << __LINE__ << ": " << buf   \
					  << "." << std::endl;                                  \
		}                                                                   \
		std::terminate();                                                   \
	}                                                                       \
} while (0)

#define RT_ABORT(buf) RT_ASSERT(false, buf)

#define JS_ASSERT(isolate, expr, format, ...) do {                          \
	if (!(expr)) {                                                          \
		char buf[MAX_ASSERT_SIZE];                                          \
		int siz = snprintf(buf, MAX_ASSERT_SIZE, format, ##__VA_ARGS__);    \
		RT_ASSERT(siz >= 0, "format failed, maybe a bad format string");    \
		std::stringstream ss;                                               \
		ss << __FUNCTION__ << ":" << __LINE__ << ": " << buf;               \
		auto localstr = deplexor::utils::make_v8_string(isolate, ss.str()); \
		isolate->ThrowException(v8::Exception::TypeError(localstr));        \
	}                                                                       \
} while (0)
