/* A simple matrix package to illustrate some C++11 features
 *
 * Everything is in the same file to make it simpler for the lecture.
 * However, clearly this is not good coding practice.
 * Furthermore, I've placed "using namespace std" at the top, and
 * you definitely don't want to do this in a header file
 */

/* This is the original (C++03) version of the "simpmat" class */

#include <vector>
#include <iostream>

using namespace std; // don't do this in a header file!

template<int M, int N, typename D=double>
class simpmat {
public:
	simpmat() : data(M,vector<D>(N)) { }
	
	D &operator()(int i, int j) {
	// skipping checking for the moment
		return data[i][j];
	}
	D operator()(int i, int j) const { // ditto
		return data[i][j];
	}

	template<int P>
	simpmat<M,P,D> operator*(const simpmat<N,P,D> &x) const {
		// an MxN matrix times a NxP matrix produces a MxP matrix
		// code placed here for simplicity
		// not the most efficient algorithm for cache hits, etc.
		// just for illustration!
		simpmat<M,P,D> ret;
		for(int i=0;i<M;i++) for(int j=0;j<P;j++) {
			ret(i,j) = 0.0;
			for(int k=0;k<N;k++) ret(i,j) += (*this)(i,k) * x(k,j);
		}
		return ret;
	}

	D max() const {
		bool first = true;
		D ret;
		for(typename vector<vector<D> >::const_iterator i=data.begin();
					i!=data.end();++i)
			for(typename vector<D>::const_iterator j=i->begin();
						j!=i->end();++j)
				if (first || ret<*j) {
					ret = *j;
					first = false;
				}
		return ret;
	}
	
private:
	vector<vector<D> > data;  // this probably isn't the best way,
				// but we'll do it for the moment
};

template<int M,int N,typename D>
void printmat(const simpmat<M,N,D> &m, ostream &os) {
	for(int i=0;i<M;i++) {
		for(int j=0;j<N;j++) 
			os << m(i,j) << ' ';
		os << endl;
	}
	os << "max value: " << m.max() << endl;
}
	
int main(int arg, char **argv) {
	simpmat<2,3,double> m1;
	m1(0,0) =  0.0; m1(0,1) =  1.0; m1(0,2) =  1.5;
	m1(1,0) = -2.0; m1(1,1) =  1.8; m1(1,2) = -0.5;
	simpmat<3,4,double> m2;
	m2(0,0) =  1.0; m2(0,1) =  1.0; m2(0,2) =  0.5; m2(0,3) = -2.3;
	m2(1,0) =  0.1; m2(1,1) = -0.2; m2(1,2) = -0.8; m2(1,3) =  2.9;
	m2(2,0) = -3.2; m2(2,1) = -5.1; m2(2,2) =  4.0; m2(2,3) = -4.2;

	cout << "M1: " << endl;
	printmat(m1,cout);
	cout << "M2: " << endl;
	printmat(m2,cout);
	cout << "M1*M2: " << endl;
	printmat(m1*m2,cout);

	return 0;
}
