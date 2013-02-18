//=================================================================================================
/*!
//  \file blaze/util/UniqueArray.h
//  \brief Header file for the UniqueArray smart pointer class
//
//  Copyright (C) 2011 Klaus Iglberger - All Rights Reserved
//
//  This file is part of the Blaze library. This library is free software; you can redistribute
//  it and/or modify it under the terms of the GNU General Public License as published by the
//  Free Software Foundation; either version 3, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
//  without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//  See the GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License along with a special
//  exception for linking and compiling against the Blaze library, the so-called "runtime
//  exception"; see the file COPYING. If not, see http://www.gnu.org/licenses/.
*/
//=================================================================================================

#ifndef _BLAZE_UTIL_UNIQUEARRAY_H_
#define _BLAZE_UTIL_UNIQUEARRAY_H_


//*************************************************************************************************
// Includes
//*************************************************************************************************

#include <blaze/uitl/constraints/Extent.h>
#include <blaze/util/NonCopyable.h>
#include <blaze/util/Null.h>
#include <blaze/util/policies/ArrayDelete.h>
#include <blaze/util/Types.h>
#include <blaze/util/typetraits/RemoveReference.h>


namespace blaze {

//=================================================================================================
//
//  CLASS DEFINITION
//
//=================================================================================================

//*************************************************************************************************
/*!\brief Scope-limited management of dynamically allocated arrays.
// \ingroup util
//
// The UniqueArray class implements a scope-restricted, lightweight smart pointer that manages a
// dynamically allocated array. In contrast to other smart pointer implementations, UniqueArray
// is non-copyable and therefore restricted to manage arrays within a single scope, but does so
// so with a minimum of runtime overhead. The following example demonstrates the application of
// UniqueArray:

   \code
   {
      blaze::UniqueArray<int> mystring( new int[10] );

      // ... Working with the integer array

   } // The array is automatically destroyed at the end of scope according to the RAII principle
   \endcode

// Note that UniqueArray's interface is optimized for arrays and that by default ArrayDelete is
// used. For the management of single objects, UniquePtr can be used:

   \code
   {
      blaze::UniquePtr<std::string> mystring( new std::string( "My string" ) );

      // ... Working with the string

   } // The string is automatically destroyed at the end of scope according to the RAII principle
   \endcode

// Note that the template argument \a T must not have any array extent (similar to the unique_ptr
// implementation of the C++11 standard, where the array extent differentiates between single
// objects and arrays). Providing a type with array extent will result in a compile time error!
*/
template< typename T                  // Type of the array elements
        , typename D = ArrayDelete >  // Type of the deleter
class UniqueArray : private NonCopyable
{
 public:
   //**Type definitions****************************************************************************
   typedef typename RemoveReference<T>::Type*  Pointer;    //!< Pointer type of the managed array elements.
   typedef typename RemoveReference<T>::Type&  Reference;  //!< Reference type of the managed array elements.
   typedef D                                   Deleter;    //!< Type of the resource deleter.
   //**********************************************************************************************

   //**Constructors********************************************************************************
   /*!\name Constructors */
   //@{
   inline UniqueArray( Pointer ptr = NULL );
   //@}
   //**********************************************************************************************

   //**Destructor**********************************************************************************
   /*!\name Destructor */
   //@{
   inline ~UniqueArray();
   //@}
   //**********************************************************************************************

   //**Access operators****************************************************************************
   /*!\name Access operators */
   //@{
   inline Reference operator[]( size_t index ) const;
   //@}
   //**********************************************************************************************

   //**Utility functions***************************************************************************
   /*!\name Utility functions */
   //@{
   inline Pointer get() const;
   inline Pointer release();
   inline void    reset( Pointer ptr = NULL );
   inline void    swap ( UniqueArray& up ) /* throw() */;
   //@}
   //**********************************************************************************************

 private:
   //**Member variables****************************************************************************
   /*!\name Member variables */
   //@{
   Pointer ptr_;      //!< Pointer to the managed array.
   Deleter deleter_;  //!< Resource deleter.
   //@}
   //**********************************************************************************************
   
