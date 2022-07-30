/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybensell <ybensell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 11:38:02 by ybensell          #+#    #+#             */
/*   Updated: 2022/07/30 16:31:51 by ybensell         ###   ########.fr       */
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


/*********************************************************************************/

/***************************** random_access_iterator ***************************/
template <typename P>
class iter
{
    public :
        
        
        typedef P        value_type;
        typedef P*       pointer;
        typedef P&       reference;

        typedef typename std::ptrdiff_t difference_type;
        typedef typename std::random_access_iterator_tag iterator_category;            

        iter () {};
        iter (P * ptr) {_iter = ptr;}
        iter (const iter<P> &obj) {_iter = obj._iter; };

        iter<P> &operator = (const iter<P> &obj){ _iter = obj._iter ; return *this ;}; //

        bool operator ==(const iter<P> &obj) const
        {
            if (_iter == obj.getIter())
                return true;
            else
                return false;
        };
        bool operator !=(const iter<P> &obj) const
        {
            if (_iter != obj.getIter())
                return true;
            return false;
        };
        
        bool operator <(const iter<P> &obj)  const
        {
            if (_iter < obj.getIter())
                return true;
            return false;
        };   
        bool operator <=(const iter<P> &obj) const
        {
            if (_iter <= obj.getIter())
                return true;
            return false;
        };   
        bool operator > (const iter<P> &obj) const
        {
            if (_iter > obj.getIter())
                return true;
            return false;
        };   
        bool operator >=(const iter<P> &obj) const
        {
            if (_iter >= obj.getIter())
                return true;
            return false;
        };

        iter<P>& operator +=(const difference_type &index) { _iter += index ; return *this; } ;
        iter<P>& operator -=(const difference_type &index) { _iter -= index ; return *this; } ; 

        iter<P>& operator ++() { _iter++ ; return *this;} ;
        iter<P>& operator --() { _iter-- ; return *this;} ;


        iter<P> operator ++(int) {
            iter<P> tmp = *this;
            _iter++;
            return tmp;
        };

        iter<P> operator --(int) {
            iter<P> tmp = *this;
            _iter--;
            return tmp;
        };

        iter<P> operator +(const difference_type &index) {
            iter<P> ret;

            ret._iter = _iter + index;
            return ret;
        };
        iter<P> operator -(const difference_type &index) {
            iter<P> ret;

            ret._iter = _iter - index;
            return ret;
        };
        
        difference_type operator -(const iter<P> &obj) { return (std::distance(obj.getIter(),this->_iter)) ;};

        P & operator *()       { return *_iter ;};
        P & operator *() const { return *_iter ;};
        P * operator ->()      { return *_iter ;};

        P * getIter() const {return _iter;};


    protected :
        P *_iter;
};    

/***************************** Reverse Iterator *********************************/

template <class Iterator> 
class reverse_iter : public iter<typename Iterator::value_type>
{
    public :
        typedef Iterator                                                iterator_type ;
        typedef typename iterator_traits<Iterator>::iterator_category   iterator_category;
        typedef typename iterator_traits<Iterator>::value_type          value_type;
        typedef typename iterator_traits<Iterator>::difference_type     difference_type;
        typedef typename iterator_traits<Iterator>::pointer             pointer;
        typedef typename iterator_traits<Iterator>::reference           reference;
        
        reverse_iter(){ };
       
        explicit reverse_iter (iterator_type it)
        {
            this->_iter = it.getIter();
            _base = this->_iter + 1;
        };
        
        // template <class Iter>
        // reverse_iter (const reverse_iter<Iter>& rev_it)
        // {
            
        // };
        
        reverse_iter<iterator_type>& operator +=(const difference_type &index) {  this->_iter -= index ; return *this; } ;
        reverse_iter<iterator_type>& operator -=(const difference_type &index) {  this->_iter += index ; return *this; } ; 

        reverse_iter<iterator_type>& operator ++() {  this->_iter-- ; return *this;} ;
        reverse_iter<iterator_type>& operator --() {  this->_iter++ ; return *this;} ;


        reverse_iter<iterator_type> operator ++(int) {
           reverse_iter<iterator_type> tmp = *this;
            this->_iter--;
            return tmp;
        };

        friend reverse_iter<Iterator> operator+ (
             typename reverse_iter<Iterator>::difference_type n,
             const reverse_iter<Iterator>& rev_it)
        {
            reverse_iter<iterator_type> ret;

            ret._iter =  rev_it - index;
            return ret;
        };

        reverse_iter<iterator_type> operator --(int) {
            reverse_iter<iterator_type> tmp = *this;
             this->_iter++;
            return tmp;
        };

        reverse_iter<iterator_type> operator +(const difference_type &index) {
            reverse_iter<iterator_type> ret;

            ret._iter =  this->_iter - index;
            return ret;
        };
        reverse_iter<iterator_type> operator -(const difference_type &index) {
            reverse_iter<iterator_type> ret;

            ret._iter =  this->_iter + index;
            return ret;
        };
        
        difference_type operator -(const reverse_iter<iterator_type> &obj) 
                    { return (std::distance(obj.getIter(),this->_iter)) ;};

        reference operator *()                          { return *(this->_iter);    };
        reference operator *()                  const   { return *(this->_iter);    };
        reference operator[](difference_type n) const   { return *(this->iter - n); };
        pointer   operator ->()                         { return *(this->_iter) ;     };

        iterator_type base() const { return this->_base;};

    private :
        value_type *_base;
};

    template <class Iterator>
    bool operator== (const reverse_iter<Iterator>& lhs,
                    const reverse_iter<Iterator>& rhs)
    {
        if (lhs.getIter() == rhs.getIter())
                return true;
            return false;
    };

    template <class Iterator>
    bool operator!= (const reverse_iter<Iterator>& lhs,
                    const reverse_iter<Iterator>& rhs)
    {
        if (lhs.getIter() != rhs.getIter())
                return true;
            return false;
    };

    template <class Iterator>
    bool operator<  (const reverse_iter<Iterator>& lhs,
                    const reverse_iter<Iterator>& rhs)
    {
        if (lhs.getIter() < rhs.getIter())
                return true;
            return false;
    };
   	
    template <class Iterator>
    bool operator<= (const reverse_iter<Iterator>& lhs,
                    const reverse_iter<Iterator>& rhs)
   	 {
        if (lhs.getIter() <= rhs.getIter())
                return true;
            return false;
    };

    template <class Iterator>
    bool operator>  (const reverse_iter<Iterator>& lhs,
                    const reverse_iter<Iterator>& rhs)
  	 {
        if (lhs.getIter() > rhs.getIter())
                return true;
            return false;
    };

    template <class Iterator>
    bool operator>= (const reverse_iter<Iterator>& lhs,
                    const reverse_iter<Iterator>& rhs)
     {
        if (lhs.getIter() >= rhs.getIter())
                return true;
            return false;
    };

    template <class Iterator>
    reverse_iter<Iterator> operator+ (
             typename reverse_iter<Iterator>::difference_type n,
             const reverse_iter<Iterator>& rev_it)
    {
        return rev_it._iter - n;
    };

    template <class Iterator>
    typename reverse_iter<Iterator>::difference_type operator- (
    const reverse_iter<Iterator>& lhs,
    const reverse_iter<Iterator>& rhs)
    {
        return lhs.base() - rhs.base();; 
    }