#include <stdint.h>

uint64_t multimod(uint64_t a, uint64_t b, uint64_t m) {
	uint64_t sum = 0;
	while (a >= 1) {
		if (a&1 == 1) {
			sum = (sum+b)&(m-1);
		}
		a = a >> 1;
		b = (b << 1)&(m-1);
	}
  return sum;
}
