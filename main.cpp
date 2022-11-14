/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybensell <ybensell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 11:52:40 by ybensell          #+#    #+#             */
/*   Updated: 2022/11/14 17:37:43 by ybensell         ###   ########.fr       */
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

void   breakFunc()
{
    std::string h;
    while (1)
    {
        getline(std::cin,h);
        if (h.empty())
            break;
    }
}

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
    std::cout << "inserting 7 elements in map"  << std::endl;
    for (int i = 0 ; i <= 7 ; i++)
        map.insert(ft::make_pair(i,i));
    std::cout << "map size now " << map.size() << std::endl;
    std::cout << "map first and second elements : " <<std::endl;
    for ( it = map.begin() ; it != map.end() ; it++)
        std::cout << "first : "  << it->first << "   second : " << it->second << std::endl;

    breakFunc();
    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "Testing copy constructor and range iterator" << std::endl;
    ft::map<int,char> copyMap(map);
    ft::map<int,char> rangeMap(map.begin(),map.end());

    ft::map<int,char> assignMap;
    for (int i = 5 ; i < 55 ; i++)
        assignMap.insert(ft::make_pair(i,i));
    
    copyMap = assignMap;
    std::cout << "assignmap size now " << assignMap.size() << std::endl;
    std::cout << "copyMap size now " << copyMap.size() << std::endl;

	breakFunc();
    std::cout << "element of assignMap " << std::endl;
    for ( it = assignMap.begin() ; it != assignMap.end() ; it++)
        std::cout << "first : "  << it->first << "   second : " << it->second << std::endl;
	breakFunc();
    std::cout << "element of copyMap " << std::endl;
    for ( it = copyMap.begin() ; it != copyMap.end() ; it++)
        std::cout << "first : "  << it->first << "   second : " << it->second << std::endl;

    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "testing insert " << std::endl;

	breakFunc();
    std::cout << "inserting one element in map" << std::endl;
    std::cout << "size before insert : " << map.size() << std::endl;
    map.insert(map.begin(),ft::make_pair(7,'c'));
    std::cout << "size after insert : " << map.size() << std::endl;
	breakFunc();
    std::cout << "inserting range of element that already exists" << std::endl;
	breakFunc();
    std::cout << "size before insert : " << map.size() << std::endl;
    map.insert(map.begin(),map.end());
    std::cout << "size after insert : " << map.size() << std::endl;
	breakFunc();
    std::cout << "inserting a range of copyMap" << std::endl;
    std::cout << "size before insert : " << map.size() << std::endl;
    map.insert(copyMap.begin(),copyMap.end());
    std::cout << "size after insert : " << map.size() << std::endl;
	breakFunc();
    for ( it = map.begin() ; it != map.end() ; it++)
        std::cout << "first : "  << it->first << "   second : " << it->second << std::endl;
	breakFunc();
    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "erasing ..." << std::endl;
    for (int i = 0 ; i < 100 ; i++)
        map.erase(i);
    std::cout << "size now : " << map.size() << std::endl;
    if (map.empty())
        std::cout << "map empty now " << std::endl;
	breakFunc();
    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "inserting 100 element  " << std::endl;
    for (int i = 0 ; i < 100 ; i++)
        map.insert(ft::make_pair(i,i));
    std::cout << "size now : " << map.size() << std::endl;
    std::cout << "max size : " << map.max_size() << std::endl;
	breakFunc();
    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "Accessing element using [] operator : " << std::endl;
    std::cout << map[48] << std::endl;
    std::cout << map[49] << std::endl;
    std::cout << map[50] << std::endl;
    std::cout << map[65] << std::endl;
    std::cout << map[66] << std::endl;
    std::cout << map[67] << std::endl;
	breakFunc();
    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "inserting more 100 elements " << std::endl;
    std::cout << "inserting ..." << std::endl;
    for (int i = 100 ; i < 200 ; i++)
        map.insert(ft::make_pair(i,i));
	breakFunc();
    std::cout << "size now " << map.size() << std::endl;
    std::cout << "erasing only first 100 elements" << std::endl;
    for (int i = 0 ; i < 100 ;i++ )
        map.erase(i);
    std::cout << "erasing ... " << std::endl;
    std::cout << "size now " << map.size() << std::endl;
	breakFunc();
    std::cout << "---------------------------------------------------" << std::endl;
    ft::map<int,char> swapMap;

    for (int i = 0 ; i < 4 ; i++)
        swapMap.insert(ft::make_pair(i,i+46));
    std::cout << "exchanging content of map with swapMap" << std::endl;
    std::cout << "swapMap only has 3 elements" << std::endl;
    map.swap(swapMap);
    std::cout << "Size of the map now : " << map.size() <<  std::endl;
	breakFunc();
    std::cout << "Checking elements ..."  << std::endl;
    for (it = map.begin() ; it != map.end() ; it++ )
        std::cout << "it-> " << it->first << std::endl;
    std::cout << "swapMap size now :  " << swapMap.size() << std::endl;
    std::cout << "swapMap elements : " << std::endl;
    for (it = swapMap.begin() ; it != swapMap.end() ; it++ )
        std::cout << "it-> " << it->first << std::endl;
	breakFunc();
    std::cout << "---------------------------------------------------" << std::endl;
    
    std::cout << "Clearing elements of swapMap " << std::endl;
    swapMap.clear();
    std::cout << "clearing ... " << std::endl;
    std::cout << "size of swapMap now : " << swapMap.size() << std::endl;
	breakFunc();
    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "\\* Testing Find memeber function */" << std::endl;
    std::cout << "finding the element 2" << std::endl;
    it = map.find(2);
    std::cout << "element : " << it->first << std::endl;
	breakFunc();
    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "\\* Testing Count memeber function */" << std::endl;
    std::cout << "finding  many element that have 7" << std::endl;
    std::cout << "nbr of element : " << map.count(7) << std::endl;
    std::cout << "finding  many element that have 2" << std::endl;
    std::cout << "nbr of element : " << map.count(2) << std::endl;
	breakFunc();
    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "Testing lower upper and equal bound functions " << std::endl;
    std::cout << "lower bound of 1 : " << map.lower_bound(1)->first << std::endl;
    std::cout << "lowe bound of 2 : " << map.lower_bound(2)->first << std::endl;
    std::cout << "upper bound of 1 : " << map.upper_bound(1)->first << std::endl;
    std::cout << "upper bound of 2 : " << map.upper_bound(2)->first << std::endl;
    breakFunc();       
    std::cout << "equal range of 1 first elem : " << map.equal_range(1).first->first << std::endl;
    std::cout <<  "equal range of 1 second elem : " << map.equal_range(1).first->second << std::endl;
    std::cout <<  "equal range of 1 first elem : " << map.equal_range(2).first->first << std::endl;
    std::cout <<  "equal range of 1 second elem : " << map.equal_range(2).first->second << std::endl;
}

