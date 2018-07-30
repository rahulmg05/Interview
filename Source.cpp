#include<iostream>
#include<array>
#include<memory>
using namespace std;

//Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
private :
	ListNode * head;

public:
	Solution() {
		head = NULL;
	}

	//Adds a node to the list
	void addNode(int val) {
		if (head == NULL) {
			head = new ListNode(val);
		} else {
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

		while (slow != NULL && fast != NULL && fast->next!=NULL) {
			slow = slow->next;
			fast = fast->next->next;
		}

		return slow;
	}

	//https://leetcode.com/problems/delete-node-in-a-linked-list/description/
	void deleteNode(ListNode* node) {
		auto prev = node;
		while (node!=NULL && node->next!=NULL){
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
		while (temp!=NULL) {
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
		while (temp!=NULL && temp->val == val) {
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
		while (t1!=NULL && t2!=NULL){
			if (t1->val < t2->val) {
				p->next = t1;
				t1 = t1->next;
			} else {
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

		while (slow!=NULL && fast!=NULL && fast->next!=NULL) {
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
		for (int i = 0;i < mid-1;i++) {
			t = t->next;
		}

		auto s = head;

		if (len % 2 == 0) {
			s = t->next;
		} else {
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
};

int main() {
	Solution s;
	s.addNode(1);
	s.addNode(2);
	s.addNode(2);
	s.addNode(1);

	cout << s.isPalindrome(s.getHead()) << endl;

	return 0;
}