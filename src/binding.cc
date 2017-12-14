#include "binding.h"

#include "module_spacewrap.h"

namespace deplexor {

void
init(v8::Local<v8::Object> exports, v8::Local<v8::Object> module)
{
	spacewrap::init();

	EXPORT_OBJECTWRAP(exports, "SpaceWrap", spacewrap);
}

} /* namespace deplexor */
