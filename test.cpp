//========================================================================
/**
 * @file	test.cpp
 * @author	Ekinox <ekinox1995@gmail.com>
 * @version	1.0
 * @date
 * 	Created:	lun. 17 mai 2010 11:49:42 CEST \n
 */
/*------------------------------------------------------------------------
 * Description:	The testing file for dynloader.
 * Note that it will require boost to be installed to work.
 * 
 *------------------------------------------------------------------------
 * TODO:	
 *========================================================================
 */

/*===========================================================================*/
/*===============================[ Includes ]================================*/
/*===========================================================================*/
#define BOOST_TEST_MODULE DynLib
#include <boost/test/unit_test.hpp>

#include "dl/DynLib.hpp"

#define RUN_TEST 1

#define TEST_LIB 1
#define LIB_NAME "test"
#define LIB_SUFFIXED false

#define TEST_FUNC 1
#define FUNC_NAME "plusOne"
#define FUNC_RET int
#define FUNC_PARAMS_TYPES int
#define FUNC_PARAMS 3
#define FUNC_RETURN 4

#define TEST_VAR 1
#define VAR_TYPE long
#define VAR_NAME "three"
#define VAR_VALUE 3

#define TEST_NONSYMB 1
#define NONSYMB_TYPE int *
#define NONSYMB_NAME "inexistantSymbol"

#define TEST_NONLIB 1
#define NONLIB_NAME "inexistantLibrary"
#define NONLIB_SUFFIXED true

/*===========================================================================*/
/*============================[ Testing DynLib ]=============================*/
/*===========================================================================*/

#if defined(RUN_TEST) && RUN_TEST == 1

#if defined(TEST_LIB) && TEST_LIB == 1

BOOST_AUTO_TEST_CASE(loadLibrary)
{
    dl::DynLib dl(LIB_NAME, not LIB_SUFFIXED);
}

#if defined(TEST_FUNC) && TEST_FUNC == 1
BOOST_AUTO_TEST_CASE(loadFunction)
{
    dl::DynLib dl(LIB_NAME, not LIB_SUFFIXED);
    FUNC_RET (*testFunction)(FUNC_PARAMS_TYPES) = dl.loadSymbol<FUNC_RET (*)(FUNC_PARAMS_TYPES)>(FUNC_NAME);
    BOOST_CHECK_EQUAL(testFunction(FUNC_PARAMS), FUNC_RETURN);
}
#endif // defined(TEST_FUNC) && TEST_FUNC == 1

#if defined(TEST_VAR) && TEST_VAR == 1
BOOST_AUTO_TEST_CASE(loadVar)
{
    dl::DynLib dl(LIB_NAME, not LIB_SUFFIXED);
    VAR_TYPE testVar = dl.loadSymbol<VAR_TYPE>(VAR_NAME);
    BOOST_CHECK_EQUAL(testVar, VAR_VALUE);
}
#endif // defined(TEST_VAR) && TEST_VAR == 1

#if defined(TEST_NONSYMB) && TEST_NONSYMB == 1
BOOST_AUTO_TEST_CASE(loadSymbError)
{
    dl::DynLib dl(LIB_NAME, not LIB_SUFFIXED);
    BOOST_CHECK_THROW(dl.loadSymbol<NONSYMB_TYPE>(NONSYMB_NAME), dl::LoadingSymbolException);
}
#endif // defined(TEST_NONSYMB) && TEST_NONSYMB == 1

#endif // defined(TEST_LIB) && TEST_LIB == 1

#if defined(TEST_NONLIB) && TEST_NONLIB == 1
BOOST_AUTO_TEST_CASE(loadLibError)
{
    BOOST_CHECK_THROW(dl::DynLib(NONLIB_NAME, not NONLIB_SUFFIXED), dl::LoadingLibException);
}
#endif // defined(TEST_NONLIB) && TEST_NONLIB == 1

#endif // defined(RUN_TEST) && RUN_TEST == 1

