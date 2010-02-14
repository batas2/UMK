#include<iostream>

using namespace std;

class base
{

private:
	void fun1()
	{
		cout << "fun1" << endl;
	}
	int test;
protected:
	void fun2()
	{
		cout << "fun2" << endl;
	}

public:
	void fun3()
	{
		cout << "fun3" << endl;
	}
	
	base(int v) : test(v)
	{
		cout << "test" << v << endl;
	}
	base() : test(0){}

};

class sub1: public base
{
public:
	sub1(int v) : test( v ) {} 

	void fsub1()
	{
		cout << "sub1" << endl;
	}
	int getTest() const
	{
		return this->test;
	}
private:
	int test;

};

class sub2: public base
{
public:
	sub2(int v)
	{
		cout << "Konstruktor sub2" << endl;
	}

	void fsub2()
	{
		cout << "sub2" << endl;
		fun2();
	}
};

class sub3: public base
{
public:
	sub3(int v): base(v)
	{
		cout << "Konstruktor sub3" << endl;
	}

	void fsub3()
	{
		cout << "sub3" << endl;
		fun3();
	}
};
/*
 * Autor: Bartosz Fr¹ckowiak
 * wwww:  http://www.batas2.boo.pl/
 */
int main()
{
	sub1 a(1);
	sub2 b(2);
	sub3 c(3);

	a.fsub1();
	b.fsub2();
	c.fsub3();
}
