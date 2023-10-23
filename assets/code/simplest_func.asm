foo:
    push rbp;
    mov rbp, rsp;
    sub rsp, 0x8;
    movq qword ptr[rbp-0x8], rdi;
    leave;
    ret;