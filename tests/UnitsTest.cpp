//
// Created by Максимов Алексей on 24.01.18.
//

#include "units/Unit.hpp"

#define BOOST_TEST_MODULE UnitTest
#include <boost/test/included/unit_test.hpp>
namespace utf = boost::unit_test;

BOOST_AUTO_TEST_CASE( Temperature_test_module, * utf::tolerance(0.00001) )
{
    BOOST_TEST( unit::convert( "Temperature", 10., "F", "C" ) == -12.2222 );
    BOOST_TEST( unit::convert( "Temperature", 10., "C", "F" ) == 50. );
    BOOST_TEST( unit::convert( "Temperature", 10., "C", "C" ) == 10. );
    BOOST_TEST( unit::convert( "Temperature", 10., "C", "K" ) == 283.15 );
}

BOOST_AUTO_TEST_CASE( Pressure_test_module, * utf::tolerance(0.00001) )
{

}

BOOST_AUTO_TEST_CASE( Length_test_module, * utf::tolerance(0.00001) )
{

}