#pragma once
#include <stdint.h>

//msvsc depended
#pragma pack(push, 1)
union TableRecord {
	std::uint64_t value;
	struct {
		std::uint64_t P : 1; //bit of usage, if zero - PAGE_FAULT!!
	};
};
#pragma pack(pop)