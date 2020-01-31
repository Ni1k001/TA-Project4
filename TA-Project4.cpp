#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>

#include "Heap.h"
#include"Huffman.h"

using namespace std;

int main()
{
	string path = "text.txt";
	ifstream file;

	string text;

	file.open(path, ios::in);

	if (file.is_open())
	{
		while (!file.eof())
		{
			string tmp;

			getline(file, tmp);

			text.append(tmp);
		}
	}
	file.close();

	int tab[52];
	for (int i = 0; i < 52; i++)
		tab[i] = 0;

	for (int i = 0; i < text.size(); i++)
	{
		if (text[i] >= 'a' && text[i] <= 'z')
			tab[text[i] - 'a']++;
		else if (text[i] >= 'A' && text[i] <= 'Z')
			tab[text[i] - 'A' + 26]++;
	}

	Heap heap;

	heap.insert(1);
	heap.insert(7);
	heap.insert(5);
	heap.insert(10);

	heap.print();
	heap.getMin();
	
	printf("\n\n");
	heap.extractMin();
	heap.print();
	heap.getMin();

	printf("\n\n");
	
	Heap heap2;
	Huffman huffman;

	for (int i = 0; i < 52; i++)
	{
		if (i < 26)
			heap2.insert(tab[i], i + 'a');
		else
			heap2.insert(tab[i], i - 26 + 'A');
	}

	while (heap2.getMin() == 0)
	{
		heap2.extractMin();
	}

	heap2.print();

	printf("\n\n");
	huffman.generate(heap2);
	huffman.printCode(huffman.getRoot(), "");
	//huffman.print();
	//printf("\n\n");
	//huffman.print(huffman.getRoot());
}