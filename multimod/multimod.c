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


uint64_t multimod(uint64_t a, uint64_t b, uint64_t m) {
	uint64_t sum = 0;
	//printf("m=%lu\n", ~m);
	while (a >= 1) {
		if ((a&1) == 1) {
			uint64_t temp = sum + b;
			if (temp < sum || temp < b) {
				//printf("%lu  ", temp);
				temp = Mod(Mod(temp, m) + (~m)+1, m);
				//printf("temp=%lu\n", temp);
			}
			sum = Mod(temp, m);
		}
		a = a >> 1;
		if (b << 1 < b) {
			b = Mod((b << 1) + (~m) + 1, m);
		}
		else b = Mod((b << 1), m);
	}
  return sum;
}
