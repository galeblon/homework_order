#include"BinomialHeap.h"

BHNode* InstertBHeap(BHNode* heap, unsigned int key) {
	BHNode* node = new BHNode();
	node->key = key;
	return UnionBHeap(heap, node);
}

BHNode* InstertBHeap(BHNode* heap, BHNode* node) {
	return UnionBHeap(heap, node);
}

void LinkBTree(BHNode* newSon, BHNode* newParent) {
	newSon->parent = newParent;
	newSon->sibling = newParent->child;
	newParent->child = newSon;
	newParent->degree++;
}

BHNode* MergeBHeap(BHNode* h1, BHNode* h2) {
	BHNode* ret = nullptr;
	BHNode* current = nullptr;
	BHNode* next = nullptr;
	while (h1 != nullptr && h2 != nullptr) {
		if (h1->degree <= h2->degree) {
			next = h1;
			h1 = h1->sibling;
		}
		else {
			next = h2;
			h2 = h2->sibling;
		}
		if (ret == nullptr) {
			ret = next;
			current = next;
		}
		else {
			current->sibling = next;
			current = next;
		}
	}
	if (h1 == nullptr) {
		BHNode* tmp = h1;
		h1 = h2;
		h2 = tmp;
	}
	if (ret == nullptr)
		return h1;
	else
		current->sibling = h1;
	return ret;
}

BHNode* UnionBHeap(BHNode* y, BHNode* z) {
	BHNode* ret = MergeBHeap(y, z);
	if (ret == nullptr)
		return nullptr;
	BHNode* prevX = nullptr;
	BHNode* X = ret;
	BHNode* nextX = ret->sibling;
	while (nextX != nullptr) {
		if (X->degree != nextX->degree || (nextX->sibling != nullptr && nextX->degree == nextX->sibling->degree)) {
			prevX = X;
			X = nextX;
			nextX = X->sibling;
		}
		else if (X->key >= nextX->key) {
			X->sibling = nextX->sibling;
			nextX->sibling = nullptr;
			LinkBTree(nextX, X);
			nextX = X->sibling;
		}
		else {
			if (prevX == nullptr)
				ret = nextX;
			else
				prevX->sibling = nextX;
			X->sibling = nullptr;
			LinkBTree(X, nextX);
			X = nextX;
			nextX = X->sibling;
		}
	}
	return ret;
}

BHNode* ExtractMax(BHNode* heap, BHNode*& max) {
	BHNode* ret = MaxBHeap(heap);
	if (ret == nullptr)
		return nullptr;
	BHNode* prev = nullptr;
	BHNode* todel = heap;
	while (todel != ret) {
		prev = todel;
		todel = todel->sibling;
	}
	if (prev != nullptr) {
		prev->sibling = todel->sibling;
	}
	else
		heap = todel->sibling;
	prev = nullptr;
	BHNode* curr = ret->child;
	BHNode* next = nullptr;
	while (curr != nullptr) {
		curr->parent = nullptr;
		next = curr->sibling;
		curr->sibling = prev;
		prev = curr;
		curr = next;
	}
	BHNode* h1 = prev;
	heap = UnionBHeap(heap, h1);
	ret->sibling = nullptr;
	ret->child = nullptr;
	max = ret;
	return heap;
}

BHNode* MaxBHeap(BHNode* heap) {
	BHNode* max = heap;
	while(heap != nullptr){
		if (heap->key > max->key)
			max = heap;
		heap = heap->sibling;
	}
	return max;
}

BHNode* IncBHEap(BHNode* node, unsigned int newKey) {
	if (newKey < node->key)
		return nullptr;
	node->key = newKey;
	while (node->parent != nullptr && node->key > node->parent->key) {
		unsigned int tmp = node->key;
		node->key = node->parent->key;
		node->parent->key = tmp;
		node = node->parent;
	}
	return node;
}

BHNode* FindBHeap(BHNode* heap, unsigned int key) {
	BHNode* ret = nullptr;
	while (heap != nullptr) {
		if (key > heap->key) {
			heap = heap->sibling;
		}
		else {
			if (key == heap->key) {
				return heap;
			}
			ret = FindBHeap(heap->child, key);
			if (ret != nullptr) {
				return ret;
			}
			else {
				heap = heap->sibling;
			}
		}
	}
	return ret;
}