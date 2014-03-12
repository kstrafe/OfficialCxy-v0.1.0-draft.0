#ifndef NEST_HPP_INCLUDED
#define NEST_HPP_INCLUDED

#include <string>


struct Nest
{
    std::string::const_iterator
        begin, // The location at the # of cxy
            start, // Right after the delimiter (
            stop, // Right before the delimiter )
        end; // The location where the delimiter ends: "
};

#endif // NEST_HPP_INCLUDED
