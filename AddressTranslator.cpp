#include "AddressTranslator.h"
#include <iostream>
#include "PageFault.h"


void AddressTranslator::setRootTableAddress(uint64_t addr)	{
	rootTableVirtualAddress = addr;
}

void AddressTranslator::insertAddressPair(std::pair<uint64_t, uint64_t> pair)	{
	pages_values.insert(pair);
}

uint64_t AddressTranslator::getPhysicalAddressOf(VirtualAddress addr) {
	TableRecord rec;
	try {
		rec.value = pages_values.at(rootTableVirtualAddress + addr.PML4 * 8);
		if (!rec.P) throw PageFault();
		rec.value = pages_values.at(rec.value -1 + addr.dir_ptr * 8);
		if (!rec.P) throw PageFault();
		rec.value = pages_values.at(rec.value -1 + addr.directory* 8);
		if (!rec.P) throw PageFault();
		rec.value = pages_values.at(rec.value -1 + addr.table* 8);
		if (!rec.P) throw PageFault();
		return rec.value -1 + addr.offset;
		//really can't understand why it shiuld be lowered by one, but working fine since i did this
	}
	catch(std::out_of_range &e) {
		std::cout << "getPhysicalAddressOf exception " << e.what() << std::endl;
		throw PageFault();
	}
}
