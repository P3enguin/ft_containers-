/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybensell <ybensell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 11:52:40 by ybensell          #+#    #+#             */
/*   Updated: 2022/10/21 14:44:42 by ybensell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.hpp"
#include <map>
#include <iostream>

// #include "Vector.hpp"
// #include "map.hpp"

int main()
{	

		ft::map<int,char> a;
		ft::map<int,char> b;
		ft::map<int,char>::iterator it;

		a.insert(ft::pair<int,char>(1,'a'));
		a.insert(ft::pair<int,char>(2,'b'));
		a.insert(ft::pair<int,char>(1,'a'));
		a.insert(ft::pair<int,char>(3,'b'));
		a.insert(ft::pair<int,char>(4,'a'));
		a.insert(ft::pair<int,char>(5,'b'));
		a.insert(ft::pair<int,char>(6,'a'));
		a.insert(ft::pair<int,char>(7,'b'));
		a[7] = 'h';
		std::cout << " size " << a.getTree().getSize() << std::endl;

		// b.insert(a.begin(),a.end());
		// // a.insert(ft::pair<int,char>(8,'a'));
		// a.insert(it,ft::make_pair(8,'c'));
		// a.insert(ft::pair<int,char>(9,'b'));
		// b.insert(a.begin(),a.end());
		// b.erase(4);
		// it = b.begin();
		// it++;
		// b.erase(it,b.end());

		// // b.getTree().printTree();
		a.getTree().printTree();
		// a.clear();
		
		std::cout << a.max_size() << std::endl;
		std::cout << a.empty() << std::endl;



		// it = a.begin();
		// while (it != a.end())
		// {
		// 	std::cout << it->first << std::endl;
		// 	it++;
		// }
		// ft::cout << (*it).first << std::endl;
		// const std::pair<int,char> hh(1,'a');
		// a.insert(hh);
		// a.insert(std::pair<int,char>(2,'a'));
		// a.insert(std::pair<int,char>(3,'a'));
		// 	a.insert(std::pair<int,char>(4,'a'));
		// a.insert(std::pair<int,char>(5,'a'));
		// 	a.insert(std::pair<int,char>(6,'a'));
		// a.insert(std::pair<int,char>(7,'a'));
		// 	a.insert(std::pair<int,char>(8,'a'));
		// a.insert(std::pair<int,char>(9,'a'));


		// while (1);
		// ft::map<int,char>::iterator it;

		// a.insert(ft::pair<int,char>(1,'a'));
		// it =  a.begin();

		//  std::cout << it->first << std::endl;
		
}