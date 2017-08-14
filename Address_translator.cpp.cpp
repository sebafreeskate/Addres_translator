#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <vector>

std::vector<uint64_t> parseLine(const char* line, char delimeter) {
	std::vector<uint64_t> tokens;
	char *end;
	for (uint64_t i = std::strtoull(line, &end, 10);
		;
		i = std::strtoull(end, &end, 10)) {
		tokens.push_back(i);
		if (*end == '\0') {
			break;
		}
	}
	return tokens;
}

	/*Sample Input :	      Sample Otput :
		4 4 0					16384
		0 4097					fault
		4096 8193				16426
		8192 12289				fault
		12288 16385
		0
		4096
		42
		131313 */

int main(int argc, char * argv[]) {
/*	if (argc != 2) {
		std::cerr << "invalid params" << std::endl;
		return -2;
	} */
	std::ifstream in("C:/Users/sebafreeskate/Source/Repos/Address_translator/test.txt");
	if (!in.is_open()) {
		std::cerr << "cant open file " << std::endl;
		return -1;
	}

	std::string line;
	std::getline(in, line);
	std::vector<uint64_t> firstLine(parseLine(line.c_str(), ' '));
	if (firstLine.size() != 3) {
		std::cerr << "invalid file stucture" << std::endl;
		return 1;
	}

	uint64_t queryCount = firstLine[1]; // total queries to response
	uint64_t rootTableAddress = firstLine[2]; // root table's address
	uint64_t count = firstLine[0]; // data rows count
	std::cout << "query count = " << queryCount << std::endl;
	std::cout << "rootTableAddress = " << rootTableAddress << std::endl;
	std::cout << "count = " << count << std::endl;

	std::map<int, int> pagesMap;

	for(int i=0; i< count; ++i) {
	  std::getline(in, line);
	  if (!line.empty()) {
		  std::vector<uint64_t> pageLine(parseLine(line.c_str(), ' '));
		  pagesMap.insert(std::make_pair(pageLine[0], pageLine[1]));
	  }
	} 
	std::cout << "pagesMap.size() = " << pagesMap.size() << std::endl;
	std::cin >> line;
	return 0;
}




