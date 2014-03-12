#ifndef REGISTER_HPP_INCLUDED
#define REGISTER_HPP_INCLUDED

// Headers
#include <string>
#include <cstddef>


class Register
{
public:

    Register ( );

    Register ( const std::string &s );
    Register ( std::string &&s );
    Register ( const std::size_t &s );
    Register ( std::size_t &&s );

    ~Register ( ) = default;

    std::size_t       getNumber ( ) const;
    std::string       &getString ( );
    const std::string &getString ( ) const;
    Register &operator= ( const std::size_t n );
    Register &operator= ( const std::string &s );
    Register &operator= ( const Register &r );

    // Indicer requirements, operator< is lexicographic
    friend bool operator< ( const Register &lhs, const Register &rhs );
    Register operator++ ( int );
    Register &operator-- ( );

    // Arithmetic
    Register &operator+= ( const Register &r );
    Register &operator-= ( const Register &r );
    Register &operator*= ( const Register &r );
    Register &operator/= ( const Register &r );
    Register &operator%= ( const Register &r );

    void swap ( Register &r );
    friend std::ostream &operator<< ( std::ostream &os, const Register &r );

private:

    inline void updateNumber ( ) const;
    inline void updateString ( ) const;

    enum class Last
    {
        String,
        Number,
        Both
    }
    mutable m_last;

    mutable std::string m_string;
    mutable std::size_t m_number;

};

#endif // REGISTER_HPP_INCLUDED
