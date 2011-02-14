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
 * \file tests/cgt/base/heap_cxx.h
 * \brief Contains unit tests for class cgt::base::heap.
 * \author Leandro Costa
 * \date 2009
 *
 * $LastChangedDate: 2009-11-24 22:12:23 -0200 (Tue, 24 Nov 2009) $
 * $LastChangedBy: leandro.costa $
 * $Revision: 83 $
 */

#ifndef __CGTL__CXXTEST_CGT_BASE_HEAP_CXX_H_
#define __CGTL__CXXTEST_CGT_BASE_HEAP_CXX_H_

#include <cxxtest/TestSuite.h>
#include "cgt/misc/cxxtest_defs.h"
#include "cgt/base/heap.h"


class heap_cxx : public CxxTest::TestSuite
{
  public:
    void setUp () { }
    void tearDown () { } 

  public:
    void test_basic ()
    {
      cgt::base::heap<int> h;
      TS_ASSERT_EQUALS (h.size (), static_cast<size_t>(0));
      TS_ASSERT_EQUALS (h.empty (), true);
    }

    void test_push ()
    {
      cgt::base::heap<int> h;
      h.push (1);
      TS_ASSERT_EQUALS (h.size (), static_cast<size_t>(1));
      TS_ASSERT_EQUALS (h.empty (), false);
    }

    //void test_find ()
    //{
    //  cgt::base::heap<int> h;
    //  h.push (1);
    //  TS_ASSERT_DIFFERS (h.find (1), h.end ());
    //  TS_ASSERT_EQUALS (*(h.find (1)), 1);
    //}

    void test_clear ()
    {
      cgt::base::heap<int> h;
      h.push (1);
      TS_ASSERT_EQUALS (h.size (), static_cast<size_t>(1));
      h.clear ();
      TS_ASSERT_EQUALS (h.size (), static_cast<size_t>(0));
      TS_ASSERT_EQUALS (h.empty (), true);
    }

    void test_pop ()
    {
      cgt::base::heap<int> h;
      h.push (2);
      h.push (1);
      h.push (3);
      TS_ASSERT_EQUALS (h.size (), static_cast<size_t>(3));
      int* p = h.pop ();
      TS_ASSERT_EQUALS (h.size (), static_cast<size_t>(2));
      TS_ASSERT_EQUALS (*p, 1);
      delete p;
    }

    void test_modify ()
    {
      cgt::base::heap<int> h;
      h.push (5);
      h.push (4);
      h.push (3);
      h.push (2);
      h.push (1);

      int* p = h.pop ();
      TS_ASSERT_EQUALS (*p, 1);
      delete p;

#ifdef CGTL_DO_NOT_USE_STL
      cgt::base::heap<int>::const_iterator it = h.find (2);
#else
	  cgt::base::heap<int>::const_iterator it = std::find (h.begin (), h.end (), 2);
#endif
//      cgt::base::heap<int>::iterator it = h.find (2);
      h.modify (it, 6);
//      h.modify (static_cast<const cgt::base::heap<int> &>(h).find (2), 6);
//      h.modify (static_cast<cgt::base::heap<int>::const_iterator&>(static_cast<const cgt::base::heap<int> &>(h).find (2)), 6);
//      h.modify (h.find (2), 6);
      p = h.pop ();
      TS_ASSERT_EQUALS (*p, 3);
      delete p;
    }

    void test_constructor_copy ()
    {
      cgt::base::heap<int> h1;
      h1.push (1);
      h1.push (2);
      h1.push (3);
      cgt::base::heap<int> h2 (h1);

      TS_ASSERT_EQUALS (h1.size (), h2.size ());

#ifdef CGTL_DO_NOT_USE_STL
      TS_ASSERT_EQUALS (*(h1.find (1)), *(h2.find (1)));
      TS_ASSERT_EQUALS (*(h1.find (2)), *(h2.find (2)));
      TS_ASSERT_EQUALS (*(h1.find (3)), *(h2.find (3)));

      TS_ASSERT_DIFFERS (&(*(h1.find (1))), &(*(h2.find (1))));
      TS_ASSERT_DIFFERS (&(*(h1.find (2))), &(*(h2.find (2))));
      TS_ASSERT_DIFFERS (&(*(h1.find (3))), &(*(h2.find (3))));
#else
      TS_ASSERT_EQUALS (*(std::find (h1.begin (), h1.end (), 1)), *(std::find (h2.begin (), h2.end (), 1)));
      //TS_ASSERT_EQUALS (*(h1.find (2)), *(h2.find (2)));
      //TS_ASSERT_EQUALS (*(h1.find (3)), *(h2.find (3)));

      //TS_ASSERT_DIFFERS (&(*(h1.find (1))), &(*(h2.find (1))));
      //TS_ASSERT_DIFFERS (&(*(h1.find (2))), &(*(h2.find (2))));
      //TS_ASSERT_DIFFERS (&(*(h1.find (3))), &(*(h2.find (3))));
#endif
    }

    void test_operator_assign ()
    {
      cgt::base::heap<int> h1;
      h1.push (1);
      h1.push (2);
      h1.push (3);
      cgt::base::heap<int> h2;
      h2 = h1;

      TS_ASSERT_EQUALS (h1.size (), h2.size ());

#ifdef CGTL_DO_NOT_USE_STL
      TS_ASSERT_EQUALS (*(h1.find (1)), *(h2.find (1)));
      TS_ASSERT_EQUALS (*(h1.find (2)), *(h2.find (2)));
      TS_ASSERT_EQUALS (*(h1.find (3)), *(h2.find (3)));

      TS_ASSERT_DIFFERS (&(*(h1.find (1))), &(*(h2.find (1))));
      TS_ASSERT_DIFFERS (&(*(h1.find (2))), &(*(h2.find (2))));
      TS_ASSERT_DIFFERS (&(*(h1.find (3))), &(*(h2.find (3))));
#else
      TS_ASSERT_EQUALS (*(std::find (h1.begin (), h1.end (), 1)), *(std::find (h2.begin (), h2.end (), 1)));
      //TS_ASSERT_EQUALS (*(h1.find (2)), *(h2.find (2)));
      //TS_ASSERT_EQUALS (*(h1.find (3)), *(h2.find (3)));

      //TS_ASSERT_DIFFERS (&(*(h1.find (1))), &(*(h2.find (1))));
      //TS_ASSERT_DIFFERS (&(*(h1.find (2))), &(*(h2.find (2))));
      //TS_ASSERT_DIFFERS (&(*(h1.find (3))), &(*(h2.find (3))));
#endif
    }
};

#endif // __CGTL__CXXTEST_CGT_BASE_HEAP_CXX_H_
