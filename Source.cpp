#include<iostream>
#include<array>
#include<memory>
#include<stack>
#include<vector>
#include<queue>
#include<algorithm>
#include<map>
#include<unordered_map>
#include<string>
#include<queue>
#include<numeric>
#include<limits.h>
#include<cmath>

using namespace std;

//Definition for singly-linked list.
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

// Definition for a Node.
class Node {
public:
	int val = NULL;
	vector<Node*> children;

	Node() {}

	Node(int _val, vector<Node*> _children) {
		val = _val;
		children = _children;
	}
};

//Min heap comparator
struct gheap {
	bool operator()(ListNode *a, ListNode *b) {
		if(a&&b)
			return a->val < b->val;

		return false;
	}
};

//Heap of pairs
struct pHeap {
	bool operator()(pair<int, int> p1, pair<int, int> p2) {
		return p1.second < p2.second;
	}
};

//Heap of pairs
struct sHeap {
	bool operator()(pair<int, int> p1, pair<int, int> p2) {
		return (p1.first + p1.second) > (p2.first + p2.second);
	}
};

//Heap of pairs
struct wHeap {
	bool operator()(pair<string, int> p1, pair<string, int> p2) {
		if (p1.second == p2.second)
			return p1.first > p2.first;
		else
			return p1.second < p2.second;
	}
};

struct fHeap {
	bool operator()(pair<char, int> p1, pair<char, int> p2) {
		return p1.second < p2.second;
	}
};

struct rHeap {
	bool operator()(pair<char, int> p1, pair<char, int> p2) {
		return p1.second < p2.second;
	}
};

//Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

//Definition for singly - linked list with a random pointer.
struct RandomListNode {
	int label;
	RandomListNode *next, *random;
	RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
};

class Solution {
private:
	ListNode * head;
	int m_iTreeNodesCount;
	vector<int> inOrderList;
	int pathSum_Paths = 0;
	int firstMin = 0;
	int secondMin = INT_MAX;

public:
	Solution() {
		head = NULL;
		m_iTreeNodesCount = 0;
		inOrderList.clear();
	}

/************************************BINARY_SEARCH************************************/
	//Adds a node to the list
	void addNode(int val) {
		if (head == NULL) {
			head = new ListNode(val);
		}
		else {
			auto temp = head;
			while (temp->next != NULL) {
				temp = temp->next;
			}

			temp->next = new ListNode(val);
		}
	}

	ListNode *getHead() {
		return head;
	}

	//https://leetcode.com/problems/middle-of-the-linked-list/description/
	ListNode * middleNode(ListNode* head) {
		if (head == NULL)
			return NULL;

		ListNode *slow = head;
		ListNode *fast = head;

		while (slow != NULL && fast != NULL && fast->next != NULL) {
			slow = slow->next;
			fast = fast->next->next;
		}

		return slow;
	}

	//https://leetcode.com/problems/delete-node-in-a-linked-list/description/
	void deleteNode(ListNode* node) {
		auto prev = node;
		while (node != NULL && node->next != NULL) {
			node->val = node->next->val;
			prev = node;
			node = node->next;
		}

		prev->next = NULL;
		delete node;
	}

	//https://leetcode.com/problems/remove-duplicates-from-sorted-list/description/
	ListNode* deleteDuplicates(ListNode* head) {
		if (head == NULL) {
			return NULL;
		}

		ListNode *temp = head;
		while (temp != NULL) {
			ListNode *d = temp;

			while (d->next != NULL && d->val == d->next->val) {
				d = d->next;
			}

			temp->next = d->next;
			temp = temp->next;
		}

		return head;
	}

	//https://leetcode.com/problems/remove-linked-list-elements/description/
	ListNode* removeElements(ListNode* head, int val) {
		if (head == NULL) {
			return NULL;
		}

		auto temp = head;

		//Handle the head node
		while (temp != NULL && temp->val == val) {
			temp = temp->next;
		}
		head = temp;
		ListNode *prev = NULL;
		while (temp != NULL) {
			if (temp->val == val) {
				prev->next = temp->next;
				temp = temp->next;
				continue;
			}

			prev = temp;
			temp = temp->next;
		}

		return head;
	}

	//https://leetcode.com/problems/merge-two-sorted-lists/description/
	ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
		if (l1 == NULL) {
			return l2;
		}

		if (l2 == NULL) {
			return l1;
		}

		ListNode *p = new ListNode(-1);
		auto pt = p;
		auto t1 = l1;
		auto t2 = l2;
		while (t1 != NULL && t2 != NULL) {
			if (t1->val < t2->val) {
				p->next = t1;
				t1 = t1->next;
			}
			else {
				p->next = t2;
				t2 = t2->next;
			}
			p = p->next;
		}

		if (t1 != NULL) {
			p->next = t1;
		}

		if (t2 != NULL) {
			p->next = t2;
		}

