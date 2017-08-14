#include "TableRecord.h"
#include <bitset>
#include <iostream>

TableRecord::TableRecord(const uint64_t& bitviseRecord)	{
	uint64_t mask = 1;
	P = bitviseRecord & mask;
	nextAddr = ((bitviseRecord << 12) >> 12); // косяк возможно тут
	std::cout << "TableRecord::TableRecord : next Addr = " << nextAddr << std::endl;
	std::cout << "TableRecord::TableRecord : P " << P << std::endl;
}

TableRecord::TableRecord()	{
	P = false;
	nextAddr = 0;
}
