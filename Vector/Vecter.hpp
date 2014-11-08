#ifndef VECTOR_H_
#define VECTOR_H_

#include <memory>//std::allocator
#include <algorithm>
#include <stddef.h>

template <typename T>
class Vector
{
public:
   typedef T *iterator;
   typedef const T *const_iterator;
   typedef size_t size_type;
   typedef T value_type;
   
   class reverse_iterator
   {
	public:
		reverse_iterator(iterator it = NULL):current_(it){ }
		iterator base() const { return current_; }
		
		reverse_iterator &operator++()//ǰ++
		{
			--current_;
			return *this;
		}
		reverse_iterator operator++(int)//��++
		{
			reverse_iterator temp(*this);
			--current_;
			return temp;
		}
		reverse_iterator &operator--()
		{
			++current_;
			return *this;
		}
		reverse_iterator &operator--(int)
		{
			reverse_iterator temp(*this);
			--current_;
			return temp;
		}
		T &operator*()
		{
			iterator temp = current_;
			return *--temp;
		}
		T *operator->()
		{
			iterator temp = current_;
			return --temp;
		}
		friend bool operator==(const reverse_iterator &lhs,
							   const reverse_iterator &rhs)
		{
			return lhs.current_ == rhs.current_;
		}
		friend bool operator!=(const reverse_iterator &lhs,
							   const reverse_iterator &rhs)
		{
			return lhs.current_ != rhs.current_;
		}
		
	private:
		iterator current_;		
   };
   
   class const_reverse_iterator
   {
	public:
		const_reverse_iterator(const_iterator it = NULL)
			:current_(it)
		{ 
		}
		const_iterator base() const
		{ return current_; }
		const_reverse_iterator &operator++()
		{
			--current_;
			return *this;
		}
		const_reverse_iterator operator++(int)
		{
			const_iterator temp(*this);
			--current_;
			return temp;
		}
		const_reverse_iterator &operator--()
		{
			++current_;
			return *this;
		}
		const_reverse_iterator operator--(int)
		{
			const_iterator temp(*this);
			++current_;
			return temp;
		}		
		const T &operator*() const
		{
			const_iterator temp = current_;
			return *(--temp);
		}
		const T *operator->() const
		{
			const_iterator temp = current_;
			return --temp;
		}
		friend bool operator==(const const_reverse_iterator &lhs, 
							   const const_reverse_iterator &rhs)
		{
			return lhs.current_ == rhs.current_;
		}
		friend bool operator!=(const const_reverse_iterator &lhs,
							   const const_reverse_iterator &rhs)
		{
			return lhs.current_ != rhs.current_;
		}
	private:
		const_iterator current_;
   };
   
   Vector() { create(); }
   explicit Vector(size_type n, const T &t = T())
   { create(n, t); }
   Vector(const Vector &v)
   { create(v.begin(), v.end()); }
   ~Vector() { uncreate(); }
   
   Vector &operator=(const Vector &other);
   T &operator[] (size_type i) { return data_[i]; }
   const T &operator[] (size_type i) const { return data_[i]; }

   void push_back(const T &t);
   void swap(Vector &rhs)
   {
       std::swap(data_, rhs.data_);
       std::swap(avail_, rhs.avail_);
       std::swap(limit_, rhs.limit_);
   }
   
   size_type size() const { return avail_ - data_; }
   size_type capacity() const { return limit_ - data_; }
   
   iterator begin() { return data_; }
   const_iterator begin() const { return data_; }
   iterator end() { return avail_; }
   const_iterator end() const { return avail_; }
   
   reverse_iterator rbegin() { return reverse_iterator(end()); }
   const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
   reverse_iterator rend() { return reverse_iterator(begin()); }
   const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }
    

private:
	iterator data_; //��Ԫ��
    iterator avail_; //ĩβԪ�ص���һ��λ��
    iterator limit_; //�ڴ�ĺ���һ��λ��

    std::allocator<T> alloc_; //�ڴ������

    void create();
    void create(size_type, const T &);
    void create(const_iterator, const_iterator);

    void uncreate();

    void grow();
    void uncheckedAppend(const T &);
   
};

template <typename T>
Vector<T> &Vector<T>::operator=(const Vector &rhs)
{
    if(this != &rhs)
    {
        uncreate(); //�ͷ�ԭ�����ڴ�
        create(rhs.begin(), rhs.end());
    }

    return *this;
}

template <typename T>
void Vector<T>::push_back(const T &t)
{
    if(avail_ == limit_)
    {
        grow();
    }
    uncheckedAppend(t);
}

template <typename T>
void Vector<T>::create()
{
    //����յ�����
    data_ = avail_ = limit_ = 0;
}

template <typename T>
void Vector<T>::create(size_type n, const T &val)
{
    //����ԭʼ�ڴ�
    data_ = alloc_.allocate(n);
    limit_ = avail_ = data_ + n;
    //��ԭʼ�ڴ����Ԫ��
    std::uninitialized_fill(data_, limit_, val);
}

template <typename T>
void Vector<T>::create(const_iterator i, const_iterator j)
{
	data_ = alloc_.allocate(j-i);
	limit_ = avail_ = std::uninitialized_copy(i, j, data_);
}

template <typename T>
void Vector<T>::uncreate()
{
	if(data_)
	{
		iterator it = avail_;
		while(it != data_)
		{
			alloc_.destroy(--it);
		}
		
		alloc_.deallocate(data_, limit_ - data_);
	}
	
	data_ = limit_ = avail_ = 0;
}

template <typename T>
void Vector<T>::grow()
{
	size_type new_size = std::max(2 * (limit_ - data_), std::ptrdiff_t(1));
	
	iterator new_data = alloc_.allocate(new_size);
	
	iterator new_avail = std::uninitialized_copy(data_, avail_, new_data);

	uncreate();
	
	data_ = new_data;
	avail_ = new_avail;
	limit_ = data_ + new_size;
}

template <typename T>
void Vector<T>::uncheckedAppend(const T &val)
{
	alloc_.construct(avail_++, val);
}

#endif  /* VECTOR_H_ */