		return pt->next;
	}

	//https://leetcode.com/problems/linked-list-cycle/description/
	bool hasCycle(ListNode *head) {
		if (head == NULL) {
			return false;
		}

		auto slow = head;
		auto fast = head;

		while (slow != NULL && fast != NULL && fast->next != NULL) {
			slow = slow->next;
			fast = fast->next->next;

			if (slow == fast) {
				return true;
			}
		}

		return false;
	}

	//https://leetcode.com/problems/reverse-linked-list/description/
	ListNode* reverseList(ListNode* head) {
		if (head == NULL) {
			return head;
		}

		ListNode *p = NULL;
		auto c = head;
		auto n = head;

		while (c != NULL) {
			n = c->next;
			c->next = p;
			p = c;
			c = n;
		}

		return p;
	}

	//https://leetcode.com/problems/intersection-of-two-linked-lists/
	ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
		if (headA == NULL || headB == NULL) {
			return NULL;
		}

		auto pA = headA;
		auto pB = headB;

		auto t1 = pA;
		auto t2 = pB;

		while (t1 != NULL || t2 != NULL) {
			if (t1 == t2) {
				return t1;
			}

			t1 = t1->next;
			t2 = t2->next;

			if (!t1 && !t2) {
				return t1;
			}

			if (t1 == NULL) {
				t1 = pB;
			}

			if (t2 == NULL) {
				t2 = pA;
			}
		}

		return NULL;
	}

	//https://leetcode.com/problems/palindrome-linked-list/description/
	bool isPalindrome(ListNode* head) {
		if (head == NULL || head->next == NULL) {
			return true;
		}

		auto len = 0;
		auto t = head;

		//Instead of finding the length and dividing it by 2, you can also use fast and slow pointers.
		while (t != NULL) {
			len++;
			t = t->next;
		}

		auto mid = 0;
		mid = len / 2;

		t = head;
		for (int i = 0;i < mid - 1;i++) {
			t = t->next;
		}

		auto s = head;

		if (len % 2 == 0) {
			s = t->next;
		}
		else {
			s = t->next->next;
		}

		t->next = NULL;
		t = reverseList(head);

		while (t != NULL && s != NULL) {
			if (t->val != s->val) {
				return false;
			}

			t = t->next;
			s = s->next;
		}

		return true;
	}

	//https://leetcode.com/problems/remove-nth-node-from-end-of-list/description/
	ListNode* removeNthFromEnd(ListNode* head, int n) {
		ListNode *d = new ListNode(-1);
		d->next = head;

		auto first = d;
		auto second = d;

		//Maintain a gap of n nodes between first and second pointers.
		for (int i = 0;i < n + 1;i++) {
			second = second->next;
		}

		//Move both pointers by node.
		while (second != NULL) {
			first = first->next;
			second = second->next;
		}

		first->next = first->next->next;

		return d->next;
	}

	//https://leetcode.com/problems/rotate-list/description/
	ListNode* rotateRight(ListNode* head, int k) {
		if (k == 0 || head == NULL) {
			return head;
		}

		//Get the list length
		auto t = head;
		auto len = 0;
		while (t != NULL) {
			t = t->next;
			len++;
		}

		auto rotate = k % len;

		if (rotate == 0) {
			return head;
		}

		//Rotate the list
		ListNode *d = new ListNode(-1);
		d->next = head;
		auto first = d;
		auto second = d;

		for (int i = 0;i < rotate + 1;i++) {
			second = second->next;
		}

		while (second != NULL) {
			first = first->next;
			second = second->next;
		}

		//Cut the list
		second = first->next;
		first->next = NULL;

		auto newHead = second;
		while (second->next != NULL) {
			second = second->next;
		}

		second->next = d->next;

		return newHead;
	}

	//https://leetcode.com/problems/linked-list-cycle-ii/description/
	ListNode *detectCycle(ListNode *head) {
		if (head == NULL) {
			return head;
		}

		auto slow = head;
		auto fast = head;
		bool exists = false;

		while (fast != NULL && fast->next != NULL) {
			slow = slow->next;
			fast = fast->next->next;

			if (slow == fast) {
				exists = true;
				break;
			}
		}

		if (!exists) {
			return NULL;
		}

		slow = head;

		//Cases where there are only 2 nodes and the tail node connnects to the first node. 1->2 - 2 connects back to 1.
		if (slow == fast) {
			return slow;
		}

		while (true) {
			slow = slow->next;
			fast = fast->next;

			if (slow == fast) {
				return slow;
			}
		}

		return NULL;
	}

	//https://leetcode.com/problems/add-two-numbers/description/
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		if (l1 == NULL || l2 == NULL) {
			auto result = (l1 == NULL) ? l2 : l1;
			return result;
		}

		auto carry = 0;
		auto sum = 0;
		auto d = new ListNode(-1);
		auto current = d;

		while (l1 != NULL && l2 != NULL) {
			sum = l1->val + l2->val + carry;
			if (sum >= 10) {
				sum = sum % 10;
				carry = 1;
			}
			else {
				carry = 0;
			}

			ListNode *r = new ListNode(sum);
			current->next = r;

			l1 = l1->next;
			l2 = l2->next;
			current = current->next;
		}

		if (l1 == NULL) {
			//Add the remaining elements of l2
			while (l2 != NULL) {
				sum = l2->val + carry;
				if (sum >= 10) {
					sum = sum % 10;
					carry = 1;
				}
				else {
					carry = 0;
				}

				ListNode *r = new ListNode(sum);
				current->next = r;

				l2 = l2->next;
				current = current->next;
			}
		}

		if (l2 == NULL) {
			//Add the remaining elements of l1
			while (l1 != NULL) {
				sum = l1->val + carry;
				if (sum >= 10) {
					sum = sum % 10;
					carry = 1;
				}
				else {
					carry = 0;
				}

				ListNode *r = new ListNode(sum);
				current->next = r;

				l1 = l1->next;
				current = current->next;
			}
		}

		if (carry) {
			ListNode *r = new ListNode(carry);
			current->next = r;
		}

		return d->next;
	}

	ListNode* addTwoNumbers2(ListNode* l1, ListNode* l2) {
		if (l1 == NULL || l2 == NULL) {
			return (l1 == NULL) ? l2 : l1;
		}

		std::stack<int> s1;
		auto t1 = l1;
		while (t1 != NULL) {
			s1.push(t1->val);
			t1 = t1->next;
		}

		std::stack<int> s2;
		auto t2 = l2;
		while (t2!=NULL) {
			s2.push(t2->val);
			t2 = t2->next;
		}

		auto carry = 0;		
		auto sum = 0;
		ListNode *result = NULL;

		while (!s1.empty() && !s2.empty()) {
			sum = carry + s1.top() + s2.top();
			s1.pop();
			s2.pop();

			if (sum >= 10) {
				sum = sum % 10;
				carry = 1;
			} else {
				carry = 0;
			}

			auto n = new ListNode(sum);
			n->next = result;
			result = n;
		}

		while (!s1.empty()) {
			sum = carry + s1.top();
			s1.pop();

			if (sum >= 10) {
				sum = sum % 10;
				carry = 1;
			} else {
				carry = 0;
			}
			auto n = new ListNode(sum);
			n->next = result;
			result = n;
		}

		while (!s2.empty()) {
			sum = carry + s2.top();
			s2.pop();

			if (sum >= 10) {
				sum = sum % 10;
				carry = 1;
			}
			else {
				carry = 0;
			}
			auto n = new ListNode(sum);
			n->next = result;
			result = n;
		}

		if (carry) {
			auto n = new ListNode(carry);
			n->next = result;
			result = n;
		}

		return result;
	}

	//https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/description/
	ListNode* deleteDuplicates2(ListNode* head) {
		if (head == NULL) {
			return head;
		}

		ListNode *d = new ListNode(INT_MIN);
		d->next = head;

		auto t1 = head;
		auto prev = d;
		while (t1!=NULL) {
			auto count = 1;
			while (t1->next!= NULL && t1->val == t1->next->val) {
				t1 = t1->next;
				count++;
			}

			if (count > 1) {
				prev->next = t1->next;
				t1 = t1->next;
				continue;
			}
				
			prev = t1;
			t1 = t1->next;
		}

		return d->next;
	}

	//https://leetcode.com/problems/odd-even-linked-list/description/
	ListNode* oddEvenList(ListNode* head) {
		if (head == NULL) {
			return head;
		}

		auto odd = head;
		auto even = head->next;

		auto t1 = odd;
		auto t2 = even;

		while (t1 != NULL && t1->next!=NULL && t2 != NULL && t2->next!=NULL) {
			t1->next = t1->next->next;
			t2->next = t2->next->next;

			t1 = t1->next;
			t2 = t2->next;
		}

		t1->next = even;

		return odd;
	}

	//https://leetcode.com/problems/linked-list-components/description/
	int numComponents(ListNode* head, vector<int>& G) {
		ListNode *t = head;
		auto start = 0;
		auto result = 0;
		
		while (t != NULL) {
			//If the list element is not found in G
			if (std::find(G.begin(), G.end(), t->val)==G.end()) {
				if (start > 0) {
					result++;
				}
				t = t->next;
				start = 0;
				continue;
			}

			//If list element is found in G
			start++;
			t = t->next;
		}

		if (start > 0) result++;

		return result;
	}

	//https://leetcode.com/problems/swap-nodes-in-pairs/description/
	ListNode* swapPairs(ListNode* head) {
		if (head == NULL || head->next == NULL) {
			return head;
		}

		auto d = new ListNode(-1);
		auto t = head;
		auto prev = d;

		while (t!=NULL && t->next!=NULL) {
			auto np = t->next->next;
			prev->next = t->next;
			t->next->next = t;
			t->next = np;

			prev = t;
			t = t->next;
		}

		return d->next;
	}

	//https://leetcode.com/problems/reorder-list/description/
	void reorderList(ListNode* head) {
		if (head == NULL || head->next == NULL) {
			return;
		}

		auto slow = head;
		auto fast = head;
		auto prev = slow;
		auto d = new ListNode(-1);

		while (fast != NULL && fast->next != NULL) {
			prev = slow;
			slow = slow->next;
			fast = fast->next->next;
		}

		auto l1 = head;
		auto l2 = prev->next;		
		bool toggle = true;

		prev->next = NULL;

		l2 = reverseList(l2);
		d->next = l1;
		auto t1 = l1;
		auto t2 = l2;

		while (t1 != NULL && t2 != NULL) {
			if (toggle) {
				auto temp = t1;
				t1 = t1->next;
				temp->next = t2;
			} else {
				auto temp = t2;
				t2 = t2->next;
				temp->next = t1;
			}

			toggle = !toggle;
		}

		head = d->next;
	}

	//https://leetcode.com/problems/reverse-linked-list-ii/description/
	ListNode* reverseBetween(ListNode* head, int m, int n) {
		if (head->next == NULL || (m-n == 0)) {
			return head;
		}

		auto start = 1;
		auto t = head;
		auto prev = new ListNode(-1);
		prev->next = head;
		auto d = prev;

		while (start<m) {
			prev = t;
			t = t->next;
			start++;
		}

		auto sr = t;

		while (start < n) {
			t = t->next;
			start++;
		}

		auto ep = t->next;
		t->next = NULL;

		//sr(start reverse) points to the starting point to reverse and ep(end plus) points to the node after the ending point.
		//prev points to node before the sr.
		auto rev = reverseList(sr);
		prev->next = rev;
		sr->next = ep;

		return d->next;
	}

	//https://leetcode.com/problems/convert-sorted-list-to-binary-search-tree/description/
	TreeNode* sortedListToBST(ListNode* head) {
		if (head == NULL) {
			return NULL;
		}

		if (head->next == NULL) {
			return new TreeNode(head->val);
		}
		
		ListNode *slow = head;
		ListNode *fast = head;
		ListNode *prev = head;
		ListNode *left = head;

		while (fast != NULL && fast->next != NULL) {
			prev = slow;
			slow = slow->next;
			fast = fast->next->next;
		}

		ListNode * right = slow->next;
		prev->next = NULL;

		auto root = new TreeNode(slow->val);
		root->left = sortedListToBST(left);
		root->right = sortedListToBST(right);

		return root;
	}

	//https://leetcode.com/problems/sort-list/description/
	ListNode* sortList(ListNode* head) {
		if (head == NULL || head->next==NULL) {
			return head;
		}

		ListNode *slow = head;
		ListNode *fast = head;
		ListNode *prev = head;

		while (fast != NULL && fast->next != NULL) {
			prev = slow;
			slow = slow->next;
			fast = fast->next->next;
		}

		prev->next = NULL;

		ListNode *left = sortList(head);
		ListNode *right = sortList(slow);

		return mergeTwoLists(left, right);
	}

	//https://leetcode.com/problems/copy-list-with-random-pointer/description/
	RandomListNode *copyRandomList(RandomListNode *head) {
		if (head == NULL) {
			return head;
		}

		RandomListNode *c = head;
		RandomListNode *t = NULL;

		//Add a copy node after every node in the original list
		while (c != NULL) {
			t = c->next;
			c->next = new RandomListNode(c->label);
			c->next->next = t;
			c = t;
		}

		c = head;
		//At this point you have the copy nodes pointing to the next nodes but the random pointers are yet to be adjusted.
		while (c != NULL) {
			c->next->random = c->random? c->random->next: c->random;
			c = c->next ? c->next->next : c->next;
		}

		//Now, that you have the copy nodes pointing to their random nodes, seperate the copy nodes and original nodes
		c = head;
		RandomListNode *copy = c->next;
		RandomListNode *temp = copy;

		while (c&&temp) {
			c->next = c->next?c->next->next: c->next;
			temp->next = temp->next ? temp->next->next : temp->next;

			c = c->next;
			temp = temp->next;
		}

		return copy;
	}

	//https://leetcode.com/problems/reverse-nodes-in-k-group/description/
	ListNode* reverseKGroup(ListNode* head, int k) {
		if (!head) {
			return head;
		}

		ListNode *prev = new ListNode(-1);
		prev->next = head;
		ListNode *temp = head;
		ListNode *tempPrev = prev;

		int count = 0;

		while (temp) {			
			//Check if there are atleast k elements to be reversed.
			count = 0;
			ListNode *t = temp;
			while (t != NULL) {
				t = t->next;				

				if (++count >= k) {
					break;
				}
			}

			if (count < k) {
				break;
			}

			tempPrev->next = reverseBetween(temp, 1, k);
			tempPrev = temp;
			temp = temp->next;
		}

		return prev->next;
	}

	//https://leetcode.com/problems/merge-k-sorted-lists/description/
	ListNode* mergeKLists(vector<ListNode*>& lists) {
		if (lists.size() == 0) {
			return NULL;
		}

		ListNode *prev = new ListNode(-1);
		ListNode* t = prev;
		vector<ListNode*> v;

		for (auto &p:lists) {
			if(p!=NULL)
				v.push_back(p);
		}
		
		std::make_heap(v.begin(), v.end(), gheap());

		while (v.size() > 0) {
			//Get the front node/min valued node and point t->next to it.
			t->next = v.front();
			//Pop the front node
			std::pop_heap(v.begin(), v.end(), gheap());
			v.pop_back();

			//Now, move the t/result pointer
			t = t->next;
			//Add the next node from t.
			if (t != NULL && t->next!=NULL)
			{
				v.push_back(t->next);
				//Correct the heap
				std::push_heap(v.begin(), v.end(), gheap());
			}
		}

		return prev->next;
	}

	//https://leetcode.com/problems/split-linked-list-in-parts/description/
	vector<ListNode*> splitListToParts(ListNode* root, int k) {
		vector<ListNode*> r(k, NULL);
		if (k==1) {
			r.front() = root;
			return r;
		}

		//Calculate the size of the list
		auto t = root;
		auto size = 0;
		while (t!=NULL) {
			t = t->next;
			size++;
		}

		auto q_r = div(size, k);
		vector<int> l;
		auto sum = 0;
		while (0 < q_r.rem) {
			l.push_back(q_r.quot + 1);
			q_r.rem--;
			sum += q_r.quot + 1;
		}
		
		while (sum < size) {
			l.push_back(q_r.quot);
			sum+=q_r.quot;
		}
		//At this point 'l' has the lengths of the sub list
		t = root;
		auto count = 0;
		ListNode *prev = root;
		auto i = 0;
		for (auto &s:l) {
			count = 0;
			r[i] = t;
			//Remove the first s elements in the list
			while (count < s) {
				prev = t;
				t = t->next;
				count++;
			}

			prev->next = NULL;
			i++;
		}

		return r;
	}

	//https://leetcode.com/problems/plus-one-linked-list/description/
	ListNode* plusOne(ListNode* head) {
		if (head == NULL) {
			return head;
		}

		std::stack<ListNode*> s;
		ListNode *t = head;

		while (t != NULL) {
			s.push(t);
			t = t->next;
		}

		while (!s.empty()) {
			ListNode *n = s.top();
			s.pop();
			if (n->val < 9) {
				n->val++;
				return head;
			} else {
				n->val = 0;
			}
		}

		ListNode *l = new ListNode(1);
		l->next = head;
		return l;
	}
