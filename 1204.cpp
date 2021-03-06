// 1204.cpp: 定义控制台应用程序的入口点。
//

#include <iostream>
#include <cstring>
using namespace std;

struct Node
{
	char data[2111] = { ' ' };
	int rowNum, colNum;
	Node *next,*prev;
	Node() { rowNum = 0; colNum = 0; next = NULL; prev = NULL; }
};

class Text
{
private:
	Node *head,*tail;
	int row;
public:
	Text() { head = new Node; head->rowNum = 0; tail = new Node; head->next = tail; tail->prev = head; row = 0; }
	~Text();
	void addLine(const char *newLine);
	void list(int n1, int n2);
	void ins(int i, int j, char *str);
	void del(int i, int j, int num);
	void display() { if (row == 0)return; list(1, row); return; }
};

int main()
{
	char txt[2111], command[5] = { ' ' }, instxt[211] = { ' ' }, tmp;
	Text newText;
	int i, j, num;
	while (true)
	{
		cin.getline(txt, 2111, '\n');
		if (strcmp(txt, "******") == 0)
			break;
		newText.addLine(txt); 
	}

	while (true)
	{
		cin.getline(command, 5, ' ');
		if (strcmp(command, "list") == 0)
		{
			cin >> i >> j;
			cin.get(tmp);
			newText.list(i, j);
		}
		else if (strcmp(command, "ins") == 0)
		{
			cin >> i >> j;
			cin.get(tmp);
			cin.getline(instxt, 211, '\n');
			newText.ins(i, j, instxt);
		}
		else if (strcmp(command, "del") == 0)
		{
			cin >> i >> j >> num;
			cin.get(tmp);
			newText.del(i, j, num);
		}
		else if (strcmp(command, "quit") == 0)
		{
			newText.display();
			break;
		}
		else
			break;
	}

	return 0;
}

Text::~Text()
{
	Node *tmp = head->next, *p;
	while (tmp->next != NULL)
	{
		p = tmp->next;
		delete tmp;
		tmp = p;
	}
	delete head;
	delete tail;
}

void Text::addLine(const char *newLine)
{
	Node *tmp = new Node;
	strcpy(tmp->data, newLine);
	tmp->next = tail;
	tmp->prev = tail->prev;
	tmp->prev->next = tmp;
	tail->prev = tmp;
	if (tmp->prev == head)
		tmp->rowNum = 1;
	else
		tmp->rowNum = tmp->prev->rowNum + 1;
	tmp->colNum = strlen(tmp->data);
	row += 1;
	tail->rowNum = row + 1;
}

void Text::list(int n1, int n2)
{
	if (n1<1 || n2>row || n2 < n1)
	{
		cout << "Error!" << endl;
		return;
	}
	Node *tmp = head->next;
	if (n1 == n2)
	{
		while (tmp->rowNum != n1)
			tmp = tmp->next;
		cout << tmp->data << endl;
		return;
	}
	while (tmp->rowNum != n1)
		tmp = tmp->next;
	while (tmp->rowNum != n2+1)
	{
		cout << tmp->data << endl;
		tmp = tmp->next;
	}
	return;
}

void Text::ins(int i, int j, char *str)
{
	if (i<1 || i>row)
	{
		cout << "Error!" << endl;
		return;
	}
	Node *tmp = head->next;
	while (tmp->rowNum != i)
		tmp = tmp->next;
	if (j > tmp->colNum + 1||j<1)
	{
		cout << "Error!" << endl;
		return;
	}
	int len = strlen(str);
	tmp->data[tmp->colNum+len] = '\0';
	for (int k = tmp->colNum + len; k > j+len-1; k--)
	{
		tmp->data[k-1] = tmp->data[k - len-1];
	}
	for (int k = j; k < j + len; k++)
	{
		tmp->data[k-1] = str[k - j];
	}
	tmp->colNum += len;
	return;
}

void Text::del(int i, int j, int num)
{
	if (i<1 || i>row)
	{
		cout << "Error!" << endl;
		return;
	}
	Node *tmp = head->next;
	while (tmp->rowNum != i)
		tmp = tmp->next;
	if (j < 1 || num<0 || j + num>tmp->colNum + 1)
	{
		cout << "Error!" << endl;
		return;
	}
	if (num == 0)
		return;
	for (int k = j; k <tmp->colNum-num+2; k++)
	{
		tmp->data[k-1] = tmp->data[k + num-1];
	}
	tmp->colNum -= num;
	return;
}