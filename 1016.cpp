#include <iostream>

using namespace std;
struct node
{
	int num;
	node *prev, *next;
	node() :next(NULL), prev(NULL) {}
	~node() {}
};
class Bigint
{
private:
	node * head, *tail;

public:
	Bigint();
	Bigint(int value);
	Bigint(const Bigint &obj);
	~Bigint() { clear(); delete head; delete tail; }

	void clear();
	Bigint operator+(const Bigint &obj);
	Bigint operator-(const Bigint &obj);
	Bigint operator/(const Bigint &obj);
	Bigint &operator=(const Bigint &obj);
	bool negative();
	friend istream & operator>>(istream &is, const Bigint &obj);
	friend ostream & operator<<(ostream &os, const Bigint &obj);
};

int main()
{
	Bigint a, b, res;
	cin >> a >> b;
	res = a / b;
	cout << res;
	return 0;
}

Bigint::Bigint()
{
	head = new node;
	tail = new node;
	head->next = tail;
	head->prev = NULL;
	tail->next = NULL;
	tail->prev = head;
}

Bigint::Bigint(int value)
{
	node *p;
	head = new node;
	tail = new node;
	head->next = tail;
	tail->prev = head;
	p = tail;
	if (value == 0)
	{
		p->prev = new node;
		p->prev->num = 0;
		p->prev->next = tail;
		p->prev->prev = head;
		head->next = p->prev;
	}
	while (value>0)
	{
		p->prev = new node;
		p->prev->num = value % 10;
		p->prev->next = p;
		p->prev->prev = head;
		head->next = p->prev;
		p = p->prev;
		value = value / 10;
	}
}

Bigint::Bigint(const Bigint &obj)
{
	node *p, *q;
	head = new node;
	tail = new node;
	head->prev = NULL;
	p = obj.head;
	q = head;
	while (p->next != obj.tail)
	{
		q->next = new node;
		q->next->num = p->next->num;
		q->next->prev = q;
		q = q->next;
		p = p->next;
	}
	q->next = tail;
	tail->prev = q;
}

Bigint &Bigint::operator=(const Bigint &obj)
{
	if (this == &obj)
		return *this;
	clear();
	delete head;
	delete tail;
	node *p, *q;
	head = new node;
	tail = new node;
	head->prev = NULL;
	p = obj.head;
	q = head;
	while (p->next != obj.tail)
	{
		q->next = new node;
		q->next->num = p->next->num;
		q->next->prev = q;
		q = q->next;
		p = p->next;
	}
	q->next = tail;
	tail->prev = q;
	return *this;
}

void Bigint::clear()
{
	node *p, *q;
	p = head->next;
	while (p != tail)
	{
		q = p->next;
		delete p;
		p = q;
	}
	head->next = NULL;
	tail->prev = NULL;
	return;
}

Bigint Bigint::operator+(const Bigint &obj)
{
	Bigint sum;
	node *p, *q, *r;
	p = tail;
	q = obj.tail;
	r = sum.tail;
	while (p->prev != head && q->prev != obj.head)
	{
		p = p->prev;
		q = q->prev;
		r->prev = new node;
		r->prev->next = r;
		r->prev->num = p->num + q->num;
		r = r->prev;
	}
	if (q->prev != obj.head)
	{
		while (q->prev != obj.head)
		{
			q = q->prev;
			r->prev = new node;
			r->prev->next = r;
			r->prev->num = q->num;
			r = r->prev;
		}
	}
	else if (p->prev != head)
	{
		while (p->prev != head)
		{
			p = p->prev;
			r->prev = new node;
			r->prev->next = r;
			r->prev->num = p->num;
			r = r->prev;
		}
	}
	r->prev = sum.head;
	sum.head->next = r;
	r = sum.tail;
	while (r->prev != sum.head)
	{
		r = r->prev;
		if (r->num < 10)
			continue;
		else
		{
			r->num -= 10;
			if (r->prev == sum.head)
			{
				r->prev = new node;
				r->prev->next = r;
				r->prev->prev = sum.head;
				sum.head->next = r->prev;
				r->prev->num = 1;
			}
			else
			{
				r->prev->num += 1;
			}
		}
	}
	return sum;
}

Bigint Bigint::operator-(const Bigint &obj)
{
	Bigint sum;
	node *p, *q, *r;
	p = tail;
	q = obj.tail;
	r = sum.tail;
	while (p->prev != head && q->prev != obj.head)
	{
		p = p->prev;
		q = q->prev;
		r->prev = new node;
		r->prev->next = r;
		r->prev->num = p->num - q->num;
		r = r->prev;
	}
	if (q->prev != obj.head)
	{
		while (q->prev != obj.head)
		{
			q = q->prev;
			r->prev = new node;
			r->prev->next = r;
			r->prev->num = -q->num;
			r = r->prev;
		}
	}
	else if (p->prev != head)
	{
		while (p->prev != head)
		{
			p = p->prev;
			r->prev = new node;
			r->prev->next = r;
			r->prev->num = p->num;
			r = r->prev;
		}
	}
	r->prev = sum.head;
	sum.head->next = r;
	r = sum.tail;
	while (r->prev != sum.head)
	{
		r = r->prev;
		if (r->num > 0)
			continue;
		else
		{
			r->num += 10;
			if (r->prev == sum.head)
			{
				r->num -= 10;
			}
			else
			{
				r->prev->num -= 1;
			}
		}
	}
	return sum;
}

bool Bigint::negative()
{
	if (head->next == tail)
		return false;
	if (head->next->num<0)
		return true;
	return false;
}

Bigint Bigint::operator/(const Bigint &obj)
{
	Bigint add(1), tmp;
	int result = 0;
	tmp = *this - obj;
	while (!tmp.negative())
	{
		result += 1;
		tmp = tmp - obj;
	}
	Bigint res(result + 1);
	return res;
}

istream & operator>>(istream &is, const Bigint &obj)
{
	char tmp;
	node *p;
	p = obj.head;
	while (is.get(tmp))
	{
		if (!(tmp > 47 && tmp < 58))
			continue;
		else
		{
			is.unget();
			break;
		}
	}
	while (is.get(tmp))
	{
		if (tmp > 47 && tmp < 58)
		{
			p->next = new node;
			p->next->prev = p;
			p->next->num = tmp - 48;
			p = p->next;
		}
		else
			break;
	}
	is.unget();
	p->next = obj.tail;
	obj.tail->prev = p;
	return is;
}

ostream & operator<<(ostream &os, const Bigint &obj)
{
	node *p;
	p = obj.head;
	while (p->next != obj.tail)
	{
		p = p->next;
		os << p->num;
	}
	return os;
}