   //**Compile time checks*************************************************************************
   /*! \cond BLAZE_INTERNAL */
   BLAZE_CONSTRAINT_MUST_NOT_HAVE_EXTENT( T );
   /*! \endcond */
   //**********************************************************************************************
};
//*************************************************************************************************




//=================================================================================================
//
//  CONSTRUCTOR
//
//=================================================================================================

//*************************************************************************************************
/*!\brief The default constructor for the UniqueArray specialization.
//
// \param ptr The array to be managed by the unique array
*/
template< typename T    // Type of the array elements
        , typename D >  // Type of the deleter
inline UniqueArray<T,D>::UniqueArray( Pointer ptr )
   : ptr_    ( ptr       )  // Pointer to the managed array
   , deleter_( Deleter() )  // Resource deleter
{}
//*************************************************************************************************




//=================================================================================================
//
//  DESTRUCTOR
//
//=================================================================================================

//*************************************************************************************************
/*!\brief The destructor for the UniqueArray specialization.
*/
template< typename T    // Type of the array elements
        , typename D >  // Type of the deleter
inline UniqueArray<T,D>::~UniqueArray()
{
   deleter_( ptr_ );
}
//*************************************************************************************************




//=================================================================================================
//
//  ACCESS OPERATORS
//
//=================================================================================================

//*************************************************************************************************
/*!\brief Direct access to the array elements.
//
// \return Reference to the managed array.
*/
template< typename T    // Type of the array elements
        , typename D >  // Type of the deleter
inline typename UniqueArray<T,D>::Reference UniqueArray<T,D>::operator[]( size_t index ) const
{
   return ptr_[index];
}
//*************************************************************************************************




//=================================================================================================
//
//  UTILITY FUNCTIONS
//
//=================================================================================================

//*************************************************************************************************
/*!\brief Returns a pointer to the managed array.
//
// \return Pointer to the managed array or NULL if no array is managed.
//
// This function returns a pointer to the managed array (or NULL in case no array is
// currently managed). Note however that the ownership remains with the unqiue pointer.
*/ 
template< typename T    // Type of the array elements
        , typename D >  // Type of the deleter
inline typename UniqueArray<T,D>::Pointer UniqueArray<T,D>::get() const
{
   return ptr_;
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Releases the ownership of the managed array to the caller.
//
// \return Pointer to the managed array or NULL if no array is managed.
//
// This function returns a pointer to the managed array (or NULL in case no array is
// currently managed). The ownership of the array is released and passed to the caller.
*/
template< typename T    // Type of the array elements
        , typename D >  // Type of the deleter
inline typename UniqueArray<T,D>::Pointer UniqueArray<T,D>::release()
{
   Pointer tmp( ptr_ );
   ptr_ = NULL;
   return tmp;
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Resets the unique array and replaces the managed array with the given array.
//
// \param ptr The new array to be managed by the unique array.
// \return void
*/
template< typename T    // Type of the array elements
        , typename D >  // Type of the deleter
inline void UniqueArray<T,D>::reset( Pointer ptr )
{
   if( ptr != ptr_ ) {
      UniqueArray( ptr ).swap( *this );
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Swapping the contents of two unique arrays.
//
// \param ptr The unique array to be swapped.
// \return void
// \exception no-throw guarantee.
*/
template< typename T    // Type of the array elements
        , typename D >  // Type of the deleter
inline void UniqueArray<T,D>::swap( UniqueArray& ptr )
{
   Pointer tmp( ptr_ );
   ptr_ = ptr.ptr_;
   ptr.ptr_ = tmp;
}
//*************************************************************************************************








//=================================================================================================
//
//  GLOBAL OPERATORS
//
//=================================================================================================

//*************************************************************************************************
/*!\name UniqueArray operators */
//@{
template< typename T1, typename D1, typename T2, typename D2 >
inline bool operator==( const UniqueArray<T1,D1>& lhs, const UniqueArray<T2,D2>& rhs );

template< typename T1, typename D1, typename T2, typename D2 >
inline bool operator!=( const UniqueArray<T1,D1>& lhs, const UniqueArray<T2,D2>& rhs );

template< typename T1, typename D1, typename T2, typename D2 >
inline bool operator<( const UniqueArray<T1,D1>& lhs, const UniqueArray<T2,D2>& rhs );

template< typename T1, typename D1, typename T2, typename D2 >
inline bool operator<=( const UniqueArray<T1,D1>& lhs, const UniqueArray<T2,D2>& rhs );

template< typename T1, typename D1, typename T2, typename D2 >
inline bool operator>( const UniqueArray<T1,D1>& lhs, const UniqueArray<T2,D2>& rhs );

template< typename T1, typename D1, typename T2, typename D2 >
inline bool operator>=( const UniqueArray<T1,D1>& lhs, const UniqueArray<T2,D2>& rhs );

template< typename T, typename D >
inline bool operator==( const UniqueArray<T,D>& ptr, const Null& null );

template< typename T, typename D >
inline bool operator!=( const UniqueArray<T,D>& ptr, const Null& null );

template< typename T, typename D >
inline bool operator<( const UniqueArray<T,D>& ptr, const Null& null );

template< typename T, typename D >
inline bool operator>( const UniqueArray<T,D>& ptr, const Null& null );

template< typename T, typename D >
inline bool operator<=( const UniqueArray<T,D>& ptr, const Null& null );

template< typename T, typename D >
inline bool operator>=( const UniqueArray<T,D>& ptr, const Null& null );

template< typename T, typename D >
inline bool operator==( const Null& null, const UniqueArray<T,D>& ptr );

template< typename T, typename D >
inline bool operator!=( const Null& null, const UniqueArray<T,D>& ptr );

template< typename T, typename D >
inline bool operator<( const Null& null, const UniqueArray<T,D>& ptr );

template< typename T, typename D >
inline bool operator>( const Null& null, const UniqueArray<T,D>& ptr );

template< typename T, typename D >
inline bool operator<=( const Null& null, const UniqueArray<T,D>& ptr );

template< typename T, typename D >
inline bool operator>=( const Null& null, const UniqueArray<T,D>& ptr );

template< typename T, typename D >
inline void swap( UniqueArray<T,D>& a, UniqueArray<T,D>& b ) /* throw() */;
//@}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Equality comparison between two UniqueArray objects.
//
// \param lhs The left-hand side unique array.
// \param rhs The right-hand side unique array.
// \return \a true if the two pointers refer to the same element, \a false if they don't.
*/
template< typename T1    // Resource type of the left-hand side unique array
        , typename D1    // Deleter type of the left-hand side unique array
        , typename T2    // Resource type of the right-hand side unique array
        , typename D2 >  // Deleter type of the right-hand side unique array
inline bool operator==( const UniqueArray<T1,D1>& lhs, const UniqueArray<T2,D2>& rhs )
{
    return lhs.get() == rhs.get();
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Inequality comparison between two UniqueArray objects.
//
// \param lhs The left-hand side unique array.
// \param rhs The right-hand side unique array.
// \return \a true if the two pointers do not refer to the same element, \a false if they do.
*/
template< typename T1    // Resource type of the left-hand side unique array
        , typename D1    // Deleter type of the left-hand side unique array
        , typename T2    // Resource type of the right-hand side unique array
        , typename D2 >  // Deleter type of the right-hand side unique array
inline bool operator!=( const UniqueArray<T1,D1>& lhs, const UniqueArray<T2,D2>& rhs )
{
    return lhs.get() != rhs.get();
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Less-than comparison between two UniqueArray objects.
//
// \param lhs The left-hand side unique array.
// \param rhs The right-hand side unique array.
// \return \a true if the left pointer is less than the right pointer, \a false if not.
*/
template< typename T1    // Resource type of the left-hand side unique array
        , typename D1    // Deleter type of the left-hand side unique array
        , typename T2    // Resource type of the right-hand side unique array
        , typename D2 >  // Deleter type of the right-hand side unique array
inline bool operator<( const UniqueArray<T1,D1>& lhs, const UniqueArray<T2,D2>& rhs )
{
   return lhs.get() < rhs.get();
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Greater-than comparison between two UniqueArray objects.
//
// \param lhs The left-hand side unique array.
// \param rhs The right-hand side unique array.
// \return \a true if the left pointer is greater than the right pointer, \a false if not.
*/
template< typename T1    // Resource type of the left-hand side unique array
        , typename D1    // Deleter type of the left-hand side unique array
        , typename T2    // Resource type of the right-hand side unique array
        , typename D2 >  // Deleter type of the right-hand side unique array
inline bool operator>( const UniqueArray<T1,D1>& lhs, const UniqueArray<T2,D2>& rhs )
{
   return rhs < lhs;
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Less-or-equal-than comparison between two UniqueArray objects.
//
// \param lhs The left-hand side unique array.
// \param rhs The right-hand side unique array.
// \return \a true if the left pointer is less or equal than the right pointer, \a false if not.
*/
template< typename T1    // Resource type of the left-hand side unique array
        , typename D1    // Deleter type of the left-hand side unique array
        , typename T2    // Resource type of the right-hand side unique array
        , typename D2 >  // Deleter type of the right-hand side unique array
inline bool operator<=( const UniqueArray<T1,D1>& lhs, const UniqueArray<T2,D2>& rhs )
{
   return !( rhs < lhs );
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Greater-or-equal-than comparison between two UniqueArray objects.
//
// \param lhs The left-hand side unique array.
// \param rhs The right-hand side unique array.
// \return \a true if the left pointer is greater or equal than the right pointer, \a false if not.
*/
template< typename T1    // Resource type of the left-hand side unique array
        , typename D1    // Deleter type of the left-hand side unique array
        , typename T2    // Resource type of the right-hand side unique array
        , typename D2 >  // Deleter type of the right-hand side unique array
inline bool operator>=( const UniqueArray<T1,D1>& lhs, const UniqueArray<T2,D2>& rhs )
{
   return !( lhs < rhs );
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Equality comparison between a UniqueArray and NULL.
//
// \param ptr The left-hand side unique array.
// \param null The right-hand side NULL pointer.
// \return \a true if the unique array is NULL, \a false if it isn't.
*/
template< typename T    // Resource type of the unique array
        , typename D >  // Deleter type of the unique array
inline bool operator==( const UniqueArray<T,D>& ptr, const Null& null )
{
   return ptr.get() == null;
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Inequality comparison between a UniqueArray and NULL.
//
// \param ptr The left-hand side unique array.
// \param null The right-hand side NULL pointer.
// \return \a true if the unique array is not NULL, \a false if it is.
*/
template< typename T    // Resource type of the unique array
        , typename D >  // Deleter type of the unique array
inline bool operator!=( const UniqueArray<T,D>& ptr, const Null& null )
{
   return !( ptr == null );
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Less-than comparison between a UniqueArray and NULL.
//
// \param ptr The left-hand side unique array.
// \param null The right-hand side NULL pointer.
// \return \a true if the unique array is less than NULL, \a false if not.
*/
template< typename T    // Resource type of the unique array
        , typename D >  // Deleter type of the unique array
inline bool operator<( const UniqueArray<T,D>& ptr, const Null& null )
{
   return ptr.get() < null;
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Greater-than comparison between a UniqueArray and NULL.
//
// \param ptr The left-hand side unique array.
// \param null The right-hand side NULL pointer.
// \return \a true if the unique array is greater than NULL, \a false if not.
*/
template< typename T    // Resource type of the unique array
        , typename D >  // Deleter type of the unique array
inline bool operator>( const UniqueArray<T,D>& ptr, const Null& null )
{
   return ptr.get() > null;
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Less-or-equal-than comparison between a UniqueArray and NULL.
//
// \param ptr The left-hand side unique array.
// \param null The right-hand side NULL pointer.
// \return \a true if the unique array is less or equal than NULL, \a false if not.
*/
template< typename T    // Resource type of the unique array
        , typename D >  // Deleter type of the unique array
inline bool operator<=( const UniqueArray<T,D>& ptr, const Null& null )
{
   return !( ptr > null );
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Greater-or-equal-than comparison between a UniqueArray and NULL.
//
// \param ptr The left-hand side unique array.
// \param null The right-hand side NULL pointer.
// \return \a true if the unique array is greater or equal than NULL, \a false if not.
*/
template< typename T    // Resource type of the unique array
        , typename D >  // Deleter type of the unique array
inline bool operator>=( const UniqueArray<T,D>& ptr, const Null& null )
{
   return !( ptr < null );
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Equality comparison between NULL and a UniqueArray.
//
// \param null The left-hand side NULL pointer.
// \param ptr The right-hand side unique array.
// \return \a true if the unique array is NULL, \a false if it isn't.
*/
template< typename T    // Resource type of the unique array
        , typename D >  // Deleter type of the unique array
inline bool operator==( const Null& null, const UniqueArray<T,D>& ptr )
{
   return ptr == null;
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Inquality comparison between NULL and a UniqueArray.
//
// \param null The left-hand side NULL pointer.
// \param ptr The right-hand side unique array.
// \return \a true if the unique array is not NULL, \a false if it is.
*/
template< typename T    // Resource type of the unique array
        , typename D >  // Deleter type of the unique array
inline bool operator!=( const Null& null, const UniqueArray<T,D>& ptr )
{
   return ptr != null;
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Less-than comparison between NULL and a UniqueArray.
//
// \param null The left-hand side NULL pointer.
// \param ptr The right-hand side unique array.
// \return \a true if NULL is less than the unique array, \a false if not.
*/
template< typename T    // Resource type of the unique array
        , typename D >  // Deleter type of the unique array
inline bool operator<( const Null& null, const UniqueArray<T,D>& ptr )
{
   return ptr > null;
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Greater-than comparison between NULL and a UniqueArray.
//
// \param null The left-hand side NULL pointer.
// \param ptr The right-hand side unique array.
// \return \a true if NULL is greater than the unique array, \a false if not.
*/
template< typename T    // Resource type of the unique array
        , typename D >  // Deleter type of the unique array
inline bool operator>( const Null& null, const UniqueArray<T,D>& ptr )
{
   return ptr < null;
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Less-or-equal-than comparison between NULL and a UniqueArray.
//
// \param null The left-hand side NULL pointer.
// \param ptr The right-hand side unique array.
// \return \a true if NULL is less or equal than the unique array, \a false if not.
*/
template< typename T    // Resource type of the unique array
        , typename D >  // Deleter type of the unique array
inline bool operator<=( const Null& null, const UniqueArray<T,D>& ptr )
{
   return ptr >= null;
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Greater-or-equal-than comparison between NULL and a UniqueArray.
//
// \param null The left-hand side NULL pointer.
// \param ptr The right-hand side unique array.
// \return \a true if NULL is greater or equal than the unique array, \a false if not.
*/
template< typename T    // Resource type of the unique array
        , typename D >  // Deleter type of the unique array
inline bool operator>=( const Null& null, const UniqueArray<T,D>& ptr )
{
   return ptr <= null;
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Swapping the contents of two unique arrays.
//
// \param a The first unique array to be swapped.
// \param b The second unique array to be swapped.
// \return void
// \exception no-throw guarantee.
*/
template< typename T    // Resource type of the unique array
        , typename D >  // Deleter type of the unique array
inline void swap( UniqueArray<T,D>& a, UniqueArray<T,D>& b ) /* throw() */
{
   a.swap( b );
}
//*************************************************************************************************

} // namespace blaze

#endif
