/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Red-BlackTree.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybensell <ybensell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:57:14 by ybensell          #+#    #+#             */
/*   Updated: 2022/10/18 18:04:34 by ybensell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RED_BLACKTREE_HPP
#define RED_BLACKTREE_HPP

#include <iostream>
#include <string>
#include <unistd.h>
#include "tool.hpp"
# define RED   1
# define BLACK 0
# define LEFT  0
# define RIGHT 1
# define COUNT 10

template<class Key,class T>
struct s_tree {
	typedef ft::pair<const Key,T> value_type;

	struct s_tree *parent;
	struct s_tree *left;
	struct s_tree *right;
	value_type	  *data;
	bool color;
} ;

/*TODO : add next and prev to every node ,  */

template <class Key,class T>
struct RBtree_Iterator 
{
	typedef ft::pair<const Key,T>	value_type;

	typedef value_type*				pointer;
	typedef value_type&				reference;
	typedef	s_tree<Key,T>*			nodePtr;

	typedef	typename std::bidirectional_iterator_tag	iterator_category;
	typedef	typename std::ptrdiff_t						difference_type;

	
	RBtree_Iterator() : _n(NULL) {};
	RBtree_Iterator(nodePtr n) :_n(n) {};
	RBtree_Iterator(const RBtree_Iterator &rhs): _n(rhs._n) {};
	
	RBtree_Iterator &operator=(const RBtree_Iterator &rhs)
	{
		_n = rhs._n;
		return *this;
	}

	RBtree_Iterator &operator ++()
	{
		
	}
	nodePtr _n;
};

template <class Key,class T,class compare , class Allocator >
class RBtree 
{
	public :

		typedef Key										 key_type;
		typedef T										 mapped_type;
		typedef ft::pair<const key_type, mapped_type>    value_type;
		typedef compare									 key_compare;
		typedef Allocator							     allocator_type;
		typedef s_tree<key_type,mapped_type>			 node;
		typedef RBtree_Iterator<key_type,mapped_type>	 Iter;
		typedef typename allocator_type::reference	     reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer         pointer;
		typedef typename allocator_type::const_pointer   const_pointer;
		typedef typename allocator_type::size_type       size_type;
		typedef typename allocator_type::difference_type difference_type;
		typedef typename allocator_type::template rebind<node>::other  allocator_node;

		
		RBtree(const allocator_type& alloc = allocator_type(),
			const allocator_node& node_alloc = allocator_node()) 
				: _data_alloc(alloc),_node_alloc(node_alloc)
		{
			this->root = NULL;
		}

		node* createNode(value_type data)
		{
			node *n;

			n = _node_alloc.allocate(1);
			_node_alloc.construct(n);
			n->data = _data_alloc.allocate(1);
			_data_alloc.construct(n->data,data);
			n->parent = NULL;
			n->left = NULL;
			n->right = NULL;
			n->color = RED;
			return n;
		}

		node*	firstElement()
		{
			node *tmp = this->root;

			while (tmp->left)
				tmp = tmp->left;
			return tmp;
		}
		node*	lastElement()
		{
			node *tmp = this->root;

			while (tmp->right)
				tmp = tmp->right;
			return tmp;
		}

		node*	search(const value_type &data)
		{
			node *t;

			t = this->root;
			while (t)
			{
				if (!comp(t->data->first,data.first) && !comp(data.first,t->data->first))
					return t;
				else if (comp(t->data->data,data.first))
					t = t->right;
				else if (!comp(t->data->first,data.first))
					t = t->left;
			}
			return NULL;
		}

