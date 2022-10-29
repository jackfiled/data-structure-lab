#include "maze_node.h"
#include "cstdlib"
#include "cstdio"

int node_number;

maze_node_p create_maze_node_array(int num)
{
    auto node = (maze_node_p) malloc(num * sizeof(maze_node_t));
    maze_node_p p = node;
    for (int i = 1; i <= num; ++i) {
        p->id = i;
        p->connect_maze_nodes = nullptr;
        p++;
    }
    return node;
}

bool maze_node_add_connect_node(maze_node_t& node, int target)
{
    auto new_node = (maze_connect_node_p) malloc(sizeof(maze_connect_node_t));
    if (new_node == nullptr)
    {
        // 分配空间失败
        return false;
    }

    new_node->next = nullptr;
    new_node->index = target;

    if (node.connect_maze_nodes == nullptr)
    {
        node.connect_maze_nodes = new_node;
        // 遍历链表总是从头开始
        node.now_node = new_node;
    }
    else
    {
        maze_connect_node_p connect_node = node.connect_maze_nodes;

        while (connect_node->next != nullptr)
        {
            // 找到链表末节点
            connect_node = connect_node->next;
        }

        connect_node->next = new_node;
    }

    return true;
}

maze_node_p read_maze_file(char* filename)
{
    FILE* config_file;
    char buffer[10];

    config_file = fopen(filename, "r");

    // 配置文件的第一行要求是迷宫中节点的总数
    fgets(buffer, sizeof buffer, config_file);
    char* point;
    node_number = (int )strtol(buffer, &point, 10);

    maze_node_p node_array = create_maze_node_array(node_number);

    while (fgets(buffer, sizeof buffer, config_file) != nullptr)
    {
        int node1, node2;
        sscanf(buffer, "%d-%d", &node1, &node2);

        // 数组中的索引总是比编号小1
        maze_node_add_connect_node(node_array[node1 - 1], node2 - 1);
        maze_node_add_connect_node(node_array[node2 - 1], node1 - 1);
    }

    fclose(config_file);

    return node_array;
}

void print_maze(maze_node_p node_array)
{
    for (int i = 0; i < node_number; ++i) {
        maze_node_t node = node_array[i];
        maze_connect_node_p p = node.connect_maze_nodes;
        while (p != nullptr)
        {
            printf("%d->%d\n", node.id, node_array[p->index].id);
            p = p->next;
        }
    }
}

void maze_node_free(maze_node_p& node_array)
{
    for(int i = 0; i < node_number; i++)
    {
        maze_connect_node_p node = node_array[i].connect_maze_nodes;
        while (node != nullptr)
        {
            maze_connect_node_p temp = node;
            node = node->next;
            free(temp);
        }
    }

    free(node_array);
    node_array = nullptr;
}