#pragma once
#include "VirtualAddress.h"
#include <iostream>
//returns "subbits" of bitset as integer
uint64_t sliceBitvise(const uint64_t bs, size_t lBound, size_t len) {
	return (bs << 64 - lBound) >> 64 - len;
}


VirtualAddress::VirtualAddress(const uint64_t& bitviseAddress)	{
	std::cout << "VirtualAddress::VirtualAddress : got " << bitviseAddress << std::endl;
	 // 0 : PML4 table index
	 // 1 : DIR_PTR table index 
	 // 2 : Directory table index
	 //	3 :	Table table index 
	 // 4 : Offset
	indicies.resize(5);

	indicies[0] = sliceBitvise(bitviseAddress, 47, 9);
	std::cout << "PML4 index = " << indicies[0]<< std::endl;

	indicies[1] = sliceBitvise(bitviseAddress, 38, 9);
	std::cout << "DIR_PTR index = " << indicies[1]<< std::endl;

	indicies[2] = sliceBitvise(bitviseAddress, 29, 9);
	std::cout << "directory index = " << indicies[2] << std::endl;

	indicies[3] = sliceBitvise(bitviseAddress, 20, 9);
	std::cout << "table index = " << indicies[3] << std::endl;

	indicies[4] = sliceBitvise(bitviseAddress, 11, 11);
	std::cout << "offset index = " << indicies[4] << std::endl;
}
