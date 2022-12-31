#pragma once
#include <iostream>
#include <Windows.h>
#include "graphics.h"

using namespace std;

struct GRAPHIC_QUEUE
{
	int maxSize;
	int x, y;
	BOXNUMBER* rear;
	BOXNUMBER* front;

	void init(int x, int y, int maxSize)
	{
		front = rear = nullptr;
		this->x = x;
		this->y = y;
		this->maxSize = maxSize;
		showQueue();
	}

	void showQueue()
	{
		emptyQueue(x, y, maxSize, RED);
	}

	bool empty()
	{
		return front == nullptr || rear == nullptr;
	}

	bool full()
	{
		return size() == maxSize;
	}

	int size()
	{
		int count = 0;
		BOXNUMBER* p = front;
		while (p != nullptr)
		{
			p = p->next;
			count++;
		}
		return count;
	}

	BOXNUMBER* top()
	{
		return front;
	}

	void movexAll(int distance, int direction)
	{
		int i = 0;
		while (i < distance)
		{
			BOXNUMBER* p;
			if (direction > 0)
			{
				p = front;
				while (p != nullptr)
				{
					p->movex(p->x + direction, 0);
					p = p->next;
				}
			}
			else
			{
				p = rear;
				while (p != nullptr)
				{
					p->movex(p->x + direction, 0);
					p = p->pre;
				}
			}
			Sleep(1);
			i++;
		}
	}

	void push(BOXNUMBER* bNum)
	{
		if (full())
		{
			char s[20] = "QUEUE OVERFLOW!!!";
			showMess(s);
			return;
		}
		if (empty())
		{
			front = bNum;
			rear = bNum;
		}
		else
		{
			rear->next = bNum;
			bNum->pre = bNum;
			rear = bNum;
		}
		int x = this->x + (maxSize - 1 - size()) * 15 - size() * 2;
		bNum->movey(y, 1);
		bNum->movex(x, 1);
		movexAll(15, 1);
	}

	BOXNUMBER* pop(int x, int y)
	{
		if (empty())
		{
			char s[20] = "QUEUE UNDERFLOW!!!";
			showMess(s);
			return nullptr;
		}
	    BOXNUMBER* res = nullptr;
		movexAll(17, 1);
		res = front;
		BOXNUMBER* next = front->next;
		if (next != nullptr)
		{
			next->pre = nullptr;
			res->next = nullptr;
		}	
		front = next;
		res->movex(x, 1);
		res->movey(y, 1);
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
				color = RGB(255, 255, 255);
			else
				color = RGB(255, 0, 0);
			displayText(x, y, s, color, 1);
			Sleep(200);
		}
		clrscr(x + 8, y + 30, x + (strlen(s) + 1) * 8, y + 60);
	}

	void showAll()
	{
		BOXNUMBER* p = front;
		emptyQueue(x, y, maxSize, 1);
		while (p != nullptr)
		{
			p->show();
			p = p->next;
		}
	}
};

int checkOutOfIndex(BOXNUMBER* arr, bool flag[], int n);
void readData(BOXNUMBER input[], int& n, int maxSize, bool isVerBox);
void insertToQueue(BOXNUMBER input[], int n, bool flag[], GRAPHIC_QUEUE& g_Queue);
void deleteFromQueue(BOXNUMBER output[], int& n, GRAPHIC_QUEUE& g_Queue);
int chooseOption(char title[], char options[]);
void addElement(BOXNUMBER arr[], int& n, int maxSize, bool isVerBox);
void menuQueue();

void insertToQueue(BOXNUMBER input[], int n, bool flag[], GRAPHIC_QUEUE& g_Queue)
{
	cout << "Enter the index of element in input: ";
	int index = checkOutOfIndex(input, flag, n);
		g_Queue.push(&input[index]);
}

void deleteFromQueue(BOXNUMBER output[], int& n, GRAPHIC_QUEUE& g_Queue)
{
	int x = (n == 0) ? 1800 :(output[n - 1].x - 50);
	int y = g_Queue.y + 110;
	BOXNUMBER* res;
	res = g_Queue.pop(x, y);
	if (res != nullptr)
		output[n++] = *res;
}

void menuQueue()
{
	int nIn = 0, nOut = 0;
	int maxSize = 10;
	BOXNUMBER input[100];
	BOXNUMBER output[100];
	bool flagIn[100] = {}, flagOut[100] = {};
	GRAPHIC_QUEUE g_Queue;
	char title[25] = "Choose one option:\n";
	char options[200] = "Create input.Add more input.Insert element from input to queue.Delete element from queue.Exit.";
	int opt;
	bool stop = false;
	g_Queue.init(1000, 290, maxSize);
	gotoxy(0, 530);
	do
	{
		opt = chooseOption(title, options);
		g_Queue.showQueue();
		switch (opt)
		{
		case 0: readData(input, nIn, 100, false); break;
		case 1: addElement(input, nIn, 100, false); break;
		case 2: insertToQueue(input, nIn, flagIn, g_Queue); break;
		case 3: deleteFromQueue(output, nOut, g_Queue); break;
		case 4: stop = true; break;
		}
		clearRange(0, 530);
	} while (stop != true);

}