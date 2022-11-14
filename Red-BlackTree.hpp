/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Red-BlackTree.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybensell <ybensell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:57:14 by ybensell          #+#    #+#             */
/*   Updated: 2022/11/14 11:56:35 by ybensell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RED_BLACKTREE_HPP
#define RED_BLACKTREE_HPP

#include <iostream>
#include <string>
#include <unistd.h>
#include "tool.hpp"
#include <stdio.h>

# define RED   1
# define BLACK 0
# define LEFT  0
# define RIGHT 1
# define COUNT 10

/*-------------------------------- Node Structure ---------------------------*/
template<class K ,class T>
struct s_tree {
	typedef T value_type;
	typedef K key_type;

	struct s_tree *parent;
	struct s_tree *left;
	struct s_tree *right;
	struct s_tree *prev;
	struct s_tree *next;
	key_type	  key;
	value_type	  *data;
	bool color;
};

/*------------------------------ Iterator Structure -------------------------*/
template <class T, class N>
struct RBtree_Iterator 
{
	typedef T 											value_type;
	typedef value_type*									pointer;
	typedef value_type&									reference;

	typedef	N											nodeType;
	typedef	N*											nodePtr;			

	typedef	typename std::bidirectional_iterator_tag	iterator_category;
	typedef	typename std::ptrdiff_t						difference_type;
	
	RBtree_Iterator ()				{ _n = NULL; };

	RBtree_Iterator (nodePtr node)	{ _n = node; };

	RBtree_Iterator (const RBtree_Iterator &rhs) :_n(rhs._n) {};

	/* 
		Implicit Conversion function , Used when trying to assign or construct
		'Const_iterator' from 'non_const' iterator . It basically construct a 
		new const_iterator based on the normal iterator and return it .
	*/
	operator RBtree_Iterator<  const value_type, const nodeType>() const {
		return RBtree_Iterator< const value_type, const nodeType> (_n);
	}

	RBtree_Iterator &operator=(const RBtree_Iterator &rhs) 
	{
		_n = rhs._n;
		return *this;
	}

	reference operator*() const { return *_n->data;}

	pointer operator->()  const { return _n->data; }
	
	RBtree_Iterator &operator ++()
	{
		_n = _n->next;
		return *this;
	}

	RBtree_Iterator operator ++(int)
	{
		RBtree_Iterator tmp(*this);

		_n = _n->next;
		return tmp;
	}

	RBtree_Iterator &operator --()
	{
		_n = _n->prev;
		return *this;
	}
	RBtree_Iterator operator --(int)
	{
		RBtree_Iterator tmp = *this;
		_n = _n->prev;
		return tmp;
	}

	bool operator == (const RBtree_Iterator& rhs) {  return (_n == rhs._n);}
	bool operator != (const RBtree_Iterator& rhs) const { return (_n != rhs._n);}

	nodePtr _n;
};

/*--------------------------- Red-Black tree class --------------------------*/

template <class Key,class T,class compare , class Allocator >
class RBtree 
{
	public :

		typedef Key                                      				key_type;
		typedef T                                        				value_type;
		typedef compare									 				key_compare;
		typedef Allocator							     				allocator_type;
	
		typedef s_tree<key_type,value_type>								node;
		typedef RBtree_Iterator<value_type,node >		 				Iter;
		typedef RBtree_Iterator<const value_type ,const node > 			const_Iter;
		typedef typename ft::reverse_iterator<Iter>       				reverse_iterator;
        typedef typename ft::reverse_iterator<const_Iter> 				const_reverse_iterator;

		typedef typename allocator_type::reference	     				reference;
		typedef typename allocator_type::const_reference 				const_reference;
		typedef typename allocator_type::pointer         				pointer;
		typedef typename allocator_type::const_pointer   				const_pointer;
		typedef typename allocator_type::size_type       				size_type;
		typedef typename allocator_type::difference_type 				difference_type;

		typedef typename allocator_type::template rebind<node>::other  	allocator_node;

		/*------------------- constructor -----------------*/

		RBtree (const key_compare& cmp ,
				const allocator_type& alloc ,
				const allocator_node& node_alloc = allocator_node()) 
				: _data_alloc(alloc),_node_alloc(node_alloc),_comp(cmp),_size(0),root(NULL)
				{ _end = createNode(key_type(),value_type()); }

		/*------------------- Destructor -----------------*/
		~RBtree()
		{
			freeTree(root);
			freeNode(_end);
		}

		/*------------------- iterators -----------------*/

		Iter 		begin()			{ return Iter(firstElement()); }
		const_Iter  begin() const	{ return const_Iter(firstElement()); }

		Iter		end	()		 	{ return Iter(_end); }
		const_Iter	end	() const 	{ return const_Iter(_end); }

