/*
MIT License

Copyright (c) 2023 LMauricius

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma once // for performance
#ifndef HEADER_MPROP_UTIL // for compat
#define HEADER_MPROP_UTIL

namespace mprop_util
{

// ****************************************************************************
// Constants
// ****************************************************************************

    /**
     * @brief Specifies the access type. Used as a template argument.
     */
    enum AccessModifier_t {
        Public,
        Protected,
        Private
    };

// ****************************************************************************
// Concept helper classes
// ****************************************************************************

    /**
     * @brief A class that accesses parent's set method
     * @note Used to test if a child class has access to set
     * 
     * @tparam Parent_t 
     * @tparam V type of value to set
     */
    template<class Parent_t, class V>
    class accesses_parents_setter: public Parent_t
    {
        void proxy_set(V& v)
        {
            set(v);
        }
    };
    
    /**
     * @brief A class that accesses parent's get method
     * @note Used to test if a child class has access to get
     * 
     * @tparam Parent_t 
     */
    template<class Parent_t>
    class accesses_parents_getter: public Parent_t
    {
        void proxy_get()
        {
            get();
        }
    };

// ****************************************************************************
// Concepts
// ****************************************************************************

    /**
     * @brief Requires that Prop_t has a public set method 
     * 
     * @tparam Prop_t 
     * @tparam V 
     */
    template<class Prop_t, class V>
    concept has_public_setter = requires(Prop_t p, V v)
    {
        p.set(v);
    };

    /**
     * @brief Requires that Prop_t has a protected set method 
     * 
     * @tparam Prop_t 
     * @tparam V 
     */
    template<class Prop_t, class V>
    concept has_protected_setter = requires
    {
        typename accesses_parents_setter<Prop_t, V>;
    };


    /**
     * @brief Requires that Prop_t has a public get method 
     * 
     * @tparam Prop_t 
     */
    template<class Prop_t>
    concept has_public_getter = requires(Prop_t p)
    {
        p.get();
    };

    /**
     * @brief Requires that Prop_t has a protected get method 
     * 
     * @tparam Prop_t 
     */
    template<class Prop_t>
    concept has_protected_getter = requires
    {
        typename accesses_parents_getter<Prop_t>;
    };

    /**
     * @brief A class that enables implicit usage of get() and set() methods to any Child_t
     * that derives from getter_prop<Child_t> when used as a property
     * 
     * @tparam Child_t The child that will derive from it
     */
    template<class Child_t>
    class behaving_like_property 
    {
    public:
        using property_t = behaving_like_property<Child_t>;

    private:
        template<class V>
        requires !has_public_getter<Child_t> && !has_protected_getter<Child_t>
        inline operator V() const
        {
            return static_cast<const Child_t*>(this)->get();
        }

        template<class V>
        requires !has_public_setter<Child_t, V> && !has_protected_setter<Child_t, V>
        inline property_t& operator=(V v)
        {
            static_cast<const Child_t*>(this)->set(v);
        }

    protected:
        template<class V>
        requires !has_public_getter<Child_t> && has_protected_getter<Child_t>
        inline operator V() const
        {
            return static_cast<const Child_t*>(this)->get();
        }

        template<class V>
        requires !has_public_setter<Child_t, V> && has_protected_setter<Child_t, V>
        inline property_t& operator=(V v)
        {
            static_cast<const Child_t*>(this)->set(v);
        }

    public:
        template<class V>
        requires has_public_getter<Child_t>
        inline operator V() const
        {
            return static_cast<const Child_t*>(this)->get();
        }

        template<class V>
        requires has_public_setter<Child_t, V>
        inline property_t& operator=(V v)
        {
            static_cast<const Child_t*>(this)->set(v);
        }

    };
}

#endif // HEADER_MPROP_UTIL