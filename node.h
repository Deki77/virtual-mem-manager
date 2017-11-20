#pragma once

class node{
	private:
		int index;
		node* next;
		node* previous;
		int page;	
		
	public:


		node();
		~node();
		node(int pageNum, int indexNum);
		node(int pageNum, int indexNum, node *nex, node* prev);
		int getIndex();
		node* getNext();
		node* getPrev();
		int getPage();
		
		void setIndex(int indexSet);
		void setPage(int pageSet);
		void setNext(node *nex);
		void setPrev(node *prev);

};
