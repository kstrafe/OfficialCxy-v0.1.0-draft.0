#ifndef FILE_HPP_INCLUDED
#define FILE_HPP_INCLUDED

#include <boost/regex.hpp>
#include <utility>
#include <TTL/TTL.hpp>
#include "Nest.hpp"


/**
    \brief manages the file's nests.

    This class's sole purpose is to
    make sure that it emits the
    correct nested cxy iterators.

    It also needs to include all
    <> statements, which are
    nests as well.

*/
class File
{
public:

    File(const std::string &filename);
    File(std::string &&filename);

    void read(const std::string &filename);
    void read(std::string &&filename);

    void parseAllIncludeStatements();
    // Gets the delimiter for the nearest cxy sequence.
    std::string getDelim (std::string::const_iterator begin, std::string::const_iterator end) const;

    Nest getMostNestedCxy (  ) const;
    void eraseNest ( const Nest &nest );

    std::string &getString ( );
    const std::string &getString ( ) const;

    friend std::ostream &operator<< ( std::ostream &os, const File &file );

    // Starts reading from an iterator until it finds the first exit symbol
        // Find the deepest nest
        // Limitation:
        /*
            #cxy
            (
                // Nothing here except comments
                #cxy
                (
                    ... // <-- contains raw statements
                )
                #cxy
                (
                    #cxy
                    [
                        ... // <-- raw statements
                    ]
                    #cxy
                    (
                        ... // <-- raw statements
                        int eax
                        char ebx
                        asgn eax 32
                        cpy ebx eax // <Implicit> conversion from int to char (uint8_t? or int8_t)
                        cast char eax // <Explicit> conversion from int to char
                    )
                )
                #cxy
                (
                    ... // <-- raw
                )
                ... // <-- transformable
            )
            ... // <-- operating data

            // Define a language for cxy transformables:
            * No closing-p signs
            * Escape p-signs?
            * Tedious

            "We need to escape \)"
            We can string-encap it or char-encap it ')'
        */

private:

    std::string m_content; // The content we are operating on.

};


#endif // FILE_HPP_INCLUDED
