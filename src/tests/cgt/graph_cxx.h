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
 * \file tests/cgt/graph_cxx.h
 * \brief Functional tests for graphs.
 * \author Leandro Costa
 * \date 2011
 *
 * $LastChangedDate: 2011-02-14 17:37:10 -0200 (Seg, 14 Fev 2011) $
 * $LastChangedBy: leandro.costa@gmail.com $
 * $Revision: 122 $
 */

#ifndef __CGTL__CXXTEST_CGT_GRAPH_CXX_H_
#define __CGTL__CXXTEST_CGT_GRAPH_CXX_H_


#include <cxxtest/TestSuite.h>
#include "cgt/misc/cxxtest_defs.h"
#include "cgt/graph.h"

class list_cxx : public CxxTest::TestSuite
{
	private:
		cgt::graph<int> g;
		cgt::graph<int>::const_iterator itn;
		cgt::graph<int>::adjlist::const_iterator itadj;

	public:
		void setUp ()
		{
			g.insert_vertex (1);
			g.insert_vertex (2);
			g.insert_vertex (3);
			g.insert_vertex (4);

			g.insert_edge (1, 2);
			g.insert_edge (2, 3);
			g.insert_edge (2, 4);

			itn = g.begin ();
		}

		void tearDown () { }

	public:
		void test_node_iteration ()
		{
			TS_ASSERT_EQUALS (1, (itn++)->vertex ().value ());
			TS_ASSERT_EQUALS (2, (itn++)->vertex ().value ());
			TS_ASSERT_EQUALS (3, (itn++)->vertex ().value ());
			TS_ASSERT_EQUALS (4, (itn++)->vertex ().value ());
			TS_ASSERT_EQUALS (g.end (), itn);
		}

		void test_adjlist_iteration ()
		{
			itadj = itn->adjlist ().begin ();
			TS_ASSERT_EQUALS (2, itadj->edge ().v2 ().value ());
			TS_ASSERT_EQUALS (itn->adjlist ().end (), ++itadj);

			++itn;
			itadj = itn->adjlist ().begin ();
			TS_ASSERT_EQUALS (3, itadj->edge ().v2 ().value ());
			TS_ASSERT_EQUALS (4, (++itadj)->edge ().v2 ().value ());
			TS_ASSERT_EQUALS (itn->adjlist ().end (), ++itadj);
			++itn;
			TS_ASSERT_EQUALS (true, itn->adjlist ().empty ());
			++itn;
			TS_ASSERT_EQUALS (true, itn->adjlist ().empty ());
		}
};

#endif // __CGTL__CXXTEST_CGT_GRAPH_CXX_H_
