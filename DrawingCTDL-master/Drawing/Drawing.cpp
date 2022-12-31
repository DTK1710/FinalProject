#include "graphics.h"
#include "graphic_stack.h"
#include "graphic_queue.h"
#include "graphic_dequeue.h"
#include "graphic_singly_linked_list.h"
#include "graphic_double_linked_list.h"
#include "graphic_circle_linked_list.h"
#include "topo_sort.h"
#include <string.h>

void convertNumToString(int n, char s[]);
void showArray(BOXNUMBER arr[], bool flag[], int n);
void addElement(BOXNUMBER arr[], int& n, int maxSize, bool isVerBox);
void deleteElement(BOXNUMBER* arr, int pos, int& n);
int checkValueError();
int checkOutOfIndex(BOXNUMBER* arr, bool flag[], int n);
void readData(BOXNUMBER arr[], int& n, int maxSize, bool isVerBox);
void showAll(BOXNUMBER* arr, int n);
int chooseOption(char title[], char options[]);
void Menu();

int main()
{
    char ini[] = "C:\\TURBOC3\\BGI";
    initgraph();
    Menu();
    return 0;
}

void Menu()
{
    char title[25] = "Choose one option:\n";
    char options[200] = "Stack.Queue.Dequeue.Singly linked list.double linked list.Circle linked list.Topological sort.";
    int opt;
    opt = chooseOption(title, options);
    system("cls");
    switch (opt)
    {
    case 0:
        menuStack();
        break;
    case 1:
        menuQueue();
        break;
    case 2:
        menuDequeue();
        break;
    case 3:
        menuSingleList();
        break;
    case 4:
        menuDoubleList();
        break;
    case 5:
        menuCricleList();
        break;
    case 6:
        runTopo();
        break;
    }
    return;
}
void readData(BOXNUMBER arr[], int& n, int maxSize, bool isVerBox)
{
    int x, y;
    if (isVerBox)
    {
        x = 200;
        y = 300;
    }
    else
    {
        x = 500;
        y = 50;
    }
    cout << "Enter the number of inputs: ";
    n = checkValueError();
    while (n > maxSize)
    {
        cout << "The number of inputs must be less than or equal to max size. Please try again!\n";
        n = checkValueError();
    }
    for (int i = 0; i < n; i++)
    {
        int val = checkValueError();
        BOXNUMBER* bNum = createBoxNumber(val, isVerBox, x, y);
        arr[i] = *bNum;
        x += isVerBox ? 100 : 50;
    }
}

void showArray(BOXNUMBER arr[], bool flag[], int n)
{
    for (int i = 0; i < n; i++)
        if (!flag[i])
            arr[i].show();
}

void deleteElement(BOXNUMBER* arr, int pos, int& n)
{
    for (int i = pos; i < n - 1; i++)
        arr[i] = arr[i + 1];
    n--;
}

int checkValueError()
{
    char input[20];
    bool flag = false;
    int sign = 1;
    double n;
    while (!flag)
    {
        n = 0;
        flag = true;
        cin >> input;
        int i = 0;
        if (input[i] == '-' && strlen(input) != 1)
        {
            sign = -1;
            i++;
        }
        while (i < strlen(input))
        {
            if (input[i] >= '0' && input[i] <= '9')
                n = n * 10 + input[i] - '0';
            else
            {
                flag = false;
                break;
            }
            i++;
        }
        if (n > double(INT_MAX))
            flag = false;
        if (flag == false)
            cout << "Error value. Please try again!\n";
    }
    n *= sign;
    return n;
}

int checkOutOfIndex(BOXNUMBER* arr, bool flag[], int n)
{
    int index;
    bool check = false;
    while (!check)
    {
        check = true;
        index = checkValueError();
        if (index < 0 || index >= n || flag[index] == true)
            check = false;
        if (!check)
            cout << "Index out of range. Please try again!\n";
    }
    flag[index] = true;
    return index;
}

int chooseOption(char title[], char options[])
{
    cout << title;
    char option[300] = "";
    int i = 0, j = 0, order = 0;
    char null[2] = " ";
    for (int i = 0; i < strlen(options); i++)
    {
        if (options[i] != '.')
            option[j++] = options[i];
        else
        {
            option[j] = '\0';
            cout << order << ". " << option << endl;
            j = 0;
            order++;
        }
    }
    int opt = checkValueError();
    while (0 > opt || order < opt)
    {
        cout << "Invalid option. Please try again!\n";
        opt = checkValueError();
    }
    return opt;
}

void addElement(BOXNUMBER arr[], int& n, int maxSize, bool isVerBox)
{
    if (n == 0)
    {
        cout << "You have not create input. Cannot add element\n";
        return;
    }
    if (n + 1 > maxSize)
    {
        cout << "The number of inputs has been reached the limit. Cannot add more element\n";
        return;
    }
    cout << "Enter the number: ";
    int val = checkValueError();
    int x = arr[n - 1].x + (isVerBox ? 110 : 50);
    int y = arr[n - 1].y;
    BOXNUMBER* bNum = createBoxNumber(val, isVerBox, x, y);
    arr[n] = *bNum;
    n++;
}

void showAll(BOXNUMBER* arr, int n)
{
    emptyStack(1200, 300, 10);
    for (int i = 0; i < n; i++)
    {
        arr[i].show();
    }
}
