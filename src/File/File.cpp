#include <File.hpp>


File::File ( const std::string &filename )
:
    m_content ( ttl::file2str ( filename ) ) // Simply read the contents of a file into working memory.
{}


File::File ( std::string &&filename )
:
    m_content ( ttl::file2str ( filename ) ) // Simply read the contents of a file into working memory.
{}


void File::read ( const std::string &filename )
{
    // Simply read the contents of a file into working memory.
    m_content = ttl::file2str ( filename );
}


void File::read ( std::string &&filename)
{
    // Simply read the contents of a file into working memory.
    m_content = ttl::file2str ( filename );
}


void File::parseAllIncludeStatements ( )
{
    // Look for a sequence akin to "#cxy <filename>", copy filename.
    boost::regex cxy_include("#cxy *?<(.+?)>");

    // Define the range of operation [begin, end), entire string.
    std::string::const_iterator
        begin = m_content.cbegin(),
        end = m_content.cend();
    boost::match_results<decltype(begin)> what;
    while (boost::regex_search(begin, end, what, cxy_include))
    {
        m_content.replace
        (
            std::distance(m_content.cbegin(), what[0].first), // Start or erasing.
            std::distance(what[0].first, what[0].second), // Length of erasing.
            ttl::file2str(what[1]) // What[1] contains the first capture - the file name.
        );
        // Because of the replace, we need to re-specify the start and ends.
        // The original iterators may be invalidated.
        begin = m_content.cbegin(); end = m_content.cend();
    }
}


std::string File::getDelim ( std::string::const_iterator begin, std::string::const_iterator end ) const
{
    boost::regex delim ( R"(#cxy.*?(\(|\[)(\w*?)=)" );
    boost::match_results<std::string::const_iterator> what;
    if ( boost::regex_search ( begin, end, what, delim ) )
        return what[2];
    return "";
}


Nest File::getMostNestedCxy (  ) const
{
    Nest position;
    std::size_t cxy_pos = m_content.rfind ( "#cxy" );
    position.begin = m_content.cbegin() + cxy_pos;

    if ( position.begin == m_content.cend() || cxy_pos == std::string::npos)
        return Nest ( { m_content.cend(), m_content.cend(), m_content.cend(), m_content.cend() } );

    position.end = m_content.cend ( );
    std::string delimiter = getDelim ( position.begin, position.end );

    boost::regex delim( R"(#cxy.*?\()" + delimiter + R"((=)(.*?)(=))" + delimiter + R"(\))" );
    boost::match_results<std::string::const_iterator> what;
    std::string::const_iterator beg = position.begin, end = m_content.cend();
    if ( boost::regex_search (beg , end, what, delim ) )
    {
        position.end = what[0].second;
        position.start = what[2].first;
        position.stop = what[2].second;
        return position;
    }
    else
    {
        throw std::logic_error
        (
            "When scanning for delimiters of #cxy (),\
            no matching closing delimiter was actually found.\
            The delimiter scanned for is: " + delimiter
        );
    }
}


void File::eraseNest ( const Nest &nest )
{
    m_content.erase
    (
        std::distance ( m_content.cbegin(), nest.begin ),
        std::distance ( m_content.cbegin(), nest.end ) - std::distance ( m_content.cbegin(), nest.begin )
    );
}


std::string &File::getString ( )
{
    return m_content;
}

const std::string &File::getString ( ) const
{
    return m_content;
}


std::ostream &operator<< ( std::ostream &os, const File &file )
{
    os << file.m_content;
    return os;
}
