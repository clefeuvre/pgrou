//-----------------------------------------------------------------------------
//  Original Author: Gene Bushuyev
//  Copyright (C) 2011 GB Research, LLC
//  
//  Boost Software License - Version 1.0 - August 17th, 2003
//
//  Permission is hereby granted, free of charge, to any person or organization
//  obtaining a copy of the software and accompanying documentation covered by
//  this license (the "Software") to use, reproduce, display, distribute,
//  execute, and transmit the Software, and to prepare derivative works of the
//  Software, and to permit third-parties to whom the Software is furnished to
//  do so, all subject to the following:
//
//  The copyright notices in the Software and this entire statement, including
//  the above license grant, this restriction and the following disclaimer,
//  must be included in all copies of the Software, in whole or in part, and
//  all derivative works of the Software, unless such copies or derivative
//  works are solely in the form of machine-executable object code generated by
//  a source language processor.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
//  SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
//  FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
//  ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
//  DEALINGS IN THE SOFTWARE.
//-----------------------------------------------------------------------------

#ifndef AXE_EXPRESSION_H
#define AXE_EXPRESSION_H

#include "axe_result.h"
#include "axe_composite_function.h"
#include "axe_terminal_function.h"
#include "axe_extractor_function.h"
#include "axe_predicate_function.h"
#include "axe_numeric_function.h"

namespace axe {

    //-------------------------------------------------------------------------
    /// e_plus_t, e_minus_t, e_mult_t, e_div_t - common extractors
    /// operators used +=, -=, *=, /=
    //-------------------------------------------------------------------------

    template<class T> struct r_expression_t;
    
    //-------------------------------------------------------------------------
    /// e_plus_t - extractor class for operator +
    //-------------------------------------------------------------------------
    template<class T>
    struct e_plus_t
    {
        T& t1_;
        const T& t2_;

        e_plus_t(T& t1, const T& t2) : t1_(t1), t2_(t2) {}

        template<class It>
        void operator()(It i1, It i2)
        {
            t1_ += t2_;
        }
    };

    //-------------------------------------------------------------------------
    /// e_minus_t - extractor class for operator-
    //-------------------------------------------------------------------------
    template<class T>
    struct e_minus_t
    {
        T& t1_;
        const T& t2_;

        e_minus_t(T& t1, const T& t2) : t1_(t1), t2_(t2) {}

        template<class It>
        void operator()(It i1, It i2)
        {
            t1_ -= t2_;
        }
    };

    //-------------------------------------------------------------------------
    /// e_mult_t - extractor class for operator*
    //-------------------------------------------------------------------------
    template<class T>
    struct e_mult_t
    {
        T& t1_;
        const T& t2_;
        e_mult_t(T& t1, const T& t2) : t1_(t1), t2_(t2) {}

        template<class It>
        void operator()(It i1, It i2)
        {
            t1_ *= t2_;
        }
    };

    //-------------------------------------------------------------------------
    /// e_div_t - extractor class for operator/
    //-------------------------------------------------------------------------
    template<class T>
    struct e_div_t
    {
        T& t1_;
        const T& t2_;
        e_div_t(T& t1, const T& t2) : t1_(t1), t2_(t2) {}

        template<class It>
        void operator()(It i1, It i2)
        {
            t1_ /= t2_;
        }
    };

    //-------------------------------------------------------------------------
    /// r_group_t - rule for syntactical group (paranthesised expression)
    //-------------------------------------------------------------------------
    template<class T>
    struct r_group_t
    {
        T& value_;
        explicit r_group_t(T& value) : value_(value) {}

        template<class It>
        result<It> operator() (It i1, It i2)
        {
            return (r_lit('(') & r_expression_t<T>(value_) & ')')(i1, i2);
        }
    };

    //-------------------------------------------------------------------------
    /// r_factor_t - rule for factor
    //-------------------------------------------------------------------------
    template<class T>
    struct r_factor_t
    {
        T& value_;
        explicit r_factor_t(T& value) : value_(value) {}

        template<class It>
        result<It> operator() (It i1, It i2)
        {
            return (r_decimal(value_) | r_group_t<T>(value_))(i1, i2);
        }
    };

    //-------------------------------------------------------------------------
    /// r_term_t - rule for term
    //-------------------------------------------------------------------------
    template<class T>
    struct r_term_t
    {
        T& value_;
        explicit r_term_t(T& value) : value_(value) {}

        template<class It>
        result<It> operator() (It i1, It i2)
        {
            T t;
            return (r_factor_t<T>(value_) 
            & r_many((r_lit('*') & r_factor_t<T>(t)) >> e_mult_t<T>(value_, t)
            | (r_lit('/') & r_factor_t<T>(t)) >> e_div_t<T>(value_, t)
            ))(i1, i2);
        }
    };

    //-------------------------------------------------------------------------
    /// r_expression_t - rule for expression
    //-------------------------------------------------------------------------
    template<class T>
    struct r_expression_t
    {
        T& value_;
        explicit r_expression_t(T& value) : value_(value) {}

        template<class It>
        result<It> operator() (It i1, It i2)
        {
            T t = T();
            return 
            (r_term_t<T>(value_) 
                & r_many((r_lit('+') & r_term_t<T>(t)) >> e_plus_t<T>(value_, t)
                                | (r_lit('-') & r_term_t<T>(t)) >> e_plus_t<T>(value_, -t))
            )(i1, i2);
        }
    };

}
#endif
