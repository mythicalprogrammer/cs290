/* Example code to show how auto works in C++11 */

#include<iostream>
#include<typeinfo>

/* as best as I can tell, the "auto" in
 *
 *     auto x = <expr>
 *
 * is inferred in the same way as the T in
 *
 *     template<typename T> void foo(T x);
 *     foo(<expr>)
 *
 * similarly, the "auto" in a stmt like
 *
 *     const auto *x = <expr>
 *
 * is inferred with the same rules as the T in
 *
 *     template<typename T> void foo(const T *x);
 *     foo(expr)
 */

/* Note on my personal preferences with "auto" (after using them for
 * only a few months :) ):
 *
 * As with any language feature, there are advantages and disadvantages.
 * - The advantage is that code is smaller and thereby more readable.
 *   It can remove syntax that gets in the way of understanding the code.
 * - The disadvantage is that the code is smaller and thereby less readable.
 *   It can remove syntax that helps understanding the code.
 * The corollary to the second point is that it removes some (small amount of)
 * type checking by the compiler.  Type checking helps you catch bugs at
 * compile time, so this can be a problem.
 *
 * Therefore, my general use of auto has been only to use it to replace
 * long type expressions.  So, I do NOT replace "int" or "double" or
 * even "int *" or the like with "auto" (even in loops).  However, iterators
 * or other types that are long and not helpful to understanding the rest
 * I do replace.
 *
 * But, that's just my preference.  It remains to be seen what different
 * coding standards will arise from this.
 */

using namespace std;

int main(int argc, char **argv) {
	auto x0(1); // x0 is an int
	auto x1 = 1; // x1 is an int
	auto x2 = 'a'; // x2 is a char
	auto x3 = x1; // x3 is an int
	auto &x4 = x1; // x4 is an int&
	// pf:
	cout << x1 << ' ' << x4 << endl;
	x4 = 4;
	cout << x1 << ' ' << x4 << endl;
	const auto x5 = 1; // x5 is a const int
	// this won't compile:
	//x5 = 6;
	const auto &x6 = x5; // x6 is a const int &
	// and neither will this:
	//x6 = 3;
	auto x7 = &x1; // x7 is an int * 
	cout << x1 << ' ' << *x7 << endl;
	*x7 = 8;
	cout << x1 << ' ' << *x7 << endl;
	x7 = &x3;
	*x7 = 0;
	cout << x1 << ' ' << *x7 << endl;
	auto *x8 = &x1; // x8 is also an int *

	// "top-level/outside" const/volatile removed:
	auto x9 = x5; // x9 is an int (not const int, like x5)
	// array names become pointers:
	int a[10];
	auto x10 = a; // x10 is an int* (not int[10])
	
	// can do multiples:
	auto x11 = 10, *x12 = x8; // x11 is an int, x12 is an int*
	// won't compile: (must be single replacement for auto)
	//auto x13 = x11, x14 = x2; // x13 would be an int, but x14 would be a char
	
	return 0;
}
