#pragma once
#include <iostream>
#include <Windows.h>
#include <windows.h>
#include "graphics.h"

using namespace std;

struct GRAPHIC_CIRCLE_LIST
{
	BOXNUMBER* head;
	BOXNUMBER* tail;
	int x, y;

	void init(int x, int y)
	{
		head = tail = nullptr;
		this->x = x, this->y = y;
	}

	int size()
	{
		if (empty())
			return 0;
		int count = 1;
		BOXNUMBER* bNum = head;
		while (bNum != tail)
		{
			count++;
			bNum = bNum->next;
		}
		return count;
	}

	bool empty()
	{
		return head == nullptr || tail == nullptr;
	}

	BOXNUMBER* getEle(int pos)
	{
		if (pos < 0 || pos >= size())
			return nullptr;
		int i = 0;
		BOXNUMBER* ele = head;
		for (int i = 1; i <= pos; i++)
			ele = ele->next;
		return ele;
	}

	void moveEles(int beg, int end, int distance, int direction, int delay)
	{
		BOXNUMBER* p = getEle(beg);
		if (p == nullptr)
			return;
		for (int i = 0; i < distance; i++)
		{
			clearHeadArrow(0);
			clearTailArrow(0);
			BOXNUMBER* ele = p;
			if (p->pre->nextArrow)
			{
				p->pre->clearArrow();
				p->pre->showArrow();
			}
			for (int j = beg; j <= end; j++)
			{
				ele->clearArrow();
				ele->movex(ele->x + direction, 0);
				ele->showArrow();
				ele = ele->next;
			}
			headArrow(GREEN, 0);
			tailArrow(RED, 1);
		}
	}

	void headArrow(int color, int delay)
	{
		line(head->x - 2, head->y + 20, head->x - 31, head->y + 20, color);
		line(head->x - 30, head->y + 20, head->x - 30, head->y + 40, color);
		line(head->x - 30, head->y + 40, tail->x + 120, tail->y + 40, color);
		line(tail->x + 120, tail->y + 40, tail->x + 120, tail->y + 19, color);
		arrow(tail->x + 120, tail->y + 20, tail->x + 92, tail->y + 20, 12, 6, color, color);
		Sleep(delay);
	}

	void tailArrow(int color, int delay)
	{
		line(tail->x + 92, tail->y + 10, tail->x + 120, tail->y + 10, color);
		line(tail->x + 120, tail->y + 10, tail->x + 120, head->y - 11, color);
		line(tail->x + 120, head->y - 10, head->x - 30, head->y - 10, color);
		line(head->x - 30, head->y - 10, head->x - 30, head->y + 10, color);
		arrow(head->x - 30, head->y + 10, head->x - 2, head->y + 10, 12, 6, color, color);
		Sleep(delay);
	}

	void clearHeadArrow(int delay)
	{
		headArrow(BACKGROUND, delay);
	}

	void clearTailArrow(int delay)
	{
		tailArrow(BACKGROUND, delay);
	}

	void refreshHeadArrow()
	{
		clearHeadArrow(0);
		headArrow(GREEN, 0);
	}

	void refreshTailArrow()
	{
		clearTailArrow(0);
		tailArrow(RED, 0);
	}

	void insert(BOXNUMBER* bNum, int pos)
	{
		if (empty())
		{
			bNum->movex(this->x, 1);
			bNum->movey(this->y, 1);
			head = tail = bNum;
			bNum->next = bNum;
			bNum->pre = bNum;
			headArrow(GREEN, 1000);
			tailArrow(RED, 0);
			return;
		}
		BOXNUMBER* p = new BOXNUMBER;
		if (pos == size())
			p = tail;
		else
			p = getEle(pos)->pre;

		if (pos == 0 || pos == size())
		{
			if (pos == 0)
				bNum->movex(this->x, 1);
			else
				bNum->movex(tail->x + 130, 1);
			bNum->movey(this->y - 50, 1);
			moveEles(pos, size() - 1, 130, 1, 1);
			bNum->movey(this->y, 1);
		}
		else
		{
			bNum->movex(p->x + 130, 1);
			bNum->movey(this->y - 50, 1);
			moveEles(pos, size() - 1, 130, 1, 1);
		}

		bNum->next = p->next;
		bNum->next->clearPreArrow(0);
		bNum->next->pre = bNum;
		if (pos == size())
		{
			clearTailArrow(0);
			clearHeadArrow(0);
			bNum->next->showArrow();
			bNum->showArrow();
			tail = bNum;
			tailArrow(RED, 1000);
			headArrow(GREEN, 1000);
		}
		else
		{
			bNum->nextArrow = true;
			bNum->showNextArrow(1000);
			bNum->next->preArrow = true;
			bNum->next->showPreArrow(1000);
		}

		bNum->pre = p;
		bNum->pre->clearNextArrow(0);
		bNum->pre->next = bNum;
		if (pos == 0)
		{
			clearHeadArrow(0);
			clearTailArrow(0);
			bNum->pre->showArrow();
			bNum->showArrow();
			head = bNum;
			headArrow(GREEN, 0);
			head->next->showPreArrow(1000);
			tailArrow(RED, 1000);
		}
		else
		{
			bNum->preArrow = true;
			bNum->showPreArrow(1000);
			bNum->pre->nextArrow = true;
			bNum->pre->showNextArrow(0);
		}
		if (pos != 0 && pos != size())
		{
			while (bNum->y != this->y)
			{
				bNum->next->clearPreArrow(0);
				bNum->pre->clearNextArrow(0);
				bNum->clearArrow();
				bNum->movey(bNum->y + 1, 1);
				bNum->showArrow();
				bNum->pre->showNextArrow(0);
				bNum->next->showPreArrow(1);
				if (bNum->y == this->y - 7)
					tailArrow(RED, 0);
			}
		}
	}

