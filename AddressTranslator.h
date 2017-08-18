#pragma once
#include <vector>
#include <map>
#include <bitset>
#include "TableRecord.h"
#include "VirtualAddress.h"


class AddressTranslator	{
public:
	void setRootTableAddress(uint64_t addr); 
	void insertAddressPair(std::pair<uint64_t, uint64_t> pair);
	uint64_t getPhysicalAddressOf(VirtualAddress addr);
private:
	uint64_t rootTableVirtualAddress = 0;
	std::map<uint64_t, uint64_t> pages_values; //physical map address and value
};

