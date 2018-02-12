//
// Created by Максимов Алексей on 28.01.18.
//

#include <boost/python.hpp>
#include "Unit.hpp"

BOOST_PYTHON_MODULE(units_ext)
{
    boost::python::def("convert", unit::convert);
}