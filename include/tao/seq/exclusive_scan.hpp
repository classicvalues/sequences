// Copyright (c) 2015-2019 Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/sequences/

#ifndef TAO_SEQ_EXCLUSIVE_SCAN_HPP
#define TAO_SEQ_EXCLUSIVE_SCAN_HPP

#include <type_traits>

#include "integer_sequence.hpp"
#include "sequence_helper.hpp"

namespace tao
{
   namespace seq
   {
      namespace impl
      {

#if( __cplusplus >= 201402L )

         template< typename OP, typename T, T... Ns, T V >
         constexpr auto exclusive_impl( integer_sequence< T, Ns... >, std::integral_constant< T, V >, integer_sequence< T > ) noexcept
         {
            return integer_sequence< T, Ns... >();
         }

         template< typename OP, typename T, T... Ns, T V, T R, T... Rs >
         constexpr auto exclusive_impl( integer_sequence< T, Ns... >, std::integral_constant< T, V >, integer_sequence< T, R, Rs... > ) noexcept
         {
            return exclusive_impl< OP, T >( integer_sequence< T, Ns..., V >(), typename OP::template apply< T, V, R >(), integer_sequence< T, Rs... >() );
         }

         template< typename T >
         struct exclusive_scan
         {
            template< typename OP, T Init, T... Ns >
            struct apply
            {
               using type = decltype( exclusive_impl< OP, T >( integer_sequence< T >(), std::integral_constant< T, Init >(), integer_sequence< T, Ns... >() ) );
            };
         };

         template< typename T, T... Ns >
         struct exclusive_scan< integer_sequence< T, Ns... > >
         {
            template< typename OP, T Init >
            struct apply
            {
               using type = decltype( exclusive_impl< OP, T >( integer_sequence< T >(), std::integral_constant< T, Init >(), integer_sequence< T, Ns... >() ) );
            };
         };

#else

         template< typename, typename T, typename, T, typename >
         struct exclusive_impl;

         template< typename OP, typename T, T... Ns, T V >
         struct exclusive_impl< OP, T, integer_sequence< T, Ns... >, V, integer_sequence< T > >
         {
            using type = integer_sequence< T, Ns... >;
         };

         template< typename OP, typename T, T... Ns, T V, T R, T... Rs >
         struct exclusive_impl< OP, T, integer_sequence< T, Ns... >, V, integer_sequence< T, R, Rs... > >
            : exclusive_impl< OP, T, integer_sequence< T, Ns..., V >, OP::template apply< T, V, R >::value, integer_sequence< T, Rs... > >
         {
         };

         template< typename T >
         struct exclusive_scan
         {
            template< typename OP, T Init, T... Ns >
            using apply = exclusive_impl< OP, T, integer_sequence< T >, Init, integer_sequence< T, Ns... > >;
         };

         template< typename T, T... Ns >
         struct exclusive_scan< integer_sequence< T, Ns... > >
         {
            template< typename OP, T Init >
            using apply = exclusive_impl< OP, T, integer_sequence< T >, Init, integer_sequence< T, Ns... > >;
         };

#endif

      }  // namespace impl

      template< typename OP, typename T, typename impl::element_type< T >::type Init, T... Ns >
      using exclusive_scan = typename impl::exclusive_scan< T >::template apply< OP, Init, Ns... >;

      template< typename OP, typename T, typename impl::element_type< T >::type Init, T... Ns >
      using exclusive_scan_t = typename exclusive_scan< OP, T, Init, Ns... >::type;

   }  // namespace seq

}  // namespace tao

#endif
