//=================================================================================================
/*!
//  \file src/mathtest/svectsvecmult/AliasingTest.cpp
//  \brief Source file for the sparse vector/sparse vector outer product aliasing test
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


//*************************************************************************************************
// Includes
//*************************************************************************************************

#include <cstdlib>
#include <iostream>
#include <blazetest/mathtest/svectsvecmult/AliasingTest.h>


namespace blazetest {

namespace mathtest {

namespace svectsvecmult {

//=================================================================================================
//
//  CONSTRUCTORS
//
//=================================================================================================

//*************************************************************************************************
/*!\brief Constructor for the aliasing test class.
//
// \exception std::runtime_error Operation error detected.
*/
AliasingTest::AliasingTest()
   : sa4_   ( 4UL )
   , sb3_   ( 3UL )
   , sc3_   ( 3UL )
   , sA3x4_ ( 3UL, 4UL )
   , sB3x3_ ( 3UL, 3UL )
   , result_()
   , test_  ()
{
   testSVecTSVecMult();
}
//*************************************************************************************************




//=================================================================================================
//
//  TEST FUNCTIONS
//
//=================================================================================================

//*************************************************************************************************
/*!\brief Test of the sparse vector/sparse vector outer product.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs aliasing tests for the sparse vector/sparse vector outer product.
// In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void AliasingTest::testSVecTSVecMult()
{
   //=====================================================================================
   // Outer product
   //=====================================================================================

   // Assignment to left-hand side compound operand
   {
      test_ = "SVecTSVecMult - Assignment to left-hand side compound operand";

      initialize();

      result_ = ( sA3x4_ * sa4_ ) * trans( sb3_ );
      sA3x4_  = ( sA3x4_ * sa4_ ) * trans( sb3_ );

      checkResult( sA3x4_, result_ );
   }

   // Assignment to right-hand side compound operand
   {
      test_ = "SVecTSVecMult - Assignment to right-hand side compound operand";

      initialize();

      result_ = sb3_ * trans( sA3x4_ * sa4_ );
      sA3x4_  = sb3_ * trans( sA3x4_ * sa4_ );

      checkResult( sA3x4_, result_ );
   }


   //=====================================================================================
   // Outer product with addition assignment
   //=====================================================================================

   // Addition assignment to left-hand side compound operand
   {
      test_ = "SVecTSVecMult - Addition assignment to left-hand side compound operand";

      initialize();

      result_ =  sB3x3_;
      result_ += ( sB3x3_ * sb3_ ) * trans( sc3_ );
      sB3x3_  += ( sB3x3_ * sb3_ ) * trans( sc3_ );

      checkResult( sB3x3_, result_ );
   }

   // Addition assignment to right-hand side compound operand
   {
      test_ = "SVecTSVecMult - Addition assignment to right-hand side compound operand";

      initialize();

      result_ =  sB3x3_;
      result_ += sb3_ * trans( sB3x3_ * sc3_ );
      sB3x3_  += sb3_ * trans( sB3x3_ * sc3_ );

      checkResult( sB3x3_, result_ );
   }


   //=====================================================================================
   // Outer product with subtraction assignment
   //=====================================================================================

   // Subtraction assignment to left-hand side compound operand
   {
      test_ = "SVecTSVecMult - Subtraction assignment to left-hand side compound operand";

      initialize();

      result_ =  sB3x3_;
      result_ -= ( sB3x3_ * sb3_ ) * trans( sc3_ );
      sB3x3_  -= ( sB3x3_ * sb3_ ) * trans( sc3_ );

      checkResult( sB3x3_, result_ );
   }

   // Subtraction assignment to right-hand side compound operand
   {
      test_ = "SVecTSVecMult - Subtraction assignment to right-hand side compound operand";

      initialize();

      result_ =  sB3x3_;
      result_ -= sb3_ * trans( sB3x3_ * sc3_ );
      sB3x3_  -= sb3_ * trans( sB3x3_ * sc3_ );

      checkResult( sB3x3_, result_ );
   }


   //=====================================================================================
   // Outer product with multiplication assignment
   //=====================================================================================

   // Multiplication assignment to left-hand side compound operand
   {
      test_ = "SVecTSVecMult - Multiplication assignment to left-hand side compound operand";

      initialize();

      result_ =  sB3x3_;
      result_ *= ( sB3x3_ * sb3_ ) * trans( sc3_ );
      sB3x3_  *= ( sB3x3_ * sb3_ ) * trans( sc3_ );

      checkResult( sB3x3_, result_ );
   }

   // Multiplication assignment to right-hand side compound operand
   {
      test_ = "SVecTSVecMult - Multiplication assignment to right-hand side compound operand";

      initialize();

      result_ =  sB3x3_;
      result_ *= sb3_ * trans( sB3x3_ * sc3_ );
      sB3x3_  *= sb3_ * trans( sB3x3_ * sc3_ );

      checkResult( sB3x3_, result_ );
   }
}
//*************************************************************************************************




//=================================================================================================
//
//  UTILITY FUNCTIONS
//
//=================================================================================================

//*************************************************************************************************
/*!\brief Initialization of all member vectors and matrices.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function initializes all member vectors and matrices to specific predetermined values.
*/
void AliasingTest::initialize()
{
   //=====================================================================================
   // Initialization of the sparse vectors
   //=====================================================================================

   // Initializing the first sparse column vector
   sa4_[0] = -1;
   sa4_[1] =  0;
   sa4_[2] = -3;
   sa4_[3] =  2;

   // Initializing the second sparse column vector
   sb3_[0] = 1;
   sb3_[1] = 2;
   sb3_[2] = 3;

   // Initializing the third sparse column vector
   sc3_[0] = 0;
   sc3_[1] = 2;
   sc3_[2] = 1;


   //=====================================================================================
   // Initialization of the sparse matrices
   //=====================================================================================

   // Initializing the first row-major sparse matrix
   sA3x4_.resize( 3UL, 4UL, false );
   sA3x4_.reset();
   sA3x4_(0,0) = -1;
   sA3x4_(0,2) = -2;
   sA3x4_(1,1) =  2;
   sA3x4_(1,2) = -3;
   sA3x4_(1,3) =  1;
   sA3x4_(2,1) =  1;
   sA3x4_(2,2) =  2;
   sA3x4_(2,3) =  2;

   // Initializing the second row-major sparse matrix
   sB3x3_.resize( 3UL, 3UL, false );
   sB3x3_.reset();
   sB3x3_(0,0) = -1;
   sB3x3_(1,1) =  1;
   sB3x3_(1,1) = -2;
   sB3x3_(1,1) =  2;
   sB3x3_(2,2) = -3;
}
//*************************************************************************************************

} // namespace svectsvecmult

} // namespace mathtest

} // namespace blazetest




//=================================================================================================
//
//  MAIN FUNCTION
//
//=================================================================================================

//*************************************************************************************************
int main()
{
   std::cout << "   Running aliasing test..." << std::endl;

   try
   {
      RUN_SVECTSVECMULT_ALIASING_TEST;
   }
   catch( std::exception& ex ) {
      std::cerr << "\n\n ERROR DETECTED during aliasing test:\n"
                << ex.what() << "\n";
      return EXIT_FAILURE;
   }

   return EXIT_SUCCESS;
}
//*************************************************************************************************