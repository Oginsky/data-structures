#include "BinHeap.h"
#define PRESENTATION
template <class T>
void BinHeap<T>::transposition(unsigned int i, unsigned int j) {
	swap(heap[i], heap[j]);
}
template <class T>
void BinHeap<T>::ascent(unsigned int i) {
	T temp = heap[i];
	unsigned int p = father(i);
	while(i && heap[p] > temp) {
		heap[i] = heap[p];
		i = p, p = father(p);
	}
	heap[i] = temp;
}
template <class T>
unsigned int BinHeap<T>::minchild(unsigned int f) {
	int l_son = leftSon(f);
	if (l_son >= size) return 0;
	else if (l_son == size-1) return l_son;
	else if (heap[l_son] < heap[l_son+1]) return l_son;
	else return l_son+1;
	
}
template <class T>
void BinHeap<T>::dive(unsigned int i) {
	unsigned int c = minchild(i);
	while(c && heap[c] < heap[i]) {
		swap(heap[i], heap[c]);
		i = c, c = minchild(c);
	}
}

template <class T>
BinHeap<T>::BinHeap() {
	size = 0;
}
template <class T>
BinHeap<T>::BinHeap(const unsigned int size) {
	heap.resize(size);
	this->size = size;
}
template <class T>
BinHeap<T>::BinHeap(BinHeap& copy) {
	heap = copy.heap;
	size = copy.size;
}
template <class T>
BinHeap<T>::~BinHeap() {
	heap.clear();
	size = 0;
}

template <class T>
void BinHeap<T>::add(T val) {
	heap.push_back(val);
	ascent(heap.size()-1);
	size++;
}
template <class T>
void BinHeap<T>::erase(unsigned int i) {
	heap[i] = heap[size-1];
	size--;
	if (i && heap[i] < heap[father(i)])
		ascent(i);
	else
		dive(i);
}
template <class T>
void BinHeap<T>::pop() {
	erase(0);
}
template <class T>
T BinHeap<T>::minkey() {
	return heap.front();
}
template <class T>
void BinHeap<T>::sort() {
	for (int i = size/2; i > 0; i--)
		dive(i);
	while (size > 1) {
		transposition(0,size-1);
#ifdef PRESENTATION
		cout << "swapped the first last elements of the heap: ";
		print();
#endif
		size--;
		dive(0);
#ifdef PRESENTATION
		cout << "dip new root: ";
		print();
		cout << "---------------------\n";
#endif
	}
}
template <class T>
void BinHeap<T>::build_heap() {
	size = heap.size();
	for (int i = size-1; i >= 0; i--)
		dive(i);
}
template <class T>
void BinHeap<T>::clear() {
	heap.clear();
	size = 0;
}

template <class T>
int BinHeap<T>::father(unsigned int node) {
	return (!node) ? 0 : (node - 1) / 2;
}
template <class T>
int BinHeap<T>::leftSon(unsigned int node) {
	return ((2*node + 1) < size) ? 2*node + 1 : -1;
}
template <class T>
int BinHeap<T>::rightSon(unsigned int node) {
	return ((2*node + 2) < size) ? 2*node + 2 : -1;
}

template <class T>
unsigned int BinHeap<T>::hight() {
	return (int)(log(size) / log(2) ) + 1;
}
template <class T>
unsigned int BinHeap<T>::levelSize(unsigned int index_level) {
	return pow(2, index_level-1);
}
template <class T>
unsigned int BinHeap<T>::levelStart(unsigned int index_level) {
	return pow(2, index_level-1)-1;
}
template <class T>
unsigned int BinHeap<T>::levelEnd(unsigned int index_level) {
	return pow(2, index_level) - 2;
}

template <class T> 
unsigned int BinHeap<T>::getSize() { return size; }
template <class T>
T& BinHeap<T>::operator[](unsigned int index) {
	return heap[index];
}

template <class T>
void BinHeap<T>::print() {
	for (int i = 0; i < size; i++)
		cout << heap[i] << " ";
	cout << endl;
}
template <class T>
void BinHeap<T>::printall() {
	for (int i = 0; i < heap.size(); i++)
		cout << heap[i] << " ";
	cout << endl;
}
template <class T>
void BinHeap<T>::printheap() { 
	int i = 0; 
	int k = 1;
	while (i < size) { 
		while ((i < k) && (i < size)) { 
			cout << heap[i] << " "; 
			i++; 
		} 
		cout << endl; 
	k = k * 2 + 1; 
	} 
} 

