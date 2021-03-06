// 1203.cpp: 定义控制台应用程序的入口点。
//

#include <iostream>
#include <cstring>
using namespace std;

template <class elemType>
class seqList
{
private:
	elemType * data;
	int currentLength;
	int maxSize;
	void doubleSpace();
public:
	seqList() { data = new elemType[10]; maxSize = 10; currentLength = 0; }
	seqList(int initSize);
	seqList(const seqList &obj);
	~seqList();
	seqList &operator=(const seqList &obj);
	seqList operator+(const seqList &obj);
	template <class elemType> friend istream &operator>>(istream &is, seqList<elemType> &obj);
	template <class elemType> friend ostream &operator<<(ostream &os,const seqList<elemType> &obj);
};

int main()
{
	char type[10];
	cin.getline(type,10);
	int n, m;
	cin >> n >> m;
	if (strcmp(type,"int")==0)
	{
		seqList <int> a(n), b(m), sum(n+m);
		cin >> a >> b;
		sum = a + b;
		cout << sum;
	}
	else if (strcmp(type,"double")==0)
	{
		seqList <double> a(n), b(m), sum(n + m);
		cin >> a >> b;
		sum = a + b;
		cout << sum;
	}
	else if (strcmp(type,"char")==0)
	{
		seqList <char> a(n), b(m), sum(n + m);
		cin >> a >> b;
		sum = a + b;
		cout << sum;
	}

	return 0;
}

template <class elemType>
void seqList<elemType>::doubleSpace()
{
	elemType *tmp = data;
	maxSize *= 2;
	data = new elemType[maxSize];
	for (int i = 0; i < currentLength; i++)
	{
		data[i] = tmp[i];
	}
	delete[]tmp;
}

template <class elemType>
seqList<elemType>::seqList(int initSize)
{
	data = new elemType[initSize];
	maxSize = initSize;
	currentLength = 0;
}

template <class elemType>
seqList<elemType>::seqList(const seqList<elemType> &obj)
{
	if (this == &obj)
		return;
	maxSize = obj.maxSize;
	currentLength = obj.currentLength;
	data = new elemType[maxSize];
	for (int i = 0; i < currentLength; i++)
		data[i] = obj.data[i];
}

template <class elemType>
seqList<elemType>::~seqList()
{
	delete[]data;
}

template <class elemType>
seqList<elemType> &seqList<elemType>::operator=(const seqList<elemType> &obj)
{
	if (this == &obj)
		return *this;
	maxSize = obj.maxSize;
	currentLength = obj.currentLength;
	data = new elemType[maxSize];
	for (int i = 0; i < currentLength; i++)
		data[i] = obj.data[i];
	return *this;
}

template <class elemType>
seqList<elemType> seqList<elemType>::operator+(const seqList<elemType> &obj)
{
	seqList sum(maxSize + obj.maxSize);
	int i;
	for (i = 0; i < currentLength; i++)
	{
		sum.data[i] = data[i];
	}
	for (i = 0; i < obj.currentLength; i++)
	{
		sum.data[currentLength + i] = obj.data[i];
	}
	sum.currentLength = currentLength + obj.currentLength;
	return sum;
}

template <class elemType>
istream &operator>>(istream &is, seqList<elemType> &obj)
{
	char tmp;
	int i = 0;
	obj.currentLength = 0;
	while (is.get(tmp))
	{
		if (tmp == '\n'&&obj.currentLength>0)
			break;
		is.unget();
		obj.currentLength += 1;
		if (obj.currentLength > obj.maxSize)
			obj.doubleSpace();
		is >> obj.data[i];
		i++;
	}
	return is;
}

template <class elemType>
ostream &operator<<(ostream &os,const seqList<elemType> &obj)
{
	for (int i = 0; i < obj.currentLength; i++)
	{
		os << obj.data[i] << " ";
	}
	return os;
}