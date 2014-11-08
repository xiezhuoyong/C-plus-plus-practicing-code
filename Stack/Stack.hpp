#ifndef STACK_H_
#define STACK_H_

#include <vector>
#include <stdexcept>

template <typename T>
class Stack
{
public:
	void push(const T &t);
	void pop();
	T top() const;
	
	bool empty() const
	{ return elems_.empty(); }
private:
	std::vector<T> elems_;
};

template <typename T>
void Stack<T>::push(const T &t)
{
	elems_.push_back(t);
}

template <typename T>
void Stack<T>::pop()
{
	if(elems_.empty())
		throw std::out_of_range("out of range");	
	elems_.pop_back();
}

template <typename T>
T Stack<T>::top() const 
{
	if(elems_.empty())
		throw std::out_of_range("out of range");
	return elems_.back();
}

template<>
class Stack<const char *>
{
public:
	void push(const char *);
	void pop();
	std::string top() const;
	
	bool empty() const
	{ return elems_.empty(); }
private:
	std::vector<std::string> elems_;
};

void Stack<const char *>::push(const char *s)
{
	elems_.push_back(s);
}

void Stack<const char *>::pop()
{
	if(elems_.empty())
		throw std::out_of_range("out of range");
	elems_.pop_back();
}

std::string Stack<const char *>::top() const
{
	if(elems_.empty())
		throw std::out_of_range("out of range");
	return elems_.back();
}


#endif //STACK_H_