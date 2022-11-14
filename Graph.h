#pragma once
#include <iostream>
template <class type>
struct Node {
	int n = 0;
	type value;
    Node<type> *prevNode = nullptr;
    Node<type> *nextNode = nullptr;
	//Node<type>* pointers = nullptr;
};

template <class type>
class Graph {
    /*Instance variable to track how many nodes are within a degenerated
    * binary tree.
    */
	int n = 0;

    /*Instance variables that point to the beginningand end of a degenerated
    * binary tree.
    */
    Node<type> *first = nullptr;
    Node<type> *root = nullptr;
    Node<type> *last = nullptr;

public:

	//Graph() {}

    /*Pushes a node onto a link / chain without regard for order.Instantiates a
    * new structure if necessary.
    */
    void push(type value) {
        Node<type> *newNode = new Node<type>;
        newNode->value = value;
        if (!first)
            last = first = newNode;
        else if (last) {
            newNode->prevNode = last;
            last = last->nextNode = newNode;
        }
        else {
            Node<type> *ptr = first;
            while (ptr->nextNode)
                ptr = ptr->nextNode;
            ptr->nextNode = newNode;
            newNode->prevNode = ptr;
            last = newNode;
        }
        n++;
    }

    //Inserts a node into a link/chain in ascending order.
    void insert(type value) {
        if (first) {
            Node<type> *newNode = new Node<type>;
            newNode->value = value;
            if (newNode->value < first->value) {
                first->prevNode = newNode;
                newNode->nextNode = first;
                first = first->prevNode;
            }
            else {

                Node<type> *ptr = first;
                /*Knowing that there's at least one node, this block loops through
                * the chain until ptr points to the last node in the tree or ptr
                * points to a node with a value greater than than node being inserted
                */
                while (ptr->nextNode && ptr->value <= newNode->value)
                    ptr = ptr->nextNode;

                /*It will either insert when ptr points to the last nodeand to a node
                * that stores a greater value or when it points to a node storing a
                * greater value deeper within the structure
                */
                if (ptr->nextNode || newNode->value < ptr->value) {
                    newNode->prevNode = ptr->prevNode;
                    ptr->prevNode->nextNode = newNode;
                    newNode->nextNode = ptr;
                    ptr->prevNode = newNode;
                } //Append a node to the end of the structure
                else {
                    last->nextNode = newNode;
                    newNode->prevNode = last;
                    last = newNode;
                }
            }
            n++;
        }
        else {
            push(value);
        }
    }

    //Appends a node to the end of a linked list.
    void emplace(type value) {
        Node<type> *newNode = new Node<type>;
        newNode->value = value;
        last = last->nextNode = newNode;
        n++;
    }

    //Removes a node from the front of a queue, or in FIFO fashion.
    type dequeue() {
        Node<type> *ptr = first;
        first = ptr->nextNode;
        type value = ptr->value;
        delete ptr;
        n--;
        return value;
    }

    //Removes a node from the end/top of a stack. 
    type pop() {
        Node<type>* ptr = last;
        last = ptr->prevNode;
        type value = ptr->value;
        delete ptr;
        n--;
        ptr = nullptr;
        return value;
    }

    //Swaps the values of two degenerated binary trees.
    void swap(Graph<type>& list) {
        type temp;
        Node<type> *ptr0 = first, *ptr1 = list->top();
        while (ptr0->prevNode && ptr1->prevNode) {
            temp = ptr0->value;
            ptr0->value = ptr1->value;
            ptr1->value = temp;
            ptr0 = ptr0->prevNode;
            ptr1 = ptr1->prevtNode;
        }
    }

    //Swaps two items within a list
    void swap(Node<type> *ptr, Node<type> *ptr1) {
        type value = ptr->value;
        ptr->value = ptr1->value;
        ptr1->value = value;
    }

    //Returns the maximum within a given range
    Node<type>* max(Node<type>* start) const {
        int max = INT_MIN;
        Node<type> *ptr = nullptr, *trv = start;
        while (trv) {
            if (max < trv->value) {
                max = trv->value;
                ptr = trv;
            }
            trv = trv->nextNode;
        }
        return ptr;
    }

    //Returns the minimum within a given range
    Node<type> *min(Node<type> *start) const {
        int min = INT_MAX;
        Node<type> *ptr = nullptr, *trv = start;
        while (trv) {
            if (trv->value < min) {
                min = trv->value;
                ptr = trv;
            }
            trv = trv->nextNode;
        }
        return ptr;
    }

    //Selection sort
    void selSort(bool findMin = true) {
        Node<type> *ptr = first;
        while (ptr) {
            if (findMin)
                swap(ptr, min(ptr));
            else
                swap(ptr, max(ptr));
            ptr = ptr->nextNode;
        }
    }

