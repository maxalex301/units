//
// Created by Максимов Алексей on 24.01.18.
//

#pragma once

#include <string>
#include <forward_list>
#include <memory>

namespace unit
{
#define FROMDEF virtual double FromDefault( const double& _val ) const override
#define TODEF virtual double ToDefault( const double& _val ) const override
#define UNITDEF( name, str, fdef, todef ) struct name : public ::unit::helper::Unit{ name(): ::unit::helper::Unit( str ){} name( const std::string& _n ) : ::unit::helper::Unit( _n ){} FROMDEF{ return fdef; } TODEF{ return todef; } };
#define SUBUNITDEF( name, str, subclass ) struct name : public subclass { explicit name(): ::unit::subclass( str ){} };
#define CATEGORYDEF( name, defunit, ... ) struct name : public helper::UnitCategory { name() : helper::UnitCategory( #name, defunit, __VA_ARGS__ ){} };

    class BadCategoryException : public std::exception
    {
        const char* what() const throw() { return "Bad units category name\n"; }
    };

    class BadUnitException : public std::exception
    {
        const char* what() const throw() { return "Bad unit name\n"; }
    };

    namespace helper
    {
        class Unit
        {
            std::string m_name;
        public:
            explicit Unit( const std::string &_name ) :
                m_name( _name )
            {}

            Unit() = delete;
            Unit( const Unit & ) = default;
            Unit &operator=( const Unit & ) = default;

            std::string Name() const
            {
                return m_name;
            }

            bool operator==( const Unit &_r ) const
            {
                return m_name.compare( _r.Name()) == 0;
            }

            bool operator==( const std::string &_name ) const
            {
                return m_name.compare( _name ) == 0;
            }

            virtual double ToDefault( const double & ) const = 0;
            virtual double FromDefault( const double & ) const = 0;
        };

        class UnitCategory
        {
            using map_t = std::forward_list< std::shared_ptr< Unit > >;
            std::string m_name;
            std::string m_defaultUnit;
            map_t m_units;
        public:
            explicit UnitCategory( const std::string &_name,
                                   const std::string &_defaultUnit,
                                   map_t &&_units ) :
                m_name( _name ), m_defaultUnit( _defaultUnit ),
                m_units( std::move( _units ))
            {
            }

            UnitCategory() = delete;
            UnitCategory( const UnitCategory &_category ) = default;
            UnitCategory &operator=( const UnitCategory & ) = default;

            std::string Name() const
            {
                return m_name;
            }

            bool operator==( const UnitCategory &_category ) const
            {
                return m_name.compare( _category.Name()) == 0;
            }

            bool operator==( const std::string &_name ) const
            {
                return m_name.compare( _name ) == 0;
            }

            bool IsDefault( const std::string &_unit ) const
            {
                return m_defaultUnit.compare( _unit ) == 0;
            }

            bool IsDefault( const Unit &_unit ) const
            {
                return m_defaultUnit.compare( _unit.Name()) == 0;
            }

            Unit *GetUnit( const std::string &_unitName ) const
            {
                auto res = std::find_if( m_units.begin(), m_units.end(),
                                         [ &_unitName ]( const auto &_unit ) { return *_unit == _unitName; } );
                if ( res == m_units.end() )
                    throw BadUnitException();

                return res->get();
            }

            double Convert( const double &_value,
                            const std::string &_from,
                            const std::string &_to ) const
            {
                auto res = _value;

                try {
                    if ( _from.compare( _to ) == 0 )
                        return res;

                    if ( !IsDefault( _from ) ) {
                        auto fUnit = GetUnit( _from );
                        res = fUnit->ToDefault( res );
                    }

                    if ( !IsDefault( _to )) {
                        auto tUnit = GetUnit( _to );
                        res = tUnit->FromDefault( res );
                    }
                } catch ( const BadUnitException &_e ) {
                    throw _e;
                }

                return res;
            }
        };

        class UnitsFactory
        {
            using map_t = std::forward_list< std::shared_ptr< UnitCategory > >;
            map_t m_categories;
        protected:
            UnitsFactory();
        public:
            static UnitsFactory &Instance()
            {
                static UnitsFactory _instance;
                return _instance;
            }

            void Register( const std::shared_ptr< UnitCategory >& _category )
            {
                m_categories.push_front( _category );
            }

            UnitsFactory( UnitsFactory & ) = delete;
            UnitsFactory &operator=( UnitsFactory & ) = delete;
            ~UnitsFactory() = default;

            UnitCategory *GetCategory( const std::string &_name ) const
            {
                auto res = std::find_if( m_categories.begin(), m_categories.end(),
                                         [ &_name ]( const auto &_category ) { return *_category == _name; } );
                if ( res == m_categories.end())
                    throw BadCategoryException();

                return res->get();
            }

            double Convert( const std::string &_category,
                            const double &_value,
                            const std::string &_from,
                            const std::string &_to ) const
            {
                auto res = _value;

                try {
                    auto category = GetCategory( _category );
                    res = category->Convert( _value, _from, _to );
                } catch ( const BadCategoryException &_e ) {
                    throw _e;
                }

                return res;
            }
        };

        inline UnitsFactory &Units()
        {
            return UnitsFactory::Instance();
        }
    }
    UNITDEF( milli, "", _val * 1e+3, _val * 1e-3 );
    UNITDEF( centi, "", _val * 1e+2, _val * 1e-2 );
    UNITDEF( deci, "", _val * 10, _val * 0.1 );
    UNITDEF( kilo, "", _val * 1e-3, _val * 1e+3 );
    UNITDEF( Mega, "", _val * 1e-6, _val * 1e+6 );
    UNITDEF( Giga, "", _val * 1e-9, _val * 1e+9 );
}

#include "TemperatureUnits.hpp"
#include "PressureUnits.hpp"
#include "LengthUnits.hpp"

namespace unit
{
    namespace helper
    {
        UnitsFactory::UnitsFactory() :
            m_categories( { std::make_shared< temperature::Temperature >(),
                              std::make_shared< pressure::Pressure >(),
                          std::make_shared< length::Length >() } )
        {}
    }

    double convert( const std::string &_category, const double &_value,
                    const std::string &_from, const std::string &_to )
    {
        return helper::Units().Convert( _category, _value, _from, _to );
    }
}