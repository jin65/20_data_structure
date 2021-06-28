#include <stdio.h>
#define SWAP(a,b,t) ((t)=(a),(a)=(b), (b)=(t))

void selectionSort(int arr[], int n) {
	int min = 0;
	int temp = 0;
	for (int i = 0; i < n - 1; i++) {
		min = i;
		for (int j = i+1; j < n; j++) {
			if (arr[j] < arr[min])
				min = j;
		}
		SWAP(arr[i], arr[min], temp);
	}
}