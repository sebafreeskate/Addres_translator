#include <iostream>
#include <bitset>
#include <functional>
#include <map>
#include <fstream>
#include <string>
#include <vector>
#include "AddressTranslator.h"
#include "PageFault.h"

std::vector<uint64_t> parseLine(const char* line, char delimeter) {
	std::vector<uint64_t> tokens;
	char *end;
	for (uint64_t i = std::strtoull(line, &end, 10);
		;
		i = std::strtoull(end, &end, 10)) {
		tokens.push_back(uint64_t(i));
		if (*end == '\0') {
			break;
		}
	}
	return tokens;
}

template <typename Func>
void for_next_n_lines_in_file(std::ifstream & in, int n, Func action) {
	std::string line;
	for (int i = 0; i < n; ++i) {
		std::getline(in, line);
		if (!line.empty()) {
			std::vector<uint64_t> tokenizedLine(parseLine(line.c_str(), ' '));
			action(tokenizedLine);
		}
	}
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
	std::vector<uint64_t> firstLine = parseLine(line.c_str(), ' ');

	if (firstLine.size() != 3) {
		std::cerr << "invalid file stucture" << std::endl;
		return 1;
	}

	AddressTranslator translator;

	uint64_t addressCount = firstLine[0]; 
	uint64_t queryCount = firstLine[1];
	uint64_t rootTableAddress = firstLine[2];

	std::cout << "addressCount = " << addressCount<< std::endl;
	std::cout << "query count = " << queryCount << std::endl;
	std::cout << "rootTableAddress = " << rootTableAddress << std::endl;

	
	for_next_n_lines_in_file(in, addressCount, 
		[&translator](const std::vector<uint64_t> & tl) {
		if (tl.size() == 2) {
			translator.insertAddressPair(std::make_pair(tl[0], tl[1]));
		}
	});

	translator.setRootTableAddress(rootTableAddress);

	translator.print();

	std::ofstream out("C:/Users/sebafreeskate/Source/Repos/Address_translator/out.txt");

	if (!out.is_open()) {
		std::cerr << "can't open output file! " << std::endl;
		return -1;
	}

	for_next_n_lines_in_file(in, queryCount, 
		[&translator, &out](const std::vector<uint64_t> & tl) {
		if (!tl.empty()) {
			uint64_t physicalAddress;
			try {
				physicalAddress = translator.getPhysicalAddressOf(tl[0]);
				std::cout << physicalAddress << std::endl;
				out << physicalAddress << std::endl;
			}
			catch (PageFault &e) {
				std::cout << "fault" << std::endl;
				out << "fault" << std::endl;
			}
			std::cout << std::endl << "---------------------" << std::endl;
		}
	});
	in.close();
	out.close();
	std::cin >> line;
	return 0;
}





