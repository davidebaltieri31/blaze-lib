//=================================================================================================
/*!
//  \file blazetest/mathtest/svectdvecmult/AliasingTest.h
//  \brief Header file for the sparse vector/dense vector outer product aliasing test
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

#ifndef _BLAZETEST_MATHTEST_SVECTDVECMULT_ALIASINGTEST_H_
#define _BLAZETEST_MATHTEST_SVECTDVECMULT_ALIASINGTEST_H_


//*************************************************************************************************
// Includes
//*************************************************************************************************

#include <sstream>
#include <stdexcept>
#include <string>
#include <blaze/math/CompressedMatrix.h>
#include <blaze/math/CompressedVector.h>
#include <blaze/math/DynamicMatrix.h>
#include <blaze/math/DynamicVector.h>
#include <blaze/math/StaticMatrix.h>


namespace blazetest {

namespace mathtest {

namespace svectdvecmult {

//=================================================================================================
//
//  CLASS DEFINITION
//
//=================================================================================================

//*************************************************************************************************
/*!\brief Auxiliary class template for the sparse vector/dense vector outer product aliasing test.
//
// This class represents a test suite for all sparse vector/dense vector outer product aliasing
// tests. It performs a series of runtime tests to assure that all mathematical operations work
// correctly even in the presence of aliasing.
*/
class AliasingTest
{
 private:
   //**Type definitions****************************************************************************
   typedef blaze::DynamicVector<int,blaze::columnVector>     DVec;  //!< Dense column vector type.
   typedef blaze::DynamicMatrix<int,blaze::rowMajor>         DMat;  //!< Row-major dense matrix type.
   typedef blaze::CompressedVector<int,blaze::columnVector>  SVec;  //!< Sparse column vector type.
   typedef blaze::CompressedMatrix<int,blaze::rowMajor>      SMat;  //!< Row-major sparse matrix type.
   typedef blaze::StaticMatrix<int,3UL,3UL,blaze::rowMajor>  RMat;  //!< Result row-major matrix type.
   //**********************************************************************************************

 public:
   //**Constructors********************************************************************************
   /*!\name Constructors */
   //@{
   explicit AliasingTest();
   // No explicitly declared copy constructor.
   //@}
   //**********************************************************************************************

   //**Destructor**********************************************************************************
   // No explicitly declared destructor.
   //**********************************************************************************************

 private:
   //**Test functions******************************************************************************
   /*!\name Test functions */
   //@{
   void testSVecTDVecMult();

   template< typename T1, typename T2 >
   void checkResult( const T1& computedResult, const T2& expectedResult );
   //@}
   //**********************************************************************************************

   //**Utility functions***************************************************************************
   /*!\name Utility functions */
   //@{
   void initialize();
   //@}
   //**********************************************************************************************

   //**Member variables****************************************************************************
   /*!\name Member variables */
   //@{
   DVec da4_;     //!< The first dense column vector.
                  /*!< The 4-dimensional vector is initialized as
                       \f[\left(\begin{array}{*{1}{c}}
                       -1 \\
                        0 \\
                       -3 \\
                        2 \\
                       \end{array}\right)\f]. */
   DVec db3_;     //!< The second dense column vector.
                  /*!< The 3-dimensional vector is initialized as
                       \f[\left(\begin{array}{*{1}{c}}
                       1 \\
                       2 \\
                       3 \\
                       \end{array}\right)\f]. */
   SVec sa4_;     //!< The first sparse column vector.
                  /*!< The 4-dimensional vector is initialized as
                       \f[\left(\begin{array}{*{1}{c}}
                       -1 \\
                        0 \\
                       -3 \\
                        2 \\
                       \end{array}\right)\f]. */
   SVec sb3_;     //!< The second sparse column vector.
                  /*!< The 3-dimensional vector is initialized as
                       \f[\left(\begin{array}{*{1}{c}}
                       1 \\
                       2 \\
                       3 \\
                       \end{array}\right)\f]. */
   DMat dA3x4_;   //!< The first row-major dense matrix.
                  /*!< The \f$ 3 \times 4 \f$ matrix is initialized as
                       \f[\left(\begin{array}{*{3}{c}}
                       -1 & 0 & -2 & 0 \\
                        0 & 2 & -3 & 1 \\
                        0 & 1 &  2 & 2 \\
                       \end{array}\right)\f]. */
   DMat dB3x3_;   //!< The second row-major dense matrix.
                  /*!< The \f$ 3 \times 3 \f$ matrix is initialized as
                       \f[\left(\begin{array}{*{3}{c}}
                       0 & -1 &  0 \\
                       1 & -2 &  2 \\
                       0 &  0 & -3 \\
                       \end{array}\right)\f]. */
   SMat sA3x4_;   //!< The first row-major sparse matrix.
                  /*!< The \f$ 3 \times 4 \f$ matrix is initialized as
                       \f[\left(\begin{array}{*{3}{c}}
                       -1 & 0 & -2 & 0 \\
                        0 & 2 & -3 & 1 \\
                        0 & 1 &  2 & 2 \\
                       \end{array}\right)\f]. */
   SMat sB3x3_;   //!< The second row-major sparse matrix.
                  /*!< The \f$ 3 \times 3 \f$ matrix is initialized as
                       \f[\left(\begin{array}{*{3}{c}}
                       0 & -1 &  0 \\
                       1 & -2 &  2 \\
                       0 &  0 & -3 \\
                       \end{array}\right)\f]. */
   RMat result_;  //!< The dense matrix for the reference result.

   std::string test_;  //!< Label of the currently performed test.
   //@}
   //**********************************************************************************************
};
//*************************************************************************************************




//=================================================================================================
//
//  TEST FUNCTIONS
//
//=================================================================================================

//*************************************************************************************************
/*!\brief Checking and comparing the computed result.
//
// \param computedResult The computed result.
// \param expectedResult The expected result.
// \return void
// \exception std::runtime_error Incorrect result detected.
//
// This function is called after each test case to check and compare the computed result.
// In case the computed and the expected result differ in any way, a \a std::runtime_error
// exception is thrown.
*/
template< typename T1    // Vector type of the computed result
        , typename T2 >  // Vector type of the expected result
void AliasingTest::checkResult( const T1& computedResult, const T2& expectedResult )
{
   if( computedResult != expectedResult ) {
      std::ostringstream oss;
      oss.precision( 20 );
      oss << " Test : " << test_ << "\n"
          << " Error: Incorrect result detected\n"
          << " Details:\n"
          << "   Computed result:\n" << computedResult << "\n"
          << "   Expected result:\n" << expectedResult << "\n";
      throw std::runtime_error( oss.str() );
   }
}
//*************************************************************************************************




//=================================================================================================
//
//  GLOBAL TEST FUNCTIONS
//
//=================================================================================================

//*************************************************************************************************
/*!\brief Testing the sparse vector/dense vector outer product in the presence of aliasing.
//
// \return void
*/
void runTest()
{
   AliasingTest();
}
//*************************************************************************************************




//=================================================================================================
//
//  MACRO DEFINITIONS
//
//=================================================================================================

//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
/*!\brief Macro for the execution of the sparse vector/dense vector outer product aliasing test.
*/
#define RUN_SVECTDVECMULT_ALIASING_TEST \
   blazetest::mathtest::svectdvecmult::runTest()
/*! \endcond */
//*************************************************************************************************

} // namespace svectdvecmult

} // namespace mathtest

} // namespace blazetest

#endif