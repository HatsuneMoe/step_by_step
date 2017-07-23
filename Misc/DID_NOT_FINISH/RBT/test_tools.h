#pragma once

#ifndef RBQ_TEST_TOOLS_H
#define RBQ_TEST_TOOLS_H
#include <iostream>
#include <bitset>

struct rb_node {
	intptr_t  __rb_parent_color;
	struct rb_node *rb_right;
	struct rb_node *rb_left;
	char val;
	rb_node(char a) { val = a; rb_left = nullptr; rb_right = nullptr; __rb_parent_color = (intptr_t) nullptr; };
	rb_node(char a, rb_node* x) { val = a; rb_left = nullptr; rb_right = nullptr; __rb_parent_color = (intptr_t)x; };
};

void output_impl(rb_node* n, bool left, std::string const& indent)
{
	if (n->rb_right)
	{
		output_impl(n->rb_right, false, indent + (left ? "|     " : "      "));
	}
	std::cout << indent;
	std::cout << (left ? '\\' : '/');
	std::cout << "----- ";
    if (((n)->__rb_parent_color & 1) == 0)
	    std::cout << n->val << "(red)" << std::endl;
    else
        std::cout << n->val << "(black)" << std::endl;
	if (n->rb_left)
	{
		output_impl(n->rb_left, true, indent + (left ? "      " : "|     "));
	}
}

void travel(rb_node *root)
{
	if (root->rb_right)
	{
		output_impl(root->rb_right, false, "");
	}
    if (((root)->__rb_parent_color & 1) == 0)
	    std::cout << root->val << "(red)" << std::endl;
    else
        std::cout << root->val << "(black)" << std::endl;
	if (root->rb_left)
	{
		output_impl(root->rb_left, true, "");
	}
}

#endif //RBQ_TEST_TOOLS_H
