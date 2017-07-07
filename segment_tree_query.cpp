#include <iostream>
#include <assert.h>

using std::cin;
using std::cout;
using std::endl;

class SegmentTreeNode {
public:
    int start, end, max;
    SegmentTreeNode *left, *right;
    SegmentTreeNode(int start, int end, int max) {
        this->start = start;
        this->end = end;
        this->max = max;
        this->left = this->right = NULL;
    }
};

class Solution {
public:
    /**
     *@param root, start, end: The root of segment tree and
     *                         an segment / interval
     *@return: The maximum number in the interval [start, end]
     */
    int query(SegmentTreeNode *root, int start, int end) {
        // write your code here
        assert(root != nullptr);
        assert(start <= end);

        cout << "start: " << start << endl;
        cout << "end: " << end << endl;

        cout << "root-start: " << root->start << endl;
        cout << "root-end: " << root->end << endl;
        cout << "root-max: " << root->max << endl;

        if (root->start == start && root->end == end)
            return root->max;

        if (end <= (root->start + root->end) / 2 && root->left)
            query(root->left, start, end);

        else if ((root->start + root->end) / 2 + 1 <= start && root->right)
            query(root->right, start, end);
        else if(root->left && root->right)
        {
            int max_left = query(root->left, start, (root->start + root->end) / 2);
            int max_right = query(root->right, (root->start + root->end) / 2 + 1, end);
            return (max_left > max_right)?max_left:max_right;
        }
    }
};


int main()
{
    Solution A;
    SegmentTreeNode *root = new SegmentTreeNode(0 ,3 ,4);
    root->left = new SegmentTreeNode(0 ,1 ,4);
    root->right = new SegmentTreeNode(2 ,3 ,3);

    root->left->left = new SegmentTreeNode(0 ,0 ,1);
    root->left->right = new SegmentTreeNode(1 ,1 ,4);
    root->right->left = new SegmentTreeNode(2 ,2 ,2);
    root->right->right = new SegmentTreeNode(3 ,3 ,3);

    int a, b;

    while (cin >> a >> b)
    {

        cout << A.query(root, a, b) << endl;
    }

    return 0;
}