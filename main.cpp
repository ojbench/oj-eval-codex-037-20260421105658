// Problem 037 - 双链表，启动！
// Implement a doubly linked list supporting operations described in README.

#include <bits/stdc++.h>
#include <iostream>
using namespace std;

namespace DoubleLinkList {

struct NODE {
    int data{};
    NODE *next{nullptr};
    NODE *pre{nullptr};
    NODE() {}
    NODE(int val) { this->data = val; }
};

static NODE *head = nullptr, *tail = nullptr;
static int len = 0;

void Pre() {
    head = new NODE();
    tail = new NODE();
    head->pre = NULL;
    tail->next = NULL;
    head->next = tail;
    tail->pre = head;
}

// Move to the real node at position i (0-based) in the list (not counting sentinels).
// Assumes 0 <= i < len.
NODE *move(int i) {
    NODE *cur = head;
    for (int j = 0; j <= i; j++) {
        cur = cur->next;
    }
    return cur;
}

void insert(int i, int x) {
    // Insert value x so that it becomes the element at position i.
    // Valid i ranges from 0..len.
    // When i == len, we append before tail sentinel.
    NODE *pos;
    if (i == len) {
        pos = tail; // insert before tail
    } else {
        pos = move(i); // existing node at position i
    }
    NODE *node = new NODE(x);
    NODE *prev = pos->pre;
    node->next = pos;
    node->pre = prev;
    prev->next = node;
    pos->pre = node;
    ++len;
}

void remove(int i) {
    // Remove node at position i (0-based). Assumes 0 <= i < len.
    NODE *cur = move(i);
    NODE *p = cur->pre;
    NODE *n = cur->next;
    p->next = n;
    n->pre = p;
    delete cur;
    --len;
}

int Get_length() { return len; }

int Query(int i) {
    if (i < 0 || i >= len) return -1;
    return move(i)->data;
}

void Print() {
    if (len == 0) {
        cout << -1 << '\n';
        return;
    }
    NODE *cur = head->next;
    for (int idx = 0; idx < len; ++idx) {
        if (idx) cout << ' ';
        cout << cur->data;
        cur = cur->next;
    }
    cout << '\n';
}

void Clear() {
    // Delete all nodes including sentinels; after Clear, list is empty.
    NODE *cur = head;
    while (cur) {
        NODE *nxt = cur->next;
        delete cur;
        cur = nxt;
    }
    head = tail = nullptr;
    len = 0;
}

} // namespace DoubleLinkList

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;
    int op, x, p, ans;
    DoubleLinkList::Pre();
    for (int _ = 0; _ < n; ++_) {
        cin >> op;
        switch (op) {
        case 0:
            ans = DoubleLinkList::Get_length();
            cout << ans << '\n';
            break;
        case 1:
            cin >> p >> x;
            DoubleLinkList::insert(p, x);
            break;
        case 2:
            cin >> p;
            ans = DoubleLinkList::Query(p);
            cout << ans << '\n';
            break;
        case 3:
            cin >> p;
            DoubleLinkList::remove(p);
            break;
        case 4:
            DoubleLinkList::Print();
            break;
        default:
            // ignore unknown ops
            break;
        }
    }
    DoubleLinkList::Clear();
    return 0;
}