		reverse_iterator rbegin() { return reverse_iterator(lastElement());}
		const_reverse_iterator rbegin() const 
							{ return const_reverse_iterator(lastElement());}
		
		reverse_iterator rend() { return reverse_iterator();}
		const_reverse_iterator rend() const 
						{ return const_reverse_iterator(); }

		/*---------------- Member Functions ---------------*/

		node* createNode(key_type key , value_type data)
		{
			node *n;

			n = _node_alloc.allocate(1);
			_node_alloc.construct(n);
			n->data = _data_alloc.allocate(1);
			_data_alloc.construct(n->data,data);
			n->key	  = key;
			n->parent = NULL;
			n->left   = NULL;
			n->right  = NULL;
			n->prev   = NULL;
			n->next   = NULL;
			n->color  = RED;
			return n;
		}

		node*	firstElement() const
		{
			node *tmp = this->root;
			if (!tmp)
				return _end;

			while (tmp->left)
				tmp = tmp->left;
			return tmp;
		}

		node*	lastElement() const
		{
			node *tmp = this->root;
			if (!tmp)
				return _end;

			while (tmp->right)
				tmp = tmp->right;
			return tmp;
		}

		node*	lower_bound(const key_type &k)
		{
			node *t; 

			t = search(k);
			if (t && !_comp(t->key,k))
				return t;
			return _end;
		}

		node* upper_bound(const key_type &k)
		{
			node *t;

			t = search(k);
			if (t && t->next && !_comp(k,t->key))
				return t->next;
			return  _end;
		}

		/*------------------- search -----------------*/

		node*	search(const key_type &data)
		{
			node *t;

			t = this->root;
			while (t)
			{
				if (!_comp(t->key,data) && !_comp(data,t->key))
					return t;
				else if (_comp(t->key,data))
					t = t->right;
				else if (!_comp(t->key,data))
					t = t->left;
			}
			return _end;
		}

		bool count (const key_type& data) const
		{
			node *t;

			t = this->root;
			while (t)
			{
				if (!_comp(t->key,data) && !_comp(data,t->key))
					return true;
				else if (_comp(t->key,data))
					t = t->right;
				else if (!_comp(t->key,data))
					t = t->left;
			}
			return false;
		}

		/*------------------- rotation -----------------*/

		void leftRotation(node *p)
		{
			node *tmp;

			tmp = p->right;
			p->right = tmp->left;
			if (tmp->left)
				tmp->left->parent = p;
			if (p->parent)
			{   
				tmp->parent = p->parent;
				if (p->parent->left == p)
					p->parent->left = tmp;
				else
					p->parent->right = tmp;
			}
			else
			{
				tmp->parent = NULL;
				this->root  = tmp;
			}
			p->parent = tmp;
			tmp->left = p;
		}

		void	rightRotation(node *p)
		{
			node *tmp;

			tmp = p->left;
			p->left = tmp->right;
			if (tmp->right)
				tmp->right->parent = p;
			if (p->parent)
			{
				tmp->parent = p->parent;
				if (p->parent->left == p)
					p->parent->left = tmp;
				else
					p->parent->right = tmp;
			}
			else
			{
				tmp->parent = NULL;
				this->root  = tmp;
			}
			p->parent  = tmp;
			tmp->right = p;
		}

		/*------------------- Insertion -----------------*/

		ft::pair<Iter,bool> addToTree(node *n,node *pos)
		{
			node *tmp;

			tmp = pos;
			
			if (!tmp)
			{
				n->color = BLACK;
				n->next = this->_end;
				this->root = n;
				this->_size++;
				return ft::make_pair(Iter(tmp),true);
			}
			while (tmp)
			{
				if (!_comp(n->key,tmp->key) 
						&& !_comp(tmp->key,n->key))
					return ft::make_pair(Iter(tmp),false);
				if (_comp(n->key,tmp->key))
				{
					if (tmp->left == NULL)
					{
						n->parent = tmp;
						tmp->left = n;
						break;
					}
					else 
						tmp = tmp->left;
				}
				else if (!_comp(n->key,tmp->key))
				{
					if (tmp->right == NULL)
					{
						n->parent = tmp;
						tmp->right = n;
						break;
					}
					else
						tmp = tmp->right;
				}
			}
			n->next = successor(n->key);
			n->prev = predeccessor(n->key);
			if (n->prev)
				n->prev->next = n;
			n->next->prev = n;
			this->_size++;
			return ft::make_pair(Iter(tmp),true);
		}


