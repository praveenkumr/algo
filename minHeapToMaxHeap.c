
int lchild (int i) {
	return (2*i + 1);
}

int rchild (int i) {
	return (2*i + 2);
}

void MaxHeapify(int arr[], int i, int n) {
	int v = arr[i];
	int l = lchild(i);
	int r = rchild(i);
	int maxIndex;
	if ( i > n || i < 0 )
		return;

	if ( l < n && v < arr[l] ) {
		maxIndex = l;
	}
	if ( r < n && arr[maxIndex] < arr[r] ) {
		maxIndex = r;
	}

	if ( maxIndex != i ) {
		// swap
		arr[i] = arr[maxIndex];
		arr[maxIndex] = v;
		MaxHeapify(arr, maxIndex, n);
	}
}


void minToMaxHeap(int arr[], int n) {
	/* Here the idea is just to build a max heap
	 * without caring the output
	 */
	int i = 0;
	for (i = (n-2)/2 ; i >=0; --i ) {
		MaxHeapify (arr, i, n);
	}
	return ;
}