/************************************LINKED_LIST************************************/

/************************************BINARY_SEARCH************************************/
	int search(vector<int>& nums, int target) {
		if (nums.empty()) {
			return -1;
		}

		int start = 0;
		size_t end = nums.size() - 1;
		int mid = 0;

		while (start <= end) {
			mid = (start + end) / 2;

			if (nums[mid] > target) {
				end = mid - 1;
			}
			else if (nums[mid] < target) {
				start = mid + 1;
			} else {
				return mid;
			}
		}

		return -1;
	}
/************************************BINARY_SEARCH************************************/

/************************************STRING************************************/
	string reverseString(string s) {
		if (s.length() == 0) {
			return s;
		}

		int start = 0;
		int end = s.length() - 1;

		while (start <= end) {
			char t = s[start];
			s[start] = s[end];
			s[end] = t;

			start++;
			end--;
		}

		return s;
	}
/************************************STRING************************************/

/***********************************HEAPS***********************************/
	//https://leetcode.com/problems/kth-largest-element-in-an-array/
	int findKthLargest(vector<int>& nums, int k) {
		std::make_heap(std::begin(nums), std::end(nums));

		auto kthlargest = nums[0];
		while (k>0) {
			kthlargest = nums.front();
			std::pop_heap(std::begin(nums), std::end(nums));
			nums.pop_back();
			k--;
		}

		return kthlargest;
	}

	//https://leetcode.com/problems/top-k-frequent-elements/description/
	vector<int> topKFrequent(vector<int>& nums, int k) {
		vector<int> result;
		if (nums.size() == 0) {
			return result;
		}

		std::unordered_map<int, int> m;

		//Create a frequency map
		for(auto &v:nums) {
			m[v]++;
		}

		//Copy the element->frequency map onto a vector of pairs
		vector<pair<int, int>> v;
		for (auto const &k : m) {
			pair<int, int> p = { k.first, k.second };
			v.push_back(p);
		}

		//Create a heap of pairs
		std::make_heap(std::begin(v), std::end(v), pHeap());

		while (k>0) {
			result.push_back(v.front().first);
			std::pop_heap(std::begin(v), std::end(v), pHeap());
			v.pop_back();
			k--;
		}

		return result;
	}

	//https://leetcode.com/problems/find-k-pairs-with-smallest-sums/description/
	vector<pair<int, int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
		if (!nums1.size() || !nums2.size()) {
			return {};
		}

		vector<pair<int, int>> result;
		vector<pair<int, int>> q;
		for (auto &i:nums1) {
			for (auto &j:nums2) {
				q.push_back({i, j});	
			}
		}

		std::make_heap(q.begin(), q.end(), sHeap());

		while (k-- && !q.empty()) {
			result.push_back(q.front());
			std::pop_heap(q.begin(), q.end(), sHeap());
			q.pop_back();
		}

		return result;
	}

	//https://leetcode.com/problems/top-k-frequent-words/description/
	vector<string> topKFrequentWords(vector<string>& words, int k) {
		std::unordered_map<string, int> m;

		for (auto &s : words) m[s]++;

		vector<pair<string, int>> p;

		for (auto &k: m) p.push_back({k.first, k.second});

		//Create a heap of 'p' pairs
		std::make_heap(p.begin(), p.end(), wHeap());

		vector<string> result;
		while (k>0) {			
			result.push_back(p.front().first);
			std::pop_heap(p.begin(), p.end(), wHeap());
			p.pop_back();
			k--;
		}

		return result;
	}

	//https://leetcode.com/problems/find-k-th-smallest-pair-distance/description/
	int smallestDistancePair(vector<int>& nums, int k) {
		std::sort(nums.begin(), nums.end());
		const size_t n = nums.size();

		//Get the min and max difference between pairs
		int low = 0;
		int high = nums.back() - nums.front();

		while (low<=high) {
			int mid = (low + high) / 2;

			//Get the count of all pairs whose difference is less than or equal to mid
			int j = 0;
			int count = 0;
			for (int i = 0;i < n;i++) {
				while (j < n && nums[j] - nums[i] <= mid) j++;
				count += j - i - 1;
			}

			if (count < k)
				low = mid + 1;
			else
				high = mid - 1;
		}

		return low;
	}

	//https://leetcode.com/problems/sort-characters-by-frequency/description/
	string frequencySort(string s) {
		if (s.empty()) {
			return "";
		}
		
		std::vector<pair<char, int>> f;
		std::unordered_map<char, int> m;
		for (char &s: s) {
			m[s]++;
		}

		for (std::pair<char, int> e : m) {
			f.emplace_back(e);
		}

		//Now, you have a vector of, pairs of a char and it's frequency. Create a heap.
		std::make_heap(f.begin(), f.end(), fHeap());
		size_t n = f.size();
		string result = "";
		while(n>0) {
			pair<char, int> p = f.front();
			std::pop_heap(f.begin(), f.end(), fHeap());
			f.pop_back();

			for (int i = 0; i < p.second;i++) {
				result += p.first;
			}
			n--;
		}

		return result;
	}

	//https://leetcode.com/problems/reorganize-string/description/
	string reorganizeString(string S) {
		if (S.empty()) {
			return "";
		}

		//Create a frquency map
		std::unordered_map<char, int> m;
		for (auto &c : S) m[c]++;

		//Create a list of pairs in m
		vector<pair<char, int>> v;
		for (auto &p : m) v.emplace_back(p);

		std::make_heap(v.begin(), v.end(), rHeap());

		string result = "";
		for (auto &c : S) {
			auto top = v.front();
			std::pop_heap(v.begin(), v.end(), rHeap());
			v.pop_back();

			if (result.back() != top.first) {				
				result.push_back(top.first);
				if (--top.second) {
					v.emplace_back(top);
					std::push_heap(v.begin(), v.end(), rHeap());
				}
			} else {										//If it is same as the last letter in S
				//Get the next element in the heap
				if (v.empty()) return "";

				//Pop one more which is guaranteed to be different from the last
				auto top2 = v.front();
				std::pop_heap(v.begin(), v.end(), rHeap());
				v.pop_back();

				result.push_back(top2.first);

				//Push back the popped elements
				v.emplace_back(top);
				std::push_heap(v.begin(), v.end(), rHeap());
				//Push top2 after decrementing the counter
				if (--top2.second) {
					v.emplace_back(top2);
					std::push_heap(v.begin(), v.end(), rHeap());
				}
			}
		}

		return result;
	}

	//https://leetcode.com/problems/sliding-window-maximum/description/
	vector<int> maxSlidingWindow(vector<int>& nums, int k) {
		list<pair<int, int>> ls;
		vector<int> ret(nums.size() ? nums.size() - k + 1 : 0, 0);
		for (int i = 0; i < nums.size(); i++) {
			while (!ls.empty() && ls.rbegin()->first <= nums[i])
				ls.pop_back();
			ls.push_back({ nums[i], i });
			while (ls.begin()->second + k <= i)
				ls.pop_front();
			if (i < k - 1) continue;
			ret[i - k + 1] = ls.begin()->first;
		}
		return ret;
	}

