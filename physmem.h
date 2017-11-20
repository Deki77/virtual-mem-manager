#pragma once
#include <string>
using namespace std;

#define PHYS_MEM_SIZE 65536
#define FRAME_SIZE 256

class physmem {
	private:
		char mainMem[PHYS_MEM_SIZE];
		int currentIndex;
	public:
		physmem();
		~physmem();
		int getCurrentIndex();
		
		bool insertFrame(int pageNum);

		char* getPhysArray();
		
		char getElement(int frameNum, int offset);
};
