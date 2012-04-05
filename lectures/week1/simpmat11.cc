/* A simple matrix package to illustrate some C++11 features
 *
 * Everything is in the same file to make it simpler for the lecture.
 * However, clearly this is not good coding practice.
 * Furthermore, I've placed "using namespace std" at the top, and
 * you definitely don't want to do this in a header file
 */

/* This is the final version of the simpmat class after a 5th change
 * (to the multiplication operator to illustrate the auto keyword when
 * used with return type) -- compare to simpmat11-v1.cc (the version with
 * only the first 4 changes)
 */

#include <vector>
#include <array> // CHANGE 4: use array instead of vector
#include <iostream>

using namespace std; // don't do this in a header file!

template<int M, int N, typename D=double>
class simpmat {
public:
	// CHANGE 4: vector => array (can remove constructor)
	//simpmat() : data(M,vector<D>(N)) { }
	
	D &operator()(int i, int j) {
	// skipping checking for the moment
		return data[i][j];
	}
	D operator()(int i, int j) const { // ditto
		return data[i][j];
	}

	D max() const {
		// CHANGE 2a: bool => auto
		auto first = true;
		D ret;
		// CHANGE 2b: iterators => auto
		/*
		for(auto i=data.begin(); i!=data.end();++i)
			for(auto j=i->begin(); j!=i->end();++j)
				if (first || ret<*j) {
					ret = *j;
					first = false;
				}
		*/
		// CHANGE 3: ranged-based for loops
		// note that *i => i and *j => j
		for(auto i : data)
			for(auto j : i)
				if (first || ret<j) {
					ret = j;
					first = false;
				}
		return ret;
	}
	
private:
	// CHANGE 1: > > => >>
	/*
	vector<vector<D>> data;  // this probably isn't the best way,
				// but we'll do it for the moment
	*/
	// CHANGE 4: vector => array
	array<array<D,N>,M> data;
};

template<int M, int N, int P,typename D, typename D2>
auto operator*(const simpmat<M,N,D> &x1, const simpmat<N,P,D2> &x2) 
			-> simpmat<M,P,decltype(x1(0,0)*x2(0,0) + x1(0,0)*x2(0,0))> {
	// an MxN matrix times a NxP matrix produces a MxP matrix
	// code placed here for simplicity
	// not the most efficient algorithm for cache hits, etc.
	// just for illustration!
	typedef decltype(x1(0,0)*x2(0,0) + x1(0,0)*x2(0,0)) Dret;
	
	simpmat<M,P,Dret> ret;
	for(int i=0;i<M;i++) for(int j=0;j<P;j++) {
		ret(i,j) = Dret();
		for(int k=0;k<N;k++) ret(i,j) += x1(i,k) * x2(k,j);
	}
	return ret;
}


template<int M,int N,typename D>
void printmat(const simpmat<M,N,D> &m, ostream &os) {
	for(int i=0;i<M;i++) {
		for(int j=0;j<N;j++) 
			os << m(i,j) << ' ';
		os << endl;
	}
	os << "max value: " << m.max() << endl;
}

string operator*(const string &s, int i) {
	string ret;
	for(;i>0;--i) ret += s;
	return ret;
}
	
int main(int arg, char **argv) {
	simpmat<2,3,double> m1;
	m1(0,0) =  0.0; m1(0,1) =  1.0; m1(0,2) =  1.5;
	m1(1,0) = -2.0; m1(1,1) =  1.8; m1(1,2) = -0.5;
	simpmat<3,(8>>1),double> m2;
	m2(0,0) =  1.0; m2(0,1) =  1.0; m2(0,2) =  0.5; m2(0,3) = -2.3;
	m2(1,0) =  0.1; m2(1,1) = -0.2; m2(1,2) = -0.8; m2(1,3) =  2.9;
	m2(2,0) = -3.2; m2(2,1) = -5.1; m2(2,2) =  4.0; m2(2,3) = -4.2;

	cout << "M1: " << endl;
	printmat(m1,cout);
	cout << "M2: " << endl;
	printmat(m2,cout);
	cout << "M1*M2: " << endl;
	printmat(m1*m2,cout);

	simpmat<2,2,string> ms;
	ms(0,0) = "hello"; ms(0,1) = "there";
	ms(1,0) = "good";  ms(1,1) = "bye";
	simpmat<2,2,int> mi;
	mi(0,0) = 1; mi(0,1) = 0;
	mi(1,0) = 2; mi(1,1) = 1;

	printmat(ms,cout);
	cout << "  times" << endl;
	printmat(mi,cout);
	cout << "  is" << endl;
	printmat(ms*mi,cout);
	
	return 0;
}
