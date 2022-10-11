/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybensell <ybensell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 09:43:12 by ybensell          #+#    #+#             */
/*   Updated: 2022/10/11 13:55:58 by ybensell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include <map>
#include <string>
#include <iostream>
#include "tool.hpp"
#include "Red-BlackTree.hpp"

namespace ft {

	template <
		class Key,
		class T,
		class Compare = std::less<Key>,
		class Allocator = std::allocator<ft::pair<const Key, T> >
			> 
	class map 
	{
		public :
			typedef Key                                      key_type;
			typedef T                                        mapped_type;
			typedef pair<const key_type, mapped_type>        value_type;
			typedef Compare									 key_compare;
			typedef Allocator                                allocator_type;
			typedef typename allocator_type::reference       reference;
			typedef typename allocator_type::const_reference const_reference;
			typedef typename allocator_type::pointer         pointer;
			typedef typename allocator_type::const_pointer   const_pointer;
			typedef typename allocator_type::size_type       size_type;
			typedef typename allocator_type::difference_type difference_type;

			explicit map (const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type())
			{
				_tree();
				_alloc = alloc;
				_comp = comp;
			}
		
			template <class InputIterator>
			map (InputIterator first, InputIterator last,
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type())
			{
					
			}
			
			map (const map& x)
			{
				
			}
			
			typedef	Bi_Iter<value_type>                 iterator;
			typedef Bi_Iter<const value_type>           const_iterator;
			typedef std::reverse_iterator<iterator>         reverse_iterator;
			typedef std::reverse_iterator<const_iterator>    const_reverse_iterator;
			// typedef INSERT_RETURN_TYPE<iterator, node_type>  insert_return_type;    
		private :
			RBtree<value_type> _tree;
			allocator_type _alloc ;
			key_compare _comp;
	};

}


#endif