// Authors: Evan Hafner, Robin Steyer
// Course Title: Data Structures
// Course Number: CS2028
// Instructor: Anca Ralescu
// TA: Suryadip Chakraborty
// Abstract: Assignment 4: This application serves to display the effectiveness of
//	various sorting algorithms. Run the program for a better description.
// Preconditions: ?
// Postconditions: ?

#include <iostream>
#include <vector>

using namespace std;

vector<int> merge(vector<int> &l, vector<int> &r) {
	// merges two vectors, to be used with MergeSort
	vector<int> result;
	unsigned int l1 = 0, r1 = 0;
	while (l1 < l.size() || r1 < r.size()) {
		if (l1 == l.size()) { // if left vector is done
			result.push_back(r[r1]);
			r1++;
		}
		else if (r1 == r.size()) { // if right vector is done
			result.push_back(l[l1]);
			l1++;
		}
		else if (l[l1] < r[r1]) { // if next value of left is less
			result.push_back(l[l1]);
			l1++;
		}
		else { // if next value of right is less (or equal)
			result.push_back(r[r1]);
			r1++;
		}
	}
	return result;
}

void mergeSort(vector<int> &v) {
	// merge sort a vector
	if (v.size() <= 1) { // base case: 0 or 1 element
		return;
	}
	unsigned int mid = v.size() / 2;
	vector<int> l, r;
	for (unsigned int i = 0; i < v.size(); i++) {
		if (i < mid){ // left half of vector
			l.push_back(v[i]);
		}
		else{ // right half of vector
			r.push_back(v[i]);
		}
	}
	mergeSort(l);
	mergeSort(r);
	v = merge(l, r);
	return;
}

void insertionSort(vector<int> &v) {
	// insertion sort a vector
	int n;
	int temp;
	for (unsigned int i = 0; i < v.size(); i++) {
		n = i;
		while (n > 0 && v[n] < v[n - 1]) {
			temp = v[n];
			v[n] = v[n - 1];
			v[n - 1] = temp;
			n--;
		}
	}
	return;
}

void bubbleSort(vector<int> &v) {
	// bubble sort a vector
	int temp;
	for (unsigned int i = 0; i < v.size() - 1; i++) {
		for (unsigned int j = 0; j < v.size() - 1; j++) {
			if (v[j] > v[j + 1]) {
				temp = v[j];
				v[j] = v[j + 1];
				v[j + 1] = temp;
			}
		}
	}
	return;
}

// this function declares the ending element as the pivot, then places the elements
// to the left or right of the pivot, depending on whether they are bigger or smaller
// Return Value: index of the partition
int partition(vector<int> &v, int start, int end) {
	int pivotValue = v[end];
	int partitionIndex = start - 1;
	int temp;

	for (int n = start; n < end; n++) {
		if (v[n] <= pivotValue) {
			temp = v[partitionIndex];
			v[partitionIndex] = v[n];
			v[n] = temp;
			partitionIndex++;
		}
	}

	partitionIndex++;
	temp = v[partitionIndex];
	v[partitionIndex] = v[end];
	v[end] = temp;

	return partitionIndex;
}

void quickSort(vector<int> &v, int start, int end) {
	if (start < end) {
		int partitionIndex = partition(v, start, end);
		quickSort(v, start, partitionIndex - 1);
		quickSort(v, partitionIndex + 1, end);
	}
}

int main() {
	system("pause");
	return 0;
}