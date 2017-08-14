#pragma once
#include <vector>


struct VirtualAddress {
	VirtualAddress(const uint64_t& bitviseAddress);
	std::vector<size_t> indicies;
};
