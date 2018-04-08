#include "ll.h"

namespace snakelinkedlist {
    //basic functions

    /**
     * default constructor
     */
    LinkedList::LinkedList() {
        head_ = nullptr;
    }

    /**
     * This constructor will create a linked list containing in order the elements from the value vector
     * @param values vector contains data to be stored in LinkedList
     */
    LinkedList::LinkedList(const std::vector<SnakeBodySegment> &values) {
        if (values.empty()) {
            return;
        }

        head_ = new Node();
        head_->data_ = values[0];
        Node *runner = head_;
        for (int i = 1; i < values.size(); i++) {
            Node *current = new Node();
            current->data_ = values[i];
            runner->next_ = current;
            runner = runner->next_;
        }
    }

    /**
     * This function will create a new linked list that is a deep copy of the source
     * @param source LinkedList to be copied
     */
    LinkedList::LinkedList(const LinkedList &source) {
        head_ = nullptr;
        if (source.head_ == nullptr) {
            return;
        }

        head_ = new Node();
        head_->data_ = source.head_->data_;
        Node *local_runner = head_;
        Node *source_runner = source.head_;
        while (source_runner->next_ != nullptr) {
            Node *current = new Node();
            current->data_ = source_runner->next_->data_;
            local_runner->next_ = current;
            local_runner = local_runner->next_;
            source_runner = source_runner->next_;
        }
    }

    /**
     * This function will implement a move constructor that will make a new linked list using the already allocated
     * elements from the source
     * @param source LinkedList to be moved from
     */
    LinkedList::LinkedList(LinkedList &&source) noexcept {
        head_ = source.head_;
        source.head_ = nullptr;
    }

    /**
     * This destructor function will delete all the allocated data in the linked list class.
     */
    LinkedList::~LinkedList() {
        this->clear();
    }

    /**
     * This function is the copy assignment operator which should make a deep copy from the source deallocating all
     * data from the old location. Remember to handle the case where the both sides are the same list
     * @param source Linked list to be copied from
     * @return pointer to a new Linked list
     */
    LinkedList &LinkedList::operator=(const LinkedList &source) {
        if (this == &source) {
            return *this;
        }

        this->clear();
        LinkedList *temp_list = new LinkedList(source);
        this->head_ = temp_list->head_;
        temp_list->head_ = nullptr;

        return *this;
    }

    /**
     * This function will copy the data from the source reusing the allocated data from the source and deleting any
     * data that was allocated. Remember to handle the case where the both sides are the same list
     * @param source Linked list to be moved from
     * @return a pointer to the new Linked list
     */
    LinkedList &LinkedList::operator=(LinkedList &&source) noexcept {
        if (this == &source) {
            return *this;
        }

        this->clear();
        this->head_ = source.head_;
        source.head_ = nullptr;
        return *this;
    }

    // Modifiers

    /**
     *This function will add a new element to the linked list at the front of the list
     * @param value data to be added
     */
    void LinkedList::push_front(SnakeBodySegment value) {
        Node *old_ptr = head_;
        head_ = new Node;
        head_->data_ = value;
        head_->next_ = old_ptr;
    }

    /**
     *  This function will add a new element to the linked list at the back of the list
     * @param value data to be added
     */
    void LinkedList::push_back(SnakeBodySegment value) {
        if (head_ == nullptr) {
            head_ = new Node();
            head_->data_ = value;
            return;
        }

        Node *runner = head_;
        while (runner->next_ != nullptr) {
            runner = runner->next_;
        }
        runner->next_ = new Node();
        runner = runner->next_;
        runner->data_ = value;
    }

    /**
     * This will remove the front element from the linked list and delete the allocated data.
     * If the list is empty it will do nothing
     */
    void LinkedList::pop_front() {
        if (head_ == nullptr) {
            return;
        }

        Node *old_head = head_;
        head_ = head_->next_;
        delete old_head;
    }

    /**
     * This will remove the back element from the linked list and delete the allocated data.
     * If the list is empty it will do nothing
     */
    void LinkedList::pop_back() {
        if (head_ == nullptr) {
            return;
        }

        if (this->size() == 1) {
            this->clear();
            return;
        }

        Node *runner = head_;
        Node *previous = runner;
        while (runner->next_ != nullptr) {
            previous = runner;
            runner = runner->next_;
        }

        delete runner;
        previous->next_ = nullptr;
    }

