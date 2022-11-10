/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybensell <ybensell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:39:07 by ybensell          #+#    #+#             */
/*   Updated: 2022/11/10 10:20:17 by ybensell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.hpp"
#include <iostream>
#include <map>

int main()
{
    ft::map<int,char> map;
    ft::map<int,char>::iterator it;
     ft::map<int,char>::reverse_iterator ir;
    for (int i = 0 ; i < 100 ; i++)
        map.insert(ft::make_pair(i,i));

    // ft::map<int,char> copyMap(map);
    // ft::map<int,char> rangeMap(map.begin(),map.end());


    // for (int i = 0 ; i < 100 ; i++)
    //     map.erase(i);
    
    // for ( it = copyMap.begin() ; it != copyMap.end() ; it++)
    //     std::cout << it->first << std::endl;

    // for ( it = rangeMap.begin() ; it != rangeMap.end() ; it++)
    //     std::cout << it->first << std::endl;

    if (!map.empty())
        std::cout << "map not empty" << std::endl;
    for (ir = map.rbegin() ; ir != map.rend(); ir++)
        std::cout << "ir value-> " << ir->first << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "erasing ..." << std::endl;
    for (int i = 0 ; i < 100 ; i++)
        map.erase(i);
    std::cout << "size now : " << map.size() << std::endl;
    if (map.empty())
        std::cout << "map empty now " << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "inserting 100 element  " << std::endl;
    for (int i = 0 ; i < 100 ; i++)
        map.insert(ft::make_pair(i,i));
    std::cout << "size now : " << map.size() << std::endl;
    std::cout << "max size : " << map.max_size() << std::endl;

    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "Accessing element using [] operator : " << std::endl;
    std::cout << map[48] << std::endl;
    std::cout << map[49] << std::endl;
    std::cout << map[50] << std::endl;
    std::cout << map[65] << std::endl;
    std::cout << map[66] << std::endl;
    std::cout << map[67] << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "inserting more 100 elements " << std::endl;
    std::cout << "inserting ..." << std::endl;
    for (int i = 100 ; i < 200 ; i++)
        map.insert(ft::make_pair(i,i));
    std::cout << "size now " << map.size() << std::endl;
    std::cout << "erasing only first 100 elements" << std::endl;
    for (int i = 0 ; i < 100 ;i++ )
        map.erase(i);
    std::cout << "erasing ... " << std::endl;
    std::cout << "size now " << map.size() << std::endl;

    std::cout << "---------------------------------------------------" << std::endl;
    ft::map<int,char> swapMap;

    for (int i = 0 ; i < 3 ; i++)
        swapMap.insert(ft::make_pair(i,i+46));
    std::cout << "exchanging content of map with swapMap" << std::endl;
    std::cout << "swapMap only has 3 elements" << std::endl;
    map.swap(swapMap);
    std::cout << "Size of the map now : " << map.size() <<  std::endl;
    std::cout << "Checking elements ..."  << std::endl;
    if (map.getTree().firstElement() == NULL)
        std::cout << "nn "<< std::endl;
    for (it = map.begin() ; it != map.end() ; it++ )
        std::cout << "it-> " << it->first << std::endl;
    std::cout << "swapMap size now :  " << swapMap.size() << std::endl;
    std::cout << "swapMap elements : " << std::endl;
    for (it = swapMap.begin() ; it != swapMap.end() ; it++ )
        std::cout << "it-> " << it->first << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;
    
    std::cout << "Clearing elements of swapMap " << std::endl;
    swapMap.clear();
    std::cout << "clearing ... " << std::endl;
    std::cout << "size of swapMap now : " << swapMap.size() << std::endl;

    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "\\* Testing Find memeber function */" << std::endl;
    std::cout << "finding the element 2" << std::endl;
    it = map.find(2);
    std::cout << "element : " << it->first << std::endl;

    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "\\* Testing Count memeber function */" << std::endl;
    std::cout << "finding  many element that have 7" << std::endl;
    std::cout << "nbr of element : " << map.count(7) << std::endl;
    std::cout << "finding  many element that have 2" << std::endl;
    std::cout << "nbr of element : " << map.count(2) << std::endl;

    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "Testing lower upper and equal bound functions " << std::endl;
    std::cout << "lower bound of 1 : " << map.lower_bound(1)->first << std::endl;
    std::cout << "lowe bound of 2 : " << map.lower_bound(2)->first << std::endl;
    std::cout << "upper bound of 1 : " << map.upper_bound(1)->first << std::endl;
    std::cout << "upper bound of 2 : " << map.upper_bound(2)->first << std::endl;
           
    std::cout << "equal range of 1 first elem : " << map.equal_range(1).first->first << std::endl;
    std::cout <<  "equal range of 1 first elem : " << map.equal_range(1).first->second << std::endl;
    std::cout <<  "equal range of 1 first elem : " << map.equal_range(2).first->first << std::endl;
     std::cout <<  "equal range of 1 first elem : " << map.equal_range(2).first->second << std::endl;

    
}

