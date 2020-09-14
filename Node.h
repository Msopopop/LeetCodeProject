#pragma once
#include <memory>
#include <string>
#include <ostream>
#ifdef __cpp_lib_experimental_propagate_const
#include <propagate_const>
#else
#include "propagate_const.h"
#endif

using std::experimental::propagate_const;
class Node
{
public:
	class impl;	
	friend std::ostream& operator<<(std::ostream& os, const Node& node);
	
	Node() noexcept;
	Node(const Node& node) = delete;
	Node& operator=(const Node&) = delete;
	Node(Node&& node) noexcept;

	~Node() noexcept;

	std::experimental::propagate_const<std::unique_ptr<impl>>&& 
		getValue() noexcept;
	
	std::unique_ptr<Node> next;
private:
	std::experimental::propagate_const<std::unique_ptr<impl>> pImpl;
};

