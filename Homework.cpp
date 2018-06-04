#include<iostream>
#include"RBTree.h"
#include"BinomialHeap.h"
#define GROUPS_MAX 1000

void parseAction(RBTNode*& id, BHNode** groups, char command, int& free);

int main(){
	BHNode** groups = new BHNode*[GROUPS_MAX];
	int free_spot = 0;
	RBTNode* groups_id = nullptr;
	for (int i = 0; i < GROUPS_MAX; i++)
		groups[i] = nullptr;
	int operations;
	scanf("%d\n", &operations);
	while (operations--) {
		char command;
		scanf(" %c", &command);
		parseAction(groups_id, groups, command, free_spot);
	}
    return 0;
}

void parseAction(RBTNode*& id, BHNode** groups, char command, int& free) {
	unsigned int arg1=0, arg2=0, arg3=0;
	switch (command) {
	case 'a': {
		scanf("%d %d", &arg1, &arg2);
		RBTNode* group = BSTFindNode(id, arg1);
		if (group == nullptr) {
			group = new RBTNode();
			group->index = free++;
			group->group_id = arg1;
			id = RBTInsertNode(id, group);
		}
		group = BSTFindNode(id, arg1);
		groups[group->index] = InstertBHeap(groups[group->index], arg2);
	}
		break;
	case 'e': {
		scanf("%d", &arg1);
		if (arg1 == 3 || arg1 == 6 || arg1 == 9 || arg1 == 8 || arg1== 15)
			printf("%d zle:", arg1);
		RBTNode* group = BSTFindNode(id, arg1);
		if (group == nullptr) {
			printf("na\n");
			return;
		}
		BHNode* max = nullptr;
		groups[group->index] = ExtractMax(groups[group->index], max);
		if (max != nullptr) {
			printf("%u\n", max->key);
			delete max;
		}
		else
			printf("na\n");
	}
		break;
	case 'p': {
		scanf("%d", &arg1);
		RBTNode* group = BSTFindNode(id, arg1);
		if (group != nullptr) {
			BHNode* tmp_heap = nullptr;
			while (groups[group->index] != nullptr) {
				BHNode* max = nullptr;
				groups[group->index] = ExtractMax(groups[group->index], max);
				tmp_heap = InstertBHeap(tmp_heap, max);
				printf("%u ", max->key);
			}
			groups[group->index] = tmp_heap;
			if (tmp_heap != nullptr) {
				printf("\n");
				return;
			}
		}
		printf("na\n");
	}
		break;
	case 'm': {
		scanf("%d %d", &arg1, &arg2);
		RBTNode* group1 = BSTFindNode(id, arg1);
		RBTNode* group2 = BSTFindNode(id, arg2);
		if (group1 == nullptr || group2 == nullptr) {
			printf("na\n");
			return;
		}
		groups[group1->index] = UnionBHeap(groups[group1->index], groups[group2->index]);
		groups[group2->index] = nullptr;
	}
		break;
	case 'i': {
		scanf("%d %d %d", &arg1, &arg2, &arg3);
		RBTNode* group = BSTFindNode(id, arg1);
		if (group != nullptr) {
			BHNode* node = FindBHeap(groups[group->index], arg2);
			if (node != nullptr) {
				if (arg3 < 0)
					return;
				node = IncBHEap(node, arg3);
				if(node != nullptr)
					return;
			}
		}
		printf("na\n");
	}
		break;
	}
}