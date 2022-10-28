//
// Created by ricardo on 9/26/22.
//
#include "LinkedList.h"
#include "define.h"

node_p read_input()
{
    int age, id, gender;
    char name[MAX_NAME_LENGTH];
    char gender_string[MAX_GENDER_LENGTH];

    // 性别字符串
    const char* male_string = "male";
    const char* female_string = "female";

    scanf("%d %s %s %d", &id, name, gender_string, &age);

    // 匹配输入的性别字符串
    if (strcmp(gender_string, male_string) == 0)
    {
        gender = MALE;
    }
    else if (strcmp(gender_string, female_string) == 0)
    {
        gender = FEMALE;
    }
    else
    {
        // 如果匹配失败说明输入非法
        return nullptr;
    }

    node_p node;
    if (create_node(node, id, age, gender, name))
    {
        return node;
    }
    else
    {
        return nullptr;
    }
}

int main() {
    // 存储总共的人数
    int number;
    // 链表的头节点
    node_p head;

    if (!init_linked_list(head))
    {
        // 创建链表的头节点
        // 如果创建失败输出错误信息
        printf("E: Init linked list failed.\n");
        return -1;
    }

    // 输入人员列表
    printf("Hint: Enter number of people join this game:");
    scanf("%d", &number);
    printf("Hint: Enter the people information list as id name gender(male|female) age.\n");
    for (int i = 0; i < number; ++i) {
        node_p node = read_input();
        if (node == nullptr)
        {
            printf("E: Create Node failed.\n");
            return -1;
        }
        else
        {
            append_node(head, node);
        }
    }

    // 打印人员列表
    print_linked_list(head);

    // 分别记录游戏开始的位置 中间的间隔 最后剩余的人数
    int begin, middle, left;
    printf("Hint: Enter the begin(begin from 0), middle and left people number.\n");
    scanf("%d %d %d", &begin, &middle, &left);

    node_p node = head->next;
    // 循环到达游戏开始的位置
    for (int i = 0; i < begin; ++i) {
        node = node->next;
    }

    // 这里有点屎
    // 由于给定的数据是"间隔"
    // 在遍历时的次数需要+1
    // 但是当前被选中的节点会被删除 在删除之间需要将指针下移一位
    // 遍历的次序又需要-1
    // 故需要在开始前在指针前移一位
    node = node->next;
    while (number > left)
    {
        // 游戏开始
        // 由于middle是间隔
        for (int i = 0; i < middle; ++i) {
            if (node == head)
            {
                // 由于头节点不存储数据
                // 遍历到头节点需要多遍历一次
                i--;
            }

            node = node->next;
        }
        if (node == head)
        {
            // 如果恰好在末尾遇到head
            // 无法在循环中处理
            node = node->next;
        }

        printf("ID:%d was killed\n", node->ID);
        node_p target = node;
        node = node->next;
        if (!delete_node(head, target))
        {
            printf("E: delete node failed.\n");
            return -1;
        }
        number--;
    }

    print_linked_list(head);

    // 在退出程序之前 释放链表占用的空间
    destroy_linked_list(head);
    return 0;
}

