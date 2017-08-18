#include <iostream>
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

void check_params(int argc) {
	if (argc != 2) {
	std::cerr << "invalid params" << std::endl;
	exit(-2);
	} 
}

std::ifstream open_input_file(const char * name) {
	std::ifstream in(name);
	if (!in.is_open()) {
		std::cerr << "cant open file " << std::endl;
		exit(-1);
	}
	return in;
}

std::ofstream open_output_file(const char * name) {
	std::ofstream out(name);
	if (!out.is_open()) {
		std::cerr << "can't open output file! " << std::endl;
		exit(-1);
	}
	return out;
}
std::vector<uint64_t> get_first_line(std::ifstream &in) {
	std::string line;
	std::getline(in, line);
	std::vector<uint64_t> firstLine = parseLine(line.c_str(), ' ');

	if (firstLine.size() != 3) {
		std::cerr << "invalid file stucture" << std::endl;
		exit(-1);
	}
	return firstLine;
}

AddressTranslator buildTranslator(std::ifstream &in, uint64_t addressCount, uint64_t rootTableAddress) {
	AddressTranslator translator;
	translator.setRootTableAddress(rootTableAddress);
	for_next_n_lines_in_file(in, addressCount,
		[&translator](const std::vector<uint64_t> & tl) {
		if (tl.size() == 2) {
			translator.insertAddressPair(std::make_pair(tl[0], tl[1]));
		}
	});
	return translator;
}

int main(int argc, char * argv[]) {

	check_params(argc);

	std::ifstream in = open_input_file(argv[1]);
	std::ofstream out = open_output_file("./out.txt");

	std::vector<uint64_t> firstLine = get_first_line(in);

	AddressTranslator translator = buildTranslator(in, firstLine[0], firstLine[2]); 

	uint64_t queryCount = firstLine[1];

	for_next_n_lines_in_file(in, queryCount, 
		[&translator, &out](const std::vector<uint64_t> & tl) {
		if (!tl.empty()) {
			uint64_t physicalAddress;
			try {
				VirtualAddress vaddr;
				vaddr.value = tl[0];
				physicalAddress = translator.getPhysicalAddressOf(vaddr);
				out << physicalAddress << std::endl;
			}
			catch (PageFault &e) {
				out << "fault" << std::endl;
			}
		}
	});

	in.close();
	out.close();

	return 0;
}





