#pragma once

#include <v8.h>

namespace deplexor {
namespace utils {

inline v8::Local<v8::String>
make_v8_string(v8::Isolate *isolate, const char* str, int length = -1)
{
	return v8::String::NewFromUtf8(isolate, str, v8::NewStringType::kNormal,
								   length).ToLocalChecked();
}

inline v8::Local<v8::String>
make_v8_string(v8::Isolate *isolate, const std::string& str)
{
	return make_v8_string(isolate, str.c_str(), static_cast<int>(str.length()));
}

} /* namespace utils */
} /* namepsace deplexor */
