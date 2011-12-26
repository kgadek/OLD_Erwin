#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cassert>

using namespace std;

class DLXMatrix {

	struct col;
	struct node {
		node *L, *R, *U, *D;
		col *C;
		node() {
			L = R = U = D = this;
		}
		//node(node *_L, node *_R, node *_U, node *_D, col *_C) : L(_L), R(_R), U(_U), D(_D), C(_C) {}
	};

	struct col : public node {
		int S;
		col() : node(), S(0) {
			C = this;
		}
		//TODO destroy <-- nie destruktor, bo virtual ma zbyt duży narzut na node
		//col(node *_L, node *_R, node *_U, node *_D, col *_C, int _S) : node(_L, _R, _U, _D, _C), S(_S) {}
	};

	vector<col> H;

public:

	DLXMatrix(int primaryCnt, int secondaryCnt) : H(vector<col>(primaryCnt+secondaryCnt+1)){
		assert(primaryCnt >= 0);
		assert(secondaryCnt >= 0);
		assert(primaryCnt + secondaryCnt > 0);

		int allCnt = primaryCnt + secondaryCnt;

		H[0].L = &H[primaryCnt];
		H[primaryCnt].R = &H[0];
		
		for(int i=1; i<primaryCnt; ++i) {
			H[i].L = &H[i-1];
			H[i].R = &H[i+1];
		}
	}

	template <class ForwardIterator>
	void addLine(ForwardIterator it, ForwardIterator end) {
		node *last = NULL;
		for(; it != end; ++it) {
			int f = *it + 1;
			assert(f >= 1);
			assert(f < H.size());
			node *n = new node();
			n->C = &H[*it+1];
		}
	}
};

int main() {
	DLXMatrix ex1(7,0);
	return 0;
}

