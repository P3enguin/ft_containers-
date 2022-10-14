/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybensell <ybensell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 11:52:40 by ybensell          #+#    #+#             */
/*   Updated: 2022/10/14 11:58:00 by ybensell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "map.hpp"
#include "Vector.hpp"
#include "map.hpp"

int main()
{	

		ft::map<int,char> a;
		a.insert(ft::pair<int,char>(1,'a'));
		a.insert(ft::pair<int,char>(2,'a'));
		a.insert(ft::pair<int,char>(3,'a'));

		// ft::map<int,char>::iterator it;

		// a.insert(ft::pair<int,char>(1,'a'));
		// it =  a.begin();

		//  std::cout << it->first << std::endl;
		
}