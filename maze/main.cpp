#include "maze_node.h"
#include "stack.h"
#include "cstdio"

int main()
{
    char config_file[10] = "maze.txt";
    maze_node_p node_array = read_maze_file(config_file);
    print_maze(node_array);

    // 输入迷宫的开始和结束节点
    int begin_node, end_node;
    printf("Please enter the start node:\n");
    scanf("%d", &begin_node);
    printf("Please enter the end node:\n");
    scanf("%d", &end_node);

    // 初始化储存路径的栈
    stack_t path_stack;
    // 显然栈的最大大小就是迷宫中节点的数量
    // 但是由于栈判满的原因需要多一个位置
    path_stack.stack_size = node_number + 1;
    init_stack(path_stack);

    // 初始化将起点填入栈中
    stack_push(path_stack, begin_node - 1);

    while (stack_get_top(path_stack) + 1 != end_node)
    {
        maze_connect_node_p& node = node_array[stack_get_top(path_stack)].now_node;
        if (node == nullptr)
        {
            // 节点已经遍历完不抱希望了
            // 这个值仅占位
            int temp;
            stack_pop(path_stack, &temp);
            continue;
        }
        // 遍历栈确定目标节点不在栈中
        bool flag = false;
        int* p = path_stack.base;
        while (p != path_stack.top)
        {
            if (node->index == *p)
            {
                flag = true;
                break;
            }
            p++;
        }

        if (!flag)
        {
            // 如果在栈中没发现这个节点
            stack_push(path_stack, node->index);
        }
        // 将未探索的节点置为下一个
        node = node->next;
    }

    // 打印路径栈
    int* p = path_stack.base;
    printf("%d", *p + 1);
    p++;
    while (p != path_stack.top)
    {
        printf("->%d", *p + 1);
        p++;
    }
    printf("\n");

    stack_free(path_stack);
    maze_node_free(node_array);

    return 0;
}
