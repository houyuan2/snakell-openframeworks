#ifndef LL_H
#define LL_H

#include<iostream>
#include<vector>

#include "snakebody.h"

namespace snakelinkedlist {

/*
 *  Declare any struct, class, or enum types you need to use here
 */

// Specialied linked list class
class LinkedList {
    /*
     *  Add member variables and private helper functions
     *  internal structs, classes, or enum types here
     */
    struct Node {
        Node* next_;
        SnakeBodySegment data_;
    };

    Node* head_;

public:
    // Default constructor
    LinkedList();
    // Initilize from vector
    explicit LinkedList(const std::vector<SnakeBodySegment>& values);
    // Big 5
    LinkedList(const LinkedList& source);                // Copy constructor
    LinkedList(LinkedList&& source) noexcept;            // Move constructor
    ~LinkedList();                                       // Destructor
    LinkedList& operator=(const LinkedList& source);     // Copy assignment operator
    LinkedList& operator=(LinkedList&& source) noexcept; // Move assignment operator

    // Modifiers
    void push_front(SnakeBodySegment value); // Push value on front
    void push_back(SnakeBodySegment value);  // Push value on back
    void pop_front();                        // remove front element
    void pop_back();                         // remove back element
    void RemoveNth(int n);                   // remove the Nth emement from the front
    void clear();                            // clear the contents

    // Accessors
    SnakeBodySegment front() const;                  // Access the front value
    SnakeBodySegment back() const;                   // Access the back valueW
    int size() const;                                // return number of elements
    std::vector<SnakeBodySegment> GetVector() const; // return a vector of the values
    bool empty() const;                              // check if empty
    friend std::ostream& operator<<(std::ostream& os, const LinkedList& list);
    bool operator==(const LinkedList& rhs) const;
};

// This can effiently be implemented outside the class
bool operator!=(const LinkedList& lhs, const LinkedList& rhs);

} // namespace snakelinkedlist
#endif //LL_H