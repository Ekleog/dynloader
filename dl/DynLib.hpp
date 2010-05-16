//========================================================================
/**@file	dl/DynLib.hpp
 * @author	Ekinox <ekinox1995@gmail.com>
 * @version	1.0
 * @date
 * 	Created:	sam. 15 mai 2010 19:11:02 CEST \n
 */
/*------------------------------------------------------------------------
 * Description:	This file provides the interface for managing dynamic libraries
 * (shared libraries).
 * 
 *------------------------------------------------------------------------
 * TODO:	Add support for more operating systems
 *========================================================================
 */

#ifndef _DL_DYNLIB_HPP__
#define _DL_DYNLIB_HPP__

#include <boost/exception/all.hpp>

namespace dl {

    typedef boost::error_info<struct tag_file_name, std::string>	file_name;
    typedef boost::error_info<struct tag_symbol_name, std::string>	symbol_name;
    typedef boost::error_info<struct tag_additional_infos, std::string>	additional_infos;

    struct Exception : virtual boost::exception, virtual std::exception { };

    struct LoadingException : virtual Exception { }
    struct FreeingException : virtual Exception { }

    struct LoadingLibException : virtual LoadingException { };
    struct FreeingLibException : virtual FreeingException { };
    struct LoadingSymbolException : virtual LoadingException { };

}

#include <boost/config.hpp>

#if BOOST_PLATFORM == "Win32"
#  include "platforms/win32.hpp"
#elif BOOST_PLATFORM == "linux"
#  include "platforms/linux.hpp"
#elif BOOST_PLATFORM == "Mac OS"
#  include "platforms/macos.hpp"
#else
#  error "Unknown platform"
#endif

#endif // _DL_DYNLIB_HPP__

