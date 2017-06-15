//----------------------------------------------------------------------------
//   ____  ____
//  /   /\/   /
// /___/  \  /   Vendor: Xilinx
// \   \   \/    Version: 6.1
//  \   \        
//  /   /        
// /___/   /\    
// \   \  /  \
//  \___\/\___\
//
//Device  : All
//Library : floating_point_v6_1
//Purpose : Test bit accurate model for Floating Point Operator: basic test of all functions
//
//------------------------------------------------------------------------------
//  (c) Copyright 2011, 2012 Xilinx, Inc. All rights reserved.
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
// Note: to compile this function as a stand-alone executable, simply rename the
// function from allfns() to main().
//-----------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <math.h>
#include <string.h>
#include "floating_point_v6_1_bitacc_cmodel.h"  // Must include before GMP and MPFR (see comments in the file for why)
#include "gmp.h"
#include "mpfr.h"


////////////////////////////////////////////////////////////////////////
// Utility Functions
////////////////////////////////////////////////////////////////////////

// Compute 1 Unit in the Last Place for the given value - double version
double calculate_ulp(double a)
{
  typedef union
  {
    double f;
    xuint64 bits;
  } dbl2bits;

  dbl2bits x;
  int ee = 0;
  double ulp = 0;

  x.f = a;
  ee = ((x.bits & (xuint64) 0x7FF0000000000000ULL) >> 52) - 1023;  // expected exponent
  ulp = ldexp(1.0, ee-52);

  return ulp;
}

