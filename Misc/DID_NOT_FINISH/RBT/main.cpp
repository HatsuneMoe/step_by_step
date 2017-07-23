#include <vector>
#include "test_tools.h"

using std::vector;

//struct rb_node {
//    unsigned long  __rb_parent_color;
//    struct rb_node *rb_right;
//    struct rb_node *rb_left;
//    char val;
//    rb_node(char a){val=a;rb_left= nullptr;rb_right= nullptr;__rb_parent_color=(unsigned long) nullptr;};
//    rb_node(char a, rb_node* x){val=a;rb_left= nullptr;rb_right= nullptr;__rb_parent_color=(unsigned long)x;};
//};
#define RB_RED 0
#define RB_BLACK 1

#define rb_color(node) ((node)->__rb_parent_color & 1)
#define rb_parent(node) ((rb_node *)((node)->__rb_parent_color & ~3))
#define rb_parent_del_fix(node) ((node == nullptr)?parent_x:((rb_node *)((node)->__rb_parent_color & ~3)))
#define set_rb_color_red(node) ((node)->__rb_parent_color &= ~1)
#define set_rb_color_black(node) ((node)->__rb_parent_color |= 1)
void set_rb_parent(rb_node *node, rb_node *parent)
{
	node->__rb_parent_color = (node->__rb_parent_color & 3) | (intptr_t)parent;
}

void left_rotate(rb_node *&root, rb_node *x)
{
	/*
	*    x
	*   / \
	*  a   y
	*     / \
	*    b   c
	* */
	rb_node *y = x->rb_right;
	x->rb_right = y->rb_left;
	if (y->rb_left != nullptr)
		set_rb_parent(y->rb_left, x);  //  y->rb_left->__rb_parent_color = (unsigned int)x;
	set_rb_parent(y, rb_parent(x));  // y->__rb_parent_color = x->__rb_parent_color;
	if (x->__rb_parent_color == (intptr_t) nullptr)
		root = y;
	else if (x == rb_parent(x)->rb_left)
		rb_parent(x)->rb_left = y;
	else
		rb_parent(x)->rb_right = y;
	y->rb_left = x;
	set_rb_parent(x, y);//  x->__rb_parent_color = (unsigned int)y;
}

void right_rotate(rb_node *&root, rb_node *y)
{
	/*
	*     y
	*    / \
	*   x   c
	*  / \
	* a   b
	* */
	rb_node *x = y->rb_left;
	y->rb_left = x->rb_right;
	if (x->rb_right != nullptr)
		set_rb_parent(x->rb_right, y);  //  x->rb_right->__rb_parent_color = (unsigned int)y;
	set_rb_parent(x, rb_parent(y));  // x->__rb_parent_color = y->__rb_parent_color;
	if (y->__rb_parent_color == (intptr_t) nullptr)
		root = x;
	else if (y == rb_parent(y)->rb_left)
		rb_parent(y)->rb_left = x;
	else
		rb_parent(y)->rb_right = x;
	x->rb_right = y;
	set_rb_parent(y, x);  // y->__rb_parent_color = (unsigned int)x;
}

void rb_insert_fixup(rb_node *&root, rb_node *z)
{
    rb_node *y = nullptr;
    while(rb_parent(z) && rb_parent(rb_parent(z)) && rb_color(rb_parent(z)) == RB_RED)
    {
        if (rb_parent(z) == rb_parent(rb_parent(z))->rb_left)
        {
            y = rb_parent(rb_parent(z))->rb_right;
            if (y && rb_color(y) == RB_RED)
            {
                // situation 1
                set_rb_color_black(rb_parent(z));
                set_rb_color_black(y);
                set_rb_color_red(rb_parent(rb_parent(z)));
                z = rb_parent(rb_parent(z));
            } else if (z == rb_parent(z)->rb_right) {
                // situation 2
                z = rb_parent(z);
                left_rotate(root, z);
            } else {
                // situation 3
                set_rb_color_black(rb_parent(z));
                set_rb_color_red(rb_parent(rb_parent(z)));
                right_rotate(root, rb_parent(rb_parent(z)));
            }
        }
        else {
            y = rb_parent(rb_parent(z))->rb_left;
            if (y && rb_color(y) == RB_RED)
            {
                // situation 1
                set_rb_color_black(rb_parent(z));
                set_rb_color_black(y);
                set_rb_color_red(rb_parent(rb_parent(z)));
                z = rb_parent(rb_parent(z));
            } else if (z == rb_parent(z)->rb_left) {
                // situation 2
                z = rb_parent(z);
                right_rotate(root, z);
            } else {
                // situation 3
                set_rb_color_black(rb_parent(z));
                set_rb_color_red(rb_parent(rb_parent(z)));
                left_rotate(root, rb_parent(rb_parent(z)));
            }
        }
    }
    set_rb_color_black(root);
}

