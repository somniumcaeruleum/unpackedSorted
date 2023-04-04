#include <iostream>
using namespace std;

const int SIZE{ 100 };
int A[SIZE]; //Ascending Order
int index; //the index of last element
int cnt; //the number of elements
bool flag[SIZE];

int unpackedSorted_search(int a, int left, int right) { //Binary Search
	if (right == left) {
		if (A[right] == a) return right;
		else return -1;
	}
	else if (right < left) {
		if (A[left] == a) return left;
		if (A[right] == a) return right;
		return -1;
	}
	int middle;
	middle = (left + right) / 2;
	if (A[middle] < a) {
		left = middle + 1;
	}
	else if (a < A[middle]) {
		right = middle - 1;
	}
	else {
		return middle;
	}
	return packedSorted_search(a, left, right);
}

int main() {
	cnt = 0;
    for (int i{}; i < SIZE; i++) flag[i] = false;
	char ch{};

	while (ch != 'q') {
		//Print Array-------
		cout << "Array" << endl;
		for (int i{}; i <= index; i++) cout << i << "\t";

		cout << endl;
		for (int i{}; i <= index; i++) cout << A[i] << "\t";

		cout << endl;
		//------------------


		cout << "Enter the option: ";
		cin >> ch;

		if (ch == 'i') {
			int a;
			cin >> a;

			if (index == -1) {
				A[0] = a;
				index++;
			}
			else if (unpackedSorted_search(a, 0, index) != -1) {
				cout << a << " is already stored." << endl;
			}
			else {
				if ((index + 1) == SIZE) {
					cout << "The array is already full." << endl;
				}
				else if (index == 0) {
					if (A[0] < a) {
						A[1] = a;
					}
					else { //a < A[0]
						int tmp;
						tmp = A[0];
						A[0] = a;
						A[1] = tmp;
					}
					index++;
				}
				else {
					int left{};
					int right;
					right = index;

					while (left < right) {
						int middle;
						middle = (left + right) / 2;

						if (A[middle] < a) left = middle + 1;
						else right = middle - 1;
					}
					if (left == right) {
						if (A[left] < a) {//A[left+1] = a
							//left+1 ~ index -> left+2 ~ index+1
							for (int i{index}; i >= left+1; i--) {
								A[i + 1] = A[i];
							}
							A[left + 1] = a;
						}
						else { //A[left] = a
							//left ~ index -> left+1 ~ index+1
							for (int i{index}; i >= left; i--) {
								A[i + 1] = A[i];
							}
							A[left] = a;
						}
					}
					else if (left > right) { //A[left] = a || pitfall: right == -1
						//left ~ index -> left+1 ~ index+1
						for (int i{ index }; i >= left; i--) {
							A[i + 1] = A[i];
						}
						A[left] = a;
					}
					index++;
				}
			}
		}
		else if (ch == 'd') { //Edited
			int a;
			cin >> a;

			if (cnt == 0) {
				cout << "The array is empty." << endl;
				continue;
			}

			int index_a{};
			index_a = unpackedSorted_search(a, 0, index);

			if (index_a == -1) {
				cout << a << " is not stored in array." << endl;
			}

			else {
				flag[index_a] = false;
			}
		}
		else if (ch == 's') {
			int a;
			cin >> a;

			int result;
			result = unpackedSorted_search(a, 0, index);

			if (result == -1) cout << a << " is not in array." << endl;
			else cout << a << " is at " << result << "." << endl;
		}
	}
	return 0;
}