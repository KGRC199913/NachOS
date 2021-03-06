#include "syscall.h"

int main() {
	int n, i, j, temp;
	int arr[100];
	PrintString("Size of Array: ");
	n = ReadInt();
	for (i =0; i < n; ++i) {
		arr[i] = ReadInt();
	}

	for (i = 0; i < n; ++i) {
		for (j = 0; j < n; ++j) {
			if (arr[i] < arr[j]) {
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}

	PrintString("Sorted Array:\n");
	for (i = 0; i < n; ++i) {
		PrintInt(arr[i]);
		PrintChar(" \n"[i == (n - 1)]);
	}
	
	Halt();
	return 0;
}
