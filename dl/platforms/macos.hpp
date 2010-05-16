//========================================================================
/**@file	dl/platforms/macos.hpp
 * @author	Ekinox <ekinox1995@gmail.com>
 * @version	1.0
 * @date
 * 	Created:	sam. 15 mai 2010 20:22:14 CEST \n
 * 	Last Update:	sam. 15 mai 2010 20:22:14 CEST
 */
/*------------------------------------------------------------------------
 * Description:	This file offers a Mac OS option for loading dynamic libraries.
 * 
 *------------------------------------------------------------------------
 * TODO:
 *========================================================================
 */

#ifndef _DL_PLATFORMS_MACOS___HPP__
#define _DL_PLATFORMS_MACOS___HPP__

#include <dlfcn.h>

namespace dl {

    /**
     * @brief The class implementing dynamic library support for Mac OS
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
		lib_ = dlopen(("lib" + fileName + ".dylib").c_str(), RTLD_LAZY);
	    } else {
		lib_ = dlopen(fileName.c_str(), RTLD_LAZY);
	    }
	    if (lib_ == NULL) {
		throw LoadingLibException() << file_name(fileName) << additional_infos(dlerror());
	    }
	}

	~DynLib()
	{
	    if (dlclose(lib_) != 0) {
		throw FreeingLibException() << additional_infos(dlerror());
	    }
	}

	template <typename SymbolType> SymbolType loadSymbol(const std::string & symbolName)
	{
	    char * error;
	    dlerror();
	    union { SymbolType symbol, void * returned } alias;
	    alias.returned = dlsym(lib_, symbolName.c_str());
	    if ((error = dlerror()) != NULL) {
		throw LoadingSymbolException() << symbol_name(symbolName) << additional_infos(error);
	    }
	    return alias.symbol;
	}

    private:
	void * lib_;
    };

}

#endif // _DL_PLATFORMS_MACOS___HPP__
