#include <iostream>


struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    /**
     * @param head a ListNode
     * @param val an integer
     * @return a ListNode
     */
    ListNode *removeElements(ListNode *head, int val) {
        // Write your code here
        for (auto i = head; i;)
        {
            if (head->val == val){
                head = head->next;
                i = head;
                continue;
            }

            if (i->next && i->next->val == val){
                i->next = i->next->next;
            } else
                i = i->next;
        }
        return head;
    }
};


int main()
{
    Solution A;
    ListNode *root = new ListNode(2);
    root->next = new ListNode(2);
    root->next->next = new ListNode(2);
    root->next->next->next = new ListNode(2);
    root->next->next->next->next = new ListNode(2);
    root->next->next->next->next->next = new ListNode(2);
    root->next->next->next->next->next->next = new ListNode(2);
    for (auto i = A.removeElements(root, 2); i; i=i->next)
        std::cout << i->val << " ";
    return 0;
}
