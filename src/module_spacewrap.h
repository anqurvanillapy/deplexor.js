#pragma once

#include "module.h"

namespace deplexor {

class space;

class spacewrap : public node::ObjectWrap {
public:
	static constexpr const char* classname = "SpaceWrap";
	static void init();
	static v8::Local<v8::Object> new_instance(std::unique_ptr<space> space_pxy);
private:
	DECL_PERSISTENT_CTOR;

	template <typename T>
	friend void ctor_defaultcb(const v8::FunctionCallbackInfo<v8::Value>& args);

	static void id(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void brdcst(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void brdcst_sync(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void exec(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void exec_sync(const v8::FunctionCallbackInfo<v8::Value>& args);

	std::unique_ptr<space> space_pxy_;
};

} /* namespace deplexor */
