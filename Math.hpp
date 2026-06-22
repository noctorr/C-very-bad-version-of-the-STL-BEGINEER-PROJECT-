#include <cstdint>
#include <stdexcept>

namespace Utilities {
inline constexpr double PI180_CONSTANT = 0.0174532952;

inline constexpr int8_t PRIVATE_S_CHECK(const double& i0)
{
    if (i0 > double(INT64_MAX) || i0 < double(-INT64_MAX)) {
        return 1;
    } else {
        return -1;
    }
}

inline constexpr int8_t PRIVATE_U_CHECK(const double& u0)
{
    if (u0 > double(UINT64_MAX)) {
        return 1;
    } else {
        return -1;
    }
}

inline constexpr int8_t PRIVATE_CHECK(const double& y)
{
    const int8_t i0 = PRIVATE_S_CHECK(y);
    if (i0 == 1)
        return 1;

    const int8_t i1 = PRIVATE_U_CHECK(y);
    if (i1 == 1)
        return 2;

    return 0;
}

inline int FACTORIAL(int i0)
{
    int Holder{ i0 };
    for ( int i { i0 }; i >= 0; i-- ) Holder *= i;

    return Holder;
}

inline double WPOWER_SERIES(double x1, int e1)
{
    double y = x1 - 1.0;
    double b = y;
    for ( uint8_t i { 0u }; i <= e1; i++ ) y *= b;

    return y;
}

static int64_t PRCounter = INT64_MIN;

inline int64_t PseudoRandGen ()
{
    return PRCounter + (PRCounter - 3) - 2;
}

}

#ifndef MATH_HPP
#define MATH