void vec_tests()
{
	ft::vector<int> vec;

	std::cout << "---------------------------------------------------" << std::endl;
	std::cout << "inserting 10 elements in vec " << std::endl;
	for (int i = 0 ; i < 10 ; i++)
		vec.push_back(i);
	std::cout << "size : " << vec.size() << "     capacity : " << vec.capacity() << std::endl;
	breakFunc();
	std::cout << "---------------------------------------------------" << std::endl;
	std::cout << "constructing new vector using copy  constructor " << std::endl;
	breakFunc();
	std::cout << "constructing ..." << std::endl;
	ft::vector<int> Copyvec(vec);
	std::cout << "size of copyvec: " << Copyvec.size() << "     capacity : " << Copyvec.capacity() << std::endl;
	breakFunc();
	std::cout << "testing if the two vector are equals or not " << std::endl;
	if (Copyvec == vec)
		std::cout << "the two vec are equals" << std::endl;
	else
		std::cout << "the two vectors are not equal" << std::endl;
	breakFunc();
	std::cout << "---------------------------------------------------" << std::endl;
	std::cout << "constructing new vector using assignment operator " << std::endl;
	breakFunc();
	ft::vector<int> Assignvec;
	Assignvec = vec;
	std::cout << "size of assignvec: " << Assignvec.size() << "     capacity : " << Assignvec.capacity() << std::endl;
	breakFunc();
	std::cout << "---------------------------------------------------" << std::endl;
	std::cout << "constructing a vector using range of iterators, 5 elements from vec" << std::endl;
	ft::vector<int> iterVec(vec.begin(),vec.begin() + 5);
	std::cout << "size of iterVec: " << iterVec.size() << "     capacity : " << iterVec.capacity() << std::endl;
	std::cout << "---------------------------------------------------" << std::endl;
	breakFunc();
	std::cout << "testing normal iterators " << std::endl;
	breakFunc();
	ft::vector<int>::iterator it;
	it = vec.begin();
	std::cout << "iterating through the vector and checking elements " << std::endl;
	while (it != vec.end())
	{
		std::cout << "["  << *it << "]" ;
		it++;
	}
	std::cout << std::endl;
	std::cout << "---------------------------------------------------" << std::endl;
	breakFunc();
	std::cout << "testing reverse iterator ... " << std::endl;
	breakFunc();
	ft::vector<int>::reverse_iterator ir;
	for (ir = vec.rbegin() ; ir != vec.rend() ; ir++)
		std::cout << "["  << *ir << "]" ;
	std::cout << std::endl;
	std::cout << "---------------------------------------------------" << std::endl;
	breakFunc();
	std::cout << "resizing vec with a size of 5" << std::endl;
	breakFunc();
	vec.resize(5);
	std::cout << "size : " << vec.size() << "     capacity : " << vec.capacity() << std::endl;
	std::cout << "reserving a capacity of 20 to vec" << std::endl;
	vec.reserve(20);
	std::cout << "size : " << vec.size() << "     capacity : " << vec.capacity() << std::endl;
	std::cout << "---------------------------------------------------" << std::endl;
	breakFunc();
	std::cout << "testing element access operators " << std::endl;
	breakFunc();
	std::cout << "getting element at index 2 []" << std::endl;
	std::cout << "vec[5] : " << vec[2] << std::endl;
	std::cout << "---------------------------------------------------" << std::endl;
	breakFunc();
	std::cout << "getting element at index 4 using at" << std::endl;
	std::cout << "vec at 4 : " << vec.at(4) << std::endl;
	breakFunc();
	std::cout << "getting an element out of range " << std::endl;
	try {
		std::cout << "at(100)" << vec.at(100) << std::endl;
	} 
	catch (std::out_of_range &e)
	{
		std::cout << "error : " << e.what() << std::endl;
	}
	std::cout << "---------------------------------------------------" << std::endl;
	breakFunc();
	std::cout << "testing front  function " << std::endl;
	std::cout << "front : " << vec.front() << std::endl;
	breakFunc();
	std::cout << "testing back  function " << std::endl;
	std::cout << "back : " << vec.back() << std::endl;
	std::cout << "---------------------------------------------------" << std::endl;
	breakFunc();
	std::cout <<  "Its time to test assign insert "<< std::endl;
	breakFunc();
	std::cout << "assigning 5 elements index 5 to 10 " <<std::endl;
	vec.assign(Assignvec.begin() + 5 , Assignvec.begin() + 10);
	for (it  = vec.begin() ; it != vec.end() ;  it++){
		std::cout << "["  << *it << "]" ;
	}
	std::cout << std::endl;
	std::cout << "size : " << vec.size() << "     capacity : " << vec.capacity() << std::endl;
	std::cout << "---------------------------------------------------" << std::endl;
	breakFunc();
	std::cout << "assigning 10 elements of value 1337 to the Assignvec " << std::endl;
	Assignvec.assign(10,1337);
	for (it  = Assignvec.begin() ; it != Assignvec.end() ;it++){
		std::cout << "["  << *it << "]" ;
	}
	std::cout << std::endl;
	std::cout << "size : " << Assignvec.size() << "     capacity : " << Assignvec.capacity() 
			<< std::endl;
	std::cout << "---------------------------------------------------" << std::endl;
	breakFunc();
	std::cout << "pushing back elements to vec" << std::endl;
	breakFunc();
	std::cout << "pushing 80 90 and 100 to the end << std::endl" << std::endl;
	vec.push_back(80);
	vec.push_back(90);
	vec.push_back(100);
	for (it  = vec.begin() ; it != vec.end() ;it++){
		std::cout << "["  << *it << "]" ;
	}
	std::cout << std::endl;
	std::cout << "size : " << vec.size() << "     capacity : " << vec.capacity() << std::endl;
	breakFunc();
	std::cout << "poping the last two elements from vec " << std::endl;
	vec.pop_back();
	vec.pop_back();
	for (it  = vec.begin() ; it != vec.end() ;it++){
		std::cout << "["  << *it << "]" ;
	}
	std::cout << std::endl;
	std::cout << "size : " << vec.size() << "     capacity : " << vec.capacity() << std::endl;
	std::cout << "---------------------------------------------------" << std::endl;
	breakFunc();
	std::cout << "inserting at the begining of vec -1 " << std::endl;
	vec.insert(vec.begin(), -1);
	for (it  = vec.begin() ; it != vec.end() ;it++){
		std::cout << "["  << *it << "]" ;
	}
	std::cout << std::endl;
	std::cout << "size : " << vec.size() << "     capacity : " << vec.capacity() << std::endl;
	std::cout << "---------------------------------------------------" << std::endl;
	breakFunc();
	std::cout << "inserting at postion 3 , 5 elements of value : 42 " << std::endl;
	vec.insert(vec.begin(), 5 , 42);
	for (it  = vec.begin() ; it != vec.end() ;it++){
		std::cout << "["  << *it << "]" ;
	}
	std::cout << std::endl;
	std::cout << "size : " << vec.size() << "     capacity : " << vec.capacity() << std::endl;
	std::cout << "---------------------------------------------------" << std::endl;
	breakFunc();
	std::cout << "inserting at index 2 , 5 element from position 5 to 10 " << std::endl;
	vec.insert(vec.begin() + 2, vec.begin() + 5 , vec.begin() + 10);
	for (it  = vec.begin() ; it != vec.end() ;it++){
		std::cout << "["  << *it << "]" ;
	}
	std::cout << std::endl;
	std::cout << "size : " << vec.size() << "     capacity : " << vec.capacity() << std::endl;
	std::cout << "---------------------------------------------------" << std::endl;
	breakFunc();
	std::cout << "testing Erase function " << std::endl;
	breakFunc();
	std::cout << "erasing the first element from vec" << std::endl;
	vec.erase(vec.begin());
	for (it  = vec.begin() ; it != vec.end() ;it++){
		std::cout << "["  << *it << "]" ;
	}
	std::cout << std::endl;
	std::cout << "size : " << vec.size() << "     capacity : " << vec.capacity() << std::endl;
	std::cout << "---------------------------------------------------" << std::endl;
	breakFunc();
	std::cout << "erasng from index 4 to index 10 " << std::endl;
	vec.erase(vec.begin() + 4,vec.begin() + 10 );
	for (it  = vec.begin() ; it != vec.end() ;it++){
		std::cout << "["  << *it << "]" ;
	}
	std::cout << std::endl;
	std::cout << "size : " << vec.size() << "     capacity : " << vec.capacity() << std::endl;
	std::cout << "---------------------------------------------------" << std::endl;
	breakFunc();
	std::cout << "testing swap  " << std::endl;

	ft::vector<int> swapVec;
	vec.swap(swapVec);
	breakFunc();
	std::cout << "vec size : " << vec.size() << "     capacity : " << vec.capacity() << std::endl;
	std::cout << "swapVec size : " << swapVec.size() << "     capacity : " << swapVec.capacity() << std::endl;
	breakFunc();
	std::cout << "testing element in swapVec" << std::endl;
	breakFunc();
	for (it  = vec.begin() ; it != vec.end() ;it++){
		std::cout << "["  << *it << "]" ;
	}
	std::cout << std::endl;
	breakFunc();
	std::cout << "clearing all element of swapVec and vec " << std::endl;
	swapVec.clear();
	vec.clear();
	std::cout << "vec size : " << vec.size() << "     capacity : " << vec.capacity() << std::endl;
	std::cout << "swapVec size : " << swapVec.size() << "     capacity : " << swapVec.capacity() << std::endl;
}

