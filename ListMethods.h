#pragma once
#include <array>
class ListMethods {
private:
    struct ForwardListNode {
        int val;
        ForwardListNode* next;
        ForwardListNode(int x) : val(x), next(nullptr) { ; }
    };
    struct ListNode {
        int val;
        ListNode* next;
        ListNode* pre;
        ListNode(int x, ListNode* pre) : val(x), next(pre->next), pre(pre) {
            pre->next = this;
            if (this->next != nullptr)
                this->next->pre = this;
        }
    };
public:
    static ForwardListNode* reverseForwardListRecursive(ForwardListNode* head)
    {
        return reverseForward(nullptr, head);
    }
    static ForwardListNode* reverseForward(ForwardListNode* pre, ForwardListNode* cur)
    {
        if (cur == nullptr) return pre;
        ForwardListNode* next = cur->next;
        cur->next = pre;
        return reverseForward(cur, next);
    }
    static ForwardListNode* reverseForwardListSimple(ForwardListNode* head)
    {
        ForwardListNode* pre = nullptr, * cur = head;
        while (cur != nullptr)
        {
            auto next = cur->next;
            cur->next = pre;
            pre = cur;
            cur = next;
        }
        return pre;
    }
    static ListNode* reverseListSimple(ListNode* head)
    {
        ListNode* pre = nullptr, * cur = nullptr;
        while (head != nullptr)
        {
            cur = head->next;
            head->next = pre;
            head->pre = cur;
            pre = head;
            head = cur;
        }
    }
    static ListNode* reverseListRecursive(ListNode* head)
    {
        return reverseList(nullptr, head);
    }
    static ListNode* reverseList(ListNode* pre, ListNode* cur)
    {
        if (cur == nullptr) return pre;
        ListNode* next = cur->next;
        cur->next = pre;
        cur->pre = next;
        return reverseList(cur, next);
    }
    static ForwardListNode* mergeSortedForwardListRecursive(ForwardListNode* lhs, ForwardListNode* rhs)
    {
        if (lhs == nullptr) return rhs;
        if (rhs == nullptr) return lhs;
        if (lhs->val < rhs->val)
        {
            lhs->next = mergeSortedForwardListRecursive(lhs->next, rhs);
            return lhs;
        }
        else
        {
            rhs->next = mergeSortedForwardListRecursive(lhs, rhs->next);
            return rhs;
        }
    }
    static ForwardListNode* mergeSortedForwardList(ForwardListNode* lhs, ForwardListNode* rhs)
    {
        if (lhs == nullptr) return rhs;
        if (rhs == nullptr) return lhs;
        ForwardListNode head(0);
        ForwardListNode* cur = &head;
        while (lhs && rhs)
        {
            if (lhs->val < rhs->val)
            {
                cur->next = lhs;
                lhs = lhs->next;
            }
            else
            {
                cur->next = rhs;
                rhs = rhs->next;
            }
        }
        cur->next = (lhs == nullptr) ? rhs : lhs;
        return head.next;
    }
    //CAUTION : THIS TWO FORWARD LIST IS REVERSED ALREADY
    static ForwardListNode* addTwoForwardList(ForwardListNode* lhs, ForwardListNode* rhs)
    {
        if (lhs == nullptr) return rhs;
        if (rhs == nullptr) return lhs;
        ForwardListNode head(0);
        ForwardListNode* cur = &head;
        unsigned short flag = 0;
        while (lhs || rhs || flag)
        {
            int tmp = 0;
            if (lhs) tmp += lhs->val;
            if (rhs) tmp += rhs->val;
            tmp += flag;
            flag = tmp / 10;
            tmp %= 10;

            ForwardListNode* next = lhs ? lhs : rhs;
            if (next == nullptr) next = new ForwardListNode(tmp);
            next->val = tmp;

            cur->next = next;
            cur = cur->next;
            lhs = lhs ? lhs->next : nullptr;
            rhs = rhs ? rhs->next : nullptr;
        }
        return head.next;
    }
    static std::array<ForwardListNode*, 2> SplitOddEvenForwardList(ForwardListNode* const head)
    {
        ForwardListNode* headOdd = nullptr;
        ForwardListNode* headEven = nullptr;
        ForwardListNode* curOdd = nullptr;
        ForwardListNode* curEven = nullptr;
        size_t count = 1;
        while (head)
        {
            if (count % 2)
            {

            }
        }
    }
};

