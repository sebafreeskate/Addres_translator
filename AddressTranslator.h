#pragma once
#include <vector>
#include <map>
#include <bitset>
#include "TableRecord.h"
#include "VirtualAddress.h"



class AddressTranslator	{
public:
	AddressTranslator();
	~AddressTranslator();
	void setRootTableAddress(uint64_t addr); 
	void insertAddressPair(std::pair<uint64_t, uint64_t> pair);
	TableRecord getRecord(uint64_t table, size_t pos);
	uint64_t getPhysicalAddressOf(VirtualAddress addr);
	void print();
private:
	uint64_t rootTableVirtualAddress;
	std::map<uint64_t, uint64_t> pages_values; //physical map address and value
};

