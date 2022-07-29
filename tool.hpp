/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybensell <ybensell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 11:38:02 by ybensell          #+#    #+#             */
/*   Updated: 2022/07/29 16:32:21 by ybensell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <iostream>
#include <string>
#include <typeinfo>

/***************************** iterator_traits **********************************/


template <class Iterator> 
class iterator_traits
{
    public :
        typedef typename Iterator::iterator_category iterator_category;
        typedef typename Iterator::value_type        value_type;
        typedef typename Iterator::difference_type   difference_type;
        typedef typename Iterator::pointer           pointer;
        typedef typename Iterator::reference         reference;
};

template <class T> 
class iterator_traits<T*>
{
    public :
        typedef std::random_access_iterator_tag iterator_category;
        typedef T                          value_type;
        typedef ptrdiff_t                  difference_type;
        typedef T*                         pointer;
        typedef T&                         reference;
};

template <class T>
class iterator_traits<const T*>
{
    public :
        typedef std::random_access_iterator_tag iterator_category;
        typedef T                          value_type;
        typedef ptrdiff_t                  difference_type;
        typedef const T*                   const_pointer;
        typedef const T&                   const_reference;
};



/***************************** is_integral **********************************/

/*  is_integral Implemented using the template specialization technique. 
for info : https://www.cprogramming.com/tutorial/template_specialization.html */

template<typename T >
struct is_integral
{  
    static const bool value = false;
};

template<>
struct is_integral<bool>
{
    static const bool value = true;
};

template<>
struct is_integral <char>
{  
    static const bool value = true;
};

template<>
struct is_integral < char16_t >
{  
    static const bool value = true;
};


template<>
struct is_integral<char32_t>
{  
    static const bool value = true;
};

template<>
struct is_integral<wchar_t>
{  
    static const bool value = true;
};

template<>
struct is_integral<signed char >
{  
    static const bool value = true;
};

template<>
struct is_integral<short int>
{  
    static const bool value = true;
};

template<>
struct is_integral<int>
{  
    static const bool value = true;
};


template<>
struct is_integral<long int>
{  
    static const bool value = true;
};

template<>
struct is_integral<long long int>
{  
    static const bool value = true;
};

template<>
struct is_integral< unsigned char>
{  
    static const bool value = true;
};

template<>
struct is_integral<unsigned short int>
{  
    static const bool value = true;
};

template<>
struct is_integral<unsigned int>
{  
    static const bool value = true;
};

template<>
struct is_integral<unsigned long int>
{  
    static const bool value = true;
};

template<>
struct is_integral<unsigned long long int>
{  
    static const bool value = true;
};



/********************* enable_if ********************************/

template<bool B, typename T >
struct enable_if { };

template<typename T>
struct enable_if<true, T> { typedef T type; };


/***************************************************************/
