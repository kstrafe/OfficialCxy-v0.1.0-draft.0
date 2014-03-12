#ifndef BLOCKPRINTER_HPP_INCLUDED
#define BLOCKPRINTER_HPP_INCLUDED

#include <iostream>


class BlockPrinter
{
public:

    template <typename Type>
    BlockPrinter &operator<< ( Type &&argument )
    {
        (*stream)
            << "============================================================\n"
            << std::forward<Type>(argument)
            << "\n============================================================\n\n";
        return *this;
    }


    template <typename Type>
    BlockPrinter &operator<< (const Type &argument )
    {
        (*stream)
            << "============================================================\n"
            << argument
            << "\n============================================================\n\n";
        return *this;
    }


    std::ostream *stream = &std::cout;

};

#endif // BLOCKPRINTER_HPP_INCLUDED
