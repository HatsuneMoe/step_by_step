#include <iostream>

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
	/** @param head The linked list's head.
	Note that the head is guaranteed to be not null, so it contains at least one node. */
	ListNode *h = nullptr;
	int num = 0;
	
	Solution(ListNode* head) {
		h = head;
	}

	/** Returns a random node's value. */
	int getRandom() {
		num = h->val;
		int c = 2;
		for (ListNode* i = h->next; i; i = i->next, ++c)
		{	
			if (std::rand() % c == 0)
				num = i->val;
		}
		return num;
	}
};

int main()
{
	ListNode *head = new ListNode(1);
	head->next = new ListNode(2);
	head->next->next = new ListNode(3);
	Solution obj(head);
	for (auto i = 0; i < 10; ++i) {
		int param_1 = obj.getRandom();
		std::cout << param_1 << std::endl;
	}
	system("pause");
	return 0;
}
