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
 * \file tests/cgt/base/queue_cxx.h
 * \brief Contains unit tests for class cgt::base::queue.
 * \author Leandro Costa
 * \date 2009
 *
 * $LastChangedDate: 2009-11-24 22:12:23 -0200 (Tue, 24 Nov 2009) $
 * $LastChangedBy: leandro.costa $
 * $Revision: 83 $
 */

#ifndef __CGTL__CXXTEST_CGT_BASE_QUEUE_CXX_H_
#define __CGTL__CXXTEST_CGT_BASE_QUEUE_CXX_H_

#include <cxxtest/TestSuite.h>
#include "cgt/misc/cxxtest_defs.h"
#include "cgt/base/queue.h"


class queue_cxx : public CxxTest::TestSuite
{
  public:
    void setUp () { }
    void tearDown () { } 

  public:
    void test_basic ()
    {
      cgt::base::queue<int> q;
      TS_ASSERT_EQUALS (q.size (), static_cast<size_t>(0));
      TS_ASSERT_EQUALS (q.empty (), true);
    }

    void test_insert ()
    {
      cgt::base::queue<int> q;
      q.insert (1);
      TS_ASSERT_EQUALS (q.size (), static_cast<size_t>(1));
      TS_ASSERT_EQUALS (q.empty (), false);
      TS_ASSERT_EQUALS (q.first (), 1);
    }

//    void test_find ()
//    {
//      cgt::base::queue<int> q;
//      q.insert (1);
//      TS_ASSERT_DIFFERS (q.find (1), q.end ());
//      TS_ASSERT_EQUALS (*(q.find (1)), 1);
//    }

    void test_clear ()
    {
      cgt::base::queue<int> q;
      q.insert (1);
      TS_ASSERT_EQUALS (q.size (), static_cast<size_t>(1));
      q.clear ();
      TS_ASSERT_EQUALS (q.size (), static_cast<size_t>(0));
      TS_ASSERT_EQUALS (q.empty (), true);
    }

    void test_dequeue ()
    {
      cgt::base::queue<int> q;
      q.insert (1);
      q.insert (2);
      q.insert (3);
      TS_ASSERT_EQUALS (q.size (), static_cast<size_t>(3));
      TS_ASSERT_EQUALS (q.first (), 1);
      int* p = q.dequeue ();
      TS_ASSERT_EQUALS (q.size (), static_cast<size_t>(2));
      TS_ASSERT_EQUALS (q.first (), 2);
      delete p;
    }

    void test_constructor_copy ()
    {
      cgt::base::queue<int> q1;
      q1.insert (1);
      q1.insert (2);
      q1.insert (3);
      cgt::base::queue<int> q2 (q1);

      TS_ASSERT_EQUALS (q1.size (), q2.size ());
    }

    void test_operator_assign ()
    {
      cgt::base::queue<int> q1;
      q1.insert (1);
      q1.insert (2);
      q1.insert (3);
      cgt::base::queue<int> q2;
      q2 = q1;

      TS_ASSERT_EQUALS (q1.size (), q2.size ());
    }
};

#endif // __CGTL__CXXTEST_CGT_BASE_QUEUE_CXX_H_
