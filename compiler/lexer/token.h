#ifndef RAVEN_LANG_TOKEN_H
#define RAVEN_LANG_TOKEN_H

#include "../../autoconf.h"

#include <string>
#if defined(HAVE_HEADER_ANY)
# include <any>
#elif defined(HAVE_HEADER_EXPERIMENTAL_ANY)
# include <experimental/any>
// Pulling in symbols into the std namespace like this is not really
// allowed. It's done for forward compatibility with the C++17 standard
namespace std
{
    using std::experimental::any;
    using std::experimental::any_cast;
    using std::experimental::bad_any_cast;
}
#elif defined(HAVE_HEADER_BOOST_ANY)
# include <boost/any.hpp>
// Pulling in symbols into the std namespace like this is not really
// allowed. It's done for forward compatibility with the C++17 standard
namespace std
{
    using boost::any;
    using boost::any_cast;
    using boost::bad_any_cast;
}
#else
# error No any header available
#endif

namespace compiler
{
    enum struct tokens : unsigned
    {
        // Literal tokens
        number,
        string,

        // Operator tokens
        assignment,                 //!< `=`
        assignment_add,             //!< `+=`
        assignment_subtract,        //!< `-=`
        assignment_multiply,        //!< `*=`
        assignment_divide,          //!< `/=`
        assignment_modulo,          //!< `%=`
        assignment_bit_or,          //!< `|=`
        assignment_bit_and,         //!< `&=`
        assignment_bit_shift_left,  //!< `<<=`
        assignment_bit_shift_right, //!< `>>=`
        left_parenthesis,           //!< `(`
        right_parenthesis,          //!< `)`
        left_square_brace,          //!< `[`
        right_square_brace,         //!< `]`
        left_curly_brace,           //!< `{`
        right_curly_brace,          //!< `}`
        dot,                        //!< `.`
        comma,                      //!< `,`
        colon,                      //!< `:`
        bit_xor,                    //!< `^`
        bit_and,                    //!< `&`
        bit_shift_left,             //!< `<<`
        bit_shift_right,            //!< `>>`
        logical_or,                 //!< `||`
        logical_and,                //!< `&&`
        logical_not,                //!< `!`
        equal,                      //!< `==`
        not_equal,                  //!< `!=`
        equal_less_than,            //!< `<=`
        equal_greater_than,         //!< `>=`
        less_than,                  //!< `<`
        greater_than,               //!< `>`
        approx_equal,               //!< `~=`
        approx_notequal,            //!< `!~=`
        plus,                       //!< `+`
        minus,                      //!< `-`
        star,                       //!< `*`
        percent,                    //!< `%`
        exponent,                   //!< `**`
        slash,                      //!< `/`
        pipe,                       //!< `|`
        tilde,                      //!< `~`
        range,                      //!< `...`
        assignment_bit_xor,         //!< `^=`

        // Keyword tokens
        // Note that these are prefixed with a `k_` because some keywords
        // are the same as C++ keywords. All keyword tokens are prefixed
        // for uniformity reasons.
        k_var,
        k_const,
        k_return,
        k_if,
        k_else,
        k_while,
        k_do,
        k_for,
        k_break,
        k_continue,
        k_switch,
        k_case,
        k_use,
        k_function,
        k_class,
        k_private,
        k_public,
        k_object,

        // Other tokens
        newline   ,     //!< Statement separator, ignored elsewhere
        semicolon,      //!< Statement separator
        end,            //!< End of the token-stream

        user_tokens = 1001  // Where user tokens begins
    };

    template<typename charT>
    class basic_token
    {
    public:
        ~basic_token()
        {}

        // Tokens can not be copied or moved
        basic_token(basic_token const&) = delete;
        basic_token(basic_token &&) = delete;
        basic_token& operator=(basic_token const&) = delete;
        basic_token& operator=(basic_token &&) = delete;

    private:
        std::string  filename_;     // Name of file token comes from
        unsigned int linenumber_;   // Line in file the token comes from
        std::any value;             // Token data
        tokens token_;              // Token
    };

    using token = basic_token<char>;
}

#endif //RAVEN_LANG_TOKEN_H
