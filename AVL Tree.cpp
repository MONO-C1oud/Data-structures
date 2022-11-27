#include <iostream>
using namespace std;
class node {
public:
	int data;
	node* left;
	node* right;
	int height;
};
	
node* minnode(node* root) {
	if (root->left == NULL)
		return root;
	else
		return minnode(root->left);
}

int treeheight(node* root) {
	if (root == NULL)
		return 0;
	else
		return root->height;
}

node* rleft(node* root) {
	node* y = root->right;
	node* temp = y->left;
	y->left = root;
	root->right = temp;
	root = y;
	return root;
}

node* rright(node* root) {
	node* y = root->left;
	node* temp = y->right;
	y->right = root;
	root->left = temp;
	root = y;
	return root;
}

node* deletenode(node* root, int x) {
	if (root == NULL)
		return root;
	else if (x > root->data)
		root->right = deletenode(root->right, x);
	else if (x < root->data)
		root->left = deletenode(root->left, x);
	else if (x == root->data) {
		if (root->right == NULL) {
			node* temp = root->left;
			delete root;
			root = temp;
		}
		else if (root->left == NULL) {
			node* temp = root->right;
			delete root;
			root = temp;
		}
		else if (root->right != NULL && root->left != NULL) {
			node* temp = root;
			root = minnode(root->right);
			temp->data = root->data;
			delete root;
			root = temp;
		}
	}
	int maxheight;
	if (treeheight(root->left) > treeheight(root->right))
		maxheight = treeheight(root->left);
	else
		maxheight = treeheight(root->right);
	root->height = 1 + maxheight;

	int balancefactor = treeheight(root->left) - treeheight(root->right);

	//LL case
	if (balancefactor > 1 && treeheight(root->left->left) > treeheight(root->left->right)) {
		root = rright(root);
	}
	//LR case
	else if (balancefactor > 1 && treeheight(root->left->left) < treeheight(root->left->right)) {
		root->left = rleft(root->left);
		root = rright(root);
	}
	//RL case
	else if (balancefactor < -1 && treeheight(root->right->left) > treeheight(root->right->right)) {
		root->right = rright(root->right);
		root = rleft(root);
	}
	//RR case
	else if (balancefactor < -1 && treeheight(root->right->left) < treeheight(root->right->right)) {
		root = rleft(root);;
	}

	return root;
}

node* newnode(int x) {
	node* n1 = new node;
	n1->left = NULL;
	n1->right = NULL;
	n1->data = x;
	n1->height = 1;
	return n1;
}


node* insertkey(node* root, int x) {
	if (root == NULL) {
		root = newnode(x);
	}
	else if (x < root->data) {
		root->left = insertkey(root->left, x);
	}
	else if (x > root->data) {
		root->right = insertkey(root->right, x);
	}

	int maxheight;
	if (treeheight(root->left) > treeheight(root->right))
		maxheight = treeheight(root->left);
	else
		maxheight = treeheight(root->right);
	root->height = 1 + maxheight;

	int balancefactor = treeheight(root->left) - treeheight(root->right);

	//LL case
	if (balancefactor > 1 && treeheight(root->left->left) > treeheight(root->left->right)) {
		root = rright(root);
	}
	//LR case
	else if (balancefactor > 1 && treeheight(root->left->left) < treeheight(root->left->right)) {
		root->left = rleft(root->left);
		root = rright(root);
	}
	//RL case
	else if (balancefactor < -1 && treeheight(root->right->left) > treeheight(root->right->right)) {
		root->right = rright(root->right);
		root = rleft(root);
	}
	//RR case
	else if (balancefactor < -1 && treeheight(root->right->left) < treeheight(root->right->right)) {
		root = rleft(root);;
	}

	return root;
}

node* insert(node* root, int x) {
	if (root == NULL) {
		node* leaf = new node;
		leaf->left = NULL;
		leaf->right = NULL;
		leaf->data = x;
		return leaf;
	}
	else
		root = insertkey(root, x);
	return root;
}
void inorder(node* leaf) {
	if (leaf != NULL) {
		inorder(leaf->left);
		cout << "data: " << leaf->data << " , height: " << treeheight(leaf) << endl;
		inorder(leaf->right);
	}
}


int main() {
	node* root = NULL;
	root = insert(root, 5);
	root = insert(root, 1);
	root = insert(root, 3);
	root = insert(root, 6);
	root = insert(root, 2);
	root = insert(root, 7);
	root = insert(root, 4);
	root = deletenode(root, 6);
	root = deletenode(root, 5);
	inorder(root);
}