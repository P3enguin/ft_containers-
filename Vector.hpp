/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybensell <ybensell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 10:42:47 by ybensell          #+#    #+#             */
/*   Updated: 2022/07/27 18:21:55 by ybensell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <vector>
#include <string>
#include <iostream>
#include "tool.hpp"

    

namespace ft {

    template <class T , class Allocator = std::allocator<T> >
    class vector 
    {
        public :

            typedef T                                        value_type;
            typedef Allocator                                allocator_type;
            typedef typename allocator_type::reference       reference;
            typedef typename allocator_type::const_reference const_reference;

            typedef typename allocator_type::pointer         pointer; 
            typedef typename allocator_type::const_pointer   const_pointer;
            typedef typename allocator_type::difference_type difference_type;
            typedef typename allocator_type::size_type       size_type;

            /**************************************************** Iterator ***************************************************/

            template <typename P = value_type>
            class iter
            {
                public :
    
                    iter () {};
                    iter (T * ptr) {_iter = ptr;}
                    iter (const iter<P> &obj) {_iter = obj._iter; };

                    iter<P> &operator = (const iter<P> &obj){ _iter = obj._iter ; return *this ;}; //

                    bool operator ==(const iter<P> &obj) const
                    {
                        if (_iter == obj.getIter())
                            return true;
                        else
                            return false;
                    };
                    bool operator !=(const iter<P> &obj) const
                    {
                        if (_iter != obj.getIter())
                            return true;
                        return false;
                    };
                    
                    bool operator <(const iter<P> &obj)  const
                    {
                        if (_iter < obj.getIter())
                            return true;
                        return false;
                    };   
                    bool operator <=(const iter<P> &obj) const
                    {
                        if (_iter <= obj.getIter())
                            return true;
                        return false;
                    };   
                    bool operator > (const iter<P> &obj) const
                    {
                        if (_iter > obj.getIter())
                            return true;
                        return false;
                    };   
                    bool operator >=(const iter<P> &obj) const
                    {
                        if (_iter >= obj.getIter())
                            return true;
                        return false;
                    };

                    iter<P>& operator +=(const difference_type &index) { _iter += index ; return *this; } ;
                    iter<P>& operator -=(const difference_type &index) { _iter -= index ; return *this; } ; 

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
                    
                    difference_type operator -(const iter<P> &obj) { return (std::distance(obj.getIter(),this->_iter)) ;};

                    P & operator *()       { return *_iter ;};
                    P & operator *() const { return *_iter ;};
                    P * operator ->()      { return *_iter ;};

                    P * getIter() const {return _iter;};


                private :
                    P *_iter;
            };      
           
            typedef iter <T>                        iterator;
            typedef iter <const T>            const_iterator;

            iterator       begin()        { return iterator      (&_vec_ptr[0])     ;};
            const_iterator begin()  const { return const_iterator(&_vec_ptr[0])     ;};

            iterator         end()        { return iterator      (&_vec_ptr[_size]) ;};
            const_iterator   end()  const { return const_iterator(&_vec_ptr[_size]) ;};
            
            /*****************************************************************************************************************/
            
            /************************************************* Constructors **************************************************/

            explicit vector (const allocator_type & alloc = allocator_type())
            {
                _vec_ptr = nullptr;
                _size = 0;
                _capacity = 0;
                _max_size = 768614336404564650;
            };

            explicit vector (size_type n, const value_type& val = value_type(),
                 const allocator_type& alloc = allocator_type()) : _alloc(alloc)
            {
                _size = n;
                _capacity = n;
                _max_size = 768614336404564650;
                _vec_ptr = _alloc.allocate(_capacity);
                for (int i = 0; i < _size ; i++ )
                    _alloc.construct(_vec_ptr + i,val);
            };

            // fill and copy constructor left ;
            
            /*****************************************************************************************************************/
            
            /**************************************************** Capacity ***************************************************/
            
            size_type size() const { return _size ;};

            size_type max_size() const {return _max_size;};

            size_type capacity() const { return _capacity;};

            bool empty() const { if (_size == 0) return 1 ; return 0;};

            void resize (size_type n, value_type val = value_type())
            {
                if (n < _size)
                {
                    for (int i = n ; i < _capacity ;i++ )
                        _alloc.destroy(_vec_ptr + i);
                    _size = n;
                }
                else if (n > _size && n > _capacity)
                {   
                    size_type i = 0;
                    T *tmp = _vec_ptr;
                    _vec_ptr = _alloc.allocate(n);
                    for (i = 0;i < _size ; i++)
                        _alloc.construct(_vec_ptr + i ,tmp[i]);
                    for (i = n - _size;i < n ; i++)
                        _alloc.construct(_vec_ptr + i , val);
                    for (i = 0; i < _size ; i++ )
                         _alloc.destroy(tmp + i);
                    _alloc.deallocate(tmp,_size);
                    _size = n;
                    _capacity = n;
                }
                else if ( n > _size && n < _capacity)
                {
                    for (int i = n - _size;i < n ; i++)
                        _alloc.construct(_vec_ptr + i,val);
                }
            };

            void reserve(size_type n)
            {
                if (n > _max_size)
                    throw std::length_error("Max size Exceeded");
                if (n > _capacity)
                {
                    T *tmp;
                    size_type i;

                    _capacity = n;
                    tmp = _vec_ptr;
                    _vec_ptr = _alloc.allocate(n);
                    for (i = 0; i < _size ; i++)
                        _alloc.construct(_vec_ptr + i,tmp[i]);
                    for (i = 0 ; i < _size; i++)
                        _alloc.destroy(tmp + i);
                    _alloc.deallocate(tmp,_size);
                }
            };

            /*****************************************************************************************************************/
            
            /************************************************ Element Access *************************************************/

            reference       operator[] (size_type n)        {       reference &tmp = _vec_ptr[n]; return tmp; };
            const_reference operator[] (size_type n) const  { const reference &tmp = _vec_ptr[n]; return tmp; };

            reference       at (size_type n)
            {
                if (n >= _size)
                    throw std::out_of_range("Out of range");
                reference &tmp = _vec_ptr[n];
                return tmp;
            };
            const_reference at (size_type n) const
            {
                if (n >= _size)
                    throw std::out_of_range("Out of range");
                const reference &tmp = _vec_ptr[n];
                return tmp;
            };

            // front and end should be tested !!!!!!

            reference       front()         {       reference &tmp = _vec_ptr[0]; return tmp; };
            const_reference front() const   { const reference &tmp = _vec_ptr[0]; return tmp; };

            reference        back()         {       reference &tmp = _vec_ptr[_size - 1]; return tmp; };
            const_reference  back() const   { const reference &tmp = _vec_ptr[_size - 1]; return tmp; };

            /*****************************************************************************************************************/
            
            /*************************************************** Modifiers ***************************************************/
            
            void assign (size_type n, const value_type& val)
            {
                if (n > _capacity)
                {
                    for (size_type i = 0; i < _capacity; i++)
                        _alloc.destroy(_vec_ptr + i);
                    _alloc.deallocate(_vec_ptr,_capacity);
                    _capacity = n;
                   _vec_ptr = _alloc.allocate(_capacity);
                }
                if (n <= _capacity)
                {
                   _size = n;
                    for (size_type i = 0; i < _capacity; i++)
                            _alloc.destroy(_vec_ptr + i);
                }
                for (size_type i = 0; i < n; i++)
                    _alloc.construct(_vec_ptr + i, val);
            };

           template <class InputIterator, typename enable_if< !is_integral<InputIterator>::value ,InputIterator>::type >
            void assign (InputIterator first, InputIterator last)
            {
                difference_type diff;
                
                //try diff in size_type;
                diff = last - first;
                if (diff > _capacity)
                {
                    for (size_type i = 0; i < _capacity; i++)
                        _alloc.destroy(_vec_ptr + i);
                    _alloc.deallocate(_vec_ptr,_capacity);
                    _capacity = diff;
                   _vec_ptr = _alloc.allocate(_capacity);
                }
                if (diff <= _capacity)
                {
                    _size = diff;
                    for (size_type i = 0; i < _capacity; i++)
                            _alloc.destroy(_vec_ptr + i);
                }
                for (difference_type i = 0; i < diff; i++)
                {
                    _alloc.construct(_vec_ptr + i, *first);
                    first++;
                }
            };
            
            

            void push_back (const value_type& val)
            {
                T* tmp  = _vec_ptr;

                if (_size == _capacity)
                {
                    if (_capacity == 0)
                        _capacity += 1;
                    else
                        _capacity = _capacity * 2;
                    _vec_ptr = _alloc.allocate(_capacity);
                    for (size_type i = 0; i < _size; i++)
                        _alloc.construct(_vec_ptr + i,tmp[i]);
                    for (size_type i = 0; i < _size; i++)
                        _alloc.destroy(tmp + i);
                    _alloc.deallocate(tmp,_size);
                };
                _alloc.construct(_vec_ptr + _size, val);
                _size++;
            };

            void pop_back()
            {
                _size--;
                _alloc.destroy(_vec_ptr + _size);
            };

            iterator insert (iterator position, const value_type& val)
            {
                size_type i = 0;
                T* tmp  = _vec_ptr;
                difference_type diff;

                diff = (_vec_ptr + _size - 1) - position;
                if (_size + 1 > _capacity)
                    _vec_ptr = _alloc.allocate(_capacity * 2);
                for (i = 0;i < diff ; i++)
                    _alloc.construct(_vec_ptr + i ,tmp[i]);
                _alloc.construct(_vec_ptr + i ,val);
                for (i ;i < _size ; i++)
                    _alloc.construct(_vec_ptr + i + 1 , tmp[i]);
                if (_size + 1  > _capacity)
                {
                    for (i = 0; i < _size ; i++ )
                         _alloc.destroy(tmp + i);
                    _alloc.deallocate(tmp,_size);
                    _capacity = _capacity * 2;
                }
                _size++;
            };
            
            void insert (iterator position, size_type n, const value_type& val)
            {
                size_type i = 0;
                size_type j = 0;
                T* tmp  = _vec_ptr;
                difference_type diff;

                diff = (_vec_ptr + _size - 1) - position;
                if (_size + n + 1 > _capacity)
                    _vec_ptr = _alloc.allocate(_capacity * 2);
                for (i = 0;i < diff ; i++)
                    _alloc.construct(_vec_ptr + i ,tmp[i]);
                for (j ; j < n ; j++)
                    _alloc.construct(_vec_ptr + i + j ,val);
                for (i ;i < _size ; i++)
                    _alloc.construct(_vec_ptr + i + j +1 , tmp[i]);
                if (_size + n + 1  > _capacity)
                {
                    for (i = 0; i < _size ; i++ )
                         _alloc.destroy(tmp + i);
                    _alloc.deallocate(tmp,_size);
                    _capacity = _capacity * 2;
                }
                _size += n;
            };
            template <class InputIterator>
            void insert (iterator position, InputIterator first, InputIterator last)
            {
                difference_type diff;
                difference_type n;
                size_type i = 0;
                size_type j = 0;
                T* tmp  = _vec_ptr;
                
                n = last - first;
                diff = (_vec_ptr + _size - 1) - position;
                if (_size + diff + 1 > _capacity)
                    _vec_ptr = _alloc.allocate(_capacity * 2);
                for (i = 0;i < diff ; i++)
                    _alloc.construct(_vec_ptr + i ,tmp[i]);
                for (j ; j < n ; j++)
                    _alloc.construct(_vec_ptr + i + j , *(first + i));
                for (i ;i < _size ; i++)
                    _alloc.construct(_vec_ptr + i + j + 1 , tmp[i]);
                if (_size + n + 1  > _capacity)
                {
                    for (i = 0; i < _size ; i++ )
                         _alloc.destroy(tmp + i);
                    _alloc.deallocate(tmp,_size);
                    _capacity = _capacity * 2;
                }
                _size += n;
            };

        private :
            T *_vec_ptr;
            allocator_type _alloc;
            size_type _size;
            size_type _max_size;
            size_type _capacity;

    };

}

#endif