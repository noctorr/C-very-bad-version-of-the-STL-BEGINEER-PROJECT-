#include <cstdint>

#ifndef ALGORITHM_HPP
#define ALGORITHM

namespace  utl {

template < typename TYPE, uint64_t SIZE >
bool Is_Sorted ( TYPE ARRAY01[SIZE])
{
    for ( uint64_t i { 1ULL }; i <= SIZE; i++ ) {
        if ( ARRAY01[i] < ARRAY01[i-1] ) {
            return false;
        }
    }
}

template < typename TYPE, uint64_t SIZE >
void Sort ( TYPE (&ARRAY01)[SIZE] )
{
    while (Is_Sorted(ARRAY01)) {
        for ( uint64_t i { 1ULL }; i <= SIZE; i++ ) {
            if ( ARRAY01[i] < ARRAY01[i-1] ) {
                TYPE X1 = ARRAY01[i];
                TYPE X2 = ARRAY01[i-1];
                ARRAY01[i] = X2;
                ARRAY01[i-1] = X1;
            }
        }
    }
}

template < typename TYPE, uint64_t SIZE >
bool Search ( TYPE ARRAY01[SIZE], TYPE VALUE )
{
    for ( uint64_t i { 0ULL }; i < SIZE; i++ ) {
        if ( ARRAY01[i] == VALUE ) return true;
    }
    return false;
}

inline void* Range ( uint16_t END )
{
    uint16_t* ARRAY01 = new uint16_t[END];
    for ( uint16_t i { 0u }; i < END; i++ ) {
        ARRAY01[i] = i;
    }
    return ARRAY01;
}

}

#endif
