#ifndef VERBOSE_HPP_INCLUDED
#define VERBOSE_HPP_INCLUDED

#include <iostream>


class Verbose
{
public:

    void set(bool state);


    template <typename Type>
    Verbose &operator << (Type &&argument)
    {
        if (m_state)
            std::cout << std::forward<Type>(argument); return *this;
    }


private:

    bool m_state = false;
};

#endif // VERBOSE_HPP_INCLUDED
