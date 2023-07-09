#ifndef BST_H
#define BST_H
#include <iostream>
#include "Stack.h"
#include "Queue.h"

template <class T>
class BinarySearchTree
{
public:
	BinarySearchTree();
	virtual ~BinarySearchTree();

	BinarySearchTree(const BinarySearchTree<T>& scr) = delete;
	BinarySearchTree(BinarySearchTree<T>&& scr) noexcept;
	BinarySearchTree <T>& operator= (const BinarySearchTree <T>& src) = delete; 
	BinarySearchTree <T>& operator= (BinarySearchTree <T>&& src) noexcept;


	
	bool iterativeSearch(const T& key) const;
	bool insert(const T& key);
	bool deletekey(const T& key);
	void print(std::ostream& out) const;
	
	int getHeight() const;
	//Advance
	void iterativeInorderWalk(std::ostream& out) const; 
	void inorderWalk(std::ostream& out) const; 
	void walkByLevels(std::ostream& out) const;
	bool isSimilar(const BinarySearchTree<T>& other) const;
	bool isIdenticalKey(const BinarySearchTree<T>& other) const; 
	void swap(BinarySearchTree<T>& other);
	size_t getCount() const;
private:
	struct Node {
		T key_;
		Node* left_;
		Node* right_;
		Node* p_;//parent

		Node(T key, Node* left = nullptr, Node* right = nullptr, Node* p = nullptr) : 
			key_(key), left_(left), right_(right), p_(p)
		{}
	};
	Node* root_;

	Node* iterativeSearchNode(const T& key) const;
	void printNode(std::ostream& out, Node* root) const;
	size_t getCount(Node* node) const; 
	int getHeight(const Node* node) const;
	void inorderWalk(std::ostream& out, Node* node) const;
	void clear(Node* node);
};


template <class T>
void BinarySearchTree <T>::print(std::ostream& out) const {
	printNode(out, root_);
}

template <class T>
void BinarySearchTree <T>::printNode(std::ostream& out, Node* node) const {
	if (!node){
		return;
	}
	out << node->key_;
	if (node->left_ || node->right_) {
		out << " ("; 
		printNode(out, node->left_); 
		out << ")("; 
		printNode(out, node->right_); 
		out << ") ";
	}
		
}

template <class T>
BinarySearchTree<T>::BinarySearchTree() :
	root_(nullptr){ }

template <class T>
void BinarySearchTree<T>::swap(BinarySearchTree<T>& other)
{
	std::swap(root_, other.root_);
}


template <class T>
BinarySearchTree <T>:: ~BinarySearchTree() {
	if (root_ != nullptr) 
		clear(root_);
}

template <class T>
void BinarySearchTree<T>::clear(Node* node) {
	if (node->left_ != nullptr) 
		clear(node->left_);
	if (node->right_ != nullptr) 
		clear(node->right_);
	delete node;
}

template <class T>
bool BinarySearchTree <T>::iterativeSearch(const T& key) const {
	return iterativeSearchNode(key) != nullptr;
}

template <class T>
typename BinarySearchTree<T>::Node* BinarySearchTree<T>::iterativeSearchNode(const T& key) const 
{
	Node* current = root_;
	while (current != nullptr && current->key_ != key) {
		if (key < current->key_)
			current = current->left_; 
		else
			current = current->right_;
	}
	return current;
}

template <class T> bool BinarySearchTree <T>::insert(const T& key) {
	Node* previous = nullptr; 
	Node* current = root_;
	while (current) {
		previous = current;
		if (current->key_ > key){
			current = current->left_;
		}
			 
		else if (current->key_ < key){
			current = current->right_;
		}
			
		else {
			return false;
		}

	}
		
	Node* newNode = new Node(key); 
	newNode->p_ = previous; 
	if (previous == nullptr) {
		root_ = newNode;
	}
	else {
		if (key < previous->key_)
			previous->left_ = newNode;
		else
			previous->right_ = newNode;
	}
		
	return true;

}

