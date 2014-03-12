#include "Token.hpp"
#include <boost/regex.hpp>


Token::Token ( )
{}


Token::Token ( const Token &token )
:
    m_token ( token.m_token )
{}


Token::Token ( Token &&token )
:
    m_token ( std::move ( token.m_token ) )
{}


Token::Token ( const std::string &value )
:
    m_token ( value )
{
}


Token::Token ( std::string &&value )
:
    m_token ( value )
{
}


Token::~Token ( )
{}


Token &Token::operator= ( const Token &token )
{
    m_token = token.m_token;
    return *this;
}


Token &Token::operator= ( Token &&token )
{
    m_token = token.m_token;
    return *this;
}


bool Token::isLiteral ( ) const
{
    if ( m_token.cbegin() != m_token.cend() )
    {
        if ( m_token.front() == '"' && m_token.back() == '"' )
        {
            return true;
        }
    }
    return false;
}


void Token::literate ( )
{
    m_token.pop_back();
    m_token.erase( m_token.begin() );
}


void Token::escape ( )
{
    std::string token;
    boost::regex regex (R"DELIM(((.*?")")|([^"]*?$))DELIM");
    std::string::const_iterator
        cbegin = m_token.cbegin(),
        cend = m_token.cend();
    boost::match_results<std::string::const_iterator> results;
    while ( boost::regex_search ( cbegin, cend, results, regex ) )
    {
        cbegin = results[0].second;
        token.append ( results[2] );
        token.append ( results[3] );
        if ( results[3].second == cbegin )
            break;
    }
    if ( token.size() > 0 )
        m_token = token;
}


std::string &Token::getString ( )
{
    return m_token;
}


const std::string &Token::getString ( ) const
{
    return m_token;
}


bool Token::operator== (const char *string) const
{
    return m_token == string;
}


bool operator< (const Token &lhs, const Token &rhs)
{
    return lhs.m_token < rhs.m_token;
}


std::ostream &operator<< ( std::ostream &os, const Token &token )
{
    os << token.getString();
    return os;
}



















