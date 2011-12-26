#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <set>
#include <iterator>
#include <functional>

using namespace std;

/*
 * Program wczytuje plan zajęć i podaje co z czym się kłóci
 */

typedef pair< int, int >
		t_termin;
typedef vector<t_termin>
		t_spisTerminow;
typedef pair<string, t_spisTerminow>
		t_przedmiot;
typedef vector<t_przedmiot>
		t_spisPrzedmiotow;

class myexception {
	string msg;
	int code;
public:
	myexception(string _msg = "No error message", int _code=-1) : msg(_msg), code(_code) {} ;
	friend ostream& operator<<(ostream&,myexception&);
};

ostream& operator<<(ostream &out, myexception &e) {
	out << "BŁĄD #" << e.code << ": " << e.msg << "\n";
	return out;
}

struct blabler : public unary_function<t_przedmiot, void> {
	t_spisPrzedmiotow &lst;
	blabler(t_spisPrzedmiotow &_lst) : lst(_lst) {}
	void operator()(t_przedmiot &y) {
		cout << "Obczajam ." << y.first << ".\n\t";
	}
};

int main() {
	try {
	
		int iloscPrzedmiotow;
		cin >> iloscPrzedmiotow;
	
		t_spisPrzedmiotow spisPrzedmiotow(iloscPrzedmiotow);
		set<int> terminy_set;
		
		for(int i=0;i<iloscPrzedmiotow;++i) {
			string nazwa;
			int iloscTerminow;
	
			cin >> nazwa >> iloscTerminow;
			if(iloscTerminow < 0) throw myexception("Podana ujemna ilość terminów!",2);
	
			t_spisTerminow przedm(iloscTerminow);
			while(iloscTerminow--) {
				int a, b;
				cin >> a >> b;
				if(a>b) throw myexception("Podano ujemny przedział czasowy (czas rozpoczęcia < czas zakończenia)", 1);
				przedm.push_back(t_termin(a,b));
				terminy_set.insert(a);
				terminy_set.insert(b);
			}
			cout << "Pusz na spisPrzedmiotow: " << nazwa << "\n";
			spisPrzedmiotow.push_back(t_przedmiot(nazwa, przedm));
		}
	
		vector<int> terminy(terminy_set.begin(), terminy_set.end());
		//DBG:ON
		cout << "Godziny: ";
		copy(terminy.begin(), terminy.end(), ostream_iterator<int>(cout, ", "));
		cout << "\n";
		//DBG:OFF

		for_each(spisPrzedmiotow.begin(), spisPrzedmiotow.end(), blabler(spisPrzedmiotow));
	
	
	} catch(myexception &e) {
		cout << e;
	}

	return 0;
}