	void remove(int pos)
	{
		BOXNUMBER* bNum = getEle(pos);
		BOXNUMBER* pre = bNum->pre;
		BOXNUMBER* next = bNum->next;
		int len = size();
		if (pos != 0 && pos != len - 1)
		{
			while (bNum->y != this->y + 50)
			{
				bNum->next->clearPreArrow(0);
				bNum->pre->clearNextArrow(0);
				bNum->clearArrow();
				bNum->movey(bNum->y + 1, 1);
				bNum->showArrow();
				bNum->pre->showNextArrow(0);
				bNum->next->showPreArrow(1);
			}
			headArrow(GREEN, 0);
		}

		if (pos == 0)
		{
			clearTailArrow(1000);
			clearHeadArrow(1000);
			Sleep(1000);
		}
		else
		{
			pre->clearNextArrow(1000);
			bNum->clearPreArrow(1000);
		}

		if (pos == len - 1)
		{
			clearHeadArrow(1000);
			clearTailArrow(1000);
		}
		else
		{
			next->clearPreArrow(1000);
			bNum->clearNextArrow(1000);
		}
		bNum->next = nullptr;
		bNum->pre = nullptr;

		if (pos == 0)
		{
			if (len == 1)
			{
				head = tail = nullptr;
				bNum->clear();
				return;
			}
			head = next;
			next->preArrow = false;
		}
			
		if (pos == len - 1)
		{
			tail = pre;
			pre->nextArrow = false;
		}
			

		pre->next = next;
		next->pre = pre;
		if (pos == 0 || pos == len - 1)
		{
			tailArrow(RED, 1000);
			headArrow(GREEN, 1000);
		}
		else
		{
			pre->showNextArrow(1000);
			next->showPreArrow(1000);
		}
		bNum->clear();
		if (pos != len - 1)
			moveEles(pos, size() - 1, 130, -1, 1);
	}
};

int checkValueError();
int chooseOption(char title[], char options[]);
void insertToCircleList(BOXNUMBER* bNum, GRAPHIC_CIRCLE_LIST& g_CircleList);

void insertToCircleList(BOXNUMBER* bNum, GRAPHIC_CIRCLE_LIST& g_CircleList)
{
	cout << "Enter postion: ";
	int pos = checkValueError();
	while (pos < 0 || pos > g_CircleList.size())
	{
		cout << "Out of index!\n";
		pos = checkValueError();
	}
	g_CircleList.insert(bNum, pos);
}

void deleteFromCircleList(GRAPHIC_CIRCLE_LIST& g_CircleList)
{
	cout << "Enter postion: ";
	int pos = checkValueError();
	while (pos < 0 || pos >= g_CircleList.size())
	{
		cout << "Out of index!\n";
		pos = checkValueError();
	}
	g_CircleList.remove(pos);
}

void menuCricleList()
{
	BOXNUMBER* input = new BOXNUMBER;
	GRAPHIC_CIRCLE_LIST g_CricleList;
	g_CricleList.init(200, 150);
	char title[25] = "Choose one option:\n";
	char options[200] = "Create input.Insert to circle linked list.Delete element from circle linked list.Exit.";
	int opt;
	bool stop = false;
	do
	{
		gotoxy(0, 530);
		opt = chooseOption(title, options);
		switch (opt)
		{
		case 0: input = createBoxNumber(30, 50); break;
		case 1: insertToCircleList(input, g_CricleList); break;
		case 2: deleteFromCircleList(g_CricleList); break;
		case 3: stop = true; break;
		}
		clearRange(0, 530);
	} while (stop != true);
}
