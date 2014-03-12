#ifndef TOKEN_HPP_INCLUDED
#define TOKEN_HPP_INCLUDED

#include <string>


/**
    \brief Manipulator and holder class for Dxy tokens.

    Holds a Dxy-valid token.
    The token can be "literated" and
    escaped.

    Literation causes the start and
    ending " to be erased.

    Escaped strings change
    "" into a single ".
    """" become "" tho.
*/
class Token
{
public:

    Token ( );
    Token ( const Token &token );
    Token ( Token &&token );
    Token ( const std::string &value );
    Token ( std::string &&value );
    ~Token ( );


    Token &operator= ( const Token &token );
    Token &operator= ( Token &&token );

    bool isLiteral ( ) const;

    /**
        \brief Trim away the first " and ending ".

        Remove only 2 quotes, one at the beginning,
        the other at the end.
    */
    void literate ( );

    /**
        \brief Replace internal "" with ".

        Replaces all literals' containing "" with ".
    */
    void escape ( );

    std::string &getString ( );
    const std::string &getString ( ) const;

    bool operator== (const char *string) const;
    friend bool operator< (const Token &lhs, const Token &rhs);

    friend std::ostream &operator<< ( std::ostream &os, const Token &token );

private:

    std::string m_token;

};

#endif // TOKEN_HPP_INCLUDED
