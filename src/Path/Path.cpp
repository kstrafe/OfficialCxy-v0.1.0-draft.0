#include "Path.hpp"
#include <boost/regex.hpp>


const std::string Path::working_directory = boost::filesystem::current_path().generic_string() + "/";


Path::Path ( )
{}


Path::Path ( const Path &path )
:
    m_path ( path.m_path )
{}


Path::Path ( Path &&path )
:
    m_path ( std::move ( path.m_path ) )
{}


Path::Path ( const std::string &path )
:
    m_path ( path )
{}


Path::Path ( std::string &&path )
:
    m_path ( std::move ( path ) )
{}


bool Path::isRelative ( ) const
{
//    boost::regex regex ( R"<--->(^[A-Z]:/.*)<--->" );
//    return !boost::regex_match ( m_path.cbegin(), m_path.cend(), regex );
    return boost::filesystem::path(m_path).is_relative();
}


void Path::toAbsolutePath ( )
{
    if ( isRelative ( ) )
    {
        m_path = working_directory + m_path;
        boost::regex regex("/[^/]+?/\\.\\.");
        std::string empty("");
        while ( isRelative ( ) )
            m_path = boost::regex_replace(m_path, regex, empty);
     }
}


void Path::eraseCurrentDirectorySymbols ( )
{
    if (m_path.find("./") == 0)
    {
        do
        {
            m_path.erase(0, 2);
        }
        while (m_path.find("./") == 0);
    }
}


void Path::collapseHierarchy ( )
{
    typedef std::size_t Sti_t;
    Sti_t i = m_path.find("/../");
    while (i != std::string::npos)
    {
        // Find the prev folder:
        Sti_t ps = i - 1;
        while (true)
        {
            if (m_path[ps] == '/')
            {
                break;
            }
            --ps;
        }
        m_path.erase(ps, (i + 3) - ps);
        i = m_path.find("/../");
    }
}


Path Path::getPathRelativeTo ( const Path &base ) const
{
    boost::filesystem::path path ( m_path ), base_boost ( base.m_path );
    if (path.has_root_path())
    {
        if (path.root_path() != base_boost.root_path())
        {
            return path.generic_string();
        }
        else
        {
            Path tmpp ( path.relative_path().generic_string ( ) );
            return tmpp.getPathRelativeTo ( Path ( base_boost.relative_path().generic_string() ) );
        }
    }
    else
    {
        if (base_boost.has_root_path())
        {
            throw "Neither paths are rooted, can therefore not create a relative path.";
        }
        else
        {
            typedef boost::filesystem::path::const_iterator path_iterator;
            path_iterator path_it = path.begin();
            path_iterator base_it = base_boost.begin();
            while ( path_it != path.end() && base_it != base_boost.end() ) {
                if (*path_it != *base_it) break;
                ++path_it; ++base_it;
            }
            boost::filesystem::path result;
            for (; base_it != base_boost.end(); ++base_it)
            {
                result /= "..";
            }
            for (; path_it != path.end(); ++path_it)
            {
                result /= *path_it;
            }
            std::string res(result.generic_string());
            res.erase(0, 3);
            return res;
        }
    }
}


void Path::setString ( const std::string &path )
{
    m_path = path;
}


void Path::setString ( std::string &&path )
{
    m_path = std::move ( path );
}


std::string &Path::getString ( )
{
    return m_path;
}


const std::string &Path::getString ( ) const
{
    return m_path;
}


std::ostream &operator << (std::ostream &os, const Path &path)
{
    os << path.m_path;
    return os;
}


























































































