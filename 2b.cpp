#include<stdio.h>
#include<stdlib.h>

struct node{
	int num;
	struct node *left;
	struct node *right;
	int height;
};

int height(struct node *curr){
	if(curr == NULL){
		return 0;
	}
	else{
		return curr->height;
	}
}

int max(int a, int b){
	return (a > b)? a : b;
}

node *createNewNode(int num){
	node *newNode = (node*)malloc(sizeof(node));
	newNode->num = num;
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->height = 1;
	
	return newNode;
}

node *leftRotate(node *curr){
	node *parent = curr->right;
	node *subtree = parent->left;
	
	parent->left = curr;
	curr->right = subtree;
	
	curr->height =  max(height(curr->left), height(curr->right)) + 1;
	parent->height = max(height(parent->left), height(parent->right)) + 1;
	
	return parent;
}

node *rightRotate(node *curr){
	node *parent = curr->left;
	node *subtree = parent->right;
	
	parent->right = curr;
	curr->left = subtree;
	
	curr->height =  max(height(curr->left), height(curr->right)) + 1;
	parent->height = max(height(parent->left), height(parent->right)) + 1;
	
	return parent;
}


int getBalance(node *curr){
	if(curr == NULL){
		return 0;
	}
	else{
		return height(curr->left) - height(curr->right);
	}
}

node *insert(node *curr, int num){
	if(curr == NULL){
		return createNewNode(num);
	}
	else if(num < curr->num){
		curr->left = insert(curr->left, num);
	}
	else if(num > curr->num){
		curr->right = insert(curr->right, num);
	}
	else{
		return curr;
	}
	
	curr->height = max(height(curr->left), height(curr->right)) + 1;
	
	int balance = getBalance(curr);
	
	if(balance > 1 && num < curr->left->num){
		return rightRotate(curr);
	}
	else if(balance > 1 && num > curr->left->num){
		curr->left = leftRotate(curr->left);
		return rightRotate(curr);
	}
	else if(balance < -1 && num > curr->right->num){
		return leftRotate(curr);
	}
	else if(balance < -1 && num < curr->right->num){
		curr->right = rightRotate(curr->right);
		return leftRotate(curr);
	}
	return curr;
}

node *getPred(node *root){
	node *curr = root->left;
	while(curr->right){
		curr = curr->right;
	}
	
	return curr;
}

node *del(node *curr, int num, int printed){
	if(curr == NULL){
		printf("Data not found\n");
		return NULL;
	}
	else if(num < curr->num){
		curr->left = del(curr->left, num, printed);
	}
	else if(num > curr->num){
		curr->right = del(curr->right, num, printed);
	}
	else if(num == curr->num){
		if(printed == 0){
			printf("Value %d was deleted\n", curr->num);
			printed = 1;
		}
		if(curr->left == NULL || curr->right == NULL){
			node *temp = NULL;
			if(curr->left){
				temp = curr->left;
			}
			else if(curr->right){
				temp = curr->right;
			}
			
			free(curr);
			curr = temp;
			
			if(curr == NULL){
				return NULL;
			}
		}
		else{
			node *pred = getPred(curr);
			curr->num = pred->num;
			curr->left = del(curr->left, curr->num, printed);
		}
	}
	
	curr->height = max(height(curr->left), height(curr->right)) + 1;
	
	int balance = getBalance(curr);
	
	if(balance > 1 && getBalance(curr->left) >= 0){
		return rightRotate(curr);
	}
	else if(balance > 1 && getBalance(curr->left) < 0){
		curr->left = leftRotate(curr->left);
		return rightRotate(curr);
	}
	else if(balance < -1 && getBalance(curr->right) <= 0){
		return leftRotate(curr);
	}
	else if(balance < -1 && getBalance(curr->right) > 0){
		curr->right = rightRotate(curr->right);
		return leftRotate(curr);
	}
	return curr;
}

void preOrder(node *curr){
	if(curr){
		printf(" %d", curr->num);
		preOrder(curr->left);
		preOrder(curr->right);
	}
}

void inOrder(node *curr){
	if(curr){
		inOrder(curr->left);
		printf(" %d", curr->num);
		inOrder(curr->right);
	}
}

void postOrder(node *curr){
	if(curr){
		postOrder(curr->left);
		postOrder(curr->right);
		printf(" %d", curr->num);
	}
}

int main(){
	int choice = 0;
	node *root = NULL;
	int num;
	
	do{
		printf("1. Insertion\n");
		printf("2. Deletion\n");
		printf("3. Traversal\n");
		printf("4. Exit\n");
		printf("Choose: ");
		scanf("%d", &choice);
		
		if(choice == 1){
			printf("Insert: ");
			scanf("%d", &num);
			root = insert(root, num);
		}
		else if(choice == 2){
			printf("Delete: ");
			scanf("%d", &num);
			root = del(root, num, 0);
		}
		else if(choice == 3){
			printf("Preorder:");
			preOrder(root);
			printf("\n");
			printf("Inorder:");
			inOrder(root);
			printf("\n");
			printf("Postorder:");
			postOrder(root);
			printf("\n");
		}
		
	}while(choice != 4);
	
	printf("Thank you\n");
}
