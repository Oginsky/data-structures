#pragma once

#include <iostream>
#include <cmath> 

using std::min;
using std::max;
using std::cout;
using std::endl;

class SegmentTree {
	private:	
		int F(const int& a, const int& b) {
			return min(a, b);
		}
		int fill = INT_MAX;
		
		int root = 0; // size (last node / min key(data))
		int base = 0; // nearest degree of 2 (2^base)
		int items; // real node
		int* tree = NULL;
		
		
		
	public:
		SegmentTree();
		SegmentTree(unsigned int N);
		~SegmentTree();
		
	
		int& operator[](unsigned int index);
		void build();
		
	
		int minonseg(int l, int r);
		int dive(int l, int r, int node_index, int nl, int nr);
	//	int up(int l, int r); 
		void insert(int index, int value);
		void clear();
		
	
		int parent(int index);
		int leftchild(int index);
		int rightchild(int index);
		
	
		void printdata();
		int ROOT();
		int BASE();
		int ITEMS();
};
