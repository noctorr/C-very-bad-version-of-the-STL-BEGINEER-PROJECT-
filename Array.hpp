#include <cstddef>
#include <stdexcept>
#include <type_traits>
#include <cstdint>
#include <initializer_list>
#include <typeinfo>

namespace Utilities {
enum class NumbersID
{
    SINGLE_PRECISION_FLOAT = 32,
    DOUBLE_PRECISION_FLOAT = 64,
    SIGNED_INTEGER_32BIT = 320,
    SIGNED_INTEGER_64BIT = 640,
    SIGNED_INTEGER_16BIT = 16,
    SIGNED_INTEGER_8BIT = 8,
    UNSIGNED_INTEGER_32BIT = 3200,
    UNSIGNED_INTEGER_64BIT = 6400,
    UNSIGNED_INTEGER_16BIT = 160,
    UNSIGNED_INTEGER_8BIT = 80
};

constexpr uint64_t VECTOR_SIZE = 10500;
}

#ifndef ARRAY_HPP
#define ARRAY

namespace utl {

template < typename TYPE , uint16_t SIZE >
struct Array {
    private:
    TYPE* ARRAY_VALUES;

    protected:
    virtual void REPLACE ( TYPE (&Array1)[SIZE] ) noexcept
    {
        for ( uint16_t i { 0u }; i <= SIZE - 1; i++ ) ARRAY_VALUES[i] = Array1[i];
    }

    virtual TYPE* RETURN () noexcept
    {
        return ARRAY_VALUES;
    }

    public:
    explicit Array (
        TYPE (&Array1)[SIZE]
    ) {
        ARRAY_VALUES = new TYPE[SIZE];
        for ( uint16_t i { 0u }; i <= SIZE - 1; i++ ) ARRAY_VALUES[i] = Array1[i];
    }

    Array ()
    {
        ARRAY_VALUES = new TYPE[SIZE];
    }

    Array (
        std::initializer_list<TYPE> LIST
    ) {
        ARRAY_VALUES = new TYPE[SIZE];

        uint16_t i0 { 0u };
        for (TYPE& i : LIST) {
            if (i0 < SIZE) {
                ARRAY_VALUES[i0] = i;
                i0++;
            }
        }
    }

    ~Array() {
        delete[] ARRAY_VALUES;
    }

    TYPE*& operator= ( const TYPE (&Array1)[SIZE] ) noexcept
    {
        for ( uint16_t i { 0u }; i <= SIZE - 1; i++ ) ARRAY_VALUES[i] = Array1[i];
        return ARRAY_VALUES;
    }

    constexpr const TYPE& operator[] ( uint16_t Index ) const noexcept
    {
        return ARRAY_VALUES[Index];
    }

    const TYPE& at ( uint16_t Index ) const
    {
        if ( Index >= SIZE ) throw std::out_of_range("Index is larger than the Array Size.");
        return ARRAY_VALUES[Index];
    }

    constexpr void insert ( TYPE& Value, uint16_t Index )
    {
        if ( Index >= SIZE) throw std::out_of_range("Index is larger than the Array Size.");
        ARRAY_VALUES[Index] = Value;
    }

    constexpr void pushBack (TYPE& Value) noexcept
    {
        ARRAY_VALUES[SIZE - 1] = Value;
    }

    virtual void sort () noexcept
    {
        TYPE*& X = ARRAY_VALUES;
        uint16_t K = SIZE;
        auto check = [&X, &K] () -> bool {
            for ( uint16_t i { 1u }; i < K; i++ ) {
                if (X[i] < X[i-1]) return false;
            }
            return true;
        };

        do {
            for ( uint16_t i { 1u }; i <= SIZE - 1; i++ ) {
                if (X[i] < X[i-1]) {
                    TYPE TEMP1 = X[i];
                    TYPE TEMP2 = X[i-1];
                    X[i] = TEMP2;
                    X[i-1] = TEMP1;
                }
            }
        } while(check());
    }

    constexpr const size_t memoryStorage () const
    {
        return sizeof(*this);
    }

    constexpr const size_t arrayMemoryStorage () const
    {
        return sizeof(ARRAY_VALUES);
    }

    const bool empty () const noexcept
    {
        for ( TYPE i : ARRAY_VALUES ) {
            if ( i != 0 || i != nullptr ) return false;
        }
        return true;
    }

    void clear () noexcept
    {
        for ( TYPE& i : ARRAY_VALUES ) {
            i = nullptr;
        }
    }

    virtual void reverse () 
    {
        for ( uint16_t i { 0u }; i < SIZE / 2; i++ ) {
            TYPE X = ARRAY_VALUES[SIZE - 1 - i];
            ARRAY_VALUES[i] = X;
        }
    }
};

template < typename TYPE >
struct Vector : public Array < TYPE, Utilities::VECTOR_SIZE >
{
    public:
    bool NumberType { false };
    Utilities::NumbersID NumID;
    