/***********************************HEAPS***********************************/
/***********************************BINARY TREES***********************************/
	TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {
		if (!t1 || !t2) {
			return t1 ? t1 : t2;
		}

		t1->val += t2->val;
		t1->left = mergeTrees(t1->left, t2->left);		
		t1->right = mergeTrees(t1->right, t2->right);

		return t1;
	}

	//https://leetcode.com/problems/leaf-similar-trees/description/
	bool leafSimilar(TreeNode* root1, TreeNode* root2) {
		vector<int> l1;
		vector<int> l2;

		getLeaves(l1, root1);
		getLeaves(l2, root2);

		return l1 == l2;
	}

	void getLeaves(vector<int> &r, TreeNode *n) {
		if (!n) {
			return;
		}

		getLeaves(r, n->left);
		getLeaves(r, n->right);

		if (!n->left && !n->right) {
			r.push_back(n->val);
		}
	}

	//https://leetcode.com/problems/trim-a-binary-search-tree/description/
	TreeNode* trimBST(TreeNode* root, int L, int R) {
		if (!root) {
			return NULL;
		}

		if (root->val < L) {
			return trimBST(root->right, L, R);
		} else if (root->val > R) {
			return trimBST(root->left, L, R);
		} else {
			root->left = trimBST(root->left, L, R);
			root->right = trimBST(root->right, L, R);
		}

		return root;
	}

	//https://leetcode.com/problems/maximum-depth-of-binary-tree/description/
	int maxDepth(TreeNode* root) {
		if (!root) {
			return 0;
		}

		return 1 + max(maxDepth(root->left), maxDepth(root->right));
	}

	//https://leetcode.com/problems/search-in-a-binary-search-tree/description/
	TreeNode* searchBST(TreeNode* root, int val) {
		if (!root) {
			return NULL;
		}

		if (val > root->val) {
			return searchBST(root->right, val);
		}
		
		if (val < root->val){
			return searchBST(root->left, val);
		}

		return root;
	}

	//https://leetcode.com/problems/same-tree/description/
	bool isSameTree(TreeNode* p, TreeNode* q) {
		return (!p && !q) || (p && q && (p->val == q->val) && isSameTree(p->left, q->left) && isSameTree(p->right, q->right));
	}

	//https://leetcode.com/problems/count-complete-tree-nodes/description/
	int countNodes(TreeNode* root) {
		if (!root) 
			return 0;

		int hl = 0, hr = 0;
		TreeNode *l = root, *r = root;
		while (l) { 
			hl++;
			l = l->left; 
		}
		while (r) { 
			hr++;
			r = r->right; 
		}
		if (hl == hr) 
			return pow(2, hl) - 1;

		return 1 + countNodes(root->left) + countNodes(root->right);
	}

	//Iterative solution for the above problem
	int countNodes2(TreeNode* root) {
		if (!root) {
			return 0;
		}

		std::queue<TreeNode*> q;
		int count = 0;
		q.push(root);
		while (!q.empty()) {
			TreeNode *e = q.front();
			q.pop();

			count++;

			if (e->left) {
				q.push(e->left);
			}

			if (e->right) {
				q.push(e->right);
			}
		}

		return count;
	}

	//https://leetcode.com/problems/symmetric-tree/description/
	bool isSymmetric(TreeNode* root) {
		if (!root) return true;
		return isSymmetricHelper(root, root);
	}

	bool isSymmetricHelper(TreeNode* root1, TreeNode *root2) {
		return (!root1 && !root2) || 
			   (root1 && root2 && (root1->val == root2->val) && isSymmetricHelper(root1->left, root2->right) && isSymmetricHelper(root1->right, root2->left));
	}

	//https://leetcode.com/problems/sum-of-left-leaves/description/
	int sumOfLeftLeaves(TreeNode* root) {
		if (!root) return 0;
		return sumOfLeftLeavesHelper(root, false);
	}

	int sumOfLeftLeavesHelper(TreeNode *r, bool isLeft) {
		if (!r) return 0;
		
		if (isLeft && !r->left && !r->right) {
			return r->val;
		}
		return sumOfLeftLeavesHelper(r->left, true) + sumOfLeftLeavesHelper(r->right, false);
	}

	//https://leetcode.com/problems/average-of-levels-in-binary-tree/description/
	vector<double> averageOfLevels(TreeNode* root) {
		if (!root) {
			return {};
		}

		std::queue<TreeNode *> q;
		q.push(root);
		auto last = root;
		vector<int> lvl;
		double sum = 0;
		vector<double> r;

		while (!q.empty()) {
			auto f = q.front();
			q.pop();

			lvl.push_back(f->val);

			if (f->left) q.push(f->left);
			if (f->right) q.push(f->right);

			if (f == last) {
				sum = 0;
				last = q.back();

				//Calculate average
				sum = std::accumulate(lvl.begin(), lvl.end(), 0.0);
				r.push_back(sum / lvl.size());

				lvl.clear();
			}
		}

		return r;
	}

	//https://leetcode.com/problems/two-sum-iv-input-is-a-bst/description/
	bool findTarget(TreeNode* root, int k) {
		findTargetHelper(root);
		if (!inOrderList.empty()) {
			int i = 0, j = inOrderList.size()-1;
			while(i < j) {
				if (inOrderList[i] + inOrderList[j] < k) i++;
				else if (inOrderList[i] + inOrderList[j] > k) j--;
				else return true;
			}
		}

		return false;
	}

	void findTargetHelper(TreeNode *root) {
		if (!root) return;

		findTargetHelper(root->left);
		inOrderList.push_back(root->val);
		findTargetHelper(root->right);
	}

	//https://leetcode.com/problems/path-sum/description/
	bool hasPathSum(TreeNode* root, int sum) {
		if (!root) {
			return false;
		}

		if (!root->left && !root->right && (sum - root->val == 0)) {
			return true;
		}

		return hasPathSum(root->left, sum-root->val) || hasPathSum(root->right, sum-root->val);
	}

	//https://leetcode.com/problems/diameter-of-binary-tree/description/
	int diameterOfBinaryTree(TreeNode* root) {
		if (!root) return 0;

		int lh = getHeight(root->left);
		int rh = getHeight(root->right);

		int ld = diameterOfBinaryTree(root->left);
		int rd = diameterOfBinaryTree(root->right);

		return max(lh+rh, max(ld, rd));
	}

	int getHeight(TreeNode *n) {
		if (!n) return 0;

		return 1 + max(getHeight(n->left), getHeight(n->right));
	}

	//https://leetcode.com/problems/minimum-depth-of-binary-tree/description/
	int minDepth(TreeNode* root) {
		if (!root) return 0;
		int m = INT_MAX;
		
		minDepthHelper(root, 0, m);

		return m;
	}

	void minDepthHelper(TreeNode *r, int nodes, int &m) {
		if (!r) return;

		if (!r->left && !r->right) {
			m = min(m, 1 + nodes);
		}

		minDepthHelper(r->left, nodes + 1, m);
		minDepthHelper(r->right, nodes + 1, m);
	}

	//https://leetcode.com/problems/binary-tree-level-order-traversal/description/
	vector<vector<int>> levelOrder(TreeNode* root) {		
		if (!root) return {};
		vector<vector<int>> result;

		std::queue<TreeNode*> q;
		TreeNode *last = root;
		q.push(root);
		vector<int> lvl;

		while (!q.empty()) {
			TreeNode *f = q.front();
			q.pop();

			lvl.push_back(f->val);

			if (f->left) q.push(f->left);
			if (f->right) q.push(f->right);

			if (f == last) {
				last = q.back();
				result.push_back(lvl);
				lvl.clear();
			}
		}

		return result;
	}

	//https://leetcode.com/problems/binary-tree-level-order-traversal-ii/description/
	vector<vector<int>> levelOrder2(TreeNode* root) {
		if (!root) return {};
		vector<vector<int>> result;

		std::queue<TreeNode*> q;
		TreeNode *last = root;
		q.push(root);
		vector<int> lvl;

		while (!q.empty()) {
			TreeNode *f = q.front();
			q.pop();

			lvl.push_back(f->val);

			if (f->left) q.push(f->left);
			if (f->right) q.push(f->right);

			if (f == last) {
				last = q.back();
				result.push_back(lvl);
				lvl.clear();
			}
		}

		std::reverse(result.begin(), result.end());
		return result;
	}

	//https://leetcode.com/problems/subtree-of-another-tree/description/
	bool isSubtree(TreeNode* s, TreeNode* t) {
		if (!t) return true;
		if (!s) return false;

		return areIdentical(s, t) || isSubtree(s->left, t) || isSubtree(s->right, t);
	}

	bool areIdentical(TreeNode *s, TreeNode *t) {
		if (!s && !t) return true;
		if (!s || !t) return false;

		return s->val == t->val && areIdentical(s->left, t->left) && areIdentical(s->right, t->right);
	}

	//https://leetcode.com/problems/binary-tree-paths/description/
	vector<string> binaryTreePaths(TreeNode* root) {
		vector<string> paths;
		binaryTreePathsHelper(root, "", paths);
		return paths;
	}

	void binaryTreePathsHelper(TreeNode* r, string path, vector<string> &paths) {
		if (!r) return;

		if (!r->left && !r->right) {
			path += std::to_string(r->val);
			paths.push_back(path);
		}

		binaryTreePathsHelper(r->left, path + std::to_string(r->val) + "->", paths);
		binaryTreePathsHelper(r->right, path + std::to_string(r->val) + "->", paths);
	}

	//https://leetcode.com/problems/path-sum-iii/description/
	int pathSum(TreeNode* root, int sum) {
		if (!root) return 0;

		pathRecur(root, sum);

		return pathSum_Paths;
	}

	void pathRecur(TreeNode *root, int sum) {
		if (!root) return;

		pathSumHelper(root, sum);
		pathRecur(root->left, sum);
		pathRecur(root->right, sum);
	}

	void pathSumHelper(TreeNode *r, int sum) {
		if (!r) return;

		if (r->val == sum) pathSum_Paths++;

		pathSumHelper(r->left, sum - r->val);
		pathSumHelper(r->right, sum - r->val);
	}

	//https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/description/
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
		if (!root) return root;

		if(root->val > p->val && root->val > q->val) return lowestCommonAncestor(root->left, p, q);
		if(root->val < p->val && root->val < q->val) return lowestCommonAncestor(root->right, p, q);

		return root;
	}

	//https://leetcode.com/problems/second-minimum-node-in-a-binary-tree/description/
	int findSecondMinimumValue(TreeNode* root) {
		firstMin = root->val;
		findSecondMinimumValueHelper(root);
		return (secondMin == INT_MAX) ? -1 : secondMin;
	}

	void findSecondMinimumValueHelper(TreeNode *r) {
		if (!r) return;

		if (r->val > firstMin) {
			secondMin = min(secondMin, r->val);
		}

		findSecondMinimumValueHelper(r->left);
		findSecondMinimumValueHelper(r->right);
	}

	//https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/description/
	TreeNode* lowestCommonAncestor2(TreeNode* root, TreeNode* p, TreeNode* q) {
		if (!root) return root;

		if (root->val == p->val || root->val == q->val) return root;

		auto left = lowestCommonAncestor(root->left, p, q);
		auto right = lowestCommonAncestor(root->right, p, q);

		if (left && right) return root;

		return left ? left : right;
	}

	//https://leetcode.com/problems/insert-into-a-binary-search-tree/description/
	TreeNode* insertIntoBST(TreeNode* root, int val) {
		if (!root) return root;
		insertIntoBSTHelper(root, val);
		return root;
	}

	TreeNode* insertIntoBSTHelper(TreeNode* root, int val) {
		if (!root) return new TreeNode(val);
		if (val > root->val) root->right = insertIntoBSTHelper(root->right, val);
		if (val < root->val) root->left = insertIntoBSTHelper(root->left, val);

		return root;
	}

	//https://leetcode.com/problems/balanced-binary-tree/description/
	bool isBalanced(TreeNode* root) {
		if (!root) return true;

		return isBalancedHelper(root);
	}

	bool isBalancedHelper(TreeNode* r) {
		if (!r) return true;

		auto lh = getHeight(r->left);
		auto rh = getHeight(r->right);

		if (abs(lh - rh) > 1) {
			return false;
		}

		return isBalancedHelper(r->left) && isBalancedHelper(r->right);
	}

	//https://leetcode.com/problems/find-bottom-left-tree-value/description/
	int findBottomLeftValue(TreeNode* root) {
		std::queue<TreeNode*> q;
		q.push(root);
		vector<int> lvl;
		TreeNode *last = root;
		int r;

		while (!q.empty()) {
			auto f = q.front();
			q.pop();
			lvl.push_back(f->val);

			if (f->left) q.push(f->left);
			if (f->right) q.push(f->right);

			if (f == last) {
				r = lvl[0];
				last = q.back();
				lvl.clear();
			}
		}

		return r;
	}

	//https://leetcode.com/problems/binary-tree-preorder-traversal/description/
	vector<int> preorderTraversal(TreeNode* root) {
		if (!root) return {};

		std::stack<TreeNode*> s;
		s.push(root);
		vector<int> r;

		while (!s.empty()) {
			auto top = s.top();
			s.pop();
			r.push_back(top->val);

			if (top->right) s.push(top->right);
			if (top->left) s.push(top->left);
		}

		return r;
	}

	//https://leetcode.com/problems/sum-root-to-leaf-numbers/description/
	int sumNumbers(TreeNode* root) {
		if (!root) return 0;
		vector<int> sum;
		sumNumbersHelper(root, 0, sum);
		return std::accumulate(sum.begin(), sum.end(), 0);
	}

	void sumNumbersHelper(TreeNode *r, int prev, vector<int> &sum) {
		if (!r) return;

		if (!r->left && !r->right) {
			auto s = prev * 10 + r->val;
			sum.push_back(s);
		}

		sumNumbersHelper(r->left, (prev * 10) + r->val, sum);
		sumNumbersHelper(r->right, (prev * 10) + r->val, sum);
	}

	//https://leetcode.com/problems/validate-binary-search-tree/description/
	bool isValidBST(TreeNode* root) {
		return isValidBST(root, LONG_MIN, LONG_MAX);
	}

	bool isValidBST(TreeNode* root, long min, long max) {
		if (!root) return true;
		if (root->val <= min || root->val >= max) return false;

		return isValidBST(root->left, min, root->val) && isValidBST(root->right, root->val, max);
	}

	//https://leetcode.com/problems/longest-univalue-path/description/
	int longestUnivaluePath(TreeNode* root) {
		if (!root) return 0;
		int len = 0;
		longestUnivaluePathHelper(root, INT_MIN, len);
		return len;
	}

	int longestUnivaluePathHelper(TreeNode *n, int prev, int &len) {
		if (!n) return 0;

		int l = longestUnivaluePathHelper(n->left, n->val, len);
		int r = longestUnivaluePathHelper(n->right, n->val, len);

		len = max(len, l + r);

		int count = 0;
		if (n->val == prev) {
			count = 1 + max(l, r);
		}

		return count;
	}

	//https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/description/
	vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
		if (!root) return {};

		auto last = root;
		bool reverse = false;
		vector<vector<int>> result;
		std::queue<TreeNode*> q;
		std::vector<int> lvl;
		q.push(root);

		while (!q.empty()) {
			auto f = q.front();
			q.pop();
			lvl.push_back(f->val);

			if (f->left) q.push(f->left);
			if (f->right) q.push(f->right);

			if (f == last) {
				last = q.back();
				if (reverse) std::reverse(lvl.begin(), lvl.end());
				result.push_back(lvl);
				lvl.clear();
				reverse = !reverse;
			}
		}

		return result;
	}

	//https://leetcode.com/problems/binary-tree-right-side-view/description/
	vector<int> rightSideView(TreeNode* root) {
		if (!root) return {};

		std::queue<TreeNode*> q;
		q.push(root);
		TreeNode *last = root;
		vector<int> lvl;
		vector<int> result;

		while (!q.empty()) {
			TreeNode *f = q.front();
			q.pop();
			lvl.push_back(f->val);

			if (f->left) q.push(f->left);
			if (f->right) q.push(f->right);

			if (f == last) {
				last = q.back();
				result.push_back(lvl.back());
				lvl.clear();
			}
		}

		return result;
	}

	//https://leetcode.com/problems/n-ary-tree-level-order-traversal/description/
	vector<vector<int>> levelOrder(Node* root) {
		if (!root) return {};

		std::queue<Node*> q;
		Node *last = root;
		q.push(root);
		vector<int> lvl;
		vector<vector<int>> result;

		while (!q.empty()) {
			Node *f = q.front();
			q.pop();
			lvl.push_back(f->val);

			for (Node *c : f->children) {
				q.push(c);
			}

			if (last == f) {
				last = q.back();
				result.push_back(lvl);
				lvl.clear();
			}
		}

		return result;
	}

	//https://leetcode.com/problems/maximum-depth-of-n-ary-tree/description/
	int maxDepth2(Node* root) {
		if (!root) return 0;

		int depth = 0;
		for (Node *c : root->children) {
			depth = max(depth, maxDepth2(c));
		}

		return depth++;
	}

	//https://leetcode.com/problems/n-ary-tree-preorder-traversal/description/
	vector<int> preorder2(Node* root) {
		if (!root) return {};

		std::stack<Node*> s;
		s.push(root);
		vector<int> result;

		while (!s.empty()) {
			Node *t = s.top();
			s.pop();
			result.push_back(t->val);

			vector<Node*>::reverse_iterator r = t->children.rbegin();
			for (;r != t->children.rend(); r++) {
				s.push(*r);
			}
		}

		return result;
	}

	//https://leetcode.com/tag/tree/
	int kthSmallest(TreeNode* root, int k) {
		return kthSmallestHelper(root, k);
	}

	int kthSmallestHelper(TreeNode *root, int &k) {		
		if (!root) return -1;
		int x = kthSmallestHelper(root->left, k);
		
		if (k) {
			k--;
			if (!k) return root->val;
		} else return x;

		return kthSmallestHelper(root->right, k);
	}

	//https://leetcode.com/problems/add-one-row-to-tree/description/
	TreeNode* addOneRow(TreeNode* root, int v, int d) {
		if (d == 1) {
			TreeNode *r = new TreeNode(v);
			r->left = root;
			return r;
		}

		std::queue<TreeNode*> q;
		q.push(root);
		vector<TreeNode*> lvl;
		TreeNode *last = root;
		int depth = 0;

		while (!q.empty()) {
			TreeNode *f = q.front();	
			q.pop();
			lvl.push_back(f);

			if (f->left) q.push(f->left);
			if (f->right) q.push(f->right);

			if (last == f) {
				last = q.size() ? q.back() : NULL;
				depth++;
				if (depth == d - 1) {
					for (TreeNode *l:lvl) {
						TreeNode *t = l->left;
						TreeNode *n = new TreeNode(v);
						n->left = t;
						l->left = n;

						t = l->right;
						n = new TreeNode(v);
						n->right = t;
						l->right = n;
					}
					break;
				}
				lvl.clear();
			}
		}

		return root;
	}

	//https://leetcode.com/problems/find-largest-value-in-each-tree-row/description/
	vector<int> largestValues(TreeNode* root) {
		if (!root) return {};

		std::queue<TreeNode *> q;
		q.push(root);
		TreeNode *last = root;
		vector<int> lvl;
		vector<int> r;

		while (!q.empty()) {
			TreeNode *f = q.front();
			q.pop();
			lvl.push_back(f->val);

			if (f->left) q.push(f->left);
			if (f->right) q.push(f->right);

			if (last == f) {
				last = q.back();
				std::make_heap(lvl.begin(), lvl.end());
				r.push_back(lvl.front());
				lvl.clear();
			}
		}

		return r;
	}

	//https://leetcode.com/problems/all-nodes-distance-k-in-binary-tree/description/
	vector<int> distanceK(TreeNode* root, TreeNode* target, int K) {

	}
