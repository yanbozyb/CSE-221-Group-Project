#include <stdlib.h>
#include "inline_hooker.h"
#include <string.h>
#include <sys/mman.h>

#define ASM_MOV_EAX(addr) { 0xb8, addr&0xFF, (addr>>8)&0xFF, (addr>>16)&0xFF, (addr>>24)&0xFF }

// for my own convenience
// this can only be used to jump to functions in non-PIE binaries
// (i.e. binaries that are not compiled with -fPIE)
// since I don't want to deal with tons of code/context recovery, too lazy
char *install_syscall_user_hook(uintptr_t hook_addr, 
                              uintptr_t jump_addr, 
                              uint64_t original_rax) {
    // we already know the syscall number,
    // so use rax to store our jump address
    // asm('mov eax, 0x4000000') b'\xb8\x00\x00@\x00', takes only 5 bytes, that's why we disable PIE
    // asm('call rax')   b'\xff\xd0'

    // most syscall wrappers have code pattern like this:
    // mov eax, syscall_number
    // syscall
    // so we can just overwrite the first 7 bytes of the wrapper, and replace the syscall instruction with a jump

    // remap the page to be writable
    char *orig_code = malloc(7);
    memcpy(orig_code, (void *)hook_addr, 7);

    mprotect((void *)(hook_addr & ~0xfff), 0x1000, PROT_READ | PROT_WRITE | PROT_EXEC);
    char jump_code[5] = ASM_MOV_EAX(jump_addr);
    memcpy((void *)hook_addr, jump_code, 5);
    memcpy((void *)(hook_addr + 5), "\xff\xd0", 2);

    mprotect((void *)(hook_addr & ~0xfff), 0x1000, PROT_READ | PROT_EXEC);
    return orig_code;
}
