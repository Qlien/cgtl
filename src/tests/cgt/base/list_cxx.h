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
 * \file tests/cgt/base/list_cxx.h
 * \brief Contains unit tests for class cgt::base::list.
 * \author Leandro Costa
 * \date 2009
 *
 * $LastChangedDate: 2009-11-24 22:12:23 -0200 (Tue, 24 Nov 2009) $
 * $LastChangedBy: leandro.costa $
 * $Revision: 83 $
 */

#ifndef __CGTL__CXXTEST_CGT_BASE_LIST_CXX_H_
#define __CGTL__CXXTEST_CGT_BASE_LIST_CXX_H_

#include <cxxtest/TestSuite.h>
#include "cgt/misc/cxxtest_defs.h"
#include "cgt/base/list.h"


class list_cxx : public CxxTest::TestSuite
{
  public:
    void setUp () { }
    void tearDown () { } 

  public:
    void test_basic ()
    {
      cgt::base::list<int> l;
      TS_ASSERT_EQUALS (l.size (), static_cast<size_t>(0));
      TS_ASSERT_EQUALS (l.empty (), true);
    }

    void test_insert ()
    {
      cgt::base::list<int> l;
      l.push_back (1);
      TS_ASSERT_EQUALS (l.size (), static_cast<size_t>(1));
      TS_ASSERT_EQUALS (l.empty (), false);
      TS_ASSERT_EQUALS (*(l.front ()), 1);
      TS_ASSERT_EQUALS (*(l.back ()), 1);
    }

    void test_find ()
    {
      cgt::base::list<int> l;
      l.push_back (1);
      TS_ASSERT_DIFFERS (l.find (1), l.end ());
      TS_ASSERT_EQUALS (*(l.find (1)), 1);
    }

    void test_clear ()
    {
      cgt::base::list<int> l;
      l.push_back (1);
      TS_ASSERT_EQUALS (l.size (), static_cast<size_t>(1));
      l.clear ();
      TS_ASSERT_EQUALS (l.size (), static_cast<size_t>(0));
      TS_ASSERT_EQUALS (l.empty (), true);
    }

    void test_remove ()
    {
      cgt::base::list<int> l;
      l.push_back (1);
      TS_ASSERT_EQUALS (l.size (), static_cast<size_t>(1));
      l.remove (1);
      TS_ASSERT_EQUALS (l.size (), static_cast<size_t>(0));
      TS_ASSERT_EQUALS (l.empty (), true);
    }

    void test_remove_middle ()
    {
      cgt::base::list<int> l;
      l.push_back (1);
      l.push_back (2);
      l.push_back (3);
      TS_ASSERT_EQUALS (l.size (), static_cast<size_t>(3));
      l.remove (2);
      TS_ASSERT_EQUALS (l.size (), static_cast<size_t>(2));
      TS_ASSERT_EQUALS (*(l.front ()), 1);
      TS_ASSERT_EQUALS (*(l.back ()), 3);
    }

    void test_pop_back ()
    {
      cgt::base::list<int> l;
      l.push_back (1);
      l.push_back (2);
      l.push_back (3);
      TS_ASSERT_EQUALS (l.size (), static_cast<size_t>(3));
      int* p = l.pop_back ();
      TS_ASSERT_EQUALS (l.size (), static_cast<size_t>(2));
      TS_ASSERT_EQUALS (*(l.front ()), 1);
      TS_ASSERT_EQUALS (*(l.back ()), 2);
      delete p;
    }

    void test_pop_front ()
    {
      cgt::base::list<int> l;
      l.push_back (1);
      l.push_back (2);
      l.push_back (3);
      TS_ASSERT_EQUALS (l.size (), static_cast<size_t>(3));
      int* p = l.pop_front ();
      TS_ASSERT_EQUALS (l.size (), static_cast<size_t>(2));
      TS_ASSERT_EQUALS (*(l.front ()), 2);
      TS_ASSERT_EQUALS (*(l.back ()), 3);
      delete p;
    }

    void test_constructor_copy ()
    {
      cgt::base::list<int> l1;
      l1.push_back (1);
      l1.push_back (2);
      l1.push_back (3);
      cgt::base::list<int> l2 (l1);

      TS_ASSERT_EQUALS (l1.size (), l2.size ());

      TS_ASSERT_EQUALS (*(l1.find (1)), *(l2.find (1)));
      TS_ASSERT_EQUALS (*(l1.find (2)), *(l2.find (2)));
      TS_ASSERT_EQUALS (*(l1.find (3)), *(l2.find (3)));

      TS_ASSERT_DIFFERS (&(*(l1.find (1))), &(*(l2.find (1))));
      TS_ASSERT_DIFFERS (&(*(l1.find (2))), &(*(l2.find (2))));
      TS_ASSERT_DIFFERS (&(*(l1.find (3))), &(*(l2.find (3))));
    }

    void test_operator_assign ()
    {
      cgt::base::list<int> l1;
      l1.push_back (1);
      l1.push_back (2);
      l1.push_back (3);
      cgt::base::list<int> l2;
      l2 = l1;

      TS_ASSERT_EQUALS (l1.size (), l2.size ());

      TS_ASSERT_EQUALS (*(l1.find (1)), *(l2.find (1)));
      TS_ASSERT_EQUALS (*(l1.find (2)), *(l2.find (2)));
      TS_ASSERT_EQUALS (*(l1.find (3)), *(l2.find (3)));

      TS_ASSERT_DIFFERS (&(*(l1.find (1))), &(*(l2.find (1))));
      TS_ASSERT_DIFFERS (&(*(l1.find (2))), &(*(l2.find (2))));
      TS_ASSERT_DIFFERS (&(*(l1.find (3))), &(*(l2.find (3))));
    }
};

#endif // __CGTL__CXXTEST_CGT_BASE_LIST_CXX_H_
