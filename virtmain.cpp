#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include "physmem.h"
#include "pagetbl.h"
#include "tlb.h"
using namespace std;



int main(int argc, char *argv[]){
	
	physmem *myMainMem = new physmem();
	pagetbl *myPageTable= new pagetbl(myMainMem);
	tlb* myTlb =  new tlb(myMainMem, myPageTable);
	/*char buffer[256];
	FILE *filep = NULL;
	if((filep = fopen("BACKING_STORE.bin", "rb")) == NULL)
		cout << "Unable to open file " << endl;
	else
		cout <<"File successfully opened " << endl;*/
	//cout << "Size of integer: " << sizeof(int) << endl;
	int address;
	ifstream myFile("addresses.txt");
	if(myFile.is_open()){
		while(myFile >> address){
		//while(1){
			//int address = 0;
			int frame = 0;
			//printf("Please input address\n");
			//scanf("%d", &address);

			int page = address >> 8;
			int offset = address & 0xff;
				
			//printf("The address is %d\n", address);
			//printf("This corresponds to page %d\n", page);
			//printf("The offset into the page is %d\n", offset);
			frame = myTlb->searchTlb(page);
			
			char value = myMainMem->getElement(frame, offset);

			if(address == 0){
				for(int i=0; i<256;i++)
					printf("Page Table Entry: %d corresponds to Physical Address: %d\n",i, myPageTable->getTableEntry(i));		
			}
			int john = frame + offset;


			//if(value == -1){
				//value = myPageTable.fillTable(myMainMem, page, offset);
				//printf("Element at address %d is value=%d\n", address, value);
			//}
			//else{
			
				printf("Element at address: %d with physical address: %d is value= %d\n", address, john, value);
				
			//}
		}
	}	
		delete myMainMem;
		delete myPageTable;
		myTlb->deleteLinkedList();
		//cout << "After delete head ptr: " << myTlb->getHead() << " and back is: " << myTlb->getBack() << endl;
		delete myTlb;
		//fclose(filep);
}