		bool addToTree(node *n)
		{
			node *tmp;

			tmp = root;
			if (!tmp)
			{
				n->color = BLACK;
				this->root = n;
				return true;
			}
			while (tmp)
			{
				if (!comp(n->data->first,tmp->data->first) 
						&& !comp(tmp->data->first,n->data->first))
					return false; // here when two elements are equal 
				if (comp(n->data->first,tmp->data->first))
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
				else
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
			return true;
		}

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
				this->root = tmp;
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
				this->root = tmp;
			}
			p->parent = tmp;
			tmp->right = p;
		}

		void insert(const value_type &data)
		{
			node* n = createNode(data);
			if (!addToTree(n))
			{
				_data_alloc.destroy(n->data);
				_data_alloc.deallocate(n->data,1);
				_node_alloc.destroy(n);
				_node_alloc.deallocate(n,1);
				return ;
			}

			node *u;   // uncle 
			node *p;   // parent of the current node
			bool dir;       // direction of the node acording to the grandPa

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
	
		node *	predeccessor(value_type *data)
		{
			node *t,*pred;

			// /* predeccessor  of a node is the node with the greatest key 
			// 	smaller than the key of the current n in Its left subtree

			// 	- if the node doesnt have a left subtree , the successor is
			// 		one of Its ancestor

			t = this->root;
			pred = NULL;
			while (t)
			{
				if (comp(t->data->first, data->first))
				{
					pred = t;
					t = t->right;
				}
				else if (!comp(t->data->first,data->first) &&
					 comp(data->first,t->data->first))
					t = t->left;
				else if (!comp(t->data->first,data->first) 
						&& !comp(data->first,t->data->first))
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

		node*	successor(value_type  *data)
		{
			node *t,*succ;

			/* Successor of a node is the node with the smallest key 
				greater than the key of the current n in Its right subtree

				- if the node doesnt have a right subtree , the successor is
					one of Its ancestor 

			*/
			t = this->root;
			succ = NULL;
			while (t)
			{
				if (comp(t->data->first, data->first))
					t = t->right;
				else if (!comp(t->data->first, data->first) 
					&& comp(data->first,t->data->first))
				{
					succ = t;
					t = t->left;
				}
				else if (!comp(t->data->first,data->first) 
						&& !comp(data->first,t->data->first))
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

		void	rebalance(node *n,node *u)
		{
			/* 
				n : the node to be deleted 
				u : the node that will replace the deleted node
				s : sibling of the node
				c : close nephew 
				d : distant nephew
			*/

			node *tmp = n; /* saving the deleted node poTer to free at the end */
			node *p = n->parent;

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
							d->color == c->color == BLACK)
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
				_data_alloc.destroy(tmp->data);
				_data_alloc.deallocate(tmp->data,1);
				_node_alloc.destroy(tmp);
				_node_alloc.deallocate(tmp,1);
				tmp = NULL;
			}
			return ;
		}

		/* basic  binary tree deletion */ 
		void	removeNode(node *n)
		{
			node *t;
			
			/*	node is  the root */
			if (n == this->root)
			{
				this->root = NULL;
				_data_alloc.destroy(n->data);
				_data_alloc.deallocate(n->data,1);
				_node_alloc.destroy(n);
				_node_alloc.deallocate(n,1);
				n = NULL;
				return ;
			}

			/*	node is a leaf	*/
			if (!n->left && !n->right)
				rebalance(n,NULL);

			/*	node has only one child */
			else if (!n->left || !n->right)
			{	
				if (n->left)
					t = n->left;
				else
					t = n->right;
				rebalance(n,t);
			}

			/* node has two childs */
			else if (n->left && n->right)
			{
				t = predeccessor(n->data);
				if (!t)
					t = successor(n->data);
				n->data = t->data;
				rebalance(t,NULL);
			}
		}

		void	Delete(const value_type  &data)
		{
			node *tmp;
			tmp = this->root;
			while (tmp)
			{
				if (!comp(tmp->data->first,data.first) 
						&& !comp(data.first,tmp->data->first))
				{
					removeNode(tmp);
					return ;
				}
				else if (!comp(tmp->data->first, data.first))
					tmp = tmp->left;
				else
					tmp = tmp->right;
			}
		}

		void	freeTree(node *root)
		{
			/* deletion using Preorder traversel */
			if (root)
			{
				if (root->left)
					freeTree(root->left);
				if (root->right)
					freeTree(root->right);

				_data_alloc.destroy(root->data);
				_data_alloc.deallocate(root->data,1);
				_node_alloc.destroy(root);
				_node_alloc.deallocate(root,1);
			}
			return ;
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
			std::cout<<root->data->first << " " << root->data->second << " " ;
			std::cout << root->color<<"\n";
			printTreeUtil(root->left, space);
		}

		void printTree()
		{
			printTreeUtil(this->root, 0);
		}

		node*		getRoot() const {return this->root;}
		const node*	getRootConst()  const {return this->root;}

	
		private :
			allocator_type	_data_alloc;
			allocator_node	_node_alloc;
			key_compare		comp;
			node *root;
			Iter *it;

};

#endif