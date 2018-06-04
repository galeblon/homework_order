#include"RBTree.h"

RBTNode* Nil = new RBTNode(1);

RBTNode*& RightRotate(RBTNode*& tree_root, RBTNode* y) {
	if (y == Nil || y == nullptr)
		return tree_root;
	RBTNode* x = y->left;
	if (x == Nil)
		return tree_root;
	y->left = x->right;
	if (x->right != Nil)
		x->right->parent = y;
	x->parent = y->parent;
	if (y->parent == nullptr)
		tree_root = x;
	else if (y == y->parent->left)
		y->parent->left = x;
	else
		y->parent->right = x;
	x->right = y;
	y->parent = x;
	return tree_root;
}

RBTNode*& LeftRotate(RBTNode*& tree_root, RBTNode* x) {
	if (x == Nil || x == nullptr)
		return tree_root;
	RBTNode* y = x->right;
	if (y == Nil)
		return tree_root;
	x->right = y->left;
	if (y->left != Nil)
		y->left->parent = x;
	y->parent = x->parent;
	if (x->parent == nullptr)
		tree_root = y;
	else if (x == x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;
	y->left = x;
	x->parent = y;
	return tree_root;
}

RBTNode*& BSTInsertNode(RBTNode*& tree_root, RBTNode*& node) {
	if (node == nullptr || node == Nil)
		return tree_root;
	if (tree_root == nullptr || tree_root == Nil) {
		node->parent = nullptr;
		node->left = Nil;
		node->right = Nil;
		return node;
	}
	RBTNode* tmp = tree_root;
	RBTNode* parent = nullptr;
	while (tmp != Nil && tmp != nullptr) {
		if (tmp == nullptr || node == nullptr)
			return tree_root;
		parent = tmp;
		if (node->group_id < tmp->group_id)
			tmp = tmp->left;
		else
			tmp = tmp->right;
	}
	node->parent = parent;
	if (node->group_id < parent->group_id)
		parent->left = node;
	else if(node->group_id == parent->group_id)
		parent->left = node;
	else
		parent->right = node;
	return tree_root;
}


RBTNode*& RBTInsertNode(RBTNode*& tree_root, RBTNode*& x) {
	tree_root = BSTInsertNode(tree_root, x);
	x->color = RED;
	while (x != tree_root && x->parent->color == RED) {
		if (x->parent == nullptr || x->parent->parent == nullptr)
			return tree_root;
		if (x->parent == x->parent->parent->left) {
			//Ojciec po lewej
			RBTNode* uncle = x->parent->parent->right;
			if (GetColor(uncle) == RED) {
				x->parent->color = BLACK;
				uncle->color = BLACK;
				x->parent->parent->color = RED;
				x = x->parent->parent;
			}
			else {
				if (x == x->parent->right) {
					x = x->parent;
					tree_root = LeftRotate(tree_root, x);
				}
				x->parent->color = BLACK;
				x->parent->parent->color = RED;
				tree_root = RightRotate(tree_root, x->parent->parent);
			}
		}
		else {
			//Ojciec po prawej
			RBTNode* uncle = x->parent->parent->left;
			if (GetColor(uncle) == RED) {
				x->parent->color = BLACK;
				uncle->color = BLACK;
				x->parent->parent->color = RED;
				x = x->parent->parent;
			}
			else {
				if (x == x->parent->left) {
					x = x->parent;
					tree_root = RightRotate(tree_root, x);
				}
				x->parent->color = BLACK;
				x->parent->parent->color = RED;
				tree_root = LeftRotate(tree_root, x->parent->parent);
			}
		}
		tree_root->color = BLACK;
	}
	tree_root->color = BLACK;
	return tree_root;
}

COLORS GetColor(RBTNode* node) {
	if (node == Nil || node == nullptr)
		return BLACK;
	return node->color;
}

void ToggleColor(RBTNode* node) {
	if(node != Nil){
		if (node->color == BLACK)
			node->color = RED;
		else
			node->color = BLACK;
	}
}

RBTNode*& BSTDeleteNode(RBTNode*& tree_root, RBTNode*& node) {
	RBTNode* todel;
	if (node->left == Nil || node->right == Nil)
		todel = node;
	else
		todel = BSTSuccesor(node);
	RBTNode* son;
	if (todel->left != Nil)
		son = todel->left;
	else
		son = todel->right;
	if (son != Nil)
		son->parent = todel->parent;
	if (todel->parent == nullptr)
		tree_root = son;
	else if (todel == todel->parent->left)
		todel->parent->left = son;
	else
		todel->parent->right = son;
	if (todel != node) {
		node->group_id = todel->group_id;
		node->index = todel->index;
		//delete todel;
	}
	return tree_root;
}

RBTNode*& RBTDelFixUp(RBTNode*& tree_root, RBTNode* x) {
	if (tree_root == Nil) {
		tree_root = nullptr;
		return tree_root;
	}
	while (x != tree_root && GetColor(x) == BLACK) {
		if (x == x->parent->left) {
			RBTNode* w = x->parent->right;
			if (GetColor(w) == RED) {
				w->color = BLACK;
				x->parent->color = RED;
				LeftRotate(tree_root, x->parent);
				w = x->parent->right;
			}
			if (GetColor(w->left) == BLACK && GetColor(w->right) == BLACK) {
				w->color = RED;
				x = x->parent;
			}
			else if (GetColor(w->right) == BLACK) {
				w->left->color = RED;
				RightRotate(tree_root, w);
				w = x->parent->right;
			}
			if(w != nullptr)
				w->color = GetColor(x->parent);
			if(x->parent != nullptr)
				x->parent->color = BLACK;
			if(w != nullptr && w->right != nullptr)
				w->right->color = BLACK;
			LeftRotate(tree_root, x->parent);
			x = tree_root;
		}
		else {
			RBTNode* w = x->parent->left;
			if (GetColor(w) == RED) {
				w->color = BLACK;
				x->parent->color = RED;
				RightRotate(tree_root, x->parent);
				w = x->parent->left;
			}
			if (GetColor(w->right) == BLACK && GetColor(w->left) == BLACK) {
				w->color = RED;
				x = x->parent;
			}
			else if (GetColor(w->left) == BLACK) {
				w->right->color = RED;
				LeftRotate(tree_root, w);
				w = x->parent->left;
			}
			w->color = GetColor(x->parent);
			if(x->parent != nullptr)
				x->parent->color = BLACK;
			if(w->left != nullptr)
				w->left->color = BLACK;
			RightRotate(tree_root, x->parent);
			x = tree_root;
		}
		x->color = BLACK;
	}
	return tree_root;
}

RBTNode* RBTDeleteNode(RBTNode*& tree_root, RBTNode*& x) {
	RBTNode* y, *x_node;
	if (x == nullptr)
		return tree_root;
	if (x->left == Nil || x->right == Nil) {
		y = x;
	}
	else
		y = BSTSuccesor(x);
	if (y->left != Nil) {
		x_node = y->left;
	}
	else
		x_node = y->right;
	x_node->parent = y->parent;
	if (y->parent == nullptr) {
		tree_root = x_node;
	}
	else if (y == y->parent->left)
		y->parent->left = x_node;
	else
		y->parent->right = x_node;
	if (y != x) {
		x->group_id = y->group_id;
		x->index = y->index;
	}
	if (GetColor(y) == BLACK) {
		RBTDelFixUp(tree_root, x_node);
	}
	return y;
}

RBTNode* BSTSuccesor(RBTNode* node) {
	if (node->right != Nil)
		return BSTMinimum(node->right);
	RBTNode* tmp = node->parent;
	while (tmp != nullptr && node == tmp->right) {
		node = tmp;
		tmp = tmp->parent;
	}
	return tmp;
}

RBTNode* BSTMinimum(RBTNode* node) {
	while (node->left != Nil) {
		node = node->left;
	}
	return node;
}

RBTNode* BSTMaximum(RBTNode* node) {
	while (node->right != Nil) {
		node = node->right;
	}
	return node;
}

RBTNode* BSTFindNode(RBTNode* node, unsigned int value) {
	while (node != Nil && node != nullptr) {
		if (node->group_id < value)
			node = node->right;
		else if (node->group_id > value)
			node = node->left;
		else if (node->group_id == value)
			return node;
	}
	return nullptr;
}