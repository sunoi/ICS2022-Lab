#include <stdint.h>

int64_t multimod(int64_t a, int64_t b, int64_t m) {
	int64_t sum = 0;
	while (a >= 1) {
		if (a&1 == 1) {
			sum = (sum+b)%m;
		}
		a = a >> 1;
		b = (b << 1)%m;
	}
  return sum;
}
