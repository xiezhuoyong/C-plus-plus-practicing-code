#ifndef QUEUE_H_
#define QUEUE_H_

#include <deque>

template <typename T, typename V = std::deque<T> >
class Queue
{
public:
	typedef typename V::size_type size_type;
	
	Queue() { }
	
	template <typename T2, typename V2>
	Queue<T, V>(const Queue<T2, V2> &other);
	
	template <typename T2, typename V2>
	Queue<T, V> &operator=(const Queue<T2, V2> &other);
	
	void push(const T &t)
	{
		elems_.push_back(t);
	}
	
	void pop()
	{
		elems_.pop_front();
	}
	
	T &front() { return elems_.front(); }
	const T &front() const { return elems_.front(); }
	T &back() { return elems_.back(); }
	const T &back() const { return elems_.back(); }
	
	bool empty() const
	{ return elems_.empty(); }
	
	size_type size() const
	{ return elems_.size(); }
	
private:
	V elems_;
		
};

template <typename T, typename V>
template <typename T2, typename V2>
Queue<T, V>::Queue(const Queue<T2, V2> &other)
{
	Queue<T2, V2> temp(other);
	while(!temp.empty())
	{
		push(temp.front());
		temp.pop();
	}
}

template <typename T, typename V>
template <typename T2, typename V2>
Queue<T, V> &Queue<T, V>::operator=(const Queue<T2, V2> &other)
{
	if((void *)this == (void *)&other)
		return *this;
		
	while(!empty())
	{
		pop();
	}
	
	Queue<T2, V2> temp(other);
	while(!temp.empty())
	{
		push(temp.front());
		temp.pop();
	}
}






#endif //QUEUE_H_