#pragma once
#include <string>
#include "physmem.h"
using namespace std;

#define PAGE_TABLE_SIZE 256

class pagetbl {
	private:
		int pageTable[PAGE_TABLE_SIZE];
		physmem* mainPtr;
		
	public:
		pagetbl();
		pagetbl(physmem* memPtr);
		~pagetbl();
		
		int getTableEntry(int index);

		int getFrameNumber(int pageNum);
		
		bool checkTable(int pageNum);
		bool fillTable(int pageNum);
	
	

};
