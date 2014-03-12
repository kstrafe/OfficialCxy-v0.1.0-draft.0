#ifndef RULE_HPP_INCLUDED
#define RULE_HPP_INCLUDED

#include <vector>
#include <initializer_list>
#include "Token.hpp"



/**
    \brief Holds a compilation rule for a token.

    This class holds a single compilation rule
    for a single token.

    Say that an input token is "int".
    An int needs 2 variables:

    1. a rawly read string of numbers
    2. a unique register name.

    We can then create the following rule:

    Rule ( "int", {"raw integer", "unique register name"} );

    This defines the syntax of int.
    When we then parse our input tokens, we
    find this Rule, and we apply the
    above tests to it.

    1. Make sure the syntax is correct.
    2. Make sure the next 2 items are not seen as an instruction.
*/
class Rule
{
private:

    const std::string         m_token;
    const std::vector<Token>  m_syntax;

public:

    Rule ( const Token &token, std::initializer_list<std::string> &syntax );
    auto getSyntax ( ) const -> const decltype(m_syntax) &;
    bool operator< ( const Rule &rule );

};

#endif // RULE_HPP_INCLUDED
