/** \addtogroup platform */
/** @{*/
/**
 * \defgroup platform_toolchain Toolchain functions
 * @{
 */

/* mbed Microcontroller Library
 * Copyright (c) 2006-2013 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/* form mbed by huaweiwx@sina.com 2017.12.5*/

#ifndef _UTILSDEF_H_
#define _UTILSDEF_H_

// Warning for unsupported compilers
#if !defined(__GNUC__)   /* GCC        */ \
 && !defined(__CC_ARM)   /* ARMCC      */ \
 && !defined(__clang__)  /* LLVM/Clang */ \
 && !defined(__ICCARM__) /* IAR        */
#warning "This compiler is not yet supported."
#endif



/** DEPRECATED("message string")
 *  Mark a function declaration as deprecated, if it used then a warning will be
 *  issued by the compiler possibly including the provided message. Note that not
 *  all compilers are able to display the message.
 *
 *  @code
 *
 *  DEPRECATED("don't foo any more, bar instead")
 *  void foo(int arg);
 *  @endcode
 */
#ifndef DEPRECATED
#if defined(__CC_ARM)
#define DEPRECATED(M) __attribute__((deprecated))
#elif defined(__GNUC__) || defined(__clang__)
#define DEPRECATED(M) __attribute__((deprecated(M)))
#else
#define DEPRECATED(M)
#endif
#endif

/** DEPRECATED_SINCE("version", "message string")
 *  Mark a function declaration as deprecated, noting that the declaration was
 *  deprecated on the specified version. If the function is used then a warning
 *  will be issued by the compiler possibly including the provided message.
 *  Note that not all compilers are able to display this message.
 *
 *  @code
 *
 *  DEPRECATED_SINCE("mbed-os-5.1", "don't foo any more, bar instead")
 *  void foo(int arg);
 *  @endcode
 */
#define DEPRECATED_SINCE(D, M) DEPRECATED(M " [since " D "]")

/** CALLER_ADDR()
 * Returns the caller of the current function.
 *
 * @note
 * This macro is only implemented for GCC and ARMCC.
 *
 * @code
 *
 * printf("This function was called from %p", CALLER_ADDR());
 * @endcode
 *
 * @return Address of the calling function
 */
#ifndef CALLER_ADDR
#if (defined(__GNUC__) || defined(__clang__)) && !defined(__CC_ARM)
#define CALLER_ADDR() __builtin_extract_return_addr(__builtin_return_address(0))
#elif defined(__CC_ARM)
#define CALLER_ADDR() __builtin_return_address(0)
#else
#define CALLER_ADDR() (NULL)
#endif
#endif

/**
 * Macro expanding to a string literal of the enclosing function name.
 *
 * The string returned takes into account language specificity and yield human
 * readable content.
 *
 * As an example, if the macro is used within a C++ function then the string
 * literal containing the function name will contain the complete signature of
 * the function - including template parameters - and namespace qualifications.
 */
#ifndef PRETTY_FUNCTION
#define PRETTY_FUNCTION __PRETTY_FUNCTION__
#endif

#ifndef PRINTF
#if defined(__GNUC__) || defined(__CC_ARM)
#define PRINTF(format_idx, first_param_idx) __attribute__ ((__format__(__printf__, format_idx, first_param_idx)))
#else
#define PRINTF(format_idx, first_param_idx)
#endif
#endif

#ifndef PRINTF_METHOD
#if defined(__GNUC__) || defined(__CC_ARM)
#define PRINTF_METHOD(format_idx, first_param_idx) __attribute__ ((__format__(__printf__, format_idx+1, first_param_idx+1)))
#else
#define PRINTF_METHOD(format_idx, first_param_idx)
#endif
#endif

#ifndef SCANF
#if defined(__GNUC__) || defined(__CC_ARM)
#define SCANF(format_idx, first_param_idx) __attribute__ ((__format__(__scanf__, format_idx, first_param_idx)))
#else
#define SCANF(format_idx, first_param_idx)
#endif
#endif

#ifndef SCANF_METHOD
#if defined(__GNUC__) || defined(__CC_ARM)
#define SCANF_METHOD(format_idx, first_param_idx) __attribute__ ((__format__(__scanf__, format_idx+1, first_param_idx+1)))
#else
#define SCANF_METHOD(format_idx, first_param_idx)
#endif
#endif

// FILEHANDLE declaration
//#if defined(TOOLCHAIN_ARM)
//#include <rt_sys.h>
//#endif

#ifndef FILEHANDLE
typedef int FILEHANDLE;
#endif

#endif

