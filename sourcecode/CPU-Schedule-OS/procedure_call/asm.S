.intel_syntax noprefix

.text
.global foo0
.global foo1
.global foo2
.global foo3
.global foo4
.global foo5
.global foo6
.global foo7
foo0:
    push rbp;
    mov rbp, rsp;
    sub rsp, 0x8;
    leave;
    ret;
foo1:
    push rbp;
    mov rbp, rsp;
    sub rsp, 0x8;
    leave;
    ret;
foo2:
    push rbp;
    mov rbp, rsp;
    sub rsp, 0x8;
    leave;
    ret;
foo3:
    push rbp;
    mov rbp, rsp;
    sub rsp, 0x8;
    leave;
    ret;
foo4:
    push rbp;
    mov rbp, rsp;
    sub rsp, 0x8;
    leave;
    ret;
foo5:
    push rbp;
    mov rbp, rsp;
    sub rsp, 0x8;
    leave;
    ret;
foo6:
    push rbp;
    mov rbp, rsp;
    sub rsp, 0x8;
    leave;
    ret;
foo7:
    push rbp;
    mov rbp, rsp;
    sub rsp, 0x10;
    movq r10, qword ptr[rbp-0x10];
    leave;
    ret;
