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

#pragma once         // for performance
#ifndef HEADER_MPROP // for compat
#define HEADER_MPROP

// ****************************************************************************
// Includes
// ****************************************************************************
#include "mprop_util.hpp"

#include <concepts>

namespace mprop
{
    /**
     * @brief Specifies the access type. Used as a template argument.
     */
    using mprop_util::AccessModifier_t;
    using mprop_util::Private;
    using mprop_util::Protected;
    using mprop_util::Public;

    template<
        AccessModifier_t GetterAccess,
        std::regular_invocable<> Getter_t,
        AccessModifier_t SetterAccess,
        class Setter_t>
    class property_proxy: public behaving_like_property<property_proxy>
    {

    };

}

#endif // HEADER_MPROP