void stack_tests()
{
    ft::stack<int> st;
    ft::stack<int> sp;

    st.push(1);
    st.push(2);
    st.push(3);

	std::cout << "testing if the stack is empty " << std::endl;
	if (sp.empty())
		std::cout << "sp is empty" << std::endl;
	else
		std::cout << "sp is not empty" << std::endl;

	breakFunc();
	std::cout << "testing if the two stacks are equals or not " << std::endl;
	breakFunc();
    if (st == sp)
        std::cout << "the two stacks are equals " << std::endl;
    else if (st != sp )
        std::cout << "the two stacks are not equals " << std::endl;
	breakFunc();
	std::cout << "testing who is bigger " << std::endl;
	breakFunc();
    if (st > sp)
        std::cout << "st bigger tham sp " << std::endl;
    else if (st < sp )
        std::cout << "st small than sp " << std::endl;
	
	sp.push(1);
    sp.push(2);
    sp.push(3);

	breakFunc();
	std::cout << "top of sp : " << sp.top() << std::endl;
	std::cout << "top of st : " << sp.top() << std::endl;

	breakFunc();
	std::cout << "testing if sp empty " << std::endl;
	breakFunc();
	if (sp.empty())
		std::cout << "sp is empty" << std::endl;
	else
		std::cout << "sp is not empty" << std::endl;
	breakFunc();
	std::cout << "testing if the two stacks are equals or not " << std::endl;
	breakFunc();
    if (st == sp)
        std::cout << "the two stacks are equals " << std::endl;
    else if (st != sp )
        std::cout << "the two stacks are not equals " << std::endl;
	breakFunc();
	std::cout << "testing if one stack is bigger than the other " << std::endl;
	breakFunc();
    if (st > sp)
        std::cout << "st bigger tham sp " << std::endl;
    else if (st < sp )
        std::cout << "st small than sp " << std::endl;
}

