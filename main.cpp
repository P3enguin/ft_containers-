/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybensell <ybensell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 11:52:40 by ybensell          #+#    #+#             */
/*   Updated: 2022/10/18 15:35:37 by ybensell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <map>
// #include "Vector.hpp"
// #include "map.hpp"

int main()
{	

		std::map<int,char> a;
		const std::pair<int,char> hh(1,'a');
		a.insert(hh);
		a.insert(std::pair<int,char>(2,'a'));
		a.insert(std::pair<int,char>(3,'a'));
			a.insert(std::pair<int,char>(4,'a'));
		a.insert(std::pair<int,char>(5,'a'));
			a.insert(std::pair<int,char>(6,'a'));
		a.insert(std::pair<int,char>(7,'a'));
			a.insert(std::pair<int,char>(8,'a'));
		a.insert(std::pair<int,char>(9,'a'));

		// while (1);
		// ft::map<int,char>::iterator it;

		// a.insert(ft::pair<int,char>(1,'a'));
		// it =  a.begin();

		//  std::cout << it->first << std::endl;
		
}