#pragma once
#include <iostream>
#include <vector>
int K = 2;

template<class T>
class circularQueue {
	std::vector<T> data;
	size_t size;
	size_t capacity;
	int FRONT;
	int TAIL;
public:
	size_t getSize() {
		return size;
	}
	circularQueue(){
		size = 0;
		capacity = 1;
		data=std::vector<T>(capacity);
		FRONT = 0;
		TAIL = 0;
	}
	
	bool isEmpty() {
		return size == 0;;
	}

	void push(T elem) {
		if (size+1>=capacity) {
			size_t newCapacity = capacity * K, tmp=size;
			std::vector<T> dataNew(newCapacity);
			for (int i = 0; i < tmp; i++) {
				dataNew[i] = this->getTop();
				this->pop();
			}
			//std::copy(data.begin(), data.end(), dataNew.begin());
			data = dataNew;
			TAIL = tmp;
			FRONT = 0;
			size = tmp;
			capacity = newCapacity;
		}
		data[TAIL] = elem;
		TAIL = (TAIL + 1) % capacity; 
		if (size < capacity) size++;
	}
	T getTop() {
		if (size > 0) {
			return data[FRONT];
		}
		else throw "empty queue\n";
	}
	void pop() {
		if (size != 0) {
			data[FRONT] = 0;
			FRONT = (FRONT + 1) % capacity;
			size--;
		}
		else throw "empty queue\n";
	
	}
	void print() {
		for (int i = 0; i < capacity; i++) {
			std::cout << data[i] << " ";
		}
		std::cout << std::endl;
	}
};
