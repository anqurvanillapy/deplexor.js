#include "module_spacewrap.h"

#include "space.h"
#include "async.h"
#include "retno.h"

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

v8::Local<v8::Object>
spacewrap::new_instance(std::unique_ptr<space> pxy)
{
	auto isolate = v8::Isolate::GetCurrent();
	auto context = isolate->GetCurrentContext();

	auto ctor = GET_PERSISTENT_CTOR(spacewrap);
	auto obj = ctor->NewInstance(context).ToLocalChecked();
	auto wrap = node::ObjectWrap::Unwrap<spacewrap>(obj);

	wrap->space_pxy_ = std::move(pxy);
	return obj;
}

void
spacewrap::id(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	auto isolate = v8::Isolate::GetCurrent();
	auto wrap = node::ObjectWrap::Unwrap<spacewrap>(args.Holder());
	args.GetReturnValue().Set(utils::make_v8_string(isolate,
													wrap->space_pxy_->id()));
}

void
spacewrap::brdcst(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	auto isolate = v8::Isolate::GetCurrent();

	JS_ASSERT(isolate, args[0]->IsString(),
			  "arg #1 of space.broadcast must be a string");
	JS_ASSERT(isolate, args[1]->IsFunction(),
			  "arg #2 of space.broadcast must be a function");

	v8::String::Utf8Value src(args[0]->ToString());

	do_async_work(v8::Local<v8::Function>::Cast(args[1]),
		[&args, &src](std::function<void(void*)> cmpl) {
			auto wrap = ObjectWrap::Unwrap<spacewrap>(args.Holder());
			wrap->space_pxy_->brdcst(*src, [cmpl = std::move(cmpl)](retno_t n) {
				cmpl(reinterpret_cast<void*>(static_cast<uintptr_t>(n)));
			});
		},
		[](auto js_cb, void* result) {
			auto isolate = v8::Isolate::GetCurrent();
			v8::HandleScope scope(isolate);
			auto icxt = isolate->GetCurrentContext();
			
			std::vector<v8::Local<v8::Value>> argv;
			auto n = static_cast<retno_t>(reinterpret_cast<uintptr_t>(result));
			argv.emplace_back(v8::Uint32::NewFromUnsigned(isolate, n));
			auto ret = js_cb->Call(icxt,
								   icxt->Global(),
								   static_cast<int>(argv.size()),
								   argv.data());
			(void)ret;
		}
	);
}

} /* namespace deplexor */
