/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* ptr1 = l1;
        ListNode* ptr2 = l2;
        ListNode* ptr3;
            
        ListNode* l3 = new ListNode();
        ptr3 = l3;
        
        bool carry = false;
        while(ptr1 || ptr2) {
            
            int num1 = 0, num2 = 0;
            
            if(ptr1 && ptr2) {
                num1 = ptr1->val;
                num2 = ptr2->val;
                
                ptr1 = ptr1->next;
                ptr2 = ptr2->next;
            }
            else if (ptr1) {
                num1 = ptr1->val;
                ptr1 = ptr1->next;
            }
            else {
                num2 = ptr2->val;
                ptr2 = ptr2->next;
            }
            
            if(num1 + num2 >= 10 && !carry) {
                carry = true;
                ptr3->val = (num1 + num2) - 10;
            }
            else if(carry) {
                if(num1 + num2 + 1 >= 10) {
                    carry = true;
                    ptr3->val = (num1 + num2 + 1) - 10;
                }
                else {
                    carry = false;
                    ptr3->val = num1 + num2 + 1;
                }
            }
            else {
                ptr3->val = num1 + num2;
            }
            
            if (ptr1 || ptr2) {
                ptr3->next = new ListNode();
                ptr3 = ptr3->next;
            }
        }
        
        if(carry) {
            ptr3->next = new ListNode();
            ptr3->next->val = 1;
        }
        return l3; 
    }
};
