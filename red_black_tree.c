#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// A binary tree node
struct node{
    int value;
    bool is_black; 
    struct node * parent;
    struct node * left_child;
    struct node * right_child;
};
typedef struct node Node;


Node * create_node(int value, Node * parent, bool is_black){
	/*
	 *	Create new Node instance into pointer n. At the same
	 *	time automatically adjusts color of parent nodes.
	 */
	Node * n = (Node *)malloc(sizeof(Node));
	n->value = value;
	n->parent = parent;
	n->is_black = is_black;  // The root and NIL nodes are always black 
	n->left_child = NULL;
	n->right_child = NULL;
	return n;
}

void show_graph(Node * tree){
	printf("[+] Root node is: %d\n", tree->value);
	if(tree->parent == NULL){
		printf("[+] Root node parent is NULL\n");
	}else{
		printf("[+] Root node parent is not NULL\n");
	}

	printf("[+] Root's left child: %d\n", tree->left_child->value);
	printf("[+] Root's left child parent: %d\n", tree->left_child->parent->value);
	printf("[+] Root's right child: %d\n", tree->right_child->value);
	printf("[+] Root's right child parent: %d\n", tree->right_child->parent->value);
	printf("[+] Root's left child's right child: %d\n", tree->left_child->right_child->value);
	printf("[+] Root's left child's right child parent: %d\n", tree->left_child->right_child->parent->value);
}


void set_parents(Node * node, Node * parent){
	/* 
	 *	Recursive function which assumes children are set properly
	 */

	if(node == NULL){
		return;
	}

	node->parent = parent;
	set_parents(node->left_child, node);	
	set_parents(node->right_child, node);
}


void right_rotate(Node * parent){
	printf("[+] Performing right rotate...\n");

	if(parent == NULL){
		printf("[+] Right Rotate cannot be done on NULL\n");
		return;
	}

	if(parent->left_child == NULL){
		printf("[+] Right Rotate cannot be done on NODE with no right child\n");
		return;
	}

	if(parent->left_child->right_child == NULL){
		printf("[+] Right Rotate cannot be done on NODE with no right child's left child\n");
		return;
	}

	Node new_parent = *(parent->left_child);
	Node new_right_child = *parent;
	Node new_right_left_child = *(parent->left_child->right_child);
	
	*(new_parent.right_child) = new_right_child;
	*(new_parent.right_child->left_child) = new_right_left_child;

	*parent = new_parent;
	set_parents(parent, NULL);
}


void left_rotate(Node * parent){
	printf("[+] Performing left rotate...\n");

	if(parent == NULL){
		printf("[+] Left Rotate cannot be done on NULL\n");
		return;
	}

	if(parent->right_child == NULL){
		printf("[+] Left Rotate cannot be done on NODE with no right child\n");
		return;
	}

	if(parent->right_child->left_child == NULL){
		printf("[+] Left Rotate cannot be done on NODE with no right child's left child\n");
		return;
	}

	Node new_parent = *(parent->right_child);
	Node new_left_child = *parent;
	Node new_left_right_child = *(parent->right_child->left_child);
	
	*(new_parent.left_child) = new_left_child;
	*(new_parent.left_child->right_child) = new_left_right_child;

	*parent = new_parent;
	set_parents(parent, NULL);
}


int main(int argc, char const *argv[]){
	/*
	 *  BLUEPRINT:
	 *
	 *	       (6b)  
	 *       /      \
	 *	  (3r)      (9b)
	 *   /    \    /    \
	 * (2b) (5b)  (7b) (10b)
	 */
	// TREE CONSTRUCTION
	Node * tree = create_node(6, NULL, true);  // Root must be always black
	
	tree->left_child = create_node(3, tree, false);  // Root's left child is red
	tree->right_child = create_node(9, tree, true);  // Root's left child is black

	// The rest nodes are NIL nodes. Always must be black.
	tree->left_child->left_child = create_node(2, tree->left_child, true);
	tree->left_child->right_child = create_node(5, tree->left_child, true);

	tree->right_child->left_child = create_node(7, tree->right_child, true);
	tree->right_child->right_child = create_node(10, tree->right_child, true);

	// Rotations
	left_rotate(tree);
	/*
	 *  AFTER LEFT ROTATION:
	 *
	 *	         (9b)  
	 *		    /    \
	 *		  (6b)	(10b)
	 *       /    \
	 *	  (3r)    (7b)
	 *   /    \    
	 * (2b) (5b)
	 */
	show_graph(tree);

	// Rotations
	right_rotate(tree);
	/*
	 *  AFTER LEFT ROTATION:
	 *
	 *	         (6b)  
	 *		    /    \
	 *		  (3r)	  (9b)
	 *       /   \    /  \
	 *	  (2b)  (5b)(7b) (10b) 
	 */
	show_graph(tree);
	return 0;
}


