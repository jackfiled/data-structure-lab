//
// Created by ricardo on 2022/10/25.
//
#include "stack.h"

bool init_stack(stack_t& s)
{
    if (s.stack_size == 0)
    {
        // 如果没有设置栈的大小
        // 就设置为默认大小
        s.stack_size = DEFAULT_STACK_LENGTH;
    }

    auto p = (int* ) malloc(sizeof(int));
    if  (p == nullptr)
    {
        // 空间分配失败
        return false;
    }

    s.base = p;
    s.top = p;
    return true;
}

bool stack_is_empty(const stack& s)
{
    return s.base == s.top;
}

bool stack_is_full(const stack& s)
{
    return s.base + s.stack_size == s.top;
}

bool stack_push(stack& s,int index)
{
    if (stack_is_full(s))
    {
        // 栈已满
        return false;
    }

    *s.top = index;
    s.top++;

    return true;
}

bool stack_pop(stack& s, int* index)
{
    if (stack_is_empty(s))
    {
        // 栈为空
        return false;
    }

    *index = *s.top;
    s.top--;

    return true;
}

int stack_get_bottom(const stack_t& s)
{
return *s.base;
}

int stack_get_top(const stack_t& s)
{
    return *(s.top-1);
}

void stack_free(stack_t& s)
{
    free(s.base);
    s.base = nullptr;
    s.top = nullptr;
    s.stack_size = 0;
}
