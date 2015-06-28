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

int main() {
	system("pause");
	return 0;
}