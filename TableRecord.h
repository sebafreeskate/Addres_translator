#pragma once
#include <stdint.h>
//Simplyfied descriptor of the page table's record (for any of four) 

struct TableRecord {
	TableRecord(const uint64_t& bitviseRecord);
	TableRecord();
	bool P; //is it final record? page fault then  
	uint64_t nextAddr; //address of the next level table or page
};
