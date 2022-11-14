/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybensell <ybensell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 09:43:12 by ybensell          #+#    #+#             */
/*   Updated: 2022/11/14 11:41:53 by ybensell         ###   ########.fr       */
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
			typedef Key                                      					key_type;
			typedef T                                        					mapped_type;
			typedef pair<const key_type, mapped_type>        					value_type;
			typedef Compare									 					key_compare;
			typedef Allocator                                					allocator_type;

			typedef typename allocator_type::reference       					reference;
			typedef typename allocator_type::const_reference 					const_reference;
			typedef typename allocator_type::pointer         					pointer;
			typedef typename allocator_type::const_pointer   					const_pointer;
			typedef typename allocator_type::size_type      					size_type;
			typedef typename allocator_type::difference_type 					difference_type;

			typedef RBtree<key_type,value_type ,key_compare,allocator_type>	RBtree;
		
		/*-------------------------- Constructors ---------------------------*/

			explicit map (const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type()) 
				: _comp(comp),_alloc(alloc),_tree(_comp,_alloc)
				{}
			
			template <class InputIterator>
			map (InputIterator first, InputIterator last,
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type())
				: _comp(comp),_alloc(alloc),_tree(_comp,_alloc) 
				{ 
					insert(first,last);
				}

			map (const map& x) : _comp(x._comp),_alloc(x._alloc),_tree(_comp,_alloc) 
			{
				insert(x.begin(),x.end());
			}

			map& operator= (const map& x)
			{
				clear();
				insert(x.begin(),x.end());
				return *this;
			}

		~map(){}
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

		size_type size     () 	const { return _tree.getSize();}
		size_type max_size ()	const { return _tree.getAllocator().max_size();}

		/*--------------------------- Iterators ------------------------------*/
		
			typedef typename RBtree::Iter						iterator;
			typedef typename RBtree::const_Iter					const_iterator;

			typedef typename RBtree::reverse_iterator			reverse_iterator;
			typedef typename RBtree::const_reverse_iterator		const_reverse_iterator;
			

			iterator		begin()		  	{ return _tree.begin();} 
			const_iterator	begin() const 	{ return _tree.begin();}

			iterator		end()			{ return _tree.end();}
			const_iterator	end() const		{ return _tree.end();}

			reverse_iterator rbegin()		{ return _tree.rbegin();}
			reverse_iterator rend  ()		{ return _tree.rend();}

			const_reverse_iterator rbegin() const { return _tree.rbegin();}
			const_reverse_iterator rend  () const { return _tree.rend();}

		/*---------------------------- Modifiers ----------------------------*/

		pair<iterator,bool> insert (const value_type& val)
			{ return (_tree.insert(val.first,val,NULL)); }
					
		iterator insert (iterator position, const value_type& val) {
				iterator it;
				it = find(val.first);
				if (it != end())
					return it;
				return (_tree.insert(val.first,val,position._n).first); 
		}
	
		template <class InputIterator>
		void insert (InputIterator first, InputIterator last)
		{
			while (first != last)
			{
				_tree.insert(first._n->key,*first._n->data,NULL);
				first++;
			};
		}
 
		void erase (iterator position) { _tree.removeNode(position._n); }

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
				erase(first);
				first++;
			}
		}

		void swap (map& x) { _tree.swap(x._tree); }

		void	clear() { _tree.clear(); }

		/*------------------------- element accessors ---------------------*/
		mapped_type& operator[] (const key_type& k)
		{
			return ((*(this->_tree.insert(k,make_pair(k,mapped_type()),NULL)).first).second);
		}

		/*----------------------------- Searching -------------------------*/
		
		iterator find (const key_type& k) { return iterator(_tree.search(k)); }

		const_iterator find (const key_type& k) const {
			return const_iterator(_tree.search(k));
		}

		size_type count (const key_type& k) const
		{
			if (_tree.count(k))
				return 1;
			return 0;
		}

		iterator 		lower_bound (const key_type& k)
		{ 
			return iterator(_tree.lower_bound(k)); 
		}
		const_iterator lower_bound (const key_type& k) const
		{
			return const_iterator(_tree.lower_bound(k));
		}
		
		iterator 		upper_bound (const key_type& k) 
		{
			return iterator(_tree.upper_bound(k));
		}

		const_iterator upper_bound (const key_type& k) const
		{
			return const_iterator(_tree.upper_bound(k));
		}

		pair<iterator,iterator>             equal_range (const key_type& k){
			return ft::make_pair(lower_bound(k),upper_bound(k));
		}

		pair<const_iterator,const_iterator>	equal_range (const key_type& k) const
		{
			return ft::make_pair(lower_bound(k),upper_bound(k));
		}

		/*----------------------------- getters -------------------------*/
		key_compare 	key_comp  () const { return _comp;}
		value_compare 	value_comp() const { return value_compare(_comp);}
		allocator_type get_allocator() const	{ return _alloc; };
		RBtree			&getTree  ()	   { return this->_tree;}

		private :
			key_compare 	_comp;
			allocator_type _alloc;
			RBtree 			_tree;
	};
}

#endif