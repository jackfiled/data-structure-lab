//
// Created by ricardo on 2022/10/25.
//

#ifndef MAZE_STACK_H
#define MAZE_STACK_H

#include "cstdlib"
#include "maze_node.h"

// 默认的栈大小
#define DEFAULT_STACK_LENGTH 200

// 由于将迷宫中的所有节点都储存在数组中
// 存储路径的栈就不用存储节点的指针
// 而是直接存储节点在数组中的索引
struct stack {
    int* top;
    int* base;
    int stack_size;
};

typedef struct stack stack_t;
typedef struct stack* stack_p;

/**
 * 初始化栈空间
 * @param s 栈结构体的引用
 * @return 栈是否创建成功
 */
bool init_stack(stack_t& s);

/**
 * 判断栈是否为空
 * @param s 对于栈结构体的引用
 * @return
 */
bool stack_is_empty(const stack_t& s);

/**
 * 判断栈是否已满
 * @param s 对于结构体的引用
 * @return
 */
bool stack_is_full(const stack_t& s);

/**
 * 在栈中压入元素
 * @param s 栈引用
 * @param value 被压入栈的值
 * @return 压入栈是否成功
 */
bool stack_push(stack_t& s, int index);

/**
 * 在栈中弹出元素
 * @param s 栈引用
 * @param value 被弹出栈的值
 * @return 弹出栈是否成功
 */
bool stack_pop(stack_t& s, int* index);

/**
 * 获得栈底的元素
 * @param s 栈引用
 * @return
 */
int stack_get_bottom(const stack_t& s);

/**
 * 获得栈顶的元素
 * @param s 栈引用
 * @return
 */
int stack_get_top(const stack_t& s);

/**
 * 释放栈所占用的空间
 * @param s 栈引用
 */
void stack_free(stack_t& s);

#endif //MAZE_STACK_H
