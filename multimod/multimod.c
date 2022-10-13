#include <stdint.h>

uint64_t myMod(uint64_t a, uint64_t m) {
	while (a >= m) {
		a -= m;
	}
	return a;
}

uint64_t multimod(uint64_t a, uint64_t b, uint64_t m) {
	uint64_t sum = 0;
	while (a >= 1) {
		if (a&1 == 1) {
			sum = myMod(sum+b, m);
		}
		a = a >> 1;
		b = myMod((b << 1), m);
	}
  return sum;
}
