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
 * \file examples/simple_graph.cpp
 * \brief An example of a simple graph, when a type for edge is not necessary.
 * \author Leandro Costa
 * \date 2011
 *
 * $LastChangedDate: 2011-02-14 17:37:10 -0200 (Seg, 14 Fev 2011) $
 * $LastChangedBy: leandro.costa@gmail.com $
 * $Revision: 122 $
 */


#include "cgt/graph.h"

int main ()
{
	cgt::graph<int> g;

	g.insert_vertex (1);
	g.insert_vertex (2);
	g.insert_vertex (3);
	g.insert_vertex (4);

	g.insert_edge (1, 2);
	g.insert_edge (2, 3);
	g.insert_edge (2, 4);

	cgt::graph<int>::const_iterator itn;
	cgt::graph<int>::const_iterator itnEnd = g.end ();

	for (itn = g.begin (); itn != itnEnd; ++itn)
	{
		const cgt::graph<int>::node&     n = *itn;
		const cgt::graph<int>::vertex&  v = n.vertex ();

		std::cout << "vertex: " << v.value () << std::endl;

		const cgt::graph<int>::adjlist &adjList = n.adjlist ();

		cgt::graph<int>::adjlist::const_iterator itadj;
		cgt::graph<int>::adjlist::const_iterator itadjEnd = adjList.end ();

		for (itadj = adjList.begin (); itadj != itadjEnd; ++itadj)
		{
			const cgt::graph<int>::edge&     e   = itadj->edge ();
			const cgt::graph<int>::vertex&  v1  = e.v1 ();
			const cgt::graph<int>::vertex&  v2  = e.v2 ();

			std::cout << "  edge (" << v1.value () << ", " << v2.value () << ")" << std::endl;
		}
	}

	return 0;
}
