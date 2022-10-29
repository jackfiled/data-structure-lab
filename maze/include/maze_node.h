//
// Created by ricardo on 2022/10/25.
//

#ifndef MAZE_MAZE_NODE_H
#define MAZE_MAZE_NODE_H

// 全局的节点总数变量
// 虽然全局变量有点不好
extern int node_number;

struct maze_connect_node
{
    // 连接的节点数组索引
    int index;
    struct maze_connect_node* next;
};

typedef struct maze_connect_node maze_connect_node_t;
typedef struct maze_connect_node* maze_connect_node_p;

struct maze_node
{
    // 迷宫中结点的编号
    int id;
    // 与这个节点相连的节点链表
    maze_connect_node_p connect_maze_nodes;
    // 当前正在遍历的节点
    maze_connect_node_p now_node;
};

// 迷宫节点结构体
typedef struct maze_node maze_node_t;
// 迷宫节点结构体指针
typedef struct maze_node* maze_node_p;

/**
 * 创建迷宫节点数组
 * @param num 迷宫中节点的数量
 * @return 数组地址
 */
maze_node_p create_maze_node_array(int num);

/**
 * 在指定的节点中添加与之相连的节点
 * @param node 指定的节点引用
 * @param target 与之相连的节点
 * @return 是否添加成功
 */
bool maze_node_add_connect_node(maze_node_t& node, int target);

/**
 * 读取迷宫配置文件
 * @param filename 配置文件文件名
 * @return 迷宫节点数组地址
 */
maze_node_p read_maze_file(char* filename);

/**
 * 打印整个迷宫
 * @param node_array 迷宫数组
 */
void print_maze(maze_node_p node_array);

/**
 * 释放迷宫节点数组占据的空间
 * @param node_array 迷宫节点数组引用
 */
void maze_node_free(maze_node_p& node_array);

#endif //MAZE_MAZE_NODE_H
