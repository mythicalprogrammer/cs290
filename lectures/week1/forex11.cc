/* Example code to show how range-based for loops work in C++11 */

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <ctype.h>

using namespace std;

template<typename T1,typename T2>
void printmap(const map<T1,T2> &m, ostream &os) {
	for(const auto &x : m) os << x.first << " => " << x.second << endl;
}

// a real version of this would also have a non-const version for
// strings that are not const (so they could be changed)
class cstr {
public:
	cstr(const char *str) : s(str) {}
	// omitting lots for simplicity
	
	class cstritt {
	public:
		cstritt(const char *s) : p(s) { }
		bool operator==(const cstritt &i) const {
			return i.p==p || (p==nullptr && *(i.p)==0) || (i.p==nullptr && *p==0);
		}
		bool operator!=(const cstritt &i) const {
			return !((*this)==i);
		}
		cstritt operator++() {// prefix
			p++; return *this;
		}
		cstritt operator++(int) {//postfix
			cstritt ret(*this);
			p++; return ret;
		}
		const char &operator*() const { return *p; }
	private:
		const char *p;
	};

	cstritt begin() { return cstritt(s); }
	cstritt end() { return cstritt(nullptr); }

private:
	const char *s;
};

int main(int argc, char **argv) {
	vector<int> v;
	int a[10] = {0,1,2,3,4,5,6,7,8,9};

	// put a into v
	// ranged for works for arrays
	for(auto x : a)
		v.push_back(x);
	// now print them out:
	for(auto x : v)
		cout << x << ' ';
	cout << endl;

	// it does not work for pointers (no idea when to end!)
	/* will not compile:
	int *aa = a;
	for(auto x : aa)
		cout << x << ' ';
	cout << endl;
	*/

	// works on C arrays, stl containers and some other things I
	// haven't mentioned yet
	//
	// works for any type user type T for which T.begin() & T.end() are
	// defined *OR* begin(T) & end(T) are defined (and the results
	// work as iterators)
	
	// thus, while char * doesn't work (and you can't make it work for
	// them, as "char *" is not a UDT -- user defined type),
	// you can write a null-terminated string class yourself
	// (see cstr above):
	for(auto x : cstr("Hello There!"))
		cout << x << x;
	cout << endl;
	// of course, you are better off using std::string!
	
	map<int,string> num2name;
	num2name[0] = "zero";
	num2name[1] = "one";
	num2name[2] = "two";
	num2name[3] = "three";
	printmap(num2name,cout);

	// example of reversing the map:
	map<string,int> name2num;
	for(auto p : num2name)
		name2num[p.second] = p.first;
	printmap(name2num,cout);

	// to make uppercase, this will NOT work:
	// (p is not a reference, but a copy)
	for(auto p : num2name)
		p.second[0] = toupper(p.second[0]);
	printmap(num2name,cout);

	// this will:
	for(auto &p : num2name)
		p.second[0] = toupper(p.second[0]);
	printmap(num2name,cout);

	// and, of course, this will not compile:
	/*
	for(const auto &p : num2name)
		p.second[0] = toupper(p.second[0]);
	*/
	// but, for loops that do not change the values, "const auto &"
	// is probably preferred
		
	return 0;
}
