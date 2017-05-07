#ifndef __STACK_TEMPLATE_H__
#define __STACK_TEMPLATE_H__

template <typename T>
class Stack {
public:
    typedef size_t size_type;
public:
    Stack()
        : items(),
          reserved(),
          amount()
    {
    }

    size_type size() const {
        return this->amount;
    }

    void push(const T& value) {
        ++this->amount;
    }

    bool pop() {
        return false;
    }
private:
    T **items;
    size_type reserved;
    size_type amount;
};

#endif //__STACK_TEMPLATE_H__
