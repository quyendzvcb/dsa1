#include<iostream>
using namespace std;
#define MAX 100
struct danhSach {
	int arr[MAX];
	int n;
};
void nhapDs(danhSach& ds) {
	cout << "Nhap so luong phan tu: ";
	cin >> ds.n;
	for (int i = 0; i < ds.n; i++) {
		cout << "arr[" << i << "]: ";
		cin >> ds.arr[i];
	}
}
void xuatDs(danhSach &ds) {
	for (int i = 0; i < ds.n; i++) {
		cout << ds.arr[i] << "\t";
	}
	cout << endl;
}
int timPt(danhSach &ds, int x) {
	for (int i = 0; i < ds.n; i++) {
		if (ds.arr[i] == x) {
			return i;
		}
	}
	return -1;
}
void themCuoi(danhSach& ds,int x) {
	if (ds.n < MAX) {
		ds.arr[ds.n] = x;
		ds.n++;
	}
	else 
		return;
}
void xoaCuoi(danhSach& ds) {
	if (ds.n > 0) {
		ds.n--;
	}
	else cout << "Danh sach rong!!";
}
void xoaTaiViTri(danhSach& ds, int i) {
	if (i >= 0 && i < ds.n) {
		for (int j = i; j < ds.n - 1; j++) {
			ds.arr[i] = ds.arr[j + 1];
		}
		ds.n--;
	}
}
void themTaiViTri(danhSach& ds, int i,int x) {
	if (i >= 0 && i < ds.n && ds.n < MAX) {
		for (int j = ds.n; j > i; j--) {
			ds.arr[j] = ds.arr[j-1];
		}
		ds.arr[i]= x;
		ds.n++;
	}
}
int timMax(danhSach& ds) {
	int max = ds.arr[0];
	for (int i = 1; i < ds.n; i++) {
		if (ds.arr[i] > max) {
			max = ds.arr[i];
		}
	}
	return max;
}
int timMax2(danhSach& ds) {
	int max = timMax(ds);
	int max2= -1;
	for (int i = 0; i < ds.n; i++) {
		if (max2 != max && max2 < ds.arr[i]) {
			max2 = ds.arr[i];
		}
	}
	return max2;
}
void selectionSort(danhSach& ds) {
	for (int i = 0; i < ds.n - 1 ; i++) {
		int min_pos = i;
		for (int j = i + 1; j < ds.n; j++) {
			if (ds.arr[j] > ds.arr[min_pos])
				min_pos = j;
		}
		if (min_pos != i) {
			swap(ds.arr[i], ds.arr[min_pos]);
		}
	}
}
void insertionSort(danhSach& ds) {
	int x, j, i;
	for (int i = 1; i < ds.n; i++) {
		x = ds.arr[i];
		j = i - 1;
		while (0 <= j && x > ds.arr[j]) {
			ds.arr[j + 1] = ds.arr[j];
			j--;
		}
		ds.arr[j + 1] = x;
	}
}
void bubbleSort(danhSach& ds) {
	for (int i = 0; i < ds.n - 1; i++) {
		for (int j = ds.n - 1; j > i; j--) {
			if (ds.arr[j - 1] < ds.arr[j]) {
				swap(ds.arr[j], ds.arr[j - 1]);
			}
		}
	}
}
void interchangeSort(danhSach& ds) {
	for (int i = 0; i < ds.n - 1; i++) {
		for (int j = i + 1; j < ds.n; j++) {
			if (ds.arr[i] < ds.arr[j]) {
				swap(ds.arr[i], ds.arr[j]);
			}
		}
	}
}
void quickSort(danhSach& ds, int left, int right) {
	int x = ds.arr[(left + right) / 2];
	int i = left;
	int j = right;
	while (i <= j) {
		while (ds.arr[i] < x) i++;
		while (ds.arr[j] > x) j--;
		if (i <= j) {
			swap(ds.arr[i], ds.arr[j]);
			i++;
			j--;
		}
	}
	if (left < j) quickSort(ds, left, j);
	if (i < right) quickSort(ds, i, right);
}
void shift(danhSach &ds, int i, int n) {
	int j = 2 * i + 1;
	if (j >= n) return;
	if (j + 1 < n)
		if (ds.arr[j] > ds.arr[j + 1])
			j++;
	if (ds.arr[i] <= ds.arr[j])
		return;
	else {
		swap(ds.arr[i], ds.arr[j]);
		shift(ds, j, n);
	}
}
void heapSort(danhSach& ds) {
	int i = ds.n / 2 - 1;
	while (i >= 0) {
		shift(ds, i, ds.n);
		i--;
	}
	int right = ds.n - 1;
	while (right > 0) {
		swap(ds.arr[0], ds.arr[right]);
		if (right > 0)
			shift(ds, 0, right);
		right--;
	}
}
void timKiemNhiPhan(danhSach& ds, int x, int l, int r) {
	
	while (l < r) {
		int mid = (l + r) / 2;
		if (ds.arr[mid] == x) {
			cout << "Co phan tu!!" << endl;
			return;
		}
		if (ds.arr[mid] > x) return timKiemNhiPhan(ds, x, mid + 1, r);
		return timKiemNhiPhan(ds, x, l, mid - 1);
	}
	cout << "Khong tim thay phan tu: " << endl;
}
int main() {
	danhSach ds;
	nhapDs(ds);
	/*themCuoi(ds, 3);
	xuatDs(ds);
	xoaCuoi(ds);*/
	/*themTaiViTri(ds, 2, 99);*/
	/*selectionSort(ds);*/

	/*insertionSort(ds);*/

	/*bubbleSort(ds);*/

	/*interchangeSort(ds);*/

	//heapSort(ds);
	// 2 3 5 7 9
	heapSort(ds);
	cout << ds.n << endl;
	timKiemNhiPhan(ds, 3, 0, ds.n-1);

	xuatDs(ds);
	return 0;}