//
// Created by ricardo on 9/26/22.
//
#include "LinkedList.h"

bool init_linked_list(node_p& head)
{
    head = (node_p) malloc(sizeof (node_t));

    if (head == nullptr)
    {
        // 空间分配失败
        return false;
    }
    // 由于是创建循环链表 头节点的下一个节点就是头节点
    head->next = head;
    return true;
}

void destroy_linked_list(node_p& head)
{
    node_p node = head->next;

    // 先循环处理所有不是头节点的节点
    while (node != head)
    {
        node_p temp = node;
        node = node->next;
        free(temp);
    }

    free(head);
    head = nullptr;
}

bool create_node(node_p& node, int id, int age, int gender, char* name)
{
    node = (node_p) malloc(sizeof(node_t));

    if (node == nullptr)
    {
        // 分配空间失败
        return false;
    }

    node->ID = id;
    node->Age = age;
    node->Gender = gender;
    strcpy(node->Name, name);

    return true;
}

void append_node(const node_p& head, node_p new_node)
{
    node_p node = head->next;

    // 找到头节点前的一个节点
    while (node->next != head)
    {
        node = node->next;
    }

    node->next = new_node;
    new_node->next = head;
}

bool delete_node(const node_p& head, node_p target_node)
{
    if (head == target_node)
    {
        // 删除头节点时不可行的
        return false;
    }

    node_p node = head;

    while (node->next != target_node)
    {
        if (node->next == head)
        {
            // 循环完了都没找见
            // 说明查无此节点
            return false;
        }

        node = node->next;
    }

    node->next = target_node->next;
    free(target_node);
    return true;
}

void print_node(const node_p& node)
{
    if (node == nullptr)
    {
        // 指定节点为空
        return;
    }

    printf("ID:%d|", node->ID);
    printf("Name:%s|", node->Name);
    printf("Age:%d|", node->Age);
    if (node->Gender == MALE)
    {
        printf("Gender:Male\n");
    }
    else
    {
        printf("Gender:Female\n");
    }
}

void print_linked_list(const node_p& head)
{
    if (head == nullptr)
    {
        // 头节点为空
        return;
    }

    node_p node = head->next;

    while (node != head)
    {
        print_node(node);
        node = node->next;
    }
}

