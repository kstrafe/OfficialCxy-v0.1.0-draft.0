#ifndef BXY_HPP_INCLUDED
#define BXY_HPP_INCLUDED

#include <string>


/**
    \brief Holds the executable Bxy

    Bxy holds executable bytecode, and
    can be applied to a string.
*/
class Bxy
{
public:

    /**
        Takes a string as input, translates it,
        and then returns it as output.

        This basically uses stored bytecode
        to translate a string.
    */
    std::string translate ( const std::string &input ) const;

private:


//    std::vector<Instruction>    m_instructions;
//    std::vector<Register>       m_registers;


};

#endif // BXY_HPP_INCLUDED
