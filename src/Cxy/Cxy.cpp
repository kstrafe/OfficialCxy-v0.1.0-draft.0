#include <iostream>
#include <map>
#include <boost/any.hpp>
#include <typeinfo>
#include "Cxy.hpp"
#include <string>
#include "Table.hpp"
#include "Register.hpp"


void Cxy::setTokens ( const std::vector<Token> &tokens )
{
    m_tokens = tokens;
}


void Cxy::setTokens ( std::vector<Token> &&tokens )
{
    m_tokens = tokens;
}


Bxy Cxy::translateToBxy ( const std::set<Rule> &rules ) const
{
    return Bxy ();
}


std::string Cxy::translate ( const std::string &input ) const
{
    std::string copy ( input );
    copy = translate ( std::move ( copy ) );
    return copy;
}


std::string Cxy::translate ( std::string &&input ) const
{
    struct Instruction
    {
        const uint8_t                                     opcode;
        const std::size_t                                 operand_count;
        const std::function< void ( ) >   function;
    };

    class ID
    {
        typedef uint8_t id_type_t;

    public:

        operator id_type_t ()
        {
            if ( std::numeric_limits<id_type_t>::max() == i )
                throw std::runtime_error("The internal ID generator has overflown because the native type that creates symbols has overflown.");
            return i++;
        }

    private:

        id_type_t i = 0;

    } uid;

    // Reference shortening.
    const decltype(m_tokens) &tks = m_tokens;

    // ii stands for "instruction index", this holds the instruction inder location.
    std::size_t                     ii ( 0 );

    // To make life easier, this Table is now a "Variable".
    typedef Table < Register, Register > Variable;

    // Each piece of data is identified by a set of symbols; a "token".
    std::map < Token, Variable >
        data;

    // The functions of the processor are described in this mapping.
    std::map<Token, Instruction>
    functions
    {
        {Token("var"), // Declares a new Table with 1 active element.
            {uid, 1, [&]()
                {
                    data[tks[ii + 1]] = Variable();
                    data[tks[ii + 1]].push_back();
                }
            }
        },
        {Token("push"), // Pushes the table by 1.
            {uid, 1, [&]()
                {
                    data[tks[ii + 1]].push_back();
                }
            }
        },
        {Token("pop"), // Pop from the table, 1.
            {uid, 1, [&]()
                {
                    data[tks[ii + 1]].pop_back();
                }
            }
        },
        {Token("asn"), // Assign to the back of the table array-wise.
            {uid, 2, [&]()
                {
                    auto tmp = data[tks[ii + 1]].length();
                    --tmp;
                    data[tks[ii + 1]][tmp]
                        = Register ( tks[ii + 2].getString() );
                }
            }
        },
        {Token("cpy"), // Copy the contents from one register to another
            {uid, 2, [&]()
                {
                    auto tmp = data[tks[ii + 1]].length();
                    --tmp;
                    auto tmp2 = data[tks[ii + 2]].length();
                    --tmp2;
                    data[tks[ii + 1]][tmp] = data[tks[ii + 2]][tmp2];
                }
            }
        },
        {Token("swap"), // Swap the contents from one register to another
            {uid, 2, [&]()
                {
                    auto tmp = data[tks[ii + 1]].length();
                    --tmp;
                    auto tmp2 = data[tks[ii + 2]].length();
                    --tmp2;
                    data[tks[ii + 1]][tmp].swap ( data[tks[ii + 2]][tmp2] );
                }
            }
        },
        {Token("show"), // Print the back of the table array to the screen.
            {uid, 1, [&]()
                {
                    auto tmp = data[tks[ii + 1]].length();
                    --tmp;
                    std::cout << data[tks[ii + 1]][tmp];
                }
            }
        },
        {Token("dump"), // Print all data assosciated with a variable.
            {uid, 1, [&]()
                {
                    std::cout
                        << "==============================\nBegin - Variable dump for \"" << tks[ii + 1] << "\"\n"
                        << "\tLength = " << data[tks[ii + 1]].length() << '\n'
                        << "\tSize = " << data[tks[ii + 1]].size() << "\n\n";
                    for (auto &var : data[tks[ii + 1]])
                    {
                        std::cout
                            << '\t' << var.first << " -> " << var.second << '\n';
                    }
                    std::cout << "End - Variable dump for \"" << tks[ii + 1] << "\"\n==============================\n";
                }
            }
        },
        {Token("inc"),
            {uid, 1, [&]()
                {
                    auto tmp = data[tks[ii + 1]].length();
                    --tmp;
                    (data[tks[ii + 1]][tmp])++;
                }
            }
        },
        {Token("dec"),
            {uid, 1, [&]()
                {
                    auto tmp = data[tks[ii + 1]].length();
                    --tmp;
                    --(data[tks[ii + 1]][tmp]);
                }
            }
        },
        {Token("add"),
            {uid, 2, [&]()
                {
                    auto tmp = data[tks[ii + 1]].length();
                    --tmp;
                    auto tmp2 = data[tks[ii + 2]].length();
                    --tmp2;
                    data[tks[ii + 1]][tmp] += data[tks[ii + 2]][tmp2];
                }
            }
        },
        {Token("sub"),
            {uid, 2, [&]()
                {
                    auto tmp = data[tks[ii + 1]].length();
                    --tmp;
                    auto tmp2 = data[tks[ii + 2]].length();
                    --tmp2;
                    data[tks[ii + 1]][tmp] -= data[tks[ii + 2]][tmp2];
                }
            }
        },
        {Token("mul"),
            {uid, 2, [&]()
                {
                    auto tmp = data[tks[ii + 1]].length();
                    --tmp;
                    auto tmp2 = data[tks[ii + 2]].length();
                    --tmp2;
                    data[tks[ii + 1]][tmp] *= data[tks[ii + 2]][tmp2];
                }
            }
        },
        {Token("div"),
            {uid, 2, [&]()
                {
                    auto tmp = data[tks[ii + 1]].length();
                    --tmp;
                    auto tmp2 = data[tks[ii + 2]].length();
                    --tmp2;
                    data[tks[ii + 1]][tmp] /= data[tks[ii + 2]][tmp2];
                }
            }
        },
        {Token("mod"),
            {uid, 2, [&]()
                {
                    auto tmp = data[tks[ii + 1]].length();
                    --tmp;
                    auto tmp2 = data[tks[ii + 2]].length();
                    --tmp2;
                    data[tks[ii + 1]][tmp] %= data[tks[ii + 2]][tmp2];
                }
            }
        },
    };

    // Processor Kernel
    for (; ii < tks.size(); ++ii)
    {
//        std::cout << "Processing: '" << tks[ii] << "'\n";

        auto function = functions.find(tks[ii]);
        if (function != functions.end())
        {
            function->second.function();
            ii += function->second.operand_count;
        }
        else
        {
            std::cout << "No handler for this opcode\n";
        }
    }
    return input;
}

















