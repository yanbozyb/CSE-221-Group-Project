#ifndef INLINE_HOOKER
#define INLINE_HOOKER

#include <stdint.h>

char *install_syscall_user_hook(uintptr_t hook_addr,
                                uintptr_t jump_addr,
                                uint64_t original_rax);

#endif
