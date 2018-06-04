#pragma once
//Pomysl na drzewo Czerwono-Czarne zaczerpniete z wykladu nr.6 dr inż. Krzysztofa Manuszewskiego "rownowazenie drzew."
// Jak rowniez z Wprowadzenia do algorytmow Thomasa Cormena, rozdzial 14
struct RBTNode;
extern RBTNode* Nil;


enum COLORS {
	BLACK,
	RED
};

struct RBTNode {
	unsigned int group_id, index;
	COLORS color;
	RBTNode *left;
	RBTNode *right;
	RBTNode *parent;
	RBTNode *duplicates;


	RBTNode() : color(BLACK), left(Nil), right(Nil), parent(nullptr), duplicates(nullptr) {}
	RBTNode(int) :color(BLACK), left(nullptr), right(nullptr), parent(nullptr) {}
	~RBTNode() {
	}
};

RBTNode*& RightRotate(RBTNode*& tree_root, RBTNode* y);
RBTNode*& LeftRotate(RBTNode*& tree_root, RBTNode* x);

RBTNode*& BSTInsertNode(RBTNode*& tree_root, RBTNode*& node);
RBTNode*& RBTInsertNode(RBTNode*& tree_root, RBTNode*& x);

RBTNode*& BSTDeleteNode(RBTNode*& tree_root, RBTNode*& node);
RBTNode* RBTDeleteNode(RBTNode*& tree_root, RBTNode*& x);

RBTNode* BSTMaximum(RBTNode* node);
RBTNode* BSTMinimum(RBTNode* node);
RBTNode* BSTSuccesor(RBTNode* node);
RBTNode* BSTFindNode(RBTNode* node, unsigned int value);

COLORS GetColor(RBTNode* node);
void ToggleColor(RBTNode* node);