#include <iostream>
#include <fstream>
#include <string>
#include <vector>
//#include <boost>

std::pair<int, int> getVals(std::string vals) {

}

int main(int argc, char * argv[]) {
	/* input file example:
	    3 6000 395952128
		73793280 125698049
		21855848 12374017
		42174784 294813697 */
	if (argc != 2) {
		std::cerr << "invalid params" << std::endl;
		return -2;
	}

	std::ifstream in(argv[1]);
	if (!in.is_open()) {
		std::cerr << "cant open file " << argv[1] << std::endl;
		return -1;

	}
	std::string line;
	std::getline(in, line);
	std::vector<std::string> firstLine(std::move(split(line, ' ')));
	if (firstLine.size() != 3) {
		std::cerr << "invalid file stucture" << std::endl;
		return 1;
	}

	uint64_t queryCount = std::stoull(firstLine[1]); // total queries to response
	uint64_t rootTableAddress = std::stoull(firstLine[2]); // root table's address
	uint64_t count = std::stoull(firstLine[0]); // data rows count
	std::cout << "query count = " << queryCount << std::endl;
	std::cout << "rootTableAddress = " << rootTableAddress << std::endl;
	std::cout << "count = " << count << std::endl;
	/* for(int i=0; i< count; ++i) {
	  std::getline(in, line);
	  splitToPair(line, delim);
	  } */
	return 0;

}




