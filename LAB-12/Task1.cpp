#include <iostream>
using namespace std;
#include "Node.h"
#include "BinaryTree.h"
#include "BinarySearchTree.h"

bool isBST(Node<int>* Parent, Node<int>* leftChild, Node<int>* rightChild) {
	return (leftChild->data < rightChild->data);
}

bool isBST(Node<int>* Parent, Node<int>* leftChild, Node<int>* rightChild, Node<int>* leftChildLeft,
	Node<int>* leftChildRight, Node<int>* rightChildLeft, Node<int>* rightChildRight) {
	return isBST(Parent, leftChild, rightChild) && isBST(leftChild, leftChildLeft, leftChildRight) &&
		isBST(rightChild, rightChildLeft, rightChildRight);
}

template <class T>
bool isFound(T value, Node<T>* Parent, Node<T>* leftChild, Node<T>* rightChild) {
	return (value == Parent->data || leftChild->data == value || rightChild->data == value);
}

template <class T>
bool isFound(T valueToFind, Node<int>* Parent, Node<int>* leftChild, Node<int>* rightChild, 
	Node<int>* leftChildLeft, Node<int>* leftChildRight, Node<int>* rightChildLeft, Node<int>* rightChildRight){
	return isFound(valueToFind, Parent, leftChild, rightChild)
		&& isFound(valueToFind, leftChild, leftChildLeft, leftChildRight)
		&& isFound(valueToFind, rightChild, rightChildLeft, rightChildRight);
}

template <class T>
void  insertValue(T valueToInsert, Node<int>* parent, Node<int>* leftChild, Node<int>* rightChild) {

	if (valueToInsert < parent->data)
	{
		if (leftChild == nullptr)
			parent->left = new Node<int>(valueToInsert);
		else if (valueToInsert < leftChild->data)
			leftChild->left = new Node<int>(valueToInsert);
		else
			leftChild->right = new Node<int>(valueToInsert);
	}
	else
	{
		if (rightChild == nullptr)
			parent->right = new Node<int>(valueToInsert);
		else if (valueToInsert < rightChild->data)
			rightChild->left = new Node<int>(valueToInsert);
		else
			rightChild->right = new Node<int>(valueToInsert);
	}

}

template <class T>
void  insertValue(T valueToFind, Node<T>* Parent, Node<T>* leftChild, Node<T>* rightChild,
	Node<T>* leftChildLeft, Node<T>* leftChildRight, Node<T>* rightChildLeft, Node<T>* rightChildRight){
	if (valueToFind < Parent->data)
	{
		if (leftChild == nullptr){
			Parent->left = new Node<T>(valueToFind);
		}
		else if (valueToFind < leftChild->data){
			if (leftChildLeft == nullptr)
				leftChild->left = new Node<T>(valueToFind);
		}
		else{
			if (leftChildRight == nullptr)
				leftChild->right = new Node<T>(valueToFind);
		}
	}
	else{
		if (rightChild == nullptr){
			Parent->right = new Node<T>(valueToFind);
		}
		else if (valueToFind < rightChild->data){
			if (rightChildLeft == nullptr)
				rightChild->left = new Node<T>(valueToFind);
		}
		else{
			if (rightChildRight == nullptr)
				rightChild->right = new Node<T>(valueToFind);
		}
	}
}
	
template <class T>
void deleteValue(T valueToFind, Node<T>* Parent, Node<T>* leftChild, Node<T>* rightChild){
	if (Parent == nullptr) return;

	if (Parent->data == valueToFind){
		delete Parent;
		return;
	}
	if (leftChild != nullptr && leftChild->data == valueToFind){
		delete Parent->left;
		Parent->left = nullptr;
		return;
	}

	if (rightChild != nullptr && rightChild->data == valueToFind){
		delete Parent->right;
		Parent->right = nullptr;
		return;
	}
}

