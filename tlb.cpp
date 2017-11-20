#include <iostream>
#include <string>
#include <cctype>
#include <stdio.h>
#include <stdlib.h>

#include "tlb.h"

using namespace std;

tlb::tlb(){
	headptr = NULL;
	backptr = NULL;
	mainPtr = NULL;
	pagePtr = NULL;

	for(int i = 0; i<16; i++){
			tlbBuffer[i].pageNumber = -1;
			tlbBuffer[i].frameNumber = -1;
	}
}

tlb::tlb(physmem* mainMemPtr, pagetbl* pageTablePtr){
	headptr = NULL;
	backptr = NULL;
	mainPtr = mainMemPtr;
	pagePtr = pageTablePtr;
	tlbIndex = 0;
	index2 = 0;
	for(int i = 0; i<16; i++){
			tlbBuffer[i].pageNumber = -1;
			tlbBuffer[i].frameNumber = -1;
	}
}

tlb::~tlb(){

}

node* tlb::getHead(){
	return headptr;
}

node* tlb::getBack(){
	return backptr;
}

void tlb::deleteLinkedList(){
	node* temp = NULL;
	while(headptr!=NULL){
		temp = headptr->getNext();
		delete headptr;
		headptr = temp;
	}

	headptr = backptr = NULL;
}

int tlb::searchTlb(int pageNum){
	int frameNum = -1;
	//cout << "value of headptr while in searchTlb "  << headptr << endl;
	for(int i =0; i<16; i++){
		if(tlbBuffer[i].pageNumber == pageNum){
			frameNum = tlbBuffer[i].frameNumber;
			if(i == linkedListSearch(pageNum)){
				break;
			}		
		}				
	}
	
	if(frameNum != -1)
		printf("Search has resulted in a TLB hit\n");
	else{
		//TLB miss but value is within page table		
		if(pagePtr->checkTable(pageNum)){
			frameNum = pagePtr->getTableEntry(pageNum);
		}
		else{	//page fault
			if(pagePtr->fillTable(pageNum))
				frameNum = pagePtr->getTableEntry(pageNum);
			else
				printf("Memory not properly filled with frame\n");	
		}
		//cout << "Before call to insert TLB head ptr valaue " << headptr << endl;
		insertTlb(pageNum, frameNum);

	}
	return frameNum;
}


bool tlb::insertTlb(int pageNum, int frameNum){
	bool status = false;
	if(tlbIndex < 16){
		tlbBuffer[tlbIndex].pageNumber = pageNum;
		tlbBuffer[tlbIndex].frameNumber = frameNum;
		//call to add new node into linked list
		linkedListAdd(pageNum, tlbIndex);
		tlbIndex++;
		status = true;
	}
	else{
		int index2 = linkedListReplaceAdd(pageNum);
		tlbBuffer[index2].pageNumber = pageNum;
		tlbBuffer[index2].frameNumber = frameNum;
		status = true;
	}
		
	return status;
}


bool tlb::linkedListAdd(int pageNum, int index){
	//create new node with page number and index
 	node* ptr = new node(pageNum, index);
	//set node next pointer to first link in chain
	ptr->setNext(headptr);
	//set node previous pointer to NULL
	ptr->setPrev(NULL);
	//if head pointer exists then set head pointer previous to ptr, so the bitch is linked in
	if(headptr != NULL){
		headptr->setPrev(ptr);
	}
	//if no elements in chain set back pointer to ndoe
	if(backptr == NULL)
		backptr = ptr;
	headptr = ptr;
}

int tlb::linkedListReplaceAdd(int pageNum){
	//set temp node pointer to node element before last element
	node* tempLast = backptr->getPrev();
	//get index of last node in chain this will be returned for which element in array to be replaced
	int indexReturn = backptr->getIndex();
	//delete last element in chain
	delete backptr;
	//set next of last element in chain to NULL
	tempLast->setNext(NULL);	

	backptr = tempLast;
	linkedListAdd(pageNum, indexReturn);
	
	return indexReturn;
}

int tlb::linkedListSearch(int pageNum){
	node* current = NULL;
	node* prevptr = NULL;
	node* nextptr = NULL;
	for(current = headptr; current!=NULL; prevptr = current, current = current->getNext()){		
		if(current->getPage() == pageNum){
			//last element in a non-empty array
			if(current == backptr && current != headptr){
				//cout << "Moving backptr to head ptr as most recently used " << endl;
				prevptr = current->getPrev();
				prevptr->setNext(NULL);
				backptr = prevptr;
				current->setNext(headptr);
				headptr->setPrev(current);
				headptr = current;			
			}
			//neither first nor last element in non emptry array
			else if(current != headptr){
				nextptr = current->getNext();
				prevptr = current->getPrev();
				nextptr->setPrev(prevptr);
				prevptr->setNext(nextptr);
				current->setNext(headptr);
				headptr->setPrev(current);
				headptr = current;

			}
			//first element in non empty array
			else
				cout << "headptr is most recently used so do nothing " << endl;
			cout << "Index= "<< current->getIndex() << endl;
			return current->getIndex();		
		}		
	}
	return -1;
}
