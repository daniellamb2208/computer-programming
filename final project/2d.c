#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//2D-maze solving the path from given start and end
//input:
//      1. maze file name
//      2. maze start and end name
//      3.output file name
//
//Authority B073040031
//Date      2019 12 29


typedef struct List                             //store the maze using linked list
{
    int index[2];                               //(x, y)
    int direction[4];                           //forbidden or not
    struct List *next;
} list;

void push_back(list *first, int *i, int *nsew)  
{
    list *current = first;
    while (current->next)
        current = current->next;

    list *node = (list *)malloc(sizeof(list));  //initialization
    int count;
    for (count = 0; count < 2; count++)
        node->index[count] = i[count];
    for (count = 0; count < 4; count++)
        node->direction[count] = nsew[count];
    node->next = NULL;

    current->next = node;
}

int size(list *first)                           //return size of the maze
{                                               //testing function
    int count = -1;
    list *current = first;
    while (current)
    {
        count++;
        current = current->next;
    }
    return count;
}

int know_row(list *head)                        //get the number of row
{
    list *current = head;
    while (current->next)
        current = current->next;
    return current->index[1];
}

typedef struct Sol                              //storing the path when solving thr maze, concept of 'stack' using linked list
{                                               //storing the solution
    int i;
    struct Sol *next;
} sol;

void push(sol *head, int path)
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

list *readfile(char *s)                         //read the file of maze
{
    FILE *fptr = fopen(s, "r");
    int index[2], direction[4], i;              // (x , y , n , s ,e , w)

    list *first = (list *)malloc(sizeof(list)); // root of the maze, its default is (0, 0, 0, 0, 0, 0) and *next is NULL
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

int *start_and_end(char *s)                     //read the file of start and end, and return the pointer to int (array)
{
    FILE *fptr = fopen(s, "r");
    int *path = (int *)malloc(sizeof(int) * 2); //dynamic declaration
    fscanf(fptr, "%d,%d", path, path + 1);
    fclose(fptr);

    return path;
}

int can_go(list *first, int index, int compass) //check whether the next step can move to or not, it will check from original maze(type list) 
{
    list *current = first;

    int i;
    for (i = 0; i < index; i++)
        current = current->next;

    return (current->direction[compass] == 0);  //0 for not barrier, others is forbidden
}

int next_step(int index, int direction, int row)//return next step, it is called after can_go() function, so it will not be out of range
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
    default:
        return 0;
    }
}

int repeated(sol *head, int index)              //check if exist the repeated path, for not going to walked place and going backward
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

int last(sol *head)                             //return the last step of solution, for not going backward, too
{
    sol *current = head;
    while (current->next)
        current = current->next;
    return current->i;
}

void find_path(list *first, sol *solution, int index, int end, int direction, int row)  //DFS, recursive 
{                                                                                       //index = now (start), end = end, direction 0N 1S 2E 3W
    push(solution, index); //second-error solved (last-one wasn't in)                   //push_back() firstly, if all direction forbidden, then pop() (take a step back), and find another direction(direction+1)
                                                                                        
    if (direction <= 3 && can_go(first, index, direction) && !repeated(solution, next_step(index, direction, row)) && last(solution) != end)
        find_path(first, solution, next_step(index, direction, row), end, 0, row);
    if (direction <= 2 && can_go(first, index, direction + 1) && !repeated(solution, next_step(index, direction + 1, row)) && last(solution) != end)
        find_path(first, solution, next_step(index, direction + 1, row), end, 0, row);
    if (direction <= 1 && can_go(first, index, direction + 2) && !repeated(solution, next_step(index, direction + 2, row)) && last(solution) != end)
        find_path(first, solution, next_step(index, direction + 2, row), end, 0, row);
    if (direction <= 0 && can_go(first, index, direction + 3) && !repeated(solution, next_step(index, direction + 3, row)) && last(solution) != end)
        find_path(first, solution, next_step(index, direction + 3, row), end, 0, row);

    if (last(solution) == end) //error solved (if condition didint come in, it was else if) //FIND the right solution, ending the function by return and return
        return;
    else
    {
        pop(solution);
        return;
    }
}

void size1(sol *first)                          //testing function
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

void output(sol *head, char *s)                 //finally, output the solution
{
    sol *current = head;

    FILE *fptr = fopen(s, "w");
    while (current->next)                       //for not outputing the last comma
    {
        if (current == head)                    //for not outputing the root of the solution which defualted to all zeros
            ;
        else
            fprintf(fptr, "%d,", current->i);
        current = current->next;
    }
    fprintf(fptr,"%d",current->i);
    fclose(fptr);
}

int main()
{
    char maze_file_name[100], in_and_out_file_name[100], output_file_name[100]; //three c_string for storing the three files' name
    printf("Please input the maze format file name: ");
    scanf("%s", maze_file_name);
    printf("Please input the in and out file name: ");
    scanf("%s", in_and_out_file_name);
    printf("Please input the solution_path file name: ");
    scanf("%s", output_file_name);

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