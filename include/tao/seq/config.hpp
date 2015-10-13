// The Art of C++ / Sequences
// Copyright (c) 2015 Daniel Frey

#ifndef TAOCPP_SEQUENCES_INCLUDE_CONFIG_HPP
#define TAOCPP_SEQUENCES_INCLUDE_CONFIG_HPP

// TODO: Get rid of manual switch, detect properly
#if (__cplusplus >= 201402L) && !defined(TAOCPP_NO_STD_INTEGER_SEQUENCE)
# define TAOCPP_USE_STD_INTEGER_SEQUENCE
#endif

#if (__cplusplus >= 201402L) && defined(_LIBCPP_VERSION)
# define TAOCPP_USE_STD_MAKE_INTEGER_SEQUENCE
#endif

#if defined(__cpp_fold_expressions)
# define TAOCPP_FOLD_EXPRESSIONS
#else
# if defined(__apple_build_version__) && (__clang_major__ >= 7)
#  define TAOCPP_FOLD_EXPRESSIONS
# else
#  if defined(__clang__) && ((__clang_major__ > 3) || ((__clang_major__ == 3) && (__clang_minor__ >= 6)))
#   define TAOCPP_FOLD_EXPRESSIONS
#  endif
# endif
#endif

#endif // TAOCPP_SEQUENCES_INCLUDE_CONFIG_HPP
