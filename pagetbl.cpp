#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include "pagetbl.h"

using namespace std;


	pagetbl::pagetbl(){
		for(int i = 0; i<256; i++)
			pageTable[i] = -1;	
	}
	
	pagetbl::pagetbl(physmem* mainMemPtr){
		mainPtr = mainMemPtr;
		for(int i = 0; i<256; i++)
			pageTable[i] = -1;	
	}
	
	pagetbl::~pagetbl(){
	}

	bool pagetbl::checkTable(int pageNum){
		bool status = false;
	
		if(pageTable[pageNum] != -1){
			printf("Page table hit\n");	 		
			status = true;
		}
		return status;			
	}
	
	int pagetbl::getFrameNumber(int pageNum){
		return pageTable[pageNum];		
	}


	bool pagetbl::fillTable(int pageNum){
		bool status = false;
		
		if(mainPtr->insertFrame(pageNum)){

			cout << "Successfully inserted into memory" << endl;

			pageTable[pageNum] = mainPtr->getCurrentIndex() - 256;

			cout << pageTable[pageNum] << endl;
			status = true;
			//returnValue = mem.getElement(pageTable[pageNum], offset);
		}	
		else
			printf("Unable to add element to memory\n");
		
		return status;	
	} 	

	int pagetbl::getTableEntry(int index){
		return pageTable[index];	
		
	}
