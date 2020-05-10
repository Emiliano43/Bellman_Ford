#pragma once
#include <iostream>
using namespace std;
template<typename T>
class List
{
private:
	class Node
	{
	private:
		T value;
		Node* next, *prev;
	public:
		Node() : next(nullptr), prev(nullptr) {};
		Node(T value) {
			this->value = value;
			next = nullptr;
			prev = nullptr;
		}
		~Node() {
			next = nullptr;
			prev = nullptr;
		}
		void set_value(T value) {
			this->value = value;
		}
		T get_value() {
			return value;
		}
		Node* get_next() {
			return next;
		}
		Node* get_prev() {
			return prev;
		}
		void set_next(Node* pointer) {
			next = pointer;
		}
		void set_prev(Node* pointer) {
			prev = pointer;
		}
	};
	Node* head, *tail;
	Node* get_pointer(size_t index)
	{
		if (isEmpty() || (index > get_size() - 1))
		{
			throw out_of_range("Invalid argument");
		}
		else if (index == get_size() - 1)
			return tail;
		else if (index == 0)
			return head;
		else
		{
			Node* cur = head;
			while ((cur) && (index--))
			{
				cur = cur->get_next();
			}
			return cur;
		}
	}
public:
	List() : head(nullptr), tail(nullptr) {}
	List(int size, int value) {
		while (size--) {
			push_back(value);
		}
	}
	List(const List<T>& list) {
		head = nullptr;
		tail = nullptr;
		Node* cur = list.head;
		while (cur) {
			push_back(cur->get_value());
			cur = cur->get_next();
		}
	}
	~List()
	{
		while (head)
		{
			tail = head->get_next();
			delete head;
			head = tail;
		}
		head = nullptr;
	}

	void push_back(T value)
	{
		Node* cur = new Node;
		cur->set_value(value);
		if (head)
		{
			cur->set_prev(tail);
			tail->set_next(cur);
			tail = cur;
		}
		else
		{
			head = cur;
			tail = head;
		}
	}
	void push_front(T value)
	{
		Node* cur = new Node;
		cur->set_data(value);
		if (head)
		{
			cur->set_next(head);
			head->set_prev(cur);
			head = cur;
		}
		else
		{
			head = cur;
			tail = head;
		}
	}
	void push_back(List<bool> ls2)
	{
		Node* cur = ls2.head;
		size_t n = ls2.get_size();
		while ((cur) && (n--))
		{
			push_back(cur->get_data());
			cur = cur->get_next();
		}
	}
	void push_front(List& ls2)
	{
		Node* cur = ls2.tail;
		size_t n = ls2.get_size();
		while ((cur) && (n--))
		{
			push_front(cur->get_data());
			cur = cur->get_prev();
		}
	}
	void pop_back()
	{
		if (head != tail)
		{
			Node* cur = tail;
			tail = tail->get_prev();
			tail->set_next(nullptr);
			delete cur;
		}
		else if (!isEmpty())
		{
			Node* cur = tail;
			tail = head = nullptr;
			delete cur;
		}
		else
			throw out_of_range("The list is empty");
	}
	void pop_front()
	{
		if (head != tail)
		{
			Node* cur = head;
			head = head->get_next();
			head->set_prev(nullptr);
			delete cur;
		}
		else if (!isEmpty())
		{
			Node* cur = head;
			head = tail = nullptr;
			delete cur;
		}
		else
			throw out_of_range("The list is empty");
	}
	void insert(size_t index, T data)
	{
		Node* cur;
		cur = get_pointer(index);
		if (cur == head)
			push_front(data);
		else
		{
			Node* newElem = new Node;
			newElem->set_data(data);
			cur->get_prev()->set_next(newElem);
			newElem->set_prev(cur->get_prev());
			newElem->set_next(cur);
			cur->set_prev(newElem);
		}
	}
	T at(size_t index)
	{
		Node* cur;
		cur = get_pointer(index);
		return cur->get_value();
	}
	void remove(size_t index)
	{
		Node* cur;
		cur = get_pointer(index);
		if (cur == head)
			pop_front();
		else if (cur == tail)
			pop_back();
		else
		{
			cur->get_prev()->set_next(cur->get_next());
			cur->get_next()->set_prev(cur->get_prev());
			delete cur;
		}
	}
	void remove(T value) {
		Node* cur = head;
		while (cur && cur->get_data() != value)
			cur = cur->get_next();
		if (!cur)
			throw out_of_range("Invalid argument");
		if (cur == head)
			pop_front();
		else if (cur == tail)
			pop_back();
		else
		{
			cur->get_prev()->set_next(cur->get_next());
			cur->get_next()->set_prev(cur->get_prev());
			delete cur;
		}
	}
	size_t get_size()
	{
		Node* cur = head;
		size_t length = 0;
		while (cur)
		{
			length++;
			cur = cur->get_next();
		}
		return length;
	}
	void print_to_console()
	{
		Node* cur = head;
		while (cur)
		{
			cout << cur->get_value();
			cur = cur->get_next();
		}
	}
	void clear()
	{
		while (head)
		{
			tail = head->get_next();
			delete head;
			head = tail;
		}
	}
	void set(size_t index, T value)
	{
		Node* cur;
		cur = get_pointer(index);
		cur->set_value(value);
	}
	bool isEmpty()
	{
		if (!head)
			return true;
		else
			return false;
	}
	bool compare(List<T> ls) {
		if (get_size() != ls.get_size())
			return false;
		for (int i = 0; i < get_size(); i++) {
			if (at(i) != ls.at(i))
				return false;
		}
		return true;
	}
	bool contains(List<char>& ls) {
		Node* cur = head;
		while (cur) {
			if (cur->get_data().compare(ls))
				return true;
			cur = cur->get_next();
		}
		return false;
	}
	void nullify() {
		head = nullptr;
		tail = nullptr;
	}
	void reverse() {
		Node* cur1 = head, *cur2 = tail;
		T value;
		for (size_t i = 0; i < get_size() / 2; i++) {
			value = cur1->get_value();
			cur1->set_value(cur2->get_value());
			cur2->set_value(value);
			cur1 = cur1->get_next();
			cur2 = cur2->get_prev();
		}
	}
	int get_price(size_t vertex1, size_t vertex2) {
		Node* cur = head;
		while (cur) {
			if (cur->get_value().vertex1 == vertex1 && cur->get_value().vertex2 == vertex2)
				return cur->get_value().cost;
			cur = cur->get_next();
		}
		throw invalid_argument("Incorrect argument");
	}
};