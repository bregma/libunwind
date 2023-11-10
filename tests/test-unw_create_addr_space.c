/** @brief Unit tests for unw_create_addr_space() */
/* libunwind - a platform-independent unwind library
 *
 *    Copyright (c) 2023 BlackBerry Limited. All rights reserved.
 * 
 * This file is part of libunwind.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "check.h"
#include "libunwind.h"

static unw_accessors_t acc;

/* Actual contents of accessors is irrelevant */
void setup(void)
{
	memset(&acc, 0, sizeof(acc));
}

void teardown(void)
{
}


START_TEST(function_exists)
{
	unw_addr_space_t (*f)(unw_accessors_t*, int) = unw_create_addr_space;
	ck_assert_msg(f != 0, "function exists");
}

START_TEST(default_byte_order)
{
	unw_addr_space_t as = unw_create_addr_space(&acc, 0);
#ifdef UNW_LOCAL_ONLY
	ck_assert_msg(as == NULL, "should return NULL in local mode");
#else /* UNW_LOCAL_ONLY */
	ck_assert_msg(as != NULL, "should not return NULL in local mode");
	/* need to check if default is sane for build, but API is not exposed */
	ck_assert_msg(0, "XFAIL: expose API for endianness");
#endif /* UNW_LOCAL_ONLY */
}

START_TEST(bigendian_byte_order)
{
#ifdef BIG_ENDIAN
	unw_addr_space_t as = unw_create_addr_space(&acc, BIG_ENDIAN);
# ifdef UNW_LOCAL_ONLY
	ck_assert_msg(as == NULL, "should return NULL in local mode");
# else /* UNW_LOCAL_ONLY */
#  if defined(UNW_TARGET_X86_64)
	ck_assert_msg(as == NULL, "should return NULL in local mode");
#  else /* other targets */
	ck_assert_msg(as != NULL, "should not return NULL in local mode");
	ck_assert_msg(0, "XFAIL: expose API for endianness");
#  endif
# endif /* UNW_LOCAL_ONLY */
#else
	ck_assert_msg(0, "XFAIL: expose UNW_BIG_ENDIAN in public API");
#endif
}

START_TEST(littleendian_byte_order)
{
#ifdef LITTLE_ENDIAN
	unw_addr_space_t as = unw_create_addr_space(&acc, LITTLE_ENDIAN);
# ifdef UNW_LOCAL_ONLY
	ck_assert_msg(as == NULL, "should return NULL in local mode");
# else /* UNW_LOCAL_ONLY */
#  if defined(UNW_TARGET_HPPA) || defined(UNW_TARGET_PPC32) || defined(UNW_TARGET_S390X)
	ck_assert_msg(as == NULL, "should return NULL in local mode");
#  else
	ck_assert_msg(as != NULL, "should not return NULL in local mode");
	ck_assert_msg(0, "XFAIL: expose API for endianness");
#  endif
# endif /* UNW_LOCAL_ONLY */
#else
	ck_assert_msg(0, "XFAIL: expose UNW_LITTLE_ENDIAN in public API");
#endif
}

TCase * case_unw_create_addr_space(void)
{
	TCase * tc = tcase_create("unw_create_addr_space");
	tcase_add_unchecked_fixture(tc, setup, teardown);
	tcase_add_test(tc, function_exists);
	tcase_add_test(tc, default_byte_order);
	tcase_add_test(tc, bigendian_byte_order);
	tcase_add_test(tc, littleendian_byte_order);
	return tc;
}
