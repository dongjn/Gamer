#pragma once
#include<Windows.h>
#include<memory>
#define SUBHOOK_STATIC
#include"../thrid/subhook.h"
#ifdef __cplusplus
extern"C" {
#endif
	using std::shared_ptr;

#define DesHook(fn) shared_ptr<subhook::Hook> p##fn##Hook;
#define pHook(fn) p##fn##Hook
#define CreateHook(fn,mn) void* fn##_src_addr = GetProcAddress(mn,#fn);\
void* fn##_dst_addr = __##fn; \
pHook(fn) = std::make_shared<subhook::Hook>(fn##_src_addr,fn##_dst_addr);\
pHook(fn)->Install();

#ifdef __cplusplus
}
#endif
