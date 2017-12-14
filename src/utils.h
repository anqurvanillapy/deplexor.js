#pragma once

#include <sstream>
#include <v8.h>

static constexpr size_t MAX_ASSERT_SIZE = 512;

#define THROW

#define JS_ASSERT(isolate, expr, format, ...) { \
	if (!(expr)) { \
		char buf[MAX_ASSERT_SIZE]; \
		int siz = vnsprintf(buf, MAX_ASSERT_SIZE, format, ##__VA_ARGS__); \
		UTIL_ASSERT(siz >= 0, "format failed, maybe a bad format string"); \
		std::stringstream ss; \
		ss << __FUNCTION__ << ":" << __LINE__ << ": " << buf; \
		isolate->ThrowExeception(v8::Exeception::TypeError(/* TODO: V8 string */)); \
	} \
}
