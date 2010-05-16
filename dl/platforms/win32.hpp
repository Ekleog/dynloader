//========================================================================
/**@file	dl/platforms/win32.hpp
 * @author	Ekinox <ekinox1995@gmail.com>
 * @version	1.0
 * @date
 * 	Created:	sam. 15 mai 2010 20:22:14 CEST \n
 * 	Last Update:	sam. 15 mai 2010 20:22:14 CEST
 */
/*------------------------------------------------------------------------
 * Description:	This file offers a Windows option for loading dynamic libraries.
 * 
 *------------------------------------------------------------------------
 * TODO:
 *========================================================================
 */

#ifndef _DL_PLATFORMS_WIN___HPP__
#define _DL_PLATFORMS_WIN___HPP__

#include <windows.h>

namespace dl {

    /**
     * @brief The class implementing dynamic library support for Window
     *
     * <p><b>Semantics</b><br>
     * <li> Entity semantics (=> reference semantics)
     * <li> Non-copyable
     *
     * @version 1.0
     * @author Ekinox <ekinox1995@gmail.com>
     */
    class DynLib : public boost::non_copyable
    {
    public:
	DynLib();

	DynLib(const std::string & fileName, bool autoAddSuffix = true)
	{
	    if (autoAddSuffix) {
		lib_ = LoadLibrary(static_cast <LPCTSTR>((fileName + ".dll").c_str()));
	    } else {
		lib_ = LoadLibrary(static_cast <LPCTSTR>(fileName.c_str()));
	    }
	    if (lib_ == NULL) {
		throw LoadingLibException() << file_name(fileName);
	    }
	}

	~DynLib()
	{
	    if (FreeLibrary(lib_) == 0) {
		throw FreeingLibException();
	    }
	}

	template <typename SymbolType> SymbolType loadSymbol(const std::string & symbolName)
	{
	    SymbolType symbol = static_cast <SymbolType>(GetProcAddress(lib_, static_cast <LPCSTR>(symbolName)));
	    if (symbol == NULL) {
		throw LoadingSymbolException() << symbol_name(symbolName);
	    }
	    return symbol;
	}

    private:
	HMODULE lib_;
    };

}

#endif // _DL_PLATFORMS_WIN___HPP__

