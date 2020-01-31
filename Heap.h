#pragma once

#include <iostream>
#include <stdio.h>
#include <vector>
#include <utility>
#include <stdexcept>

using namespace std;

class Node
{
private:
	int v;
	char c;
	Node* parent;
	Node* leftChild;
	Node* rightChild;

public:
	Node(char c = '\0', int value = 0, Node* leftChild = NULL, Node* rightChild = NULL, Node* parent = NULL)
	{
		this->c = c;
		this->v = value;
		this->parent = parent;
		this->leftChild = leftChild;
		this->rightChild = rightChild;
	}

	char getCharacter() { return c; }
	int getValue() { return v; }
	Node* getLeftChild() { return leftChild; }
	Node* getRightChild() { return rightChild; }
	Node* getParent() { return parent; }

	void Update(char c, int value, Node* leftChild, Node* rightChild, Node* parent)
	{
		this->c = c;
		this->v = value;
		this->parent = parent;
		this->leftChild = leftChild;
		this->rightChild = rightChild;
	}
};

class Heap
{
private:
	vector<Node*> heap;

public:
	Heap();
	~Heap();

	void insert(int value, char c);
	void insert(Node* node);

	int getMin();
	char getMinChar();
	Node* getMinNode();

	void extractMin();
	void update(int index);

	void print();
	bool empty();
};

Heap::Heap() {}

Heap::~Heap()
{
	heap.clear();
}

void Heap::insert(int value, char c = '\0')
{
	heap.push_back(new Node(c, value));
	update(heap.size() - 1);
}

void Heap::insert(Node* node)
{
	heap.push_back(node);
	update(heap.size() - 1);
}

int Heap::getMin()
{
	if (!heap.empty())
		return heap.at(0)->getValue();
	throw out_of_range("Heap is empty\n");
}

char Heap::getMinChar()
{
	if (!heap.empty())
		return heap.at(0)->getCharacter();
	throw out_of_range("Heap is empty\n");
}

Node* Heap::getMinNode()
{
	if (!heap.empty())
		return heap.at(0);
}

void Heap::extractMin()
{
	if (heap.size() == 0)
		return;

	heap.at(0) = heap.at(heap.size() - 1);
	heap.pop_back();

	if (heap.size() > 0)
		update(0);
}

void Heap::update(int index)
{
	if (index < heap.size() && index >= 0)
	{
		bool l = false, r = false;

		if (index * 2 + 1 < heap.size())
			if (heap.at(index)->getValue() > heap.at(index * 2 + 1)->getValue())
				l = true;

		if (index * 2 + 2 < heap.size())
			if (heap.at(index)->getValue() > heap.at(index * 2 + 2)->getValue())
				r = true;

		if (l && r)
		{
			if (heap.at(index * 2 + 1)->getValue() < heap.at(index * 2 + 2)->getValue())
			{
				swap(heap.at(index), heap.at(index * 2 + 1));
				update(index * 2 + 1);
			}
			else
			{
				swap(heap.at(index), heap.at(index * 2 + 2));
				update(index * 2 + 2);
			}
		}
		else if (l)
		{
			swap(heap.at(index), heap.at(index * 2 + 1));
			update(index * 2 + 1);
		}
		else if (r)
		{
			swap(heap.at(index), heap.at(index * 2 + 2));
			update(index * 2 + 2);
		}

		if ((index - 1) / 2 >= 0 && index != 0)
		{
			if (heap.at(index)->getValue() < heap.at((index - 1) / 2)->getValue())
			{
				swap(heap.at(index), heap.at((index - 1) / 2));
				update((index - 1) / 2);
			}
		}
	}
	else
		printf("Index: index - Out of Range\n");
}

void Heap::print()
{
	for (int i = 0; i < heap.size(); i++)
		printf("%d: %c - %d\n", i, heap.at(i)->getCharacter(), heap.at(i)->getValue());
}

bool Heap::empty()
{
	return heap.empty();
}