		void insertBalancing(node *n)
		{
			node *u;	// uncle 
			node *p;	// parent of the current node
			bool dir;	// direction of the node acording to the grandPa
			while (n && n != this->root)
			{
				p = n->parent;

				// parent color is BLACK , No violation of the rules 
				if (p->color == BLACK)
					break;

				// now parent is RED , we check the uncle of the node
				if (p->parent->left == p)
				{
					u = p->parent->right;
					dir = LEFT;
				}
				else
				{
					u = p->parent->left;
					dir = RIGHT;
				}

				// if the uncle is RED , we just re-color 
				if (u && u->color == RED)
				{
					u->color = BLACK;
					p->color = BLACK;
					p->parent->color = RED;
					// We move the node to the grandParent since Its RED Now and we re-check
					n = p->parent;
				}
				else
				{
					/* 
						now uncle is BLACK we have two cases :
							- the node is `inner` child of It grandparent 
							- the node is `outter` child of It grandparent
					*/
					if (dir == LEFT)
					{
						if (n == p->parent->left->right)
						{
							// left-right rotation
							n = p;
							leftRotation(p);
						}
						else
						{
							p->color = BLACK;
							p->parent->color = RED;
							rightRotation(p->parent);
						}
					}
					else
					{
						if (n == p->parent->right->left)
						{
							// right-left rotation 
							n = p;
							rightRotation(p);
						}
						else
						{
							p->color = BLACK;
							p->parent->color = RED;
							leftRotation(p->parent);
						}
					}
				}
			}
			if ((this->root)->color == RED)
				(this->root)->color = BLACK;
		}

		ft::pair<Iter,bool> insert(const key_type &key, const value_type &data,node *position)
		{
			node* n = createNode(key,data);
			ft::pair<Iter,bool> 	ret;
			if (position)
				ret = addToTree(n,position);
			else
				ret = addToTree(n,this->root);
			if (!ret.second)
			{
				freeNode(n);
				return ret ;
			}
			insertBalancing(n);
			return ft::make_pair(Iter(n),true);
		}

		/*------------------- predecc and success -----------------*/

		node*	predeccessor(const key_type &key)
		{
			node *t,*pred;

			//  predeccessor  of a node is the node with the greatest key 
			// 	smaller than the key of the current n in Its left subtree

			// 	- if the node doesnt have a left subtree, the successor is
			// 	  one of Its ancestor

			t = this->root;
			pred = NULL;
			while (t)
			{
				if (_comp(t->key, key))
				{
					pred = t;
					t = t->right;
				}
				else if (!_comp(t->key,key) &&
					 _comp(key,t->key))
					t = t->left;
				else if (!_comp(t->key,key) 
						&& !_comp(key,t->key))
				{
					if (t->left)
					{
						t = t->left;
						while (t)
						{
							if (t->right)
								t = t->right;
							else if (t->left)
								t = t->left;
							else
								return t;
						}
					}
					else
						break;
				}
			}
			return pred;
		}

		node*	successor(const key_type  &key)
		{
			node *t,*succ;

			/* Successor of a node is the node with the smallest key 
				greater than the key of the current n in Its right subtree

				- if the node doesnt have a right subtree , the successor is
					one of Its ancestor 

			*/
			t = this->root;
			succ = this->_end;
			while (t)
			{
				if (_comp(t->key, key))
					t = t->right;
				else if (!_comp(t->key, key) 
					&& _comp(key,t->key))
				{
					succ = t;
					t = t->left;
				}
				else if (!_comp(t->key,key) 
						&& !_comp(key,t->key))
				{
					if (t->right)
					{
						t = t->right;
						while (t)
						{
							if (t->left)
								t = t->left;
							else if (t->right)
								t = t->right;
							else
								return t;
						}
					}
					else
						break;
				}
			}
			return succ;
		}

		/*------------------- deletion -----------------*/

