#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct List
{
    int index[2];
    int direction[4];
    struct List *next;
} list;

void push_back(list *first, int *i, int *nsew)
{
    list *current = first;
    while (current->next)
        current = current->next;

    list *node = (list *)malloc(sizeof(list));
    int count;
    for (count = 0; count < 2; count++)
        node->index[count] = i[count];
    for (count = 0; count < 4; count++)
        node->direction[count] = nsew[count];
    node->next = NULL;

    current->next = node;
}

int size(list *first)
{
    int count = -1;
    list *current = first;
    while (current)
    {
        count++;
        current = current->next;
    }
    return count;
}

int know_row(list *head)
{
    list *current = head;
    while (current->next)
        current = current->next;
    return current->index[1];
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
    int index[2], direction[4], i;
    char c; //comma

    list *first = (list *)malloc(sizeof(list));
    first->index[0] = 0;
    first->index[1] = 0;
    for (i = 0; i < 4; i++)
        first->direction[i] = 0;
    first->next = NULL;

    while (1)
    {
        fscanf(fptr, "%d,%d,%d,%d,%d,%d", &index[0], &index[1], &direction[0], &direction[1], &direction[2], &direction[3]);
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
    int *path = (int *)malloc(sizeof(int) * 2);
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

int next_step(int index, int direction, int row)
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

void find_path(list *first, sol *solution, int index, int end, int direction, int row) //direction 0N 1S 2E 3W
{                                                                                      //index = now (start), end = end
    push(solution, index);                                                             //second-error solved

    if (direction <= 3 && can_go(first, index, direction) && !repeated(solution, next_step(index, direction, row)) && last(solution) != end)
        find_path(first, solution, next_step(index, direction, row), end, 0, row);
    if (direction <= 2 && can_go(first, index, direction + 1) && !repeated(solution, next_step(index, direction + 1, row)) && last(solution) != end)
        find_path(first, solution, next_step(index, direction + 1, row), end, 0, row);
    if (direction <= 1 && can_go(first, index, direction + 2) && !repeated(solution, next_step(index, direction + 2, row)) && last(solution) != end)
        find_path(first, solution, next_step(index, direction + 2, row), end, 0, row);
    if (direction <= 0 && can_go(first, index, direction + 3) && !repeated(solution, next_step(index, direction + 3, row)) && last(solution) != end)
        find_path(first, solution, next_step(index, direction + 3, row), end, 0, row);

    if (last(solution) == end) //error solved
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
    char maze_file_name[100] = "maze_prob1_100_by_100.txt", in_and_out_file_name[100] = "maze_prob1_100_by_100_in_and_out2.txt", output_file_name[100] = "solution.txt";
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
    int *sae = start_and_end(in_and_out_file_name); //start_and_end
    find_path(data_head, solution, sae[0], sae[1], 0, row);
    //    size1(solution);

    output(solution, output_file_name);

    return 0;
}