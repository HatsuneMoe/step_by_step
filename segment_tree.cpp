#include <iostream>
#include <assert.h>

using std::cin;
using std::endl;
using std::cout;

class SegmentTreeNode {
public:
    int start, end;
    SegmentTreeNode *left, *right;
    SegmentTreeNode(int start, int end) {
        this->start = start, this->end = end;
        this->left = this->right = NULL;
    }
};

/**
     *@param start, end: Denote an segment / interval
     *@return: The root of Segment Tree
     */
	SegmentTreeNode * build(int start, int end) {
    // write your code here
    // assert(start < end);
    if(start > end)
        return nullptr;

    if(start == end)
        return new SegmentTreeNode(start, end);


    SegmentTreeNode *root = new SegmentTreeNode(start, end);

    root->left = build(start, (start + end) / 2);
    root->right = build((start + end) / 2 + 1, end);

    return root;
}

int main()
{
    auto tree = build(1, 1);

    std::cout << "Start!" << std::endl;
    cout << tree << endl;
    cout << tree->start << " " << tree->end << endl;

    cout << tree->left->start << " " << tree->left->end << endl;
    cout << tree->right->start << " " << tree->right->end << endl;

    return 0;
}