#pragma once

#include "module.h"

namespace deplexor {

class shbuf;

class shbufwrap : public node::ObjectWrap {
public:
	static constexpr const char* classname = "DeplexArrayBuffer";
	static void init();
	static v8::Local<v8::Object> new_instance(std::unique_ptr<shbuf> space_pxy);
private:
	DECL_PERSISTENT_CTOR;

	template <typename T>
	friend void ctor_defaultcb(const v8::FunctionCallbackInfo<v8::Value>& args);

	std::unique_ptr<shbuf> shbuf_pxy_;
};

} /* namespace deplexor */
