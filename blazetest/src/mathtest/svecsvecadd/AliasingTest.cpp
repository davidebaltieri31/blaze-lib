//=================================================================================================
/*!
//  \file src/mathtest/svecsvecadd/AliasingTest.cpp
//  \brief Source file for the sparse vector/sparse vector addition aliasing test
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
#include <blazetest/mathtest/svecsvecadd/AliasingTest.h>


namespace blazetest {

namespace mathtest {

namespace svecsvecadd {

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
   testSVecSVecAdd();
}
//*************************************************************************************************




//=================================================================================================
//
//  TEST FUNCTIONS
//
//=================================================================================================

//*************************************************************************************************
/*!\brief Test of the sparse vector/sparse vector addition.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs aliasing tests for the sparse vector/sparse vector addition.
// In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void AliasingTest::testSVecSVecAdd()
{
   //=====================================================================================
   // Addition
   //=====================================================================================

   // Assignment to left-hand side operand
   {
      test_ = "SVecSVecAdd - Assignment to left-hand side operand";

      initialize();

      result_ = sb3_ + sc3_;
      sb3_    = sb3_ + sc3_;

      checkResult( sb3_, result_ );
   }

   // Assignment to left-hand side compound operand
   {
      test_ = "SVecSVecAdd - Assignment to left-hand side compound operand";

      initialize();

      result_ = ( sA3x4_ * sa4_ ) + sc3_;
      sa4_    = ( sA3x4_ * sa4_ ) + sc3_;

      checkResult( sa4_, result_ );
   }

   // Assignment to right-hand side operand
   {
      test_ = "SVecSVecAdd - Assignment to right-hand side operand";

      initialize();

      result_ = sb3_ + sc3_;
      sc3_    = sb3_ + sc3_;

      checkResult( sc3_, result_ );
   }

   // Assignment to right-hand side compound operand
   {
      test_ = "SVecSVecAdd - Assignment to right-hand side compound operand";

      initialize();

      result_ = sb3_ + ( sA3x4_ * sa4_ );
      sa4_    = sb3_ + ( sA3x4_ * sa4_ );

      checkResult( sa4_, result_ );
   }


   //=====================================================================================
   // Addition with addition assignment
   //=====================================================================================

   // Addition assignment to left-hand side operand
   {
      test_ = "SVecSVecAdd - Addition assignment to left-hand side operand";

      initialize();

      result_ =  sb3_;
      result_ += sb3_ + sc3_;
      sb3_    += sb3_ + sc3_;

      checkResult( sb3_, result_ );
   }

   // Addition assignment to left-hand side dense compound operand
   {
      test_ = "SVecSVecAdd - Addition assignment to left-hand side dense compound operand";

      initialize();

      result_ =  sb3_;
      result_ += ( sB3x3_ * sb3_ ) + sc3_;
      sb3_    += ( sB3x3_ * sb3_ ) + sc3_;

      checkResult( sb3_, result_ );
   }

   // Addition assignment to right-hand side operand
   {
      test_ = "SVecSVecAdd - Addition assignment to right-hand side operand";

      initialize();

      result_ =  sc3_;
      result_ += sb3_ + sc3_;
      sc3_    += sb3_ + sc3_;

      checkResult( sc3_, result_ );
   }

   // Addition assignment to right-hand side dense compound operand
   {
      test_ = "SVecSVecAdd - Addition assignment to right-hand side dense compound operand";

      initialize();

      result_ =  sc3_;
      result_ += sb3_ + ( sB3x3_ * sc3_ );
      sc3_    += sb3_ + ( sB3x3_ * sc3_ );

      checkResult( sc3_, result_ );
   }


   //=====================================================================================
   // Addition with subtraction assignment
   //=====================================================================================

   // Subtraction assignment to left-hand side operand
   {
      test_ = "SVecSVecAdd - Subtraction assignment to left-hand side operand";

      initialize();

      result_ =  sb3_;
      result_ -= sb3_ + sc3_;
      sb3_    -= sb3_ + sc3_;

      checkResult( sb3_, result_ );
   }

   // Subtraction assignment to left-hand side dense compound operand
   {
      test_ = "SVecSVecAdd - Subtraction assignment to left-hand side dense compound operand";

      initialize();

      result_ =  sb3_;
      result_ -= ( sB3x3_ * sb3_ ) + sc3_;
      sb3_    -= ( sB3x3_ * sb3_ ) + sc3_;

      checkResult( sb3_, result_ );
   }

   // Subtraction assignment to right-hand side operand
   {
      test_ = "SVecSVecAdd - Subtraction assignment to right-hand side operand";

      initialize();

      result_ =  sc3_;
      result_ -= sb3_ + sc3_;
      sc3_    -= sb3_ + sc3_;

      checkResult( sc3_, result_ );
   }

   // Subtraction assignment to right-hand side dense compound operand
   {
      test_ = "SVecSVecAdd - Subtraction assignment to right-hand side dense compound operand";

      initialize();

      result_ =  sc3_;
      result_ -= sb3_ + ( sB3x3_ * sc3_ );
      sc3_    -= sb3_ + ( sB3x3_ * sc3_ );

      checkResult( sc3_, result_ );
   }


   //=====================================================================================
   // Addition with multiplication assignment
   //=====================================================================================

   // Multiplication assignment to left-hand side operand
   {
      test_ = "SVecSVecAdd - Multiplication assignment to left-hand side operand";

      initialize();

      result_ =  sb3_;
      result_ *= sb3_ + sc3_;
      sb3_    *= sb3_ + sc3_;

      checkResult( sb3_, result_ );
   }

   // Multiplication assignment to left-hand side dense compound operand
   {
      test_ = "SVecSVecAdd - Multiplication assignment to left-hand side dense compound operand";

      initialize();

      result_ =  sb3_;
      result_ *= ( sB3x3_ * sb3_ ) + sc3_;
      sb3_    *= ( sB3x3_ * sb3_ ) + sc3_;

      checkResult( sb3_, result_ );
   }

   // Multiplication assignment to right-hand side operand
   {
      test_ = "SVecSVecAdd - Multiplication assignment to right-hand side operand";

      initialize();

      result_ =  sc3_;
      result_ *= sb3_ + sc3_;
      sc3_    *= sb3_ + sc3_;

      checkResult( sc3_, result_ );
   }

   // Multiplication assignment to right-hand side dense compound operand
   {
      test_ = "SVecSVecAdd - Multiplication assignment to right-hand side dense compound operand";

      initialize();

      result_ =  sc3_;
      result_ *= sb3_ + ( sB3x3_ * sc3_ );
      sc3_    *= sb3_ + ( sB3x3_ * sc3_ );

      checkResult( sc3_, result_ );
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
   sa4_.resize( 4UL, false );
   sa4_.reset();
   sa4_[0] = -1;
   sa4_[2] = -3;
   sa4_[3] =  2;

   // Initializing the second sparse column vector
   sb3_.resize( 3UL, false );
   sb3_.reset();
   sb3_[0] = 1;
   sb3_[1] = 2;
   sb3_[2] = 3;

   // Initializing the third sparse column vector
   sc3_.resize( 3UL, false );
   sc3_.reset();
   sc3_[1] = 2;
   sc3_[2] = 1;


   //=====================================================================================
   // Initialization of the sparse matrices
   //=====================================================================================

   // Initializing the first row-major sparse matrix
   sA3x4_(0,0) = -1;
   sA3x4_(0,2) = -2;
   sA3x4_(1,1) =  2;
   sA3x4_(1,2) = -3;
   sA3x4_(1,3) =  1;
   sA3x4_(2,1) =  1;
   sA3x4_(2,2) =  2;
   sA3x4_(2,3) =  2;

   // Initializing the second row-major sparse matrix
   sB3x3_(0,0) = -1;
   sB3x3_(1,1) =  1;
   sB3x3_(1,1) = -2;
   sB3x3_(1,1) =  2;
   sB3x3_(2,2) = -3;
}
//*************************************************************************************************

} // namespace svecsvecadd

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
      RUN_SVECSVECADD_ALIASING_TEST;
   }
   catch( std::exception& ex ) {
      std::cerr << "\n\n ERROR DETECTED during aliasing test:\n"
                << ex.what() << "\n";
      return EXIT_FAILURE;
   }

   return EXIT_SUCCESS;
}
//*************************************************************************************************