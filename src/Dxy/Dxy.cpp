#include "Dxy.hpp"
#include <boost/regex.hpp>


Dxy::Dxy ( )
{}


Dxy::Dxy ( const Dxy &dxy )
:
    m_dxy_data  ( dxy.m_dxy_data )
{}


Dxy::Dxy (Dxy &&dxy )
:
    m_dxy_data ( std::move ( dxy.m_dxy_data ) )
{}


Dxy::Dxy ( const std::string &dxy_data )
:
    m_dxy_data    ( dxy_data )
{}


Dxy::Dxy ( std::string &&dxy_data )
:
    m_dxy_data    ( std::move ( dxy_data ) )
{}


Dxy::~Dxy ( )
{}


void Dxy::setData ( const std::string &dxy_data )
{
    m_dxy_data = dxy_data;
}


void Dxy::setData ( std::string &&dxy_data )
{
    m_dxy_data = std::move ( dxy_data );
}


std::string &Dxy::getData ( )
{
    return m_dxy_data;
}


const std::string &Dxy::getData ( ) const
{
    return m_dxy_data;
}


void Dxy::uncomment ( )
{
    std::string cxy_code;
    boost::regex tokens (R"((.*?)((//.*?)(\n)|(/\*.*?\*/)|("([^"]|"")*")|([^\w])))");
    std::string::const_iterator
        cbegin = m_dxy_data.cbegin(),
        cend = m_dxy_data.cend();
    boost::match_results<std::string::const_iterator> results;
    while ( boost::regex_search ( cbegin, cend, results, tokens ) )
    {
        cbegin = results[0].second;
        cxy_code.append ( results[1] );
        cxy_code.append ( results[4] );
        cxy_code.append ( results[6] );
        cxy_code.append ( results[8] );
    }

    m_dxy_data = cxy_code;
}


std::vector < Token > Dxy::tokenize ( ) const
{
    std::vector < Token > cxy_tokens;
    boost::regex tokens (R"((")?(?(1)([^"]|"")*"|\w+))");
    std::string::const_iterator beg = m_dxy_data.cbegin(), end = m_dxy_data.cend();
    boost::match_results<std::string::const_iterator> matches;
    while (boost::regex_search(beg, end, matches, tokens))
    {
        beg = matches[0].second;
        cxy_tokens.emplace_back ( std::move ( std::string ( matches[0] ) ) );
    }
    return cxy_tokens;
}


std::ostream &operator<< (std::ostream &os, const Dxy &dxy)
{
    os << dxy.m_dxy_data;
    return os;
}


