void rb_insert(rb_node *&root, rb_node *z)
{
	rb_node *parent = nullptr, *x = root;
	while (x != nullptr)
	{
        parent = x;
		if (z->val < x->val)
			x = x->rb_left;
		else
			x = x->rb_right;
	}
	set_rb_parent(z, parent);
	if (parent == nullptr) {
		root = z;
	}
	else if (z->val < parent->val) {
        parent->rb_left = z;
	}
	else {
        parent->rb_right = z;
	}
	z->rb_left = nullptr;
	z->rb_right = nullptr;
	set_rb_color_red(z);
	rb_insert_fixup(root, z);
}
/*
void rb_transplant(rb_node *&root, rb_node *u, rb_node *v)
{
    if (rb_parent(u) == nullptr)
        root = v;
    else if (u == rb_parent(u)->rb_left)
        rb_parent(u)->rb_left = v;
    else
        rb_parent(u)->rb_right = v;
    if (v != nullptr)
    set_rb_parent(v, rb_parent(u));
}

void rb_delete_fixup(rb_node *&root, rb_node *x, rb_node *parent_x)
{
    rb_node* w = nullptr;
    while (x != root && (x == nullptr || rb_color(x) == RB_BLACK))
    {
        if (x == rb_parent_del_fix(x)->rb_left)
        {
            w = rb_parent_del_fix(x)->rb_right;
            if (w && rb_color(w) == RB_RED)
            {
                set_rb_color_black(w);
                set_rb_color_red(rb_parent_del_fix(x));
                left_rotate(root, rb_parent_del_fix(x));
                w = rb_parent_del_fix(x)->rb_right;
            }
            if (w && rb_color(w->rb_left) == RB_BLACK && rb_color(w->rb_right) == RB_BLACK)
            {
                set_rb_color_red(w);
                x = rb_parent_del_fix(x);
            } else if (w && rb_color(w->rb_right) == RB_BLACK) {
                set_rb_color_black(w->rb_left);
                set_rb_color_red(w);
                right_rotate(root, w);
                w = rb_parent_del_fix(x)->rb_right;
            } else {
                if (w != nullptr){
                    if (rb_color(rb_parent_del_fix(x)) == RB_RED)
                        set_rb_color_red(w);
                    else
                        set_rb_color_black(w);
                    set_rb_color_black(w->rb_right);
                }
                set_rb_color_black(rb_parent_del_fix(x));
                std::cout << rb_parent_del_fix(x) << std::endl;
                left_rotate(root, rb_parent_del_fix(x));
                x = root;
            }
        } else {
            w = rb_parent_del_fix(x)->rb_left;
            if (w && rb_color(w) == RB_RED)
            {
                set_rb_color_black(w);
                set_rb_color_red(rb_parent_del_fix(x));
                right_rotate(root, rb_parent_del_fix(x));
                w = rb_parent_del_fix(x)->rb_left;
            }
            if (w && rb_color(w->rb_right) == RB_BLACK && rb_color(w->rb_left) == RB_BLACK)
            {
                set_rb_color_red(w);
                x = rb_parent_del_fix(x);
            } else if (w && rb_color(w->rb_left) == RB_BLACK) {
                set_rb_color_black(w->rb_right);
                set_rb_color_red(w);
                left_rotate(root, w);
                w = rb_parent_del_fix(x)->rb_left;
            } else {
                if (w != nullptr){
                    if (rb_color(rb_parent_del_fix(x)) == RB_RED)
                        set_rb_color_red(w);
                    else
                        set_rb_color_black(w);
                    set_rb_color_black(w->rb_left);
                }
                set_rb_color_black(rb_parent_del_fix(x));
                right_rotate(root, rb_parent_del_fix(x));
                x = root;
            }
        }
    }
    set_rb_color_black(x);
}

rb_node* tree_minimum(rb_node* x)
{
    while (x->rb_left != nullptr)
        x = x->rb_left;
    return x;
}

void rb_delete(rb_node *&root, rb_node *z)
{
    rb_node *y = z, *x = nullptr, *parent_x = nullptr;
    auto y_ori_color = rb_color(y);
    if (rb_parent(z) == nullptr)
    {
        x = z->rb_right;
        rb_transplant(root, z, z->rb_right);
        parent_x = z;
    } else if (z->rb_right == nullptr) {
        x = z->rb_left;
        rb_transplant(root, z, z->rb_left);
        parent_x = z;
    } else {
        y = tree_minimum(z->rb_right);
        y_ori_color = rb_color(y);
        x = y->rb_right;
        parent_x = y;
        if (rb_parent(y) == z)
            set_rb_parent(x, y);
        else {
            rb_transplant(root, y, y->rb_right);
            y->rb_right = z->rb_right;
            set_rb_parent(y->rb_right, y);
        }
        rb_transplant(root, z, y);
        y->rb_left = z->rb_left;
        set_rb_parent(y->rb_left, y);
        if (rb_color(z) == RB_RED)
            set_rb_color_red(y);
        else
            set_rb_color_black(y);
    }
    if (y_ori_color == RB_BLACK){
        std::cout << "before fix:" << std::endl;
        travel(root);
        rb_delete_fixup(root, x, parent_x);
    }
}*/

