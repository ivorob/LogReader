#ifndef __STACK_TEMPLATE_H__
#define __STACK_TEMPLATE_H__

template <typename T>
class Stack {
public:
    typedef size_t size_type;
private:
    const size_type increment = 20;
public:
    Stack()
        : items(),
          reserved(),
          amount(),
          nullValue()
    {
    }

    ~Stack() {
        for (size_type i = 0; i < this->amount; ++i) {
            delete this->items[i];
        }

        delete this->items;
    }

    size_type size() const {
        return this->amount;
    }

    bool empty() const {
        return this->amount == 0;
    }

    void push(const T& value) {
        if (this->amount <= this->reserved) {
            reserve(this->amount + this->increment);
        }

        this->items[this->amount++] = new T(value);
    }

    bool pop() {
        if (this->amount == 0) {
            return false;
        }

        delete this->items[--this->amount];
        this->items[this->amount] = nullptr;
        return true;
    }

    const T& back() const {
        if (size() != 0) {
            return *items[this->amount - 1];
        }

        return nullValue;
    }

    void reserve(size_type size = increment) {
        this->reserved = size;

        T **items = new T*[this->reserved];
        if (items != nullptr) {
            memset(items, 0, this->reserved * sizeof(T*));

            if (this->items != nullptr) {
                memcpy(items, this->items, this->amount * sizeof(T*));
            }

            delete[] this->items;
            this->items = items;
        }
    }
private:
    T **items;
    size_type reserved;
    size_type amount;
    const T nullValue;
};

#endif //__STACK_TEMPLATE_H__
