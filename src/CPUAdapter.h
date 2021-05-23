#pragma once

#if defined __x86_64__ || defined _M_X64
#define x64 1
#elif defined __aarch64__ || defined _M_ARM
#define arm64 1
#else
#error "unsupported CPU"
#endif