#pragma once
//Pomysl na drzewo Czerwono-Czarne zaczerpniete z wykladu nr.7 dr in¿. Krzysztofa Manuszewskiego "kopce zlaczalne."

struct BHNode {
	unsigned int key;
	unsigned int degree;
	BHNode *child, *sibling, *parent, *root;

	BHNode(): key(0), degree(0), child(nullptr), sibling(nullptr), parent(nullptr), root(nullptr) {}
};

BHNode* UnionBHeap(BHNode* heap, BHNode* node);
BHNode* InstertBHeap(BHNode* heap, unsigned int key);
BHNode* InstertBHeap(BHNode* heap, BHNode* node);
void LinkBTree(BHNode* newSon, BHNode* newParent);
BHNode* MergeBHeap(BHNode* h1, BHNode* h2);
BHNode* UnionBHeap(BHNode* y, BHNode* z);
BHNode* ExtractMax(BHNode* heap, BHNode*& max);
BHNode* MaxBHeap(BHNode* heap);
BHNode* IncBHEap(BHNode* node, unsigned int newKey);
BHNode* FindBHeap(BHNode* heap, unsigned int key);