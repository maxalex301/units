//
// Created by Максимов Алексей on 24.01.18.
//

#pragma once

namespace unit
{
    namespace pressure
    {
        SUBUNITDEF( MPa, "MPa", Mega )
        SUBUNITDEF( kPa, "kPa", kilo )
        UNITDEF( Bar, "bar", _val*1e-5, _val*1e+5 )
        UNITDEF( At, "at", _val*1.0197e-5, _val*1.0197e+5 )
        UNITDEF( Atm, "atm", _val*9.8692e-6, _val*9.8692e+6 )
        UNITDEF( mmHg, "mm Hg", _val*7.5006e-3, _val*7.5006e+3 )
        UNITDEF( mH2O, "m H2O", _val*1.0197e-4, _val*1.0197e+4 )
        UNITDEF( PSI, "psi", _val*145.04e-6, _val*145.04e+6 )

        CATEGORYDEF( Pressure, "Pa",
        {
            std::make_shared< MPa >(),
            std::make_shared< kPa >(),
            std::make_shared< Bar >(),
            std::make_shared< At >(),
            std::make_shared< Atm >(),
            std::make_shared< mmHg >(),
            std::make_shared< mH2O >(),
            std::make_shared< PSI >()
        }
    );

    }
}
