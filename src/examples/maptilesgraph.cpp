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
 * \file examples/maptilesgraph.cpp
 * \brief A map tiles's graph example
 * \author Leandro Costa
 * \date 2011
 *
 * $LastChangedDate: 2011-02-13 18:06:26 -0200 (Dom, 13 Fev 2011) $
 * $LastChangedBy: leandro.costa $
 * $Revision: 120 $
 */

#include <ctime>
#include <iostream>
#include <vector>

#include "cgt/graph.h"

class Tile
{
	public:
		Tile () { }
		Tile (unsigned int zoom, unsigned int x, unsigned int y) : mZoom (zoom), mX (x), mY (y) { }

	public:
		Tile& operator=(const Tile& o) { mZoom = o.mZoom; mX = o.mX; mY = o.mY; return *this; }

	public:
		const bool operator==(const Tile& o) const { return (mZoom == o.mZoom && mX == o.mX && mY == o.mY); }

	public:
		unsigned int mZoom;

		unsigned int mX;
		unsigned int mY;
};

typedef cgt::graph<Tile, bool, cgt::_Undirected> TileGraph;
typedef TileGraph::iterator TileGraphIt;
typedef std::vector<TileGraphIt> TileGraphItVector;

class TileInsertRec
{
	public:
		TileGraphItVector itVecTop;
		TileGraphItVector itVecLeft;
		TileGraphItVector itVecRight;
		TileGraphItVector itVecBottom;
};

class TileGraphManager
{
	public:
		static void setMaxZoom (unsigned int z) { msMaxZoom = z; }

		static void add_edges (TileGraph& g, TileGraphItVector& itVec1, TileGraphItVector& itVec2)
		{
			for (TileGraphItVector::iterator it1 = itVec1.begin (); it1 != itVec1.end (); ++it1)
				for (TileGraphItVector::iterator it2 = itVec2.begin (); it2 != itVec2.end (); ++it2)
					g.insert_edge (true, *it1, *it2);
		}

		static TileInsertRec* insert_tiles (TileGraph& g, TileGraphIt parent, unsigned int zoom)
		{
			const Tile& t = parent->vertex ().value ();

			TileGraphIt t00 = g.insert_vertex (Tile (zoom, 2 * t.mX + 0, 2 * t.mY + 0));
			TileGraphIt t01 = g.insert_vertex (Tile (zoom, 2 * t.mX + 0, 2 * t.mY + 1));
			TileGraphIt t10 = g.insert_vertex (Tile (zoom, 2 * t.mX + 1, 2 * t.mY + 0));
			TileGraphIt t11 = g.insert_vertex (Tile (zoom, 2 * t.mX + 1, 2 * t.mY + 1));

			g.insert_edge (true, t00, t01);
			g.insert_edge (true, t00, t10);
			g.insert_edge (true, t01, t11);
			g.insert_edge (true, t10, t11);

			g.insert_edge (true, parent, t00);
			g.insert_edge (true, parent, t01);
			g.insert_edge (true, parent, t10);
			g.insert_edge (true, parent, t11);

			TileInsertRec* pRec = new TileInsertRec ();

			if (zoom < msMaxZoom)
			{
				TileInsertRec* pRec00 = insert_tiles (g, t00, zoom + 1);
				TileInsertRec* pRec01 = insert_tiles (g, t01, zoom + 1);
				TileInsertRec* pRec10 = insert_tiles (g, t10, zoom + 1);
				TileInsertRec* pRec11 = insert_tiles (g, t11, zoom + 1);

				// add edges between 00-right and 10-left boundaries
				add_edges (g, pRec00->itVecRight, pRec10->itVecLeft);

				// add edges between 00-bottom and 01-top boundaries
				add_edges (g, pRec00->itVecBottom, pRec01->itVecTop);

				// add edges between 10-bottom and 11-top boundaries
				add_edges (g, pRec10->itVecBottom, pRec11->itVecTop);

				// add edges between 01-right and 11-left boundaries
				add_edges (g, pRec01->itVecRight, pRec11->itVecLeft);


				// merge 00-top and 10-top
				pRec->itVecTop.insert (pRec->itVecTop.end (), pRec00->itVecTop.begin (), pRec00->itVecTop.end ());
				pRec->itVecTop.insert (pRec->itVecTop.end (), pRec10->itVecTop.begin (), pRec10->itVecTop.end ());

				// merge 00-left and 01-left
				pRec->itVecLeft.insert (pRec->itVecLeft.end (), pRec00->itVecLeft.begin (), pRec00->itVecLeft.end ());
				pRec->itVecLeft.insert (pRec->itVecLeft.end (), pRec01->itVecLeft.begin (), pRec01->itVecLeft.end ());

				// merge 10-right and 11-rigth
				pRec->itVecRight.insert (pRec->itVecRight.end (), pRec10->itVecRight.begin (), pRec10->itVecRight.end ());
				pRec->itVecRight.insert (pRec->itVecRight.end (), pRec11->itVecRight.begin (), pRec11->itVecRight.end ());

				// merge 01-bottom and 11-bottom
				pRec->itVecBottom.insert (pRec->itVecBottom.end (), pRec01->itVecBottom.begin (), pRec01->itVecBottom.end ());
				pRec->itVecBottom.insert (pRec->itVecBottom.end (), pRec11->itVecBottom.begin (), pRec11->itVecBottom.end ());

				delete pRec00;
				delete pRec01;
				delete pRec10;
				delete pRec11;
			}
			//else
			//{
			pRec->itVecTop.push_back (t00);
			pRec->itVecTop.push_back (t10);

			pRec->itVecLeft.push_back (t00);
			pRec->itVecLeft.push_back (t01);

			pRec->itVecRight.push_back (t10);
			pRec->itVecRight.push_back (t11);

			pRec->itVecBottom.push_back (t01);
			pRec->itVecBottom.push_back (t11);
			//}

			return pRec;
		}

