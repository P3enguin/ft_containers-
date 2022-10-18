/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybensell <ybensell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 11:52:40 by ybensell          #+#    #+#             */
/*   Updated: 2022/10/18 13:42:21 by ybensell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "map.hpp"
#include "Vector.hpp"
#include "map.hpp"

int main()
{	

		ft::map<int,char> a;
		const ft::pair<int,char> hh(1,'a');
		a.insert(hh);
		a.insert(ft::pair<int,char>(2,'a'));
		a.insert(ft::pair<int,char>(3,'a'));
		// while (1);
		// ft::map<int,char>::iterator it;

		// a.insert(ft::pair<int,char>(1,'a'));
		// it =  a.begin();

		//  std::cout << it->first << std::endl;
		
}