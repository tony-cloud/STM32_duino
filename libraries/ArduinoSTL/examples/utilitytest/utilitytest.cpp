#include <ArduinoSTL.h>
#include <utility>
#include <cstdio>
#include "testframework.h"

using namespace std::rel_ops;

class Foo{
public:
	Foo(int i) : q(new int(i)) { }

	Foo(const Foo & f) : q(new int( *(f.q))) {  }

	~Foo(){
		delete q;
	}

	bool operator< (const Foo & rhs) const{
		if(*q < *(rhs.q)){
			return true;
		}
		return false;
	}

	Foo & operator=(Foo & rhs){
		if( & rhs == this){
			return *this;
		}
		*q = *(rhs.q);
		return *this;
	}

	bool operator==(const Foo & rhs) const{
		return ( *q == *(rhs.q));
	}

private:
	int * q;

};


bool checkValidPairEquality(){
	Foo a(1);
	Foo b(2);

	std::pair<Foo, Foo> p(a, b);
	std::pair<Foo, Foo> q(a, b);

	return p == q;
}

bool checkInvalidPairLessThan(){
	Foo a(1);
	Foo b(2);

	std::pair<Foo, Foo> p(a, b);
	std::pair<Foo, Foo> q(a, b);

	return p < q;
}
bool checkInvalidPairGreaterThan(){
	//This checks to make sure the operators are being generated by rel_ops
	Foo a(1);
	Foo b(2);

	std::pair<Foo, Foo> p(a, b);
	std::pair<Foo, Foo> q(a, b);

	return p > q;
}
bool checkInvalidPairNotEquals(){
	//This checks to make sure the operators are being generated by rel_ops
	Foo a(1);
	Foo b(2);

	std::pair<Foo, Foo> p(a, b);
	std::pair<Foo, Foo> q(a, b);

	return p != q;
}
bool checkmake_pair(){
	Foo a(1);
	Foo b(2);

	std::pair<Foo, Foo> p(a, b);
	std::pair<Foo, Foo> r = std::make_pair(a, b);

	return p == r;
}
bool checkInvalidrel_ops_not_equals(){
	using namespace std::rel_ops;

	Foo a(5);
	Foo b(5);
	return a != b;
}
bool checkValidrel_ops_not_equals(){
	using namespace std::rel_ops;

	Foo a(5);
	Foo c(6);
	return a != c;
}
bool checkInvalidrel_ops_greater_than1(){
	using namespace std::rel_ops;

	Foo a(5);
	Foo b(5);
	return a > b;
}
bool checkInvalidrel_ops_greater_than2(){
	using namespace std::rel_ops;

	Foo a(5);
	Foo c(6);
	return a > c;
}
bool checkValidrel_ops_greater_than1(){
	using namespace std::rel_ops;

	Foo a(5);
	Foo c(6);
	return c > a;
}
bool checkValidrel_ops_less_than_equals1(){
	using namespace std::rel_ops;

	Foo a(5);
	Foo b(5);
	return a <= b;
}
bool checkValidrel_ops_less_than_equals2(){
	using namespace std::rel_ops;

	Foo a(5);
	Foo c(6);
	return a <= c;
}
bool checkInvalidrel_ops_less_than_equals1(){
	using namespace std::rel_ops;

	Foo a(5);
	Foo c(6);
	return c <= a;
}
bool checkInvalidrel_ops_greater_than_equals1(){
	using namespace std::rel_ops;

	Foo a(5);
	Foo c(6);
	return a >= c;
}
bool checkValidrel_ops_greater_than_equals1(){
	using namespace std::rel_ops;

	Foo a(5);
	Foo c(6);
	return c >= a;
}
bool checkValidrel_ops_greater_than_equals2(){
	using namespace std::rel_ops;

	Foo a(5);
	Foo b(6);
	return b >= a;
}

bool checkpair_opsConstructor(){
	std::pair<char, int> a;
	a = std::pair<char, int>('a', 7531);

	return a.first == 'a' && a.second == 7531;
}
bool checkpair_opsAssignmentOperator(){
	std::pair<char, int> a;
	a = std::pair<char, int>('a', 7531);

	return a.first == 'a' && a.second == 7531;
}
bool checkpair_opsElementAssignment(){
	std::pair<char, int> a;

	a = std::pair<char, int>('a', 7531);
	a.second=61473;
	a.first='b';

	return a.first == 'b' && a.second == 61473;
}
bool checkpair_opsCopyConstructor(){
	std::pair<char, int> b;
	b = std::pair<char, int>('b', 61473);

	std::pair<char, int> c(b);
	
	return c.first == 'b' && c.second == 61473;
}
bool checkpair_opsReplacementAssignment(){
	std::pair<Foo, Foo> d = std::pair<Foo, Foo>(5, 18);
	std::pair<Foo, Foo> e(d);

	e = d;
	
	return e.first == 5 && e.second == 18;
}


void testmain(void)
{
	TestFramework::init();

	TestFramework::AssertReturns<bool>(checkInvalidrel_ops_not_equals, false);
	TestFramework::AssertReturns<bool>(checkValidrel_ops_not_equals, true);
	TestFramework::AssertReturns<bool>(checkInvalidrel_ops_greater_than1, false);
	TestFramework::AssertReturns<bool>(checkInvalidrel_ops_greater_than2, false);
	TestFramework::AssertReturns<bool>(checkValidrel_ops_greater_than1, true);
	TestFramework::AssertReturns<bool>(checkValidrel_ops_less_than_equals1, true);
	TestFramework::AssertReturns<bool>(checkValidrel_ops_less_than_equals2, true);
	TestFramework::AssertReturns<bool>(checkInvalidrel_ops_less_than_equals1, false);
	TestFramework::AssertReturns<bool>(checkValidrel_ops_greater_than_equals1, true);
	TestFramework::AssertReturns<bool>(checkValidrel_ops_greater_than_equals2, true);
	TestFramework::AssertReturns<bool>(checkInvalidrel_ops_greater_than_equals1, false);

	TestFramework::AssertReturns<bool>(checkpair_opsConstructor, true);
	TestFramework::AssertReturns<bool>(checkpair_opsAssignmentOperator, true);
	TestFramework::AssertReturns<bool>(checkpair_opsElementAssignment, true);
	TestFramework::AssertReturns<bool>(checkpair_opsCopyConstructor, true);
	TestFramework::AssertReturns<bool>(checkpair_opsCopyConstructor, true);
	TestFramework::AssertReturns<bool>(checkpair_opsReplacementAssignment, true);


	TestFramework::AssertReturns<bool>(checkValidPairEquality, true);
	TestFramework::AssertReturns<bool>(checkInvalidPairLessThan, false);
	TestFramework::AssertReturns<bool>(checkInvalidPairGreaterThan, false);
	TestFramework::AssertReturns<bool>(checkInvalidPairNotEquals, false);
	TestFramework::AssertReturns<bool>(checkmake_pair, true);

	TestFramework::results();

}
