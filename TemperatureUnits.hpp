//
// Created by Максимов Алексей on 24.01.18.
//

#pragma once

namespace unit
{
    namespace temperature
    {
        struct Celsius : public helper::Unit
        {
            Celsius() : helper::Unit( "C" ) {}
            FROMDEF{ return _val-273.15; }
            TODEF{ return _val+273.15; }
        };

        struct Fahrenheit : public helper::Unit
        {
            Fahrenheit() : helper::Unit( "F" ) {}
            FROMDEF{ return _val*1.8-459.67; }
            TODEF{ return (_val+459.67)/1.8; }
        };

        CATEGORYDEF( Temperature, "K",
        {
            std::make_shared< Celsius >(),
            std::make_shared< Fahrenheit >()
        }
    );

    }
}
