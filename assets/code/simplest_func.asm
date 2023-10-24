foo:
    push rbp;
    mov rbp, rsp;
    sub rsp, 0x8;
    ; do something with RDI
    leave;
    ret;