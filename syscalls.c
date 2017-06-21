#include "syscalls.h"

/* SystemCall Read */
int read(unsigned int fd, void *buff, unsigned int bytes) {
    return _int80h(3, fd, (uint64_t) buff, bytes);
}

/* SystemCall Write */
int write(unsigned int fd, void *buff, unsigned int bytes) {
    return _int80h(4, fd, (uint64_t) buff, bytes);
}

/* SystemCall para malloc*/
void * res (unsigned int bytes) {
	return (void *) _int80h(5, bytes, 0, 0);
}

/* SystemCall para saber direccion de memoria*/
void * data_dir() {
    return (void *) _int80h(6, 0, 0, 0);
}

/* SystemCall Time */
int time(int selector) {
    return _int80h(7, selector, 0, 0);
}
/* Syscall Clear */
void clear(){
	return _int80h(8, 0, 0, 0);
}