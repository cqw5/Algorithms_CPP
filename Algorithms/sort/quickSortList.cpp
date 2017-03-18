/*! Author: qwchen
 *! Date: 2017-03-18
 *! 链表的快速排序
 *  思路：
 *    对一个链表，以第一个结点head作为key，然后遍历链表：
 *    <=key的作为一个链表L1，>key的作为一个链表L2
 *    递归的将两个链表L1 L2排序，然后L1->head->L2
 *  时间复杂度：O(nlogn)
 *  空间复杂度：O(1)
 */

#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int theVal): val(theVal), next(nullptr) {}
    ListNode(int theVal, ListNode* theNext): val(theVal), next(theNext) {}
};

// 使用引用指针
void sort(ListNode* &head, ListNode* &end) {
    if (head == nullptr) return;
    ListNode head1(0),       // <= key的链表的头结点，注意是头结点，不是首节点，设置头结点为了简化代码
             head2(0),       // > key的链表的头结点
             *end1 = &head1, // <= key的链表的尾结点
             *end2 = &head2; // > key的链表的尾结点
    // 将首节点孤立出来
    int key = head->val;
    ListNode* p = head->next;
    head->next = nullptr;
    // 获得元素都<=key的链表和元素都>key的链表
    while (p !=nullptr) {  // 注意每次会把前面end结点的next结点置为nullptr
        if (p->val <= key) {
            end1->next = p;
            end1 = end1->next;
        }
        else {
            end2->next = p;
            end2 = end2->next;
        }
        p = p->next;
    }
    end1->next = nullptr;
    end2->next = nullptr;
    // 对左右两个链表递归排序
    sort(head1.next, end1);
    sort(head2.next, end2);
    // 连接：左链表->head->右链表，重新设置head和end指针
    // 如果左右两个链表都存在
    if (end1 && head2.next) {
        end1->next = head;
        head->next = head2.next;
        head = head1.next;
        end = end2;    
    }
    // 如果只有左链表，而右链表不存在
    else if (end1) {
        end1->next = head;
        end = head;
        head = head1.next;
    }
    // 如果只有右链表，而左链表不存在
    else if (head2.next) {
        head->next = head2.next;
        end = end2;
    }
}

void quickSort(ListNode* &head) {
    if (head != nullptr) {
        ListNode* end = head;
        while (end->next != nullptr) {
            end = end->next;
        }
        sort(head, end);
    }
}

int main() {
    // 10, 4, 2, 9, 5
    ListNode* p4 = new ListNode(5);
    ListNode* p3 = new ListNode(9, p4);
    ListNode* p2 = new ListNode(2, p3);
    ListNode* p1 = new ListNode(4, p2);
    ListNode* head = new ListNode(10, p1);
    for (ListNode* p = head; p != nullptr; p = p->next) {
        cout << p->val << " ";
    }
    cout << endl;
    quickSort(head);
    for (ListNode* p = head; p != nullptr; p = p->next) {
        cout << p->val << " ";
    }
    cout << endl;    
}

