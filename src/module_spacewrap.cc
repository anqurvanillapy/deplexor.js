#include "module_spacewrap.h"

#include "space.h"

namespace deplexor {

DEF_PERSISTENT_CTOR(spacewrap);

void
spacewrap::init()
{
	auto isolate = v8::Isolate::GetCurrent();

	auto functmpl = v8::FunctionTemplate::New(isolate,
											  ctor_defaultcb<spacewrap>);
	functmpl->SetClassName(utils::make_v8_string(isolate, classname));
	functmpl->InstanceTemplate()->SetInternalFieldCount(1);

	NODE_SET_PROTOTYPE_METHOD(functmpl, "id", id);
	NODE_SET_PROTOTYPE_METHOD(functmpl, "broadcast", brdcst);
	NODE_SET_PROTOTYPE_METHOD(functmpl, "broadcastSync", brdcst_sync);
	NODE_SET_PROTOTYPE_METHOD(functmpl, "exec", exec);
	NODE_SET_PROTOTYPE_METHOD(functmpl, "execSync", exec_sync);

	SET_PERSISTENT_CTOR(classname, functmpl->GetFunction());
}

} /* namespace deplexor */
