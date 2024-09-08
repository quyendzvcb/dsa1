#include<iostream>
using namespace std;
#define MAX 50
struct Node {
	int info;
	Node* left;
	Node* right;
	int count;
};
void init(Node*& root) {
	root = NULL;
}
Node* createNode(int x) {
	Node* p = new Node;
	p->count = 1;
	p->info = x;
	p->left = p->right = NULL;
	return p;
}
//with recusion
void insertNodeWithoutRecusion(Node*& root, int x) {
	if (root == NULL) {
		root = createNode(x);
	}
	if (x == root->info) {
		return;
	}
	if (x > root->info) {
		return insertNodeWithoutRecusion(root->right, x);
	}
	else if (x < root->info) {
		return insertNodeWithoutRecusion(root->left, x);
	}
}
//normal
void insertNode(Node*& p, int x) {
	Node* q = createNode(x);
	if (p == NULL) {
		p = q;
	}
	else {
		Node* tmp = p;
		Node* parent = NULL;
		while (tmp != NULL) {
			parent = tmp;
			if (tmp->info == x) {
				return;
			}
			else {
				if (x < tmp->info) {
					tmp = tmp->left;
				}
				else tmp = tmp->right;
			}
		}
		if (x < parent->info) {
			parent->left = q;
		}
		else parent->right = q;
	}
}
Node* searchNode(Node* p, int x) {
	if (p != NULL) {
		if (p->info == x) {
			return p;
		}
		else {
			if (p->info < x) return searchNode(p->right, x);
			else return searchNode(p->left, x);
		}
	}
	return NULL;
}
void searchStandFor(Node*& p, Node*& q) {
	if (q->left != NULL) {
		searchStandFor(p, q->left);
	}
	else {
		p->info = q->info;
		p = q;
		q = q->right;
	}
}
void delNode(Node* root, int x) {
	if (root == NULL)
		return;
	if (x == root->info) {
		Node* p = root;
		if (root-> left == NULL) {
			root = root->right;
		}
		else if (root->right ==NULL ){
			root = root->left;
		}
		else {
			searchStandFor(p, root->right);
		}
		delete p;
		p = NULL;
		return;
	}
	if (x > root->info)
		delNode(root->right, x);
	else if (x < root->info)
		delNode(root->left, x);
}
void LRN(Node* p) {
	if (p != NULL) {
		LRN(p->left);
		LRN(p->right);
		cout << p->info << "\t";
	}
}
void NLR(Node* p) {
	if (p != NULL) {
		cout << p->info << "\t";
		LRN(p->left);
		LRN(p->right);
	}
}
void LNR(Node* p) {
	if (p != NULL) {
		LRN(p->left);
		cout << p->info << "\t";
		LRN(p->right);
	}
}
//STACK
struct Stack {
	Node* a[MAX];
	int top;
};
void initStack(Stack& s) {
	s.top = -1;
}
bool isEmpty(Stack s) {
	return s.top == -1;
}
bool isFull(Stack s) {
	return s.top = MAX - 1;
}
void push(Stack& s, Node* p) {
	if (s.top < MAX - 1) {
		s.a[++s.top] = p;
	}
	else {
		cout << "Stack overflow!" << endl;
	}
}
Node* pop(Stack& s) {
	if (!isEmpty(s)) {
		return s.a[s.top--];
	}
}
Node* peek(Stack& s) {
		return s.a[s.top];  
}

void LNRNoRec(Node* root) {
	if (root != NULL) {
		Stack s;
		initStack(s);
		Node* p = root;
		while (!isEmpty(s) || p != NULL) {
			while (p != NULL) {
				push(s, p);
				p = p->left;
			}
			p = pop(s);
			cout << p->info << " ";
			p = p->right;
		}
	}
}
void NLRNoRec(Node* root) {
	if (root != NULL) {
		Stack s;
		initStack(s);
		Node* p = root;
		while (!isEmpty(s) || p != NULL) {
			while (p != NULL) {
				cout << p->info << " ";
				push(s, p);
				p = p->left;
			}
			p = pop(s);
			p = p->right;
		}
	}
}

void LRNNoRec(Node* root) {
	if (root != NULL) {
		Stack s;
		initStack(s);   // Khởi tạo ngăn xếp
		Node* p = root; // Con trỏ hiện tại
		Node* prev = NULL; // Lưu dấu nút trước đó đã được duyệt

		do {
			// Đẩy tất cả các nút bên trái vào ngăn xếp
			while (p != NULL) {
				push(s, p);
				p = p->left;
			}

			// Lấy nút trên đỉnh ngăn xếp
			p = peek(s);

			// Kiểm tra nếu nhánh phải đã duyệt xong hoặc không tồn tại
			if (p->right == NULL || p->right == prev) {
				// In giá trị nút (sau khi đã duyệt xong cả trái và phải)
				cout << p->info << " ";

				// Đánh dấu nút hiện tại đã duyệt xong
				prev = p;
				pop(s);
				p = NULL;  // Đặt p = NULL để không quay lại nhánh trái
			}
			else {
				// Nếu nhánh phải chưa duyệt, chuyển sang nhánh phải
				p = p->right;
			}
		} while (!isEmpty(s));
	}
}
struct NodeQueue {
	Node* value;
	NodeQueue* next;
};
void init(NodeQueue*& q) {
	q = NULL;
}
bool isEmpty(NodeQueue* q) {
	return q == NULL;
}
NodeQueue* createNodeQueue(Node* x) {
	NodeQueue* p = new NodeQueue;
	p->value = x;
	p->next = NULL;
	return p;
}
void enQueue(NodeQueue*& head, Node* x) {
	if (head == NULL) {
		head = createNodeQueue(x);
	}
	else {
		NodeQueue* p = createNodeQueue(x);
		NodeQueue* q = head;
		while (q->next != NULL) {
			q = q->next;
		}
		q->next = p;
	}
}
Node* deQueue(NodeQueue*& head) {
	if (head != NULL) {
		NodeQueue* p = head;
		head = head->next;
		p->next = NULL;
		return p->value;
	}
}
void displayTreeQueue(Node* root) {
	NodeQueue* q;
	init(q);
	enQueue(q, root);
	Node* cur = NULL;
	while (!isEmpty(q)) {
		cur = deQueue(q);
		cout << cur->info << " ";
		if (cur->left != NULL)
			enQueue(q, cur->left);
		if (cur->right != NULL)
			enQueue(q, cur->right);
	}
}
int main() {
	Node* root;
	init(root);
	insertNode(root, 2);
	insertNode(root, 6);
	insertNode(root, 8);
	insertNode(root, 4);

	/*Node* p = searchNode(root, 2);
	if (p!=NULL){
		cout << "Co phan tu" << endl;
	}*/
	/*delNode(root, 6);*/
	/*LRN(root);
	cout << endl;
	LRNNoRec(root);*/

	


	displayTreeQueue(root);
	

	/*searchNode(root, 2);*/
	return 0;
}