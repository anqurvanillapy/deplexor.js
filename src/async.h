#pragma once

#include <node.h>
#include <uv.h>
#include "common.h"

namespace deplexor {

using async_work_t      = std::function<void*()>;
using cmpl_work_t       = std::function<void(std::function<void(void*)>)>;
using async_cmpl_cb_t   = std::function<void(v8::Local<v8::Function>, void*)>;

struct cmpl_ctx_t {
	uv_async_t                      work;
	v8::Persistent<v8::Function>    js_cb;
	void*                           result{};
	async_cmpl_cb_t                 cmpl_cb;
};

inline void
run_cmpl_cb(uv_async_t* work)
{
	auto isolate = v8::Isolate::GetCurrent();
	v8::HandleScope scope(isolate);

	auto ctx = static_cast<cmpl_ctx_t*>(work->data);
	auto jscb = v8::Local<v8::Function>::New(isolate, ctx->js_cb);
	ctx->cmpl_cb(jscb, ctx->result);

	uv_close(reinterpret_cast<uv_handle_t*>(work), [](uv_handle_t* work) {
		auto ctx = static_cast<cmpl_ctx_t*>(work->data);
		ctx->js_cb.Reset();
		delete ctx;
	});
}

inline void
do_async_work(v8::Local<v8::Function> js_cb,
			  const cmpl_work_t& cmpl_work,
			  async_cmpl_cb_t cmpl_cb)
{
	auto isolate = v8::Isolate::GetCurrent();
	v8::HandleScope scope(isolate);

	auto ctx = new cmpl_ctx_t(); // deleted on run_cmpl_cb
	ctx->work.data = ctx;
	ctx->js_cb.Reset(isolate, js_cb);
	ctx->cmpl_cb = std::move(cmpl_cb);

	uv_async_init(uv_default_loop(), &ctx->work, run_cmpl_cb);

	cmpl_work([ctx](void* result) {
		ctx->result = result;
		uv_async_send(&ctx->work);
	});
}

} /* namespace deplexor */
