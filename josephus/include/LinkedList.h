//
// Created by ricardo on 9/26/22.
//

#ifndef JOSEPHUS_LINKED_LIST_H
#define JOSEPHUS_LINKED_LIST_H
#include "cstdlib"
#include "cstring"
#include "cstdio"

#include "define.h"

/**
 * 列表节点结构体
 */
struct node {
    int ID;
    char Name[MAX_NAME_LENGTH];
    int Age;
    int Gender;
    struct node* next;
};

typedef struct node node_t;
typedef struct node* node_p;

/**
 * 创建循环列表
 * @param head 头节点地址的引用
 * @return true 创建成功
 * @return false 创建失败
 */
bool init_linked_list(node_p& head);

/**
 * 销毁链表
 * @param head 链表头节点的地址
 */
void destroy_linked_list(node_p& head);

/**
 * 创建一个链表中的节点
 * @param node 新节点地址引用
 * @param id 人的编号
 * @param age 人的年龄
 * @param gender 人的性别
 * @param name 人的姓名字符串
 * @return true 创建成功
 * @return false 创建失败
 */
bool create_node(node_p& node, int id, int age, int gender, char* name);

/**
 * 在链表的末尾插入新节点
 * 虽然是循环链表 我们不妨认为头节点前的节点
 * @param head 链表头节点的引用
 * @param new_node 需要插入的新节点
 */
void append_node(const node_p& head, node_p new_node);

/**
 * 从链表中删除指定的节点
 * @param head 链表头节点的引用
 * @param target_node 需要删除的目标节点
 * @return true 删除成功
 * @return false 删除失败 一般是目标节点非法
 */
bool delete_node(const node_p& head, node_p target_node);

/**
 * 打印指定节点记录人员的信息
 * @param node 对指定节点的引用
 */
void print_node(const node_p& node);

/**
 * 打印链表中每个节点的值
 * @param head 链表头节点的引用
 */
void print_linked_list(const node_p& head);

#endif //JOSEPHUS_LINKED_LIST_H
