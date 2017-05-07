#include <gtest/gtest.h>
#include "Stack.h"

TEST(StackTest, size)
{
    Stack<int> stack;
    ASSERT_EQ(0, stack.size());
}

TEST(StackTest, push)
{
    Stack<int> stack;
    stack.push(1);
    ASSERT_EQ(1, stack.size());

    stack.push(1);
    ASSERT_EQ(2, stack.size());
}

TEST(StackTest, pop)
{
    Stack<int> stack;
    ASSERT_FALSE(stack.pop());
}