/***********************************BINARY TREES***********************************/
};

//https://leetcode.com/problems/kth-largest-element-in-a-stream/description/
class KthLargest {
private:
	std::priority_queue<int, vector<int>> pq;
	int kth;

public:
	KthLargest(int k, vector<int> nums) {		
		kth = k;		
		for (auto &i: nums) {
			pq.push(i);
			if (pq.size() > kth) pq.pop();
		}
	}

	int add(int val) {
		pq.push(val);
		if (pq.size() > kth) pq.pop();

		return pq.top();
	}
};

//https://leetcode.com/problems/binary-search-tree-iterator/description/
class BSTIterator {
private:
	std::stack<int> s;
	TreeNode *root;

	void reverseInOrder(TreeNode *r) {
		if (!r) return;
		reverseInOrder(r->right);
		s.push(r->val);
		reverseInOrder(r->left);
	}

public:
	BSTIterator(TreeNode *root) {
		//Initialize the root of the BST and the stack
		this->root = root;				
		reverseInOrder(root);
	}

	/** @return whether we have a next smallest number */
	bool hasNext() {
		return !s.empty();
	}

	/** @return the next smallest number */
	int next() {
		int r = s.top();
		s.pop();
		return r;
	}
};

int main() {
	Solution s;

	TreeNode *n = new TreeNode(1);
	n->left = new TreeNode(2);
	n->right = new TreeNode(3);
	n->left->left = new TreeNode(4);

	s.addOneRow(n, 5, 4);

	return 0;
}