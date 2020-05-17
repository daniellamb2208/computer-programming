#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct List
{
    int index[3];
    int direction[6];
    struct List *next;
} list;

void push_back(list *first, int *i, int *nsew)
{
    list *current = first;
    while (current->next)
        current = current->next;

    list *node = (list *)malloc(sizeof(list));
    int count;
    for (count = 0; count < 3; count++)
        node->index[count] = i[count];
    for (count = 0; count < 6; count++)
        node->direction[count] = nsew[count];
    node->next = NULL;

    current->next = node;
}

int know_row(list *head)
{
    list *current = head;
    while (current->next)
        current = current->next;
    return current->index[1];
}

int know_column(list *head)
{
    list *current = head;
    while (current->next)
        current = current->next;
    return current->index[0];
}

typedef struct Sol
{
    int i;
    struct Sol *next;
} sol;

void push(sol *head, int path) //for storing the solution
{
    sol *current = head;
    while (current->next)
        current = current->next;
    sol *node = (sol *)malloc(sizeof(sol));
    node->i = path;
    node->next = NULL;

    current->next = node;
}

void pop(sol *head)
{
    sol *current = head;
    while (current->next->next)
        current = current->next;
    sol *to_be_deleted = current->next;
    current->next = NULL;
    free(to_be_deleted);
}

list *readfile(char *s)
{
    FILE *fptr = fopen(s, "r");
    int index[3], direction[6], i;
    char c; //comma

    list *first = (list *)malloc(sizeof(list));
    for (i = 0; i < 3; i++)
        first->index[i] = 0;
    for (i = 0; i < 6; i++)
        first->direction[i] = 0;
    first->next = NULL;

    while (1)
    {
        fscanf(fptr, "%d,%d,%d,%d,%d,%d,%d,%d,%d", &index[0], &index[1], &index[2], &direction[0], &direction[1], &direction[2], &direction[3], &direction[4], &direction[5]);
        if (feof(fptr))
            break;
        push_back(first, index, direction);
    }
    fclose(fptr);

    return first;
}

int *start_and_end(char *s)
{
    FILE *fptr = fopen(s, "r");
    int *path = (int *)malloc(sizeof(int) * 3);
    fscanf(fptr, "%d,%d", path, path + 1);
    fclose(fptr);

    return path;
}

int can_go(list *first, int index, int compass)
{
    list *current = first;

    int i;
    for (i = 0; i < index; i++)
        current = current->next;

    return (current->direction[compass] == 0);
}

int next_step(int index, int direction, int row, int col)
{
    switch (direction)
    {
    case 0:
        return index + 1;
    case 1:
        return index - 1;
    case 2:
        return index + row;
    case 3:
        return index - row;
    case 4:
        return index + row * col;
    case 5:
        return index - row * col;
    }
}

int repeated(sol *head, int index)
{
    sol *current = head;
    while (current)
    {
        if (current->i == index)
            return 1;
        current = current->next;
    }
    return 0;
}

int last(sol *head)
{
    sol *current = head;
    while (current->next)
        current = current->next;
    return current->i;
}

void find_path(list *first, sol *solution, int index, int end, int direction, int row, int col) //direction 0N 1S 2E 3W
{                                                                                               //index = now (start), end = end
    push(solution, index);

    if (direction <= 5 && can_go(first, index, direction) && !repeated(solution, next_step(index, direction, row, col)) && last(solution) != end)
        find_path(first, solution, next_step(index, direction, row, col), end, 0, row, col);
    if (direction <= 4 && can_go(first, index, direction + 1) && !repeated(solution, next_step(index, direction + 1, row, col)) && last(solution) != end)
        find_path(first, solution, next_step(index, direction + 1, row, col), end, 0, row, col);
    if (direction <= 3 && can_go(first, index, direction + 2) && !repeated(solution, next_step(index, direction + 2, row, col)) && last(solution) != end)
        find_path(first, solution, next_step(index, direction + 2, row, col), end, 0, row, col);
    if (direction <= 2 && can_go(first, index, direction + 3) && !repeated(solution, next_step(index, direction + 3, row, col)) && last(solution) != end)
        find_path(first, solution, next_step(index, direction + 3, row, col), end, 0, row, col);
    if (direction <= 1 && can_go(first, index, direction + 4) && !repeated(solution, next_step(index, direction + 4, row, col)) && last(solution) != end)
        find_path(first, solution, next_step(index, direction + 4, row, col), end, 0, row, col);
    if (direction <= 0 && can_go(first, index, direction + 5) && !repeated(solution, next_step(index, direction + 5, row, col)) && last(solution) != end)
        find_path(first, solution, next_step(index, direction + 5, row, col), end, 0, row, col);

    if (last(solution) == end) //error solved (if condition didint come in, it was else if)
        return;
    else
    {
        pop(solution);
        return;
    }
}

void size1(sol *first)
{
    int count = -1;
    sol *current = first;
    while (current)
    {
        count++;
        current = current->next;
    }
    printf("%d", count);
}

void output(sol *head, char *s)
{
    sol *current = head;

    FILE *fptr = fopen(s, "w");
    while (current->next)
    {
        if (current == head)
            ;
        else
            fprintf(fptr, "%d,", current->i);
        current = current->next;
    }
    fprintf(fptr, "%d", current->i);
    fclose(fptr);
}

int main()
{
    char maze_file_name[100] = "maze3_3x3x2.txt", in_and_out_file_name[100] = "maze3_3x3x2_in_and_out.txt", output_file_name[100] = "solution.txt";
    /*    printf("Please input the maze format file name: ");
    scanf("%s", &maze_file_name);
    printf("Please input the in and out file name: ");
    scanf("%s", &in_and_out_file_name);
    printf("Please input the solution_path file name: ");
    scanf("%s", output_file_name);*/

    list *data_head = readfile(maze_file_name); //maze
    sol *solution = (sol *)malloc(sizeof(sol)); //output solution
    solution->i = 0;
    solution->next = NULL;

    int row = know_row(data_head);
    int col = know_column(data_head);

    int *sae = start_and_end(in_and_out_file_name); //start_and_end

    find_path(data_head, solution, sae[0], sae[1], 0, row, col);
    //    size1(solution);

    output(solution, output_file_name);

    return 0;
}