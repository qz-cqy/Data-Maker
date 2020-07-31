#ifndef _RAND_MAKER_H_
#define _RAND_MAKER_H_ 1

#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>

int randint(int a, int b);
double uniform();

int randint(int a, int b) {
	return rand() % (b-a+1) + a;
}
double uniform() {
	return 1.0 * rand() / rand();
}

#endif