    void print(Node<type>* ptr) {
        while (ptr)
        {
            std::cout << ptr->value;
            ptr = ptr->nextNode;
        }
    }

    //Divide
    Node<type> **divide(Node<type> *list)
    {
        std::cout << "DIVDIE ";print(list); std::cout << std::endl;
        Node<type> **sublist = new Node<type>*[2];
        sublist[0] = list, sublist[1] = nullptr;

        if (list)
        {
            sublist[1] = list;
            Node<type> *ptr = list->nextNode;

            while (ptr)
            {
                if (ptr->prevNode == sublist[1])
                    ptr = ptr->nextNode;
                else
                {
                    sublist[1] = sublist[1]->nextNode;
                    ptr = ptr->nextNode;
                    ptr = ptr->nextNode;
                }

                if (!ptr)
                {
                    sublist[1] = sublist[1]->nextNode;
                    std::cout << sublist[1]->value << " unlinked from " << sublist[1]->prevNode->value << "\n";
                    sublist[1]->prevNode->nextNode = nullptr;
                }
            }

            if (sublist[1] == sublist[0])
                sublist[1] = nullptr;

        } 
        std::cout << "SUBLIST 0--------------------------------" << "\n";
        sublist[0] = mergeSort(sublist[0]);
        std::cout << "SUBLIST 1--------------------------------" << "\n";
        sublist[1] = mergeSort(sublist[1]);
        std::cout << "-----------------------------------------" << "\n";
        std::cout << "I got "; print(sublist[0]); std::cout << " and "; print(sublist[1]);
        std::cout<< "\n";
        return sublist;
    }

    
    // Merge
    Node<type> *merge(Node<type> **sublist)
    {
        Node<type> *ptr0 = sublist[0];
        Node<type> *ptr1 = sublist[1];
        std::cout << "MERGE "; print(sublist[0]);  std::cout << " AND ";  print(sublist[1]); std::cout << std::endl;
        Node<type> *temp = nullptr;

        while (ptr0 && ptr1)
        {
            if (ptr0->value > ptr1->value)
            {
                std::cout << "(PTR0 > PTR1) " << ptr0->value << " > " << ptr1->value << "\n";
                temp = ptr1;
                ptr1 = ptr1->nextNode;
                temp->nextNode = ptr0;
            }
            else 
            {
                std::cout << "(PTR1 > PTR0) " << ptr1->value << " > " << ptr0->value << "\n";
                temp = ptr0;
                ptr0 = ptr0->nextNode;
                temp->nextNode = ptr1;
            }
        }
        std::cout << "TOTAL "; print(sublist[0]);  std::cout << " AND ";  print(sublist[1]); std::cout << std::endl;
        if (sublist[0] && sublist[1])
        {
            if (sublist[0]->value < sublist[1]->value)
            {
                std::cout<< "RET SUB0(" << sublist[0]->value << ") < SUB1(" << sublist[1]->value << ")\n";
                return sublist[0];
            }
            else 
            {
                std::cout << "SUB0(" << sublist[0]->value << ") > RET SUB1(" << sublist[1]->value << ")\n";
                return sublist[1];
            }
        }
        else if (sublist[0])
        {
            std::cout << "RET SUB0(" << sublist[0]->value << ")\n";
            return sublist[0];
        }
        else if (sublist[1])
        {
            std::cout << "RET SUB1(" << sublist[1]->value << ")\n";
            return sublist[1];
        }
        else 
        {
            std::cout << "RET NO SUB" << "\n";
            return nullptr;
        }
    }


    //Merge sort
    Node<type> *mergeSort(Node<type> *list)
    {
        Node<type>** sublist = new Node<type>*[2];
        sublist[0] = list;
        sublist[1] = nullptr;

        if (list && list->nextNode)
        {
            sublist = divide(list);
        }

        return merge(sublist);
    }


    //Returns a pointer to the last node within a degenerated tree.
    Node<type> *top() {
        return last;
    }

    //Returns a boolean indicating if the tree is empty.
    bool empty() {
        return (last) ? false : true;
    }

    // Returns a pointer to the root of the tree
    Node<type> *getRoot() {
        return root;
    }

    //Returns a pointer to the first node within a tree.
    Node<type> *begin() {
        return first;
    }

    //Reurns a nullptr
    Node<type> *end() {
        return last->nextNode;
    }

    //Returns the last value within a degenerated tree.
    type back() {
        return last->value;
    }

    //Returns the current size of (or nodes within) the data structure.
    int size() {
        return n;
    }
	~Graph() {}
};
