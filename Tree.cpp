#include "Tree.h"
#include <stdexcept>

tree::normalNode::normalNode(int index, const std::string& s):
	leftNode(nullptr), rightNode(nullptr), 
	basicNode(index, s)
{
}

tree::normalNode::~normalNode()
{
}

const bool tree::normalNode::contains(int index) const
{
	if (index == this->index) return true;
	else if (index > this->index) return
		this->rightNode == nullptr ? false : this->rightNode->contains(index);
	else return
		this->leftNode == nullptr ? false : this->leftNode->contains(index);
}

std::string& tree::normalNode::get(int _index)
{
	if (_index == this->index) return this->getValue();
	else if (_index > this->index) 
			return this->rightNode->get(_index);
		else 
			return this->leftNode->get(_index);
}

void tree::normalNode::set(int _index, const std::string& s)
{
	if (_index == this->index)
		this->value = s;
	else if (_index < this->index) {
		if (this->leftNode) this->leftNode->set(_index, s);
		else this->leftNode = std::make_unique<normalNode>(_index, s);
	}
	else {
		if (this->rightNode) this->rightNode->set(_index, s);
		else this->rightNode = std::make_unique<normalNode>(_index, s);
	}
}

const size_t tree::normalNode::size() const
{
	const size_t leftH = (!leftNode) ? 0 : leftNode->size();
	const size_t rightH = (!rightNode) ? 0 : rightNode->size();
	return leftH + rightH + 1;
}

const size_t tree::normalNode::height() const
{
	size_t leftH = 0, rightH = 0;
	if (leftNode)  leftH = leftNode->height();
	if (rightNode)  rightH = rightNode->height();
	return (leftH > rightH) ? leftH + 1 : rightH + 1;
}

tree::BSTree::BSTree(int index, const std::string& s):
	root(std::make_unique<normalNode>(index, s))
{
}

std::string& tree::BSTree::get(int index)
{
	if (contains(index)) return root->get(index);
	else throw std::out_of_range("no elements");
}

tree::LLRBNode::LLRBNode(int index, const std::string& s, const COLOR& color) :
	basicNode(index, s), leftNode(nullptr), color(color), rightNode(nullptr)
{
}

std::unique_ptr<tree::LLRBNode>&& tree::LLRBTree::set(std::unique_ptr<LLRBNode>& node,int index, const std::string& s)
{
	if (index == node->index)
		node->value = s;
	// new node shall be RED
	else if (index < node->index) {
		if (node->leftNode) node->leftNode = set(node->leftNode, index, s);
		else node->leftNode = std::make_unique<LLRBNode>(index, s, COLOR::RED);
	}
	else {
		if (node->rightNode) node->rightNode = set(node->rightNode, index, s);
		else node->rightNode = std::make_unique<LLRBNode>(index, s, COLOR::RED);
	}
	/*
			EXAMPLE: We have B, insert A
		    ...  
			 |	
			 b	
		   N/ \          // OK ¡ª¡ª NO OPERATION NEEDED
		   a(NEW)
	*/

	if (isRed(node->rightNode) && !isRed(node->leftNode))
		rotateLeft(node);
	// lean left
	/*
			EXAMPLE: We have A, insert B
			1. Do standard insert; color new link RED;
			2. if new red link is a right link, rorate left.
		   ...             ...
			|				|
			a				b
		   / \N   --->    N/ \
		   1  b           a   3  // RED LINK shall always in left direction
		     / \         / \     // needs left rotation
			2   3       1   2   
 	*/

	if (isRed(node->leftNode) && isRed(node->leftNode->leftNode))
		rotateRight(node);
	// Balance 4-node
	/*
			EXAMPLE: We have C and B, insert A
			3. if node's left and left-left children are all red, rotate right.
		   ...             ...
			|				|
			c				b
		  N/ \   --->      / \
		  b   2           a   c    // shall not have 2 red link continuously
        N/ \                 / \   // needs right rotation
		a   1               1   2
	*/
	if (isRed(node->leftNode) && isRed(node->rightNode))
		node->flipColor();
	// Split 4-node
	/*
			EXAMPLE: We have B and A, insert C
			4. if both its children are red, flip the color.
		   ...             ...
			|			   N|
			b				b     // a node shall not have 2 red children
          N/ \N   --->     / \    // flip the color, make node RED (go up in 2-3 tree)
		  a   c           a   c
	*/

	return std::move(node);
}

void tree::LLRBNode::flipColor() noexcept
{
	this->color = COLOR::RED;
	this->leftNode->color = COLOR::BLACK;
	this->rightNode->color = COLOR::BLACK;
	
}

const size_t tree::LLRBNode::size() const
{
	const size_t leftH = (!leftNode) ? 0 : leftNode->size();
	const size_t rightH = (!rightNode) ? 0 : rightNode->size();
	return leftH + rightH + 1;
}

const size_t tree::LLRBNode::height() const
{
	size_t leftH = 0, rightH = 0;
	if (leftNode)  leftH = leftNode->height();
	if (rightNode)  rightH = rightNode->height();
	return (leftH > rightH) ? leftH + 1 : rightH + 1;
}

const bool tree::LLRBNode::contains(int _index) const
{
	if (_index == this->index) return true;
	else if (_index > this->index) return
		this->rightNode == nullptr ? false : this->rightNode->contains(_index);
	else return
		this->leftNode == nullptr ? false : this->leftNode->contains(_index);
}

std::string& tree::LLRBNode::get(int _index)
{
	if (_index == this->index) return this->getValue();
	else if (_index > this->index) 
			return this->rightNode->get(_index);
		else 
			return this->leftNode->get(_index);
}

void tree::LLRBTree::rotateLeft(std::unique_ptr<tree::LLRBNode>& node)
{
	if (!isRed(node->rightNode)) throw std::runtime_error("Illegal operation: rotateLeft");
	auto x = std::move(node->rightNode);
	node->rightNode = std::move(x->leftNode);
	x->leftNode = std::move(node);
	x->color = x->leftNode->color;
	x->leftNode->color = COLOR::RED;
	node = std::move(x);
}

void tree::LLRBTree::rotateRight(std::unique_ptr<tree::LLRBNode>& node)
{
	if (!isRed(node->leftNode)) throw std::runtime_error("Illegal operation: rotateRight");
	auto x = std::move(node->leftNode->leftNode);
	node->leftNode = std::move(x->rightNode);
	x->rightNode = std::move(node);
	x->color = x->rightNode->color;
	x->rightNode->color = COLOR::RED;
	node = std::move(x);
}

tree::LLRBTree::LLRBTree(int index, const std::string& s):
	root(std::make_unique<LLRBNode>(index, s, COLOR::BLACK))
{
}

std::string& tree::LLRBTree::get(int index)
{
	if (contains(index)) return root->get(index);
	else throw std::out_of_range("no elements");
}

const bool tree::LLRBTree::isRed(const std::unique_ptr<LLRBNode>& node) noexcept
{
	if (node == nullptr) return false;
	else return node->color == COLOR::RED;
}

