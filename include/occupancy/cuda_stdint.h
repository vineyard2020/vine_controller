/*
 * Copyright 2018 Foundation for Research and Technology - Hellas
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0 [1] [1]
 *
 * Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
 *  implied.
 * See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 * Links:
 *  ------
 * [1] http://www.apache.org/licenses/LICENSE-2.0 [1]
*/
/*
 * Copyright 2009-2015 NVIDIA Corporation.  All rights reserved.
 *
 * NOTICE TO LICENSEE:
 *
 * This source code and/or documentation ("Licensed Deliverables") are
 * subject to NVIDIA intellectual property rights under U.S. and
 * international Copyright laws.
 *
 * These Licensed Deliverables contained herein is PROPRIETARY and
 * CONFIDENTIAL to NVIDIA and is being provided under the terms and
 * conditions of a form of NVIDIA software license agreement by and
 * between NVIDIA and Licensee ("License Agreement") or electronically
 * accepted by Licensee.  Notwithstanding any terms or conditions to
 * the contrary in the License Agreement, reproduction or disclosure
 * of the Licensed Deliverables to any third party without the express
 * written consent of NVIDIA is prohibited.
 *
 * NOTWITHSTANDING ANY TERMS OR CONDITIONS TO THE CONTRARY IN THE
 * LICENSE AGREEMENT, NVIDIA MAKES NO REPRESENTATION ABOUT THE
 * SUITABILITY OF THESE LICENSED DELIVERABLES FOR ANY PURPOSE.  IT IS
 * PROVIDED "AS IS" WITHOUT EXPRESS OR IMPLIED WARRANTY OF ANY KIND.
 * NVIDIA DISCLAIMS ALL WARRANTIES WITH REGARD TO THESE LICENSED
 * DELIVERABLES, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY,
 * NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE.
 * NOTWITHSTANDING ANY TERMS OR CONDITIONS TO THE CONTRARY IN THE
 * LICENSE AGREEMENT, IN NO EVENT SHALL NVIDIA BE LIABLE FOR ANY
 * SPECIAL, INDIRECT, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, OR ANY
 * DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
 * WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS
 * ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THESE LICENSED DELIVERABLES.
 *
 * U.S. Government End Users.  These Licensed Deliverables are a
 * "commercial item" as that term is defined at 48 C.F.R. 2.101 (OCT
 * 1995), consisting of "commercial computer software" and "commercial
 * computer software documentation" as such terms are used in 48
 * C.F.R. 12.212 (SEPT 1995) and is provided to the U.S. Government
 * only as a commercial end item.  Consistent with 48 C.F.R.12.212 and
 * 48 C.F.R. 227.7202-1 through 227.7202-4 (JUNE 1995), all
 * U.S. Government End Users acquire the Licensed Deliverables with
 * only those rights set forth herein.
 *
 * Any use of the Licensed Deliverables in individual and commercial
 * software must include, in the user documentation and internal
 * comments to the code, the above Disclaimer and U.S. Government End
 * Users Notice.
 */

#ifndef __cuda_stdint_h__
#define __cuda_stdint_h__

// Compiler-specific treatment for C99's stdint.h
//
// By default, this header will use the standard headers (so it
// is your responsibility to make sure they are available), except
// on MSVC before Visual Studio 2010, when they were not provided.
// To support old MSVC, a few of the commonly-used definitions are
// provided here.  If more definitions are needed, add them here,
// or replace these definitions with a complete implementation,
// such as the ones available from Google, Boost, or MSVC10.  You
// can prevent the definition of any of these types (in order to
// use your own) by #defining CU_STDINT_TYPES_ALREADY_DEFINED.

#if !defined(CU_STDINT_TYPES_ALREADY_DEFINED)

// In VS including stdint.h forces the C++ runtime dep - provide an opt-out
// (CU_STDINT_VS_FORCE_NO_STDINT_H) for users that care (notably static
// cudart).
#if defined(_MSC_VER) && ((_MSC_VER < 1600) || defined(CU_STDINT_VS_FORCE_NO_STDINT_H))

// These definitions can be used with MSVC 8 and 9,
// which don't ship with stdint.h:

typedef            char    int8_t;
typedef unsigned   char   uint8_t;

typedef            short  int16_t;
typedef unsigned   short uint16_t;

typedef            long   int32_t;
typedef unsigned   long  uint32_t;

typedef          __int64  int64_t;
typedef unsigned __int64 uint64_t;

#elif defined(__DJGPP__)

// These definitions can be used when compiling
// C code with DJGPP, which only provides stdint.h
// when compiling C++ code with TR1 enabled.

typedef               char    int8_t;
typedef unsigned      char   uint8_t;

typedef               short  int16_t;
typedef unsigned      short uint16_t;

typedef               long   int32_t;
typedef unsigned      long  uint32_t;

typedef          long long   int64_t;
typedef unsigned long long  uint64_t;

#else

// Use standard headers, as specified by C99 and C++ TR1.
// Known to be provided by:
// - gcc/glibc, supported by all versions of glibc
// - djgpp, supported since 2001
// - MSVC, supported by Visual Studio 2010 and later

#include <stdint.h>

#endif

#endif // !defined(CU_STDINT_TYPES_ALREADY_DEFINED)


#endif // file guard