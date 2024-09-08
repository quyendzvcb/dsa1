#include<iostream>
#include<string>
#include<cstring>
#include<fstream>
#include<vector>
#define DIEMTB 3
using namespace std;
struct SinhVien {
	long long mssv;
	string hoTen;
	char maLop[9];
	string phoneNumber;
	double diemTb[3];
};
void nhap1Sv(SinhVien& sv) {
	cout << "Nhap ma so sinh vien: ";
	cin >> sv.mssv;
	cin.ignore();
	cout << "Nhap ho va ten: ";
	getline(cin, sv.hoTen);
	cout << "Nhap ma lop: ";
	cin >> sv.maLop;
	cout << "Nhap so dien thoai: ";
	cin >> sv.phoneNumber;
	cout << "Nhap diem trung binh 3 mon: ";
	for (int i = 0; i < DIEMTB; i++) {
		cin >> sv.diemTb[i];
	}
}
void xuat1Sv(SinhVien& sv) {
	cout << "===========THONG TIN SINH VIEN=============\n";
	cout << "Ma so sinh vien: " << sv.mssv << endl;
	cout << "Ho va ten:" << sv.hoTen << endl;
	cout << "Ma lop: " << sv.maLop << endl;
	cout << "So dien thoai: " << sv.phoneNumber << endl;
	cout << "Diem trung binh 3 mon: ";
	for (int i = 0; i < DIEMTB; i++) {
		cout << sv.diemTb[i] <<  " ";
	}
}
struct NodeSinhVien {
	SinhVien sv;
	NodeSinhVien* prev;
	NodeSinhVien* next;
};
struct doubleLinkedList {
	NodeSinhVien* head;
	NodeSinhVien* tail;
};
void init(doubleLinkedList& dl) {
	dl.head = dl.tail = NULL;
}
NodeSinhVien* createNode(SinhVien sv) {
	NodeSinhVien* p = new NodeSinhVien;
	p->sv = sv;
	p->next = p->prev = NULL;
	return p;
}
void insertFirst(doubleLinkedList& dl, SinhVien sv) {
	NodeSinhVien* p = createNode(sv);
	if (dl.head == NULL) {
		dl.head = dl.tail = p;
	}
	else {
		p->next = dl.head;
		dl.head->prev = p;
		dl.head = p;
	}
}
void delEle(NodeSinhVien* &p) {
	p->next = NULL;
	p->prev = NULL;
	delete p;
}
void delFirst(doubleLinkedList& dl) {
	if (dl.head != NULL) {
		NodeSinhVien* p = dl.head;
		dl.head = dl.head->next;
		if (dl.head == NULL) {
			dl.tail = NULL;
		}
		else
			dl.head->prev = NULL;
		delEle(p);
	}
}
void delLast(doubleLinkedList& dl) {
	if (dl.head != NULL) {
		NodeSinhVien* p = dl.tail;
		dl.tail = dl.tail->prev;
		if (dl.tail == NULL) {
			dl.head = NULL;
		}
		else {
			dl.tail->next = NULL;
		}
		delEle(p);
	}
}
void delNode(doubleLinkedList& dl, string key) {
	NodeSinhVien* p = search(dl, key);
	if (dl.head != NULL) {
		if (p != NULL) {
			p->prev->next = p->next;
			p->next->prev = p->prev;
			delEle(p);
		}
	}
}
int diemTB(SinhVien sv) {
	int diemtb = 0;
	for (int i = 0; i < DIEMTB; i++) {
		diemtb += sv.diemTb[i];
	}
	return diemtb/DIEMTB ;
}
void swap(NodeSinhVien*& a, NodeSinhVien*& b) {
	NodeSinhVien* tmp = a;
	a = b;
	b = tmp;
}
void sortList(doubleLinkedList& dl) {
	if (dl.head != NULL) {
		for (NodeSinhVien* i = dl.head; i->next != NULL; i++) {
			for (NodeSinhVien* j = i->next; j != NULL; j++) {
				if (diemTB(i->sv) > diemTB(j->sv)) {
					swap(i->sv, j->sv);
				}
			}
		}
	}
}
void readFile(doubleLinkedList& dl) {
	ifstream myFile("data_sv.txt");
	if (myFile.is_open()) {
		while (!myFile.eof()) {
			SinhVien sv;
			myFile >> sv.mssv;
			myFile.ignore();
			getline(myFile, sv.hoTen, '\n');
			myFile.getline(sv.maLop, 9, '\n');
			myFile >> sv.phoneNumber;
			cin.ignore();
			for (int i = 0; i < DIEMTB; i++) {
				myFile >> sv.diemTb[i];
			}
			insertFirst(dl, sv);
		}
		myFile.close();
	}
}
void displayOpt(doubleLinkedList& dl, string key) {
	vector<int> res;
	int num = stoi(key);
	while (num != 0) {
		int tmp = num % 10;
		res.push_back(tmp);
		num /= 10;
	}
	for (int i = 0; i < res.size() - 1; i++) {
		for (int j = i + 1; j < res.size(); j++) {
			if (res[i] > res[j])
				swap(res[i], res[j]);
		}
	}
	NodeSinhVien* p = dl.head;
	while (p != NULL) {
		cout << "========THONG TIN SINH VIEN==========\n";
		for (int i = 0; i < res.size(); i++) {
			switch (res[i])
			{
			case 1: cout << "Mssv: " << p->sv.mssv << endl;
				break;
			case 2: cout << "Ho va ten: " << p->sv.hoTen << endl;
				break;
			case 3: cout << "So dien thoai: " << p->sv.phoneNumber << endl;
				break;
			case 4: cout << "Diem 3 mon: ";
				for (int i = 0; i < DIEMTB; i++) {
					cout << p->sv.diemTb[i] << " ";
				}
				break;
			default:
				break;
			}
		}
			cout << "==================================";
			p = p->next;
	}
}
NodeSinhVien* search(doubleLinkedList& dl, string key) {
	NodeSinhVien* p = dl.head;
	while (p != NULL) {
		if (p->sv.hoTen == key || p->sv.maLop == key) {
			return p;
		}
		p = p->next;
	}
	return p;
}
void duyetDs(doubleLinkedList& dl) {
	if (dl.head != NULL) {
		NodeSinhVien* p = dl.head;
		while (p != NULL) {
			xuat1Sv(p->sv);
			int choose;
			cout << "1:Tiep/0:Tro lai:=>";
			cin >> choose;
			switch (choose)
			{
			case 1:
				p = p->next;
				break;
			case 0:
				p = p->prev;
				break;
			default:
				cout << "ERROR!!";
				break;
			}
			system("cls");
			p = p->next;
		}
	}
}
void destroyList(doubleLinkedList& dl) {
	if (dl.head != NULL) {
		while (dl.head != NULL) {
			delFirst(dl);
		}
	}
	
}
int main() {
	doubleLinkedList dl;
	init(dl);
	readFile(dl);
	duyetDs(dl);
	
	NodeSinhVien* p = search(dl, "DH23CS01");
	if (p != NULL) {
		xuat1Sv(p->sv);
	}
	else cout << "Khong tim thay sinh vien!!";

	if (p != NULL) {

	}
	delNode(dl, "DH23CS01");

	sortList(dl);

	cout << "=====DANH SACH THONG TIN SINH VIEN======\n";
	cout << "1: Mssv" << endl;
	cout << "2: Ho va ten" << endl;
	cout << "3: So dien thoai" << endl;
	cout << "4: Diem trung binh 3 mon" << endl;
	cout << "Nhap lua chon(vd: 123 or 234): ";
	displayOpt(dl, "123");
	destroyList(dl);
	SinhVien sv;
	/*nhap1Sv(sv);
	xuat1Sv(sv);*/
	return 0;
}