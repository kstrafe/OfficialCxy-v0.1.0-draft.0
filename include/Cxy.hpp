#ifndef CXY_HPP_INCLUDED
#define CXY_HPP_INCLUDED

#include "Token.hpp"
#include "Rule.hpp"
#include "Bxy.hpp"
#include <set>


class Cxy
{
public:

    void setTokens ( const std::vector<Token> &tokens );
    void setTokens ( std::vector<Token> &&tokens );
    Bxy translateToBxy ( const std::set<Rule> &rules ) const;

    /**
        \brief Interpreter of Cxy

        Takes an input and copies it into output.
    */
    std::string translate ( const std::string &input) const;

    /**
        \brief Interpreter of Cxy

        This takes an rvalue reference as input.
        It does thus not need to copy the input,
        so it is slightly faster.
    */
    std::string translate ( std::string &&input ) const;



private:

    std::vector<Token> m_tokens;

};

#endif // CXY_HPP_INCLUDED
