#pragma once
#include <iostream>
#include <Windows.h>
#include "graphics.h"

using namespace std;

struct GRAPHIC_DEQUE
{
	int maxSize;
	int x, y;
	BOXNUMBER* leftMost;
	BOXNUMBER* rightMost;

	void init(int x, int y, int maxSize)
	{
		leftMost = rightMost = nullptr;
		this->x = x;
		this->y = y;
		this->maxSize = maxSize;
		showDequeue();
	}

	void showDequeue()
	{
		emptyQueue(x, y, maxSize, WHITE);
	}

	bool empty()
	{
		return leftMost == nullptr || rightMost == nullptr;
	}

	bool full()
	{
		return size() == maxSize;
	}

	int size()
	{
		int count = 0;
		BOXNUMBER* p = leftMost;
		while (p != nullptr)
		{
			p = p->next;
			count++;
		}
		return count;
	}

	BOXNUMBER* top(bool isLeft)
	{
		if (isLeft)
		    return leftMost;
		return rightMost;
	}

	void movexAll(int distance, int direction)
	{
		int i = 0;
		while (i < distance)
		{
			BOXNUMBER* p;
			if (direction == 1)
			{
				p = leftMost;
				while (p != nullptr)
				{
					p->movex(p->x + direction, 1);
					p = p->next;
				}
			}
			else
			{
				p = rightMost;
				while (p != nullptr)
				{
					p->movex(p->x + direction, 1);
					p = p->pre;
				}
			}
			i++;

		}
	}

	void push(BOXNUMBER* bNum, bool isLeft)
	{
		if (full())
		{
			char s[100] = "DEQUEUE OVERFLOW!!!";
			showMess(s);
			return;
		}
		if (empty())
		{
			leftMost = bNum;
			rightMost = bNum;
		}
		else
		{
			if (isLeft)
			{
				bNum->next = leftMost;
				leftMost->pre = bNum;
				leftMost = bNum;
			}
			else
			{
				rightMost->next = bNum;
				bNum->pre = rightMost;
				rightMost = bNum;
			}
		}
		if (isLeft)
		{
			int x = this->x + (maxSize - 1 - size()) * 15 - size() * 2;
			bNum->movey(y, 1);
			bNum->movex(x, 1);
			movexAll(17, 1);
		}
		else
		{
			int x = this->x + (maxSize - 1 + size()) * 15 + size() * 2;
			bNum->movey(this->y - 130, 1);
			bNum->movex(this->x + maxSize * 30 + 30, 1);
			bNum->movey(y, 1);
			bNum->movex(x, 1);
			movexAll(17, -1);
		}
	}

	BOXNUMBER* pop(bool isLeft, int x, int y)
	{
		if (empty())
		{
			char s[100] = "DEQUEUE UNDERFLOW!!!";
			showMess(s);
			return nullptr;
		}
	    BOXNUMBER* res = nullptr;
		if (isLeft)
		{
			movexAll(15, -1);
			res = leftMost;
			BOXNUMBER* next = leftMost->next;
			if (next != nullptr)
			{
				next->pre = nullptr;
				leftMost->next = nullptr;
			}	
			leftMost = next;
			res->movex(this->x - 40, 1);
			res->movey(y, 1);
			res->movex(x, 1);
		}
		else
		{
			movexAll(15, 1);
			res = rightMost;
			BOXNUMBER* pre = rightMost->pre;
			if (pre != nullptr)
			{
				pre->next = nullptr;
				rightMost->pre = nullptr;
			}
			rightMost = pre;
			res->movex(x, 1);
			res->movey(y, 1);
		}
		return res;
	}

	void showMess(char s[])
	{
		int x = this->x + maxSize * 15 - int(4.3 * strlen(s) + 0.5);
		int y = this->y - 40;
		for (int i = 0; i < 10; i++)
		{
			int color;
			if (i % 2 == 0)
				color = WHITE;
			else
				color = RED;
			displayText(x, y, s, color, 1);
			Sleep(200);
		}
		clrscr(x + 8, y + 30, x + (strlen(s) + 1) * 8, y + 60);
	}
};

void convertNumToString(int n, char s[]);
int checkValueError();
int checkOutOfIndex(BOXNUMBER* arr, bool flag[], int n);
void readData(BOXNUMBER input[], int& n, int maxSize, bool isVerBox);
void insertToDequeue(BOXNUMBER input[], int n, bool flag[], GRAPHIC_DEQUE& g_Dequeue);
void deleteFromDequeue(BOXNUMBER output[], int& n, GRAPHIC_DEQUE& g_Dequeue);
int chooseOption(char title[], char options[]);
void addElement(BOXNUMBER arr[], int& n, int maxSize, bool isVerBox);
void menuDequeue();

void insertToDequeue(BOXNUMBER input[], int n, bool flag[], GRAPHIC_DEQUE& g_Dequeue)
{
	cout << "Enter the index of element in input: ";
	int index = checkOutOfIndex(input, flag, n);
	char title [80] = "What side do you want to insert:\n";
	char options[15] = "Left.Right.";
	int opt = chooseOption(title, options);
	if (opt == 0)
		g_Dequeue.push(&input[index], true);
	else
		g_Dequeue.push(&input[index], false);
}

void deleteFromDequeue(BOXNUMBER output[], int& n, GRAPHIC_DEQUE& g_Dequeue)
{
	char title[80] = "What side do you want to delete:\n";
	char options[15] = "Left.Right.";
	int opt = chooseOption(title, options);
	int x = (n == 0) ? 1800 : (output[n - 1].x - (output[n - 1].isVer ? 110 : 50));
	int y = g_Dequeue.y + 110;
	BOXNUMBER* res;
	if (opt == 0)
		res = g_Dequeue.pop(true, x, y);
	else
		res = g_Dequeue.pop(false, x, y);
	if (res != nullptr)
		output[n++] = *res;
}

void menuDequeue()
{
	int nIn = 0, nOut = 0;
	int maxSize = 10;
	BOXNUMBER input[100];
	BOXNUMBER output[100];
	bool flagIn[100] = {}, flagOut[100] = {};
	GRAPHIC_DEQUE g_Deque;
	char title[25] = "Choose one option:\n";
	char options[200] = "Create input.Add more input.Insert element from input to dequeue.Delete element from dequeue.Exit.";
	int opt;
	g_Deque.init(1100, 290, maxSize);
	bool stop = false;
	do
	{
		gotoxy(0, 530);
		opt = chooseOption(title, options);
		g_Deque.showDequeue();
		switch (opt)
		{
		case 0: readData(input, nIn, 100, false); break;
		case 1: addElement(input, nIn, 100, false); break;
		case 2: insertToDequeue(input, nIn, flagIn, g_Deque); break;
		case 3: deleteFromDequeue(output, nOut, g_Deque); break;
		case 4: stop = true; break;
		}
		clearRange(0, 530);
	} while (stop != true);

}