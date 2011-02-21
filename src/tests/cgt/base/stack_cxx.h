/*
 * CGTL - A graph template library for C++
 * ---------------------------------------
 * Copyright (C) 2009 Leandro Costa
 *
 * This file is part of CGTL.
 *
 * CGTL is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * CGTL is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with CGTL. If not, see <http://www.gnu.org/licenses/>.
 */

/*!
 * \file tests/cgt/base/stack_cxx.h
 * \brief Contains unit tests for class cgt::base::stack.
 * \author Leandro Costa
 * \date 2009
 *
 * $LastChangedDate: 2009-11-24 22:12:23 -0200 (Tue, 24 Nov 2009) $
 * $LastChangedBy: leandro.costa $
 * $Revision: 83 $
 */

#ifndef __CGTL__CXXTEST_CGT_BASE_STACK_CXX_H_
#define __CGTL__CXXTEST_CGT_BASE_STACK_CXX_H_

#include <cxxtest/TestSuite.h>
#include "cgt/misc/cxxtest_defs.h"
#include "cgt/base/stack.h"


class stack_cxx : public CxxTest::TestSuite
{
  public:
    void setUp () { }
    void tearDown () { } 

  public:
    void test_basic ()
    {
      cgt::base::stack<int> s;
      TS_ASSERT_EQUALS (s.size (), static_cast<size_t>(0));
      TS_ASSERT_EQUALS (s.empty (), true);
    }

    void test_insert ()
    {
      cgt::base::stack<int> s;
      s.insert (1);
      TS_ASSERT_EQUALS (s.size (), static_cast<size_t>(1));
      TS_ASSERT_EQUALS (s.empty (), false);
      TS_ASSERT_EQUALS (s.top (), 1);
    }

//    void test_find ()
//    {
//      cgt::base::stack<int> s;
//      s.insert (1);
//      TS_ASSERT_DIFFERS (s.find (1), s.end ());
//      TS_ASSERT_EQUALS (*(s.find (1)), 1);
//    }

    void test_clear ()
    {
      cgt::base::stack<int> s;
      s.insert (1);
      TS_ASSERT_EQUALS (s.size (), static_cast<size_t>(1));
      s.clear ();
      TS_ASSERT_EQUALS (s.size (), static_cast<size_t>(0));
      TS_ASSERT_EQUALS (s.empty (), true);
    }

    void test_pop ()
    {
      cgt::base::stack<int> s;
      s.insert (1);
      s.insert (2);
      s.insert (3);
      TS_ASSERT_EQUALS (s.size (), static_cast<size_t>(3));
      TS_ASSERT_EQUALS (s.top (), 3);
      int* p = s.pop ();
      TS_ASSERT_EQUALS (s.size (), static_cast<size_t>(2));
      TS_ASSERT_EQUALS (s.top (), 2);
      delete p;
    }

    void test_constructor_copy ()
    {
      cgt::base::stack<int> s1;
      s1.insert (1);
      s1.insert (2);
      s1.insert (3);
      cgt::base::stack<int> s2 (s1);

      TS_ASSERT_EQUALS (s1.size (), s2.size ());
    }

    void test_operator_assign ()
    {
      cgt::base::stack<int> s1;
      s1.insert (1);
      s1.insert (2);
      s1.insert (3);
      cgt::base::stack<int> s2;
      s2 = s1;

      TS_ASSERT_EQUALS (s1.size (), s2.size ());
    }
};

#endif // __CGTL__CXXTEST_CGT_BASE_STACK_CXX_H_
