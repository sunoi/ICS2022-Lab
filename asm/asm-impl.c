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
	asm ("xor %%ecx,%%ecx;"
			 "xor %%edx,%%edx;"
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
			 "xor %%rcx,%%rcx;"
			 "L2:movzbl (%%rsi,%%rcx,1),%%r8d;"
			 "mov %%r8b,(%%rax,%%rcx,1);"
			 "add $0x1,%%rcx;"
			 "cmp %%rcx,%%rdx;"
			 "jne L2;"
			 :
			 :[dest]"r"(dest), [src]"r"(src), [n]"r"(n)
			 :"%rdi","%rsi","%rax","%rcx","%rdx"
			);
	return dest;
}

int asm_setjmp(asm_jmp_buf env) {
  //return setjmp(env);
	asm ("mov %[env],%%rdi;"
			 "pop %%rsi;"
			 "movq %%rbx,(%%rdi);"
			 "movq %%rsp,8(%%rdi);"
			 "push %%rsi;"
			 "movq %%rbp,16(%%rdi);"
			 "movq %%r12,24(%%rdi);"
			 "movq %%r13,32(%%rdi);"
			 "movq %%r14,40(%%rdi);"
			 "movq %%r15,48(%%rdi);"
			 "movq %%rsi,56(%%rdi);"
			 "xor %%eax,%%eax;"
			 :
			 :[env]"r"(env)
			 :
			 //:"%rdi","%rbx","%rbp","%r12","%r13","%r14","%r15","%eax"
		);
	return 0;
}

void asm_longjmp(asm_jmp_buf env, int val) {
  asm ("mov %[val],%%eax;"
			 "mov %[env],%%rdi;"
			 "movq %%rdi,%%rbx;"
			 "movq 8(%%rdi),%%rsp;"
			 "movq 16(%%rdi),%%rbp;"
			 "movq 24(%%rdi),%%r12;"
			 "movq 32(%%rdi),%%r13;"
			 "movq 40(%%rdi),%%r14;"
			 "movq 48(%%rdi),%%r15;"
			 "jmp *56(%%rdi);"
			 :
			 :[val]"r"(val),[env]"r"(env)
			 //:
			 :"%eax","%rdi","%rbx","%rbp","%r12","%r13","%r14","%r15"
			);
	//longjmp(env, val);
}
