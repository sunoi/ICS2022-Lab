#include "asm.h"
#include <string.h>

int64_t asm_add(int64_t a, int64_t b) {
  asm ("add %[src1], %[src2];"
			:[src2]"+r"(b), [src1]"+r"(a)
			);
	return b;
}

int asm_popcnt(uint64_t x) {
  int s = 0;
  /*for (int i = 0; i < 64; i++) {
    if ((x >> i) & 1) s++;
  }*/
	asm ("mov $0x0,%%ecx;"
			 "mov $0x0,%%edx;"
			 "mov %[x],%%rsi;"
			 "L1: mov %%rsi,%%rax;"
			 "shr %%ecx,%%rax;"
			 "add $0x1,%%ecx;"
			 "and $0x1,%%eax;"
			 "add %%eax,%%edx;"
			 "mov %%edx,%[s];"
			 "cmp $0x40,%%ecx;"
			 "jne L1;"
			 :[s]"+r"(s)
			 :[x]"m"(x)
			 :"%ecx","%edx","%rsi","%rax","%eax"
			);
  return s;
}

void *asm_memcpy(void *dest, const void *src, size_t n) {
	asm ("mov %[dest],%%rdi;"
			 "mov %[src],%%rsi;"
		 	 "mov %[n],%%rdx;"
			 "mov %%rdi,%%rax;"
			 "xor %%ecx,%%ecx;"
			 "L2:movzbl (%%rsi,%%rcx,1),%%r8d;"
			 "mov %%r8b,(%%rax,%%rcx,1);"
			 "add $0x1,%%rcx;"
			 "cmp %%rcx,%%rdx;"
			 "jne L2;"
			 :
			 :[dest]"r"(dest), [src]"r"(src), [n]"r"(n)
			 :"%rdi","%edx","%rsi","%rax","%ecx","%rcx","%rdx"
			);
	return dest;
}

int asm_setjmp(asm_jmp_buf env) {
  return setjmp(env);
	//asm ("mov %[env] "
			
	//	);
}

void asm_longjmp(asm_jmp_buf env, int val) {
  longjmp(env, val);
}
