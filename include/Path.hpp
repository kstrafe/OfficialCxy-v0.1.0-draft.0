#ifndef PATH_HPP_INCLUDED
#define PATH_HPP_INCLUDED

#include <boost/filesystem.hpp>


/**
	\brief Path manipulator

	This class is designed to manage all path
	operations that boost does not provide.
	In addition, it's a clean and simple wrapper.
*/
class Path
{
public:

    Path ( );
    Path ( const Path &path );
    Path ( Path &&path );
    Path ( const std::string &path );
    Path ( std::string &&path );

    bool isRelative ( ) const;
    /**
    	\brief Makes a relative path absolute.
    */
    void toAbsolutePath ( ); // GetAbsolutePath

    /**
    	\brief Erases starting ./ "current path" symbols.

    	The paths here are already taken
    	in comparison to the current working directory.
    */
    void eraseCurrentDirectorySymbols ( ); // remove_all_dot_slash...

    /**
		\brief Collapses Z/X/../Y to Z/Y
    */
    void collapseHierarchy ( ); // get_non_dot_dot_path

    /**

    */
    //std::string get_absolute_file ( std::string &, std::string & ); // get_absolute_file

    /**
    	\brief Get the relative path to base.
    */
    Path getPathRelativeTo ( const Path &base ) const;

    void setString ( const std::string &path );
    void setString ( std::string &&path );
    std::string &getString ( );
    const std::string &getString ( ) const;

    friend std::ostream &operator << (std::ostream &os, const Path &path);

private:

	std::string m_path;
	static const std::string working_directory;

};


#endif // PATH_HPP_INCLUDED