		void	rebalance(node *n, node *u)
		{
			/* 
				n : the node to be deleted 
				u : the node that will replace the deleted node
				s : sibling of the node
				c : close nephew 
				d : distant nephew
			*/

			/* saving the deleted node pointer to free at the end */
			node *tmp	= n; 
			node *p 	= n->parent;

			/* Node being replaced by Its one child */
			if (u)
			{
				u->color = BLACK;
				if (p->left == n)
					p->left = u;
				else
					p->right = u;
				u->parent = p;
			}
			/* node is leaf and BLACK */
			else if (!u && n->color == BLACK)
			{
				bool dir;
				node *s,*d,*c;
			
				while (p != NULL)
				{
					if (p->left == n)
					{
						s = p->right;
						d = s->right;
						c = s->left;
						dir = LEFT;
					}
					else
					{
						s = p->left;
						d = s->left;
						c = s->right;
						dir = RIGHT;
					}
					/* case 4 :parent is RED and s+c+d BLACK */
					if (p->color == RED && 
						(s->color == BLACK && ( (d && c && 
							d->color ==  BLACK && c->color == BLACK)
							|| (!d && !c))))
					{
						p->color = BLACK;
						s->color = RED;
						break ;
					}
					/* case 2 : p+s+c+d all BLACK */
					else if (p->color == BLACK && 
						(s->color == BLACK && ((d && c && 
							d->color  == BLACK && c->color == BLACK)
							|| (!d && !c))))
					{
						s->color = RED;
						n = p;
						p = p->parent;
						continue;
					}
					/* case 3 : sibling is RED */
					else if (s->color == RED)
					{	
						p->color = RED;
						s->color = BLACK;
						if (dir == LEFT)
							leftRotation(p);
						else
							rightRotation(p);
						continue;
					}
					else if (s->color == BLACK)
					{
					/* case 5 : s is BLACK & d is BLACK */
						if (!d || (d && d->color == BLACK /*&&
							c && c->color == RED*/))
						{
							c->color = BLACK;
							s->color = RED;
							if (dir == RIGHT)
								leftRotation(s);
							else
								rightRotation(s);
							continue;
						}
					/* case 6 : s is BLACK & d is RED */
						else if (d && d->color == RED)
						{
							s->color = p->color;
							d->color =  p->color = BLACK;
							if (dir == RIGHT)
								rightRotation(p);
							else
								leftRotation(p);
							break ;
						}
					}
				}
			}
			/* 	deleting the node and setting  
				it parent to NULL + RED leaf case */
			if (tmp->parent)
			{
				if (tmp->parent->left == tmp)
					tmp->parent->left = NULL;
				else if (tmp->parent->right == tmp)
					tmp->parent->right = NULL;
				freeNode(tmp);
				tmp = NULL;
			}
			return ;
		}

		/* basic  binary tree deletion */ 
		void	removeNode(node *n)
		{
			node *t;

			/*	node is a leaf	*/
			if (n->prev)
				n->prev->next = n->next;
			if (n->next)
				n->next->prev = n->prev;
			if (!n->left && !n->right)
			{
				this->_size--;
				if (n == this->root)
				{
					freeNode(n);
					this->root = NULL;
					return ;
				}
				rebalance(n,NULL);
			}

			/*	node has only one child */
			else if (!n->left || !n->right)
			{	

				this->_size--;
				if (n->left)
					t = n->left;
				else
					t = n->right;
				if (n == this->root)
				{
					freeNode(n);
					t->parent = NULL;
					this->root = t;
					return;
				}
				rebalance(n,t);
			}

			/* node has two childs */
			else if (n->left && n->right)
			{
				value_type *dataTmp;

				this->_size--;
				dataTmp = n->data;
				t = predeccessor(n->key);
				if (!t)
					t = successor(n->key);
				n->data = t->data;
				t->data = dataTmp;
				rebalance(t,NULL);
			}
		}

		bool	Delete(const key_type &key)
		{
			node *tmp;
			tmp = this->root;
			while (tmp)
			{
				if (!_comp(tmp->key,key) 
						&& !_comp(key,tmp->key))
				{
					removeNode(tmp);
					return true ;
				}
				else if (!_comp(tmp->key, key))
					tmp = tmp->left;
				else
					tmp = tmp->right;
			}
			return false;
		}

		void	clear()
		{
			freeTree(this->root);
			this->_size = 0;
			this->root = NULL;
		}

		/*------------------- Free func -----------------*/
		void	freeTree(node *root)
		{
			/* deletion using Preorder traversel */
			if (root)
			{
				if (root->left)
					freeTree(root->left);
				if (root->right)
					freeTree(root->right);
				freeNode(root);
			}
			return ;
		}

		void	freeNode(node *n)
		{
			if (n )
			{
				_data_alloc.destroy(n->data);
				_data_alloc.deallocate(n->data,1);
				_node_alloc.destroy(n);
				_node_alloc.deallocate(n,1);
			}
		}

		void	printTreeUtil(node *root, int space)
		{
		
			if (root == NULL)
				return;
		
			space += COUNT;
		
			printTreeUtil(root->right, space);

			std::cout<<std::endl;
			for (int i = COUNT; i < space; i++)
				std::cout << " ";
			std::cout<<root->key << " " << root->data->second << " " ;
			std::cout << root->color<<"\n";
			printTreeUtil(root->left, space);
		}

		void printTree()
		{
			printTreeUtil(this->root, 0);
		}

		key_compare 	getKeyComp() 	const { return _comp;}
		node*			getRoot() 		const { return this->root;}
		size_type		getSize() 		const { return this->_size;}
		allocator_type	getAllocator () const { return this->_data_alloc;}

		void swap(RBtree &tree)
		{
			std::swap(root,tree.root);
			std::swap(_data_alloc,tree._data_alloc);
			std::swap(_comp,tree._comp);
			std::swap(_node_alloc,tree._node_alloc);
			std::swap(_size,tree._size);
			std::swap(_end,tree._end);
		}

		private :
			allocator_type	_data_alloc;
			allocator_node	_node_alloc;
			key_compare		_comp;
			size_type		_size;
			node 			*root;
			node			*_end;
};

#endif