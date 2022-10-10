/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybensell <ybensell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 11:38:02 by ybensell          #+#    #+#             */
/*   Updated: 2022/10/10 12:03:16 by ybensell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOL_HPP
#define TOOL_HPP

#include <algorithm>
#include <iostream>
#include <string>
#include <typeinfo>


/***************************** iterator_traits *******************************/

template <class Iterator> 
class iterator_traits
{
	public :
		typedef typename Iterator::iterator_category iterator_category;
		typedef typename Iterator::value_type        value_type;
		typedef typename Iterator::difference_type   difference_type;
		typedef typename Iterator::pointer           pointer;
		typedef typename Iterator::reference         reference;
};

template <class T> 
class iterator_traits<T*>
{
	public :
		typedef std::random_access_iterator_tag     iterator_category;
		typedef T                                   value_type;
		typedef ptrdiff_t                           difference_type;
		typedef T*                                  pointer;
		typedef T&                                  reference;
};

template <class T>
class iterator_traits<const T*>
{
	public :
		typedef std::random_access_iterator_tag     iterator_category;
		typedef T                                   value_type;
		typedef ptrdiff_t                           difference_type;
		typedef const T*                            const_pointer;
		typedef const T&                            const_reference;
};



/*****************************************************************************/

/***************************** random_access_iterator ************************/
template <typename P>
class iter
{
	public :
		
	/*--------------------- Member types definition -------------------------*/

		typedef P        value_type;
		typedef P*       pointer;
		typedef P&       reference;

		typedef typename std::ptrdiff_t difference_type;
		typedef typename std::random_access_iterator_tag iterator_category;

	/*---------------------------- Constructors -----------------------------*/

		iter () {};
		iter (P * ptr) {_iter = ptr;}
		iter (const iter<P> &obj) {_iter = obj._iter; };

		iter<P> &operator  = (const iter<P> &obj){ _iter = obj._iter;
													return *this ;};
 
	/*------------------------- Operators Overloads -------------------------*/

		bool    operator  == (const iter<P> &obj) const
		{
			if (_iter == obj.getIter())
				return true;
			else
				return false;
		};

		bool    operator  != (const iter<P> &obj) const
		{
			if (_iter != obj.getIter())
				return true;
			return false;
		};
		
		bool    operator  <  (const iter<P> &obj) const
		{
			if (_iter < obj.getIter())
				return true;
			return false;
		};   
		bool    operator <=  (const iter<P> &obj) const
		{
			if (_iter <= obj.getIter())
				return true;
			return false;
		};   
		bool    operator  >  (const iter<P> &obj) const
		{
			if (_iter > obj.getIter())
				return true;
			return false;
		};   
		bool     operator >= (const iter<P> &obj) const
		{
			if (_iter >= obj.getIter())
				return true;
			return false;
		};

		iter<P>& operator +=(const difference_type &index) 
							   { _iter += index ; return *this;} ;
		iter<P>& operator -=(const difference_type &index) 
							   { _iter -= index ; return *this;} ; 


		iter<P>& operator ++() { _iter++ ; return *this;} ;
		iter<P>& operator --() { _iter-- ; return *this;} ;


		iter<P> operator ++(int) {
			iter<P> tmp = *this;
			_iter++;
			return tmp;
		};

		iter<P> operator --(int) {
			iter<P> tmp = *this;
			_iter--;
			return tmp;
		};

		iter<P> operator +(const difference_type &index) {
			iter<P> ret;

			ret._iter = _iter + index;
			return ret;
		};
		iter<P> operator -(const difference_type &index) {
			iter<P> ret;

			ret._iter = _iter - index;
			return ret;
		};
		
		difference_type operator -(const iter<P> &obj) 
			{ return (std::distance(obj.getIter(),this->_iter)) ;};

		P & operator  *()       { return *_iter ;};
		P & operator  *() const { return *_iter ;};
		P * operator ->()       { return *_iter ;};

		//getter for _iter pointer 
		P * getIter() const {return _iter;};

	protected :
		P *_iter;  /* this is the pointer that track my iterator since, 
					random access iterators are more like an arrays */
};    

/*****************************************************************************/

/***************************** Reverse Iterator ******************************/

namespace ft {
	template <class Iterator> 
	class reverse_iterator : public iter<typename Iterator::value_type>
	{
		public :
	/*--------------------- Member types definition -------------------------*/
	
			typedef          Iterator                        iterator_type ;
			typedef typename Iterator::iterator_category     iterator_category;
			typedef typename Iterator::value_type            value_type;
			typedef typename Iterator::difference_type       difference_type;
			typedef typename Iterator::pointer               pointer;
			typedef typename Iterator::reference             reference;
			
