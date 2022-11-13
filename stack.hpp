/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybensell <ybensell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 12:54:18 by ybensell          #+#    #+#             */
/*   Updated: 2022/11/13 16:53:09 by ybensell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP
#include "tool.hpp"
#include "Vector.hpp"
#include <stack>
#include <deque>

namespace ft {

    template <class T, class Container = ft::vector<T> >
    class stack 
    {
        public :
            public:
            typedef Container                                container_type;
            typedef typename container_type::value_type      value_type;
            typedef typename container_type::reference       reference;
            typedef typename container_type::const_reference const_reference;
            typedef typename container_type::size_type       size_type;

            explicit stack (const container_type& ctnr = container_type())
            : c(ctnr) {}

            bool empty() const { return c.empty(); }
            size_type size() const {return c.size(); }
    
            value_type& top() { return c.back(); }
            const value_type& top() const {return c.back();} 
            
            void push (const value_type& val) {c.push_back(val);}
            void pop() { c.pop_back();}

            template<class T1,class C1>
            friend  bool operator== (const stack<T1,C1>& lhs, const stack<T1,C1>& rhs);

            template<class T1,class C1>
            friend  bool operator!= (const stack<T1,C1>& lhs, const stack<T1,C1>& rhs);

            template<class T1,class C1>
            friend  bool operator< (const stack<T1,C1>& lhs, const stack<T1,C1>& rhs);

            template<class T1,class C1>
            friend  bool operator> (const stack<T1,C1>& lhs, const stack<T1,C1>& rhs);

            template<class T1,class C1>
            friend  bool operator>= (const stack<T1,C1>& lhs, const stack<T1,C1>& rhs); 

            template<class T1,class C1>
            friend  bool operator<= (const stack<T1,C1>& lhs, const stack<T1,C1>& rhs);

        protected :
            container_type c;
    };

    template <class T, class Container>
    bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
    {
       return (lhs.c == rhs.c);
    }

    template <class T, class Container>
    bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
    {
        return !(lhs == rhs);
    }

    template <class T, class Container>
    bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
    {
        return (lhs.c < rhs.c);
    }

    template <class T, class Container>
    bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
    {
        return (!(rhs.c > lhs.c));
    }

    template <class T, class Container>
    bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
    {
        return ((lhs <= rhs));
    }
        
    template <class T, class Container>
    bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
    {
        return (!(lhs < rhs));
    }
}

#endif