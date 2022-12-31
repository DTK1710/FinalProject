#pragma once
#include <iostream>
#include <Windows.h>
#include "graphics.h"

using namespace std;
int checkOutOfIndex(BOXNUMBER* arr, bool flag[], int n);
void readData(BOXNUMBER arr[], int& n, int maxSize, bool isVerBox);
void showAll(BOXNUMBER* arr, int n);
int chooseOption(char title[], char options[]);
void emptyStack(int x, int y, int size)
{
	int x1 = x - 5, x2 = x1 + 100;
	int y1 = y, y2 = y1 + 35 * size;
	line(x1, y1, x1, y2, BLUE);
	line(x2, y1, x2, y2, BLUE);
	line(x1, y2, x2, y2, BLUE);
}

struct GRAPHIC_STACK
{
	int maxSize;
	int x, y;
	BOXNUMBER* top;

	void init(int x, int y, int maxSize)
	{
		top = new BOXNUMBER();
		top = nullptr;
		this->x = x;
		this->y = y;
		this->maxSize = maxSize;
		emptyStack(x, y, maxSize);
	}

	bool empty()
	{
		return top == nullptr;
	}

	int size()
	{
		int count = 0;
		BOXNUMBER* p = top;
		while (p != nullptr)
		{
			p = p->next;
			count++;
		}
		return count;
	}

	BOXNUMBER* pop(int x) {
		if (empty())
		{
			char s[20] = "STACK UNDERFLOW!!!";
			showMess(s);
			return nullptr;
		}
		BOXNUMBER* result;
		result = (BOXNUMBER*)calloc(1, sizeof(BOXNUMBER));
		result = top;
		top = top->next;
		result->movey(100, 1);
		result->movex(x, 1);
		result->movey(50, 1);
		return result;
	}

	void showMess(char s[])
	{
		int x = this->x - 25;
		int y = this->y + maxSize * 35 ;
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

	void push(BOXNUMBER* bNum)
	{
		if (size() == maxSize)
		{
			char s[20] = "SATCK OVERFLOW!!!";
			showMess(s);
			return;
		}
		int y = (maxSize - size() - 1) * 35 + this->y;
		if (top == nullptr)
		{
			top = bNum;
			top->next = nullptr;
		}
		else
		{
			bNum->next = top;
			top = bNum;
		}
		bNum->movey(200, 1);
		bNum->movex(x, 1);
		bNum->movey(y, 1);
	}
};


void Insert(BOXNUMBER* arr, int n, GRAPHIC_STACK& stack, bool flagIn[])
{
	int pos = checkOutOfIndex(arr, flagIn,n);
	stack.push(&arr[pos]);
}

void menuStack()
{
	BOXNUMBER* arr = new BOXNUMBER[10];
	int n = 0;
	GRAPHIC_STACK sTack;
	BOXNUMBER* Output = new BOXNUMBER[10];
	int t = 0;
	bool flagIn[100] = {}, flagOut[100] = {};
	sTack.init(1200, 300, 10);
	int temp = 0;
	BOXNUMBER* temp1;
	int x = 1500;
	int opt;
	bool stop = false;
	char title[25] = "Choose one option:\n";
	char options[200] = "Create input.Insert element from input to stack.Delete element from stack.Exit.";
	while (stop != true)
	{
		gotoxy(0, 530);
		showAll(arr, n);
		opt = chooseOption(title, options);
		switch (opt)
		{
		case 0:
			readData(arr, n, 10, true);
			break;
		case 1:
			Insert(arr, n, sTack, flagIn);
			break;
		case 2:
			temp1 = sTack.pop(x -= 100);
			if (temp1 != nullptr)
				Output[t++] = *temp1;
			break;
		case 3:
			stop = true;
			break;
		}
		system("cls");
	}
}
