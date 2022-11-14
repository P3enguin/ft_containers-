/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybensell <ybensell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 11:52:40 by ybensell          #+#    #+#             */
/*   Updated: 2022/11/14 11:17:57 by ybensell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.hpp"
#include "Vector.hpp"
#include "stack.hpp"
#include "set.hpp"

void map_tests();
void vec_tests();
void stack_tests();
void set_tests();

int main()
{	
	
	std::string line ;
	std::string a[5] = {"map","vector","stack","set"};
	void (*func_ptr[4])() = {map_tests,vec_tests,stack_tests,set_tests};
	std::cout << "hi and welcome to ypencel containers !!" << std::endl;
	std::cout << "please enter one of the following: vector, map, stack, set"<< std::endl;
	while (std::getline(std::cin,line))
	{
		std::cout << "please enter one of the following: vector, map, stack, set"<< std::endl;
		for (int i = 0 ; i != 4 ; i++)
		{
			if (a[i] == line)
				(*func_ptr[i])();
		}

	}

}
void map_tests()
{

	ft::map<int,char> map;
	ft::map<int,char>::iterator it;
	ft::map<int,char>::reverse_iterator ir;
    for (int i = 0 ; i <= 7 ; i++)
        map.insert(ft::make_pair(i,i));

    ft::map<int,char> copyMap(map);
    ft::map<int,char> rangeMap(map.begin(),map.end());

    ft::map<int,char> assignMap;
    for (int i = 5 ; i < 55 ; i++)
        assignMap.insert(ft::make_pair(i,i));
    
    assignMap = copyMap;

    for ( it = assignMap.begin() ; it != assignMap.end() ; it++)
        std::cout << it->first << std::endl;
    std::cout << "size now " << assignMap.size() << std::endl;
    std::cout << "size before " << map.size() << std::endl;
    map.insert(map.begin(),ft::make_pair(7,'c'));
    std::cout << "size after " << map.size() << std::endl;
    map.insert(map.begin(),map.end());

    for ( it = map.begin() ; it != map.end() ; it++)
        std::cout << it->first << std::endl;

    for (int i = 0 ; i < 100 ; i++)
        map.erase(i);
    
    for ( it = copyMap.begin() ; it != copyMap.end() ; it++)
        std::cout << it->first << std::endl;

    for ( it = rangeMap.begin() ; it != rangeMap.end() ; it++)
        std::cout << it->first << std::endl;

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

void vec_tests()
{
	ft::vector<int> vec;

	std::cout << "inserting 10 elements in vec " << std::endl;
	for (int i = 0 ; i < 10 ; i++)
		vec.push_back(i);
	std::cout << "size : " << vec.size() << "     capacity : " << vec.capacity() << std::endl;
	std::cout << "constructing new vector using copy  constructor " << std::endl;
	std::cout << "constructing ..." << std::endl;

	ft::vector<int> Copyvec(vec);
	std::cout << "testing whetere the two vector are equals or not " << std::endl;
	std::cout << "size of copyvec: " << Copyvec.size() << "     capacity : " << Copyvec.capacity() << std::endl;
	if (Copyvec == vec)
		std::cout << "the two vec are equals" << std::endl;
	else
		std::cout << "the two vectors are not equal" << std::endl;
	
	std::cout << "constructing new vector using assignment operator " << std::endl;
	ft::vector<int> Assignvec;
	Assignvec = vec;
	std::cout << "size of assignvec: " << Assignvec.size() << "     capacity : " << Assignvec.capacity() << std::endl;

	std::cout << "constructing a vector using range of iterators, 5 elements from vec" << std::endl;
	ft::vector<int> iterVec(vec.begin(),vec.begin() + 5);
	std::cout << "size of iterVec: " << iterVec.size() << "     capacity : " << iterVec.capacity() << std::endl;

	std::cout << "testing normal iterators " << std::endl;
	ft::vector<int>::iterator it;
	it = vec.begin();
	std::cout << "iterating through the vector and checking elements " << std::endl;
	while (it != vec.end())
	{
		std::cout << "["  << *it << "]" ;
		it++;
	}
	std::cout << std::endl;

	std::cout << "testing reverse iterator ... " << std::endl;
	ft::vector<int>::reverse_iterator ir;
	for (ir = vec.rbegin() ; ir != vec.rend() ; ir++)
		std::cout << "["  << *ir << "]" ;
	std::cout << std::endl;
	
	std::cout << "resizing vec with a size of 5" << std::endl;
	vec.resize(5);
	std::cout << "size : " << vec.size() << "     capacity : " << vec.capacity() << std::endl;
	std::cout << "reserving a capacity of 11 to vec" << std::endl;
	vec.reserve(11);
	std::cout << "size : " << vec.size() << "     capacity : " << vec.capacity() << std::endl;


	std::cout << "testing element access operators " << std::endl;
	std::cout << "getting element at index 5 []" << std::endl;
	std::cout << "vec[5] : " << vec[5] << std::endl;
	std::cout << "getting an element out of range " << std::endl;
	try {
		std::cout << "vec[100]" << vec[100] << std::endl;
	} 
	catch (std::out_of_range &e)
	{
		std::cout << "error : " << e.what() << std::endl;
	}

	
	std::cout << "getting element at index 4 using at" << std::endl;
	std::cout << "vec[5] : " << vec.at(4) << std::endl;
	std::cout << "getting an element out of range " << std::endl;
	try {
		std::cout << "at(100)" << vec.at(100) << std::endl;
	} 
	catch (std::out_of_range &e)
	{
		std::cout << "error : " << e.what() << std::endl;
	}

	std::cout << "testing front  function " << std::endl;
	std::cout << "front : " << vec.front() << std::endl;
	std::cout << "testing back  function " << std::endl;
	std::cout << "back : " << vec.back() << std::endl;

	std::cout <<  "Its time to test assign insert "<< std::endl;
	std::cout << "assigning 5 elements index 5 to 10 " <<std::endl;
	vec.assign(vec.begin() + 5 , vec.begin() + 10);
	for (it  = vec.begin() ; it != vec.end() ;  it++){
		std::cout << "["  << *it << "]" ;
	}
	std::cout << std::endl;
	std::cout << "size : " << vec.size() << "     capacity : " << vec.capacity() << std::endl;
	
	std::cout << "assigning 10 elements of value 1337 to the Assignvec " << std::endl;
	vec.assign(10,1337);
	for (it  = Assignvec.begin() ; it != Assignvec.end() ;it++){
		std::cout << "["  << *it << "]" ;
	}
	std::cout << std::endl;
	std::cout << "size : " << Assignvec.size() << "     capacity : " << Assignvec.capacity() 
			<< std::endl;
	
	std::cout << "pushing back elements to vec" << std::endl;
	std::cout << "pushing 80 90 and 100 to the end << std::endl" << std::endl;
	std::cout << std::endl;
	vec.push_back(80);
	vec.push_back(90);
	vec.push_back(100);
	for (it  = vec.begin() ; it != vec.end() ;it++){
		std::cout << "["  << *it << "]" ;
	}
	std::cout << std::endl;
	std::cout << "size : " << vec.size() << "     capacity : " << vec.capacity() << std::endl;

	std::cout << "poping the last two elements from vec " << std::endl;
	vec.pop_back();
	vec.pop_back();
	for (it  = vec.begin() ; it != vec.end() ;it++){
		std::cout << "["  << *it << "]" ;
	}
	std::cout << std::endl;
	std::cout << "size : " << vec.size() << "     capacity : " << vec.capacity() << std::endl;

	std::cout << "inserting at the begining of vec -1 " << std::endl;
	vec.insert(vec.begin(), -1);
	for (it  = vec.begin() ; it != vec.end() ;it++){
		std::cout << "["  << *it << "]" ;
	}
	std::cout << std::endl;
	std::cout << "size : " << vec.size() << "     capacity : " << vec.capacity() << std::endl;

	std::cout << "inserting at postion 3 , 5 elements of value : 42 " << std::endl;
	vec.insert(vec.begin(), 5 , 42);
	for (it  = vec.begin() ; it != vec.end() ;it++){
		std::cout << "["  << *it << "]" ;
	}
	std::cout << std::endl;
	std::cout << "size : " << vec.size() << "     capacity : " << vec.capacity() << std::endl;

	std::cout << "inserting at index 2 , 5 element from position 5 to 10 " << std::endl;
	vec.insert(vec.begin() + 2, vec.begin() + 5 , vec.begin() + 10);
	for (it  = vec.begin() ; it != vec.end() ;it++){
		std::cout << "["  << *it << "]" ;
	}
	std::cout << std::endl;
	std::cout << "size : " << vec.size() << "     capacity : " << vec.capacity() << std::endl;

	std::cout << "testing Erase function " << std::endl;
	std::cout << "erasing the first element from vec" << std::endl;
	vec.erase(vec.begin());
	for (it  = vec.begin() ; it != vec.end() ;it++){
		std::cout << "["  << *it << "]" ;
	}
	std::cout << std::endl;
	std::cout << "size : " << vec.size() << "     capacity : " << vec.capacity() << std::endl;
	
	std::cout << "erasng from index 4 to index 10 " << std::endl;
	vec.erase(vec.begin() + 4,vec.begin() + 10 );
	for (it  = vec.begin() ; it != vec.end() ;it++){
		std::cout << "["  << *it << "]" ;
	}
	std::cout << std::endl;
	std::cout << "size : " << vec.size() << "     capacity : " << vec.capacity() << std::endl;

	std::cout << "testing swap  " << std::endl;
	ft::vector<int> swapVec;
	vec.swap(swapVec);

	std::cout << "vec size : " << vec.size() << "     capacity : " << vec.capacity() << std::endl;
	std::cout << "swapVec size : " << swapVec.size() << "     capacity : " << swapVec.capacity() << std::endl;

	std::cout << "testing element in swapVec" << std::endl;
	for (it  = vec.begin() ; it != vec.end() ;it++){
		std::cout << "["  << *it << "]" ;
	}
	std::cout << std::endl;

	std::cout << "clearing all element of swapVec and vec " << std::endl;
	swapVec.clear();
	vec.clear();
	std::cout << "vec size : " << vec.size() << "     capacity : " << vec.capacity() << std::endl;
	std::cout << "swapVec size : " << swapVec.size() << "     capacity : " << swapVec.capacity() << std::endl;
}

void stack_tests()
{
	return ;

}
void set_tests()
{
	return ;
}