#define rb_color_test(p) (p & 1)
#define rb_parent_test(p) (p & ~3)
#define set_rb_color_red_test(p) (p &= ~1)
#define set_rb_color_black_test(p) (p |= 1)

void set_rb_parent_test(intptr_t &x, intptr_t &y)
{
	x = x & 3 | y;
}

int test1()
{
    rb_node *base = new rb_node('0');
    rb_node *root = new rb_node('y', base), *head = root;
    root->rb_right = new rb_node('c', root);
    root->rb_left = new rb_node('x', root);
    root->rb_left->rb_left = new rb_node('a', root->rb_right);
    root->rb_left->rb_right = new rb_node('b', root->rb_right);

    base->rb_left = new rb_node('1', base);
    base->rb_right = root;
    travel(base);
    right_rotate(head, root);
    travel(base);
//    rb_insert(base, new rb_node('d'));
//    travel(base);
    int a = 1235254324;
    int c = 254364;
    auto b = (intptr_t)&a;
    std::cout << &a << " " << b << " " << std::hex << b << std::endl;
    std::bitset<32> _bits(b);
    std::cout << _bits << " " << rb_parent_test(b) << " " << rb_color_test(b) << std::endl;

    set_rb_color_black_test(b);
    _bits = b;
    std::cout << _bits << " " << rb_parent_test(b) << " " << rb_color_test(b) << std::endl;

    //    set_rb_color_red_test(b);
    //    _bits = b;
    //    std::cout << _bits << " " << rb_parent_test(b) << " " << rb_color_test(b) << std::endl;

    auto d = (intptr_t)&c;
    set_rb_parent_test(b, d);
    std::cout << &c << " " << b << " " << rb_color_test(b) << " " << rb_parent_test(b) << std::endl;

    return 0;
}

int test2()
{
    rb_node *root = nullptr;
    std::vector<rb_node *> _list;
    for (char i='0'; i<='9'; ++i){
        rb_node *a = new rb_node(i);
        rb_insert(root, a);
        std::cout << "add " << i << std::endl;
        _list.push_back(a);
        travel(root);
    }

    for (auto i=_list.rbegin(); i!=_list.rend(); ++i)
    {
        std::cout << "delete " << (*i)->val << std::endl;
        rb_delete(root, (*i));
        travel(root);
    }

    return 0;
}

int main()
{
    test2();
	system("pause");
	return 0;
}