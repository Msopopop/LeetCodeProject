#pragma once
#include <array>
#pragma warning(disable:26440, 26486, 26487, 26489)
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

        static std::array<ForwardListNode*, 2> SplitOddEvenForwardList(ForwardListNode* head)
        {
            using std::array;
            ForwardListNode head2(0);
            ForwardListNode* r = &head2;
            ForwardListNode* pre = head;
            ForwardListNode* p = pre->next;
            while (p) {
                if (p->val % 2) {
                    pre = p;
                    p = p->next;
                }
                else {
                    pre->next = p->next;
                    r->next = p;
                    r = p;
                    p = pre->next;
                }
            }
            r->next = nullptr;
            array<ForwardListNode*, 2> arrayAns;
            arrayAns[0] = head;
            arrayAns[1] = &head2;
            return arrayAns;
        }

        static bool hasCircle(ForwardListNode* const head)
        {
            auto fast = head;
            auto slow = head;
            while (fast && fast->next)
            {
                fast = fast->next->next;
                slow = slow->next;
                if (fast == slow)
                    return true;
            }
            return false;
        }
        static ForwardListNode* getCircleEntry(ForwardListNode* const head)
        {
            ForwardListNode* encounter = nullptr;
            auto fast = head;
            auto slow = head;
            while (fast && fast->next)
            {
                fast = fast->next->next;
                slow = slow->next;
                if (fast == slow)
                    encounter = fast;
            }
            if (encounter == nullptr) return nullptr;

            decltype(encounter) p1 = head;
            decltype(p1) p2 = encounter;
            while (p1 != p2)
            {
                p1 = p1->next;
                p2 = p2->next;
            }
            return p1;
        }
        static ForwardListNode* findFirstCommonNode(ForwardListNode* const lhs, decltype(lhs) rhs)
        {
            ForwardListNode* p1 = lhs;
            decltype(p1) p2 = rhs;
            while (p1 != p2)
            {
                p1 = (p1 == nullptr) ? rhs : p1->next;
                p2 = (p2 == nullptr) ? lhs : p2->next;
            }
            return p1;
        }
        static ForwardListNode* deleteDuplicatedNode(ForwardListNode* head)
        {
            if (head == nullptr) return head;
            auto cur = head;
            while (cur && cur->next)
            {
                if (cur->val == cur->next->val)
                    cur->next = cur->next->next;
                else
                    cur = cur->next;
            }
            return head;

        }
    };
#pragma warning(default:26440, 26486, 26487, 26489)
