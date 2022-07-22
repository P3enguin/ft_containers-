/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybensell <ybensell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 10:42:47 by ybensell          #+#    #+#             */
/*   Updated: 2022/07/22 15:42:40 by ybensell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <vector>
#include <string>
#include <iostream>

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
            
            /************************ Constructors ********************************/

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
                _vec_ptr = _alloc.allocate(_size);
                for (int i = 0; i < _size ; i++ )
                    _alloc.construct(_vec_ptr + i,val);
            }
                
            // fill and copy constructor left ;
            
            /**********************************************************************/
            
            /*************************** Capacity ***********************************/
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
                    int i = 0;
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
            }

            
            // typedef implementation-defined                   iterator;
            // typedef implementation-defined                   const_iterator;
            // typedef std::reverse_iterator<iterator>          reverse_iterator;
            // typedef std::reverse_iterator<const_iterator>    const_reverse_iterator;
        
        private :
            T *_vec_ptr;
            allocator_type _alloc;
            size_type _size;
            size_type _max_size;
            size_type _capacity;

    };

}

#endif