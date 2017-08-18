#pragma once
#include <vector>

//Virtual address contains indexes of records in four tables which used in x86 address tranlation routine 
// its msvsc dependent implementation, could work with gcc 
#pragma pack(push, 1)
union VirtualAddress {
	std::uint64_t value;
	struct {
		std::uint64_t offset : 12;
		std::uint64_t table : 9;
		std::uint64_t directory : 9;
		std::uint64_t dir_ptr : 9;
		std::uint64_t PML4 : 9;
	};
};
#pragma pack(pop)
