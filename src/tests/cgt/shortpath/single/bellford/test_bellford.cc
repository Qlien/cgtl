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
 * \file tests/cgt/shortpath/single/bellford/test_bellford.cc
 * \brief Functional tests for bellford iterator.
 * \author Leandro Costa
 * \date 2011
 *
 * $LastChangedDate: 2011-02-14 17:37:10 -0200 (Seg, 14 Fev 2011) $
 * $LastChangedBy: leandro.costa@gmail.com $
 * $Revision: 122 $
 */


#include <glog/logging.h>
#include "gtest/gtest.h"
#include "cgt/graph.h"


class BellFordTest : public testing::Test {
	protected:
		virtual void SetUp() {
			g = new cgt::graph<int, int>;

			/*
			 *      (2)
			 * 1 --------- 2
			 * |           |
			 * |           |
			 * |(1)        |(10)
			 * |           |
			 * |    (5)    |
			 * 3 --------- 4
			 *
			 */

			v1 = g->insert_vertex(1);
			v2 = g->insert_vertex(2);
			v3 = g->insert_vertex(3);
			v4 = g->insert_vertex(4);

			g->insert_edge(2, v1, v2);
			g->insert_edge(1, v1, v3);

			g->insert_edge(10, v2, v4);
			g->insert_edge(5, v3, v4);
		}

		virtual void TearDown() {
			delete g;
		}

		cgt::graph<int, int>* g;
		cgt::graph<int, int>::iterator v1, v2, v3, v4;
};

TEST_F(BellFordTest, ShouldSetDistance0ToOrigin) {
	cgt::graph<int, int>::bfiterator itd = g->bfbegin (g->find (1));

	EXPECT_EQ(1, itd->vertex ().value ());
	EXPECT_EQ(0, itd.info (*itd)->distance ());
}

TEST_F(BellFordTest, ShouldReturnNextClosestNodeAfterOrigin) {
	cgt::graph<int, int>::bfiterator itd = g->bfbegin (g->find (1));
	++itd;

	EXPECT_EQ(3, itd->vertex ().value ());
	EXPECT_EQ(1, itd.info (*itd)->distance ());
}

TEST_F(BellFordTest, ShouldReturnNodesInDistanceOrder) {
	cgt::graph<int, int>::bfiterator itd = g->bfbegin (g->find (1));

	EXPECT_EQ(1, itd->vertex ().value ());
	EXPECT_EQ(0, itd.info (*itd)->distance ());

	++itd;

	EXPECT_EQ(3, itd->vertex ().value ());
	EXPECT_EQ(1, itd.info (*itd)->distance ());

	++itd;

	EXPECT_EQ(2, itd->vertex ().value ());
	EXPECT_EQ(2, itd.info (*itd)->distance ());

	++itd;

	EXPECT_EQ(4, itd->vertex ().value ());
	EXPECT_EQ(6, itd.info (*itd)->distance ());
}

TEST_F(BellFordTest, ShouldThrowExceptionIfGraphHasNegativeCycles) {
	cgt::graph<int, int>::iterator v5 = g->insert_vertex(5);

	g->insert_edge(-1, v1, v5);
	g->insert_edge(-1, v5, v1);

	ASSERT_THROW(g->bfbegin (g->find (1)), cgt::shortpath::single::bellford::negcycl_except);
}


int main (int argc, char* argv[])
{
	google::InitGoogleLogging(argv[0]);
	::testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}