	/*---------------------------- Constructors -----------------------------*/

			reverse_iterator(){};
	
			explicit reverse_iterator (iterator_type it)
			{
				this->_iter = it.getIter();
			};
			
			template <class Iter>
			reverse_iterator (const reverse_iterator<Iter>& rev_it)
			{
				this->_iter  = rev_it.getIter();
			};
			
	/*------------------------- Operators Overloads -------------------------*/

			reverse_iterator<iterator_type>& operator = 
							(const reverse_iterator<iterator_type>& rev_it)
			{
				this->_iter = rev_it.getIter();
				return (*this);
			};
			
			reverse_iterator<iterator_type>& operator +=
				(const difference_type &index)
					 {  this->_iter -= index ; return *this; } ;

			reverse_iterator<iterator_type>& operator -=
				(const difference_type &index) 
					 {  this->_iter += index ; return *this; } ; 

			reverse_iterator<iterator_type>& operator ++
				  () {  this->_iter-- ; return *this;} ;

			reverse_iterator<iterator_type>& operator --
				  () {  this->_iter++ ; return *this;} ;


			reverse_iterator<iterator_type> operator ++(int)
			{
				reverse_iterator<iterator_type> tmp = *this;

				this->_iter--;
				return tmp;
			};

			reverse_iterator<iterator_type> operator --(int)
			{
				reverse_iterator<iterator_type> tmp = *this;

				this->_iter++;
				return tmp;
			};

			reverse_iterator<iterator_type> operator +
							(const difference_type &index)
			{
				reverse_iterator<iterator_type> ret;

				ret._iter =  this->_iter - index; 
				return ret;
			};
			
			reverse_iterator<iterator_type> operator -
							(const difference_type &index)
			{
				reverse_iterator<iterator_type> ret;

				ret._iter =  this->_iter + index;
				return ret;
			};
			
			reference operator  *()            { return *this->_iter;    };
			pointer   operator ->()            { return &(operator *()); };
			reference operator  *()     const  { return *this->_iter;    };


			reference operator   [](difference_type n) const
											   {return *(this->_iter - n);};
 
			iterator_type base() const         { return this->_iter + 1;};
	};
};

	/*---------------------- Non Member type functions ----------------------*/

		template <class Iterator>
		bool operator== (const ft::reverse_iterator<Iterator>& lhs,
						const ft::reverse_iterator<Iterator>& rhs)
		{
			if (lhs.getIter() == rhs.getIter())
					return true;
				return false;
		};

		template <class Iterator>
		bool operator!= (const ft::reverse_iterator<Iterator>& lhs,
							const ft::reverse_iterator<Iterator>& rhs)
		{
			if (lhs.getIter() != rhs.getIter())
					return true;
				return false;
		};

		template <class Iterator>
		bool operator<  (const ft::reverse_iterator<Iterator>& lhs,
							const ft::reverse_iterator<Iterator>& rhs)
		{
			if (lhs.getIter() > rhs.getIter())
					return true;
				return false;
		};
		
		template <class Iterator>
		bool operator<= (const ft::reverse_iterator<Iterator>& lhs,
							const ft::reverse_iterator<Iterator>& rhs)
		{
			if (lhs.getIter() >= rhs.getIter())
					return true;
				return false;
		};

		template <class Iterator>
		bool operator>  (const ft::reverse_iterator<Iterator>& lhs,
							const ft::reverse_iterator<Iterator>& rhs)
		{
			if (lhs.getIter() < rhs.getIter())
					return true;
				return false;
		};

		template <class Iterator>
		bool operator>= (const ft::reverse_iterator<Iterator>& lhs,
							const ft::reverse_iterator<Iterator>& rhs)
		{
			if (lhs.getIter() <= rhs.getIter())
					return true;
				return false;
		};

		template <class Iterator>
			ft::reverse_iterator<Iterator> operator+ (
					typename ft::reverse_iterator<Iterator>::difference_type n,
							const ft::reverse_iterator<Iterator>& rev_it)
		{
			ft::reverse_iterator<Iterator> tmp(rev_it);

			tmp += n;
			return tmp;
		};

		template <class Iterator>
			typename ft::reverse_iterator<Iterator>::difference_type operator- 
			( const ft::reverse_iterator<Iterator>& lhs,
				const ft::reverse_iterator<Iterator>& rhs)
			{
				return  rhs.base() - lhs.base(); 
			};

