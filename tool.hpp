/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybensell <ybensell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 11:38:02 by ybensell          #+#    #+#             */
/*   Updated: 2022/07/27 17:49:52 by ybensell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <iostream>
#include <string>
#include <typeinfo>

/********************* is_integral ********************************/
template<typename T >
struct is_integral
{  
    static const bool value = false;
};

template<>
struct is_integral<bool>
{  typedef bool hh;
    static const hh value = true;
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

template<bool B, typename T>
struct enable_if { };

template<typename T>
struct enable_if<true, T> { typedef T type; };


/***************************************************************/
// template<typename T>
// struct const_integral {

//         static bool _vall ;
//         const_integral() 
//         {
            
//             if (typeid(T) == typeid(int) 
//                 || typeid(T) == typeid(bool)
//                 || typeid(T) == typeid(char)
//                 || typeid(T) == typeid(char16_t)
//                 || typeid(T) == typeid(char32_t)
//                 || typeid(T) == typeid(wchar_t)
//                 || typeid(T) == typeid(signed char)
//                 || typeid(T) == typeid(short int)
//                 || typeid(T) == typeid(long int)
//                 || typeid(T) == typeid(long long int)
//                 || typeid(T) == typeid(unsigned char)
//                 || typeid(T) == typeid(unsigned short int)
//                 || typeid(T) == typeid(unsigned int)
//                 || typeid(T) == typeid(unsigned long int)
//                 || typeid(T) == typeid(unsigned long long int))
//             {
//                 _vall = true;      
//             }
//             else
//                 _vall = false;
//         }; 
//        bool getvall() { return _vall; };
            
// };