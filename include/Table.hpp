#ifndef TABLE_HPP_INCLUDED
#define TABLE_HPP_INCLUDED

// Headers
#include <map>


/**
    \brief The Table Container

    This container functions exactly like a map, with the exception being
    that it can be pushed and popped like a normal vector.

    The compatible key type is one that has the following features:
    1. Default initialization is the zero-point (null); which is well-defined.
    2. Supports postfix ++.
    3. Supports prefix --.
    3. Supports operator<
*/
template <typename Key, typename Value>
class Table : public std::map<Key, Value>
{
public:

    using std::map<Key, Value>::map;

    /**

    */
    auto length ( ) const -> const Key &
    {
        return m_current_index;
    }


    void push_back ( )
    {
        this->insert(std::make_pair(m_current_index++, Value()));
    }

    void push_back ( const Value &register_arg )
    {
        this->insert(std::make_pair(m_current_index++, register_arg));
    }


    void push_back ( Value &&register_arg )
    {
        this->insert(std::make_pair(m_current_index++, register_arg));
    }


    void pop_back ( )
    {
        auto x = --m_current_index;
        if ( this->find(x) == this->end() )
            std::cout << "COULD NOT LOCATE THE INDEX!\n";
        this->erase(x);
    }


private:

    Key m_current_index;

};

#endif // TABLE_HPP_INCLUDED
