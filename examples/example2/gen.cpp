// gen.exe --problem AplusB --std std.exe --validator val.exe

#include "testlib.h"
#include "data_maker.h"

const int W = 1e9;

inline void gen() {
	print("%d %d\n", rnd.next(-W, W), rnd.next(-W, W));
}

int main(int argc, char** argv) {
	registerGen(argc, argv, 1);
	registerDataMaker(argc, argv);
	
	mkr.generate(gen, 10);
	return 0;
}
