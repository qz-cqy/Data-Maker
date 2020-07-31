# Data Maker

## What is Data Maker?

Maybe it is a better way to generate answer files by input files.

## Examples (in windows)

Example 1 (A+B problem):

```cpp
#include "testlib.h"
#include "data_maker.h"

const int W = 1e9;

inline void gen() {
	print("%d %d\n", rnd.next(-W, W), rnd.next(-W, W));
}

int main(int argc, char** argv) {
	registerGen(argc, argv, 1);
	
	mkr.setProblemName("AplusB");
	mkr.setStdName("std.exe");
	mkr.setValidatorName("val.exe");
	mkr.generate(gen, 10); // generate AplusB1.in/.ans, AplusB2.in/.ans, ..., AplusB10.in/.ans
	return 0;
}
```

Example 2 (still A+B problem):

```cpp
// command line arguments: gen.exe --problem AplusB --std std.exe --validator val.exe

#include "testlib.h"
#include "data_maker.h"

const int W = 1e9;

inline void gen() {
	print("%d %d\n", rnd.next(-W, W), rnd.next(-W, W));
}

int main(int argc, char** argv) {
	registerGen(argc, argv, 1);
	registerDataMaker(argc, argv);
	
	mkr.generate(gen, 10); // generate AplusB1.in/.ans, AplusB2.in/.ans, ..., AplusB10.in/.ans
	return 0;
}
```

## How to use it?

Of course you should throw `data_maker.h` to your compiler path and to include this file.

```cpp
#include "data_maker.h"
```

There is a class called `DataMaker` and a `DataMaker` called `mkr` . It's recommend to use this.

### Functions in `DataMaker` 

1. `DataMaker(std::string)` : same as `setProblemName(std::string)` .
2. `void setProblemName(std::string _problemName)` : set problem name to `_problemName` .
3. `void setStdName(std::string _stdName)` : set standard program's **execution** to `_stdName` .
4. `void setValidatorName(std::string _validatorName)` : set validator to `_validatorName` .
5. `void setReportFileName(std::string _reportFileName)` : set report file name to `_reportFileName` .
6. `void setTestCase(int _testCase)` : set test case to `_testCase` . This means that you will generate `<problemName><testCase>.in/.ans` then.
7. `template<typename T> void generate(T gen, int from, int to)` : use function `gen()` to generate `<problemName><from>.in/.ans`, `<problemName><from + 1>.in/.ans` , ..., `<problemName><to>.in/.ans` .
8. `template<typename T> void generate(T gen, int tests)` : same as `generate(gen, 1, tests)` .
9. `void openInputFile()` : open `<problemName><testCase>.in` .
10. `void closeInputFile()` : close `<problemName><testCase>.in` .
11. `void makeAnswerFile()` : make `<problemName><testCase>.ans` .
12. `void validate()` : validate `<problemName><testCase>.in` .
13. `void nextTestCase()` : same as `setTestCase(testCase + 1)` .

### Generate data with command line

First you need to call the function `registerDataMaker(argc, argv)` **at the beginning of `main()` function**.

Command line arguments should be like this: `[--problem <problemName>] [--std <stdName>] [--validator <validatorName>] [--reportFile <reportFileName>]` .

### Notices

You should output your input files' data to `mkr.fin` .

But you don't need to write something like `fprintf(mkr.fin, "%d", a);` because there is a macro:

```cpp
#define print(...) std::fprintf(mkr.fin, __VA_ARGS__)
```

Just use `print("%d", a);` instead.