#pragma once

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

#include "Heap.h"

using namespace std;

class Huffman
{
private:
	Node* root;
	vector<Node*> tab;

public:
	Huffman();
	~Huffman();

	void generate(Heap h);
	void printCode(Node* node, string s);

	bool isLeaf(Node* node);

	Node* getRoot();

	void print();
	void print(Node* node);
};

Huffman::Huffman()
{
	root = new Node();
}

Huffman::~Huffman()
{
	tab.clear();
}

void Huffman::generate(Heap h)
{
	while (!h.empty())
	{
		tab.push_back(h.getMinNode());
		h.extractMin();

		if (!h.empty())
		{
			tab.push_back(h.getMinNode());
			h.extractMin();

			h.insert(new Node('\0', tab.at(tab.size() - 2)->getValue() + tab.at(tab.size() - 1)->getValue(), tab.at(tab.size() - 2), tab.at(tab.size() - 1), NULL));
		}
	}

	root = tab.at(tab.size() - 1);
}

void Huffman::printCode(Node* node, string s)
{
	if (isLeaf(node))
		printf("%c - %s\n", node->getCharacter(), s.c_str());
	else
	{
		printCode(node->getLeftChild(), s + '0');
		printCode(node->getRightChild(), s + "1");
	}
}

bool Huffman::isLeaf(Node* node)
{
	if (node->getLeftChild() == NULL && node->getRightChild() == NULL)
		return true;
	return false;
}

Node* Huffman::getRoot()
{
	return root;
}

void Huffman::print()
{
	for (int i = 0; i < tab.size(); i++)
		if (tab.at(i)->getParent() == NULL)
			printf("%c - %d\tNO PARENT\n", tab.at(i)->getCharacter(), tab.at(i)->getValue());
		else
			printf("%c - %d\n", tab.at(i)->getCharacter(), tab.at(i)->getValue());
}

void Huffman::print(Node* node)
{
	printf("%c - %d\n", node->getCharacter(), node->getValue());

	if (!isLeaf(node))
	{
		print(node->getLeftChild());
		print(node->getRightChild());
	}
}