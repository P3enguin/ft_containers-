/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybensell <ybensell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 09:43:12 by ybensell          #+#    #+#             */
/*   Updated: 2022/10/18 12:33:12 by ybensell         ###   ########.fr       */
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
			// typedef s_tree<value_type>						 node;
			typedef typename allocator_type::reference       reference;
			typedef typename allocator_type::const_reference const_reference;
			typedef typename allocator_type::pointer         pointer;
			typedef typename allocator_type::const_pointer   const_pointer;
			typedef typename allocator_type::size_type       size_type;
			typedef typename allocator_type::difference_type difference_type;
			// typedef typename allocator_type::template rebind<node>::other  allocator_node;
			// typedef RBtree<value_type ,allocator_node>		 				RBtree;
			
	
		/*-------------------------- Constructors ---------------------------*/

			explicit map (const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type())
			{
				_alloc = alloc;
				_comp = comp;
				_size = 0;
				_capacity = 0;
			}
			void insert(const value_type &val)
			{
				// p = _alloc.allocate(1);
				// _alloc.construct(p,val);

				_tree.insert(val);
				_tree.printTree();
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


		/*---------------------------- Modifiers ----------------------------*/

		// pair<iterator,bool> insert (const value_type& val)
		// {
			
		// }
		// iterator insert (iterator position, const value_type& val){}
		// template <class InputIterator>  void insert (InputIterator first, 
		// 		InputIterator last){}


		/*----------------------------- Searching -------------------------*/
		// iterator find (const key_type& k)
		// {
		// 	return iterator(_tree.search(k));
		// }
		// const_iterator find (const key_type& k) const;

		private :
			// RBtree _tree;
			pointer p;
			allocator_type _alloc ;
			// allocator_node _alloc_node;
			key_compare _comp;
			size_type _size;
			size_type _capacity;
	};
}

#endif