template <class T>
bool BinarySearchTree <T>::deletekey(const T& key) {
	Node* toDelete = iterativeSearchNode(key);
	if (toDelete == nullptr) {
		return false;
	}
	Node* parent = toDelete->p_;
	if (toDelete->left_ == nullptr) { // 0 children or only right child
		if (toDelete == root_){
			root_ = toDelete->right_;

		}
		else if (toDelete == parent->left_){
			parent->left_ = toDelete->right_;
		}	
		else{
			parent->right_ = toDelete->right_;

		}
		delete toDelete;
	}

	else if (toDelete->right_ == nullptr) { // only left child
		if (toDelete == root_){
			root_ = toDelete->left_;
		}
		else if (toDelete == parent->left_){
			parent->left_ = toDelete->left_;
		}
		else{
			parent->right_ = toDelete->left_;
		}	
		delete toDelete;
	}

	else { // two children
		Node* minRight = toDelete->right_;
		parent = nullptr;
		while (minRight->left_ != nullptr) {
			parent = minRight;
			minRight = minRight->left_;
		}
		toDelete->key_ = minRight->key_;
		if (parent == nullptr){
			toDelete->right_ = minRight->right_;
		}
		else{
			parent->left_ = minRight->right_;

		}
		delete minRight;
	}
		
	return true;
		
}


template <class T>
size_t BinarySearchTree <T>::getCount() const
{
	return getCount(this->root_);
};

template <class T> 
size_t BinarySearchTree <T>::getCount(Node* node) const 
{
	if (node == nullptr) {
		return 0;
	}
	return (1 + getCount(node->left_) + getCount(node->right_));
		
}

template <class T> int BinarySearchTree <T>::getHeight() const {
	return getHeight(root_);
}

template <class T>
int BinarySearchTree <T>::getHeight(const Node* node) const 
{
	if (node == nullptr){
		return 0;
	}
	return std::max(getHeight(node->left_), getHeight(node->right_)) + 1;
}

template <class T>
void BinarySearchTree <T>::iterativeInorderWalk(std::ostream& out) const
{
	if (root_ == nullptr){
		return;
	} 
	StackArray<Node*> stack(getHeight());
	Node* current = root_;
	while (!stack.isEmpty() || current != nullptr)
	{
		if (current != nullptr) {
			stack.push(current);
			current = current->left_;
		}
		else {
			current = stack.pop();
			out << current->key_ << " ";
			current = current->right_;
		}
	}
}
template <class T> void BinarySearchTree <T>::inorderWalk(std::ostream& out) const {
		inorderWalk(out, root_);
}
template <class T>
void BinarySearchTree<T>::inorderWalk(std::ostream& out, Node* node) const {
	if (node != nullptr) {
		inorderWalk(out, node->left_);
		out << node->key_ << " ";
		inorderWalk(out, node->right_);
	}
}

template <class T>
void BinarySearchTree <T>::walkByLevels(std::ostream& out) const {
	if (root_ == nullptr){
		return;
	} 
	int numOfNodes = getCount();
	QueueArray<Node*> queue(numOfNodes);
	queue.enQueue(root_);
	Node* current = nullptr;
	while (!queue.isEmpty()) {
		current = queue.deQueue();
		out << current->key_ << " ";
		if (current->left_ != nullptr)
		{
			queue.enQueue(current->left_);
		}
		if (current->right_ != nullptr){
			queue.enQueue(current->right_);
		} 
	}
}
		
template <class T>
bool BinarySearchTree <T>::isSimilar(const BinarySearchTree<T>& other) const 
{
	int countThis = this->getCount();
	if (countThis != other.getCount())
	{
				return false;
	}
	if (countThis == 0)
	{
		return true;
	}
	StackArray<Node*> stack(getHeight());
	Node* current = root_;
	while (!stack.isEmpty() || current != nullptr) 
	{
		if (current != nullptr) 
		{
			stack.push(current);
			current = current->left_;
		}	
		else {
			current = stack.pop();
			if (!other.iterativeSearch(current->key_)) 
				return false;
			current = current->right_;
		}
	}
	return true;
}

template <class T>
bool BinarySearchTree <T>::isIdenticalKey(const BinarySearchTree<T>& other) const {
	if (this->getCount() + other.getCount() == 0)//****
	{
		return false;
	}
	Node* current = root_;
	StackArray<Node*> stack(getHeight());
	while (!stack.isEmpty() || current != nullptr) 
	{
		if (current != nullptr) 
		{
			stack.push(current);
			current = current->left_;
		}
		else 
		{
			current = stack.pop();
			if (other.iterativeSearch(current->key_)) 
				return true;;
			current = current->right_;
		}
	}
	return false;
}

#endif