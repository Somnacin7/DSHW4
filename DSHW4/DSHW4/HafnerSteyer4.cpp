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
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

enum large_sort_type { MERGE, QUICK };
enum small_sort_type { BUBBLE, INSERTION };
unsigned int bubbleCounter;
unsigned int insertionCounter;
unsigned int mergeCounter;
unsigned int quickCounter;

// this function merges two vectors, to be used with MergeSort
vector<int> merge(vector<int> &l, vector<int> &r) {
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
			mergeCounter++;
			result.push_back(l[l1]);
			l1++;
		}
		else { // if next value of right is less (or equal)
			mergeCounter++;
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
			insertionCounter++;
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
				// if the current value is greater than the next one, switch them
				temp = v[j];
				v[j] = v[j + 1];
				v[j + 1] = temp;
			}
			bubbleCounter++;
		}
	}
	return;
}

// this function declares the ending element as the pivot, then places the elements
// to the left or right of the pivot, depending on whether they are bigger or smaller
// Return Value: index of the partition
// To be used with quickSort
int partition(vector<int> &v, int start, int end) {
	int pivotValue = v[end];
	int partitionIndex = start;
	int temp;

	for (int n = start; n < end; n++) {
		if (v[n] <= pivotValue) {
			temp = v[partitionIndex];
			v[partitionIndex] = v[n];
			v[n] = temp;
			partitionIndex++;
		}
		quickCounter++;
	}

	//partitionIndex++;
	temp = v[partitionIndex];
	v[partitionIndex] = v[end];
	v[end] = temp;

	return partitionIndex;
}

// quickSort: recursively sorts a vector
void quickSort(vector<int> &v, int start, int end) {
	if (start < end) {
		int partitionIndex = partition(v, start, end);
		quickSort(v, start, partitionIndex - 1);
		quickSort(v, partitionIndex + 1, end);
	}
}

void hybridSort(	vector<int> &v, large_sort_type Large, small_sort_type Small, 
					unsigned int T) {
	if (v.size() > T) {
		if (Large == MERGE) {
			mergeSort(v);
			return;
		}
		quickSort(v, 0, v.size() - 1);
		return;
	}
	if (Small == BUBBLE) {
		bubbleSort(v);
		return;
	}
	insertionSort(v);
	return;
}


void printVector(vector<int> &v) {
	for (unsigned int i = 0; i < v.size(); i++) {
		cout << v[i] << "\t";
	}
	cout << endl;
}

// main function
int main() {
	srand(time(NULL));

	cout << "This program allows the user to create a list, and then hybrid" << endl;
	cout << "sort it depending on an entered threshold" << endl;

	bool again = true;
	int threshold;
	int listSize;
	bool manualEntry;
	bool display = true;
	string tmp;
	int tmpInt;
	bool displayComparisons = false;
	

	while (again) {

		// Get threshold from user
		cout << "Threshold: ";
		cin >> threshold;
		while (threshold < 0) { // If threshold is negative, ask again
			cout << "Please enter a valid threshold: ";
			cin >> threshold;
		}

		// Get whether to display number of comparisons
		cout << "Should the number of comparisons be displayed? (y/n) ";
		while (cin >> tmp) {
			if (tmp == "y") {
				displayComparisons = true;
				break;
			}
			else if (tmp == "n") {
				displayComparisons = false;
				break;
			}
			else {
				cout << "Should the number of comparisons be displayed? (y/n) ";
			}
		}

		// Get size of list
		cout << "List size: ";
		cin >> listSize;
		while (listSize < 0) { // If listSize is negative, ask again
			cout << "Please enter a valid list size: ";
			cin >> listSize;
		}

		vector<int> arr;


		// If <= 100, ask for manual entry
		if (listSize <= 100) {
			cout << "Manual entry or automatic entry? (manual/auto): ";
			while (cin >> tmp) {
				if (tmp == "manual") {
					manualEntry = true;
					break;
				}
				else if (tmp == "auto") {
					manualEntry = false;
					break;
				}
				else {
					cout << "Manual entry or automatic entry? (manual/auto): ";
				}
			}

			if (!manualEntry) {
				cout << "Should the generated lists be displayed? (y/n) ";
				while (cin >> tmp) {
					if (tmp == "y") {
						display = true;
						break;
					}
					else if (tmp == "n") {
						display = false;
						break;
					}
					else {
						cout << "Should the generated lists be displayed? (y/n) ";
					}
				}

			}
			else { // Automatic by default: no manual entry, no display
				display = false;
				manualEntry = false;
			}

			// Enter each value by hand
			if (manualEntry) {
				for (int i = 0; i < listSize; i++) {
					cout << "Value for element " << i << ": ";
					cin >> tmpInt;
					arr.push_back(tmpInt);
				}
			}
			else { // Generated a random integer array
				for (int i = 0; i < listSize; i++) {
					arr.push_back(rand() % 1000000);
				}
			}

			// Create copies to be sorted
			vector<int> bubbleArr = vector<int>(arr);
			vector<int> insertionArr = vector<int>(arr);
			vector<int> mergeBubbleArr = vector<int>(arr);
			vector<int> mergeInsertionArr = vector<int>(arr);
			vector<int> quickBubbleArr = vector<int>(arr);
			vector<int> quickInsertionArr = vector<int>(arr);

			bubbleCounter = 0;
			insertionCounter = 0;
			mergeCounter = 0;
			quickCounter = 0;

			// Perform each sort
			bubbleSort(bubbleArr);
			insertionSort(insertionArr);
			hybridSort(mergeBubbleArr, MERGE, BUBBLE, threshold);
			hybridSort(mergeInsertionArr, MERGE, INSERTION, threshold);
			hybridSort(quickBubbleArr, QUICK, BUBBLE, threshold);
			hybridSort(quickInsertionArr, QUICK, INSERTION, threshold);

			if (display) {
				cout << endl << endl;
				cout << "Unsorted:" << endl;
				printVector(arr);

				cout << endl << endl;
				cout << "Bubble Sort:" << endl;
				cout << "Comparisons: " << bubbleCounter << endl;
				printVector(bubbleArr);

				cout << endl << endl;
				cout << "Insertion Sort:" << endl;
				cout << "Comparisons: " << insertionCounter << endl;
				printVector(insertionArr);

				cout << endl << endl;
				cout << "Hybrid (Merge & Bubble, Threshold = "
					<< threshold << "):" << endl;
				printVector(mergeBubbleArr);

				cout << endl << endl;
				cout << "Hybrid (Merge & Insertion, Threshold = "
					<< threshold << "):" << endl;
				printVector(mergeInsertionArr);

				cout << endl << endl;
				cout << "Hybrid (Quick & Bubble, Threshold = "
					<< threshold << "):" << endl;
				printVector(quickBubbleArr);

				cout << endl << endl;
				cout << "Hybrid (Quick & Insertion, Threshold = "
					<< threshold << "):" << endl;
				printVector(quickInsertionArr);
			}

			cout << endl << endl << "Again? (y/n): ";
			cin >> tmp;
			again = (tmp == "y") ? true : false;

		}
	}

	return 0;
}