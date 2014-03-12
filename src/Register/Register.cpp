// Headers
#include "Register.hpp"
#include <ostream>
#include <iostream>


Register::Register ( )
:
    m_last ( Last::Both ),
    m_string ( "0" ),
    m_number ( 0 )
{}


Register::Register ( const std::string &s )
:
    m_last ( Last::String ),
    m_string ( s )
{}


Register::Register ( std::string &&s )
:
    m_last ( Last::String ),
    m_string ( s )
{}


Register::Register ( const std::size_t &s )
:
    m_last ( Last::Number ),
    m_number ( s )
{}


Register::Register ( std::size_t &&s )
:
    m_last ( Last::Number ),
    m_number ( s )
{}


std::size_t Register::getNumber ( ) const
{
    if ( m_last == Last::String )
    {
        updateNumber ( );
    }
    return m_number;
}


std::string &Register::getString ( )
{
    if ( m_last == Last::Number )
    {
        updateString ( );
    }
    return m_string;
}


const std::string &Register::getString ( ) const
{
    if ( m_last == Last::Number )
    {
        updateString ( );
    }
    return m_string;
}


Register &Register::operator= ( std::size_t n )
{
    m_number = n;
    m_last = Last::Number;
    return *this;
}


Register &Register::operator= ( const std::string &s )
{
    m_string = s;
    m_last = Last::String;
    return *this;
}

Register &Register::operator= ( const Register &r )
{
    m_last = r.m_last;
    m_string = r.m_string;
    m_number = r.m_number;
    return *this;
}


bool operator< ( const Register &lhs, const Register &rhs )
{
    if ( lhs.m_last == Register::Last::Number )
    {
        lhs.updateString ( );
    }
    if ( rhs.m_last == Register::Last::Number )
    {
        rhs.updateString ( );
    }
    return lhs.m_string < rhs.m_string;
}


Register Register::operator++ ( int )
{
    Register tmp ( *this );
    if ( m_last == Last::String )
    {
        m_number = std::stoll ( m_string, nullptr, 0 );
    }
    ++m_number;
    m_last = Last::Number;
    return tmp;

}

Register &Register::operator-- ( )
{
    if ( m_last == Last::String )
    {
        m_number = std::stoll ( m_string, nullptr, 0 );
    }
    --m_number;
    m_last = Last::Number;
    return *this;
}


Register &Register::operator+= ( const Register &r )
{
    if ( m_last == Last::String )
        m_number = std::stoll ( m_string, nullptr, 0 );
    if ( r.m_last == Last::String )
        r.updateNumber();

    m_number += r.m_number;
    m_last = Last::Number;
}


Register &Register::operator-= ( const Register &r )
{
    if ( m_last == Last::String )
        m_number = std::stoll ( m_string, nullptr, 0 );
    if ( r.m_last == Last::String )
        r.updateNumber();

    m_number -= r.m_number;
    m_last = Last::Number;
}


Register &Register::operator*= ( const Register &r )
{
    if ( m_last == Last::String )
        m_number = std::stoll ( m_string, nullptr, 0 );
    if ( r.m_last == Last::String )
        r.updateNumber();

    m_number *= r.m_number;
    m_last = Last::Number;
}


Register &Register::operator/= ( const Register &r )
{
    if ( m_last == Last::String )
        m_number = std::stoll ( m_string, nullptr, 0 );
    if ( r.m_last == Last::String )
        r.updateNumber();

    m_number /= r.m_number;
    m_last = Last::Number;
}


Register &Register::operator%= ( const Register &r )
{
    if ( m_last == Last::String )
        m_number = std::stoll ( m_string, nullptr, 0 );
    if ( r.m_last == Last::String )
        r.updateNumber();

    m_number %= r.m_number;
    m_last = Last::Number;
}


void Register::swap ( Register &r )
{
    std::swap ( m_string, r.m_string );
    std::swap ( m_number, r.m_number );
    std::swap ( m_last, r.m_last );
}


std::ostream &operator<< ( std::ostream &os, const Register &r )
{
    if ( r.m_last == Register::Last::Number )
    {
        os << r.getNumber();
    }
    else
    {
        os << r.getString();
    }
    return os;
}


void Register::updateNumber ( ) const
{
    m_number = std::stoll ( m_string, nullptr, 0 );
    m_last = Last::Both;
}


void Register::updateString ( ) const
{
    m_string = std::to_string ( m_number );
    m_last = Last::Both;
}
