#include <iostream>
#include <unordered_map>
using std::unordered_map;
struct ListNode_I
{
	int key;
	int val;
	ListNode_I *pre, *next;
	ListNode_I(int k, int x) { key = k; val = x; pre = nullptr; next = nullptr; };
};

class LRUCache {
public:
	LRUCache(int capacity) {
		cap = 0;
		max_cap = capacity;
		head = nullptr;
		tail = nullptr;
	}

	int get(int key) {
		auto it = hash_map.find(key);
		if (it != hash_map.end())
		{
			if (it->second == tail && cap > 1)
				tail = it->second->pre;
			if (it->second->pre)
				it->second->pre->next = it->second->next;
			if (it->second->next && it->second->pre)
				it->second->next->pre = it->second->pre;
			if (it->second != head) {
				it->second->pre = nullptr;
				it->second->next = head;
				head->pre = it->second;
				head = it->second;
			}
			std::cout << "get : " << it->second->val << std::endl;
			return it->second->val;
		}
		else {
			std::cout << "get : " << -1 << std::endl;
			return -1;
		}
	}

	void put(int key, int value) {
		std::cout << key << "  " << value << std::endl;
		auto it = hash_map.find(key);
		if (it != hash_map.end())
		{
			it->second->val = value;
			if (it->second == head)
				return;
			else if(it->second == tail)
			{
				tail = it->second->pre;
				tail->next = nullptr;
			}
			else 
			{
				it->second->pre->next = it->second->next;
				it->second->next->pre = it->second->pre;
			}
			it->second->pre = nullptr;
			head->pre = it->second;
			it->second->next = head;
			head = it->second;
			return;
		}
		ListNode_I *node = new ListNode_I(key, value);
		if (cap == 0)
		{
			head = node;
			tail = node;
			hash_map[key] = node;
			cap++;
		}
		else if (cap < max_cap) 
		{
			head->pre = node;
			node->next = head;
			head = node;
			hash_map[key] = node;
			cap++;
		}
		else {
			if (head != tail)
			{
				tail = tail->pre;
				auto it = hash_map.find(tail->next->key);
				if (it != hash_map.end())
					hash_map.erase(it);
				delete tail->next;
				tail->next = nullptr;
			}
			else {
				auto it = hash_map.find(tail->key);
				if (it != hash_map.end())
					hash_map.erase(it);
				head = node;
				tail = node;
				hash_map[key] = node;
				return;
			}
			
			head->pre = node;
			node->next = head;
			head = node;
			hash_map[key] = node;
		}
		
	}
private:
	int cap;
	int max_cap;
	ListNode_I *head;
	ListNode_I *tail;
	unordered_map<int, ListNode_I *> hash_map;
};

int main()
{
	LRUCache cache(1 /* capacity */);
	cache.put(2, 1);
	cache.get(2);
	cache.put(3, 2);
	cache.get(2);
	cache.get(3);

	//cache.put(1, 1);
	//cache.put(2, 2);
	//cache.get(1);       // returns 1
	//cache.put(3, 3);    // evicts key 2
	//cache.get(2);       // returns -1 (not found)
	//cache.put(4, 4);    // evicts key 1
	//cache.get(1);       // returns -1 (not found)
	//cache.get(3);       // returns 3
	//cache.get(4);       // returns 4

	system("pause");
	return 0;
}