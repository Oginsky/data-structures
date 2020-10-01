#pragma once
#include <vector>
#include <cmath>
#include <iostream>
using std::vector;
using std::cout;
using std::endl;
using std::swap;

template <class T>
class BinHeap {
	private:
		vector<T> heap;
		unsigned int size;
		
		void transposition(unsigned int i, unsigned int j);
		//void ascent(unsigned int i);
		unsigned int minchild(unsigned int);
		//void dive(unsigned int i);
		
	public:
		void dive(unsigned int i);
		void ascent(unsigned int i);
		BinHeap();
		BinHeap(const unsigned int size);
		BinHeap(BinHeap& copy);
		~BinHeap();
		
		void add(T val);
		void erase(unsigned int i);
		void pop();
		T minkey();
		void sort();
		void build_heap();
		void clear();
		
		int father(unsigned int node);
		int leftSon(unsigned int node);
		int rightSon(unsigned int node);
		
		unsigned int hight();
		unsigned int levelSize(unsigned int index_level);
		unsigned int levelStart(unsigned int index_level);
		unsigned int levelEnd(unsigned int index_level);
		
		unsigned int getSize();
		T& operator[](unsigned int index);
		
		void print();
		void printall();
		void printheap();
};
