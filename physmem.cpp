#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include "physmem.h"

using namespace std;

	physmem::physmem(){
		int i = 0;
		for(;i<PHYS_MEM_SIZE;i++)
			mainMem[i] = -1;
		currentIndex = 0;
	}
	
	physmem::~physmem(){
	
	}

	bool physmem::insertFrame(int pageNum){
		bool status = true;		
		int index = pageNum * 256;
		char buffer[256];
		FILE *filep = NULL;
		if((filep = fopen("BACKING_STORE.bin", "rb")) == NULL){
			cout << "Unable to open file " << endl;
			status = false;	
		}
		else
			cout <<"File successfully opened " << endl;

		fseek(filep, index, SEEK_SET);
		fread(buffer, 256, 1, filep);
	
		memcpy(mainMem + currentIndex, buffer, 256);
		fclose(filep);
		currentIndex+=256;
		return status;			
	}

	char* physmem::getPhysArray(){
		return mainMem;	
	}

	char physmem::getElement(int frameNum, int offset){
		int index = frameNum+offset;
		return mainMem[index];	
	}

	int physmem::getCurrentIndex(){
		return currentIndex;	
	}
