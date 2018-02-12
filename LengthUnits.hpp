//
// Created by Максимов Алексей on 24.01.18.
//

#pragma once

namespace unit
{
    namespace length
    {
        SUBUNITDEF( kilometre, "km", kilo )
        SUBUNITDEF( centimetre, "cm", centi )
        SUBUNITDEF( decimetre, "dm", deci )
        UNITDEF( inch, "in", _val/39.369948001550156, _val*39.369948001550156 )
        UNITDEF( foot, "ft", _val/3.2808290000021665, _val*3.2808290000021665 )
        UNITDEF( yard, "yd", _val/1.0936099999984663, _val*1.0936099999984663 )
        UNITDEF( mile, "mi", _val/0.0006213699999986272, _val*0.0006213699999986272 )

        CATEGORYDEF( Length, "metre", {
                    std::make_shared< kilometre >(),
                    std::make_shared< centimetre >(),
                    std::make_shared< decimetre >(),
                    std::make_shared< inch >(),
                    std::make_shared< foot >(),
                    std::make_shared< yard >(),
                    std::make_shared< mile >() });
    }
}
