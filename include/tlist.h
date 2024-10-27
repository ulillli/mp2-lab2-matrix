#include <iostream>

template<typename T>
struct list {
	struct Node {
		Node * next;
		T value;
		Node(Node * n, T data) {
			next = n;
			value = data;
		}
	};
	Node * first = nullptr;
	list(int n = 0) {
		if (n < 0) {
			throw "Not correct the len of the list\n";
		}
		while (n) {
			Node* newNode = new Node(first, 0);
			first = newNode;
			n--;
		}
	}
	list(const list & other) {
		Node* curr1 = other.first;
		if (curr1 != nullptr) {
			Node* curr2 = new Node(nullptr, curr1->value);;
			first = curr2;
			curr1 = curr1->next;
			while (curr1) {
				Node* next1 = new Node(nullptr, curr1->value);
				curr2->next = next1;
				curr2 = next1;
				curr1 = curr1->next;
			}
		}
	}
	Node & operator[](int index) {
		int i = 0;
		Node* curr=first;
		T result;
		while (i != index) {
			curr = curr->next;
			i++;
		}

		return *curr;
	}
	list& operator=(const list& other) {
		Node* curr = first;
		while (first) {
			curr = first->next;
			delete first;
			first = curr;
		}
		Node* curr1 = other.first;
		if (curr1) {
			Node* curr2 = new Node(nullptr, curr1->value);
			curr1 = curr1->next;
			first = curr2;
			while (curr1) {
				Node* tmp= new Node(nullptr, curr1->value);
				curr2->next = tmp;
				curr2 = curr2->next;
				curr1 = curr1->next;
			}
		}
		return *this;
	}
	list(list&& other) {
		first = other.first;
		other.first =nullptr;
	}
	size_t size() const {
		Node* curr = first;
		size_t count = 0;
		while (curr) {
			count++;
			curr = curr->next;
		}
		return count;
	}
	void print() {
		Node* curr = first;
		while (curr) {
			std::cout << curr->value << " ";
			curr = curr->next;
		}
		std::cout << std::endl;
	}
	Node * insert_front(T data) {
		first = new Node(first, data);
		return first;
	}
	Node* insert_after(T data, Node * prev) {
		Node* tmp = new Node(prev->next, data);
		prev->next = tmp;
		return tmp;
	}
	void erase_afer(Node* prev) {
		if (prev->next != nullptr) {
			Node * tmp = prev->next->next;
			delete prev->next;
			prev->next = tmp;
		}
	}
	void erase_front() {
		if (first!= nullptr) {
			Node * tmp = first->next;
			delete first;
			first = tmp;
		}
	}
	void erase_back() {
		Node * curr = first;
		while (curr->next->next) {
			curr = curr->next;
		}
		delete curr->next;
		curr->next = nullptr;
	}
	Node * insert_back(T data) {
		Node * curr = first;
		while (curr->next) {
			curr = curr->next;
		}
		curr->next = new Node(nullptr, data);
		return curr;
	}
	~list() {
		Node * curr=first;
		while (first) {
			curr = first->next;
			delete first;
			first = curr;
			/*first = curr->next;
			delete curr;
			curr = first;*/
		}
	}
};