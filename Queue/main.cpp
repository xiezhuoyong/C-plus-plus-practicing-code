#include "Queue.hpp"
#include <string>
#include <list>
#include <iostream>

using namespace std;

int main()
{
	Queue<double> qt0;
	qt0.push(1.1);
	qt0.push(2.2);
	qt0.push(3.3);
	qt0.push(4.4);
	while(!qt0.empty())
	{
		cout << qt0.front() << endl;
		qt0.pop();
	}
	
	Queue<int> qt1;
	qt1.push(1);
	qt1.push(2);
	qt1.push(3);
	qt1.push(4);
	
	Queue<double> qt2(qt1);
	while(!qt2.empty())
	{
		cout << qt2.front() << endl;
		qt2.pop();
	}
	
	Queue<double, list<double> > qt3;
	qt3 = qt1;
	while(!qt3.empty())
	{
		cout << qt3.front() << endl;
		qt3.pop();
	}
	
	qt1 = qt0;
	while(!qt1.empty())
	{
		cout << qt1.front() << endl;
		qt1.pop();
	}
	
	return 0;
}