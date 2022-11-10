/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybensell <ybensell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:21:17 by ybensell          #+#    #+#             */
/*   Updated: 2022/11/10 14:57:51 by ybensell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.hpp"


int main()
{
    ft::stack<int> st;
    ft::stack<int> sp;
    sp.push(2);
    sp.push(2);
    sp.push(3);
    st.push(1);
    st.push(2);
    st.push(3);

    if (st == sp)
        std::cout << "the two stacks are equals " << std::endl;
    else if (st != sp )
        std::cout << "the two stacks are not equals " << std::endl;
    if (st > sp)
        std::cout << "st bigger tham sp " << std::endl;
    else if (st < sp )
        std::cout << "st small than sp " << std::endl;
           

    
}