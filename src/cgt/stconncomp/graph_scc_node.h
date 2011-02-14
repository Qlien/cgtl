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
 * \file cgt/stconncomp/graph_scc_node.h
 * \brief Contains definition of a thin node used by SCC iterator.
 * \author Leandro Costa
 * \date 2009
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CGTL__CGT_STCONNCOMP__GRAPH_SCC_NODE_H_
#define __CGTL__CGT_STCONNCOMP__GRAPH_SCC_NODE_H_

#include "cgt/graph_node.h"
#include "cgt/graph_adjlist.h"


namespace cgt
{
  namespace stconncomp
  {
    /*!
     * \class _GraphSCCNode
     * \brief The node used by _GraphSCCComponent. It has a reference to the real node.
     * \author Leandro Costa
     * \date 2009
     *
     * This is the node used by strongly connected component structure. It's a
     * special node with a reference to the real node and its own list of adjacencies.
     */

    template<typename _TpVertex, typename _TpEdge>
      class _GraphSCCNode
      {
		  private:
			  typedef _GraphSCCNode<_TpVertex, _TpEdge> _Self;

        private:
          typedef _GraphVertex<_TpVertex>           _Vertex;
          typedef _GraphNode<_TpVertex, _TpEdge>    _Node;
          typedef _GraphEdge<_TpVertex, _TpEdge>    _Edge;
          typedef _GraphAdjList<_TpVertex, _TpEdge> _AdjList;

        public:
          explicit _GraphSCCNode (_Node& _n) : _node (_n) { }

		public:
		  _Self& operator=(const _Self& _s);

        public:
          void _insert (_Edge& _e, _Node& _n) { _adjList._insert (_e, _n); }

        public:
          _Node& node () const { return _node; }
          const _Vertex& vertex () const { return _node.vertex (); }
          const _AdjList& adjlist () const { return _adjList; }

        private:
          _Node&    _node;
          _AdjList  _adjList;
      };

	template<typename _TpVertex, typename _TpEdge>
		_GraphSCCNode<_TpVertex, _TpEdge>& _GraphSCCNode<_TpVertex, _TpEdge>::operator=(const _GraphSCCNode<_TpVertex, _TpEdge>& _s)
		{
			_node = _s._node;
			_adjList = _s._adjList;

			return *this;
		}
  }
}

#endif // __CGTL__CGT_STCONNCOMP__GRAPH_SCC_NODE_H_
