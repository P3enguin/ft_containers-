/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybensell <ybensell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 11:52:40 by ybensell          #+#    #+#             */
/*   Updated: 2022/10/23 16:39:31 by ybensell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



// #include "Vector.hpp"
#include "map.hpp"

int main()
{	

		ft::map<int,char> a;
		// ft::map<int,char> b;
		// ft::map<int,char>::iterator it;

		// a.insert(ft::pair<int,char>(1,'a'));
		// a.insert(ft::pair<int,char>(2,'b'));
		// a.insert(ft::pair<int,char>(1,'a'));
		// a.insert(ft::pair<int,char>(3,'b'));
		// a.insert(ft::pair<int,char>(4,'a'));
		// a.insert(ft::pair<int,char>(5,'b'));
		// a.insert(ft::pair<int,char>(6,'a'));
		// a.insert(ft::pair<int,char>(7,'b'));
		// a[7] = 'h';
		// std::cout << " size " << a.getTree().getSize() << std::endl;

		// // b.insert(a.begin(),a.end());
		// // // a.insert(ft::pair<int,char>(8,'a'));
		// // a.insert(it,ft::make_pair(8,'c'));
		// // a.insert(ft::pair<int,char>(9,'b'));
		// // b.insert(a.begin(),a.end());
		// // b.erase(4);
		// // it = b.begin();
		// // it++;
		// // b.erase(it,b.end());

		// // // b.getTree().printTree();
		// a.getTree().printTree();
		// // a.clear();
		
		// std::cout << a.lower_bound(6)->first << std::endl;
		// std::cout << a.empty() << std::endl;

		for (int i = 0 ; i < 100000 ; i++)
    	{
        	a.insert(ft::make_pair(i,'a'));
     	}
		ft::map<int,char>::iterator it ;

		
		for ( it = a.begin() ; it !=  a.end() ;it++)
		{
			std::cout << "it " << it->first << std::endl;
			a.erase(it);	
		}
		
}