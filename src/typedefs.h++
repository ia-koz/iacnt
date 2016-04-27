#ifndef TYPEDEFS_HPP
#define TYPEDEFS_HPP

#include <cstddef>
#include <string>


/// Dimention/size type , 32 or 64 bit
typedef std::size_t							dim_t;

/// Character
typedef char								char_t;

/// Bool type
typedef bool								bool_t;

/// Byte , signed 8 bit
typedef char								sbyte_t;

/// Byte , unsigned 8 bit
typedef unsigned char						byte_t;

/// Word , unsigned 16 bit
typedef unsigned short int					word_t;

/// Double word , unsigned 32 bit
typedef unsigned int						dword_t;

/// Quad word , unsigned 64 bit
typedef unsigned long long int				qword_t;

/// Integer , signed 16 bit
typedef short int							short_t;

/// Integer , unsigned 16 bit
typedef unsigned short int					ushort_t;

/// Integer , signed 32 bit
typedef int									int_t;

/// Integer , unsigned 32 bit
typedef unsigned int						uint_t;

/// Integer , signed 64 bit
typedef long long int						long_t;

/// Integer , unsigned 64 bit
typedef unsigned long long int				ulong_t;

/// Floating type
typedef float								float_t;

/// Double floating type
typedef double								double_t;

/// Long double floating type
typedef long double							ldouble_t;

/// String
typedef std::string							string_t;


#endif // TYPEDEFS_HPP
