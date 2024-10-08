#include <stdio.h>
#include <stdlib.h>

struct node{
	int num;
	char color;
	struct node *parent;
	struct node *left;
	struct node *right;
}*root = NULL;

node *createNewNode(int num){
	node *newNode = (node*)malloc(sizeof(node));
	newNode->num = num;
	newNode->color = 'r';
	newNode->parent= NULL;
	newNode->left = NULL;
	newNode->right = NULL;
}

void leftRotate(node *curr){
	node *newParent = curr->right;
	curr->right = newParent->left;
	
	if(curr->right){
		curr->right->parent = curr;
	}
	
	newParent->parent = curr->parent;
	
	if(!curr->parent){
		root = newParent;
	}
	else if(curr == curr->parent->left){
		curr->parent->left = newParent;
	}
	else{
		curr->parent->right = newParent;
	}
	
	newParent->left = curr;
	curr->parent = newParent;
}

void rightRotate(node *curr){
	node *newParent = curr->left;
	curr->left = newParent->right;
	
	if(curr->left){
		curr->left->parent = curr;
	}
	
	newParent->parent = curr->parent;
	
	if(!curr->parent){
		root = newParent;
	}
	else if(curr == curr->parent->left){
		curr->parent->left = newParent;
	}
	else{
		curr->parent->right = newParent;
	}
	
	newParent->right = curr;
	curr->parent = newParent;
}

node *insert(node *curr, node *newNode){
	if(curr == NULL){
		return newNode;
	}
	else if(newNode->num < curr->num){
		curr->left = insert(curr->left, newNode);
		curr->left->parent = curr;
	}
	else if(newNode->num > curr->num){
		curr->right = insert(curr->right, newNode);
		curr->right->parent = curr;
	}
	
	return curr;
}

void fix(node *curr, node *newNode){
	while(newNode != curr && newNode->color != 'b' && newNode->parent->color == 'r'){
		node *newNodeParent = newNode->parent;
		node *grandParent = newNode->parent->parent;
		
		if(newNodeParent == grandParent->left){
			node *uncle = grandParent->right;
			
			if(uncle != NULL && uncle->color == 'r'){
				grandParent->color = 'r';
				newNodeParent->color = 'b';
				uncle->color = 'b';
				newNode = grandParent;
			}
			else{
				if(newNode == newNodeParent->right){
					leftRotate(newNodeParent);
					newNode = newNode->parent;
					newNodeParent = newNode->parent;
				}
				
				rightRotate(grandParent);
				char temp = newNodeParent->color;
				newNodeParent->color = grandParent->color;
				grandParent->color = temp;
				newNode = newNodeParent;
			}
		}
		else{
			node *uncle = grandParent->left;
			
			if(uncle != NULL && uncle->color == 'r'){
				grandParent->color = 'r';
				newNodeParent->color = 'b';
				uncle->color = 'b';
				newNode = grandParent;
			}
			else{
				if(newNode == newNodeParent->left){
					rightRotate(newNodeParent);
					newNode = newNodeParent;
					newNodeParent = newNode->parent;
				}
				
				leftRotate(grandParent);
				char temp = newNodeParent->color;
				newNodeParent->color = grandParent->color;
				grandParent->color = temp;
				newNode = newNodeParent;
			}
		}
	}
}

void inOrder(node *curr){
	if(curr){
		inOrder(curr->left);
		printf("%d ", curr->num);
		inOrder(curr->right);
	}
}

int main(){
	int num[11] = {41,22,5,51,48,29,18,21,45,3};
	
	for(int i = 0; i < 10; i++){
		node *newNode = createNewNode(num[i]);
		root = insert(root, newNode);
		fix(root, newNode);
		root->color = 'b';
	}
	
	printf("Inorder Traversal of Created Tree\n");
    inOrder(root);
    
	return 0;
}