    /**
     * Remove the Nth element from the list deleting the allocated data. If the list does not contain a Nth element
     * this function will do nothing. This function is zero indexed so RemoveNth(0) should remove the head and
     * RemoveNth(1) will remove the second element in the list
     * @param n index of the element to be removed
     */
    void LinkedList::RemoveNth(int n) {
        if (n == 0) {
            pop_front();
            return;
        }

        if (n == size() - 1) {
            pop_back();
            return;
        }

        if (n > size() - 1) {
            return;
        }

        Node *runner = head_;
        for (int i = 0; i < n - 1; i++) {
            runner = runner->next_;
        }

        Node *node_to_remove = runner->next_;
        Node *next_node = node_to_remove->next_;
        delete node_to_remove;
        runner->next_ = next_node;
    }

    /**
     * Delete all data in the linked list returning the list to the same state as the default constructor
     */
    void LinkedList::clear() {
        if (head_ == nullptr) {
            return;
        }

        Node *runner = head_;
        while (head_ != nullptr) {
            head_ = head_->next_;
            delete runner;
            runner = head_;
        }
    }

    // Accessors

    /**
     * Return a copy of the SnakeBodySegment element stored in the first node of the list. This does not remove
     * any items from the list.
     * @return a copy of the data in the head, or the default SnakeBodySegment if the list is empty
     */
    SnakeBodySegment LinkedList::front() const {
        if (head_ == nullptr) {
            return snakelinkedlist::SnakeBodySegment();
        }
        return head_->data_;
    }

    /**
     * Return a copy of the SnakeBodySegment element stored in the last node of the list.
     * This does not remove any items from the list.
     * @return a copy of the data in the last node, or the default SnakeBodySegment if the list is empty
     */
    SnakeBodySegment LinkedList::back() const {
        if (head_ == nullptr) {
            return snakelinkedlist::SnakeBodySegment();
        }

        Node *runner = head_;
        while (runner->next_ != nullptr) {
            runner = runner->next_;
        }

        return runner->data_;
    }

    /**
     * Return the number of elements in the list
     * @return the number of elements in the list
     */
    int LinkedList::size() const {
        if (head_ == nullptr) {
            return 0;
        }

        int sum = 1;
        Node *runner = head_;
        while (runner->next_ != nullptr) {
            sum++;
            runner = runner->next_;
        }
        return sum;
    }

    /**
     * Return a vector that contains all the elements in the list
     * @return vector contains all the data in the list in order
     */
    std::vector<SnakeBodySegment> LinkedList::GetVector() const {
        if (head_ == nullptr) {
            return std::vector<SnakeBodySegment>();
        }

        std::vector<SnakeBodySegment> snake_body_seg_list;
        Node *runner = head_;

        while (runner->next_ != nullptr) {
            snake_body_seg_list.push_back(runner->data_);
            runner = runner->next_;
        }

        snake_body_seg_list.push_back(back());

        return snake_body_seg_list;
    }

    /**
     * This function determines whether the list is empty
     * @return true true if the list is empty otherwise returns false
     */
    bool LinkedList::empty() const {
        if (head_ == nullptr) {
            return true;
        }
        return false;
    }

    /**
     * This should print the SnakeBodySegment elements stored in the list using the « operator from the SnakeBodySegment
     * class to print the list with a comma and a space separating each element for example "3, 2" when there are
     * elements that would print as 3 and 2 respectively
     * @param os output stream
     * @param list the list to print
     * @return the output stream
     */
    std::ostream &operator<<(std::ostream &os, const LinkedList &list) {
        if (list.head_ == nullptr) {
            os << "" << std::endl;
            return os;
        }

        LinkedList::Node *runner = list.head_;
        while (runner->next_ != nullptr) {
            os << runner->data_ << ", ";
            runner = runner->next_;
        }

        os << list.back() << std::endl;
        return os;
    }

    /**
     * This function will compare the list element by element
     * @param rhs the right hand side of the operator
     * @return true if they are all equal otherwise it will return false
     */
    bool LinkedList::operator==(const LinkedList &rhs) const {
        return (this->GetVector() == rhs.GetVector());
    }

    /**
     * This function will compare the list element by element
     * @param lhs left hand side of the operator
     * @param rhs right hand side of the operator
     * @return false if they are all equal otherwise it will return true
     */
    bool operator!=(const LinkedList &lhs, const LinkedList &rhs) {
        return !(lhs == rhs);
    }
} // namespace snakelinkedlist
