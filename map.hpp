/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybensell <ybensell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 09:43:12 by ybensell          #+#    #+#             */
/*   Updated: 2022/11/08 10:38:38 by ybensell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include <map>
#include <string>
#include <iostream>
#include "Red-BlackTree.hpp"
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
			typedef typename allocator_type::reference       reference;
			typedef typename allocator_type::const_reference const_reference;
			typedef typename allocator_type::pointer         pointer;
			typedef typename allocator_type::const_pointer   const_pointer;
			typedef typename allocator_type::size_type       size_type;
			typedef typename allocator_type::difference_type difference_type;
			typedef RBtree<key_type,mapped_type ,key_compare,allocator_type>		 		RBtree;
		
		/*-------------------------- Constructors ---------------------------*/

			explicit map (const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type())
			{
			}
			
		class value_compare
      	 : public std::binary_function<value_type, value_type, bool>
		{
			friend class map<Key,T,Compare,Allocator>;
			protected:
			Compare comp;
		
			value_compare(Compare _c)
			: comp(_c) { }
		
			public:
			bool operator()(const value_type& _x, const value_type& _y) const
			{ return comp(_x.first, _y.first); }
		};

		/*--------------------------- capacity ------------------------------*/
		bool empty() const
		{
			if (_tree.getSize() == 0)
				return true;
			return false;
		}
		size_type size() const { return _tree.getSize();}
		size_type max_size() const { return _tree.getAllocator().max_size();}

		/*--------------------------- Iterators ------------------------------*/
		
			typedef typename RBtree::Iter						iterator;
			typedef typename RBtree::const_Iter					const_iterator;
			

			iterator		begin()		  {return _tree.begin();} 
			const_iterator	begin() const {return _tree.begin();}

			iterator		end()			{ return _tree.end();}
			const_iterator	end() const		{return _tree.end();}

		/*---------------------------- Modifiers ----------------------------*/

		pair<iterator,bool> insert (const value_type& val)
			{ return (_tree.insert(val,NULL)); }
					
		iterator insert (iterator position, const value_type& val)
			{ return (_tree.insert(val,position._n).first); }
	
		template <class InputIterator>
		void insert (InputIterator first, InputIterator last)
		{
			while (first != last)
			{
				_tree.insert(*first._n->data,NULL);
				first++;
			};
		}

		void erase (iterator position)
		{
			_tree.removeNode(position._n);
		}

		size_type erase (const key_type& k)
		{
			if (_tree.Delete(k))
				return 1;
			return 0;
		}

		void erase (iterator first, iterator last)
		{
			while (first != last)
			{
				_tree.removeNode(first._n);
				first++;
			}
			
		}

		void swap (map& x)
		{
			map tmp = x;
			
			x._tree = _tree;
			_tree = tmp._tree;
		}

		void	clear()
		{
			_tree.clear();
		}
		/*------------------------- element accessors ---------------------*/
		mapped_type& operator[] (const key_type& k)
		{
			return ((*(this->_tree.insert(make_pair(k,mapped_type()),NULL)).first).second);
		}

		/*----------------------------- Searching -------------------------*/
		
		iterator find (const key_type& k)
		{
		 	return iterator(_tree.search(k));
		}

		const_iterator find (const key_type& k) const
		{
			return const_iterator(_tree.search(k));
		}

		size_type count (const key_type& k) const
		{
			if (_tree.count(k))
				return 1;
			return 0;
		}

		iterator lower_bound (const key_type& k){ return _tree.lower_bound(k); }
		const_iterator lower_bound (const key_type& k) const
		{
			return _tree.lower_bound(k);
		}
		
		iterator upper_bound (const key_type& k) { return _tree.upper_bound(k); }
		const_iterator upper_bound (const key_type& k) const
		{
			return _tree.upper_bound(k);
		}

		/*----------------------------- observers -------------------------*/
		key_compare key_comp() const { return _tree.getKeyComp();}
		value_compare value_comp() const { return value_compare(_tree.getKeyComp()); }

		RBtree &getTree(){ return this->_tree;};
		private :
			RBtree _tree;
	};
}

#endif