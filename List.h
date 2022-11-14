#pragma once
#include "LinkList.h"
#include "Graph.h"

/*List is a template class containing overlaping 
*functionalities with the vector class. It's main 
*function is to create instances of dynamically 
*allocated arrays, but it also contains many 
*searching and sorting algorithms.
*/

template <class type>
class List {

	/*Instance for size of the list, it sorted state,
	* and pointer to the dynamic array for the list.
	*/
	int n = 0;
	bool sorted = false;
	type* list = nullptr;

public:

	/*Default constructor that creats an empty list where n = 0.
	*/
	List() : n(0), list(nullptr) {}

	/*An overloaded  construcutre that instantiates a list of
	* size n and initializes ever index with a single element.
	*/
	List(int n, type data) : n(n) {
		list = new type[n];
		for (int i = 0; i < n; i++)
			list[i] = data;
	}

	/*An overloaded constructor that takes a pointer to an
	* existing list of a predetermined size.
	*/
	List(int n, type *data) : n(n), list(data) {
	}

	/*An overloaded constructor that instantiates a list of a
	* predetermined size.
	*/
	List(int n) : n(n) {
		list = new type[n];
		for (int i = 0; i < n; i++)
			list[i] = nullptr;
	}

	//A function used to add elments to the list.
	void push(type data) {
		if (!n) {
			list = new type[++n];
			list[0] = data;
		}
		else {
			int preSize = n;
			type *newList = new type[++n];
			for (int i = 0; i < preSize; i++)
				newList[i] = list[i];
			newList[preSize] = data;
			list = newList;
		}
	}

	/*An overloaded operator used to assign an element 
	* to a specific index within the list or to retrieve
	* the reference of a value from that given index.
	*/
	type& operator[](int i) {
		if (n <= i)
			return list[n - 1];
		else if (i <= 0)
			return list[0];
		else
			return list[i];
	}

	/*A function that returns a reference to a given index
	* within the list.
	*/
	type& at(int i) {
		if (n <= i)
			return list[n - 1];
		else if (i <= 0)
			return list[0];
		else
			return list[i];
	}

	//A linear search algorithm used for unordered lists.
	int seqSearch(type data) {
		for (int i = 0; i < n; i++) {
			if (list[i] == data)
				return i;
		}
		return -1;
	}

	//A binary search algorithm used for ordered lists.
	int binSearch(type data) {
		if (true) {
			int a = 0, c = n - 1, b = 0;
			do {
				b = (a + c) / 2;
				if (data == list[b])
					return b;
				else if (data > list[b])
					a = b + 1;
				else
					c = b - 1;
			} while (b && data != list[b]);

			return -1;
		}
		else
			return -1;
	}

	/*A modulo hash function used to generate indices
	* for a hash table.
	*/
	template <typename value>
	int modH(value key) {
		return key % n;
	}

	/*A chaining function used to resolve collisions and 
	* overflow within a hash table.
	*/
	template <typename value>
	void link(value data) {
		if (list[modH<value>(data)]) {
			list[modH<value>(data)]->push(data);
		}
		else {
			list[modH<value>(data)] = new LinkList<value>();
			list[modH<value>(data)]->push(data);
		}
	}

	//Swaps two items within a list
	void swap(int a, int b) {
		type tmp = list[a];
		list[a] = list[b];
		list[b] = tmp;
	}

	//Returns the maximum within a given range
	int max(int beg = 0, int end = n) const {
		int max = INT_MIN, ind = beg;
		for (int i = beg; i < end; i++) {
			if (max < list[i]) {
				max = list[i];
				ind = i;
			}
		}
		return ind;
	}

	//Returns the minimum within a given range
	int min(int beg = 0, int end = n) const {
		int min = INT_MAX, ind = beg;
		for (int i = beg; i < end; i++) {
			if (list[i] < min) {
				min = list[i];
				ind = i;
			}
		}
		return ind;
	}
	
	//Selection sort
	void selectionSort(bool findMin = true) {
		for (int i = 0; i < n; i++) {
			if (findMin) 
				swap(i, min(i, n));
			else
				swap(i, max(i, n));
		}
	}

	//Insertion sort
	void insertionSort() {
		int wrd = 1, trc = 0;
		type tmp;

		while (wrd < n) {
			if (list[trc] > list[wrd]) {
				tmp = list[wrd];
				while (trc >= 0 && tmp < list[trc])
					list[trc + 1] = list[trc--];
				list[trc + 1] = tmp;
			}
			trc =  ++wrd - 1;
		}
	}

	//Shell sort
	void shellSort() {
		int inc = n/2, wrd = inc, trc = 0;;
		type tmp;
		do {
			while (wrd < n) {
				if (list[trc] > list[wrd]) {
					tmp = list[wrd];
					list[wrd] = list[trc];
					list[trc] = tmp;
				}
				trc = ++wrd - inc;
			}
			inc = inc / 2;
			wrd = inc;
			trc = 0;
		} while (inc > 0);
		insertionSort();
	}

	//Partition
	int partition(int beg, int end)
	{
		int piv = list[beg], cnt = 0;

		for (int i = beg + 1; i <= end; i++)
			if (list[i] <= piv)
				cnt++;

		int pivInd = beg + cnt, lrg = beg, sml = end;

		swap(pivInd, beg);

		while (lrg < pivInd && sml > pivInd) {

			while (list[lrg] <= piv)
				lrg++;
			while (list[sml] > piv)
				sml--;

			if (lrg < pivInd && sml > pivInd)
				swap(lrg++, sml--);
		}

		return pivInd;
	}

	//Quick sort
	void quickSort(int beg, int end)
	{

		if (beg >= end)
			return;

		int piv = partition(beg, end);

		quickSort(beg, piv - 1);

		quickSort(piv + 1, end);
	}

	//Divide
	void divide() {
	}

	// Merge
	void merge() {
	}

	//Merge sort
	void mergeSort() {
	}

	//Heap sort
	void heapSort() {
	}

	//Returns the size of the list
	int size() const {
		return n;
	}
};
