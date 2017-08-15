#include "AddressTranslator.h"
#include <iostream>
#include "PageFault.h"


AddressTranslator::AddressTranslator()	{
}


AddressTranslator::~AddressTranslator()	{
}

void AddressTranslator::setRootTableAddress(uint64_t addr)	{
	rootTableVirtualAddress = addr;
}

void AddressTranslator::insertAddressPair(std::pair<uint64_t, uint64_t> pair)	{
	pages_values.insert(pair);
}

TableRecord AddressTranslator::getRecord(uint64_t table, size_t pos) {
	std::cout << "AddressTranslator::getRecord : table = " << table << ", pos = " << pos <<", offset = " << pos * sizeof(uint64_t) << std::endl;
	uint64_t recordAddr = table + (pos * sizeof(uint64_t));
	std::cout << "AddressTranslator::getRecord : record addr = " << recordAddr << std::endl;
	try {
		return pages_values.at(recordAddr);
	}
	catch (std::out_of_range &e) {
		std::cout << "getRecord ecxeption " << e.what() << std::endl;
		throw PageFault();
	}
}

uint64_t AddressTranslator::getPhysicalAddressOf(VirtualAddress addr) {
	TableRecord rec = getRecord(rootTableVirtualAddress, addr.indicies[0]);
	for (int i = 1; i < addr.indicies.size() -1 && rec.P; ++i) {
		rec = getRecord(rec.nextAddr, addr.indicies[i]);
	}

	if (rec.nextAddr != 0) {
		rec.nextAddr += addr.indicies[4]; //offset
	}
	return rec.nextAddr;
}

void AddressTranslator::print()	{
	std::cout<< "rootTableVirtualAddress = " << rootTableVirtualAddress << std::endl;
	std::cout << "first 10 pages and vals:" << std::endl;
	int n = 10;
	for (auto &pair : pages_values) {
		std::cout << pair.first << " : " << pair.second << std::endl;
		if (!--n)
			break;
	}
}