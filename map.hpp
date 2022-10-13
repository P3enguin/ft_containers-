/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybensell <ybensell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 09:43:12 by ybensell          #+#    #+#             */
/*   Updated: 2022/10/13 15:14:22 by ybensell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include <map>
#include <string>
#include <iostream>
#include "tool.hpp"

namespace ft {

	template <
		class Key,
		class T,
		class Compare = std::less<Key>,
		class Allocator = std::allocator< ft::pair<const Key, T> >
			>
	class map 
	{
		
		public :
			typedef Key                                      key_type;
			typedef T                                        mapped_type;
			typedef pair<const key_type, mapped_type>        value_type;
			typedef Compare									 key_compare;
			typedef Allocator                                allocator_type;
			typedef RBtree<value_type>				 		 RBtree;
			typedef s_tree<value_type>						 node;
			typedef typename allocator_type::reference       reference;
			typedef typename allocator_type::const_reference const_reference;
			typedef typename allocator_type::pointer         pointer;
			typedef typename allocator_type::const_pointer   const_pointer;
			typedef typename allocator_type::size_type       size_type;
			typedef typename allocator_type::difference_type difference_type;
			typedef typename allocator_type::template rebind<node>::other  allocator_node;
			
	
		/*-------------------------- Constructors ---------------------------*/

			explicit map (const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type())
			{
				_alloc = alloc;
				_comp = comp;
				_size = 0;
				_capacity = 0;
			}
		
			// template <class InputIterator>
			// map (InputIterator first, InputIterator last,
			// 	const key_compare& comp = key_compare(),
			// 	const allocator_type& alloc = allocator_type())
			// {
					
			// }
			
			// map (const map& x)
			// {
				
			// }
			

		/*--------------------------- Iterators ------------------------------*/
		template <class node,typename P = value_type>
		class Bi_Iter 
		{
			public :
			/*--------------------- Member types definition -------------------------*/
				typedef s_tree<P>*				pointer;

				// typedef typename pointer::data	value;
				typedef typename std::ptrdiff_t difference_type;
				typedef typename std::bidirectional_iterator_tag     iterator_category;
				// typedef typename P::first first_type;
				// typedef typename P::second second_type;

				// first_type	first;
				// second_type	second;


			/*---------------------------- Constructors -----------------------------*/

				Bi_Iter () {};
				Bi_Iter (pointer ptr) {_iter = ptr;}
				Bi_Iter (const Bi_Iter<node> &obj) {_iter = obj._iter;};

				Bi_Iter<node> &operator  = (const Bi_Iter<node> &obj){ _iter = obj._iter;
								 return *this ;};
		
			/*------------------------- Operators Overloads -------------------------*/

				bool    operator  == (const Bi_Iter<node> &obj) const
				{
					if (_iter == obj.getIter())
						return true;
					else
						return false;
				}

				bool    operator  != (const Bi_Iter<node> &obj) const
				{
					if (_iter != obj.getIter())
						return true;
					return false;
				}

				Bi_Iter<node>& operator ++() { 
					_iter = _tree->successor(_iter->data);
					return *this;
					} 

				Bi_Iter<node>& operator --() {
						_iter = _tree->predeccessor(_iter->data);
						return *this;
					}

				Bi_Iter<node> operator ++(int) {
					Bi_Iter<tree> tmp = *this;
					_iter = _tree->successor(_iter->data);
					return tmp;
				}

				Bi_Iter<node> operator --(int) {
					Bi_Iter<node> tmp = *this;
					_iter = _tree->predeccessor(_iter->data);
					return tmp;
				}

				// P & operator  *()       { return _iter->data ;}
				// P & operator  *() const { return _iter->data ;}
				// pointer  operator ->()  { return _iter->data ;}

				//getter for _iter pointer 
				pointer getIter() const {return _iter;}
	
			protected :
				pointer		_iter;  /* this is the pointer that track memory of the container */
		};
			typedef	Bi_Iter<node,value_type>				iterator;
			typedef Bi_Iter<node,const value_type>		const_iterator;
			typedef std::reverse_iterator<iterator>			reverse_iterator;
			typedef std::reverse_iterator<const_iterator>	const_reverse_iterator;
		
			iterator begin() 			 { return iterator(_tree.firstElement()); } 
			const_iterator begin() const { return const_iterator(_tree.firstElement());} 

		/*---------------------------- Modifiers ----------------------------*/

		pair<iterator,bool> insert (const value_type& val)
		{
			node *n	= _alloc_node.allocate(1);
			// if (_tree.find())
			n->data = _alloc.allocate(1);
			_alloc.construct(n->data,val);
			_tree.createNode(n);
			_tree.insert(n);
			return pair<iterator,bool>(begin(),true);
		}
		// iterator insert (iterator position, const value_type& val){}
		// template <class InputIterator>  void insert (InputIterator first, 
		// 		InputIterator last){}


		/*----------------------------- Searching -------------------------*/
		iterator find (const key_type& k)
		{
			return iterator(_tree.search(k));
		}
		const_iterator find (const key_type& k) const;

		private :
			RBtree _tree;
			allocator_type _alloc ;
			allocator_node _alloc_node;
			key_compare _comp;
			size_type _size;
			size_type _capacity;
	};
}

#endif