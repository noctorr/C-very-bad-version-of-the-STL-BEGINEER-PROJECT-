#include <cstdint>

#ifndef MAP_HPP
#define MAP

namespace utl {

template < typename KEY_TYPE, typename VALUE_TYPE >
struct Map {
    private:
    KEY_TYPE* KEYS;
    VALUE_TYPE* VALUES;

    public:
    explicit Map ()
    {
        KEYS = new KEY_TYPE[UINT32_MAX];
        VALUES = new VALUE_TYPE[UINT32_MAX];
    }

    ~Map ()
    {
        delete[] KEYS;
        delete[] VALUES;
    }

    void Push ( VALUE_TYPE Value ) noexcept
    {
        for ( uint32_t i { 0u }; i <= UINT32_MAX; i++ ) {
            if ( !VALUES[i] ) {
                VALUES[i] = Value;
                break;
            }
        }
    }

    void Place ( KEY_TYPE Key, VALUE_TYPE Value ) noexcept
    {
        for ( uint32_t i { 0u }; i <= UINT32_MAX; i++ ) {
            if ( KEYS[i] == Key ) {
                VALUES[i] = Value;
                return;
            }
        }

        for ( uint32_t i { 0u }; i<= UINT32_MAX; i++ ) {
            if ( !KEYS[i] ) {
                KEYS[i] = Key;
                VALUES[i] = Value;
                return;
            }
        }
    }
};
}

#endif
