int binarySearchRec(int arr[], int left, int right, int key) {
    if(left > right) return -1;
    int mid = (left + right) / 2;
    if(arr[mid] == key)
        return mid;
    else if(arr[mid] < key)
        return binarySearchRec(arr, mid + 1, right, key);
    else
        return binarySearchRec(arr, left, mid - 1, key);
}