namespace utl {

inline constexpr double EULERS_CONSTANT = 2.718281828;
inline constexpr double PI_CONSTANT = 3.141592654;
inline constexpr double PI2_CONSTANT = 1.570796327;
inline constexpr double SQRT_OF_FIVE_CONSTANT = 2.236067977;
inline constexpr double SQRT_OF_TWO_CONSTANT = 1.414213562;
inline constexpr double SQRT_OF_THREE_CONSTANT = 1.732050808;
inline constexpr double TGR_CONSTANT = 1.61803398875;
inline constexpr double CONJUGATE_TGR_CONSTANT = -0.6180339887;

template < typename NUMBER_TYPE, typename SECOND_NUMBER_TYPE >
NUMBER_TYPE Power ( NUMBER_TYPE x, SECOND_NUMBER_TYPE power )
{
    if (power == 0) {
        return NUMBER_TYPE(1);
    } else if (power < 0) {
        NUMBER_TYPE X = Power(1 / x, -power);
        return X;
    }

    NUMBER_TYPE Holder = x;
    for (uint64_t i { 0ULL }; i <= power; i++) Holder *= x;

    return Holder;
}

template < typename NUMBER_TYPE >
constexpr NUMBER_TYPE Abs ( NUMBER_TYPE x1 )
{
    if (x1 < 0) {
        return -x1;
    } else {
        return x1;
    }
}


inline constexpr double Round ( double x )
{
    if (UINT64_MAX < x) return x;

    int8_t i0 = Utilities::PRIVATE_CHECK(x);

    switch (i0) {
    case 1: {
        double i = double(static_cast<long long>(x));
        if (x > 0) {
            return (x > i + 0.5) ? i + 1.0 : i;
        } else {
            return (x > i - 0.5) ? i : i - 1.0;
        }
    }
    case 2: {
        double i = double(static_cast<uint64_t>(x));
        return (x > i + 0.5) ? i + 1.0 : i;
    }
    }

    return 0.0;
}

inline constexpr double Ceil ( double x )
{
    if (UINT64_MAX < x) return x;

    int8_t i0 = Utilities::PRIVATE_CHECK(x);

    switch (i0) {
        case 1: {
            double i = double(static_cast<long long>(x));
            if (x > 0) {
                return i + 1.0;
            } else {
                return i;
            }
        }

        case 2: {
            double i = double(static_cast<uint64_t>(x));
            return i + 1.0;
        }
    }

    return 0.0;
}

inline constexpr double Floor ( double x )
{
    if (UINT64_MAX < x) return x;

    int8_t i0 = Utilities::PRIVATE_CHECK(x);

    switch (i0) {
        case 1: {
            double i = double(static_cast<long long>(x));
            if (x > 0) {
                return i;
            } else {
                return i - 1.0;
            }
        }

        case 2: {
            double i = double(static_cast<uint64_t>(x));
            return i;
        }
    }

    return 0.0;
}

template < typename NUMBER_TYPE >
double Exp ( NUMBER_TYPE power )
{
    return Power(EULERS_CONSTANT, power);
}

inline constexpr double Sine ( double x1 )
{
    if (x1 == 0.0 || x1 == 180.0 || x1 == -0.0) {
        return 0.0;
    } else if (x1 == 30.0 || x1 == 270.0) {
        return 0.5;
    } else if (x1 == 45.0 || x1 == 135.0) {
        return 0.7071067812;
    } else if (x1 == 60.0 || x1 == 120.0) {
        return 0.8660254038;
    } else if (x1 == 90.0 || x1 == 450.0) {
        return 1.0;
    }

    x1 *= Utilities::PI180_CONSTANT;
    const double x2 { x1 * x1 };
    constexpr double P1 = -0.1666666667;
    constexpr double P2 = 0.008333333333;
    constexpr double P3 = -0.000198412698;
    constexpr double P4 = 0.00000275573192;

    return x1 * (1.0 + x2 * (P1 + x2) * (P2 + x2) * (P3 + (x2 * P4)));
}

inline constexpr double Cosine ( double x1 )
{
    if (x1 == 0.0 || x1 == 360.0 || x1 == -0.0) {
        return 1.0;
    } else if (x1 == 30.0 || x1 == 390.0) {
        return 0.8660254038;
    } else if (x1 == 45.0 || x1 == 300.0) {
        return 0.7071067812;
    } else if (x1 == 60.0 || x1 == 420.0) {
        return 0.5;
    } else if (x1 == 90.0 || x1 == 270.0) {
        return 0.0;
    }

    x1 *= Utilities::PI180_CONSTANT;
    const double x2 { x1 * x1 };
    constexpr double P1 = -0.5;
    constexpr double P2 = 0.041666666667;
    constexpr double P3 = -0.001388888889;
    constexpr double P4 = 0.0000248015873015873;

    return 1.0 + x2 * (P1 + x2 * (P2 + x2 * (P3 + x2 * P4)));
}

inline double NaturalLog ( double x1 )
{
    if (x1 == 0.0) {
        return 1.0;
    } else if (x1 == 1.0) {
        return 0;
    } else if (x1 < 0.0) {
        throw std::domain_error("ERRROR, NEGATIVE VALUE INPUTTED INTO NATURAL LOGARITHM FUNCTION.");
    }

    double Holder { x1 - 1.0 };
    bool sign = false;

    for (uint8_t i { 2u }; i <= 5; i++ ) {
        if (sign) {
            Holder += Utilities::WPOWER_SERIES(x1, i) / (1.0 / i);
        } else {
            Holder -= Utilities::WPOWER_SERIES(x1, i) / (1.0 / i);
        }
    }

    return Holder;
}

inline double SquareRoot ( double x1 )
{
    if ( x1 < 0.0 ) {
        throw std::domain_error("Cannot compute imaginary numbers.");
    } else if (x1 == 0.0 || x1 == 1.0) {
        return x1;
    }

    double a { x1 };
    
    for ( uint8_t i { 0u }; i < 10; i++ ) a = 0.5 * (a + (x1 / a));
    return a;
}

inline double Tangent ( double x1 )
{
    if (x1 == 0.0 || x1 == 180.0 || x1 == -0.0) {
        return 0.0;
    } else if (x1 == 30.0 || x1 == 210.0) {
        return 0.5773502692;
    } else if (x1 == 45.0 || x1 == 225.0) {
        return 1.0;
    } else if (x1 == 60.0 || x1 == 240.0) {
        return SQRT_OF_THREE_CONSTANT;
    } else if (x1 == 90.0 || x1 == 270.0) {
        throw std::domain_error("90 Degrees is undefined for Tan.");
    }

    x1 *= Utilities::PI180_CONSTANT;
    const double x2 { x1*x1 };

    double t = 0.008863235;
    t = 0.021869488 + x2 * t;
    t = 0.053968253 + x2 * t;
    t = 0.133333333 + x2 * t;
    t = 0.333333333 + x2 * t;
    t = 1.0 + x2 * t;

    return x1 * t;
}

inline double Sigmoid ( double x1 )
{
    return 1.0 / (1.0 + Exp(-x1));
}

inline constexpr double ArcSine ( double x1 )
{
    if (x1 == 1) {
        return PI_CONSTANT / 2.0;
    } else if (x1 == -1) {
        return -(PI_CONSTANT / 2.0);
    } else if (x1 == 0.0 || x1 == -0.0) {
        return 0.0;
    } else if (x1 == 0.5) {
        return PI_CONSTANT / 6.0;
    } else if (x1 == -0.5) {
        return -(PI_CONSTANT / 6.0);
    } else if (x1 == 0.7071067812) {
        return PI_CONSTANT / 4.0;
    } else if (x1 == 0.8660254038) {
        return PI_CONSTANT / 3.0;
    } else if (x1 > 1 || x1 < -1) {
        throw std::domain_error("Error cannot compute values above 1 or below -1.");
    }

    constexpr double P1 = 0.16666666;
    constexpr double P2 = 0.075;
    constexpr double P3 = 0.04464285;
    constexpr double P4 = 0.03038194;
    const double x2 = x1 * x1;

    return x1 * (P1 + x2 * (P2 + x2 * (P3 + x2 * P4)));
}

inline double ArcCosine ( double x1 )
{
    return PI2_CONSTANT - ArcSine(x1);
}

inline constexpr double ArcTangent ( double x1 )
{
    if (x1 == 0.0 || x1 == -0.0) {
        return 0.0;
    } else if (x1 == 1.0) {
        return PI_CONSTANT / 4.0;
    } else if (x1 == -1.0) {
        return -(PI_CONSTANT / 4.0);
    } else if (x1 == SQRT_OF_THREE_CONSTANT) {
        return PI_CONSTANT / 3.0;
    } else if (x1 == -SQRT_OF_THREE_CONSTANT) {
        return -(PI_CONSTANT / 3.0);
    } else if (x1 == 1.0 / SQRT_OF_THREE_CONSTANT) {
        return PI_CONSTANT / 6.0;
    } else if (x1 == -(1.0 / SQRT_OF_THREE_CONSTANT)) {
        return -(PI_CONSTANT / 6.0);
    }


    x1 *= Utilities::PI180_CONSTANT;
    const double x2 { x1 * x1 };
    constexpr double P1 = -0.14285714;
    constexpr double P2  = 0.2;
    constexpr double P3 = 0.333333333;

    return x1 * ((P1 * x2 + P2) * x2 - P3) * x2 + 1.0;
}

inline double Radian ( double x1 )
{
    return (x1 * PI_CONSTANT) / 180.0;
}

inline double Degree ( double x1 )
{
    return (x1 * 180.0) / PI_CONSTANT;
}

inline double SineHyp ( double x1 )
{
    return (Exp(x1) - Exp(-x1)) / 2.0;
}

inline double CosineHyp ( double x1 )
{
    return (Exp(x1) + Exp(-x1)) / 2.0;
}

inline double TangentHyp ( double x1 )
{
    return SineHyp(x1) / CosineHyp(x1);
}

inline int64_t Random ( int64_t m1, int64_t m2 )
{
    Utilities::PRCounter = m1;
    return Utilities::PseudoRandGen();
}

}

#endif