template <class T>
void deleteValue(T valueToFind,Node<T>* Parent,Node<T>* leftChild,Node<T>* rightChild,Node<T>* leftChildLeft,Node<T>* leftChildRight,
	Node<T>* rightChildLeft,Node<T>* rightChildRight){
	if (Parent == nullptr) return;

	if (Parent->data == valueToFind){
		delete Parent;
		return;
	}

	if (leftChild != nullptr){
		if (leftChild->data == valueToFind){
			delete Parent->left;
			Parent->left = nullptr;
			return;
		}

		if (leftChildLeft != nullptr && leftChildLeft->data == valueToFind){
			delete leftChild->left;
			leftChild->left = nullptr;
			return;
		}

		if (leftChildRight != nullptr && leftChildRight->data == valueToFind){
			delete leftChild->right;
			leftChild->right = nullptr;
			return;
		}
	}

	if (rightChild != nullptr){
		if (rightChild->data == valueToFind){
			delete Parent->right;
			Parent->right = nullptr;
			return;
		}

		if (rightChildLeft != nullptr && rightChildLeft->data == valueToFind){
			delete rightChild->left;
			rightChild->left = nullptr;
			return;
		}

		if (rightChildRight != nullptr && rightChildRight->data == valueToFind){
			delete rightChild->right;
			rightChild->right = nullptr;
			return;
		}
	}
}

int main() {
	
	Node<int>* parent = new Node<int>(10);
	Node<int>* left = new Node<int>(5);
	Node<int>* right = new Node<int>(15);

	Node<int>* leftChildLeft = new Node<int>(3);
	Node<int>* leftChlidRight = new Node<int>(14);
	Node<int>* rightChildRight = new Node<int>(20);
	Node<int>* rightChildLeft = new Node<int>(12);


	bool result = isBST(parent, left, right);
	bool result_two = isBST(parent, left, right ,leftChildLeft,leftChlidRight,rightChildLeft,rightChildRight);

	if (result) cout << "It is a BST" << endl;
	else cout << "Not a BST" << endl;

	if (result_two) cout << "It is a BST" << endl;
	else cout << "Not a BST" << endl;

	bool found = isFound<int>(5, parent, left, right);
	if (found) cout << "value found" << endl;
	else cout << "value not found" << endl;

	bool found_two = isFound<int>(12, parent, left, right , leftChildLeft , leftChlidRight , rightChildLeft , rightChildRight);
	if (found) cout << "value found" << endl;
	else cout << "value not found" << endl;

	insertValue<int>(0, parent, left, right);
	cout << "Parent: " << parent->data << endl;

	if (parent->left)
		cout << "Left Child: " << parent->left->data << endl;

	if (parent->right)
		cout << "Right Child: " << parent->right->data << endl;

	insertValue<int>(12, parent,
		left, right,
		leftChildLeft, leftChlidRight,
		rightChildLeft, rightChildRight);

	Node<int>* rootNode = new Node<int>(50);

	Node<int>* leftNode = new Node<int>(30);
	Node<int>* rightNode = new Node<int>(70);

	rootNode->left = leftNode;
	rootNode->right = rightNode;

	Node<int>* leftLeftNode = new Node<int>(20);
	Node<int>* leftRightNode = new Node<int>(40);
	leftNode->left = leftLeftNode;
	leftNode->right = leftRightNode;

	Node<int>* rightLeftNode = new Node<int>(60);
	Node<int>* rightRightNode = new Node<int>(80);
	rightNode->left = rightLeftNode;
	rightNode->right = rightRightNode;

	deleteValue(40,rootNode,leftNode,rightNode,leftLeftNode,leftRightNode,rightLeftNode,rightRightNode);

	cout << "Deleted: "
		<< (leftNode->right == nullptr ? "Yes" : "No") << endl;

	delete parent;
	delete left;
	delete leftChildLeft;
	delete leftChlidRight;
	delete rightChildLeft;
	delete rightChildRight;
	
	
}