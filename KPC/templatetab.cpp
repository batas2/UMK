#include<iostream>

using namespace std;

template<class T>
class tab
{
public:
	T *_tab;
	int _n;

	tab()
	{
		_tab = NULL;
		_n = 0;
	}

	tab(const tab &bTab)
	{
		_n = bTab._n;
		_tab = new T[ _n ];

		for(int i = 0; i < _n; i++){
			_tab[i] = bTab._tab[i];
		}
				
	}

	void dodaj(T v)
	{
		if (_tab == NULL){
			_tab = new T[1];
			_n = 1;
			_tab[0] = v;
		}else{
			tab bTab( *this );
			this->~tab();

			_n = bTab._n + 1;
			_tab = new T[ _n];
			for(int i = 0; i < _n - 1; i++){
				_tab[i] = bTab._tab[i];
			}
			_tab[_n - 1] = v;
		}
	}

	void usun(int index)
	{
	
		if(_tab != NULL && index < _n){
			tab bTab( *this );
			this->~tab();

			_n = bTab._n - 1;
			_tab = new T[_n];
			for(int i = 0; i < _n; i++){
				if(i < index){
					_tab[i] = bTab._tab[i];
				}else if(i > index){
					_tab[i] = bTab._tab[i + 1];
				}
			}
		}
	}


	
	void operator+(tab t)
	{
		if(_n = t._n){
			for(int i = 0; i < _n; i++){
				_tab[i] += t._tab[i];
			}
		}
	}

	T operator[](int v)
	{
		return _tab[v];
	}

	bool operator==(tab t)
	{
		if(t._n == _n){
			for(int i = 0; i < _n; i++){
				if(t._tab[i] != _tab[i]){
					return false;
				}
				return true;
			}
		}else{
			return false;
		}
	}

	void pokaz()
	{
		for(int i = 0; i < _n; i++){
			cout << _tab[i] << " : ";
		}
		cout << endl;
	}

	~tab()
	{
		if ( (_tab != NULL) && (_n > 0) )
		{
			delete[] _tab;
			_tab = NULL;
			_n = 0;
		}
	}	
};

/*
 * Autor: Bartosz Fr¹ckowiak
 * wwww:  http://www.batas2.boo.pl/
 */
int main()
{
	tab<double> t;
	t.dodaj(2.5);
	t.dodaj(3.98);
	t.dodaj(8.234);
	
	t.pokaz();

	tab<double> t2(t);

	if(t == t2){
		cout << "Tablice t i t2 sa rowne" << endl;
	}else{
		cout << "Tablice t i t2 sa rozne" << endl;
	}

	t + t2;

	t.pokaz();

	t.usun(2);
	t.usun(1);

	t.pokaz();
}
