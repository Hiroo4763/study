#include <iostream>

int arr[100];
int mergearr[100];

void merge(int low, int mid, int high) {
	int i = low, int j = mid + 1;
	int k = low;

	
	while (i <= mid && j <= high) {
		if (arr[i] <= arr[j]) {
			mergearr[k] = arr[i];
			k++, i++;
		}
		else {
			mergearr[k] = arr[j];
			j++, k++;
		}
	}

	while (i <= mid ) {
		mergearr[k] = arr[i];
		k++, i++;

	}

	while (j <= mid) {
		mergearr[k] = arr[j];
		k++, j++;

	}

	for (int i = low; i <= high; i++) {
		arr[i] = mergearr[i];
	}


}

void merge_sort(int low, int high) {
	if (low < high) {
		int mid = (low + high) / 2;
		merge_sort(low, mid);
		merge_sort(mid + 1, high);
		merge(low, mid, high);
	}
}

int main() {

}