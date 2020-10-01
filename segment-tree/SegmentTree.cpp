#include "SegmentTree.h"


SegmentTree::SegmentTree() {
	
}
SegmentTree::SegmentTree(unsigned int N) {
	base = pow(2, ceil(log(N)/log(2)));
	root = (base * 2) - 2;
	items = N;
	tree = new int[root+1];
	for(int i = 0; i < base; i++) tree[i] = fill;
}
SegmentTree::~SegmentTree() {
	base = root = items = 0;
	delete[] tree;
	tree = NULL;
}

int& SegmentTree::operator[](unsigned int index) {
	return tree[index];
}
void SegmentTree::build() {
	int i = base, temp = 0;
	for(i; i <= root; i++)
		tree[i] = F(tree[temp++], tree[temp++]);
}

int SegmentTree::minonseg(int l, int r) {
	//if (r - l >= base/4) 
	return dive(l-1, r-1, root, 0, base-1);
	//else return up(l-1, r-1);
}
int SegmentTree::dive(int l, int r, int node_index, int nl, int nr) {
	if(nl == l && nr == r) {
		return tree[node_index];
	}
		
	int left_min = tree[l], right_min = tree[r];
	int left_child = leftchild(node_index);
	int right_child = left_child + 1;
	
	int left_child_right_border = nl + ((nr-nl)/2);
	int right_child_left_border = (nl + (nr-nl)/2 + 1);
	
	
	if (l <= left_child_right_border) {
		left_min = dive(l, min(r, left_child_right_border), left_child, nl, left_child_right_border);
	}
	if (r >= right_child_left_border) {
		right_min = dive(max(right_child_left_border, l), r, right_child, right_child_left_border, nr);
	}
	return F(left_min, right_min);
}

//int SegmentTree::up(int l, int r) {
//	int lp = l, rp = r; // left_parent and right_parent
//	int lmin = tree[l].data, rmin = tree[r].data; // left and right min data
//	
//	while(r - l > 1) {
//		while(tree[parent(lp)].left_border == l && tree[parent(lp)].right_border < r) lp = parent(lp);
//		while(tree[parent(rp)].right_border == r && tree[parent(rp)].left_border > l) rp = parent(rp);
//		
//		if(tree[lp].data < lmin) lmin = tree[lp].data;
//		if(tree[rp].data < rmin) rmin = tree[rp].data;
//		
//		
//		l = tree[lp].right_border + 1;
//		r = tree[rp].left_border - 1;
//		
//		lp = l, rp = r;
//	}
//	
//	return min(lmin, rmin);
//}
void SegmentTree::insert(int index, int value) {
	tree[index] = value;
	int pi = parent(index), lc;
	while(pi <= root) {
		lc = leftchild(pi);
		tree[pi] = min(tree[lc], tree[lc+1]);
		pi = parent(pi);
	}
}
void SegmentTree::clear() {
	items = root = base = 0;
	delete[] tree;
	tree = NULL;
}

int SegmentTree::parent(int index) {
	return (index/2 + base);
}
int SegmentTree::leftchild(int index) {
	return (index - base)*2;	
}
int SegmentTree::rightchild(int index) {
	return (((index - base)*2) - 1);
}


void SegmentTree::printdata() {
	int base1 = base;
	int k = 0;
	while(base1) {
		for(int i = 0; i < base1; i++) {
			cout << tree[i+k] << " ";
		}
		k += base1;
		base1 /= 2;
		cout << endl;
	}
	cout << endl;
}
int SegmentTree::ROOT() {
	return root;
}
int SegmentTree::BASE() {
	return base;
}
int SegmentTree::ITEMS() {
	return items;
}
