#include <stdlib.h>
#include <set>
#include <iostream>

using namespace std;

struct ListNode {
	int value;
	ListNode * next;
};

bool hasLoops(ListNode * myList) {
	set<ListNode*> addresses;

	int count = 0;

	ListNode *current = myList;

	while (current) {
		addresses.insert(current);
		count += 1;

		if (addresses.size() != count) {
			return true;
		}

		current = current->next;
	}

	return false;
}

int main() {
	ListNode *l1, *l2, *l3, *l4, *l5;
	l1 = new ListNode;
	l2 = new ListNode;
	l3 = new ListNode;

	l1->value = 1;
	l2->value = 2;
	l3->value = 3;

	l1->next = l2;
	l2->next = l3;
	l3->next = l1;

	cout << hasLoops(l1) << endl;

	return EXIT_SUCCESS;
}
