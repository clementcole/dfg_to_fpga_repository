//----------------------------------------------------------------------------
//   ____  ____
//  /   /\/   /
// /___/  \  /   Vendor: Xilinx
// \   \   \/    Version: 6.0
//  \   \        Filename: $RCSfile: run_bitacc_cmodel.c,v $
//  /   /        Date Last Modified: $Date: 2011/06/24 16:06:54 $
// /___/   /\    Date Created:
// \   \  /  \
//  \___\/\___\
//
//Device  : All
//Library : floating_point_v6_1
//Purpose : Example use of bit accurate model for floating_point_v6_1
//Revision: $Revision: 1.6.4.4 $
//
//------------------------------------------------------------------------------
//  (c) Copyright 2011 Xilinx, Inc. All rights reserved.
//
//  This file contains confidential and proprietary information
//  of Xilinx, Inc. and is protected under U.S. and
//  international copyright and other intellectual property
//  laws.
//
//  DISCLAIMER
//  This disclaimer is not a license and does not grant any
//  rights to the materials distributed herewith. Except as
//  otherwise provided in a valid license issued to you by
//  Xilinx, and to the maximum extent permitted by applicable
//  law: (1) THESE MATERIALS ARE MADE AVAILABLE "AS IS" AND
//  WITH ALL FAULTS, AND XILINX HEREBY DISCLAIMS ALL WARRANTIES
//  AND CONDITIONS, EXPRESS, IMPLIED, OR STATUTORY, INCLUDING
//  BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, NON-
//  INFRINGEMENT, OR FITNESS FOR ANY PARTICULAR PURPOSE; and
//  (2) Xilinx shall not be liable (whether in contract or tort,
//  including negligence, or under any other theory of
//  liability) for any loss or damage of any kind or nature
//  related to, arising under or in connection with these
//  materials, including for any direct, or any indirect,
//  special, incidental, or consequential loss or damage
//  (including loss of data, profits, goodwill, or any type of
//  loss or damage suffered as a result of any action brought
//  by a third party) even if such damage or loss was
//  reasonably foreseeable or Xilinx had been advised of the
//  possibility of the same.
//
//  CRITICAL APPLICATIONS
//  Xilinx products are not designed or intended to be fail-
//  safe, or for use in any application requiring fail-safe
//  performance, such as life-support or safety devices or
//  systems, Class III medical devices, nuclear facilities,
//  applications related to the deployment of airbags, or any
//  other applications that could lead to death, personal
//  injury, or severe property or environmental damage
//  (individually and collectively, "Critical
//  Applications"). Customer assumes the sole risk and
//  liability of any use of Xilinx products in Critical
//  Applications, subject only to applicable laws and
//  regulations governing limitations on product liability.
//
//  THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS
//  PART OF THIS FILE AT ALL TIMES.
//-----------------------------------------------------------------------------

#include <stdio.h>
#define _USE_MATH_DEFINES 1 // required for M_E to be found in math.h when compiling on Windows
#include <math.h>
#include <float.h>
#include "floating_point_v6_1_bitacc_cmodel.h" // Must include before GMP and MPFR (see comments in the file for why)
#include "gmp.h"
#include "mpfr.h"

int main()
{

  /* An example algorithm
     Use the Taylor Series for the exponential function to calculate the value of e, the base of natural logarithms
     The Taylor Series for the exponential function e^x is:
       1 + x/1! + x^2/2! + x^3/3! + ... + x^n/n! + ...
     To calculate e, set x = 1:
       e = 1 + 1/1! + 1/2! + 1/3! + ... + 1/n! + ...
     Calculate terms until the accuracy of e no longer improves.
  */

  xip_fpo_exp_t exp_prec, mant_prec;
  // The algorithm will work for any legal combination
  // of values for exp_prec and mant_prec
  exp_prec  = 16;
  mant_prec = 64;
  printf("Using Taylor Series expansion to calculate e, the base of natural logarithms, in %d-bit mantissa precision\n", mant_prec);

  int i, done;
  xip_fpo_t n, fact, one, term, e, e_old;
  xip_fpo_exc_t ex;
  xip_fpo_exp_t exp;
  char * result = 0;
  double e_d, delta, err_get_d, rel_err, rel_err_lim;

  xip_fpo_inits2 (exp_prec, mant_prec, n, fact, one, term, e,
                  e_old, (xip_fpo_ptr) 0);
  xip_fpo_set_ui (one, 1);

  // 0th term
  i = 0;
  xip_fpo_set_ui (fact, 1);
  xip_fpo_set_ui (e, 1);

  // Main iteration loop
  do {

    // Set up this iteration
    i++;
    xip_fpo_set_ui (n, i);
    xip_fpo_set (e_old, e);

    // Calculate the next term: 1/n!
    ex  = xip_fpo_mul (fact, fact, n);  // n!
    ex |= xip_fpo_div (term, one, fact);  // 1/n!
    // Note: an alternative to the preceding line is:
    //   ex |= xip_fpo_rec (term, fact);
    // but this is only possible if using single or double
    // (exp_prec, mant_prec = 8, 24 or 11, 53 respectively)
    // because xip_fpo_rec only supports single and double

    // Calculate the estimate of e
    ex |= xip_fpo_add (e, e, term);

    // Are we done?
    ex |= xip_fpo_equal (&done, e, e_old);

    // Check for exceptions (none should occur)
    if (ex) {
      printf ("Iteration %d: exception occurred: %d\n", i, ex);
      return 1;
    }

    // Print result so far
    result = xip_fpo_get_str (result, &exp, 10, 0, e);
    printf ("After %2d iteration(s), e is 0.%s * 10 ^ %d\n",
            i, result, exp);

  } while (!done);

  // Convert result to C's double precision type
  e_d = xip_fpo_get_d (e);
  printf ("As a C double, e is %.20f\n", e_d);

  // Compare result with the constant M_E from math.h
  delta = fabs(e_d - M_E);
  if (delta == 0) {
    printf("Calculated e at double precision is identical to M_E from math.h\n");
  } else {
    rel_err = delta / M_E;
    printf("Calculated e differs from double precision M_E from math.h by %e, a relative error of %g%%\n", delta, rel_err * 100);
    if (delta <= 2 * DBL_EPSILON) {
      printf("This error is acceptable, due to rounding e to double precision.\n");
    } else {
      rel_err_lim = ldexp(M_E, -(mant_prec-1));
      if (rel_err <= rel_err_lim) {
        printf("This error is acceptable, due to the limited mantissa precision.\n");
      } else {
        printf("ERROR: This error is unacceptably large.\n");
      }
    }
  }

  // Free up memory
  xip_fpo_clears (n, fact, one, term, e, e_old, (xip_fpo_ptr) 0);
  xip_fpo_free_str (result);

  printf("Simulation completed successfully\n");
  return 0;
}
