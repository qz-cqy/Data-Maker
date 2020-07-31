#ifndef _DATA_MAKER_H_
#define _DATA_MAKER_H_ 1

#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>

#define print(...) std::fprintf(mkr.fin, __VA_ARGS__)

class DataMaker {
private:
	std::string problemName;
	std::string stdName;
	std::string validatorName;
	std::string reportFileName;
	int testCase;
	std::FILE* flog;

	inline void openFile(std::string, std::FILE*&);
	inline void closeFile(std::FILE*&);

public:
	DataMaker();
	DataMaker(std::string);
	~DataMaker();

	std::FILE* fin;

	inline void openInputFile();
	inline void closeInputFile();
	inline void makeAnswerFile();
	inline void validate();
	inline void nextTestCase();

	inline void setProblemName(std::string);
	inline void setStdName(std::string);
	inline void setValidatorName(std::string);
	inline void setReportFileName(std::string);
	inline void setTestCase(int);

	template<typename T>
	inline void generate(T, int);
	
	template<typename T>
	inline void generate(T, int, int);
};

DataMaker mkr;

inline void DataMaker::openFile(std::string fileName, std::FILE*& file) {
	file = std::fopen(fileName.c_str(), "w");
	if (file == NULL) {
		std::fprintf(flog, "Error: cannot open \"%s\".\n", fileName.c_str());
		exit(1);
	}
}

inline void DataMaker::closeFile(std::FILE*& file) {
	std::fclose(file);
	file = NULL;
}

DataMaker::DataMaker() {
	testCase = 1;
	fin = NULL;
	flog = stderr;
}

DataMaker::DataMaker(std::string _problemName) {
	testCase = 1;
	fin = NULL;
	flog = stderr;
	problemName = _problemName;
}

DataMaker::~DataMaker() {
	testCase = 1;
	fin = NULL;
	flog = NULL;
	problemName.clear();
	stdName.clear();
	validatorName.clear();
}

inline void DataMaker::openInputFile() {
	openFile((problemName + std::to_string(testCase) + ".in").c_str(), fin);
	std::fprintf(flog, "Generating \"%s%d.in/.ans\"...\n", problemName.c_str(), testCase);
}

inline void DataMaker::closeInputFile() {
	closeFile(fin);
}

inline void DataMaker::makeAnswerFile() {
	std::string cmd;
#ifdef __linux__
	cmd += "./";
#endif
	cmd += stdName + " ";
	cmd += "< " + problemName + std::to_string(testCase) + ".in";
	cmd += "> " + problemName + std::to_string(testCase) + ".ans";
	if (system(cmd.c_str())) {
		std::fprintf(flog, "Error: bugs appeared while running \"%s\". (\"%s\"'s exit code isn't 0)\n", 
				stdName.c_str(), stdName.c_str());
		exit(1);
	}
}

inline void DataMaker::validate() {
	std::string cmd;
#ifdef __linux__
	cmd += "./";
#endif
	cmd += validatorName + " ";
	cmd += "< " + problemName + std::to_string(testCase) + ".in";
	if (system(cmd.c_str())) {
		std::fprintf(flog, "Error: \"%s%d.in\" is invalid.\n", problemName.c_str(), testCase);
		exit(1);
	}
}

inline void DataMaker::nextTestCase() {
	testCase++;
}

inline void DataMaker::setProblemName(std::string _problemName) {
	problemName = _problemName;
}

inline void DataMaker::setStdName(std::string _stdName) {
	stdName = _stdName;
}

inline void DataMaker::setValidatorName(std::string _validatorName) {
	validatorName = _validatorName;
}

inline void DataMaker::setReportFileName(std::string _reportFileName) {
	openFile(_reportFileName.c_str(), flog);
	reportFileName = _reportFileName;
}

inline void DataMaker::setTestCase(int _testCase) {
	testCase = _testCase;
}

template<typename T>
inline void DataMaker::generate(T gen, int from, int to) {
	if (from > to) {
		std::fprintf(flog, "Error: DataMaker::generate(T gen, int from, int to): from cannot greater than to, from = %d, to = %d.\n", 
				from, to);
		exit(1);
	}
	for (testCase = from; testCase <= to; testCase++) {
		openInputFile();
		gen();
		closeInputFile();
		if (validatorName != "") validate();
		if (stdName != "") makeAnswerFile();
	}
}

template<typename T>
inline void DataMaker::generate(T gen, int tests) {
	generate(gen, 1, tests);
}

void registerDataMaker(int argc, char** argv) {
	for (int i = 1; i < argc; i++) {
		char* opt = argv[i];
		if (!std::strcmp(opt, (char*)("--problem")))
			mkr.setProblemName(argv[++i]);
		else if (!std::strcmp(opt, (char*)("--std")))
			mkr.setStdName(argv[++i]);
		else if (!std::strcmp(opt, (char*)("--validator")))
			mkr.setValidatorName(argv[++i]);
		else if (!std::strcmp(opt, (char*)("--reportFile")))
			mkr.setReportFileName(argv[++i]);
		else {
			std::fprintf(stderr, "Error: command line arguments must be look like this: [--problem <problemName>] [--std <stdName>] [--validator <validatorName>] [--reportFile <reportFileName>].\n");
			exit(1);
		}
	}
}

#endif // data_maker.h
