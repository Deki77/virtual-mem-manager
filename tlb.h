#pragma once

#include "physmem.h"
#include "pagetbl.h"
#include "node.h"

typedef struct tblEntry{
	int pageNumber;
	int frameNumber;
}tblEntry;

class tlb{
	private:
		tblEntry tlbBuffer[16];
		node* headptr;
		node* backptr;
		int tlbIndex;
		int index2;
		physmem* mainPtr;
		pagetbl* pagePtr;

	public:
		tlb();
		tlb(physmem* mainPtr, pagetbl* pagePtr);
		~tlb();
		node* getHead();
		node* getBack();

		void deleteLinkedList();
		int searchTlb(int pageNum);
		bool insertTlb(int pageNum, int frameNum);

		int linkedListSearch(int pageNum);
		int linkedListReplaceAdd(int pageNum);
		bool linkedListAdd(int pageNum, int index); 
};