    Vector(
        std::initializer_list<TYPE> LIST
    )
    {
        TYPE stackArray[Utilities::VECTOR_SIZE];

        uint16_t i0 { 0u };
        for (TYPE i : LIST) {
            stackArray[i0] = i;
            i0++;
        }

        this->REPLACE(stackArray);
        
        if constexpr (std::is_same_v<TYPE, int16_t> || (std::is_same_v<TYPE, short> && (sizeof(short) * 8) == 16)) {
            NumberType = true;
            NumID = Utilities::NumbersID::SIGNED_INTEGER_16BIT;
        }
        else if constexpr (std::is_same_v<TYPE, int8_t> || (std::is_same_v<TYPE, char> && (sizeof(char) * 8) == 8)) {
            NumberType = true;
            NumID = Utilities::NumbersID::SIGNED_INTEGER_8BIT;
        }
        else if constexpr (std::is_same_v<TYPE, int32_t> || (std::is_same_v<TYPE, int> && (sizeof(int) * 8) == 32)) {
            NumberType = true;
            NumID = Utilities::NumbersID::SIGNED_INTEGER_32BIT;
        }
        else if constexpr (std::is_same_v<TYPE, int64_t> || (std::is_same_v<TYPE, long long> && (sizeof(long long) * 8) == 64)) {
            NumberType = true;
            NumID = Utilities::NumbersID::SIGNED_INTEGER_64BIT;
        }
        else if constexpr (std::is_same_v<TYPE, uint8_t>) {
            NumberType = true;
            NumID = Utilities::NumbersID::UNSIGNED_INTEGER_8BIT;
        }
        else if constexpr (std::is_same_v<TYPE, uint16_t>) {
            NumberType = true;
            NumID = Utilities::NumbersID::UNSIGNED_INTEGER_16BIT;
        }
        else if constexpr (std::is_same_v<TYPE, uint32_t>) {
            NumberType = true;
            NumID = Utilities::NumbersID::UNSIGNED_INTEGER_32BIT;
        }
        else if constexpr (std::is_same_v<TYPE, uint64_t>) {
            NumberType = true;
            NumID = Utilities::NumbersID::UNSIGNED_INTEGER_64BIT;
        }
        else if constexpr (std::is_same_v<TYPE, float>) {
            NumberType = true;
            NumID = Utilities::NumbersID::SINGLE_PRECISION_FLOAT;
        }
        else if constexpr (std::is_same_v<TYPE, double>) {
            NumberType = true;
            NumID = Utilities::NumbersID::DOUBLE_PRECISION_FLOAT;
        }
    }

    template < uint16_t SIZE >
    Vector 
    (
        TYPE (&VALUES)[SIZE]
    ) {
        this->REPLACE(VALUES);
    }
    
    Vector () {}

    constexpr const TYPE& operator[] ( uint16_t Index ) noexcept
    {
        return this->RETURN()[Index];
    }

    const uint16_t length()
    {
        uint16_t i0 { 0u };
        TYPE*& x = this->RETURN();
        for ( uint16_t i { 0u }; i <= Utilities::VECTOR_SIZE - 1u; i++ ) {
            if (x[i] == 0) {
                return i;
            }
            i0++;
        }
        return i0;
    }
    
    TYPE* SHOWARRAY () noexcept
    {
        return this->RETURN();
    }
    
    void operator+ ( Vector& OTHER )
    {
        if (!OTHER.NumberType || !NumberType) throw std::runtime_error("Tryed to perform arithmetics on a none number type.");

        TYPE*& VALUES = this->RETURN();
        auto otherVALUES = OTHER.SHOWARRAY();
        for ( uint16_t i { 0u }; i <= Utilities::VECTOR_SIZE - 1u; i++ ) {
            VALUES[i] += otherVALUES[i];
        }
    }

    void operator- ( Vector& OTHER )
    {
        if (!OTHER.NumberType || !NumberType) throw std::runtime_error("Tryed to perform arithmetics on a none number type.");

        TYPE*& VALUES = this->RETURN();
        auto otherVALUES = OTHER.SHOWARRAY();
        for ( uint16_t i { 0u }; i <= Utilities::VECTOR_SIZE - 1u; i++ ) {
            VALUES[i] -= otherVALUES[i];
        }
    }

    void operator* ( Vector& OTHER )
    {
        if (!OTHER.NumberType || !NumberType) throw std::runtime_error("Tryed to perform arithmetics on a none number type.");

        TYPE*& VALUES = this->RETURN();
        auto otherVALUES = OTHER.SHOWARRAY();
        for ( uint16_t i { 0u }; i <= Utilities::VECTOR_SIZE - 1u; i++ ) {
            VALUES[i] *= otherVALUES[i];
        }
    }

    void operator/ ( Vector& OTHER )
    {
        if (!OTHER.NumberType || !NumberType) throw std::runtime_error("Tryed to perform arithmetics on a none number type.");

        TYPE* VALUES = this->RETURN();
        auto otherVALUES = OTHER.SHOWARRAY();
        for ( uint16_t i { 0u }; i <= Utilities::VECTOR_SIZE - 1u; i++ ) {
            VALUES[i] /= otherVALUES[i];
        }
    }

    void operator= ( Vector& OTHER )
    {
        if (typeid(OTHER.RETURN()).name() != typeid(this->RETURN()).name()) throw std::out_of_range("Tryed to perform copy operator function on a vector not the same type.");

        TYPE*& VALUES = this->RETURN();
        uint16_t i0 { 0u };
        for ( TYPE i : OTHER.RETURN() ) {
            VALUES[i0] = i;
            i0++;
        }
    }
};

}

#endif
