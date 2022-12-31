#pragma once

#include <iostream>
#include <Windows.h>
#include <windows.h>
#include "graphics.h"

using namespace std;

struct GRAPHIC_SINGLE_LINKLIST
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
		int count = 0;
		BOXNUMBER* p = head;
		while (p != nullptr)
		{
			count++;
			p = p->next;
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
		int i = 0;
		while (i != distance)
		{
			BOXNUMBER* ele = p;
			for (int j = beg; j <= end; j++)
			{
				ele->clearArrow();
				ele->movex(ele->x + direction, 0);
				ele->showArrow();
				ele = ele->next;
			}
			i += 1;
			Sleep(delay);
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
			return;
		}

		bNum->movex(this->x, 1);
		bNum->movey(this->y - 50, 1);
		moveEles(0, size() - 1, 130, 1, 1);
		bNum->movey(this->y, 1);

		bNum->next = head;
		bNum->nextArrow = true;
		bNum->showNextArrow(1000);
		head->show();

		head = bNum;

		bNum->show();
	}



	void push_back(BOXNUMBER* bNum)
	{

		if (empty())
		{
			bNum->movex(this->x, 1);
			bNum->movey(this->y, 1);
			head = tail = bNum;
			bNum->next = nullptr;
			return;
		}

		bNum->movex(tail->x + 130, 1);
		bNum->movey(this->y - 50, 1);
		bNum->movey(this->y, 1);
		Sleep(1000);
		tail->next = bNum;
		tail->nextArrow = true;
		tail->showArrow();
		Sleep(1000);

		bNum->next = nullptr;
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

		BOXNUMBER* p = new BOXNUMBER;
		p = getEle(pos - 1);
		

		bNum->movex(p->x + 130, 1);
		bNum->movey(this->y - 50, 1);
		p->clearNextArrow(0);
		Sleep(1000);
		moveEles(pos, size() - 1, 130, 1, 1);
		bNum->next = p->next;
		bNum->nextArrow = true;
		bNum->showNextArrow(1000);
		p->next = bNum;
		p->nextArrow = true;
		p->showNextArrow(1000);
		while (bNum->y != this->y)
		{
			p->clearNextArrow(1);
			bNum->clearArrow();
			bNum->movey(bNum->y + 1, 1);
			bNum->showNextArrow(1);
			p->showNextArrow(1);
			Sleep(1);
		}
	}

	void remove(int pos)
	{
		if (pos < 0 || pos > size() - 1)
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
			head->clearNextArrow(1);
			head->nextArrow = false;

			Sleep(1000);
			head = head->next;
			head->show();

			moveEles(0, size() - 1, 130, -1,  1);
			return;
		}

		if (pos == size() - 1)
		{
			BOXNUMBER* temp = getEle(pos - 1);
			temp->clearArrow();
			temp->nextArrow = false;
			Sleep(1000);
			tail->clear();
			temp->next = nullptr;
			tail = temp;
			return;
		}

		BOXNUMBER* bNum = getEle(pos);
		BOXNUMBER* pre = getEle(pos - 1);


		bNum->clear();
		Sleep(1000);
		bNum->clearArrow();
		bNum->nextArrow = false;
		

		pre->next = bNum->next;
		pre->clearNextArrow(1);

		moveEles(pos, size() - 1, 130, -1, 1);

		pre->showNextArrow(1);
	}
};

int checkValueError();
int chooseOption(char title[], char options[]);
BOXNUMBER* createBoxNumberForList(int x, int y);
void insertToSingleList(BOXNUMBER* bNum, GRAPHIC_SINGLE_LINKLIST& g_SingleList);

void insertToSingleList(BOXNUMBER* bNum, GRAPHIC_SINGLE_LINKLIST& g_SingleList)
{
	cout << "Enter postion: ";
	int pos = checkValueError();
	while (pos < 0 || pos > g_SingleList.size())
	{
		cout << "Out of index!\n";
		pos = checkValueError();
	}
	g_SingleList.insert(bNum, pos);
}

void deleteFromSingleList(GRAPHIC_SINGLE_LINKLIST& g_SingleList)
{
	cout << "Enter postion: ";
	int pos = checkValueError();
	while (pos < 0 || pos >= g_SingleList.size())
	{
		cout << "Out of index!\n";
		pos = checkValueError();
	}
	g_SingleList.remove(pos);
}

void menuSingleList()
{
	BOXNUMBER* input = new BOXNUMBER;
	GRAPHIC_SINGLE_LINKLIST g_SingleList;
	g_SingleList.init(200, 150);
	gotoxy(0, 530);
	char title[25] = "Choose one option:\n";
	char options[200] = "Create input.Push.Push_back.Insert to singly linked list.Delete element from singly linked list.Exit.";
	int opt;
	bool stop = false;
	do
	{
		opt = chooseOption(title, options);
		switch (opt)
		{
		case 0: input = createBoxNumber(30, 50); break;
		case 1: g_SingleList.push(input); break;
		case 2: g_SingleList.push_back(input); break;
		case 3: insertToSingleList(input, g_SingleList); break;
		case 4: deleteFromSingleList(g_SingleList); break;
		case 5: stop = true; break;
		}
		clearRange(0, 530);
	} while (stop != true);
}
