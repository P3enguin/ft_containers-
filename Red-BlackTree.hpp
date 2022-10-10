/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Red-BlackTree.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybensell <ybensell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:57:14 by ybensell          #+#    #+#             */
/*   Updated: 2022/10/10 15:47:46 by ybensell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <unistd.h>
# define RED   1
# define BLACK 0
# define LEFT  0
# define RIGHT 1
# define COUNT 10

template<class T>
struct s_tree{
	struct s_tree *parent;
	struct s_tree *left;
	struct s_tree *right;
	T data;
	bool color;
} ; 

template <class T>
class RBtree 
{
	s_tree<T> *ROOT;
	public :
		RBtree() { this->root = NULL; } 

		s_tree<T>* createNode(T data)
		{
			s_tree<T> *n;

			n = new s_tree<T>;
			n->parent = NULL;
			n->left = NULL;
			n->right = NULL;
			n->data = data;
			n->color = RED;
			return n;
		}

		s_tree<T>*	search(T data)
		{
			s_tree<T> *t;

			t = this->root;
			while (t)
			{
				if (t->data == data)
					return t;
				else if (t->data  < data)
					t = t->right;
				else if (t->data > data)
					t = t->left;
			}
			return NULL;
		}

		void addToTree(s_tree<T> *n)
		{
			s_tree<T> *tmp;

			tmp = root;
			if (!tmp)
			{
				n->color = BLACK;
				this->root = n;
				return ;
			}
			while (tmp)
			{
				if (n->data < tmp->data)
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
		}

		void leftRotation(s_tree<T> *p)
		{
			s_tree<T> *tmp;

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

		void	rightRotation(s_tree<T> *p)
		{
			s_tree<T> *tmp;

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

		void insert(T data)
		{
			s_tree<T> *n = createNode(data);
			addToTree(n);

			s_tree<T> *u;   // uncle 
			s_tree<T> *p;   // parent of the current node
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

		s_tree<T> *	predeccessor(T data)
		{
			s_tree<T> *t,*pred;

			// /* predeccessor  of a node is the node with the greatest key 
			// 	smaller than the key of the current n in Its left subtree

			// 	- if the node doesnt have a left subtree , the successor is
			// 		one of Its ancestor
			t = this->root;
			pred = NULL;
			while (t)
			{
				if (t->data < data)
				{
					pred = t;
					t = t->right;
				}
				else if (t->data > data)
					t = t->left;
				else if (t->data == data)
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

		s_tree<T>*	successor(T data)
		{
			s_tree<T> *t,*succ;

			/* Successor of a node is the node with the smallest key 
				greater than the key of the current n in Its right subtree

				- if the node doesnt have a right subtree , the successor is
					one of Its ancestor 

			*/
			t = this->root;
			succ = NULL;
			while (t)
			{
				if (t->data < data)
					t = t->right;
				else if (t->data > data)
				{
					succ = t;
					t = t->left;
				}
				else if (t->data == data)
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


		void	rebalance(s_tree<T> *n,s_tree<T> *u)
		{
			/* 
				n : the node to be deleted 
				u : the node that will replace the deleted node
				s : sibling of the node
				c : close nephew 
				d : distant nephew
			*/

			s_tree<T> *tmp = n; /* saving the deleted node poTer to free at the end */
			s_tree<T> *p = n->parent;

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
				s_tree<T> *s,*d,*c;
			
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
				delete tmp;
				tmp = NULL;
			}
			return ;
		}

		/* basic  binary tree deletion */ 
		void	removeNode(s_tree<T> *n)
		{
			s_tree<T> *t;
			
			/*	node is  the root */
			if (n == this->root)
			{
				this->root = NULL;
				delete n;
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
				t = pREDecessor(n->data);
				if (!t)
					t = successor(n->data);
				n->data = t->data;
				rebalance(t,NULL);
			}
		}

		void	Delete(T data)
		{
			s_tree<T> *tmp;
			tmp = this->root;
			while (tmp)
			{
				if (tmp->data == data)
				{
					removeNode(tmp);
					return ;
				}
				else if (tmp->data > data)
					tmp = tmp->left;
				else
					tmp = tmp->right;
			}
		}

		void	freeTree(s_tree<T> *root)
		{
			if (root)
			{
				if (root->left)
					freeTree(root->left);
				if (root->right)
					freeTree(root->right);
				delete root;
			}
			return ;
		}

		void printTreeUtil(s_tree<T> *root, int space)
		{
		
			if (root == NULL)
				return;
		
			space += COUNT;
		
			printTreeUtil(root->right, space);
		
			std::cout<<std::endl;
			for (int i = COUNT; i < space; i++)
				std::cout<<" ";
			std::cout<<root->data << " " ;
			std::cout << root->color<<"\n";
			printTreeUtil(root->left, space);
		}

		void printTree()
		{
			printTreeUtil(this->root, 0);
		}

		s_tree<T>*	getRoot() {return this->root;}

		private :
			s_tree<T> *root;

};