void set_tests()
{
	ft::set<int> set;
	ft::set<int>::iterator it;
	ft::set<int>::reverse_iterator ir;
    std::cout << "inserting 7 elements in set"  << std::endl;
    for (int i = 0 ; i <= 7 ; i++)
        set.insert(i);
    std::cout << "set size now " << set.size() << std::endl;
    std::cout << "set first and second elements : " <<std::endl;
    for ( it = set.begin() ; it != set.end() ; it++)
        std::cout << "first : "  << *it  << std::endl;

    breakFunc();
    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "Testing copy constructor and range iterator" << std::endl;
    ft::set<int> copySet(set);
    ft::set<int> rangeSet(set.begin(),set.end());

    ft::set<int> assignSet;
    for (int i = 5 ; i < 55 ; i++)
        assignSet.insert(i);
    
    copySet = assignSet;
    std::cout << "assignset size now " << assignSet.size() << std::endl;
    std::cout << "copySet size now " << copySet.size() << std::endl;

	breakFunc();
    std::cout << "element of assignSet " << std::endl;
    for ( it = assignSet.begin() ; it != assignSet.end() ; it++)
        std::cout << "first : "  << *it <<  std::endl;
	breakFunc();
    std::cout << "element of copySet " << std::endl;
    for ( it = copySet.begin() ; it != copySet.end() ; it++)
        std::cout << "first : "  << *it <<  std::endl;

    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "testing insert " << std::endl;

	breakFunc();
    std::cout << "inserting one element in set" << std::endl;
    std::cout << "size before insert : " << set.size() << std::endl;
    set.insert(set.begin(),7);
    std::cout << "size after insert : " << set.size() << std::endl;
	breakFunc();
    std::cout << "inserting range of element that already exists" << std::endl;
	breakFunc();
    std::cout << "size before insert : " << set.size() << std::endl;
    set.insert(set.begin(),set.end());
    std::cout << "size after insert : " << set.size() << std::endl;
	breakFunc();
    std::cout << "inserting a range of copySet" << std::endl;
    std::cout << "size before insert : " << set.size() << std::endl;
    set.insert(copySet.begin(),copySet.end());
    std::cout << "size after insert : " << set.size() << std::endl;
	breakFunc();
    for ( it = set.begin() ; it != set.end() ; it++)
        std::cout << "first : "  << *it <<  std::endl;
	breakFunc();
    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "erasing ..." << std::endl;
    for (int i = 0 ; i < 100 ; i++)
        set.erase(i);
    std::cout << "size now : " << set.size() << std::endl;
    if (set.empty())
        std::cout << "set empty now " << std::endl;
	breakFunc();
    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "inserting 100 element  " << std::endl;
    for (int i = 0 ; i < 100 ; i++)
        set.insert(i);
    std::cout << "size now : " << set.size() << std::endl;
    std::cout << "max size : " << set.max_size() << std::endl;
	breakFunc();
    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "inserting more 100 elements " << std::endl;
    std::cout << "inserting ..." << std::endl;
    for (int i = 100 ; i < 200 ; i++)
        set.insert(i);
	breakFunc();
    std::cout << "size now " << set.size() << std::endl;
    std::cout << "erasing only first 100 elements" << std::endl;
    for (int i = 0 ; i < 100 ;i++ )
        set.erase(i);
    std::cout << "erasing ... " << std::endl;
    std::cout << "size now " << set.size() << std::endl;
	breakFunc();
    std::cout << "---------------------------------------------------" << std::endl;
    ft::set<int> swapSet;

    for (int i = 0 ; i < 4 ; i++)
        swapSet.insert(i);
    std::cout << "exchanging content of set with swapSet" << std::endl;
    std::cout << "swapSet only has 3 elements" << std::endl;
    set.swap(swapSet);
    std::cout << "Size of the set now : " << set.size() <<  std::endl;
	breakFunc();
    std::cout << "Checking elements ..."  << std::endl;
    for (it = set.begin() ; it != set.end() ; it++ )
        std::cout << "it-> " << *it << std::endl;
    std::cout << "swapSet size now :  " << swapSet.size() << std::endl;
    std::cout << "swapSet elements : " << std::endl;
    for (it = swapSet.begin() ; it != swapSet.end() ; it++ )
        std::cout << "it-> " << *it << std::endl;
	breakFunc();
    std::cout << "---------------------------------------------------" << std::endl;
    
    std::cout << "Clearing elements of swapSet " << std::endl;
    swapSet.clear();
    std::cout << "clearing ... " << std::endl;
    std::cout << "size of swapSet now : " << swapSet.size() << std::endl;
	breakFunc();
    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "\\* Testing Find memeber function */" << std::endl;
    std::cout << "finding the element 2" << std::endl;
    it = set.find(2);
    std::cout << "element : " << *it << std::endl;
	breakFunc();
    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "\\* Testing Count memeber function */" << std::endl;
    std::cout << "finding  many element that have 7" << std::endl;
    std::cout << "nbr of element : " << set.count(7) << std::endl;
    std::cout << "finding  many element that have 2" << std::endl;
    std::cout << "nbr of element : " << set.count(2) << std::endl;
	breakFunc();
    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "Testing lower upper and equal bound functions " << std::endl;
    std::cout << "lower bound of 1 : " << *set.lower_bound(1) << std::endl;
    std::cout << "lowe bound of 2 : " << *set.lower_bound(2) << std::endl;
    std::cout << "upper bound of 1 : " << *set.upper_bound(1) << std::endl;
    std::cout << "upper bound of 2 : " << *set.upper_bound(2) << std::endl;
    breakFunc();       
    std::cout << "equal range of 1 first elem : " << *set.equal_range(1).first << std::endl;
    std::cout <<  "equal range of 1 second elem : " << *set.equal_range(1).second<< std::endl;
    std::cout <<  "equal range of 1 first elem : " << *set.equal_range(2).first  << std::endl;
    std::cout <<  "equal range of 1 second elem : " << *set.equal_range(2).second << std::endl;
}
