#include <stdint.h>
#include <stdio.h>

int getBit(uint64_t a) {
	int i=0;
	for (i=1; a > 0; i++)
		a >>= 1;
	return i;
}

uint64_t Mod(uint64_t a, uint64_t m) {
	if (a < m) return a;
	int bitA=getBit(a);
	int bitB=getBit(m);
	uint64_t M = m << (bitA-bitB);
	while (M >= m) {
		if (a >= M) {
			a = a - M;
		}
		M = M >> 1;
	}
	return a;
}

/*
uint64_t Mod(uint64_t a, uint64_t m) {
	while (a >= m) {
		a -= m;
	}
	return a;
}*/

uint64_t multimod(uint64_t a, uint64_t b, uint64_t m) {
	uint64_t sum = 0;
	while (a >= 1) {
		if ((a&1) == 1) {
			sum = Mod(sum + b, m);
		}
		a = a >> 1;
		b = Mod((b << 1), m);
	}
  return sum;
}
