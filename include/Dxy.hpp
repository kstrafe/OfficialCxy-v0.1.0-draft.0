#ifndef DXY_HPP_INCLUDED
#define DXY_HPP_INCLUDED

#include <string>
#include <vector>
#include "Token.hpp"


/**
    \brief Defines a Dxy processor
    This processor processes a string that
    conforms with the Dxy data specification.

    Dxy specification: (regex (PERL): (")?(?(1)([^"]|""[^"])*"|\w+) )
    Everything is "tokenized",
    A few valid tokens (examples):
    token
    "stringtoken"
    "allowed with whitespace"
    "and of course a "" single quote"
    or_a_simple_43_non_whitespace_sequence

    Basically, anything that is inside a "" and alpha-numeric strings
    are seen as "tokens", outside of quotes, non-alpha-numerics are
    seen as separators.
*/
class Dxy
{
public:

    Dxy ( );
    Dxy ( const Dxy &dxy );
    Dxy ( Dxy &&dxy );
    Dxy ( const std::string &dxy_data );
    Dxy ( std::string &&dxy_data );

    ~Dxy ( );

    void        setData ( std::string &&dxy_data );
    void        setData ( const std::string &dxy_data );
    std::string &getData ( );
    const std::string &getData ( ) const;

    /**
        \brief Remove all comments from the data.
    */
    void uncomment ( );

    /**
        \brief Change all Dxy data into tokens.
    */
    std::vector < Token > tokenize ( ) const;

    friend std::ostream &operator<< (std::ostream &os, const Dxy &dxy);

private:

    std::string          m_dxy_data;

};

// We first need to uncomment dxy to turn it cxy.
/*
    The comment style is like in C++:
    2 forward slashes denote a line comment.
    These insert a new line once removed.

    forward-slash, star, content, start, forward-slash
    denotes a block-comment. These do not put new lines
    into the feed after they have been removed.

    Examples of transformations:
    I use * / for the C++ block ender, since doing otherwise
    will make this comment malfunction.

    "
        Data 34// This data is the data of data
    "
    ->
    "
        Data 34
    "

    And:

    "
        Data 34/* This data is the data of data* /
    "
    ->
    "
        Data 34
    "

    The reason why block comments are not new-lined is because
    it would require the uncommenter to count the amount of
    newlines in the block-quote, making the task more intensive
    and complicated.
    Therefore, it is up to the programmer to allocate
    the correct block quote, knowing that it will be completely
    removed without any insertions.
    Another reason is for the following scenario:

    "
        data/*
            string stands for an array of characters
        * /string
    "
    ->
    "
        datastring
    "

    This makes the block comment completely invisible in the result.
    The reason why the standard // does in fact emit a new line is:

    "
        "float data"//This is some data...
        "int data"//Well, this too!
    "
    ->
    "
        "float data""int data""

    Would be the result. The "" is parsed as a " inside strings, so
    the comment system must not mess this up!

    Comments inside literals are ignored.
*/


#endif // DXY_HPP_INCLUDED
