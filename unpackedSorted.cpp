#include <iostream>
using namespace std;

const int SIZE{ 100 };
int A[SIZE]; //Ascending Order
bool mark[SIZE];
int index; //the index of last element - Actually, it's tricky in unpacked sorted array operation.
int cnt;

void insert(int position, int a) {
	if (mark[position] == false) {
		A[position] = a;
		mark[position] = true;
		cnt++;
	}
	else {
		bool flag{ false };
		int end;
		for (end = position; end <= SIZE; end++) {
			if (mark[end] == false) {
				flag = true;
				break;
			}
		}
		if (flag == true) { //false exists.
			for (int i{ end - 1 }; i >= position + 1; i--) {
				A[i + 1] = A[i];
			}
			A[position + 1] = A[position];
			A[position] = a;
			cnt++;
			for (int i{ position }; i <= end; i++) mark[i] = true;
		}
		else { //false doesn't exist.
			if (mark[position - 1] == false) {
				A[position - 1] = a;
				cnt++;
				mark[position - 1] = true;
			}
			else {
				int index_false = -1;
				for (int i{ position - 2 }; i >= 0; i--) {
					if (mark[i] == false) {
						flag = true;
						index_false = i;
						break;
					}
				}
				//flag must be true.
				mark[index_false] = true;
				for (int i{ index_false }; i <= position - 1; i++) {
					A[i] = A[i + 1];
				}
				A[position] = a;
				cnt++;
			}
		}
	}
}

int unpackedSorted_search(int a, int left, int right) { //Binary Search
	if (right == left) {
		if (A[right] == a) {
			return right;
		}
		else return -1;
	}
	else if (right < left) {
		if (A[left] == a) return left;
		if (A[right] == a) return right;
		else return -1;
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
	return unpackedSorted_search(a, left, right);
}

int main() {
	index = -1;
	cnt = 0;
	for (int i{}; i < SIZE; i++) mark[i] = false;
	char ch{};

	while (ch != 'q') {
		//Print Array-------
		cout << "Array" << endl;

		for (int i{}; i <= index; i++) cout << i << "\t";
		cout << endl;

		for (int i{}; i <= index; i++) cout << A[i] << "\t";
		cout << endl;

		for (int i{}; i <= index; i++) cout << mark[i] << "\t";
		cout << endl;
		//------------------


		cout << "Enter the option: ";
		cin >> ch;

		if (ch == 'i') {
			int a;
			cin >> a;

			int index_ = unpackedSorted_search(a, 0, index);

			if (index == -1) {
				A[0] = a;
				index++;
				mark[0] = true;
				cnt++;
			}
			else if (index_ != -1) {
				if (mark[index_] == true) cout << a << " is already stored." << endl;
				else {
					mark[index_] = true;
					cnt++;
				}
			}
			else {
				if (cnt == SIZE) {
					cout << "The array is already full." << endl;
				}
				else if (index == 0) {
					if (A[0] < a) {
						A[1] = a;
						mark[1] = true;
						cnt++;
					}
					else { //a < A[0]
						int tmp;
						tmp = A[0];
						A[0] = a;
						A[1] = tmp;
						mark[1] = true;
						cnt++;
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
						if (A[left] < a) { //A[left+1] = a
							//WORST case: left+1 ~ index -> left+2 ~ index+1
							insert(left + 1, a);
						}
						else { //A[left] = a
							insert(left, a);
						}
					}
					else if (left > right) { //A[left] = a
						insert(left, a);
					}
					index++;
				}
			}
		}
		else if (ch == 'd') {
			int a;
			cin >> a;

			if (index == -1) {
				cout << "The array is empty." << endl;
				continue;
			}

			int index_a{};
			index_a = unpackedSorted_search(a, 0, index);

			if ((index_a == -1) || (mark[index_a] == false)) {
				cout << a << " is not stored in array." << endl;
			}
			else {
				mark[index_a] = false;
				cnt--;
				if (index_a == index) {
					for (int i{ index - 1 }; i >= 0; i--) {
						if (mark[i] == true) {
							index = i;
							break;
						}
					}
				}
			}
		}
		else if (ch == 's') {
			int a;
			cin >> a;

			int result;
			result = unpackedSorted_search(a, 0, index);
			if (mark[result] == false) result = -1;

			if (result == -1) cout << a << " is not in array." << endl;
			else cout << a << " is at " << result << "." << endl;
		}
	}
	return 0;
}