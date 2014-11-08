#include "Stack.hpp"
#include <iostream>
using namespace std;

int main()
{
	try
	{
		const char *s1 = "foo";
		Stack<const char *> st;
		
		st.push(s1);
		st.push("bar");
		
		cout << st.top() << endl;
		st.pop();
		
		cout << st.top() << endl;
		st.pop();
	}
	catch(exception &e)
	{
		cout << e.what() << endl;
	}
	
	return 0;
}