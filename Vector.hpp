/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybensell <ybensell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 10:42:47 by ybensell          #+#    #+#             */
/*   Updated: 2022/09/10 13:41:41 by ybensell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <vector>
#include <string>
#include <iostream>
#include "tool.hpp"

// check if Deallocate done by capacity

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

            /**************************** Iterator ***************************/
     
           
            typedef iter <T>                        iterator;
            typedef iter <const T>            const_iterator;

            typedef typename ft::reverse_iterator<iterator>       reverse_iterator;
            typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;


            iterator       begin()        { return iterator      (&_vec_ptr[0])     ;}
            const_iterator begin()  const { return const_iterator(&_vec_ptr[0])     ;}

            iterator         end()        { return iterator      (&_vec_ptr[_size]) ;}
            const_iterator   end()  const { return const_iterator(&_vec_ptr[_size]) ;}


            reverse_iterator  rbegin ()       
                                { return reverse_iterator  (this->end() - 1);}
            reverse_iterator    rend ()            
                                { return reverse_iterator (this->begin() - 1);}


            const_reverse_iterator  rbegin()  
                        const { return const_reverse_iterator (this->end() - 1);}
            
            const_reverse_iterator   rend() 
                        const {return const_reverse_iterator (this->begin() - 1);}

            
            /*****************************************************************/
            
            /************************* Constructors **************************/
            
            explicit vector (const allocator_type & alloc = allocator_type())
            {
                _vec_ptr = nullptr;
                _size = 0;
                _capacity = 0;
                _max_size = 768614336404564650;
            }

            explicit vector (size_type n, const value_type& val = value_type(),
                const allocator_type& alloc = allocator_type()) : _alloc(alloc)
            {
                _size = n;
                _capacity = n;
                _max_size = 768614336404564650;
                _vec_ptr = _alloc.allocate(_capacity);
                for (size_type i = 0; i < _size ; i++ )
                    _alloc.construct(_vec_ptr + i,val);
            }

            template <class InputIterator>
            vector (typename enable_if<!is_integral<InputIterator>::value,
                    InputIterator>::type
                    first, InputIterator last,
                    const allocator_type& alloc = allocator_type()) : _alloc(alloc)
            {
                size_type i = 0;
                size_type n = last - first;

                _size     = n;
                _capacity = n;
                _max_size = 768614336404564650;
                _vec_ptr = _alloc.allocate(_capacity);
                while (first != last)
                {
                    _alloc.construct(_vec_ptr + i,*first);
                    first++;
                    i++;
                }
            }

            vector (const vector& x)
            {
                size_type i = 0;

                _size     = x._size;
                _capacity = x._capacity;
                _max_size = x._max_size;
                _vec_ptr = _alloc.allocate(_capacity);
                while (i < _size)
                {
                    _alloc.construct(_vec_ptr + i,x[i]);
                    i++;
                }
            }

            vector& operator= (const vector& x)
            {
               size_type i = 0;
    
                _size     = x._size;
                _capacity = x._capacity;
                _max_size = x._max_size;
                _vec_ptr = _alloc.allocate(_capacity);
                while (i < _size)
                {
                    _alloc.construct(_vec_ptr + i,x[i]);
                    i++;
                }
                return *this;
            }
            /*****************************************************************/
            
            /************************** Destructor ***************************/

            ~vector()
            {
                size_type i;
                for (i = 0; i < _size; i++)
                    _alloc.destroy(_vec_ptr + i);
                _alloc.deallocate(_vec_ptr,_capacity);
            }

            /*****************************************************************/
            
            /**************************** Capacity ***************************/
            
            size_type size() const { return _size ;}

            size_type max_size() const {return _max_size;}

            size_type capacity() const { return _capacity;}

            bool empty() const { if (_size == 0) return 1 ; return 0;}

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
                    for (size_type i = n - _size;i < n ; i++)
                        _alloc.construct(_vec_ptr + i,val);
                    _size = n;
                }
            }

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
            }

            /*****************************************************************/
            
            /************************** Element Access ***********************/

            reference       operator[] (size_type n)        
                            {       reference &tmp = _vec_ptr[n]; return tmp; }

            const_reference operator[] (size_type n) const  
                            { const reference &tmp = _vec_ptr[n]; return tmp; }

            reference       at (size_type n)
            {
                if (n >= _size)
                    throw std::out_of_range("Out of range");
                reference &tmp = _vec_ptr[n];
                return tmp;
            }
            const_reference at (size_type n) const
            {
                if (n >= _size)
                    throw std::out_of_range("Out of range");
                const reference &tmp = _vec_ptr[n];
                return tmp;
            }

            // front and end should be tested !!!!!!

            reference       front()     
                            {       reference &tmp = _vec_ptr[0]; return tmp; }

            const_reference front() const
                            { const reference &tmp = _vec_ptr[0]; return tmp; }


            reference        back()  
                          { reference &tmp = _vec_ptr[_size - 1]; return tmp; }

            const_reference  back() const
                    { const reference &tmp = _vec_ptr[_size - 1]; return tmp; }

            /*******************************************************************/
            
            /************************* Modifiers *******************************/
            
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
            }

            template <class InputIterator >
            void assign (typename enable_if< !is_integral<InputIterator>::value,
                                InputIterator>::type  first, InputIterator last)
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
                    for (size_type i = 0 ;i < _capacity; i++)
                            _alloc.destroy(_vec_ptr + i);
                }
                for (difference_type i = 0; i < diff; i++)
                {
                    _alloc.construct(_vec_ptr + i, *first);
                    first++;
                }
            }

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
                }
                _alloc.construct(_vec_ptr + _size, val);
                _size++;
            }

            void pop_back()
            {
                _size--;
                _alloc.destroy(_vec_ptr + _size);
            }

            iterator insert (iterator position, const value_type& val)
            {
                size_type i;
                T* tmp  = _vec_ptr;
                difference_type diff;

                diff = position.getIter() - _vec_ptr ;
                if (_size + 1 > _capacity)
                    _vec_ptr = _alloc.allocate(_capacity * 2);
                for (i = 0; i < diff ; i++)
                    _alloc.construct(_vec_ptr + i ,tmp[i]);
                _alloc.construct(_vec_ptr + i ,val);
                i++;
                while (i < _size)
                {
                    _alloc.construct(_vec_ptr + i, tmp[i]);
                    i++;
                }
                if (_size + 1  > _capacity)
                {
                    for (i = 0; i < _size ; i++ )
                         _alloc.destroy(tmp + i);
                    _alloc.deallocate(tmp,_size);
                    _capacity = _capacity * 2;
                }
                _size++;
                position = _vec_ptr + diff;
                return position;
            }
            
            void insert (iterator position, size_type n, const value_type& val)
            {
                size_type i = 0;
                size_type j = 0;
                T* tmp  = _vec_ptr;
                difference_type diff;
                size_type alloc_nbr;

                diff = position.getIter() - _vec_ptr ;
                if (_size + n + 1 > _capacity)
                {
                    if (_size + n + 1 <= _capacity * 2)
                        alloc_nbr = _capacity * 2;
                    else
                        alloc_nbr = _size + n;
                    _vec_ptr = _alloc.allocate(alloc_nbr);
                }
                for (i = 0; i < diff ; i++)
                    _alloc.construct(_vec_ptr + i ,tmp[i]);
                while (j < n)
                {
                    _alloc.construct(_vec_ptr + i + j ,val);
                    j++;
                }
                while (i < _size)
                {
                    _alloc.construct(_vec_ptr + i + j , tmp[i]);
                    i++;
                }
                if (_size + n + 1  > _capacity)
                {
                    for (i = 0; i < _size ; i++ )
                         _alloc.destroy(tmp + i);
                    _alloc.deallocate(tmp,_size);
                    _capacity = alloc_nbr;
                }
                _size += n;
            }
            
            template <class InputIterator>
            void insert (iterator position, 
                    typename enable_if<!is_integral<InputIterator>::value,
                            InputIterator>::type first, InputIterator last)
            {
                difference_type diff;
                difference_type n;
                size_type i ;
                size_type j;
                size_type alloc_nbr;
                T* tmp  = _vec_ptr;
                
                n = last - first;
                diff =  position  - _vec_ptr;
                if (_size + n + 1 > _capacity)
                {
                    if (_size + n + 1 <= _capacity * 2)
                        alloc_nbr = _capacity * 2;
                    else
                        alloc_nbr = _size + n;
                    _vec_ptr = _alloc.allocate(alloc_nbr);
                }

                for (i = 0; i < diff ; i++)
                    _alloc.construct(_vec_ptr + i ,tmp[i]);
                for (j = 0 ; j < n ; j++)
                {
                    _alloc.construct(_vec_ptr + i + j , *first);
                    first++;
                }
                i++;
                while (i < _size )
                {
                    _alloc.construct(_vec_ptr + i + j, tmp[i]);
                    i++;
                }
                if (_size + n + 1  > _capacity)
                {
                    for (i = 0; i < _size ; i++ )
                         _alloc.destroy(tmp + i);
                    _alloc.deallocate(tmp,_size);
                    _capacity = alloc_nbr;
                }
                _size += n;
            }

            iterator erase (iterator position)
            {
                size_type i;
                difference_type n;
                T *tmp = _vec_ptr;

                n = position - _vec_ptr;
                _vec_ptr = _alloc.allocate(_capacity);
                for (i = 0; i < n ; i++)
                    _alloc.construct(_vec_ptr + i,tmp[i]);
                i++;
                while (i < _size)
                {
                    _alloc.construct(_vec_ptr + i - 1,tmp[i]);
                    i++;
                }
                for (i = 0; i < _size; i ++)
                    _alloc.destroy(tmp + i);
                _alloc.deallocate(tmp,_capacity);
                _size -= 1;
                position = _vec_ptr + n;
                return position;
            }

            iterator erase (iterator first, iterator last)
            {
                size_type range;
                difference_type n;
                size_type i;
                iterator position;
                T *tmp = _vec_ptr;
                
                n = first - _vec_ptr;
                range = last - first;
                _vec_ptr = _alloc.allocate(_capacity);
                for (i = 0 ; i < n ; i++)
                    _alloc.construct(_vec_ptr + i,tmp[i]);
                while (i < range + n)
                    i++;
                while (i < _size)
                {
                    _alloc.construct(_vec_ptr + i - range,tmp[i]);
                    i++;
                }
                for (i = 0 ; i < _size ; i++)
                    _alloc.destroy(tmp + i);
                _alloc.deallocate(tmp,_capacity);
                position = _vec_ptr + n;
                _size  -= range;
                return position;
            }

            friend void swap (vector& x, vector& y);

            void swap (vector& x)
            {
                T *tmp = _vec_ptr;
                T *tmp2 = x._vec_ptr;
                size_type tmp_size = _size;
                size_type tmp_capacity = _capacity;
                size_type i;

                _size = x.size();
                _capacity = x.capacity();
                _vec_ptr = _alloc.allocate(_capacity);
                for (i = 0 ; i < _size ; i++)
                    _alloc.construct(_vec_ptr + i,x[i]);
                
                x._size = tmp_size;
                x._capacity = tmp_capacity;
                x._vec_ptr = _alloc.allocate(tmp_capacity);
                for (i = 0 ; i < tmp_size ; i++)
                    _alloc.construct(x._vec_ptr + i,tmp[i]);
                
                for (i = 0 ; i < _size ; i++)
                    _alloc.destroy(tmp2 + i);
                for (i = 0 ; i < tmp_size ; i++)
                    _alloc.destroy(tmp + i);
                _alloc.deallocate(tmp,tmp_capacity);
                _alloc.deallocate(tmp2,_capacity);
            }

            void clear()
            {
                size_type i;
                for (i = _size - 1 ; i > _size; i--)
                    _alloc.destroy(_vec_ptr + i);
                _size = 0;
            }

        /*********************************************************************/

        /***************************** Allocator *****************************/
        allocator_type get_allocator() const { return this->_alloc; }

            
        private :
            T *_vec_ptr;
            allocator_type _alloc;
            size_type _size;
            size_type _max_size;
            size_type _capacity;

    };
        /************************* Non Member Functions **********************/

        template <class T, class Alloc>
        bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
        {
            if (lhs.size() == rhs.size())
                return (ft::equal(lhs.begin(),lhs.end(),rhs.begin()));
            return false;
        }

        template <class T, class Alloc>
        bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
        {
            return (!(lhs == rhs));
        }
            
        template <class T, class Alloc>
        bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
        {
            return (ft::lexicographical_compare(lhs.begin(),lhs.end(),
                        rhs.begin(),rhs.end()));
        }
            
        template <class T, class Alloc>
        bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
        {
            return (!(ft::lexicographical_compare(rhs.begin(),rhs.end(),
                        lhs.begin(),lhs.end())));
        }
            
        template <class T, class Alloc>
        bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
        {
            return (ft::lexicographical_compare(rhs.begin(),rhs.end(),
                        lhs.begin(),lhs.end()));
        }

        template <class T, class Alloc>
        bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
        {
            return (!(ft::lexicographical_compare(lhs.begin(),lhs.end(),
                        rhs.begin(),rhs.end())));
        }

     /******************************** swap **********************************/
        template <class T, class Alloc>
        void swap (ft::vector<T,Alloc>& x, ft::vector<T,Alloc>& y)
        {
            x.swap(y);
            return;
        }
}

#endif