	private:
		static unsigned int msMaxZoom;
};

unsigned int TileGraphManager::msMaxZoom;

int main (int argc, char* argv[])
{
	if (argc < 2)
	{
		std::cerr << "run: " << argv[0] << " <max-zoom> (>= 1)" << std::endl;
		return 0;
	}

	TileGraphManager::setMaxZoom (atoi (argv[1]));

	TileGraph g;

	time_t rawtime;
	char buffer[64];

	time (&rawtime);
	strftime (buffer, 64, "%X", localtime (&rawtime));
	std::cout << buffer << " - creating graph..." << std::endl;

	TileGraphIt t000 = g.insert_vertex (Tile (0, 0, 0));
	TileInsertRec* pRec = TileGraphManager::insert_tiles (g, t000, 1);
	delete pRec;

	time (&rawtime);
	strftime (buffer, 64, "%X", localtime (&rawtime));
	std::cout << buffer << " - graph created!" << std::endl;

	TileGraph::const_biterator itn;
	TileGraph::const_biterator itnEnd = g.bend ();

	time (&rawtime);
	strftime (buffer, 64, "%X", localtime (&rawtime));
	std::cout << buffer << " - breadth-first search..." << std::endl;

	for (itn = g.bbegin (); itn != itnEnd; ++itn)
	{
		const TileGraph::node& n = *itn;
		//const TileGraph::vertex& v = n.vertex ();

		//std::cout << "vertex: (" << v.value ().mZoom << "," << v.value ().mX << "," << v.value ().mY << ") -> ";

		const TileGraph::adjlist &adjList = n.adjlist ();

		TileGraph::adjlist::const_iterator itadj = adjList.begin ();
		TileGraph::adjlist::const_iterator itadjEnd = adjList.end ();

		if (itadj != itadjEnd)
		{
			//const TileGraph::edge& e = itadj->edge ();
			//const TileGraph::vertex& v2 = (v == e.v1 () ? e.v2 ():e.v1 ());

			//std::cout << "(" << v2.value ().mZoom << "," << v2.value ().mX << "," << v2.value ().mY << ")";

			for (++itadj; itadj != itadjEnd; ++itadj)
			{
				//const TileGraph::edge& e = itadj->edge ();
				//const TileGraph::vertex& v2 = (v == e.v1 () ? e.v2 ():e.v1 ());

				//std::cout << ", (" << v2.value ().mZoom << "," << v2.value ().mX << "," << v2.value ().mY << ")";
			}
		}
		
		//std::cout << std::endl;
	}

	time (&rawtime);
	strftime (buffer, 64, "%X", localtime (&rawtime));
	std::cout << buffer << " - breadth-first done!" << std::endl;

	return 0;
}
