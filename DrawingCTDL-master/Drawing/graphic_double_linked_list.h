#pragma once

#include <iostream>
#include <Windows.h>
#include <windows.h>
#include "graphics.h"

using namespace std;

struct GRAPHIC_DOUBLE_LINKLIST
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

	void moveEles(int beg, int end, int distance, int direction)
	{
		BOXNUMBER* p = getEle(beg);
		if (p == nullptr)
			return;
		int i = 0;
		while (i != distance)
		{
			BOXNUMBER* ele = p;
			if (p->pre != nullptr)
			{
				if (p->pre->nextArrow)
				{
					p->pre->clearArrow();
					p->pre->showArrow();
				}
			}
			for (int j = beg; j <= end; j++)
			{
				ele->clearArrow();
				ele->movex(ele->x + direction, 0);
				ele->showArrow();
				ele = ele->next;
			}
			i += 1;
			Sleep(1);
		}
	}

	void push(BOXNUMBER* bNum)
	{
		if (empty())
		{
			bNum->movex(this->x, 1);
			bNum->movey(this->y, 1);
			head = tail = bNum;
			bNum->next = nullptr;
			bNum->pre = nullptr;
			return;
		}

		bNum->movex(this->x, 1);
		bNum->movey(this->y - 50, 1);
		moveEles(0, size() - 1, 130, 1);
		bNum->movey(this->y, 1);
		bNum->next = head;
		bNum->nextArrow = true;
		bNum->showArrow();
		Sleep(1000);

		head->pre = bNum;
		head->preArrow = true;
		head->showArrow();
		Sleep(1000);

		head->show();

		head = bNum;

		bNum->show();
	}

	void push_back(BOXNUMBER* bNum)
	{
		if (empty())
		{
			bNum->movex(this->x, 0);
			bNum->movey(this->y, 0);
			head = tail = bNum;
			bNum->next = nullptr;
			bNum->pre = nullptr;
			return;
		}
		bNum->movex(tail->x + 130, 0);
		bNum->movey(this->y - 50, 0);
		bNum->movey(this->y, 0);

		tail->next = bNum;
		tail->nextArrow = true;
		tail->showArrow();
		Sleep(1000);

		bNum->pre = tail;
		bNum->preArrow = true;
		bNum->next = nullptr;
		bNum->showArrow();
		Sleep(1000);
						
		tail = bNum;

	}

	void insert(BOXNUMBER* bNum, int pos)
	{
		if (pos == 0)
		{
			push(bNum);
			return;
		}
		if (pos == size())
		{
			push_back(bNum);
			return;
		}
		BOXNUMBER* p = new BOXNUMBER();
		BOXNUMBER* q = new BOXNUMBER();
		p = getEle(pos);
		q = p->pre;
		
		bNum->movex(p->x, 1);
		bNum->movey(p->y-50, 1);

		moveEles(pos, size() - 1, 130, 1);

		bNum->next = p;
		q->clearNextArrow(0);
		p->clearPreArrow(0);
		p->pre = bNum;
		bNum->nextArrow = true;
		bNum->showNextArrow(1000);
		p->preArrow = true;
		p->showPreArrow(1000);

		bNum->pre = q;
		q->clearNextArrow(0);
		q->next = bNum;
		bNum->preArrow = true;
		bNum->showPreArrow(1000);
		q->nextArrow = true;
		q->showNextArrow(1000);
		while (bNum->y != this->y)
		{
			q->clearNextArrow(0);
			p->clearPreArrow(0);
			bNum->clearArrow();
			bNum->movey(bNum->y + 1, 1);
			bNum->showArrow();
			p->showPreArrow(0);
			q->showNextArrow(1);
		}
	}

	void remove(int pos)
	{
		if (pos < 0 || pos > size()-1)
			return;

		if (pos == 0)
		{
			if (size() == 1)
			{
				head->clear();
				head = tail = nullptr;
				return;
			}
			head->clear();
			Sleep(1000);
			head->clearNextArrow(0);
			Sleep(1000);
			head = head->next;
			head->clearPreArrow(0);
			head->pre = nullptr;
			head->preArrow = false;
			head->show();
			moveEles(0, size() - 1, 130, -1);
			return;
		}

		if (pos == size() - 1)
		{
			tail->clear();
			Sleep(1000);
			tail->clearPreArrow(0);
			Sleep(1000);
			tail = tail->pre;
			tail->clearNextArrow(0);
			tail->next = nullptr;
			return;
		}
		
		BOXNUMBER* bNum = getEle(pos);
		BOXNUMBER* next = bNum->next;
		BOXNUMBER* pre = bNum->pre;

		bNum->clearArrow();
		next->clearPreArrow(0);
		pre->clearNextArrow(0);

		bNum->clear();

		pre->next = next;
		next->pre = pre;

		moveEles(pos, size()-1, 130, -1);

		pre->showNextArrow(0);
		next->showPreArrow(0);
	}
};

int checkValueError();
int chooseOption(char title[], char options[]);
BOXNUMBER* createBoxNumberForList(int x, int y);
void insertToDoubleList(BOXNUMBER* bNum, GRAPHIC_DOUBLE_LINKLIST& g_DoubleList);

void insertToDoubleList(BOXNUMBER* bNum, GRAPHIC_DOUBLE_LINKLIST& g_DoubleList)
{
	cout << "Enter postion: ";
	int pos = checkValueError();
	while (pos < 0 || pos > g_DoubleList.size())
	{
		cout << "Out of index!\n";
		pos = checkValueError();
	}
	g_DoubleList.insert(bNum, pos);
}

void deleteFromDoubleList(GRAPHIC_DOUBLE_LINKLIST& g_DoubleList)
{
	cout << "Enter postion: ";
	int pos = checkValueError();
	while (pos < 0 || pos >= g_DoubleList.size())
	{
		cout << "Out of index!\n";
		pos = checkValueError();
	}
	g_DoubleList.remove(pos);
}

void menuDoubleList()
{
	BOXNUMBER* input = new BOXNUMBER;
	GRAPHIC_DOUBLE_LINKLIST g_DoubleList;
	g_DoubleList.init(200, 150);
	gotoxy(0, 530);
	char title[25] = "Choose one option:\n";
	char options[200] = "Create input.Push.Push back.Insert to double linked list.Delete element from double linked list.Exit.";
	int opt;
	int stop = false;
	do
	{
		opt = chooseOption(title, options);
		switch (opt)
		{
		case 0: input = createBoxNumber(30, 50); break;
		case 1: g_DoubleList.push(input); break;
		case 2: g_DoubleList.push_back(input); break;
		case 3: insertToDoubleList(input, g_DoubleList); break;
		case 4: deleteFromDoubleList(g_DoubleList); break;
		case 5: stop = true; break;
		}
		clearRange(0, 530);
	} while (stop != true);
}
