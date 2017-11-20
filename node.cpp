#include <iostream>
#include "node.h"

node::node(){
	index = 0;
	next = NULL;
}

node::~node(){
	
}

node::node(int pageNum, int indexNum){
	index = indexNum;
	page = pageNum;
	next = NULL;
	previous = NULL;
}

node::node(int pageNum, int indexNum, node *nex, node* prev){
	index = indexNum;
	page = pageNum;
	next = nex;
	previous = prev;
}

int node::getIndex(){
	return index;
}

int node::getPage(){
	return page;
}

node* node::getNext(){
	return next;
}

node* node::getPrev(){
	return previous;
}

void node::setIndex(int indexSet){
	index = indexSet;
}

void node::setPage(int pageSet){
	page = pageSet;
}

void node::setNext(node* nex){
	next = nex;
}

void node::setPrev(node* prev){
	previous = prev;
}
