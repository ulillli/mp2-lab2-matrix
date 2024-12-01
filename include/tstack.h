#pragma once
#include <iostream>

template<class T, class Container>
class stack {
	Container data;
public:
	explicit stack(const Container& Ñont = Container()) {
		data = Ñont;
	}
	void push(T elem) {
		data.push_back(elem);
	}
	void pop() {
		data.pop_back();
	}
	T& top() {
		if (size() != 0) {
			return data.back();
		}
		else throw "empty stack";
	}
	void clear() {
		data = Container(0);
	}
	bool empty() {
		return data.size() == 0;
	}
	size_t size() {
		return data.size();
	}
};
