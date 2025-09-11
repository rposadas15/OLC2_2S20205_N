.section .data
mensaje:    .asciz "Hola mundo\n"

.section .text
.global _start

_start:
    // write(int fd, const void *buf, size_t count)
    mov     x0, 1              // fd = 1 (stdout)
    ldr     x1, =mensaje       // buf = dirección del mensaje
    mov     x2, 11             // count = longitud del mensaje
    mov     x8, 64             // syscall número 64 = write
    svc     0                  // llamada al sistema

    // exit(int status)
    mov     x0, 0              // status = 0
    mov     x8, 93             // syscall número 93 = exit
    svc     0