// Compute 1 Unit in the Last Place for the given value - float version
float calculate_ulp(float a)
{
  typedef union
  {
    float f;
    xuint32 bits;
  } flt2bits;

  flt2bits x;
  int ee = 0;
  float ulp = 0;

  x.f = a;
  ee = ((x.bits & 0x7F800000) >> 23) - 127;  // expected exponent
  ulp = ldexpf(1.0f, ee-23);

  return ulp;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Basic test of all functions: stop and return -1 if any test fails; return 0 if all tests pass
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int allfns ()
{

  ////////////////////////////////////////////////////////////////////////
  // Setup
  ////////////////////////////////////////////////////////////////////////
  typedef union {
    double  f;
    xint64 i;
  } snan_d_t;
  snan_d_t snan_d, snan_d_res, snan_d_expected;

  typedef union {
    float  f;
    xint32 i;
  } snan_flt_t;
  snan_flt_t snan_flt, snan_flt_res, snan_flt_expected;

  const float one_flt = 1.0;
  const float zero_flt = 0.0;
  float inf_flt = one_flt / zero_flt;  // infinity (use variables not literals to avoid compiler divide by zero warning)
  const double inf_d = (double) inf_flt;
  const double nan_d = inf_d - inf_d;

  ////////////////////////////////////////////////////////////////////////
  // Information functions
  ////////////////////////////////////////////////////////////////////////

  printf("Testing information functions\n");

  // xip_fpo_get_version
  const char * version_str;
  version_str = xip_fpo_get_version();  // expect "6.1"
  if (strcmp(version_str, "6.1") != 0) {
    printf("ERROR: xip_fpo_get_version: result '%s' does not match expected string '6.1'\n", version_str);
    return -1;
  }
  // Also check that the returned version matches the version defined in floating_point_v6_1_bitacc_cmodel.h
  if (strcmp(version_str, XIP_FPO_VERSION_STRING) != 0) {
    printf("ERROR: xip_fpo_get_version: result '%s' does not match version string defined in floating_point_v6_1_bitacc_cmodel.h '%s'\n", version_str, XIP_FPO_VERSION_STRING);
    return -1;
  }
  char vstr[8];  // build up version string from numeric version #defines in floating_point_v6_1_bitacc_cmodel.h
  if (XIP_FPO_REVISION == 0) {  // if revision is 0, version string does not include it
    sprintf(vstr, "%d.%d", XIP_FPO_VERSION_MAJOR, XIP_FPO_VERSION_MINOR);
  } else {
    sprintf(vstr, "%d.%d.%d", XIP_FPO_VERSION_MAJOR, XIP_FPO_VERSION_MINOR, XIP_FPO_REVISION);
  }
  if (strcmp(version_str, vstr) != 0) {
    printf("ERROR: xip_fpo_get_version: result '%s' does not match version string built up from version numbers defined in floating_point_v6_1_bitacc_cmodel.h '%s'\n", version_str, vstr);
    return -1;
  }


  ////////////////////////////////////////////////////////////////////////
  // Initialization functions: floating point
  ////////////////////////////////////////////////////////////////////////

  printf("Testing initialization functions - floating point\n");
  xip_fpo_t a, b, x, c, d, y, t, u;


  // xip_fpo_init2, xip_fpo_inits2
  xip_fpo_init2(a, 8, 24);  // single precision
  xip_fpo_init2(b, 7, 17);  // custom precision
  xip_fpo_inits2(11, 53, c, d, y, (xip_fpo_ptr) 0);  // double precision
  xip_fpo_init2(t, 4, 4);    // tiny custom precision
  xip_fpo_init2(u, 16, 64);  // huge custom precision

  xip_fpo_init2(x, 1, 122);  // custom precision, illegal values (which are corrected internally)
  xip_fpo_prec_t res_exp_prec  = xip_fpo_get_prec_exp(x);
  xip_fpo_prec_t res_mant_prec = xip_fpo_get_prec_mant(x);
  if (res_exp_prec != 8 || res_mant_prec != 64) {  // these are the corrected values
    printf("ERROR: xip_fpo_init2 did not correct precision as expected: expected exp=8, mant=64, got exp=%d, mant=%d\n", res_exp_prec, res_mant_prec);
    return -1;
  }

  // xip_fpo_set_prec, xip_fpo_clear
  xip_fpo_set_prec(x, 8, 24);  // change to single precision
  xip_fpo_clear(b);
  xip_fpo_init2(b, 8, 24);  // reinitialize to single precision after clearing


  ////////////////////////////////////////////////////////////////////////
  // Initialization functions: fixed point
  ////////////////////////////////////////////////////////////////////////

  printf("Testing initialization functions - fixed point\n");
  xip_fpo_fix_t afix, bfix, xfix, cfix, dfix, yfix, tfix, ufix;

  // xip_fpo_fix_init2, xip_fpo_fix_inits2
  xip_fpo_fix_init2(afix, 32, 0);  // 32-bit integer
  xip_fpo_fix_init2(bfix, 5, 15);  // custom precision
  xip_fpo_fix_inits2(32, 32, cfix, dfix, yfix, (xip_fpo_fix_ptr) 0);  // 64-bit with binary point in the middle
  xip_fpo_fix_init2(tfix, 3, 1);   // tiny custom precision
  xip_fpo_fix_init2(ufix, 64, 0);  // huge custom precision

  xip_fpo_fix_init2(xfix, 0, 149);  // custom precision, illegal values (which are corrected internally)
  xip_fpo_prec_t res_int_prec  = xip_fpo_fix_get_prec_int(xfix);
  xip_fpo_prec_t res_frac_prec = xip_fpo_fix_get_prec_frac(xfix);
  if (res_int_prec != 1 || res_frac_prec != 63) {  // these are the corrected values
    printf("ERROR: xip_fpo_fix_init2 did not correct precision as expected: expected int=1, frac=63, got int=%d, frac=%d\n", res_int_prec, res_frac_prec);
    return -1;
  }

  // xip_fpo_fix_set_prec, xip_fpo_fix_clear
  xip_fpo_fix_set_prec(xfix, 32, 0);  // change to 32-bit integer
  xip_fpo_fix_clear(bfix);
  xip_fpo_fix_init2(bfix, 32, 0);  // reinitialize to 32-bit integer after clearing


  ////////////////////////////////////////////////////////////////////////
  // Assignment and conversion functions: floating point
  ////////////////////////////////////////////////////////////////////////

  printf("Testing assignment and conversion functions - floating point\n");
  xip_fpo_exc_t exc;

  // xip_fpo_set_ui, xip_fpo_get_ui
  // xip_fpo_set_si, xip_fpo_get_si
  // xip_fpo_set
  exc = xip_fpo_set_ui(a, 0);  // a = 0
  if (exc != 0) {
    printf("ERROR: xip_fpo_set_ui: FP(8.24) = 0: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  unsigned long res_ui = xip_fpo_get_ui(a);
  if (res_ui != 0) {
    printf("ERROR: xip_fpo_get_ui: result %u does not match set value 0\n", res_ui);
    return -1;
  }
  exc = xip_fpo_set(b, a);  // b = a (same precision)
  if (exc != 0) {
    printf("ERROR: xip_fpo_set: FP(8.24) = (FP(8.24)) 0: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  res_ui = xip_fpo_get_ui(b);
  if (res_ui != 0) {
    printf("ERROR: xip_fpo_get_ui: result %u does not match expected value 0 after xip_fpo_set\n", res_ui);
    return -1;
  }
  exc = xip_fpo_set_ui(t, 240);  // largest number exactly representable in floating point format exp=4, mant=4
  if (exc != 0) {
    printf("ERROR: xip_fpo_set_ui: FP(4.4) = 240: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  res_ui = xip_fpo_get_ui(t);
  if (res_ui != 240) {
    printf("ERROR: xip_fpo_get_ui: result %u does not match set value 240\n", res_ui);
    return -1;
  }
  exc = xip_fpo_set(x, t);  // FP(8.24) x = FP(4.4) t
  if (exc != 0) {
    printf("ERROR: xip_fpo_set: FP(8.24) = (FP(4.4)) -240: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  res_ui = xip_fpo_get_ui(x);
  if (res_ui != 240) {
    printf("ERROR: xip_fpo_get_ui: result %u does not match expected value 240 after xip_fpo_set\n", res_ui);
    return -1;
  }
  exc = xip_fpo_set_si(t, -240);  // most negative number exactly representable in floating point format exp=4, mant=4
  if (exc != 0) {
    printf("ERROR: xip_fpo_set_si: FP(4.4) = -240: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  long res_si = xip_fpo_get_si(t);
  if (res_si != -240) {
    printf("ERROR: xip_fpo_get_si: result %d does not match set value -240\n", res_si);
    return -1;
  }
  exc = xip_fpo_set_ui(t, 248);  // smallest number that overflows in exp=4, mant=4
  if (exc != 2) {
    printf("ERROR: xip_fpo_set_ui: FP(4.4) = 248: overflow expected (exc=2), but got exc=%d\n", exc);
    return -1;
  }
  res_ui = xip_fpo_get_ui(t);
  if (res_ui != ULONG_MAX) {
    printf("ERROR: xip_fpo_get_ui: result %u does not match expected value %u after overflow\n", res_ui, ULONG_MAX);
    return -1;
  }
  exc = xip_fpo_set_si(t, -248);  // smallest negative number that overflows in exp=4, mant=4
  if (exc != 2) {
    printf("ERROR: xip_fpo_set_si: FP(4.4) = -248: overflow expected (exc=2), but got exc=%d\n", exc);
    return -1;
  }
  res_si = xip_fpo_get_si(t);
  if (res_si != LONG_MIN) {
    printf("ERROR: xip_fpo_get_si: result %d does not match expected value %u after overflow\n", res_si, LONG_MIN);
    return -1;
  }
  exc = xip_fpo_set_ui(u, LONG_MAX);  // very large number into very large type
  if (exc != 0) {
    printf("ERROR: xip_fpo_set_ui: FP(16.64) = %d: no exceptions expected (exc=0), but got exc=%d\n", LONG_MAX, exc);
    return -1;
  }
  res_ui = xip_fpo_get_ui(u);
  if (res_ui != LONG_MAX) {
    printf("ERROR: xip_fpo_get_ui: result %u does not match expected value %u after overflow\n", res_ui, LONG_MAX);
    return -1;
  }
  exc = xip_fpo_set_si(u, LONG_MIN);  // very large negative number into very large type
  if (exc != 0) {
    printf("ERROR: xip_fpo_set_si: FP(16.64) = %d: no exceptions expected (exc=0), but got exc=%d\n", LONG_MIN, exc);
    return -1;
  }
  res_si = xip_fpo_get_si(u);
  if (res_si != LONG_MIN) {
    printf("ERROR: xip_fpo_get_si: result %d does not match expected value %d after overflow\n", res_si, LONG_MIN);
    return -1;
  }
  exc = xip_fpo_set(t, u);  // FP(4.4) = FP(16.64) very large negative number: expect overflow
  if (exc != 2) {
    printf("ERROR: xip_fpo_set: FP(4.4) = (FP(14.64)) %d: overflow expected (exc=2), but got exc=%d\n", exc);
    return -1;
  }
  res_si = xip_fpo_get_si(t);
  if (res_si != LONG_MIN) {  // expected result after conversion from -Infinity
    printf("ERROR: xip_fpo_get_si: result %d does not match expected value %d after overflow\n", res_si, LONG_MIN);
    return -1;
  }

  // xip_fpo_set_uj, xip_fpo_get_uj
  // xip_fpo_set_sj, xip_fpo_get_sj
  uintmax_t expected_uj = ((uintmax_t) 1 << 63) - 1 * 2 + 1;  // largest number that can be stored in a 64-bit uint
  exc = xip_fpo_set_uj(u, expected_uj);  // very large number into very large type
  if (exc != 0) {
    printf("ERROR: xip_fpo_set_uj: FP(16.64) = %llu: no exceptions expected (exc=0), but got exc=%d\n", ((uintmax_t) 1 << 63) - 1 * 2 + 1, exc);
    return -1;
  }
  uintmax_t res_uj = xip_fpo_get_uj(u);
  if (res_uj != expected_uj) {
    printf("ERROR: xip_fpo_get_uj: result %llu does not match set value %llu\n", res_uj, expected_uj);
    return -1;
  }
  intmax_t expected_sj = -((uintmax_t) 1 << 63);  // largest negative number that can be stored in a 64-bit int
  exc = xip_fpo_set_sj(u, expected_sj);  // very large negative number into very large type
  if (exc != 0) {
    printf("ERROR: xip_fpo_set_sj: FP(16.64) = %lld: no exceptions expected (exc=0), but got exc=%d\n", -((uintmax_t) 1 << 63), exc);
    return -1;
  }
  intmax_t res_sj = xip_fpo_get_sj(u);
  if (res_sj != expected_sj) {
    printf("ERROR: xip_fpo_get_sj: result %lld does not match set value %lld\n", res_sj, expected_sj);
    return -1;
  }
  exc = xip_fpo_set_flt(a, 0.1);  // a = 0.1
  if (exc != 0) {
    printf("ERROR: xip_fpo_set_flt: FP(8.24) = 0.1: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }

  // xip_fpo_set_flt, xip_fpo_get_flt
  float res_flt = xip_fpo_get_flt(a);
  float delta_flt = FLT_EPSILON;  // acceptable difference between set and get values due to rounding
  if (fabsf(res_flt - 0.1) > delta_flt) {
    printf("ERROR: xip_fpo_get_flt: result %f does not match set value 0.1\n", res_flt);
    return -1;
  }
  exc = xip_fpo_set_flt(a, inf_flt);  // a = Inf: no exceptions
  if (exc != 0) {
    printf("ERROR: xip_fpo_set_flt: FP(8.24) = Inf: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  res_flt = xip_fpo_get_flt(a);
  if (res_flt != inf_flt) {
    printf("ERROR: xip_fpo_get_flt: result %f does not match set value Infinity\n", res_flt);
    return -1;
  }
  float nan_flt = inf_flt - inf_flt;  // NaN
  exc = xip_fpo_set_flt(a, nan_flt);  // a = NaN: no exceptions
  if (exc != 0) {
    printf("ERROR: xip_fpo_set_flt: FP(8.24) = NaN: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  // Can't use xip_fpo_get_flt(a) and compare to nan_flt, because the comparison NaN == NaN returns false
  exc = xip_fpo_set_flt(t, 248.0);  // expect overflow
  if (exc != 2) {
    printf("ERROR: xip_fpo_set_flt: FP(4.4) = 248.0: expected overflow (exc=2), but got exc=%d\n", exc);
    return -1;
  }
  res_flt = xip_fpo_get_flt(t);
  if (res_flt != inf_flt) {
    printf("ERROR: xip_fpo_get_flt: result %f does not match expected result Infinity following overflow\n", res_flt);
    return -1;
  }
  exc = xip_fpo_set_flt(t, 0.015625);  // smallest number representable in 4.4 format
  if (exc != 0) {
    printf("ERROR: xip_fpo_set_flt: FP(4.4) = 0.015625: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  res_flt = xip_fpo_get_flt(t);
  if (res_flt != 0.015625) {
    printf("ERROR: xip_fpo_get_flt: result %f does not match set value 0.015625\n", res_flt);
    return -1;
  }
  exc = xip_fpo_set_flt(t, 0.014648437);  // expect underflow
  if (exc != 1) {
    printf("ERROR: xip_fpo_set_flt: FP(4.4) = 0.014648437: expected underflow (exc=1), but got exc=%d\n", exc);
    return -1;
  }
  res_flt = xip_fpo_get_flt(t);
  if (res_flt != 0.0) {
    printf("ERROR: xip_fpo_get_flt: result %f does not match expected result 0.0 following underflow\n", res_flt);
    return -1;
  }

  // xip_fpo_set_d, xip_fpo_get_d
  exc = xip_fpo_set_d(t, 0.015625);  // smallest number representable in 4.4 format
  if (exc != 0) {
    printf("ERROR: xip_fpo_set_d: FP(4.4) = 0.015625: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  double delta_d = 0.015625 / 2.0;  // acceptable difference between set and get values in 4.4 format due to rounding
  double res_d = xip_fpo_get_d(t);
  if (fabs(res_d - 0.015625) > delta_d) {
    printf("ERROR: xip_fpo_get_d: result %f does not match set value 0.015625\n", res_d);
    return -1;
  }
  exc = xip_fpo_set_d(u, 1.0e40);  // large number requires double precision into large format, no overflow
  if (exc != 0) {
    printf("ERROR: xip_fpo_set_d: FP(16.64) = 1.0e40: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  delta_d = DBL_EPSILON;  // acceptable difference between set and get values in large format due to rounding
  res_d = xip_fpo_get_d(u);
  if (fabs(res_d - 1.0e40) > delta_d) {
    printf("ERROR: xip_fpo_get_d: result %f does not match set value 1.0e40\n", res_d);
    return -1;
  }

  // xip_fpo_set_z, xip_fpo_get_z
  mpz_t z, res_z;
  mpz_init(z);
  mpz_set_si(z, 240);
  exc = xip_fpo_set_z(t, z);  // largest number exactly representable in floating point format exp=4, mant=4
  if (exc != 0) {
    printf("ERROR: xip_fpo_set_z: FP(4.4) = 240: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  mpz_init(res_z);
  exc = xip_fpo_get_z(res_z, t);
  if (exc != 0) {
    printf("ERROR: xip_fpo_get_z: get 240 from FP(4.4): no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (mpz_cmp(res_z, z) != 0) {
    printf("ERROR: xip_fpo_get_z: result %s does not match set value %s\n", mpz_get_str((char *) 0, 10, res_z), mpz_get_str((char *) 0, 10, z));
    return -1;
  }
  mpz_set_str(z, "340282346638528859811704183484516925440", 10);  // largest finite single-precision value
  exc = xip_fpo_set_z(a, z);  // convert to single precision floating point
  if (exc != 0) {
    printf("ERROR: xip_fpo_set_z: FP(8.24) = 340282346638528859811704183484516925440: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  exc = xip_fpo_get_z(res_z, a);
  if (exc != 0) {
    printf("ERROR: xip_fpo_get_z: get large number from FP(4.4): no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (mpz_cmp(res_z, z) != 0) {
    printf("ERROR: xip_fpo_get_z: result %s does not match set value %s\n", mpz_get_str((char *) 0, 10, res_z), mpz_get_str((char *) 0, 10, z));
    return -1;
  }
  mpz_set_str(z, "340282366920938463463374607431768211456", 10);  // this larger value will overflow
  exc = xip_fpo_set_z(a, z);  // convert to single precision floating point
  if (exc != 2) {
    printf("ERROR: xip_fpo_set_z: FP(8.24) = 340282366920938463463374607431768211456: overflow expected (exc=2), but got exc=%d\n", exc);
    return -1;
  }
  exc = xip_fpo_get_z(res_z, a);  // expect invalid operation as t = Infinity
  if (exc != 4) {
    printf("ERROR: xip_fpo_get_z: get Inf from FP(4.4): invalid operation expected (exc=4), but got exc=%d\n", exc);
    return -1;
  }
  if (mpz_cmp_si(res_z, 0) != 0) {
    printf("ERROR: xip_fpo_get_z: result %s does not match expected value 0 following invalid operation\n", mpz_get_str((char *) 0, 10, res_z));
    return -1;
  }

  // xip_fpo_set_q (there is no xip_fpo_get_q)
  mpq_t q;
  mpq_init(q);
  mpq_set_si(q, 1, 3);  // q = 1/3
  exc = xip_fpo_set_q(a, q);  // convert to single precision floating point
  if (exc != 0) {
    printf("ERROR: xip_fpo_set_q: FP(8.24) = 1/3: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  res_flt = xip_fpo_get_flt(a);  // exact conversion
  delta_flt = FLT_EPSILON;  // acceptable difference between set and get values due to rounding
  float expected_flt = (float) mpq_get_d(q);
  if (fabsf(res_flt - expected_flt) > delta_flt) {
    printf("ERROR: xip_fpo_get_flt: result %f does not match set value %f\n", res_flt, expected_flt);
    return -1;
  }
  mpq_set_str(q, "1/85070591730234615865843651857942052864", 10);  // smallest finite single-precision value
  exc = xip_fpo_set_q(a, q);  // convert to single precision floating point
  if (exc != 0) {
    printf("ERROR: xip_fpo_set_q: FP(8.24) = 1/85070591730234615865843651857942052864: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  res_flt = xip_fpo_get_flt(a);  // exact conversion
  expected_flt = (float) mpq_get_d(q);
  if (fabsf(res_flt - expected_flt) > delta_flt) {
    printf("ERROR: xip_fpo_get_flt: result %f does not match set value %f\n", res_flt, expected_flt);
    return -1;
  }
  mpq_set_str(q, "1/85070601871439417691678863831567695872", 10);  // this smaller value will underflow
  exc = xip_fpo_set_q(a, q);  // convert to single precision floating point
  if (exc != 1) {
    printf("ERROR: xip_fpo_set_q: FP(8.24) = 1/85070601871439417691678863831567695872: underflow expected (exc=1), but got exc=%d\n", exc);
    return -1;
  }
  res_flt = xip_fpo_get_flt(a);  // exact conversion
  expected_flt = (float) mpq_get_d(q);
  if (fabsf(res_flt - expected_flt) > delta_flt) {
    printf("ERROR: xip_fpo_get_flt: result %f does not match set value %f\n", res_flt, expected_flt);
    return -1;
  }

  // xip_fpo_set_f, xip_fpo_get_f
  mpf_t f, res_f;
  mpf_init2(f, 53);  // at least double precision
  mpf_set_d(f, 240);
  exc = xip_fpo_set_f(t, f);  // largest number exactly representable in floating point format exp=4, mant=4
  if (exc != 0) {
    printf("ERROR: xip_fpo_set_f: FP(4.4) = 240: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  mpf_init(res_f);
  exc = xip_fpo_get_f(res_f, t);
  if (exc != 0) {
    printf("ERROR: xip_fpo_get_f: get 240 from FP(4.4): no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (mpf_cmp(res_f, f) != 0) {
    printf("ERROR: xip_fpo_get_f: result %f does not match set value %f\n", mpf_get_d(res_f), mpf_get_d(f));
    return -1;
  }
  mpf_set_d(f, 248.3);  // too large to represent in 4.4 format
  exc = xip_fpo_set_f(t, f);  // expect overflow
  if (exc != 2) {
    printf("ERROR: xip_fpo_set_f: FP(4.4) = 248.3: expected overflow (exc=2), but got exc=%d\n", exc);
    return -1;
  }
  exc = xip_fpo_get_f(res_f, t);  // get Infinity: expect invalid operation
  if (exc != 4) {
    printf("ERROR: xip_fpo_get_f: get Infinity from FP(4.4) following overflow: invalid operation expected (exc=4), but got exc=%d\n", exc);
    return -1;
  }
  if (mpf_cmp_si(res_f, 0) != 0) {  // returned GMP floating point value is zero for conversion from Infinity
    printf("ERROR: xip_fpo_get_f: result %g does not match expected value 0 following overflow\n", mpf_get_d(res_f));
    return -1;
  }
  mpf_set_d(f, 0.014648437);  // too small to represent in 4.4 format
  exc = xip_fpo_set_f(t, f);  // expect underflow
  if (exc != 1) {
    printf("ERROR: xip_fpo_set_f: FP(4.4) = 0.014648437: expected underflow (exc=1), but got exc=%d\n", exc);
    return -1;
  }
  exc = xip_fpo_get_f(res_f, t);
  if (exc != 0) {
    printf("ERROR: xip_fpo_get_f: get from FP(4.4) following underflow: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (mpf_cmp_si(res_f, 0) != 0) {
    printf("ERROR: xip_fpo_get_f: result %f does not match expected value 0 following underflow\n", mpf_get_d(res_f));
    return -1;
  }

  // xip_fpo_set_fr, xip_fpo_get_fr
  mpfr_t fr, res_fr;
  mpfr_init2(fr, 6);  // custom precision, slightly more precise than t (4.4 format)
  mpfr_set_d(fr, 240, MPFR_RNDN);
  exc = xip_fpo_set_fr(t, fr);  // largest number exactly representable in floating point format exp=4, mant=4
  if (exc != 0) {
    printf("ERROR: xip_fpo_set_fr: FP(4.4) = 240: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  mpfr_init2(res_fr, 4);  // same precision as t
  exc = xip_fpo_get_fr(res_fr, t);
  if (exc != 0) {
    printf("ERROR: xip_fpo_get_fr: get 240 from FP(4.4): no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (mpfr_cmp(res_fr, fr) != 0) {
    printf("ERROR: xip_fpo_get_fr: result %f does not match set value %f\n", mpfr_get_d(res_fr, MPFR_RNDN), mpfr_get_d(fr, MPFR_RNDN));
    return -1;
  }
  mpfr_set_d(fr, 248, MPFR_RNDN);  // can be represented in this MPFR variable but not in the less precise variable t
  exc = xip_fpo_set_fr(t, fr);  // expect overflow
  if (exc != 2) {
    printf("ERROR: xip_fpo_set_fr: FP(4.4) = 248: expected overflow (exc=2), but got exc=%d\n", exc);
    return -1;
  }
  exc = xip_fpo_get_fr(res_fr, t);
  if (exc != 0) {
    printf("ERROR: xip_fpo_get_fr: get Inf from FP(4.4): no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if ((mpfr_inf_p(res_fr) != 1) || (mpfr_sgn(res_fr) <= 0)) {  // check for +Inf
    printf("ERROR: xip_fpo_get_fr: result %f does not match expected value +Infinity following overflow\n", mpfr_get_d(res_fr, MPFR_RNDN));
    return -1;
  }
  mpfr_set_inf(fr, 1);  // infinity
  exc = xip_fpo_set_fr(t, fr);  // assignment of infinity is fine
  if (exc != 0) {
    printf("ERROR: xip_fpo_set_fr: FP(4.4) = Inf: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  exc = xip_fpo_get_fr(res_fr, t);
  if (exc != 0) {
    printf("ERROR: xip_fpo_get_fr: get Inf from FP(4.4): no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if ((mpfr_inf_p(res_fr) != 1) || (mpfr_sgn(res_fr) <= 0)) {  // check for +Inf
    printf("ERROR: xip_fpo_get_fr: result %f does not match expected value +Infinity\n", mpfr_get_d(res_fr, MPFR_RNDN));
    return -1;
  }
  mpfr_set_nan(fr);  // NaN
  exc = xip_fpo_set_fr(t, fr);  // assignment of NaN is fine
  if (exc != 0) {
    printf("ERROR: xip_fpo_set_fr: FP(4.4) = Inf: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  exc = xip_fpo_get_fr(res_fr, t);
  if (exc != 0) {
    printf("ERROR: xip_fpo_get_fr: get NaN from FP(4.4): no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (mpfr_nan_p(res_fr) != 1) {  // check for NaN
    printf("ERROR: xip_fpo_get_fr: result %f does not match expected value NaN\n", mpfr_get_d(res_fr, MPFR_RNDN));
    return -1;
  }

  // xip_fpo_set_ui_2exp, xip_fpo_set_si_2exp, xip_fpo_get_d_2exp
  exc = xip_fpo_set_ui_2exp(a, 1, 127);  // a = 1 * 2^127: fits in single precision
  if (exc != 0) {
    printf("ERROR: xip_fpo_set_ui_2exp: FP(8.24) = 1*2^127: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  res_d = xip_fpo_get_d_2exp(&res_si, a);
  delta_d = FLT_EPSILON;  // acceptable difference between set and get values due to rounding in single precision
  if ((fabs(res_d - 0.5) > delta_d) || (res_si != 128)) {  // get_d_2exp return value is in range 0.5 <= d < 1
    printf("ERROR: xip_fpo_get_d_2exp: result %f does not match expected value 0.5 or exponent %d does not match expected exponent 128\n", res_d, res_si);
    return -1;
  }
  exc = xip_fpo_set_ui_2exp(a, 2, 127);  // a = 2 * 2^127: overflows in single precision
  if (exc != 2) {
    printf("ERROR: xip_fpo_set_ui_2exp: FP(8.24) = 2*2^127: overflow expected (exc=2), but got exc=%d\n", exc);
    return -1;
  }
  res_d = xip_fpo_get_d_2exp(&res_si, a);
  if (res_d != inf_d) {  // result after overflow should be infinity; exponent is undefined
    printf("ERROR: xip_fpo_get_d_2exp: result %f does not match expected value Infinity following overflow\n", res_d);
    return -1;
  }
  exc = xip_fpo_set_ui_2exp(a, 1, -127);  // a = 1 * 2^-127: underflows in single precision
  if (exc != 1) {
    printf("ERROR: xip_fpo_set_ui_2exp: FP(8.24) = 1*2^-127: underflow expected (exc=1), but got exc=%d\n", exc);
    return -1;
  }
  res_d = xip_fpo_get_d_2exp(&res_si, a);
  if ((res_d != 0.0) || (res_si != 0)) {  // both return value and exponent should be zero following underflow
    printf("ERROR: xip_fpo_get_d_2exp: result %f does not match expected value 0.0 or exponent %d does not match expected exponent 0 following underflow\n", res_d, res_si);
    return -1;
  }
  exc = xip_fpo_set_si_2exp(a, -1, 127);  // a = -1 * 2^127: fits in single precision
  if (exc != 0) {
    printf("ERROR: xip_fpo_set_si_2exp: FP(8.24) = -1*2^127: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  res_d = xip_fpo_get_d_2exp(&res_si, a);
  if ((fabs(res_d - (-0.5)) > delta_d) || (res_si != 128)) {  // get_d_2exp return value is in range 0.5 <= d < 1
    printf("ERROR: xip_fpo_get_d_2exp: result %f does not match expected value -0.5 or exponent %d does not match expected exponent 128\n", res_d, res_si);
    return -1;
  }
  exc = xip_fpo_set_si_2exp(a, -2, 127);  // a = -2 * 2^127: overflows in single precision
  if (exc != 2) {
    printf("ERROR: xip_fpo_set_si_2exp: FP(8.24) = -2*2^127: overflow expected (exc=2), but got exc=%d\n", exc);
    return -1;
  }
  res_d = xip_fpo_get_d_2exp(&res_si, a);
  if (res_d != -inf_d) {  // result after overflow should be -infinity; exponent is undefined
    printf("ERROR: xip_fpo_get_d_2exp: result %f does not match expected value -Infinity following overflow\n", res_d);
    return -1;
  }
  exc = xip_fpo_set_si_2exp(a, -1, -127);  // a = -1 * 2^-127: underflows in single precision
  if (exc != 1) {
    printf("ERROR: xip_fpo_set_si_2exp: FP(8.24) = -1*2^-127: underflow expected (exc=1), but got exc=%d\n", exc);
    return -1;
  }
  res_d = xip_fpo_get_d_2exp(&res_si, a);
  if ((res_d != -0.0) || (res_si != 0)) {  // both return value and exponent should be zero following underflow
    printf("ERROR: xip_fpo_get_d_2exp: result %f does not match expected value -0.0 or exponent %d does not match expected exponent 0 following underflow\n", res_d, res_si);
    return -1;
  }

  // xip_fpo_set_uj_2exp, xip_fpo_set_sj_2exp
  exc = xip_fpo_set_uj_2exp(c, 1, -1022);  // a = 1 * 2^-1022: fits in double precision
  if (exc != 0) {
    printf("ERROR: xip_fpo_set_uj_2exp: FP(8.24) = 1*2^-1022: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  res_d = xip_fpo_get_d_2exp(&res_si, c);
  if ((fabs(res_d - 0.5) > delta_d) || (res_si != -1021)) {  // get_d_2exp return value is in range 0.5 <= d < 1
    printf("ERROR: xip_fpo_get_d_2exp: result %f does not match expected value 0.5 or exponent %d does not match expected exponent -1021\n", res_d, res_si);
    return -1;
  }
  exc = xip_fpo_set_sj_2exp(c, -1, 1023);  // a = -1 * 2^1023: fits in double precision
  if (exc != 0) {
    printf("ERROR: xip_fpo_set_uj_2exp: FP(8.24) = -1*2^1023: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  res_d = xip_fpo_get_d_2exp(&res_si, c);
  if ((fabs(res_d - (-0.5)) > delta_d) || (res_si != 1024)) {  // get_d_2exp return value is in range 0.5 <= d < 1
    printf("ERROR: xip_fpo_get_d_2exp: result %f does not match expected value -0.5 or exponent %d does not match expected exponent 1024\n", res_d, res_si);
    return -1;
  }

  // xip_fpo_set_str, xip_fpo_get_str, xip_fpo_free_str, xip_fpo_sizeinbase
  exc = xip_fpo_set_str(a, "3", 10);  // normal behavior
  if (exc != 0) {
    printf("ERROR: xip_fpo_set_str: FP(8.24) = 3: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  char * res_str = 0;  // memory for the string is allocated by xip_fpo_get_str
  xip_fpo_exp_t res_exp;
  res_str = xip_fpo_get_str(res_str, &res_exp, 10, 0, a);
  if (res_str == 0) {
    printf("ERROR: xip_fpo_get_str: get 3 from FP(8.24): null pointer returned\n");
    return -1;
  }
  // res_str has an implicit "0." prefix: explicitly add this
  // Note that in the general case, res_str might have a leading minus sign:
  // "0." must go after the minus sign in this case
  const int str_length = 11;  // length of res_str + 3; Windows compiler requires a constant array length for str[]
  char str[str_length];  // enough space for the "0." prefix, the number, and the null terminator
  strcpy(str, "0.");
  strcat(str, res_str);
  res_d = strtod(str, (char **) 0);  // convert string result to double
  double expected_d = 3.0;  // the input value
  long expected_exp = (long) (ceil(log10(expected_d)));  // base-10 exponent
  expected_d = expected_d / pow(10.0, (double) expected_exp);  // base-10 mantissa
  if ((fabs(res_d - expected_d) > delta_d) || (res_exp != expected_exp)) {
    printf("ERROR: xip_fpo_get_str: result %f (converted from string %s, from result %s) does not match expected value %f or exponent %d does not match expected exponent %d\n", res_d, str, res_str, expected_d, res_exp, expected_exp);
    return -1;
  }
  xip_fpo_free_str(res_str);
  exc = xip_fpo_set_str(a, "", 10);  // empty string: invalid operation
  if (exc != 4) {
    printf("ERROR: xip_fpo_set_str: FP(8.24) = empty string: invalid operation expected (exc=4), but got exc=%d\n", exc);
    return -1;
  }
  exc = xip_fpo_set_str(a, "12.381e6", 10);  // normal behavior with decimal point and exponent
  if (exc != 0) {
    printf("ERROR: xip_fpo_set_str: FP(8.24) = 12.381e6: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  int str_size = xip_fpo_sizeinbase(a, 10);  // number of digits that should be expected from xip_fpo_get_str
  str_size = str_size + 2;  // +2 for (possible) minus sign and null terminator
  if (str_size < 7) str_size = 7;  // 7 to allow for -@Inf@ and null terminator
  res_str = (char *) malloc(str_size * sizeof(char));  // allocate memory for string result
  res_str = xip_fpo_get_str(res_str, &res_exp, 10, 0, a);  // get all significant digits
  if ((strcmp(res_str, "123810000") != 0) || (res_exp != 8)) {  // expect [0.]12381e8
    printf("ERROR: xip_fpo_get_str: string result %s does not match expected value [0.]123810000 or exponent %d does not match expected exponent 8\n", res_str, res_exp);
    return -1;
  }
  free(res_str);  // free memory used for string
  char res_str_array[64];  // plenty of pre-allocated space for strings
  res_str = &(res_str_array[0]);  // point to the start of the array
  exc = xip_fpo_set_str(a, "3a.f0249b@-11", 16);  // normal behavior in base 16 with decimal point and base-10 exponent
  if (exc != 0) {
    printf("ERROR: xip_fpo_set_str: FP(8.24) = 3a.f0249b@-11 in base-16: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  res_str = xip_fpo_get_str(res_str, &res_exp, 16, 6, a);  // get 6 significant digits in hex (beyond that were rounded)
  if ((strcmp(res_str, "3af024") != 0) || (res_exp != -9)) {  // expect [0.]3af024@-9
    printf("ERROR: xip_fpo_get_str: string result %s does not match expected value [0.]3af024 or exponent %d does not match expected exponent -9\n", res_str, res_exp);
    return -1;
  }
  exc = xip_fpo_set_str(t, "0", 4);  // normal behavior: zero
  if (exc != 0) {
    printf("ERROR: xip_fpo_set_str: FP(4.4) = 0: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  res_str = xip_fpo_get_str(res_str, &res_exp, 10, 1, t);
  if ((strcmp(res_str, "0") != 0) || (res_exp != 0)) {  // expect zero, exponent is zero
    printf("ERROR: xip_fpo_get_str: string result %s does not match expected value 0 or exponent %d does not match expected exponent 0\n", res_str, res_exp);
    return -1;
  }
  exc = xip_fpo_set_str(a, "-@inf@", 10);  // normal behavior: minus Infinity
  if (exc != 0) {
    printf("ERROR: xip_fpo_set_str: FP(8.24) = -@inf@: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  res_str = xip_fpo_get_str(res_str, &res_exp, 16, 0, a);
  if (strcmp(res_str, "-@Inf@") != 0) {  // expect -Infinity, exponent is not used
    printf("ERROR: xip_fpo_get_str: string result %s does not match expected value -@Inf@\n", res_str);
    return -1;
  }
  exc = xip_fpo_set_str(a, "@nan@", 10);  // normal behavior: NaN
  if (exc != 0) {
    printf("ERROR: xip_fpo_set_str: FP(8.24) = -@nan@: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  res_str = xip_fpo_get_str(res_str, &res_exp, 8, 0, a);
  if (strcmp(res_str, "@NaN@") != 0) {  // expect NaN, exponent is not used
    printf("ERROR: xip_fpo_get_str: string result %s does not match expected value @NaN@\n", res_str);
    return -1;
  }
  exc = xip_fpo_set_str(a, "3.5e38", 10);  // large number, overflows in single precision
  if (exc != 2) {
    printf("ERROR: xip_fpo_set_str: FP(8.24) = 3.5e38: overflow expected (exc=2), but got exc=%d\n", exc);
    return -1;
  }
  res_str = xip_fpo_get_str(res_str, &res_exp, 10, 0, a);
  if (strcmp(res_str, "@Inf@") != 0) {  // expect Infinity, exponent is not used
    printf("ERROR: xip_fpo_get_str: string result %s does not match expected value @Inf@ following overflow\n", res_str);
    return -1;
  }
  exc = xip_fpo_set_str(a, "-1.16e-38", 10);  // small number, underflows in single precision
  if (exc != 1) {
    printf("ERROR: xip_fpo_set_str: FP(8.24) = -1.16e-38: underflow expected (exc=1), but got exc=%d\n", exc);
    return -1;
  }
  res_str = xip_fpo_get_str(res_str, &res_exp, 2, 8, a);  // get 8 digits in base-2
  if (strcmp(res_str, "-00000000") != 0) {  // expect 8 digits of minus zero, exponent is not used
    printf("ERROR: xip_fpo_get_str: string result %s does not match expected value -00000000 following underflow\n", res_str);
    return -1;
  }

  // xip_fpo_set_nan, xip_fpo_set_inf, xip_fpo_set_zero
  xip_fpo_set_nan(a);
  res_str = xip_fpo_get_str(res_str, &res_exp, 10, 0, a);
  if (strcmp(res_str, "@NaN@") != 0) {  // expect NaN, exponent is not used
    printf("ERROR: xip_fpo_get_str: string result %s does not match expected value @NaN@ following xip_fpo_set_nan\n", res_str);
    return -1;
  }
  xip_fpo_set_inf(b, 1);
  res_str = xip_fpo_get_str(res_str, &res_exp, 10, 0, b);
  if (strcmp(res_str, "@Inf@") != 0) {  // expect Infinity, exponent is not used
    printf("ERROR: xip_fpo_get_str: string result %s does not match expected value @Inf@ following xip_fpo_set_inf\n", res_str);
    return -1;
  }
  xip_fpo_set_zero(c, -3);
  res_str = xip_fpo_get_str(res_str, &res_exp, 10, 2, c);  // get 2 digits
  if (strcmp(res_str, "-00") != 0) {  // expect 2 digits of minus zero, exponent is not used
    printf("ERROR: xip_fpo_get_str: string result %s does not match expected value -00 following xip_fpo_set_zero\n", res_str);
    return -1;
  }


  ////////////////////////////////////////////////////////////////////////
  // Assignment and conversion functions: fixed point
  ////////////////////////////////////////////////////////////////////////

  printf("Testing assignment and conversion functions - fixed point\n");

  // xip_fpo_fix_set_ui, xip_fpo_fix_get_ui
  // xip_fpo_fix_set_si, xip_fpo_fix_get_si
  // xip_fpo_fix_set
  exc = xip_fpo_fix_set_ui(afix, 10);  // afix = 10
  if (exc != 0) {
    printf("ERROR: xip_fpo_fix_set_ui: FX(32.0) = 10: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  res_ui = xip_fpo_fix_get_ui(afix);
  if (res_ui != 10) {
    printf("ERROR: xip_fpo_fix_get_ui: result %u does not match set value 10\n", res_ui);
    return -1;
  }
  exc = xip_fpo_fix_set(tfix, bfix);  // tiny tfix = 0 from larger bfix: no exceptions expected
  if (exc != 0) {
    printf("ERROR: xip_fpo_fix_set: FX(3.1) = 0: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  exc = xip_fpo_fix_set(tfix, afix);  // tiny tfix = larger afix: expect overflow
  if (exc != 2) {
    printf("ERROR: xip_fpo_fix_set: FX(3.1) = 10: overflow expected (exc=2), but got exc=%d\n", exc);
    return -1;
  }
  exc = xip_fpo_fix_set_ui(tfix, 3);  // largest number representable in fixed point format int=3, frac=1
  if (exc != 0) {
    printf("ERROR: xip_fpo_fix_set_ui: FX(3.1) = 3: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  res_ui = xip_fpo_fix_get_ui(tfix);
  if (res_ui != 3) {
    printf("ERROR: xip_fpo_fix_get_ui: result %u does not match set value 3\n", res_ui);
    return -1;
  }
  exc = xip_fpo_fix_set_si(tfix, -4);  // largest negative number representable in fixed point format int=3, frac=1
  if (exc != 0) {
    printf("ERROR: xip_fpo_fix_set_si: FX(3.1) = -4: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  res_si = xip_fpo_fix_get_si(tfix);
  if (res_si != -4) {
    printf("ERROR: xip_fpo_fix_get_si: result %d does not match set value -4\n", res_si);
    return -1;
  }
  exc = xip_fpo_fix_set_ui(tfix, 4);  // smallest number that overflows in int=3, frac=1
  if (exc != 2) {
    printf("ERROR: xip_fpo_fix_set_ui: FX(3.1) = 4: overflow expected (exc=2), but got exc=%d\n", exc);
    return -1;
  }
  res_ui = xip_fpo_fix_get_ui(tfix);
  if (res_ui != 4) {  // 4 into 3.1 format overflows to max value = 3.5; 3.5 to unsigned long is rounded to 4
    printf("ERROR: xip_fpo_fix_get_ui: result %u does not match saturated value 4 following overflow\n", res_ui);
    return -1;
  }
  exc = xip_fpo_fix_set_si(tfix, -5);  // smallest negative number that overflows in int=3, frac=1
  if (exc != 2) {
    printf("ERROR: xip_fpo_fix_set_si: FX(3.1) = -5: overflow expected (exc=2), but got exc=%d\n", exc);
    return -1;
  }
  res_si = xip_fpo_fix_get_si(tfix);
  if (res_si != -4) {  // -5 into 3.1 format overflows to min value = -4
    printf("ERROR: xip_fpo_fix_get_si: result %d does not match saturated value -4 following overflow\n", res_si);
    return -1;
  }
  exc = xip_fpo_fix_set_ui(ufix, LONG_MAX);  // very large number into very large type
  if (exc != 0) {
    printf("ERROR: xip_fpo_fix_set_ui: FX(64.0) = %lld: no exceptions expected (exc=0), but got exc=%d\n", LONG_MAX, exc);
    return -1;
  }
  res_ui = xip_fpo_fix_get_ui(ufix);
  if (res_ui != LONG_MAX) {
    printf("ERROR: xip_fpo_fix_get_ui: result %u does not match set value %u\n", res_ui, LONG_MAX);
    return -1;
  }
  exc = xip_fpo_fix_set_si(ufix, LONG_MIN);  // very large negative number into very large type
  if (exc != 0) {
    printf("ERROR: xip_fpo_fix_set_si: FX(64.0) = %lld: no exceptions expected (exc=0), but got exc=%d\n", LONG_MIN, exc);
    return -1;
  }
  res_si = xip_fpo_fix_get_si(ufix);
  if (res_si != LONG_MIN) {
    printf("ERROR: xip_fpo_fix_get_si: result %d does not match set value %d\n", res_si, LONG_MIN);
    return -1;
  }
  exc = xip_fpo_fix_set_ui(afix, (unsigned long) LONG_MAX + 1);  // too large unsigned number into 32-bit type
  // Note: use 32-bit fixed point type because unsigned long may be only 32 bits on a 32-bit platform
  if (exc != 2) {
    printf("ERROR: xip_fpo_fix_set_ui: FX(64.0) = %lld: overflow expected (exc=2), but got exc=%d\n", (unsigned long) LONG_MAX + 1, exc);
    return -1;
  }
  res_ui = xip_fpo_fix_get_ui(afix);
  unsigned long expected_ui = ((unsigned long) 1 << 31) - 1;
  if (res_ui != expected_ui) {  // LONG_MAX+1 into 32.0 format overflows to max value = 2^31-1
    printf("ERROR: xip_fpo_fix_get_ui: result %u does not match saturated value %u following overflow\n", res_ui, LONG_MAX);
    return -1;
  }

  // xip_fpo_fix_set_uj, xip_fpo_fix_get_uj
  // xip_fpo_fix_set_sj, xip_fpo_fix_get_sj
  expected_uj = ((uintmax_t) 1 << 63) - 1;
  exc = xip_fpo_fix_set_uj(ufix, expected_uj);  // very large number into very large type
  if (exc != 0) {
    printf("ERROR: xip_fpo_fix_set_uj: FX(64.0) = %lld: no exceptions expected (exc=0), but got exc=%d\n", ((uintmax_t) 1 << 63) - 1, exc);
    return -1;
  }
  res_uj = xip_fpo_fix_get_uj(ufix);
  if (res_uj != expected_uj) {
    printf("ERROR: xip_fpo_fix_get_uj: result %llu does not match set value %llu\n", res_uj, expected_uj);
    return -1;
  }
  exc = xip_fpo_fix_set_uj(ufix, ((uintmax_t) 1 << 63));  // too large unsigned number into very large type
  if (exc != 2) {
    printf("ERROR: xip_fpo_fix_set_uj: FX(64.0) = %lld: overflow expected (exc=2), but got exc=%d\n", (uintmax_t) 1 << 63, exc);
    return -1;
  }
  expected_uj = ((uintmax_t) 1 << 63) - 1;  // saturated maximum value of 64.0 format
  res_uj = xip_fpo_fix_get_uj(ufix);
  if (res_uj != expected_uj) {
    printf("ERROR: xip_fpo_fix_get_uj: result %llu does not match set value %llu\n", res_uj, expected_uj);
    return -1;
  }
  expected_sj = -((uintmax_t) 1 << 63);  // largest negative number that fits in a 64-bit int
  exc = xip_fpo_fix_set_sj(ufix, expected_sj);  // very large negative number into very large type
  if (exc != 0) {
    printf("ERROR: xip_fpo_fix_set_sj: FX(64.0) = %lld: no exceptions expected (exc=0), but got exc=%d\n", -((uintmax_t) 1 << 63), exc);
    return -1;
  }
  res_sj = xip_fpo_fix_get_sj(ufix);
  if (res_sj != expected_sj) {
    printf("ERROR: xip_fpo_fix_get_sj: result %lld does not match set value %lld\n", res_sj, expected_sj);
    return -1;
  }

  // xip_fpo_fix_set_flt, xip_fpo_fix_get_flt
  exc = xip_fpo_fix_set_flt(afix, 10.2);  // 32-bit integer afix = 10.2
  if (exc != 0) {
    printf("ERROR: xip_fpo_fix_set_flt: FX(32.0) = 10.2: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  delta_flt = 0.5;  // acceptable error due to rounding to afix type (no fractional bits)
  res_flt = xip_fpo_fix_get_flt(afix);
  if (fabsf(res_flt - 10.2) > delta_flt) {
    printf("ERROR: xip_fpo_fix_get_flt: result %f does not match set value 10.2\n", res_flt);
    return -1;
  }
  exc = xip_fpo_fix_set_flt(tfix, 3.5);  // largest number representable in fixed point format int=3, frac=1
  if (exc != 0) {
    printf("ERROR: xip_fpo_fix_set_flt: FX(3.1) = 3.5: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  delta_flt = 0.25;  // acceptable error due to rounding to tfix type (1 fractional bit)
  res_flt = xip_fpo_fix_get_flt(tfix);
  if (fabsf(res_flt - 3.5) > delta_flt) {
    printf("ERROR: xip_fpo_fix_get_flt: result %f does not match set value 3.5\n", res_flt);
    return -1;
  }
  exc = xip_fpo_fix_set_flt(tfix, 3.75);  // will round up to 4 and overflow in 3.1 format
  if (exc != 2) {
    printf("ERROR: xip_fpo_fix_set_flt: FX(3.1) = 3.75: overflow expected (exc=2), but got exc=%d\n", exc);
    return -1;
  }
  res_flt = xip_fpo_fix_get_flt(tfix);
  if (fabsf(res_flt - 3.5) > delta_flt) {  // 3.5 is saturated value of tfix following overflow
    printf("ERROR: xip_fpo_fix_get_flt: result %f does not match saturated value 3.5 following overflow\n", res_flt);
    return -1;
  }
  exc = xip_fpo_fix_set_flt(tfix, 0.25);  // will round down to 0 in 3.1 format, but this is rounding, not underflow
  if (exc != 0) {
    printf("ERROR: xip_fpo_fix_set_flt: FX(3.1) = 0.25: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  res_flt = xip_fpo_fix_get_flt(tfix);
  if (res_flt != 0.0) {  // 0.0 is rounded value of tfix
    printf("ERROR: xip_fpo_fix_get_flt: result %f does not match value 0.0\n", res_flt);
    return -1;
  }
  exc = xip_fpo_fix_set_flt(ufix, inf_flt);  // infinity will overflow (with invalid operation) even in huge format
  if (exc != 6) {
    printf("ERROR: xip_fpo_fix_set_flt: FX(64.0) = Inf: overflow and invalid operation expected (exc=6), but got exc=%d\n", exc);
    return -1;
  }
  delta_flt = 0.5;  // acceptable error due to rounding to ufix type (no fractional bits)
  res_flt = xip_fpo_fix_get_flt(ufix);
  expected_flt = pow(2.0,63) - 1;  // 2^63-1 is saturated value of ufix following overflow
  if (fabsf(res_flt - expected_flt) > delta_flt) {
    printf("ERROR: xip_fpo_fix_get_flt: result %f does not match saturated value %f following overflow\n", res_flt, expected_flt);
    return -1;
  }
  exc = xip_fpo_fix_set_flt(tfix, nan_flt);  // NaN input gives invalid operation exception
  if (exc != 4) {
    printf("ERROR: xip_fpo_fix_set_flt: FX(3.1) = NaN: invalid operation expected (exc=4), but got exc=%d\n", exc);
    return -1;
  }
  delta_flt = 0.25;  // acceptable error due to rounding to tfix type (1 fractional bit)
  res_flt = xip_fpo_fix_get_flt(tfix);
  expected_flt = -pow(2.0,2);  // NaN to fixed point sets the result to the most negative number, -2^2 in 3.1 format
  if (fabsf(res_flt - expected_flt) > delta_flt) {
    printf("ERROR: xip_fpo_fix_get_flt: result %f does not match most negative value %f following set to NaN\n", res_flt, expected_flt);
    return -1;
  }

  // xip_fpo_fix_set_d, xip_fpo_fix_get_d
  exc = xip_fpo_fix_set_d(tfix, 3.5);  // largest number representable in fixed point format int=3, frac=1
  if (exc != 0) {
    printf("ERROR: xip_fpo_fix_set_d: FX(3.1) = 3.5: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  delta_d = 0.25;  // acceptable difference between set and get values in 3.1 format due to rounding
  res_d = xip_fpo_fix_get_d(tfix);
  if (fabs(res_d - 3.5) > delta_d) {
    printf("ERROR: xip_fpo_fix_get_d: result %f does not match set value 3.5\n", res_d);
    return -1;
  }
  exc = xip_fpo_fix_set_d(ufix, 1.0e40);  // large number requiring double precision, will overflow in huge format
  if (exc != 2) {
    printf("ERROR: xip_fpo_fix_set_d: FX(64.0) = 1.0e40: overflow expected (exc=2), but got exc=%d\n", exc);
    return -1;
  }
  delta_d = 1024.0;  // acceptable difference between set and get values in 64.0 format because double precision
                     // has only 53 bits of precision but is dealing with exponent of 63
  res_d = xip_fpo_fix_get_d(ufix);
  expected_d = pow(2.0,63) - 1;  // 2^63-1 is saturated value of ufix following overflow
  if (fabs(res_d - expected_d) > delta_d) {
    printf("ERROR: xip_fpo_fix_get_d: result %f does not match saturated value %f following overflow\n", res_d, expected_d);
    return -1;
  }

  // xip_fpo_fix_set_z, xip_fpo_fix_get_z
  mpz_set_str(z, "9223372036854775807", 10);  // largest number representable in 64.0 fixed point type
  exc = xip_fpo_fix_set_z(ufix, z);  // very large number into very large type
  if (exc != 0) {
    printf("ERROR: xip_fpo_fix_set_z: FX(64.0) = 9223372036854775807: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  exc = xip_fpo_fix_get_z(res_z, ufix);
  if (exc != 0) {
    printf("ERROR: xip_fpo_fix_get_z: get large number from FX(64.0): no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (mpz_cmp(res_z, z) != 0) {
    printf("ERROR: xip_fpo_fix_get_z: result %s does not match set value %s\n", mpz_get_str((char *) 0, 10, res_z), mpz_get_str((char *) 0, 10, z));
    return -1;
  }
  mpz_add_ui(z, z, 1);  // increment by 1, will no longer fit
  exc = xip_fpo_fix_set_z(ufix, z);  // too large number into very large type
  if (exc != 2) {
    printf("ERROR: xip_fpo_fix_set_z: FX(64.0) = 9223372036854775808: overflow expected (exc=2), but got exc=%d\n", exc);
    return -1;
  }
  exc = xip_fpo_fix_get_z(res_z, ufix);
  if (exc != 0) {
    printf("ERROR: xip_fpo_fix_get_z: get saturated number from FX(64.0): no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  mpz_sub_ui(z, z, 1);  // decrement by 1 to give expected saturated value of ufix following overflow
  if (mpz_cmp(res_z, z) != 0) {
    printf("ERROR: xip_fpo_fix_get_z: result %s does not match saturated value %s following overflow\n", mpz_get_str((char *) 0, 10, res_z), mpz_get_str((char *) 0, 10, z));
    return -1;
  }
  xip_fpo_fix_set_d(tfix, 0.5);  // can be stored exactly
  exc = xip_fpo_fix_get_z(res_z, tfix);  // will round to zero, but this is not underflow
  if (exc != 0) {
    printf("ERROR: xip_fpo_fix_get_z: get 0.5 from FX(64.0): no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (mpz_cmp_si(res_z, 0) != 0) {  // result should be zero
    printf("ERROR: xip_fpo_fix_get_z: result %s does not match expected value 0\n", mpz_get_str((char *) 0, 10, res_z));
    return -1;
  }
  // xip_fpo_fix_set_q (there is no xip_fpo_fix_get_q)
  mpq_set_ui(q, 7, 2);  // q = 7/2
  exc = xip_fpo_fix_set_q(tfix, q);  // largest number representable in fixed point format int=3, frac=1
  if (exc != 0) {
    printf("ERROR: xip_fpo_fix_set_q: FX(3.1) = 7/2: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  delta_d = 0.25;  // acceptable difference between set and get values in 3.1 format due to rounding
  res_d = xip_fpo_fix_get_d(tfix);
  if (fabs(res_d - 3.5) > delta_d) {
    printf("ERROR: xip_fpo_fix_get_d: result %f does not match set value 3.5\n", res_d);
    return -1;
  }
  mpq_set_ui(q, 1, 4);  // q = 1/4
  exc = xip_fpo_fix_set_q(tfix, q);  // too small for format int=3, frac=1, will round to zero (this is not underflow)
  if (exc != 0) {
    printf("ERROR: xip_fpo_fix_set_q: FX(3.1) = 1/4: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  res_d = xip_fpo_fix_get_d(tfix);
  if (fabs(res_d - 0.0) > delta_d) {
    printf("ERROR: xip_fpo_fix_get_d: result %f does not match expected value 0.0 after underflow\n", res_d);
    return -1;
  }
  // xip_fpo_fix_set_f, xip_fpo_fix_get_f
  mpf_set_d(f, 3.5);
  exc = xip_fpo_fix_set_f(tfix, f);  // largest number representable in fixed point format int=3, frac=1
  if (exc != 0) {
    printf("ERROR: xip_fpo_fix_set_f: FX(3.1) = 3.5: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  exc = xip_fpo_fix_get_f(res_f, tfix);
  if (exc != 0) {
    printf("ERROR: xip_fpo_fix_get_f: get 3.5 from FX(3.1): no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (mpf_cmp(res_f, f) != 0) {
    printf("ERROR: xip_fpo_fix_get_f: result %f does not match expected value %f\n", mpf_get_d(res_f), mpf_get_d(f));
    return -1;
  }
  mpf_set_d(f, 0.5);
  exc = xip_fpo_fix_set_f(ufix, f);  // 0.5 into format with no fractional bits will round to 0 (this is not underflow)
  if (exc != 0) {
    printf("ERROR: xip_fpo_fix_set_f: FX(64.0) = 0.5: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  exc = xip_fpo_fix_get_f(res_f, ufix);
  if (exc != 0) {
    printf("ERROR: xip_fpo_fix_get_f: get 0 from FX(3.1): no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (mpf_cmp_si(res_f, 0) != 0) {
    printf("ERROR: xip_fpo_fix_get_f: result %f does not match expected value 0\n", mpf_get_d(res_f));
    return -1;
  }
  // xip_fpo_fix_set_fr, xip_fpo_fix_get_fr
  mpfr_set_d(fr, 3.5, MPFR_RNDN);
  exc = xip_fpo_fix_set_fr(tfix, fr);  // largest number representable in fixed point format int=3, frac=1
  if (exc != 0) {
    printf("ERROR: xip_fpo_fix_set_fr: FX(3.1) = 3.5: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  mpfr_set_prec(res_fr, 6);  // same precision as input variable fr
  exc = xip_fpo_fix_get_fr(res_fr, tfix);
  if (exc != 0) {
    printf("ERROR: xip_fpo_fix_get_fr: get 3.5 from FX(3.1): no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (mpfr_cmp(res_fr, fr) != 0) {
    printf("ERROR: xip_fpo_fix_get_fr: result %f does not match set value %f\n", mpfr_get_d(res_fr, MPFR_RNDN), mpfr_get_d(fr, MPFR_RNDN));
    return -1;
  }
  mpfr_set_prec(fr, 24);  // increase precision for rounding test
  mpfr_set_d(fr, -1.75, MPFR_RNDN);
  exc = xip_fpo_fix_set_fr(tfix, fr);  // check for correct rounding to fixed point format int=3, frac=1
  if (exc != 0) {
    printf("ERROR: xip_fpo_fix_set_fr: FX(3.1) = -1.75: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  mpfr_set_prec(res_fr, 24);  // same precision as input variable fr
  exc = xip_fpo_fix_get_fr(res_fr, tfix);
  if (exc != 0) {
    printf("ERROR: xip_fpo_fix_get_fr: get -1.75 from FX(3.1): no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  mpfr_set_d(fr, -2.0, MPFR_RNDN);  // expected value of tfix after rounding
  if (mpfr_cmp(res_fr, fr) != 0) {
    printf("ERROR: xip_fpo_fix_get_fr: result %f does not match set value %f\n", mpfr_get_d(res_fr, MPFR_RNDN), mpfr_get_d(fr, MPFR_RNDN));
    return -1;
  }
  mpfr_set_inf(fr, 1);  // infinity
  exc = xip_fpo_fix_set_fr(ufix, fr);  // assignment of infinity results in overflow and invalid operation
  if (exc != 6) {
    printf("ERROR: xip_fpo_fix_set_fr: FX(64.0) = Inf: overflow and invalid operation expected (exc=6), but got exc=%d\n", exc);
    return -1;
  }
  exc = xip_fpo_fix_get_fr(res_fr, ufix);
  if (exc != 0) {
    printf("ERROR: xip_fpo_fix_get_fr: get saturated value from FX(64.0) following overflow: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  xint64 expected_i64 = (xint64) (((xuint64) 1 << 63) - 1);  // 2^63-1 is saturated value of ufix following overflow
  xint64 res_fr_i64 = mpfr_get_sj(res_fr, MPFR_RNDN);  // MPFR result of get_fr in xint64_t type
  xint64 delta_i64 = 1;  // expected rounding error after conversion to MPFR type
  xint64 diff_i64 = res_fr_i64 - expected_i64;
  if (diff_i64 < 0) diff_i64 = -diff_i64;  // no abs() function for xint64 type, use this expression instead
  if (diff_i64 > delta_i64) {
    printf("ERROR: xip_fpo_fix_get_fr: result %f does not match saturated value %lld following overflow\n", mpfr_get_d(res_fr, MPFR_RNDN), expected_i64);
    return -1;
  }
  mpfr_set_nan(fr);  // NaN
  exc = xip_fpo_fix_set_fr(ufix, fr);  // assignment of NaN results in invalid operation
  if (exc != 4) {
    printf("ERROR: xip_fpo_fix_set_fr: FX(64.0) = NaN: invalid operation expected (exc=4), but got exc=%d\n", exc);
    return -1;
  }
  exc = xip_fpo_fix_get_fr(res_fr, ufix);
  if (exc != 0) {
    printf("ERROR: xip_fpo_fix_get_fr: get saturated value from FX(64.0) following invalid operation: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  expected_i64 = -expected_i64 - 1;  // -2^63 is negative saturated value of ufix following invalid operation
  res_fr_i64 = mpfr_get_sj(res_fr, MPFR_RNDN);  // MPFR result of get_fr in xint64 type
  delta_i64 = 0;  // expected rounding error after conversion to MPFR type
  diff_i64 = res_fr_i64 - expected_i64;
  if (diff_i64 < 0) diff_i64 = -diff_i64;  // no abs() function for xint64 type, use this expression instead
  if (diff_i64 > delta_i64) {
    printf("ERROR: xip_fpo_fix_get_fr: result %f does not match negative saturated value %lld following invalid operation\n", mpfr_get_d(res_fr, MPFR_RNDN), expected_i64);
    return -1;
  }
  // xip_fpo_fix_set_str, xip_fpo_fix_get_str, xip_fpo_fix_free_str, xip_fpo_fix_sizeinbase
  exc = xip_fpo_fix_set_str(afix, "3", 10);  // normal behavior
  if (exc != 0) {
    printf("ERROR: xip_fpo_fix_set_str: FX(32.0) = 3: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  char * res_fix_str = 0;  // memory for the string is allocated by xip_fpo_fix_get_str
  res_fix_str = xip_fpo_fix_get_str(res_fix_str, 10, afix);
  if (res_fix_str == 0) {
    printf("ERROR: xip_fpo_fix_get_str: get 3 from FX(32.0): null pointer returned\n");
    return -1;
  }
  if (strcmp(res_fix_str, "3") != 0) {
    printf("ERROR: xip_fpo_fix_get_str: result %s does not match expected value 3\n", res_fix_str);
    return -1;
  }
  xip_fpo_fix_free_str(res_fix_str);
  res_fix_str = 0;
  exc = xip_fpo_fix_set_str(afix, "", 10);  // empty string: invalid operation
  if (exc != 4) {
    printf("ERROR: xip_fpo_fix_set_str: FX(32.0) = empty string: invalid operation expected (exc=4), but got exc=%d\n", exc);
    return -1;
  }
  exc = xip_fpo_fix_set_str(cfix, "-12.375", 10);  // normal behavior with decimal point
  if (exc != 0) {
    printf("ERROR: xip_fpo_fix_set_str: FX(32.32) = -12.375: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  str_size = xip_fpo_fix_sizeinbase(cfix, 10);
  str_size = str_size + 2;  // +2 for minus sign and null terminator
  res_fix_str = (char *) malloc(str_size * sizeof(char));  // allocate memory for string result
  res_fix_str = xip_fpo_fix_get_str(res_fix_str, 10, cfix);  // using pre-allocated string
  if (res_fix_str == 0) {
    printf("ERROR: xip_fpo_fix_get_str: get -12.375 from FX(32.32): null pointer returned\n");
    return -1;
  }
  if (strcmp(res_fix_str, "-12.375") != 0) {
    printf("ERROR: xip_fpo_fix_get_str: string result %s does not match expected value -12.375\n", res_fix_str);
    return -1;
  }
  free(res_fix_str);  // free memory used for string
  res_fix_str = 0;
  exc = xip_fpo_fix_set_str(cfix, "3.90625e-3", 10);  // normal behavior with decimal point and exponent
  if (exc != 0) {
    printf("ERROR: xip_fpo_fix_set_str: FX(32.32) = 3.90625e-3: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  res_fix_str = xip_fpo_fix_get_str(res_fix_str, 10, cfix);
  if (res_fix_str == 0) {
    printf("ERROR: xip_fpo_fix_get_str: get 0.00390625 from FX(32.32): null pointer returned\n");
    return -1;
  }
  if (strcmp(res_fix_str, "0.00390625") != 0) {
    printf("ERROR: xip_fpo_fix_get_str: string result %s does not match expected value 0.00390625\n", res_fix_str);
    return -1;
  }
  xip_fpo_fix_free_str(res_fix_str);
  res_fix_str = 0;
  exc = xip_fpo_fix_set_str(cfix, "-3a.f0249b@3", 16);  // base 16 with decimal point and base-10 exponent
  if (exc != 0) {
    printf("ERROR: xip_fpo_fix_set_str: FX(32.32) = -3a.f0249b@3 in base-16: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  res_fix_str = xip_fpo_fix_get_str(res_fix_str, 16, cfix);
  if (res_fix_str == 0) {
    printf("ERROR: xip_fpo_fix_get_str: get -3af02.49b from FX(32.32): null pointer returned\n");
    return -1;
  }
  if (strcmp(res_fix_str, "-3af02.49b") != 0) {
    printf("ERROR: xip_fpo_fix_get_str: string result %s does not match expected value -3af02.49b\n", res_fix_str);
    return -1;
  }
  xip_fpo_fix_free_str(res_fix_str);
  char res_fix_str_array[64];  // plenty of pre-allocated space for strings
  res_fix_str = &(res_fix_str_array[0]);  // point to the start of the array
  exc = xip_fpo_fix_set_str(tfix, "@inf@", 27);  // Infinity: expect overflow and invalid operation
  if (exc != 6) {
    printf("ERROR: xip_fpo_fix_set_str: FX(3.1) = Infinity: expected overflow and invalid operation (exc=6), but got exc=%d\n", exc);
    return -1;
  }
  res_fix_str = xip_fpo_fix_get_str(res_fix_str, 10, tfix);
  if (res_fix_str == 0) {
    printf("ERROR: xip_fpo_fix_get_str: get saturated value following overflow from FX(3.1): null pointer returned\n");
    return -1;
  }
  if (strcmp(res_fix_str, "3.5") != 0) {
    printf("ERROR: xip_fpo_fix_get_str: string result %s does not match expected value 3.5 following overflow\n", res_fix_str);
    return -1;
  }
  exc = xip_fpo_fix_set_str(tfix, "-0.1", 10);  // small number, rounded to 0 in 3.5 precision (but no underflow)
  if (exc != 0) {
    printf("ERROR: xip_fpo_fix_set_str: FX(3.1) = -0.1: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  res_fix_str = xip_fpo_fix_get_str(res_fix_str, 10, tfix);
  if (res_fix_str == 0) {
    printf("ERROR: xip_fpo_fix_get_str: get 0 from FX(3.1): null pointer returned\n");
    return -1;
  }
  if (strcmp(res_fix_str, "0") != 0) {
    printf("ERROR: xip_fpo_fix_get_str: string result %s does not match expected value 0\n", res_fix_str);
    return -1;
  }


  ////////////////////////////////////////////////////////////////////////
  // Operation functions: add
  ////////////////////////////////////////////////////////////////////////

  printf("Testing operation functions: add\n");

  // xip_fpo_add
  xip_fpo_set_flt(a, 3.0);
  xip_fpo_set_flt(b, 0.5);
  exc = xip_fpo_add(x, a, b);  // normal operation: 3.0 + 0.5
  if (exc != 0) {
    printf("ERROR: xip_fpo_add: FP(8.24) = 3.0 + 0.5: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  res_flt = xip_fpo_get_flt(x);
  delta_flt = FLT_EPSILON;  // acceptable difference between result and expected values due to rounding
  if (fabsf(res_flt - 3.5) > delta_flt) {
    printf("ERROR: xip_fpo_add: FP(8.24) = 3.0 + 0.5: result %f does not match expected value 3.5\n", res_flt);
    return -1;
  }
  exc = xip_fpo_add(x, a, c);  // inputs are not the same precision: operation not supported
  if (exc != 16) {
    printf("ERROR: xip_fpo_add: FP(8.24) = FP(8.24) + FP(11.53): expected operation not supported (exc=16), but got exc=%d\n", exc);
    return -1;
  }
  xip_fpo_set_flt(t, 240);  // largest number representable in 4.4 format
  exc = xip_fpo_add(t, t, t);  // sum of two large numbers: expect overflow
  if (exc != 2) {
    printf("ERROR: xip_fpo_add: FP(4.4) = 240 + 240: expected overflow (exc=2), but got exc=%d\n", exc);
    return -1;
  }
  res_flt = xip_fpo_get_flt(t);
  if (res_flt != inf_flt) {
    printf("ERROR: xip_fpo_add: FP(4.4) = 240 + 240: result %f does not match expected result Infinity following overflow\n", res_flt);
    return -1;
  }
  xip_fpo_set_flt(a, 1.5e-38);
  xip_fpo_set_flt(b, -1.2e-38);
  exc = xip_fpo_add(x, a, b);  // sum of two different very small numbers, one positive, one negative: expect underflow
  if (exc != 1) {
    printf("ERROR: xip_fpo_add: FP(8.24) = 1.2e-38 + -1.3e-38: expected underflow (exc=1), but got exc=%d\n", exc);
    return -1;
  }
  res_flt = xip_fpo_get_flt(x);
  if (res_flt != 0.0) {
    printf("ERROR: xip_fpo_add: FP(8.24) = 1.2e-38 + -1.3e-38: result %f does not match expected result 0.0 following underflow\n", res_flt);
    return -1;
  }
  xip_fpo_set_inf(c, 1);   // +Inf
  xip_fpo_set_inf(d, -1);  // -Inf
  exc = xip_fpo_add(y, c, d);  // sum of differently signed infinities: expect invalid operation
  if (exc != 4) {
    printf("ERROR: xip_fpo_add: FP(11.53) = +Inf + -Inf: expected invalid operation (exc=4), but got exc=%d\n", exc);
    return -1;
  }
  // Can't use xip_fpo_get_flt(y) and compare to nan_flt, because the comparison NaN == NaN returns false
  // Use xip_fpo_get_str instead
  res_str = xip_fpo_get_str(res_str, &res_exp, 8, 0, y);
  if (strcmp(res_str, "@NaN@") != 0) {  // expect NaN, exponent is not used
    printf("ERROR: xip_fpo_add: FP(11.53) = +Inf + -Inf: result %s does not match expected result @NaN@ following invalid operation\n", res_str);
    return -1;
  }
  xip_fpo_set_flt(a, 1.3e7);
  xip_fpo_set_nan(b);
  exc = xip_fpo_add(x, a, b);  // one input NaN: expect NaN output but no exceptions (only quiet NaNs supported)
  if (exc != 0) {
    printf("ERROR: xip_fpo_add: FP(8.24) = 1.3e7 + NaN: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  // Can't use xip_fpo_get_flt(x) and compare to nan_flt, because the comparison NaN == NaN returns false
  // Use xip_fpo_get_str instead
  res_str = xip_fpo_get_str(res_str, &res_exp, 8, 0, x);
  if (strcmp(res_str, "@NaN@") != 0) {  // expect NaN, exponent is not used
    printf("ERROR: xip_fpo_add: FP(8.24) = 1.3e7 + NaN: result %s does not match expected result @NaN@ following operation with NaN input\n", res_str);
    return -1;
  }

  // xip_fpo_add_flt, xip_fpo_add_d
  exc = xip_fpo_add_flt(&res_flt, (float) 17.6, (float) -3.2);  // normal operation
  if (exc != 0) {
    printf("ERROR: xip_fpo_add_flt: float = 17.6 + -3.2: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  delta_flt = FLT_EPSILON;  // acceptable difference between result and expected values due to rounding
  expected_flt = (float) 17.6 + (float) -3.2;
  if (fabsf(res_flt - expected_flt) > delta_flt) {
    printf("ERROR: xip_fpo_add_flt: float = 17.6 + -3.2: result %f does not match expected value %f\n", res_flt, expected_flt);
    return -1;
  }
  exc = xip_fpo_add_flt(&res_flt, (float) 3.0e38, (float) 1.4e38);  // two very large numbers, expect overflow
  if (exc != 2) {
    printf("ERROR: xip_fpo_add_flt: float = 3.0e38 + 1.4e38: expected overflow (exc=2), but got exc=%d\n", exc);
    return -1;
  }
  if (res_flt != inf_flt) {
    printf("ERROR: xip_fpo_add_flt: float = 3.0e38 + 1.4e38: result %f does not match expected value Infinity following overflow\n", res_flt);
    return -1;
  }
  exc = xip_fpo_add_d(&res_d, (double) 243.56079356, (double) 141.045956204);  // normal operation
  if (exc != 0) {
    printf("ERROR: xip_fpo_add_d: double = 243.56079356 + 141.045956204: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  delta_d = DBL_EPSILON;  // acceptable difference between result and expected values due to rounding
  expected_d = (double) 243.56079356 + (double) 141.045956204;
  if (fabs(res_d - expected_d) > delta_d) {
    printf("ERROR: xip_fpo_add_d: double = 243.56079356 + 141.045956204: result %f does not match expected value %f\n", res_d, expected_d);
    return -1;
  }
  exc = xip_fpo_add_d(&res_d, (double) 2.3e-308, (double) -2.6e-308);  // two very small numbers, expect underflow
  if (exc != 1) {
    printf("ERROR: xip_fpo_add_d: double = 2.3e-308 + -2.6e-308: expected underflow (exc=1), but got exc=%d\n", exc);
    return -1;
  }
  expected_d = (double) 2.3e-308 + (double) -2.6e-308;
  if (fabs(res_d - expected_d) > delta_d) {
    printf("ERROR: xip_fpo_add_d: double = 2.3e-308 + -2.6e-308: result %f does not match expected value %f\n", res_d, expected_d);
    return -1;
  }


  ////////////////////////////////////////////////////////////////////////
  // Operation functions: subtract
  ////////////////////////////////////////////////////////////////////////

  printf("Testing operation functions: subtract\n");

  // xip_fpo_sub
  xip_fpo_set_flt(a, 0.5);
  xip_fpo_set_flt(b, 4.0);
  exc = xip_fpo_sub(x, a, b);  // normal operation: 3.0 - 0.5
  if (exc != 0) {
    printf("ERROR: xip_fpo_sub: FP(8.24) = 0.5 - 4.0: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  res_flt = xip_fpo_get_flt(x);
  delta_flt = FLT_EPSILON;  // acceptable difference between result and expected values due to rounding
  if (fabsf(res_flt - (-3.5)) > delta_flt) {
    printf("ERROR: xip_fpo_sub: FP(8.24) = 0.5 - 4.0: result %f does not match expected value -3.5\n", res_flt);
    return -1;
  }
  exc = xip_fpo_sub(u, a, a);  // inputs are not the same precision as output: operation not supported
  if (exc != 16) {
    printf("ERROR: xip_fpo_sub: FP(16.64) = FP(8.24) - FP(8.24): expected operation not supported (exc=16), but got exc=%d\n", exc);
    return -1;
  }
  xip_fpo_set_flt(a, 2.5e38);
  xip_fpo_set_flt(b, -3.0e38);
  exc = xip_fpo_sub(a, a, b);  // difference of two large numbers of opposite sign: expect overflow
  if (exc != 2) {
    printf("ERROR: xip_fpo_sub: FP(8.24) = 2.5e38 - -3.0e38: expected overflow (exc=2), but got exc=%d\n", exc);
    return -1;
  }
  res_flt = xip_fpo_get_flt(a);
  if (res_flt != inf_flt) {
    printf("ERROR: xip_fpo_sub: FP(8.24) = 2.5e38 - -3.0e38: result %f does not match expected result Infinity following overflow\n", res_flt);
    return -1;
  }
  xip_fpo_set_si_2exp(a, 1, -126);  // smallest number representable in single precision (1.18e-38)
  exc = xip_fpo_set_si_2exp(b, 3, -127);  // 1.5 times the value of a (1.76e-38)
  exc = xip_fpo_sub(x, a, b);  // difference of two very small numbers: expect underflow
  if (exc != 1) {
    printf("ERROR: xip_fpo_sub: FP(4.4) = 1.18e-38 - 1.76e-38: expected underflow (exc=1), but got exc=%d\n", exc);
    return -1;
  }
  res_flt = xip_fpo_get_flt(x);
  if (res_flt != -0.0) {
    printf("ERROR: xip_fpo_sub: FP(4.4) = 1.18e-38 - 1.76e-38: result %f does not match expected result -0.0 following underflow\n", res_flt);
    return -1;
  }
  xip_fpo_set_flt(t, 0.015625);  // smallest number representable in 4.4 format
  exc = xip_fpo_sub(t, t, t);  // difference of two very small but identical numbers: result is zero, no underflow
  if (exc != 0) {
    printf("ERROR: xip_fpo_sub: FP(4.4) = 0.015625 - 0.015625: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  res_flt = xip_fpo_get_flt(t);
  if (res_flt != 0.0) {
    printf("ERROR: xip_fpo_sub: FP(4.4) = 0.015625 - 0.015625: result %f does not match expected result 0.0\n", res_flt);
    return -1;
  }
  xip_fpo_set_inf(c, 1);   // +Inf
  exc = xip_fpo_sub(y, c, c);  // difference of infinities: expect invalid operation
  if (exc != 4) {
    printf("ERROR: xip_fpo_sub: FP(11.53) = +Inf - +Inf: expected invalid operation (exc=4), but got exc=%d\n", exc);
    return -1;
  }
  // Can't use xip_fpo_get_flt(y) and compare to nan_flt, because the comparison NaN == NaN returns false
  // Use xip_fpo_get_str instead
  res_str = xip_fpo_get_str(res_str, &res_exp, 8, 0, y);
  if (strcmp(res_str, "@NaN@") != 0) {  // expect NaN, exponent is not used
    printf("ERROR: xip_fpo_sub: FP(11.53) = +Inf - -Inf: result %s does not match expected result @NaN@ following invalid operation\n", res_str);
    return -1;
  }
  xip_fpo_set_nan(a);
  xip_fpo_set_nan(b);
  exc = xip_fpo_sub(x, a, b);  // both inputs NaN: expect NaN output but no exceptions (only quiet NaNs supported)
  if (exc != 0) {
    printf("ERROR: xip_fpo_sub: FP(8.24) = NaN - NaN: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  // Can't use xip_fpo_get_flt(x) and compare to nan_flt, because the comparison NaN == NaN returns false
  // Use xip_fpo_get_str instead
  res_str = xip_fpo_get_str(res_str, &res_exp, 8, 0, x);
  if (strcmp(res_str, "@NaN@") != 0) {  // expect NaN, exponent is not used
    printf("ERROR: xip_fpo_add: FP(8.24) = NaN - NaN: result %s does not match expected result @NaN@ following operation with NaN input\n", res_str);
    return -1;
  }

  // xip_fpo_sub_flt, xip_fpo_sub_d
  exc = xip_fpo_sub_flt(&res_flt, (float) 17.6, (float) -3.2);  // normal operation
  if (exc != 0) {
    printf("ERROR: xip_fpo_sub_flt: float = 17.6 - -3.2: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  delta_flt = FLT_EPSILON;  // acceptable difference between result and expected values due to rounding
  expected_flt = (float) 17.6 - (float) -3.2;
  if (fabsf(res_flt - expected_flt) > delta_flt) {
    printf("ERROR: xip_fpo_sub_flt: float = 17.6 - -3.2: result %f does not match expected value %f\n", res_flt, expected_flt);
    return -1;
  }
  exc = xip_fpo_sub_flt(&res_flt, (float) 3.0e38, (float) -1.4e38);  // two very large numbers, expect overflow
  if (exc != 2) {
    printf("ERROR: xip_fpo_sub_flt: float = 3.0e38 - -1.4e38: expected overflow (exc=2), but got exc=%d\n", exc);
    return -1;
  }
  if (res_flt != inf_flt) {
    printf("ERROR: xip_fpo_sub_flt: float = 3.0e38 - -1.4e38: result %f does not match expected value Infinity following overflow\n", res_flt);
    return -1;
  }
  exc = xip_fpo_sub_d(&res_d, (double) 243.56079356, (double) 141.045956204);  // normal operation
  if (exc != 0) {
    printf("ERROR: xip_fpo_sub_d: double = 243.56079356 - 141.045956204: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  delta_d = DBL_EPSILON;  // acceptable difference between result and expected values due to rounding
  expected_d = (double) 243.56079356 - (double) 141.045956204;
  if (fabs(res_d - expected_d) > delta_d) {
    printf("ERROR: xip_fpo_sub_d: double = 243.56079356 - 141.045956204: result %f does not match expected value %f\n", res_d, expected_d);
    return -1;
  }
  exc = xip_fpo_sub_d(&res_d, (double) 2.3e-308, (double) 2.6e-308);  // two very small numbers, expect underflow
  if (exc != 1) {
    printf("ERROR: xip_fpo_sub_d: double = 2.3e-308 - 2.6e-308: expected underflow (exc=1), but got exc=%d\n", exc);
    return -1;
  }
  expected_d = (double) 2.3e-308 - (double) 2.6e-308;
  if (fabs(res_d - expected_d) > delta_d) {
    printf("ERROR: xip_fpo_sub_d: double = 2.3e-308 - 2.6e-308: result %f does not match expected value %f\n", res_d, expected_d);
    return -1;
  }


  ////////////////////////////////////////////////////////////////////////
  // Operation functions: multiply
  ////////////////////////////////////////////////////////////////////////

  printf("Testing operation functions: multiply\n");

  // xip_fpo_mul
  xip_fpo_set_flt(a, 3.0);
  xip_fpo_set_flt(b, 0.5);
  exc = xip_fpo_mul(x, a, b);  // normal operation: 3.0 * 0.5
  if (exc != 0) {
    printf("ERROR: xip_fpo_mul: FP(8.24) = 3.0 * 0.5: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  res_flt = xip_fpo_get_flt(x);
  delta_flt = FLT_EPSILON;  // acceptable difference between result and expected values due to rounding
  if (fabsf(res_flt - 1.5) > delta_flt) {
    printf("ERROR: xip_fpo_mul: FP(8.24) = 3.0 * 0.5: result %f does not match expected value 1.5\n", res_flt);
    return -1;
  }
  exc = xip_fpo_mul(y, a, u);  // inputs and outputs are not the same precision: operation not supported
  if (exc != 16) {
    printf("ERROR: xip_fpo_mul: FP(11.53) = FP(8.24) * FP(16.64): expected operation not supported (exc=16), but got exc=%d\n", exc);
    return -1;
  }
  xip_fpo_set_flt(t, 16);
  exc = xip_fpo_mul(t, t, t);  // product of two medium numbers: expect overflow
  if (exc != 2) {
    printf("ERROR: xip_fpo_mul: FP(4.4) = 16 * 16: expected overflow (exc=2), but got exc=%d\n", exc);
    return -1;
  }
  res_flt = xip_fpo_get_flt(t);
  if (res_flt != inf_flt) {
    printf("ERROR: xip_fpo_mul: FP(4.4) = 16 * 16: result %f does not match expected result Infinity following overflow\n", res_flt);
    return -1;
  }
  xip_fpo_set_flt(a, 1.5e-20);
  xip_fpo_set_flt(b, 1.2e-26);
  exc = xip_fpo_mul(x, a, b);  // product of two small numbers: expect underflow
  if (exc != 1) {
    printf("ERROR: xip_fpo_mul: FP(8.24) = 1.5e-20 * 1.2e-26: expected underflow (exc=1), but got exc=%d\n", exc);
    return -1;
  }
  res_flt = xip_fpo_get_flt(x);
  if (res_flt != 0.0) {
    printf("ERROR: xip_fpo_mul: FP(8.24) = 1.5e-20 * 1.2e-26: result %f does not match expected result 0.0 following underflow\n", res_flt);
    return -1;
  }
  xip_fpo_set_inf(c, -1);  // -Inf
  xip_fpo_set_zero(d, 1);  // +zero
  exc = xip_fpo_mul(y, c, d);  // product of -Infinity and zero: expect invalid operation
  if (exc != 4) {
    printf("ERROR: xip_fpo_mul: FP(11.53) = -Inf * zero: expected invalid operation (exc=4), but got exc=%d\n", exc);
    return -1;
  }
  // Can't use xip_fpo_get_flt(y) and compare to nan_flt, because the comparison NaN == NaN returns false
  // Use xip_fpo_get_str instead
  res_str = xip_fpo_get_str(res_str, &res_exp, 8, 0, y);
  if (strcmp(res_str, "@NaN@") != 0) {  // expect NaN, exponent is not used
    printf("ERROR: xip_fpo_mul: FP(11.53) = +Inf * -Inf: result %s does not match expected result @NaN@ following invalid operation\n", res_str);
    return -1;
  }
  xip_fpo_set_nan(c);
  xip_fpo_set_inf(d, 1);
  exc = xip_fpo_mul(y, c, d);  // one input NaN: expect NaN output but no exceptions (only quiet NaNs supported)
  if (exc != 0) {
    printf("ERROR: xip_fpo_mul: FP(11.53) = NaN * Infinity: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  // Can't use xip_fpo_get_flt(y) and compare to nan_flt, because the comparison NaN == NaN returns false
  // Use xip_fpo_get_str instead
  res_str = xip_fpo_get_str(res_str, &res_exp, 8, 0, y);
  if (strcmp(res_str, "@NaN@") != 0) {  // expect NaN, exponent is not used
    printf("ERROR: xip_fpo_mul: FP(11.53) = NaN * Infinity: result %s does not match expected result @NaN@ following operation with NaN input\n", res_str);
    return -1;
  }

  // xip_fpo_mul_flt, xip_fpo_mul_d
  exc = xip_fpo_mul_flt(&res_flt, (float) 17.6, (float) -3.2);  // normal operation
  if (exc != 0) {
    printf("ERROR: xip_fpo_mul_flt: float = 17.6 * -3.2: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  delta_flt = FLT_EPSILON;  // acceptable difference between result and expected values due to rounding
  expected_flt = (float) 17.6 * (float) -3.2;
  if (fabsf(res_flt - expected_flt) > delta_flt) {
    printf("ERROR: xip_fpo_mul_flt: float = 17.6 * -3.2: result %f does not match expected value %f\n", res_flt, expected_flt);
    return -1;
  }
  exc = xip_fpo_mul_flt(&res_flt, (float) 3.0e28, (float) 1.4e18);  // two very large numbers, expect overflow
  if (exc != 2) {
    printf("ERROR: xip_fpo_mul_flt: float = 3.0e28 * 1.4e18: expected overflow (exc=2), but got exc=%d\n", exc);
    return -1;
  }
  if (res_flt != inf_flt) {
    printf("ERROR: xip_fpo_mul_flt: float = 3.0e28 * 1.4e18: result %f does not match expected value Infinity following overflow\n", res_flt);
    return -1;
  }
  exc = xip_fpo_mul_d(&res_d, (double) 243.56079356, (double) 141.045956204);  // normal operation
  if (exc != 0) {
    printf("ERROR: xip_fpo_mul_d: double = 243.56079356 * 141.045956204: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  delta_d = DBL_EPSILON;  // acceptable difference between result and expected values due to rounding
  expected_d = (double) 243.56079356 * (double) 141.045956204;
  if (fabs(res_d - expected_d) > delta_d) {
    printf("ERROR: xip_fpo_mul_d: double = 243.56079356 * 141.045956204: result %f does not match expected value %f\n", res_d, expected_d);
    return -1;
  }
  exc = xip_fpo_mul_d(&res_d, (double) 2.3e-208, (double) -2.6e-146);  // two very small numbers, expect underflow
  if (exc != 1) {
    printf("ERROR: xip_fpo_mul_d: double = 2.3e-208 * -2.6e-146: expected underflow (exc=1), but got exc=%d\n", exc);
    return -1;
  }
  expected_d = (double) 2.3e-208 * (double) -2.6e-146;
  if (fabs(res_d - expected_d) > delta_d) {
    printf("ERROR: xip_fpo_mul_d: double = 2.3e-208 * -2.6e-146: result %f does not match expected value %f\n", res_d, expected_d);
    return -1;
  }


  ////////////////////////////////////////////////////////////////////////
  // Operation functions: divide
  ////////////////////////////////////////////////////////////////////////

  printf("Testing operation functions: divide\n");

  // xip_fpo_div
  xip_fpo_set_flt(a, 1.5);
  xip_fpo_set_flt(b, 2.0);
  exc = xip_fpo_div(x, a, b);  // normal operation: 1.5 / 2.0
  if (exc != 0) {
    printf("ERROR: xip_fpo_div: FP(8.24) = 1.5 / 2.0: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  res_flt = xip_fpo_get_flt(x);
  delta_flt = FLT_EPSILON;  // acceptable difference between result and expected values due to rounding
  if (fabsf(res_flt - 0.75) > delta_flt) {
    printf("ERROR: xip_fpo_div: FP(8.24) = 1.5 / 2.0: result %f does not match expected value 0.75\n", res_flt);
    return -1;
  }
  exc = xip_fpo_div(t, a, b);  // inputs and outputs are not the same precision: operation not supported
  if (exc != 16) {
    printf("ERROR: xip_fpo_div: FP(4.4) = FP(8.24) / FP(8.24): expected operation not supported (exc=16), but got exc=%d\n", exc);
    return -1;
  }
  xip_fpo_set_d(c, 2.3e200);
  xip_fpo_set_d(d, 1.5e-150);
  exc = xip_fpo_div(y, c, d);  // divide a large number by a small number: expect overflow
  if (exc != 2) {
    printf("ERROR: xip_fpo_div: FP(11.53) = 2.3e200 / 1.5e-150: expected overflow (exc=2), but got exc=%d\n", exc);
    return -1;
  }
  res_d = xip_fpo_get_d(y);
  if (res_d != inf_d) {
    printf("ERROR: xip_fpo_div: FP(11.53) = 2.3e200 / 1.5e-150: result %f does not match expected result Infinity following overflow\n", res_d);
    return -1;
  }
  xip_fpo_set_flt(a, 1.5e-20);
  xip_fpo_set_flt(b, 1.2e26);
  exc = xip_fpo_div(x, a, b);  // divide a small number by a large number: expect underflow
  if (exc != 1) {
    printf("ERROR: xip_fpo_div: FP(8.24) = 1.5e-20 / 1.2e26: expected underflow (exc=1), but got exc=%d\n", exc);
    return -1;
  }
  res_flt = xip_fpo_get_flt(x);
  if (res_flt != 0.0) {
    printf("ERROR: xip_fpo_div: FP(8.24) = 1.5e-20 / 1.2e-26: result %f does not match expected result 0.0 following underflow\n", res_flt);
    return -1;
  }
  xip_fpo_set_d(c, 1.9675);
  xip_fpo_set_zero(d, -1);  // -zero
  exc = xip_fpo_div(y, c, d);  // divide a finite non-zero number by zero: expect division by zero
  if (exc != 8) {
    printf("ERROR: xip_fpo_div: FP(11.53) = 1.9675 / -0.0: expected division by zero (exc=8), but got exc=%d\n", exc);
    return -1;
  }
  res_d = xip_fpo_get_d(y);
  if (res_d != -inf_d) {
    printf("ERROR: xip_fpo_div: FP(11.53) = 1.9675 / -0.0: result %f does not match expected result -Infinity following division by zero\n", res_d);
    return -1;
  }
  xip_fpo_set_zero(c, -1);  // -zero
  xip_fpo_set_zero(d, 1);   // +zero
  exc = xip_fpo_div(y, c, d);  // divide minus zero by zero: expect invalid operation
  if (exc != 4) {
    printf("ERROR: xip_fpo_div: FP(11.53) = -Inf / zero: expected invalid operation (exc=4), but got exc=%d\n", exc);
    return -1;
  }
  // Can't use xip_fpo_get_flt(y) and compare to nan_flt, because the comparison NaN == NaN returns false
  // Use xip_fpo_get_str instead
  res_str = xip_fpo_get_str(res_str, &res_exp, 8, 0, y);
  if (strcmp(res_str, "@NaN@") != 0) {  // expect NaN, exponent is not used
    printf("ERROR: xip_fpo_div: FP(11.53) = +Inf / -Inf: result %s does not match expected result @NaN@ following invalid operation\n", res_str);
    return -1;
  }
  // xip_fpo_div
  xip_fpo_set_nan(t);
  exc = xip_fpo_div(t, t, t);  // both inputs NaN: expect NaN output but no exceptions (only quiet NaNs supported)
  if (exc != 0) {
    printf("ERROR: xip_fpo_div: FP(4.4) = NaN / NaN: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  // Can't use xip_fpo_get_flt(t) and compare to nan_flt, because the comparison NaN == NaN returns false
  // Use xip_fpo_get_str instead
  res_str = xip_fpo_get_str(res_str, &res_exp, 8, 0, t);
  if (strcmp(res_str, "@NaN@") != 0) {  // expect NaN, exponent is not used
    printf("ERROR: xip_fpo_div: FP(11.53) = NaN / NaN: result %s does not match expected result @NaN@ following operation with NaN input\n", res_str);
    return -1;
  }

  // xip_fpo_div_flt, xip_fpo_div_d
  exc = xip_fpo_div_flt(&res_flt, (float) 17.6, (float) -3.2);  // normal operation
  if (exc != 0) {
    printf("ERROR: xip_fpo_div_flt: float = 17.6 / -3.2: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  delta_flt = FLT_EPSILON;  // acceptable difference between result and expected values due to rounding
  expected_flt = (float) 17.6 / (float) -3.2;
  if (fabsf(res_flt - expected_flt) > delta_flt) {
    printf("ERROR: xip_fpo_div_flt: float = 17.6 / -3.2: result %f does not match expected value %f\n", res_flt, expected_flt);
    return -1;
  }
  exc = xip_fpo_div_flt(&res_flt, (float) 3.0e28, (float) 1.4e-18);  // large number / small number, expect overflow
  if (exc != 2) {
    printf("ERROR: xip_fpo_div_flt: float = 3.0e28 / 1.4e-18: expected overflow (exc=2), but got exc=%d\n", exc);
    return -1;
  }
  if (res_flt != inf_flt) {
    printf("ERROR: xip_fpo_div_flt: float = 3.0e28 / 1.4e-18: result %f does not match expected value Infinity following overflow\n", res_flt);
    return -1;
  }
  exc = xip_fpo_div_d(&res_d, (double) 243.56079356, (double) 141.045956204);  // normal operation
  if (exc != 0) {
    printf("ERROR: xip_fpo_div_d: double = 243.56079356 / 141.045956204: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  delta_d = DBL_EPSILON;  // acceptable difference between result and expected values due to rounding
  expected_d = (double) 243.56079356 / (double) 141.045956204;
  if (fabs(res_d - expected_d) > delta_d) {
    printf("ERROR: xip_fpo_div_d: double = 243.56079356 / 141.045956204: result %f does not match expected value %f\n", res_d, expected_d);
    return -1;
  }
  exc = xip_fpo_div_d(&res_d, (double) 2.3e-208, (double) -2.6e146);  // small number / large number, expect underflow
  if (exc != 1) {
    printf("ERROR: xip_fpo_div_d: double = 2.3e-208 / -2.6e146: expected underflow (exc=1), but got exc=%d\n", exc);
    return -1;
  }
  expected_d = (double) 2.3e-208 / (double) -2.6e146;
  if (fabs(res_d - expected_d) > delta_d) {
    printf("ERROR: xip_fpo_div_d: double = 2.3e-208 / -2.6e146: result %f does not match expected value %f\n", res_d, expected_d);
    return -1;
  }


  ////////////////////////////////////////////////////////////////////////
  // Operation functions: reciprocal
  ////////////////////////////////////////////////////////////////////////

  printf("Testing operation functions: reciprocal\n");

  // xip_fpo_rec
  xip_fpo_set_flt(a, 2.0);
  exc = xip_fpo_rec(x, a);  // normal operation: 1 / 2.0
  if (exc != 0) {
    printf("ERROR: xip_fpo_rec: FP(8.24) = 1 / 2.0: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  res_flt = xip_fpo_get_flt(x);
  expected_flt = 0.5f;
  delta_flt = calculate_ulp(expected_flt);  // acceptable difference between result and expected values due to rounding
  if (fabsf(res_flt - expected_flt) > delta_flt) {
    printf("ERROR: xip_fpo_rec: FP(8.24) = 1 / 2.0: result %f does not match expected value 0.5\n", res_flt);
    return -1;
  }
  xip_fpo_set_d(c, 3.4);
  exc = xip_fpo_rec(y, c);  // normal operation: 1 / 3.4
  if (exc != 0) {
    printf("ERROR: xip_fpo_rec: FP(11.53) = 1 / 3.4: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  res_d = xip_fpo_get_d(y);
  expected_d = (double) 1.0 / (double) 3.4;
  delta_d = calculate_ulp(expected_d);  // acceptable difference between result and expected values due to rounding
  if (fabs(res_d - expected_d) > delta_d) {
    printf("ERROR: xip_fpo_rec: FP(11.53) = 1 / 3.4: result %f does not match expected value %f\n", res_d, expected_d);
    return -1;
  }
  exc = xip_fpo_rec(t, a);  // inputs and outputs are not the same precision: operation not supported
  if (exc != 16) {
    printf("ERROR: xip_fpo_rec: FP(4.4) = 1 / FP(8.24): expected operation not supported (exc=16), but got exc=%d\n", exc);
    return -1;
  }
  xip_fpo_set_flt(a, 1.2e38);
  exc = xip_fpo_rec(x, a);  // reciprocal of a large number: expect underflow
  if (exc != 1) {
    printf("ERROR: xip_fpo_rec: FP(8.24) = 1 / 1.2e38: expected underflow (exc=1), but got exc=%d\n", exc);
    return -1;
  }
  res_flt = xip_fpo_get_flt(x);
  if (res_flt != 0.0) {
    printf("ERROR: xip_fpo_rec: FP(8.24) = 1 / 1.2e38: result %f does not match expected result 0.0 following underflow\n", res_flt);
    return -1;
  }
  xip_fpo_set_zero(c, -1);  // -zero
  exc = xip_fpo_rec(y, c);  // reciprocal of zero: expect division by zero
  if (exc != 8) {
    printf("ERROR: xip_fpo_rec: FP(11.53) = 1 / -0.0: expected division by zero (exc=8), but got exc=%d\n", exc);
    return -1;
  }
  res_d = xip_fpo_get_d(y);
  if (res_d != -inf_d) {
    printf("ERROR: xip_fpo_rec: FP(11.53) = 1 / -0.0: result %f does not match expected result -Infinity following division by zero\n", res_d);
    return -1;
  }
  xip_fpo_set_nan(d);
  exc = xip_fpo_rec(c, d);  // expect NaN output but no exceptions (only quiet NaNs supported)
  if (exc != 0) {
    printf("ERROR: xip_fpo_rec: FP(11.53) = 1 / NaN: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  // Can't use xip_fpo_get_flt(t) and compare to nan_flt, because the comparison NaN == NaN returns false
  // Use xip_fpo_get_str instead
  res_str = xip_fpo_get_str(res_str, &res_exp, 8, 0, c);
  if (strcmp(res_str, "@NaN@") != 0) {  // expect NaN, exponent is not used
    printf("ERROR: xip_fpo_rec: FP(11.53) = 1 / NaN: result %s does not match expected result @NaN@ following operation with NaN input\n", res_str);
    return -1;
  }

  // xip_fpo_rec_flt, xip_fpo_rec_d
  exc = xip_fpo_rec_flt(&res_flt, (float) -3.2);  // normal operation
  if (exc != 0) {
    printf("ERROR: xip_fpo_rec_flt: float = 1 / -3.2: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  expected_flt = (float) 1.0 / (float) -3.2;
  delta_flt = calculate_ulp(expected_flt);  // acceptable difference between result and expected values due to rounding
  if (fabsf(res_flt - expected_flt) > delta_flt) {
    printf("ERROR: xip_fpo_rec_flt: float = 1 / -3.2: result %f does not match expected value %f\n", res_flt, expected_flt);
    return -1;
  }
  exc = xip_fpo_rec_flt(&res_flt, (float) 0.0);  // reciprocal of zero, expect division by zero
  if (exc != 8) {
    printf("ERROR: xip_fpo_rec_flt: float = 1 / 0.0: expected division by zero (exc=8), but got exc=%d\n", exc);
    return -1;
  }
  if (res_flt != inf_flt) {
    printf("ERROR: xip_fpo_rec_flt: float = 1 / 0.0: result %f does not match expected value -Infinity\n", res_flt);
    return -1;
  }
  exc = xip_fpo_rec_d(&res_d, (double) 141.045956204);  // normal operation
  if (exc != 0) {
    printf("ERROR: xip_fpo_rec_d: double = 1 / 141.045956204: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  expected_d = (double) 1.0 / (double) 141.045956204;
  delta_d = calculate_ulp(expected_d);  // acceptable difference between result and expected values due to rounding
  if (fabs(res_d - expected_d) > delta_d) {
    printf("ERROR: xip_fpo_rec_d: double = 1 / 141.045956204: result %.18f does not match expected value %.18f\n", res_d, expected_d);
    return -1;
  }
  exc = xip_fpo_rec_d(&res_d, (double) -5.6e307);  // reciprocal of large number, expect underflow
  if (exc != 1) {
    printf("ERROR: xip_fpo_rec_d: double = 1 / -5.6e307: expected underflow (exc=1), but got exc=%d\n", exc);
    return -1;
  }
  expected_d = (double) 1.0 / (double) -5.6e307;
  if (fabs(res_d - expected_d) > delta_d) {
    printf("ERROR: xip_fpo_rec_d: double = 1 / -5.6e307: result %f does not match expected value %f\n", res_d, expected_d);
    return -1;
  }


  ////////////////////////////////////////////////////////////////////////
  // Operation functions: square root
  ////////////////////////////////////////////////////////////////////////

  printf("Testing operation functions: square root\n");

  // xip_fpo_sqrt
  xip_fpo_set_flt(a, 4.0);
  exc = xip_fpo_sqrt(x, a);  // normal operation: sqrt(4.0)
  if (exc != 0) {
    printf("ERROR: xip_fpo_sqrt: FP(8.24) = sqrt(4.0): no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  res_flt = xip_fpo_get_flt(x);
  delta_flt = FLT_EPSILON;  // acceptable difference between result and expected values due to rounding
  if (fabsf(res_flt - 2.0) > delta_flt) {
    printf("ERROR: xip_fpo_sqrt: FP(8.24) = sqrt(4.0): result %f does not match expected value 2.0\n", res_flt);
    return -1;
  }
  exc = xip_fpo_sqrt(x, u);  // input and output are not the same precision: operation not supported
  if (exc != 16) {
    printf("ERROR: xip_fpo_sqrt: FP(8.24) = sqrt(FP(16.64)): expected operation not supported (exc=16), but got exc=%d\n", exc);
    return -1;
  }
  xip_fpo_set_d(c, -43.7);
  exc = xip_fpo_sqrt(y, c);  // square root of a negative number: expect invalid operation
  if (exc != 4) {
    printf("ERROR: xip_fpo_sqrt: FP(11.53) = sqrt(-43.7): expected invalid operation (exc=4), but got exc=%d\n", exc);
    return -1;
  }
  // Can't use xip_fpo_get_flt(y) and compare to nan_flt, because the comparison NaN == NaN returns false
  // Use xip_fpo_get_str instead
  res_str = xip_fpo_get_str(res_str, &res_exp, 8, 0, y);
  if (strcmp(res_str, "@NaN@") != 0) {  // expect NaN, exponent is not used
    printf("ERROR: xip_fpo_sqrt: FP(11.53) = sqrt(-43.7): result %s does not match expected result @NaN@ following invalid operation\n", res_str);
    return -1;
  }
  xip_fpo_set_nan(a);
  exc = xip_fpo_sqrt(x, a);  // input NaN: expect NaN output but no exceptions (only quiet NaNs supported)
  if (exc != 0) {
    printf("ERROR: xip_fpo_sqrt: FP(8.24) = sqrt(NaN): no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  // Can't use xip_fpo_get_flt(x) and compare to nan_flt, because the comparison NaN == NaN returns false
  // Use xip_fpo_get_str instead
  res_str = xip_fpo_get_str(res_str, &res_exp, 8, 0, x);
  if (strcmp(res_str, "@NaN@") != 0) {  // expect NaN, exponent is not used
    printf("ERROR: xip_fpo_sqrt: FP(8.24) = sqrt(NaN): result %s does not match expected result @NaN@ following operation with NaN input\n", res_str);
    return -1;
  }

  // xip_fpo_sqrt_flt, xip_fpo_sqrt_d
  exc = xip_fpo_sqrt_flt(&res_flt, (float) 17.6);  // normal operation
  if (exc != 0) {
    printf("ERROR: xip_fpo_sqrt_flt: float = sqrt(17.6): no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  delta_flt = FLT_EPSILON;  // acceptable difference between result and expected values due to rounding
  expected_flt = sqrt((float) 17.6);
  if (fabsf(res_flt - expected_flt) > delta_flt) {
    printf("ERROR: xip_fpo_sqrt_flt: float = sqrt(17.6): result %f does not match expected value %f\n", res_flt, expected_flt);
    return -1;
  }
  exc = xip_fpo_sqrt_flt(&res_flt, (float) -17.6);  // negative input, expect invalid operation
  if (exc != 4) {
    printf("ERROR: xip_fpo_sqrt_flt: float = sqrt(-17.6): expected invalid operation (exc=4), but got exc=%d\n", exc);
    return -1;
  }
  // Can't compare res_flt to nan_flt, because the comparison NaN == NaN returns false
  exc = xip_fpo_sqrt_d(&res_d, (double) 243.56079356);  // normal operation
  if (exc != 0) {
    printf("ERROR: xip_fpo_sqrt_d: double = sqrt(243.56079356): no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  delta_d = DBL_EPSILON;  // acceptable difference between result and expected values due to rounding
  expected_d = sqrt((double) 243.56079356);
  if (fabs(res_d - expected_d) > delta_d) {
    printf("ERROR: xip_fpo_sqrt_d: double = sqrt(243.56079356): result %f does not match expected value %f\n", res_d, expected_d);
    return -1;
  }
  exc = xip_fpo_sqrt_d(&res_d, (double) -0.0);  // normal operation: -0.0 is the only legal negative input to sqrt
  if (exc != 0) {
    printf("ERROR: xip_fpo_sqrt_d: double = sqrt(-0.0): no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  expected_d = sqrt((double) -0.0);
  if (fabs(res_d - expected_d) > delta_d) {
    printf("ERROR: xip_fpo_sqrt_d: double = sqrt(-0.0): result %f does not match expected value %f\n", res_d, expected_d);
    return -1;
  }


  ////////////////////////////////////////////////////////////////////////
  // Operation functions: reciprocal square root
  ////////////////////////////////////////////////////////////////////////

  printf("Testing operation functions: reciprocal square root\n");

  // xip_fpo_recsqrt
  xip_fpo_set_flt(a, 4.0);
  exc = xip_fpo_recsqrt(x, a);  // normal operation: 1 / sqrt(4.0)
  if (exc != 0) {
    printf("ERROR: xip_fpo_recsqrt: FP(8.24) = 1 / sqrt(4.0): no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  res_flt = xip_fpo_get_flt(x);
  expected_flt = 0.5f;
  delta_flt = calculate_ulp(expected_flt);  // acceptable difference between result and expected values due to rounding
  if (fabsf(res_flt - expected_flt) > delta_flt) {
    printf("ERROR: xip_fpo_recsqrt: FP(8.24) = 1 / sqrt(4.0): result %f does not match expected value 0.5\n", res_flt);
    return -1;
  }
  xip_fpo_set_d(c, 0.125);
  exc = xip_fpo_recsqrt(y, c);  // normal operation: 1 / sqrt(0.125)
  if (exc != 0) {
    printf("ERROR: xip_fpo_recsqrt: FP(11.53) = 1 / sqrt(0.125): no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  res_d = xip_fpo_get_d(y);
  expected_d = sqrt((double) 8.0);  // 2-step approach of (double) 1.0 / sqrt((double) 0.125) is not accurate
  delta_d = calculate_ulp(expected_d);  // acceptable difference between result and expected values due to rounding
  if (fabs(res_d - expected_d) > delta_d) {
    printf("ERROR: xip_fpo_recsqrt: FP(11.53) = 1 / sqrt(0.125): result %f does not match expected value %f\n", res_d, expected_d);
    return -1;
  }
  xip_fpo_set_d(c, 3.4);
  exc = xip_fpo_recsqrt(y, c);  // normal operation: 1 / sqrt(3.4)
  if (exc != 0) {
    printf("ERROR: xip_fpo_recsqrt: FP(11.53) = 1 / sqrt(3.4): no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  res_d = xip_fpo_get_d(y);
  // The 2-step approach of (double) 1.0 / sqrt((double) 3.4) is not accurate enough, have to use MPFR instead
  mpfr_t expected_fr_d;
  mpfr_init2(expected_fr_d, 53);
  mpfr_set_d(expected_fr_d, 3.4, MPFR_RNDN);
  mpfr_rec_sqrt(expected_fr_d, expected_fr_d, MPFR_RNDN);
  expected_d = mpfr_get_d(expected_fr_d, MPFR_RNDN);
  delta_d = calculate_ulp(expected_d);  // acceptable difference between result and expected values due to rounding
  if (fabs(res_d - expected_d) > delta_d) {
    printf("ERROR: xip_fpo_recsqrt: FP(11.53) = 1 / sqrt(3.4): result %f does not match expected value %f\n", res_d, expected_d);
    return -1;
  }
  exc = xip_fpo_recsqrt(t, a);  // inputs and outputs are not the same precision: operation not supported
  if (exc != 16) {
    printf("ERROR: xip_fpo_recsqrt: FP(4.4) = 1 / sqrt(FP(8.24)): expected operation not supported (exc=16), but got exc=%d\n", exc);
    return -1;
  }
  xip_fpo_set_zero(c, -1);  // -zero
  exc = xip_fpo_recsqrt(y, c);  // reciprocal square root of zero: expect division by zero
  if (exc != 8) {
    printf("ERROR: xip_fpo_recsqrt: FP(11.53) = 1 / sqrt(-0.0): expected division by zero (exc=8), but got exc=%d\n", exc);
    return -1;
  }
  res_d = xip_fpo_get_d(y);
  if (res_d != -inf_d) {
    printf("ERROR: xip_fpo_recsqrt: FP(11.53) = 1 / sqrt(-0.0): result %f does not match expected result -Infinity following division by zero\n", res_d);
    return -1;
  }
  xip_fpo_set_flt(b, -43.7);
  exc = xip_fpo_recsqrt(x, b);  // reciprocal square root of a negative number: expect invalid operation
  if (exc != 4) {
    printf("ERROR: xip_fpo_sqrt: FP(8.24) = 1 / sqrt(-43.7): expected invalid operation (exc=4), but got exc=%d\n", exc);
    return -1;
  }
  // Can't use xip_fpo_get_flt(x) and compare to nan_flt, because the comparison NaN == NaN returns false
  // Use xip_fpo_get_str instead
  res_str = xip_fpo_get_str(res_str, &res_exp, 8, 0, x);
  if (strcmp(res_str, "@NaN@") != 0) {  // expect NaN, exponent is not used
    printf("ERROR: xip_fpo_recsqrt: FP(8.24) = 1 / sqrt(-43.7): result %s does not match expected result @NaN@ following invalid operation\n", res_str);
    return -1;
  }
  xip_fpo_set_nan(d);
  exc = xip_fpo_recsqrt(y, d);  // expect NaN output but no exceptions (only quiet NaNs supported)
  if (exc != 0) {
    printf("ERROR: xip_fpo_recsqrt: FP(11.53) = 1 / sqrt(NaN): no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  // Can't use xip_fpo_get_d(y) and compare to nan_d, because the comparison NaN == NaN returns false
  // Use xip_fpo_get_str instead
  res_str = xip_fpo_get_str(res_str, &res_exp, 8, 0, y);
  if (strcmp(res_str, "@NaN@") != 0) {  // expect NaN, exponent is not used
    printf("ERROR: xip_fpo_recsqrt: FP(11.53) = 1 / sqrt(NaN): result %s does not match expected result @NaN@ following operation with NaN input\n", res_str);
    return -1;
  }
  // xip_fpo_recsqrt_flt, xip_fpo_recsqrt_d
  exc = xip_fpo_recsqrt_flt(&res_flt, (float) 17.6);  // normal operation
  if (exc != 0) {
    printf("ERROR: xip_fpo_recsqrt_flt: float = 1 / sqrt(17.6): no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  // The 2-step approach of (float) 1.0 / sqrt((float) 17.6) is not accurate enough, have to use MPFR instead
  mpfr_t expected_fr_flt;
  mpfr_init2(expected_fr_flt, 24);
  mpfr_set_flt(expected_fr_flt, (float) 17.6, MPFR_RNDN);
  mpfr_rec_sqrt(expected_fr_flt, expected_fr_flt, MPFR_RNDN);
  expected_flt = mpfr_get_flt(expected_fr_flt, MPFR_RNDN);
  delta_flt = calculate_ulp(expected_flt);  // acceptable difference between result and expected values due to rounding
  if (fabsf(res_flt - expected_flt) > delta_flt) {
    printf("ERROR: xip_fpo_recsqrt_flt: float = 1 / sqrt(17.6): result %f does not match expected value %f\n", res_flt, expected_flt);
    return -1;
  }
  exc = xip_fpo_recsqrt_flt(&res_flt, (float) -17.6);  // negative input, expect invalid operation
  if (exc != 4) {
    printf("ERROR: xip_fpo_recsqrt_flt: float = 1 / sqrt(-17.6): expected invalid operation (exc=4), but got exc=%d\n", exc);
    return -1;
  }
  // Can't compare res_flt to nan_flt, because the comparison NaN == NaN returns false
  exc = xip_fpo_recsqrt_d(&res_d, (double) 243.56079356);  // normal operation
  if (exc != 0) {
    printf("ERROR: xip_fpo_recsqrt_d: double = 1 / sqrt(243.56079356): no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  // The 2-step approach of (double) 1.0 / sqrt((double) 243.56079356) is not accurate enough, have to use MPFR instead
  mpfr_set_d(expected_fr_d, (double) 243.56079356, MPFR_RNDN);
  mpfr_rec_sqrt(expected_fr_d, expected_fr_d, MPFR_RNDN);
  expected_d = mpfr_get_d(expected_fr_d, MPFR_RNDN);
  delta_d = calculate_ulp(expected_d);  // acceptable difference between result and expected values due to rounding
  if (fabs(res_d - expected_d) > delta_d) {
    printf("ERROR: xip_fpo_recsqrt_d: double = 1 / sqrt(243.56079356): result %f does not match expected value %f\n", res_d, expected_d);
    return -1;
  }
  exc = xip_fpo_recsqrt_d(&res_d, (double) -0.0);  // zero input, expect division by zero
  if (exc != 8) {
    printf("ERROR: xip_fpo_recsqrt_d: double = 1 / sqrt(-0.0): expected division by zero (exc=8), but got exc=%d\n", exc);
    return -1;
  }
  if (res_d != -inf_d) {
    printf("ERROR: xip_fpo_recsqrt_d: double = 1 / sqrt(-0.0): result %f does not match expected value -Infinity\n", res_d);
    return -1;
  }


  ////////////////////////////////////////////////////////////////////////
  // Operation functions: absolute value
  ////////////////////////////////////////////////////////////////////////

  printf("Testing operation functions: absolute value\n");

  // Variables needed just for ABS()
  //
  double abs_d;
  float  abs_f;

  mpfr_t     abs_mpfr;
  mp_limb_t *backup_of_limb_pointer;

  // Test a normal +ve number
  // ------------------------
  //

  abs_f = 4.0;

  xip_fpo_set_flt(a, abs_f);
  exc = xip_fpo_abs(x, a);  // normal operation, single precision: abs(+4.0)
  if (exc != 0) {
    printf("ERROR: xip_fpo_abs 1: FP(8.24) = abs(%e): no exceptions expected (exc=0), but got exc=%d\n", abs_f, exc);
    return -1;
  }
  if (xip_fpo_get_flt(x) != fabsf(abs_f)) {
    printf("ERROR: xip_fpo_abs 2: FP(8.24) = abs(%e): result %e does not match expected result %e\n", abs_f, res_d, fabsf(abs_f));
    return -1;
  }

  exc = xip_fpo_abs_flt(&res_flt, abs_f);
  if (exc != 0) {
    printf("ERROR: xip_fpo_abs 3: FP(8.24) = abs(%e): no exceptions expected (exc=0), but got exc=%d\n", abs_f, exc);
    return -1;
  }

  if (res_flt != fabs(abs_f)) {
    printf("ERROR: xip_fpo_abs_flt 4: FP(8.24) = abs(%e): result %e does not match expected result %e\n", abs_f, res_f, fabsf(abs_f));
    return -1;
  }


  // Test a normal -ve number
  // ------------------------
  //
  abs_d = -256.781;

  xip_fpo_set_d(d, abs_d);
  exc = xip_fpo_abs(y, d);
  if (exc != 0) {
    printf("ERROR: xip_fpo_abs  5: FP(11.53) = abs(%e): no exceptions expected (exc=0), but got exc=%d\n", abs_d, exc);
    return -1;
  }

  if (xip_fpo_get_d(y) != fabs(abs_d)) {
    printf("ERROR: xip_fpo_abs 6: FP(11.53) = abs(%e): result %e does not match expected result %e\n", abs_d, res_d, fabs(abs_d));
    return -1;
  }


  exc = xip_fpo_abs_d(&res_d, abs_d);  // normal operation
  if (exc != 0) {
    printf("ERROR: xip_fpo_abs_d 7: FP(11.53) = abs(%e): no exceptions expected (exc=0), but got exc=%d\n", abs_d, exc);
    return -1;
  }
  if (res_d != fabs(abs_d)) {
    printf("ERROR: xip_fpo_abs_d 8: FP(11.53) = abs(%e): result %e does not match expected result %e\n", abs_d, res_d, fabs(abs_d));
    return -1;
  }



  // Test ABS with mismatching precision
  // -----------------------------------
  //
  exc = xip_fpo_abs(t, a);  // inputs and outputs are not the same precision: operation not supported
  if (exc != 16) {
    printf("ERROR: xip_fpo_abs 9: FP(4.4) = abs(FP(8.24)): expected operation not supported (exc=16), but got exc=%d\n", exc);
    return -1;
  }


  // Test ABS with +0
  // ----------------
  //
  xip_fpo_set_zero(d, 1);  // +zero

  exc = xip_fpo_abs(y, d);  // magnitude of positive zero: expect positive zero

  if (exc != 0) {
    printf("ERROR: xip_fpo_abs 10: FP(11.53) = abs(0.0): no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }

  res_d = xip_fpo_get_d(y);
  if (res_d != 0.0) {
    printf("ERROR: xip_fpo_abs 11: FP(11.53) = abs(0.0): result %e does not match expected result 0.0\n", res_d);
    return -1;
  }

  abs_d = 0.0;
  exc = xip_fpo_abs_d(&res_d, abs_d);
  if (exc != 0) {
    printf("ERROR: xip_fpo_abs_d 12: FP(11.53) = abs(%e): result %e does not match expected result %e\n", abs_d, res_d);
    return -1;
  }
  if (res_d != fabs(abs_d)) {
    printf("ERROR: xip_fpo_abs_d 13: FP(11.53) = abs(%e): result %e does not match expected result %e\n", abs_d, res_d, fabs(abs_d));
    return -1;
  }


  // Test ABS with -0
  // ----------------
  //
  xip_fpo_set_zero(d, -1);  // -zero

  exc = xip_fpo_abs(y, d);  // magnitude of negative zero: expect positive zero
  if (exc != 0) {
    printf("ERROR: xip_fpo_abs 14: FP(11.53) = abs(-0.0): no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  res_d = xip_fpo_get_d(y);
  if (res_d != 0.0) {
    printf("ERROR: xip_fpo_abs 15: FP(11.53) = abs(-0.0): result %f does not match expected result +0.0\n", res_d);
    return -1;
  }

  abs_d = -0.0;
  exc = xip_fpo_abs_d(&res_d, abs_d);

  if (exc != 0) {
    printf("ERROR: xip_fpo_abs_d 16: FP(11.53) = abs(-0.0): result %f does not match expected result -0.0\n", res_d);
    return -1;
  }
  if (res_d != 0.0) {
    printf("ERROR: xip_fpo_abs_d 17: FP(11.53) = abs(-0.0): result %f does not match expected result -0.0\n", res_d);
    return -1;
  }



  // Test ABS on a -ve Subnormal
  // ---------------------------
  //
  //
  // xip_fpo_set_flt() does not support subnormal numbers, so bypass it and populate the xip_fpo_t struct directly

  mpfr_init2(abs_mpfr, 24);

  // Create a subnormal number.  exponent is all 0 and the significand is non-zero
  // Set sign to -
  //
  // 1000 0000 0000 0000 0000 0000 0000 1111 = 0x8000000f
  //
  snan_flt.i = (xint32)0x8000000f;

  mpfr_set_flt(abs_mpfr, snan_flt.f, MPFR_RNDN);

  a->_xip_fpo_mant_prec = abs_mpfr->_mpfr_prec;
  a->_xip_fpo_sign      = abs_mpfr->_mpfr_sign;
  a->_xip_fpo_exp       = abs_mpfr->_mpfr_exp;

  backup_of_limb_pointer = a->_xip_fpo_d;      // Backup the limb pointer
  a->_xip_fpo_d          = abs_mpfr->_mpfr_d;  // Overwrite the limb pointer rather than copying the contents

  exc = xip_fpo_abs(x, a);
  if (exc != 0) {
    printf("ERROR: xip_fpo_abs: single = abs(Subnormal): no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }

  // Check the value
  //
  // fabsf(xip_fpo_get_flt(x)) destroys the value in someway, so use 0- to get the expected +ve value
  if (xip_fpo_get_flt(a) != 0-xip_fpo_get_flt(x)) {
    printf("ERROR: xip_fpo_abs: FP(8.24) = abs(-Subnormal): result %e does not match expected result %e following operation with subnormal input\n", xip_fpo_get_flt(x), 0-xip_fpo_get_flt(a));
    return -1;
   }

  if (x->_xip_fpo_sign != 1) {
    printf("ERROR: xip_fpo_abs: FP(8.24) = abs(-Subnormal): +ve result expected\n");
    return -1;
  }

  abs_f = snan_flt.f;
  exc = xip_fpo_abs_flt(&res_flt, abs_f);
  if (exc != 0) {
    printf("ERROR: xip_fpo_abs_flt : FP(8.24) = abs(%e): no exceptions expected (exc=0), but got exc=%d\n", abs_f, exc);
    return -1;
  }

  if (res_flt != fabs(abs_f)) {
    printf("ERROR: xip_fpo_abs_flt: FP(8.24) = abs(%e): result %e does not match expected result %e\n", abs_f, res_f, fabsf(abs_f));
    return -1;
  }

  a->_xip_fpo_d = backup_of_limb_pointer;  // Restore the limb pointer
  mpfr_clear(abs_mpfr);


  // Test ABS on a +ve Inf
  // ---------------------
  //
  xip_fpo_set_flt (a, inf_flt);
  exc = xip_fpo_abs(x, a);
  if (exc != 0) {
    printf("ERROR: xip_fpo_abs: single = abs(INF): no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }

  // Can't use xip_fpo_get_d(y) and compare to nan_d, because the comparison NaN == NaN returns false
  // Use xip_fpo_get_str instead
  //
  res_str = xip_fpo_get_str(res_str, &res_exp, 8, 0, x);

  if (strcmp(res_str, "@Inf@") != 0) {  // expect NaN, exponent is not used
    printf("ERROR: xip_fpo_abs: FP(8.24) = abs(+INF): result %s does not match expected result @INF@ following operation with INF input\n", res_str);
    return -1;
  }

  if (x->_xip_fpo_sign != 1) {
    printf("ERROR: xip_fpo_abs: FP(8.24) = abs(INF): +ve result expected\n");
    return -1;
  }


  abs_f = inf_flt;
  exc = xip_fpo_abs_flt(&res_flt, abs_f);
  if (exc != 0) {
    printf("ERROR: xip_fpo_abs_flt : FP(8.24) = abs(%e): no exceptions expected (exc=0), but got exc=%d\n", abs_f, exc);
    return -1;
  }

  if (res_flt != fabs(abs_f)) {
    printf("ERROR: xip_fpo_abs_flt: FP(8.24) = abs(%e): result %e does not match expected result %e\n", abs_f, res_f, fabsf(abs_f));
    return -1;
  }


  // Test ABS on a -ve Inf
  // ---------------------
  //
  xip_fpo_set_flt (a, -inf_flt);
  exc = xip_fpo_abs(x, a);
  if (exc != 0) {
    printf("ERROR: xip_fpo_abs: single = abs(-INF): no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }

  res_str = xip_fpo_get_str(res_str, &res_exp, 8, 0, x);

  if (strcmp(res_str, "@Inf@") != 0) {  // expect NaN, exponent is not used
    printf("ERROR: xip_fpo_abs: FP(8.24) = abs(INF): result %s does not match expected result @INF@ following operation with INF input\n", res_str);
    return -1;
  }

  if (x->_xip_fpo_sign != 1) {
    printf("ERROR: xip_fpo_abs: FP(8.24) = abs(INF): +ve result expected\n");
    return -1;
  }

  abs_f = -inf_flt;
  exc = xip_fpo_abs_flt(&res_flt, abs_f);
  if (exc != 0) {
    printf("ERROR: xip_fpo_abs_flt : FP(8.24) = abs(%e): no exceptions expected (exc=0), but got exc=%d\n", abs_f, exc);
    return -1;
  }

  if (res_flt != fabs(abs_f)) {
    printf("ERROR: xip_fpo_abs_flt: FP(8.24) = abs(%e): result %e does not match expected result %e\n", abs_f, res_f, fabsf(abs_f));
    return -1;
  }

  ////////////////////////////////////////////////////////////////////////
  // Operation functions: logarithm
  ////////////////////////////////////////////////////////////////////////

  printf("Testing operation functions: logarithm\n");

  // xip_fpo_log
  xip_fpo_set_flt(a, 4.0);
  exc = xip_fpo_log(x, a);  // normal operation: log(4.0)
  if (exc != 0) {
    printf("ERROR: xip_fpo_log: FP(8.24) = log(4.0): no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  res_flt = xip_fpo_get_flt(x);
  expected_flt = log((float)4.0);
  delta_flt = calculate_ulp(expected_flt);  // acceptable difference between result and expected values due to rounding
  if (fabsf(res_flt - expected_flt) > delta_flt) {
    printf("ERROR: xip_fpo_log: FP(8.24) = log(4.0): result %f does not match expected value %f\n", res_flt, expected_flt);
    return -1;
  }
  xip_fpo_set_d(c, 0.125);
  exc = xip_fpo_log(y, c);  // normal operation: log(0.125)
  if (exc != 0) {
    printf("ERROR: xip_fpo_log: FP(11.53) = log(0.125): no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  res_d = xip_fpo_get_d(y);
  expected_d = log(0.125);
  delta_d = calculate_ulp(expected_d);  // acceptable difference between result and expected values due to rounding
  if (fabs(res_d - expected_d) > delta_d) {
    printf("ERROR: xip_fpo_log: FP(11.53) = log(0.125): result %f does not match expected value %f\n", res_d, expected_d);
    return -1;
  }
  xip_fpo_set_d(c, 3.4);
  exc = xip_fpo_log(y, c);  // normal operation: log(3.4)
  if (exc != 0) {
    printf("ERROR: xip_fpo_log: FP(11.53) = log(3.4): no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  res_d = xip_fpo_get_d(y);
  expected_d = log(3.4);
  delta_d = calculate_ulp(expected_d);  // acceptable difference between result and expected values due to rounding
  if (fabs(res_d - expected_d) > delta_d) {
    printf("ERROR: xip_fpo_log: FP(11.53) = log(3.4): result %f does not match expected value %f\n", res_d, expected_d);
    return -1;
  }
  exc = xip_fpo_log(t, a);  // inputs and outputs are not the same precision: operation not supported
  if (exc != 16) {
    printf("ERROR: xip_fpo_log: FP(4.4) = log(FP(8.24)): expected operation not supported (exc=16), but got exc=%d\n", exc);
    return -1;
  }
  xip_fpo_set_zero(c, 1);  // zero
  exc = xip_fpo_log(y, c);  // log of zero: expect division by zero
  if (exc != 8) {
    printf("ERROR: xip_fpo_log: FP(11.53) = log(0.0): expected division by zero (exc=8), but got exc=%d\n", exc);
    return -1;
  }
  res_d = xip_fpo_get_d(y);
  if (res_d != -inf_d) {
    printf("ERROR: xip_fpo_log: FP(11.53) = log(0.0): result %f does not match expected result -Infinity\n", res_d);
    return -1;
  }
  xip_fpo_set_flt(b, -43.7);
  exc = xip_fpo_log(x, b);  // log of a negative number: expect invalid operation
  if (exc != 4) {
    printf("ERROR: xip_fpo_log: FP(8.24) = log(-43.7): expected invalid operation (exc=4), but got exc=%d\n", exc);
    return -1;
  }
  // Can't use xip_fpo_get_flt(x) and compare to nan_flt, because the comparison NaN == NaN returns false
  // Use xip_fpo_get_str instead
  res_str = xip_fpo_get_str(res_str, &res_exp, 8, 0, x);
  if (strcmp(res_str, "@NaN@") != 0) {  // expect NaN, exponent is not used
    printf("ERROR: xip_fpo_log: FP(8.24) = log(-43.7): result %s does not match expected result @NaN@ following invalid operation\n", res_str);
    return -1;
  }
  xip_fpo_set_nan(d);
  exc = xip_fpo_log(y, d);  // expect NaN output but no exceptions (only quiet NaNs supported)
  if (exc != 0) {
    printf("ERROR: xip_fpo_log: FP(11.53) = log(NaN): no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  // Can't use xip_fpo_get_d(y) and compare to nan_d, because the comparison NaN == NaN returns false
  // Use xip_fpo_get_str instead
  res_str = xip_fpo_get_str(res_str, &res_exp, 8, 0, y);
  if (strcmp(res_str, "@NaN@") != 0) {  // expect NaN, exponent is not used
    printf("ERROR: xip_fpo_log: FP(11.53) = log(NaN): result %s does not match expected result @NaN@ following operation with NaN input\n", res_str);
    return -1;
  }
  // xip_fpo_log_flt, xip_fpo_log_d
  exc = xip_fpo_log_flt(&res_flt, (float) 17.6);  // normal operation
  if (exc != 0) {
    printf("ERROR: xip_fpo_log_flt: float = log(17.6): no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }

  expected_flt = (float) log((float) 17.6);
  delta_flt = calculate_ulp(expected_flt);  // acceptable difference between result and expected values due to rounding
  if (fabsf(res_flt - expected_flt) > delta_flt) {
    printf("ERROR: xip_fpo_log_flt: float = log(17.6): result %.23e does not match expected value %.23e\n", res_flt, expected_flt);
    return -1;
  }
  exc = xip_fpo_log_flt(&res_flt, (float) -17.6);  // negative input, expect invalid operation
  if (exc != 4) {
    printf("ERROR: xip_fpo_log_flt: float = log(-17.6): expected invalid operation (exc=4), but got exc=%d\n", exc);
    return -1;
  }

  // Can't compare res_flt to nan_flt, because the comparison NaN == NaN returns false
  exc = xip_fpo_log_d(&res_d, (double) 243.56079356);  // normal operation
  if (exc != 0) {
    printf("ERROR: xip_fpo_log_d: double = log(243.56079356): no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  expected_d = log(243.56079356);
  delta_d = calculate_ulp(expected_d);  // acceptable difference between result and expected values due to rounding
  if (fabs(res_d - expected_d) > delta_d) {
    printf("ERROR: xip_fpo_log_d: double = log(243.56079356): result %f does not match expected value %f\n", res_d, expected_d);
    return -1;
  }
  exc = xip_fpo_log_d(&res_d, (double) 0.0);  // zero input, expect division by zero
  if (exc != 8) {
    printf("ERROR: xip_fpo_log_d: double = log(0.0): expected division by zero (exc=8), but got exc=%d\n", exc);
    return -1;
  }
  if (res_d != -inf_d) {
    printf("ERROR: xip_fpo_log_d: double = log(0.0): result %f does not match expected value -Infinity\n", res_d);
    return -1;
  }


  ////////////////////////////////////////////////////////////////////////
  // Operation functions: compare unordered
  ////////////////////////////////////////////////////////////////////////

  printf("Testing operation functions: compare unordered\n");

  // xip_fpo_unordered
  xip_fpo_set_flt(a, 3.0);
  xip_fpo_set_flt(b, 0.5);
  int res_int;
  exc = xip_fpo_unordered(&res_int, a, b);  // normal operation, neither is NaN
  if (exc != 0) {
    printf("ERROR: xip_fpo_unordered: compare 3.0 and 0.5: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (res_int != 0) {
    printf("ERROR: xip_fpo_unordered: compare 3.0 and 0.5: result %d does not match expected value 0\n", res_int);
    return -1;
  }
  exc = xip_fpo_unordered(&res_int, a, c);  // inputs are not the same precision: operation not supported
  if (exc != 16) {
    printf("ERROR: xip_fpo_unordered: compare FP(8.24) and FP(11.53): expected operation not supported (exc=16), but got exc=%d\n", exc);
    return -1;
  }
  xip_fpo_set_nan(b);
  exc = xip_fpo_unordered(&res_int, a, b);  // normal operation, one input is NaN
  if (exc != 0) {
    printf("ERROR: xip_fpo_unordered: compare 3.0 and NaN: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (res_int != 1) {
    printf("ERROR: xip_fpo_unordered: compare 3.0 and NaN: result %d does not match expected value 1\n", res_int);
    return -1;
  }
  xip_fpo_set_nan(t);
  exc = xip_fpo_unordered(&res_int, t, t);  // normal operation, both inputs are NaN
  if (exc != 0) {
    printf("ERROR: xip_fpo_unordered: compare NaN and NaN: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (res_int != 1) {
    printf("ERROR: xip_fpo_unordered: compare NaN and NaN: result %d does not match expected value 1\n", res_int);
    return -1;
  }

  // xip_fpo_unordered_flt, xip_fpo_unordered_d
  exc = xip_fpo_unordered_flt(&res_int, (float) 17.6, (float) -3.2);  // normal operation
  if (exc != 0) {
    printf("ERROR: xip_fpo_unordered_flt: compare 17.6 and -3.2: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (res_int != 0) {
    printf("ERROR: xip_fpo_unordered_flt: compare 17.6 and -3.2: result %d does not match expected value 0\n", res_int);
    return -1;
  }
  exc = xip_fpo_unordered_flt(&res_int, nan_flt, (float) 1.4e38);  // one input is NaN
  if (exc != 0) {
    printf("ERROR: xip_fpo_unordered_flt: compare NaN and 1.4e38: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (res_int != 1) {
    printf("ERROR: xip_fpo_unordered_flt: compare NaN and 1.4e38: result %d does not match expected value 1\n", res_int);
    return -1;
  }
  exc = xip_fpo_unordered_d(&res_int, (double) 243.56079356, (double) 141.045956204);  // normal operation
  if (exc != 0) {
    printf("ERROR: xip_fpo_unordered_d: compare 243.56079356 and 141.045956204: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (res_int != 0) {
    printf("ERROR: xip_fpo_unordered_d: compare 243.56079356 and 141.045956204: result %d does not match expected value 0\n", res_int);
    return -1;
  }
  exc = xip_fpo_unordered_d(&res_int, nan_d, nan_d);  // both inputs NaN
  if (exc != 0) {
    printf("ERROR: xip_fpo_unordered_d: compare NaN and NaN: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (res_int != 1) {
    printf("ERROR: xip_fpo_unordered_d: compare NaN and NaN: result %d does not match expected value 1\n", res_int);
    return -1;
  }


  ////////////////////////////////////////////////////////////////////////
  // Operation functions: compare equal
  ////////////////////////////////////////////////////////////////////////

  printf("Testing operation functions: compare equal\n");

  // xip_fpo_equal
  xip_fpo_set_flt(a, 3.0);
  xip_fpo_set_flt(b, 0.5);
  exc = xip_fpo_equal(&res_int, a, b);  // normal operation, differing inputs
  if (exc != 0) {
    printf("ERROR: xip_fpo_equal: compare 3.0 and 0.5: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (res_int != 0) {
    printf("ERROR: xip_fpo_equal: compare 3.0 and 0.5: result %d does not match expected value 0\n", res_int);
    return -1;
  }
  exc = xip_fpo_equal(&res_int, t, c);  // inputs are not the same precision: operation not supported
  if (exc != 16) {
    printf("ERROR: xip_fpo_equal: compare FP(4.4) and FP(11.53): expected operation not supported (exc=16), but got exc=%d\n", exc);
    return -1;
  }
  xip_fpo_set_flt(b, 3.0);
  exc = xip_fpo_equal(&res_int, a, b);  // normal operation, equal inputs
  if (exc != 0) {
    printf("ERROR: xip_fpo_equal: compare 3.0 and 3.0: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (res_int != 1) {
    printf("ERROR: xip_fpo_equal: compare 3.0 and 3.0: result %d does not match expected value 1\n", res_int);
    return -1;
  }
  xip_fpo_set_zero(c, 1);
  xip_fpo_set_zero(d, -1);
  exc = xip_fpo_equal(&res_int, c, d);  // normal operation, plus zero and minus zero: expect equal
  if (exc != 0) {
    printf("ERROR: xip_fpo_equal: compare 0.0 and -0.0: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (res_int != 1) {
    printf("ERROR: xip_fpo_equal: compare 0.0 and -0.0: result %d does not match expected value 1\n", res_int);
    return -1;
  }
  xip_fpo_set_nan(d);
  exc = xip_fpo_equal(&res_int, d, d);  // normal operation, both inputs are NaN: expect not equal
  if (exc != 0) {
    printf("ERROR: xip_fpo_equal: compare NaN and NaN: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (res_int != 0) {
    printf("ERROR: xip_fpo_equal: compare NaN and NaN: result %d does not match expected value 0\n", res_int);
    return -1;
  }

  // xip_fpo_equal_flt, xip_fpo_equal_d
  exc = xip_fpo_equal_flt(&res_int, (float) 17.6, (float) -3.2);  // normal operation
  if (exc != 0) {
    printf("ERROR: xip_fpo_equal_flt: compare 17.6 and -3.2: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (res_int != 0) {
    printf("ERROR: xip_fpo_equal_flt: compare 17.6 and -3.2: result %d does not match expected value 0\n", res_int);
    return -1;
  }
  exc = xip_fpo_equal_flt(&res_int, (float) 1.4e38, (float) 1.4e38);  // equal inputs
  if (exc != 0) {
    printf("ERROR: xip_fpo_equal_flt: compare 1.4e38 and 1.4e38: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (res_int != 1) {
    printf("ERROR: xip_fpo_equal_flt: compare 1.4e38 and 1.4e38: result %d does not match expected value 1\n", res_int);
    return -1;
  }
  exc = xip_fpo_equal_d(&res_int, (double) 243.56079356, (double) 141.045956204);  // normal operation
  if (exc != 0) {
    printf("ERROR: xip_fpo_equal_d: compare 243.56079356 and 141.045956204: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (res_int != 0) {
    printf("ERROR: xip_fpo_equal_d: compare 243.56079356 and 141.045956204: result %d does not match expected value 0\n", res_int);
    return -1;
  }
  exc = xip_fpo_equal_d(&res_int, inf_d, inf_d);  // normal operation, both inputs infinity
  if (exc != 0) {
    printf("ERROR: xip_fpo_equal_d: compare Infinity and Infinity: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (res_int != 1) {
    printf("ERROR: xip_fpo_equal_d: compare Infinity and Infinity: result %d does not match expected value 1\n", res_int);
    return -1;
  }


  ////////////////////////////////////////////////////////////////////////
  // Operation functions: compare less than
  ////////////////////////////////////////////////////////////////////////

  printf("Testing operation functions: compare less than\n");

  // xip_fpo_less
  xip_fpo_set_flt(a, 3.0);
  xip_fpo_set_flt(b, 0.5);
  exc = xip_fpo_less(&res_int, a, b);  // normal operation, op1 not less than op2
  if (exc != 0) {
    printf("ERROR: xip_fpo_less: compare 3.0 and 0.5: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (res_int != 0) {
    printf("ERROR: xip_fpo_less: compare 3.0 and 0.5: result %d does not match expected value 0\n", res_int);
    return -1;
  }
  exc = xip_fpo_less(&res_int, t, u);  // inputs are not the same precision: operation not supported
  if (exc != 16) {
    printf("ERROR: xip_fpo_less: compare FP(4.4) and FP(16.64): expected operation not supported (exc=16), but got exc=%d\n", exc);
    return -1;
  }
  exc = xip_fpo_less(&res_int, b, a);  // normal operation, op1 less than op2
  if (exc != 0) {
    printf("ERROR: xip_fpo_less: compare 0.5 and 3.0: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (res_int != 1) {
    printf("ERROR: xip_fpo_less: compare 0.5 and 3.0: result %d does not match expected value 1\n", res_int);
    return -1;
  }
  xip_fpo_set_zero(c, -1);
  xip_fpo_set_zero(d, 1);
  exc = xip_fpo_less(&res_int, c, d);  // normal operation, minus zero and plus zero: expect not less (considered equal)
  if (exc != 0) {
    printf("ERROR: xip_fpo_less: compare -0.0 and 0.0: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (res_int != 0) {
    printf("ERROR: xip_fpo_less: compare -0.0 and 0.0: result %d does not match expected value 0\n", res_int);
    return -1;
  }
  xip_fpo_set_nan(d);
  exc = xip_fpo_less(&res_int, c, d);  // one input is NaN: invalid operation
  if (exc != 4) {
    printf("ERROR: xip_fpo_less: compare -0.0 and NaN: expected invalid operation (exc=4), but got exc=%d\n", exc);
    return -1;
  }
  if (res_int != 0) {
    printf("ERROR: xip_fpo_less: compare -0.0 and NaN: result %d does not match expected value 0 following invalid operation\n", res_int);
    return -1;
  }

  // xip_fpo_less_flt, xip_fpo_less_d
  exc = xip_fpo_less_flt(&res_int, (float) 17.6, (float) -3.2);  // normal operation
  if (exc != 0) {
    printf("ERROR: xip_fpo_less_flt: compare 17.6 and -3.2: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (res_int != 0) {
    printf("ERROR: xip_fpo_less_flt: compare 17.6 and -3.2: result %d does not match expected value 0\n", res_int);
    return -1;
  }
  exc = xip_fpo_less_flt(&res_int, (float) -1.4e38, (float) 1.4e38);  // op1 less than op2
  if (exc != 0) {
    printf("ERROR: xip_fpo_less_flt: compare -1.4e38 and 1.4e38: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (res_int != 1) {
    printf("ERROR: xip_fpo_less_flt: compare -1.4e38 and 1.4e38: result %d does not match expected value 1\n", res_int);
    return -1;
  }
  exc = xip_fpo_less_d(&res_int, (double) 243.56079356, (double) 141.045956204);  // normal operation
  if (exc != 0) {
    printf("ERROR: xip_fpo_less_d: compare 243.56079356 and 141.045956204: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (res_int != 0) {
    printf("ERROR: xip_fpo_less_d: compare 243.56079356 and 141.045956204: result %d does not match expected value 0\n", res_int);
    return -1;
  }
  exc = xip_fpo_less_d(&res_int, -inf_d, inf_d);  // inputs -/+infinity, op1 < op2
  if (exc != 0) {
    printf("ERROR: xip_fpo_less_d: compare -Infinity and Infinity: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (res_int != 1) {
    printf("ERROR: xip_fpo_less_d: compare -Infinity and Infinity: result %d does not match expected value 1\n", res_int);
    return -1;
  }


  ////////////////////////////////////////////////////////////////////////
  // Operation functions: compare less than or equal
  ////////////////////////////////////////////////////////////////////////

  printf("Testing operation functions: compare less than or equal\n");

  // xip_fpo_lessequal
  xip_fpo_set_flt(a, 3.0);
  xip_fpo_set_flt(b, 0.5);
  exc = xip_fpo_lessequal(&res_int, a, b);  // normal operation, op1 not less than or equal to op2
  if (exc != 0) {
    printf("ERROR: xip_fpo_lessequal: compare 3.0 and 0.5: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (res_int != 0) {
    printf("ERROR: xip_fpo_lessequal: compare 3.0 and 0.5: result %d does not match expected value 0\n", res_int);
    return -1;
  }
  exc = xip_fpo_lessequal(&res_int, t, a);  // inputs are not the same precision: operation not supported
  if (exc != 16) {
    printf("ERROR: xip_fpo_lessequal: compare FP(4.4) and FP(8.24): expected operation not supported (exc=16), but got exc=%d\n", exc);
    return -1;
  }
  exc = xip_fpo_lessequal(&res_int, b, a);  // normal operation, op1 less than op2
  if (exc != 0) {
    printf("ERROR: xip_fpo_lessequal: compare 0.5 and 3.0: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (res_int != 1) {
    printf("ERROR: xip_fpo_lessequal: compare 0.5 and 3.0: result %d does not match expected value 1\n", res_int);
    return -1;
  }
  xip_fpo_set_flt(b, 3.0);
  exc = xip_fpo_lessequal(&res_int, a, b);  // normal operation, op1 equals op2
  if (exc != 0) {
    printf("ERROR: xip_fpo_lessequal: compare 3.0 and 3.0: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (res_int != 1) {
    printf("ERROR: xip_fpo_lessequal: compare 3.0 and 3.0: result %d does not match expected value 1\n", res_int);
    return -1;
  }
  xip_fpo_set_zero(c, 1);
  xip_fpo_set_zero(d, -1);
  exc = xip_fpo_lessequal(&res_int, c, d);  // normal operation, plus zero and minus zero: expect equal
  if (exc != 0) {
    printf("ERROR: xip_fpo_lessequal: compare 0.0 and -0.0: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (res_int != 1) {
    printf("ERROR: xip_fpo_lessequal: compare 0.0 and -0.0: result %d does not match expected value 1\n", res_int);
    return -1;
  }
  xip_fpo_set_nan(t);
  exc = xip_fpo_lessequal(&res_int, t, t);  // both inputs are NaN: invalid operation
  if (exc != 4) {
    printf("ERROR: xip_fpo_lessequal: compare NaN and NaN: expected invalid operation (exc=4), but got exc=%d\n", exc);
    return -1;
  }
  if (res_int != 0) {
    printf("ERROR: xip_fpo_lessequal: compare NaN and NaN: result %d does not match expected value 0 following invalid operation\n", res_int);
    return -1;
  }

  // xip_fpo_lessequal_flt, xip_fpo_lessequal_d
  exc = xip_fpo_lessequal_flt(&res_int, (float) 17.6, (float) -3.2);  // normal operation
  if (exc != 0) {
    printf("ERROR: xip_fpo_lessequal_flt: compare 17.6 and -3.2: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (res_int != 0) {
    printf("ERROR: xip_fpo_lessequal_flt: compare 17.6 and -3.2: result %d does not match expected value 0\n", res_int);
    return -1;
  }
  exc = xip_fpo_lessequal_flt(&res_int, (float) -1.4e38, (float) 1.4e38);  // op1 less than op2
  if (exc != 0) {
    printf("ERROR: xip_fpo_lessequal_flt: compare -1.4e38 and 1.4e38: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (res_int != 1) {
    printf("ERROR: xip_fpo_lessequal_flt: compare -1.4e38 and 1.4e38: result %d does not match expected value 1\n", res_int);
    return -1;
  }
  exc = xip_fpo_lessequal_d(&res_int, (double) 243.56079356, (double) 141.045956204);  // normal operation
  if (exc != 0) {
    printf("ERROR: xip_fpo_lessequal_d: compare 243.56079356 and 141.045956204: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (res_int != 0) {
    printf("ERROR: xip_fpo_lessequal_d: compare 243.56079356 and 141.045956204: result %d does not match expected value 0\n", res_int);
    return -1;
  }
  exc = xip_fpo_lessequal_d(&res_int, inf_d, inf_d);  // both inputs infinity
  if (exc != 0) {
    printf("ERROR: xip_fpo_lessequal_d: compare Infinity and Infinity: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (res_int != 1) {
    printf("ERROR: xip_fpo_lessequal_d: compare Infinity and Infinity: result %d does not match expected value 1\n", res_int);
    return -1;
  }


  ////////////////////////////////////////////////////////////////////////
  // Operation functions: compare greater than
  ////////////////////////////////////////////////////////////////////////

  printf("Testing operation functions: compare greater than\n");

  // xip_fpo_greater
  xip_fpo_set_flt(a, 3.0);
  xip_fpo_set_flt(b, 0.5);
  exc = xip_fpo_greater(&res_int, a, b);  // normal operation, op1 greater than op2
  if (exc != 0) {
    printf("ERROR: xip_fpo_greater: compare 3.0 and 0.5: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (res_int != 1) {
    printf("ERROR: xip_fpo_greater: compare 3.0 and 0.5: result %d does not match expected value 1\n", res_int);
    return -1;
  }
  exc = xip_fpo_greater(&res_int, t, y);  // inputs are not the same precision: operation not supported
  if (exc != 16) {
    printf("ERROR: xip_fpo_greater: compare FP(4.4) and FP(11.53): expected operation not supported (exc=16), but got exc=%d\n", exc);
    return -1;
  }
  exc = xip_fpo_greater(&res_int, b, a);  // normal operation, op1 not greater than op2
  if (exc != 0) {
    printf("ERROR: xip_fpo_greater: compare 0.5 and 3.0: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (res_int != 0) {
    printf("ERROR: xip_fpo_greater: compare 0.5 and 3.0: result %d does not match expected value 0\n", res_int);
    return -1;
  }
  xip_fpo_set_zero(c, 1);
  xip_fpo_set_zero(d, -1);
  exc = xip_fpo_greater(&res_int, c, d);  // normal operation, minus zero and plus zero: expect not greater (considered equal)
  if (exc != 0) {
    printf("ERROR: xip_fpo_greater: compare 0.0 and -0.0: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (res_int != 0) {
    printf("ERROR: xip_fpo_greater: compare 0.0 and -0.0: result %d does not match expected value 0\n", res_int);
    return -1;
  }
  xip_fpo_set_nan(c);
  exc = xip_fpo_greater(&res_int, c, d);  // one input is NaN: invalid operation
  if (exc != 4) {
    printf("ERROR: xip_fpo_greater: compare NaN and -0.0: expected invalid operation (exc=4), but got exc=%d\n", exc);
    return -1;
  }
  if (res_int != 0) {
    printf("ERROR: xip_fpo_greater: compare NaN and -0.0: result %d does not match expected value 0 following invalid operation\n", res_int);
    return -1;
  }

  // xip_fpo_greater_flt, xip_fpo_greater_d
  exc = xip_fpo_greater_flt(&res_int, (float) 17.6, (float) -3.2);  // normal operation
  if (exc != 0) {
    printf("ERROR: xip_fpo_greater_flt: compare 17.6 and -3.2: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (res_int != 1) {
    printf("ERROR: xip_fpo_greater_flt: compare 17.6 and -3.2: result %d does not match expected value 1\n", res_int);
    return -1;
  }
  exc = xip_fpo_greater_flt(&res_int, -inf_flt, inf_flt);  // inputs -/+infinity, op1 < op2
  if (exc != 0) {
    printf("ERROR: xip_fpo_greater_flt: compare -Infinity and Infinity: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (res_int != 0) {
    printf("ERROR: xip_fpo_greater_flt: compare -Infinity and Infinity: result %d does not match expected value 0\n", res_int);
    return -1;
  }
  exc = xip_fpo_greater_d(&res_int, (double) 243.56079356, (double) 141.045956204);  // normal operation
  if (exc != 0) {
    printf("ERROR: xip_fpo_greater_d: compare 243.56079356 and 141.045956204: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (res_int != 1) {
    printf("ERROR: xip_fpo_greater_d: compare 243.56079356 and 141.045956204: result %d does not match expected value 1\n", res_int);
    return -1;
  }
  exc = xip_fpo_greater_d(&res_int, (double) 1.5e-106, (double) 1.5e-106);  // op1 = op2
  if (exc != 0) {
    printf("ERROR: xip_fpo_greater_d: compare 1.5e-106 and 1.5e-106: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (res_int != 0) {
    printf("ERROR: xip_fpo_greater_d: compare 1.5e-106 and 1.5e-106: result %d does not match expected value 0\n", res_int);
    return -1;
  }


  ////////////////////////////////////////////////////////////////////////
  // Operation functions: compare greater than or equal
  ////////////////////////////////////////////////////////////////////////

  printf("Testing operation functions: compare greater than or equal\n");

  // xip_fpo_greaterequal
  xip_fpo_set_flt(a, 3.0);
  xip_fpo_set_flt(b, 0.5);
  exc = xip_fpo_greaterequal(&res_int, a, b);  // normal operation, op1 greater than or equal to op2
  if (exc != 0) {
    printf("ERROR: xip_fpo_greaterequal: compare 3.0 and 0.5: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (res_int != 1) {
    printf("ERROR: xip_fpo_greaterequal: compare 3.0 and 0.5: result %d does not match expected value 1\n", res_int);
    return -1;
  }
  exc = xip_fpo_greaterequal(&res_int, y, a);  // inputs are not the same precision: operation not supported
  if (exc != 16) {
    printf("ERROR: xip_fpo_greaterequal: compare FP(11.53) and FP(8.24): expected operation not supported (exc=16), but got exc=%d\n", exc);
    return -1;
  }
  exc = xip_fpo_greaterequal(&res_int, b, a);  // normal operation, op1 not greater than op2
  if (exc != 0) {
    printf("ERROR: xip_fpo_greaterequal: compare 0.5 and 3.0: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (res_int != 0) {
    printf("ERROR: xip_fpo_greaterequal: compare 0.5 and 3.0: result %d does not match expected value 0\n", res_int);
    return -1;
  }
  xip_fpo_set_flt(a, 0.5);
  exc = xip_fpo_greaterequal(&res_int, a, b);  // normal operation, op1 equals op2
  if (exc != 0) {
    printf("ERROR: xip_fpo_greaterequal: compare 0.5 and 0.5: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (res_int != 1) {
    printf("ERROR: xip_fpo_greaterequal: compare 0.5 and 0.5: result %d does not match expected value 1\n", res_int);
    return -1;
  }
  xip_fpo_set_zero(c, -1);
  xip_fpo_set_zero(d, 1);
  exc = xip_fpo_greaterequal(&res_int, c, d);  // normal operation, minus zero and plus zero: expect equal
  if (exc != 0) {
    printf("ERROR: xip_fpo_greaterequal: compare -0.0 and 0.0: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (res_int != 1) {
    printf("ERROR: xip_fpo_greaterequal: compare -0.0 and 0.0: result %d does not match expected value 1\n", res_int);
    return -1;
  }
  xip_fpo_set_nan(u);
  exc = xip_fpo_greaterequal(&res_int, u, u);  // both inputs are NaN: invalid operation
  if (exc != 4) {
    printf("ERROR: xip_fpo_greaterequal: compare NaN and NaN: expected invalid operation (exc=4), but got exc=%d\n", exc);
    return -1;
  }
  if (res_int != 0) {
    printf("ERROR: xip_fpo_greaterequal: compare NaN and NaN: result %d does not match expected value 0 following invalid operation\n", res_int);
    return -1;
  }

  // xip_fpo_greaterequal_flt, xip_fpo_greaterequal_d
  exc = xip_fpo_greaterequal_flt(&res_int, (float) -3.2, (float) 17.6);  // normal operation
  if (exc != 0) {
    printf("ERROR: xip_fpo_greaterequal_flt: compare -3.2 and 17.6: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (res_int != 0) {
    printf("ERROR: xip_fpo_greaterequal_flt: compare -3.2 and 17.6: result %d does not match expected value 0\n", res_int);
    return -1;
  }
  exc = xip_fpo_greaterequal_flt(&res_int, -inf_flt, -inf_flt);  // both inputs minus infinity
  if (exc != 0) {
    printf("ERROR: xip_fpo_greaterequal_flt: compare -Infinity and -Infinity: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (res_int != 1) {
    printf("ERROR: xip_fpo_greaterequal_flt: compare -Infinity and -Infinity: result %d does not match expected value 1\n", res_int);
    return -1;
  }
  exc = xip_fpo_greaterequal_d(&res_int, (double) 243.56079356, (double) 141.045956204);  // normal operation
  if (exc != 0) {
    printf("ERROR: xip_fpo_greaterequal_d: compare 243.56079356 and 141.045956204: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (res_int != 1) {
    printf("ERROR: xip_fpo_greaterequal_d: compare 243.56079356 and 141.045956204: result %d does not match expected value 1\n", res_int);
    return -1;
  }
  exc = xip_fpo_greaterequal_d(&res_int, (double) -243.56079356, (double) 141.045956204);  // normal operation, both inputs infinity
  if (exc != 0) {
    printf("ERROR: xip_fpo_greaterequal_d: compare -243.56079356 and 141.045956204: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (res_int != 0) {
    printf("ERROR: xip_fpo_greaterequal_d: compare -243.56079356 and 141.045956204: result %d does not match expected value 0\n", res_int);
    return -1;
  }


  ////////////////////////////////////////////////////////////////////////
  // Operation functions: compare not equal
  ////////////////////////////////////////////////////////////////////////

  printf("Testing operation functions: compare not equal\n");

  // xip_fpo_notequal
  xip_fpo_set_flt(a, 3.0);
  xip_fpo_set_flt(b, 0.5);
  exc = xip_fpo_notequal(&res_int, a, b);  // normal operation, differing inputs
  if (exc != 0) {
    printf("ERROR: xip_fpo_notequal: compare 3.0 and 0.5: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (res_int != 1) {
    printf("ERROR: xip_fpo_notequal: compare 3.0 and 0.5: result %d does not match expected value 1\n", res_int);
    return -1;
  }
  exc = xip_fpo_notequal(&res_int, t, d);  // inputs are not the same precision: operation not supported
  if (exc != 16) {
    printf("ERROR: xip_fpo_notequal: compare FP(4.4) and FP(11.53): expected operation not supported (exc=16), but got exc=%d\n", exc);
    return -1;
  }
  xip_fpo_set_flt(b, 3.0);
  exc = xip_fpo_notequal(&res_int, a, b);  // normal operation, equal inputs
  if (exc != 0) {
    printf("ERROR: xip_fpo_notequal: compare 3.0 and 3.0: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (res_int != 0) {
    printf("ERROR: xip_fpo_notequal: compare 3.0 and 3.0: result %d does not match expected value 0\n", res_int);
    return -1;
  }
  xip_fpo_set_zero(c, 1);
  xip_fpo_set_zero(d, -1);
  exc = xip_fpo_notequal(&res_int, c, d);  // normal operation, plus zero and minus zero: expect equal
  if (exc != 0) {
    printf("ERROR: xip_fpo_notequal: compare 0.0 and -0.0: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (res_int != 0) {
    printf("ERROR: xip_fpo_notequal: compare 0.0 and -0.0: result %d does not match expected value 0\n", res_int);
    return -1;
  }
  xip_fpo_set_nan(u);
  exc = xip_fpo_notequal(&res_int, u, u);  // normal operation, both inputs are NaN: expect not equal
  if (exc != 0) {
    printf("ERROR: xip_fpo_notequal: compare NaN and NaN: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (res_int != 1) {
    printf("ERROR: xip_fpo_notequal: compare NaN and NaN: result %d does not match expected value 1\n", res_int);
    return -1;
  }

  // xip_fpo_notequal_flt, xip_fpo_notequal_d
  exc = xip_fpo_notequal_flt(&res_int, (float) 17.6, (float) -3.2);  // normal operation
  if (exc != 0) {
    printf("ERROR: xip_fpo_notequal_flt: compare 17.6 and -3.2: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (res_int != 1) {
    printf("ERROR: xip_fpo_notequal_flt: compare 17.6 and -3.2: result %d does not match expected value 1\n", res_int);
    return -1;
  }
  exc = xip_fpo_notequal_flt(&res_int, (float) 1.4e38, (float) 1.4e38);  // equal inputs
  if (exc != 0) {
    printf("ERROR: xip_fpo_notequal_flt: compare 1.4e38 and 1.4e38: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (res_int != 0) {
    printf("ERROR: xip_fpo_notequal_flt: compare 1.4e38 and 1.4e38: result %d does not match expected value 0\n", res_int);
    return -1;
  }
  exc = xip_fpo_notequal_d(&res_int, (double) 243.56079356, (double) 141.045956204);  // normal operation
  if (exc != 0) {
    printf("ERROR: xip_fpo_notequal_d: compare 243.56079356 and 141.045956204: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (res_int != 1) {
    printf("ERROR: xip_fpo_notequal_d: compare 243.56079356 and 141.045956204: result %d does not match expected value 1\n", res_int);
    return -1;
  }
  exc = xip_fpo_notequal_d(&res_int, -inf_d, -inf_d);  // normal operation, both inputs minus infinity
  if (exc != 0) {
    printf("ERROR: xip_fpo_notequal_d: compare -Infinity and -Infinity: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (res_int != 0) {
    printf("ERROR: xip_fpo_notequal_d: compare -Infinity and -Infinity: result %d does not match expected value 0\n", res_int);
    return -1;
  }


  ////////////////////////////////////////////////////////////////////////
  // Operation functions: compare condition code
  ////////////////////////////////////////////////////////////////////////

  printf("Testing operation functions: compare condition code\n");

  // xip_fpo_condcode
  xip_fpo_set_flt(a, 3.0);
  xip_fpo_set_flt(b, 0.5);
  exc = xip_fpo_condcode(&res_int, a, b);  // normal operation
  if (exc != 0) {
    printf("ERROR: xip_fpo_condcode: compare 3.0 and 0.5: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (res_int != 4) {  // greater than
    printf("ERROR: xip_fpo_condcode: compare 3.0 and 0.5: result %d does not match expected value 4\n", res_int);
    return -1;
  }
  exc = xip_fpo_condcode(&res_int, a, c);  // inputs are not the same precision: operation not supported
  if (exc != 16) {
    printf("ERROR: xip_fpo_condcode: compare FP(8.24) and FP(11.53): expected operation not supported (exc=16), but got exc=%d\n", exc);
    return -1;
  }
  exc = xip_fpo_condcode(&res_int, b, a);  // normal operation, inputs swapped
  if (exc != 0) {
    printf("ERROR: xip_fpo_condcode: compare 0.5 and 3.0: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (res_int != 2) {  // less than
    printf("ERROR: xip_fpo_condcode: compare 0.5 and 3.0: result %d does not match expected value 2\n", res_int);
    return -1;
  }
  xip_fpo_set_flt(b, 3.0);
  exc = xip_fpo_condcode(&res_int, a, b);  // normal operation, equal inputs
  if (exc != 0) {
    printf("ERROR: xip_fpo_condcode: compare 3.0 and 3.0: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (res_int != 1) {  // equal
    printf("ERROR: xip_fpo_condcode: compare 3.0 and 3.0: result %d does not match expected value 1\n", res_int);
    return -1;
  }
  xip_fpo_set_zero(c, 1);
  xip_fpo_set_zero(d, -1);
  exc = xip_fpo_condcode(&res_int, c, d);  // normal operation, plus zero and minus zero: expect equal
  if (exc != 0) {
    printf("ERROR: xip_fpo_condcode: compare 0.0 and -0.0: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (res_int != 1) {  // equal
    printf("ERROR: xip_fpo_condcode: compare 0.0 and -0.0: result %d does not match expected value 1\n", res_int);
    return -1;
  }
  xip_fpo_set_nan(d);
  exc = xip_fpo_condcode(&res_int, c, d);  // normal operation, one input is NaN: expect unordered
  if (exc != 0) {
    printf("ERROR: xip_fpo_condcode: compare 0.0 and NaN: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (res_int != 8) {  // unordered
    printf("ERROR: xip_fpo_condcode: compare 0.0 and NaN: result %d does not match expected value 8\n", res_int);
    return -1;
  }

  // xip_fpo_condcode_flt, xip_fpo_condcode_d
  exc = xip_fpo_condcode_flt(&res_int, (float) 17.6, (float) -3.2);  // normal operation
  if (exc != 0) {
    printf("ERROR: xip_fpo_condcode_flt: compare 17.6 and -3.2: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (res_int != 4) {  // greater than
    printf("ERROR: xip_fpo_condcode_flt: compare 17.6 and -3.2: result %d does not match expected value 4\n", res_int);
    return -1;
  }
  exc = xip_fpo_condcode_flt(&res_int, (float) -1.2e-14, (float) 4.6e29);  // normal operation
  if (exc != 0) {
    printf("ERROR: xip_fpo_condcode_flt: compare -1.2e-14 and 4.6e29: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (res_int != 2) {  // less than
    printf("ERROR: xip_fpo_condcode_flt: compare -1.2e-14 and 4.6e29: result %d does not match expected value 2\n", res_int);
    return -1;
  }
  exc = xip_fpo_condcode_flt(&res_int, (float) 1.4e38, (float) 1.4e38);  // equal inputs
  if (exc != 0) {
    printf("ERROR: xip_fpo_condcode_flt: compare 1.4e38 and 1.4e38: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (res_int != 1) {  // equal
    printf("ERROR: xip_fpo_condcode_flt: compare 1.4e38 and 1.4e38: result %d does not match expected value 1\n", res_int);
    return -1;
  }
  exc = xip_fpo_condcode_flt(&res_int, nan_flt, nan_flt);  // both inputs are NaN
  if (exc != 0) {
    printf("ERROR: xip_fpo_condcode_flt: compare NaN and NaN: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (res_int != 8) {  // unordered
    printf("ERROR: xip_fpo_condcode_flt: compare NaN and NaN: result %d does not match expected value 8\n", res_int);
    return -1;
  }
  exc = xip_fpo_condcode_d(&res_int, (double) 243.56079356, (double) 141.045956204);  // normal operation
  if (exc != 0) {
    printf("ERROR: xip_fpo_condcode_d: compare 243.56079356 and 141.045956204: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (res_int != 4) {  // greater than
    printf("ERROR: xip_fpo_condcode_d: compare 243.56079356 and 141.045956204: result %d does not match expected value 4\n", res_int);
    return -1;
  }
  exc = xip_fpo_condcode_d(&res_int, (double) 0.0, (double) 1.2e-302);  // normal operation
  if (exc != 0) {
    printf("ERROR: xip_fpo_condcode_d: compare 0.0 and 1.2e-302: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (res_int != 2) {  // less than
    printf("ERROR: xip_fpo_condcode_d: compare 0.0 and 1.2e-302: result %d does not match expected value 2\n", res_int);
    return -1;
  }
  exc = xip_fpo_condcode_d(&res_int, inf_d, inf_d);  // both inputs infinity
  if (exc != 0) {
    printf("ERROR: xip_fpo_condcode_d: compare Infinity and Infinity: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (res_int != 1) {  // equal
    printf("ERROR: xip_fpo_condcode_d: compare Infinity and Infinity: result %d does not match expected value 1\n", res_int);
    return -1;
  }
  exc = xip_fpo_condcode_d(&res_int, inf_d, nan_d);  // one input NaN
  if (exc != 0) {
    printf("ERROR: xip_fpo_condcode_d: compare Infinity and NaN: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (res_int != 8) {  // unordered
    printf("ERROR: xip_fpo_condcode_d: compare Infinity and NaN: result %d does not match expected value 8\n", res_int);
    return -1;
  }


  ////////////////////////////////////////////////////////////////////////
  // Operation functions: convert float to fixed
  ////////////////////////////////////////////////////////////////////////

  printf("Testing operation functions: convert float to fixed\n");

  // xip_fpo_flttofix
  xip_fpo_set_flt(a, 3.0);
  exc = xip_fpo_flttofix(afix, a);  // normal operation: FX(32.0) = (FP(8.24)) 3.0
  if (exc != 0) {
    printf("ERROR: xip_fpo_flttofix: FX(32.0) = (FP(8.24)) 3.0: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  res_flt = xip_fpo_fix_get_flt(afix);
  delta_flt = FLT_EPSILON;  // acceptable difference between result and expected values due to rounding
  if (fabsf(res_flt - 3.0) > delta_flt) {
    printf("ERROR: xip_fpo_flttofix: FX(32.0) = (FP(8.24)) 3.0: result %f does not match expected value 3.0\n", res_flt);
    return -1;
  }
  exc = xip_fpo_flttofix(afix, t);  // input and output have incompatible precisions: operation not supported
  if (exc != 16) {
    printf("ERROR: xip_fpo_flttofix: FX(32.0) = FP(4.4): expected operation not supported (exc=16), but got exc=%d\n", exc);
    return -1;
  }
  xip_fpo_set_d(c, 1.5);
  exc = xip_fpo_flttofix(ufix, c);  // normal operation: FX(64.0) = (FP(11.53)) 1.5
  if (exc != 0) {
    printf("ERROR: xip_fpo_flttofix: FX(64.0) = (FP(11.53)) 1.5: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  res_flt = xip_fpo_fix_get_flt(ufix);
  if (fabsf(res_flt - 2.0) > delta_flt) {  // expect round to nearest even integer
    printf("ERROR: xip_fpo_flttofix: FX(64.0) = (FP(11.53)) 1.5: result %f does not match expected value 2.0\n", res_flt);
    return -1;
  }
  xip_fpo_set_d(c, 1.75);
  exc = xip_fpo_flttofix(tfix, c);  // normal operation: FX(3.1) = (FP(11.53)) 1.75
  if (exc != 0) {
    printf("ERROR: xip_fpo_flttofix: FX(3.1) = (FP(11.53)) 1.75: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  res_flt = xip_fpo_fix_get_flt(tfix);
  if (fabsf(res_flt - 2.0) > delta_flt) {  // expect round to nearest even last fractional bit, i.e. nearest integer
    printf("ERROR: xip_fpo_flttofix: FX(3.1) = (FP(11.53)) 1.75: result %f does not match expected value 2.0\n", res_flt);
    return -1;
  }
  xip_fpo_set_d(c, -14.0);
  exc = xip_fpo_flttofix(tfix, c);  // input is too large for output precision: expect overflow
  if (exc != 2) {
    printf("ERROR: xip_fpo_flttofix: FX(3.1) = (FP(11.53)) -14.0: expected overflow (exc=2), but got exc=%d\n", exc);
    return -1;
  }
  res_flt = xip_fpo_fix_get_flt(tfix);
  if (fabsf(res_flt - (-4.0)) > delta_flt) {  // expect saturated most negative value
    printf("ERROR: xip_fpo_flttofix: FX(3.1) = (FP(11.53)) -14.0: result %f does not match expected value -4.0 following overflow\n", res_flt);
    return -1;
  }
  xip_fpo_set_inf(d, -1);
  exc = xip_fpo_flttofix(yfix, d);  // input is -Infinity, expect invalid operation and overflow
  if (exc != 6) {
    printf("ERROR: xip_fpo_flttofix: FX(32.32) = (FP(11.53)) -Infinity: expected invalid operation and overflow (exc=6), but got exc=%d\n", exc);
    return -1;
  }
  res_sj = xip_fpo_fix_get_sj(yfix);
  expected_sj = -((uintmax_t) 1 << 31);  // largest negative number that can be stored in FX(32.32)
  if (res_sj != expected_sj) {  // expect saturated most negative value
    printf("ERROR: xip_fpo_flttofix: FX(32.32) = (FP(11.53)) -Infinity: result %lld does not match expected value %lld following overflow\n", res_sj, expected_sj);
    return -1;
  }
  xip_fpo_set_nan(a);
  exc = xip_fpo_flttofix(xfix, a);  // input is NaN: expect invalid operation and saturated most negative result
  if (exc != 4) {
    printf("ERROR: xip_fpo_flttofix: FX(32.0) = (FP(8.24)) NaN: expected invalid operation (exc=4), but got exc=%d\n", exc);
    return -1;
  }
  res_sj = xip_fpo_fix_get_sj(xfix);
  expected_sj = -((uintmax_t) 1 << 31);  // largest negative number that can be stored in FX(32.32)
  if (res_sj != expected_sj) {  // expect saturated most negative value
    printf("ERROR: xip_fpo_flttofix: FX(32.0) = (FP(8.24)) NaN: result %lld does not match expected value %lld\n", res_sj, expected_sj);
    return -1;
  }

  // xip_fpo_flttofix_int_flt, xip_fpo_flttofix_int_d
  exc = xip_fpo_flttofix_int_flt(&res_int, (float) 17.6);  // normal operation
  if (exc != 0) {
    printf("ERROR: xip_fpo_flttofix_int_flt: int = (float) 17.6: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  int expected_int = 18;
  if (res_int != expected_int) {
    printf("ERROR: xip_fpo_flttofix_int_flt: int = (float) 17.6: result %d does not match expected value %d\n", res_int, expected_int);
    return -1;
  }
  exc = xip_fpo_flttofix_int_flt(&res_int, (float) -2.9e12);  // large negative number, expect overflow
  if (exc != 2) {
    printf("ERROR: xip_fpo_flttofix_int_flt: int = (float) -2.9e12: expected overflow (exc=2), but got exc=%d\n", exc);
    return -1;
  }
  expected_int = INT_MIN;  // saturated most negative integer value
  if (res_int != expected_int) {
    printf("ERROR: xip_fpo_flttofix_int_flt: int = (float) -2.9e12: result %d does not match expected value %d\n", res_int, expected_int);
    return -1;
  }
  exc = xip_fpo_flttofix_int_d(&res_int, (double) 243.56079356);  // normal operation
  if (exc != 0) {
    printf("ERROR: xip_fpo_flttofix_int_d: int = (double) 243.56079356: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  expected_int = 244;
  if (res_int != expected_int) {
    printf("ERROR: xip_fpo_flttofix_int_d: int = (double) 243.56079356: result %d does not match expected value %d\n", res_int, expected_int);
    return -1;
  }
  exc = xip_fpo_flttofix_int_d(&res_int, inf_d);  // Infinity, expect invalid operation and overflow
  if (exc != 6) {
    printf("ERROR: xip_fpo_flttofix_int_d: int = (double) Infinity: expected invalid operation and overflow (exc=6), but got exc=%d\n", exc);
    return -1;
  }
  expected_int = INT_MAX;  // saturated most positive integer value
  if (res_int != expected_int) {
    printf("ERROR: xip_fpo_flttofix_int_d: int = (double) Infinity: result %d does not match expected value %d\n", res_int, expected_int);
    return -1;
  }


  ////////////////////////////////////////////////////////////////////////
  // Operation functions: convert fixed to float
  ////////////////////////////////////////////////////////////////////////

  printf("Testing operation functions: convert fixed to float\n");

  // xip_fpo_fixtoflt
  xip_fpo_fix_set_flt(afix, 3.0);
  exc = xip_fpo_fixtoflt(a, afix);  // normal operation: FP(8.24) = (FX(32.0)) 3.0
  if (exc != 0) {
    printf("ERROR: xip_fpo_fixtoflt: FP(8.24) = (FX(32.0)) 3.0: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  res_flt = xip_fpo_get_flt(a);
  delta_flt = FLT_EPSILON;  // acceptable difference between result and expected values due to rounding
  if (fabsf(res_flt - 3.0) > delta_flt) {
    printf("ERROR: xip_fpo_fixtoflt: FP(8.24) = (FX(32.0)) 3.0: result %f does not match expected value 3.0\n", res_flt);
    return -1;
  }
  exc = xip_fpo_fixtoflt(t, afix);  // input and output have incompatible precisions: operation not supported
  if (exc != 16) {
    printf("ERROR: xip_fpo_fixtoflt: FP(4.4) = FX(32.0): expected operation not supported (exc=16), but got exc=%d\n", exc);
    return -1;
  }
  expected_sj = 0x7a6702b59f356012LL;
  exc = xip_fpo_fix_set_sj(ufix, expected_sj);  // large number, requires 64 bits to represent
  exc = xip_fpo_fixtoflt(a, ufix);  // normal operation: FP(8.24) = (FX(64.0)) (large number)
  if (exc != 0) {
    printf("ERROR: xip_fpo_fixtoflt: FP(8.24) = (FX(64.0)) (large number): no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  res_sj = xip_fpo_get_sj(a);
  intmax_t delta_sj = ((intmax_t) 1 << (63 - 24));  // 1 ulp at single precision (24-bit mantissa) when exponent = 0b63
  intmax_t diff_sj = res_sj - expected_sj;
  if (diff_sj < 0) diff_sj = -diff_sj;  // no abs() function for intmax_t type, use this expression instead
  if (diff_sj > delta_sj) {
    printf("ERROR: xip_fpo_fixtoflt: FP(8.24) = (FX(64.0)) (large number): result %lld does not match expected value %lld\n", res_sj, expected_sj);
    return -1;
  }

  // xip_fpo_fixtoflt_flt_int, xip_fpo_fixtoflt_d_int
  exc = xip_fpo_fixtoflt_flt_int(&res_flt, (int) 18);  // normal operation
  if (exc != 0) {
    printf("ERROR: xip_fpo_fixtoflt_flt_int: float = (int) 18: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  delta_flt = FLT_EPSILON;  // acceptable difference between result and expected values due to rounding
  expected_flt = 18.0;
  if (fabsf(res_flt - expected_flt) > delta_flt) {
    printf("ERROR: xip_fpo_fixtoflt_flt_int: float = (int) 18: result %f does not match expected value %f\n", res_flt, expected_flt);
    return -1;
  }
  exc = xip_fpo_fixtoflt_flt_int(&res_flt, (int) 2.14e9);  // normal operation with large input value
  if (exc != 0) {
    printf("ERROR: xip_fpo_fixtoflt_flt_int: float = (int) 2.14e9: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  expected_flt = 2.14e9;
  if (fabsf(res_flt - expected_flt) > delta_flt) {
    printf("ERROR: xip_fpo_fixtoflt_flt_int: float = (int) 2.14e9: result %f does not match expected value %f\n", res_flt, expected_flt);
    return -1;
  }
  exc = xip_fpo_fixtoflt_d_int(&res_d, (int) 243);  // normal operation
  if (exc != 0) {
    printf("ERROR: xip_fpo_fixtoflt_d_int: double = (int) 243: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  delta_d = DBL_EPSILON;  // acceptable difference between result and expected values due to rounding
  expected_d = 243.0;
  if (fabs(res_d - expected_d) > delta_d) {
    printf("ERROR: xip_fpo_fixtoflt_d_int: double = (int) 243: result %f does not match expected value %f\n", res_d, expected_d);
    return -1;
  }
  exc = xip_fpo_fixtoflt_d_int(&res_d, (int) 0);  // normal operation with zero input value
  if (exc != 0) {
    printf("ERROR: xip_fpo_fixtoflt_d_int: double = (int) 0: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  expected_d = 0.0;
  if (fabs(res_d - expected_d) > delta_d) {
    printf("ERROR: xip_fpo_fixtoflt_d_int: double = (int) 0: result %f does not match expected value %f\n", res_d, expected_d);
    return -1;
  }


  ////////////////////////////////////////////////////////////////////////
  // Operation functions: convert float to float
  ////////////////////////////////////////////////////////////////////////

  printf("Testing operation functions: convert float to float\n");

  // xip_fpo_flttoflt
  xip_fpo_set_flt(a, 3.0);
  exc = xip_fpo_flttoflt(y, a);  // normal operation: FP(11.53) = (FP(8.24)) 3.0
  if (exc != 0) {
    printf("ERROR: xip_fpo_flttoflt: FP(11.53) = (FP(8.24)) 3.0: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  res_d = xip_fpo_get_d(y);
  delta_d = DBL_EPSILON;  // acceptable difference between result and expected values due to rounding
  if (fabs(res_d - 3.0) > delta_d) {
    printf("ERROR: xip_fpo_flttoflt: FP(11.53) = (FP(8.24)) 3.0: result %f does not match expected value 3.0\n", res_d);
    return -1;
  }
  xip_fpo_set_d(c, -5.75);
  exc = xip_fpo_flttoflt(t, c);  // normal operation: FP(4.4) = (FP(11.53)) -5.75: expect round to nearest
  if (exc != 0) {
    printf("ERROR: xip_fpo_flttoflt: FP(4.4) = (FP(11.53)) -5.75: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  res_d = xip_fpo_get_d(t);
  if (fabs(res_d - (-6.0)) > delta_d) {  // expect 06.0 due to rounding to FP(4.4) format
    printf("ERROR: xip_fpo_flttoflt: FP(4.4) = (FP(11.53)) -5.75: result %f does not match expected value -6.0\n", res_d);
    return -1;
  }
  xip_fpo_set_flt(a, 248.0);
  exc = xip_fpo_flttoflt(t, a);  // FP(4.4) = (FP(8.24)) 248.0: too large for output precision: expect overflow
  if (exc != 2) {
    printf("ERROR: xip_fpo_flttoflt: FP(4.4) = (FP(8.24)) 248.0: expected overflow (exc=2), but got exc=%d\n", exc);
    return -1;
  }
  res_d = xip_fpo_get_d(t);
  if (res_d != inf_d) {  // expect infinity following overflow
    printf("ERROR: xip_fpo_flttoflt: FP(4.4) = (FP(8.24)) 248.0: result %f does not match expected value Infinity following overflow\n", res_d);
    return -1;
  }
  xip_fpo_set_d(c, -2.3e-106);
  exc = xip_fpo_flttoflt(x, c);  // FP(8.24) = (FP(11.53)) -2.3e-106: too small for output precision: expect underflow
  if (exc != 1) {
    printf("ERROR: xip_fpo_flttoflt: FP(8.24) = (FP(11.53)) -2.3e-106: expected underflow (exc=1), but got exc=%d\n", exc);
    return -1;
  }
  res_str = xip_fpo_get_str(res_str, &res_exp, 10, 2, x);  // use xip_fpo_get_str to distinguish minus and plus zero
  if (strcmp(res_str, "-00") != 0) {  // expect 2 digits of minus zero, exponent is not used
    printf("ERROR: xip_fpo_flttoflt: result %s does not match expected value -00 following underflow\n", res_str);
    return -1;
  }
  xip_fpo_set_nan(t);
  exc = xip_fpo_flttoflt(u, t);  // FP(16.64) = (FP(4.4)) NaN: no exceptions, precision is irrelevant with NaN input
  if (exc != 0) {
    printf("ERROR: xip_fpo_flttoflt: FP(16.64) = (FP(4.4)) NaN: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  // Can't use xip_fpo_get_flt(u) and compare to nan_flt, because the comparison NaN == NaN returns false
  // Use xip_fpo_get_str instead
  res_str = xip_fpo_get_str(res_str, &res_exp, 8, 0, u);
  if (strcmp(res_str, "@NaN@") != 0) {  // expect NaN, exponent is not used
    printf("ERROR: xip_fpo_sqrt: FP(16.64) = (FP(4.4)) NaN: result %s does not match expected result @NaN@\n", res_str);
    return -1;
  }

  // xip_fpo_flttoflt_flt_flt, xip_fpo_flttoflt_flt_d, xip_fpo_flttoflt_d_flt, xip_fpo_flttoflt_d_d
  exc = xip_fpo_flttoflt_flt_flt(&res_flt, (float) 17.6);  // normal operation
  if (exc != 0) {
    printf("ERROR: xip_fpo_flttoflt_flt_flt: float = (float) 17.6: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  expected_flt = 17.6;
  if (res_flt != expected_flt) {
    printf("ERROR: xip_fpo_flttoflt_flt_flt: float = (float) 17.6: result %f does not match expected value %f\n", res_flt, expected_flt);
    return -1;
  }
  exc = xip_fpo_flttoflt_flt_flt(&res_flt, (float) 1.0e-41);  // denormalized input, expect conditioned zero output
  if (exc != 0) {
    printf("ERROR: xip_fpo_flttoflt_flt_flt: float = (float) 1.0e-41: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  expected_flt = 0.0;
  if (res_flt != expected_flt) {
    printf("ERROR: xip_fpo_flttoflt_flt_flt: float = (float) 1.0e-41: result %f does not match expected value %f\n", res_flt, expected_flt);
    return -1;
  }
  // To test conditioning of signalling NaNs, the float NaN value must be bit-manipulated to make it a signalling NaN
  snan_flt.f = nan_flt;  // quiet NaN
  snan_flt.i &= 0x7f800000;  // clear sign bit and all mantissa bits
  snan_flt.i |= 0x001f8e47;  // set some mantissa bits
  exc = xip_fpo_flttoflt_flt_flt(&res_flt, snan_flt.f);  // signalling NaN input, expect conditioned quiet NaN output
  if (exc != 0) {
    printf("ERROR: xip_fpo_flttoflt_flt_flt: float = (float) signalling NaN: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  snan_flt_res.f = res_flt;
  snan_flt_expected.f = nan_flt;  // quiet NaN (expected value)
  if (snan_flt_res.i != snan_flt_expected.i) {  // compare integer representations, as float NaN == NaN returns false
    printf("ERROR: xip_fpo_flttoflt_flt_flt: float = (float) signalling NaN: result %f (encoding 0x%x) does not match expected value %f (encoding 0x%x)\n", snan_flt_res.f, snan_flt_res.i, snan_flt_expected.f, snan_flt_expected.i);
    return -1;
  }
  exc = xip_fpo_flttoflt_flt_d(&res_flt, (double) 243.56079356);  // normal operation
  if (exc != 0) {
    printf("ERROR: xip_fpo_flttoflt_flt_d: float = (double) 243.56079356: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  expected_flt = (float) 243.56079356;
  if (res_flt != expected_flt) {
    printf("ERROR: xip_fpo_flttoflt_flt_flt: float = (double) 243.56079356: result %f does not match expected value %f\n", res_flt, expected_flt);
    return -1;
  }
  exc = xip_fpo_flttoflt_flt_d(&res_flt, (double) -6.97e41);  // large negative input, expect overflow
  if (exc != 2) {
    printf("ERROR: xip_fpo_flttoflt_flt_d: float = (double) -6.97e41: expected overflow (exc=2), but got exc=%d\n", exc);
    return -1;
  }
  if (res_flt != -inf_flt) {  // expect -Infinity following overflow
    printf("ERROR: xip_fpo_flttoflt_flt_d: float = (double) -6.97e41: result %f does not match expected value -Infinity following overflow\n", res_flt);
    return -1;
  }
  exc = xip_fpo_flttoflt_flt_d(&res_flt, (double) 3.9e-112);  // very small input, expect underflow
  if (exc != 1) {
    printf("ERROR: xip_fpo_flttoflt_flt_d: float = (double) 3.9e-112: expected underflow (exc=1), but got exc=%d\n", exc);
    return -1;
  }
  if (res_flt != 0.0) {  // expect zero following underflow
    printf("ERROR: xip_fpo_flttoflt_flt_d: float = (double) 3.9e-112: result %f does not match expected value 0.0 following underflow\n", res_flt);
    return -1;
  }
  exc = xip_fpo_flttoflt_d_flt(&res_d, (float) -3.2);  // normal operation
  if (exc != 0) {
    printf("ERROR: xip_fpo_flttoflt_d_flt: double = (float) -3.2: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  expected_d = (double) ((float) -3.2);
  if (res_d != expected_d) {
    printf("ERROR: xip_fpo_flttoflt_d_flt: double = (float) -3.2: result %f does not match expected value %f\n", res_d, expected_d);
    return -1;
  }
  exc = xip_fpo_flttoflt_d_flt(&res_d, -inf_flt);  // normal operation, -Infinity input
  if (exc != 0) {
    printf("ERROR: xip_fpo_flttoflt_d_flt: double = (float) -Infinity: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  if (res_d != -inf_d) {  // expect -Infinity in double precision
    printf("ERROR: xip_fpo_flttoflt_d_flt: double = (float) -Infinity: result %f does not match expected value -Infinity\n", res_d);
    return -1;
  }
  exc = xip_fpo_flttoflt_d_flt(&res_d, nan_flt);  // normal operation, NaN input
  if (exc != 0) {
    printf("ERROR: xip_fpo_flttoflt_d_flt: double = (float) NaN: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  // Can't check the NaN result directly as double NaN == NaN returns false: compare bitwise representations
  snan_d_res.f = res_d;  // result
  snan_d_expected.f = nan_d;  // quiet NaN (expected value)
  if (snan_d_res.i != snan_d_expected.i) {  // compare integer representations, as double NaN == NaN returns false
    printf("ERROR: xip_fpo_flttoflt_d_flt: double = (float) NaN: result %f (encoding 0x%x) does not match expected value %f (encoding 0x%x)\n", snan_d_res.f, snan_d_res.i, snan_d_expected.f, snan_d_expected.i);
    return -1;
  }
  exc = xip_fpo_flttoflt_d_d(&res_d, (double) 141.045956204);  // normal operation
  if (exc != 0) {
    printf("ERROR: xip_fpo_flttoflt_d_d: double = (double) 141.045956204: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  expected_d = 141.045956204;
  if (res_d != expected_d) {
    printf("ERROR: xip_fpo_flttoflt_d_d: double = (double) 141.045956204: result %f does not match expected value %f\n", res_d, expected_d);
    return -1;
  }
  exc = xip_fpo_flttoflt_d_d(&res_d, (double) -1.4e-317);  // denormalized input, expect conditioned zero output
  if (exc != 0) {
    printf("ERROR: xip_fpo_flttoflt_d_d: double = (double) -1.4e-317: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  expected_d = -0.0;
  if (res_d != expected_d) {
    printf("ERROR: xip_fpo_flttoflt_d_d: double = (double) -1.4e-317: result %f does not match expected value -0.0\n", res_d, expected_d);
    return -1;
  }
  // To test conditioning of signalling NaNs, the double NaN value must be bit-manipulated to make it a signalling NaN
  snan_d.f = nan_d;  // quiet NaN
  snan_d.i &= (xint64) 0x7ff0000000000000LL;  // clear sign bit and all mantissa bits
  snan_d.i |= (xint64) 0x00079b13a9cc0215LL;  // set some mantissa bits
  exc = xip_fpo_flttoflt_d_d(&res_d, snan_d.f);  // signalling NaN input, expect conditioned quiet NaN output
  if (exc != 0) {
    printf("ERROR: xip_fpo_flttoflt_d_d: double = (double) signalling NaN: no exceptions expected (exc=0), but got exc=%d\n", exc);
    return -1;
  }
  snan_d_res.f = res_d;
  snan_d_expected.f = nan_d;  // quiet NaN (expected value)
  if (snan_d_res.i != snan_d_expected.i) {  // compare integer representations, as float NaN == NaN returns false
    printf("ERROR: xip_fpo_flttoflt_d_d: float = (float) signalling NaN: result %f (encoding %#llx) does not match expected value %f (encoding %#llx)\n", snan_d_res.f, snan_d_res.i, snan_d_expected.f, snan_d_expected.i);
    return -1;
  }


  ////////////////////////////////////////////////////////////////////////
  // Tidy up after tests
  ////////////////////////////////////////////////////////////////////////

  printf("Calling clear functions\n");

  xip_fpo_clears(a, b, x, c, d, y, t, u, (xip_fpo_ptr) 0);
  xip_fpo_fix_clears(afix, bfix, xfix, cfix, dfix, yfix, tfix, ufix, (xip_fpo_fix_ptr) 0);
  mpz_clear(z);
  mpz_clear(res_z);
  mpq_clear(q);
  mpf_clear(f);
  mpf_clear(res_f);
  mpfr_clears(fr, res_fr, expected_fr_d, expected_fr_flt, (mpfr_ptr) 0);

  printf("All functions tested successfully\n");
  return 0;

}