/***************************** is_integral ***********************************/

/*  is_integral Implemented using the template specialization technique. 
for info : https://www.cprogramming.com/tutorial/template_specialization.html */

template<typename T >
struct is_integral
{  
	static const bool value = false;
};

template<>
struct is_integral<bool>
{
	static const bool value = true;
};

template<>
struct is_integral <char>
{  
	static const bool value = true;
};

template<>
struct is_integral < char16_t >
{  
	static const bool value = true;
};


template<>
struct is_integral<char32_t>
{  
	static const bool value = true;
};

template<>
struct is_integral<wchar_t>
{  
	static const bool value = true;
};

template<>
struct is_integral<signed char>
{  
	static const bool value = true;
};

template<>
struct is_integral<short int>
{  
	static const bool value = true;
};

template<>
struct is_integral<int>
{  
	static const bool value = true;
};


template<>
struct is_integral<long int>
{  
	static const bool value = true;
};

template<>
struct is_integral<long long int>
{  
	static const bool value = true;
};

template<>
struct is_integral< unsigned char>
{  
	static const bool value = true;
};

template<>
struct is_integral<unsigned short int>
{  
	static const bool value = true;
};

template<>
struct is_integral<unsigned int>
{  
	static const bool value = true;
};

template<>
struct is_integral<unsigned long int>
{  
	static const bool value = true;
};

template<>
struct is_integral<unsigned long long int>
{  
	static const bool value = true;
};

/********************************* enable_if *********************************/

template<bool B, typename T >
struct enable_if { };

template<typename T>
struct enable_if<true, T> { typedef T type; };

/*********************************** Equal **********************************/
namespace ft 
{
	template <class InputIterator1, class InputIterator2>
	bool equal (InputIterator1 first1, InputIterator1 last1,
				InputIterator2 first2)
	{
		while (first1 != last1)
		{
			if (*first1 != *first2)
				return false;
			first1++;
			first2++;
		};
		return true;
	};
		
	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	bool equal (InputIterator1 first1, InputIterator1 last1,
				InputIterator2 first2, BinaryPredicate pred)

	{
		while (first1 != last1)
		{
			if (!pred(*first1,*first2))
				return false;
			first1++;
			first2++;
		};
		return true;
	};
};

/*************************** lexicographical_compare *************************/

/* Lexicographical_compare : the same comparaison  being done 
	in dictionarries to sort words alphabatically in order of position,
	if one of the character in the first range < second range ,the comparaison stop 
	. if one of the ranges terminated , the shortest one considered the smallest */
namespace ft
{
	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
									InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first1 > *first2)
				return false;
			else if (*first1 < *first2)
				return true;
			first1++;
			first2++;
		};
		return (first2 != last2);
	};

	template <class InputIterator1, class InputIterator2, class Compare>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
									InputIterator2 first2, InputIterator2 last2,
									Compare comp)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || comp(*first2,*first1))
				return false;
			if (comp(*first1,*first2))
				return true;
			first1++;
			first2++;
		};
		return (first2 != last2);
	};
}

/************************************ Pair ***********************************/
namespace ft 
{
	template <class T1, class T2> 
	struct pair
	{
		typedef T1 first_type;
		typedef T2 second_type;

		first_type first;
		second_type second;

		pair():first(),second(){}

		template<class U, class V> 
		pair (const pair<U,V>& pr) : first(pr.first),second(pr.second){}

		pair (const first_type& a, const second_type& b) : first(a),second(b){}

		pair& operator= (const pair& pr){first = pr.first; second = pr.second;
				return *this;}
		
		void swap (pair& pr){
			std::swap(first,pr.first);
			std::swap(second,pr.second);
		}
	};
	template <class T1, class T2>
	bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	}
	template <class T1, class T2>
	bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return (lhs != rhs);
	}
	template <class T1, class T2>
	bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return (lhs.first < rhs.first || (!(rhs.first<lhs.first) 
			&& lhs.second < rhs.second));
	}
	template <class T1, class T2>
	bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return !(rhs<lhs);
	}

	template <class T1, class T2>
	bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return (rhs < lhs);
	}
	template <class T1, class T2>
	bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return (!(lhs<rhs));
	}

	template <class T1, class T2>
 	void swap (pair<T1,T2>& x, pair<T1,T2>& y)
	{
		std::swap(x.first,y.first);
		std::swap(x.second,y.second);
	}
	
	template <class T1, class T2>
	pair<T1,T2> make_pair (T1 x, T2 y)
	{
		return (pair<T1,T2>(x,y));
	}
}

#endif