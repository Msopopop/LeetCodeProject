#include "Node.h"

Node::Node():
	next(nullptr),
	pImpl(std::make_unique<impl>())
{}

Node::Node(Node&& node) noexcept:
	next(std::move(node.next)),
	pImpl(node.getValue())
{}

Node::~Node() noexcept {
}

class Node::impl {
public:
	impl() :
		indexValue(0),
		stringValue("DEAFULT")  {
	}

	friend std::ostream& operator<<(std::ostream& os, const impl& imp) {
		os << imp.stringValue << '|' << imp.indexValue;
		return os;
	}
private:
	size_t indexValue;
	std::string stringValue;
};


std::experimental::propagate_const
<std::unique_ptr<Node::impl>>&& 
Node::getValue() noexcept
{
	return std::move(pImpl);
}

std::ostream& operator<<(std::ostream& os, const Node& node)
{
	return os << *(node.pImpl);
}
