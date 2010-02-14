#include<iostream>
#include<vector>
#include<algorithm>
#include<string>

using namespace std;

void pokaz(vector<int> *w, const char *napis)
{
	cout << napis << ": ";
	for(int i = 0; i < w->size(); i++){
		cout << (*w)[i] << ", ";
	}
	cout << endl;
}

void pokaz(vector<string> *w, const char *napis)
{
	cout << napis << ": ";
	for(int i = 0; i < w->size(); i++){
		cout << (*w)[i] << ", ";
	}
	cout << endl;
}

bool cmp(string a, string b)
{
	if(a.length() > b.length()){
		return false;
	}else{
		return true;
	}
}
/*
 * Autor: Bartosz Fr¹ckowiak
 * wwww:  http://www.batas2.boo.pl/
 */
int main()
{
	vector<int> w;
	vector<int> v;

	w.push_back(6);
	w.push_back(8);
	w.push_back(2);
	w.push_back(4);
	
	v.push_back(3);
	v.push_back(1);
	v.push_back(7);
	v.push_back(5);

	pokaz(&w, "Tab1");
	pokaz(&v, "Tab2");

	w.erase(w.begin() + 1);

	pokaz(&w, "Usuniecie");

	w.swap(v);

	pokaz(&w, "Zamiana\nTab1");
	pokaz(&v, "Tab2");	
	
	cout << "Pokazywanie z iteratorem" << endl;
	for(vector<int>::iterator it = w.begin(); it != w.end(); it++){
		cout << *it << ", ";
	}
	cout << endl;

	sort(w.begin(), w.end());

	pokaz(&w, "Posortowana");

	vector<string> s;

	s.push_back("ala");
	s.push_back("ma");
	s.push_back("kota");

	pokaz(&s, "string");

	sort(s.begin(), s.end(), cmp);

	pokaz(&s, "string posortowany");
}
