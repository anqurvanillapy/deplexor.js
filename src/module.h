#pragma once

#include <node.h>
#include <node_object_wrap.h>

#include "utils.h"

namespace deplexor {

#define DECL_PERSISTENT_CTOR \
	static v8::Persistent<v8::Function> ctor_

#define DEF_PERSISTENT_CTOR(classname) \
	v8::Persistent<v8::Function> classname::ctor_

#define GET_PERSISTENT_CTOR(classname) \
	v8::Local<v8::Function>::New(v8::Isolate::GetCurrent(), classname::ctor_)

#define EXPORT_OBJECTWRAP(exports, exportname, classname)           \
	exports->Set(v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), \
										 exportname),               \
				 GET_PERSISTENT_CTOR(classname))

template <typename TWrap>
inline void
ctor_defaultcb(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	auto isolate = v8::Isolate::GetCurrent();
	v8::HandleScope scope(isolate);

	JS_CHECK_ARG(isolate, args.Length() == 0, "no args for '%s' class ctor",
			  TWrap::classname);

	auto wrap = new TWrap;
}

} /* namespace deplexor */
