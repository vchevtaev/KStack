#pragma once
#include <fstream>
#include <iostream>
#include <istream>
#include <ostream>
using namespace std;
template <typename T, typename U>
class StackIterator {
private:
	U* stack;
	int index;

public:
	StackIterator(U* stack1) { stack = stack1; }
	void First() { index = 0; }
	void Next() { index++; }
	bool IsDone() { return index == stack->size_; }
	T currentItem() { return stack->data_[index]; }
};

template <typename T>
class Stack {
	friend class StackIterator<T, Stack>;

private:
	T* data_;
	int size_;
	int capacity_;

public:
	Stack();
	Stack(const int size);
	Stack(const initializer_list<T>& list);
	Stack(Stack& stack);
	Stack(Stack&& stack);
	~Stack();
	bool IsEmpty();
	int Size();
	void Clear();
	T Top();
	void Push(T element);
	T Pop();
	StackIterator<T, Stack>* createIterator() {
		return new StackIterator<T, Stack>(this);
	}
	void Swap(Stack& stack);
	friend ostream& operator<<(ostream& out, Stack<T>& stack) {
		StackIterator < T, Stack < T>>* it = stack.createIterator();
		for (it->First(); !it->IsDone(); it->Next()) {
			out << it->currentItem() << " ";
		}
		delete it;
		return out;
	}
	friend istream& operator>>(istream& in, Stack& stack) {
		for (int i = 0; i < stack.capacity_; i++) {
			in >> stack.data_[i];
		}
		stack.size_ = stack.capacity_;
		return in;
	}
	bool operator==(Stack& stack);
	bool operator!=(Stack& stack1);
	Stack& operator+=(Stack& stack);
	Stack& operator+(Stack& stack);
	Stack& operator=(Stack& stack);
	Stack& operator=(Stack&& stack);
};
template <typename T>
Stack<T>::Stack() {
	data_ = new T[10];
	capacity_ = 10;
	size_ = 0;
}
template <typename T>
Stack<T>::Stack(Stack& stack) {
	if (stack.size_ > size_) {
		delete[] data_;
		capacity_ = stack.capacity_;
		size_ = stack.size_;
		data_ = new T[capacity_];
	}
	StackIterator<T, Stack>* it = stack.createIterator();
	int i = 0;
	for (it->First(); !it->IsDone(); it->Next()) {
		data_[i] = it->currentItem();
		i++;
	}
	delete it;
}
template <typename T>
Stack<T>::Stack(Stack&& stack) {
	if (stack.size_ > size_) {
		delete[] data_;
		capacity_ = stack.capacity_;
		size_ = stack.size_;
		data_ = new T[capacity_];
	}
	StackIterator<T, Stack>* it = stack.createIterator();
	int i = 0;
	for (it->First(); !it->IsDone(); it->Next()) {
		data_[i] = it->currentItem();
		i++;
	}
	delete it;
	while (stack.size_ > 0) {
		stack.Pop();
	}
	return this;
}
template <typename T>
Stack<T>::Stack(const int size) {
	data_ = new T[size];
	capacity_ = size;
	size_ = 0;
}
template <typename T>
Stack<T>::Stack(const initializer_list<T>& list) {
	size_ = 0;
	capacity_ = 10;
	data_ = new T[capacity_];
	for (auto it = list.begin(); it != list.end(); it++) {
		this->Push(*it);
	}
}
template <typename T>
Stack<T>::~Stack() {
	delete[] data_;
}
template <typename T>
bool Stack<T>::IsEmpty() {
	return size_ == 0;
}
template <typename T>
int Stack<T>::Size() {
	return size_;
}
template <typename T>
void Stack<T>::Push(T element) {
	if (size_ == capacity_) {
		T* new_data_ = new T[capacity_ * 2];
		// put all objects from data to new_data
		for (int i = 0; i < size_; i++) {
			new_data_[i] = data_[i];
		}
		//
		delete[] data_;
		capacity_ *= 2;
		data_ = new T[capacity_];
		// put all objects from new_data to data
		for (int i = 0; i < size_; i++) {
			data_[i] = new_data_[i];
		}
		//
		delete[] new_data_;
	}
	data_[size_] = element;
	size_++;
}
template <typename T>
T Stack<T>::Top() {
	if (size_ > 0) return data_[size_ - 1];
	throw "Your stack is Empty";
}
template <typename T>
T Stack<T>::Pop() {
	if (size_ > 0) {
		size_--;
		return data_[size_];
	}
	throw "Your stack is empty";
}
template <typename T>
void Stack<T>::Clear() {
	while (size_ > 0) {
		this->Pop();
	}
}
template <typename T>
Stack<T>& Stack<T>::operator+(Stack& stack) {
	StackIterator<T, Stack>* it = stack.createIterator();
	for (it->First(); !it->IsDone(); it->Next()) {
		this->Push(it->currentItem());
	}
	delete it;
	return *this;
}
template <typename T>

Stack<T>& Stack<T>::operator=(Stack& stack) {
	if (stack.size_ > size_) {
		delete[] data_;
		capacity_ = stack.capacity_;
		size_ = stack.size_;
		data_ = new T[capacity_];
	}
	StackIterator<T, Stack>* it = stack.createIterator();
	int i = 0;
	for (it->First(); !it->IsDone(); it->Next()) {
		data_[i] = it->currentItem();
		i++;
	}
	delete it;
	return *this;
}
template <typename T>
Stack<T>& Stack<T>::operator=(Stack&& stack) {
	if (stack.size_ > size_) {
		delete[] data_;
		capacity_ = stack.capacity_;
		size_ = stack.size_;
		data_ = new T[capacity_];
	}
	StackIterator<T, Stack>* it = stack.createIterator();
	int i = 0;
	for (it->First(); !it->IsDone(); it->Next()) {
		data_[i] = it->currentItem();
		i++;
	}
	while (!stack.IsEmpty()) {
		stack.Pop();
	}
	delete it;
	return *this;
}
template <typename T>
Stack<T>& Stack<T>::operator+=(Stack& stack) {
	StackIterator<T, Stack>* it = stack.createIterator();
	for (it->First(); !it->IsDone(); it->Next()) {
		this->Push(it->currentItem());
	}
	delete it;
	return *this;
}
template <typename T>
bool Stack<T>::operator==(Stack& stack) {
	StackIterator<T, Stack>* it1 = this->createIterator();
	StackIterator<T, Stack>* it2 = stack.createIterator();
	for (it1->First(), it2->First(); !it1->IsDone(); it1->Next(), it2->Next()) {
		if (it1->currentItem() != it2->currentItem()) {
			break;
		}
	}
	bool answer = it1->IsDone() && it2->IsDone();
	delete it1;
	delete it2;
	return answer;
}
template <typename T>
bool Stack<T>::operator!=(Stack& stack) {
	if (*this == stack) {
		return false;
	}
	return true;
}
template <typename T>
void Stack<T>::Swap(Stack& stack) {
	Stack<T> buffer_stack = stack;
	stack.Clear();
	StackIterator<T, Stack>* it = this->createIterator();
	for (it->First(); !it->IsDone(); it->Next()) {
		stack.Push(it->currentItem());
	}
	this->Clear();
	it = buffer_stack.createIterator();
	for (it->First(); !it->IsDone(); it->Next()) {
		this->Push(it->currentItem());
	}
}
