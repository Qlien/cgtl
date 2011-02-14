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
 * \file cgt/toposort/graph_ts_node.h
 * \brief Contains definition of a thin node used by topological sort iterator.
 * \author Leandro Costa
 * \date 2009
 *
 * $LastChangedDate: 2009-12-01 21:05:33 -0200 (Ter, 01 Dez 2009) $
 * $LastChangedBy: leandro.costa $
 * $Revision: 96 $
 */

#ifndef __CGTL__CGT_STCONNCOMP__GRAPH_TS_NODE_H_
#define __CGTL__CGT_STCONNCOMP__GRAPH_TS_NODE_H_

#include "cgt/graph_node.h"
#include "cgt/graph_adjlist.h"


namespace cgt
{
  namespace toposort
  {
    /*!
     * \class _GraphTSNode
     * \brief The node used by topological sort iterator. It has a reference to the real node.
     * \author Leandro Costa
     * \date 2009
     *
     * This is the node used by topological sort algorithm. It's a
     * special node with a reference to the real node and its own list of adjacencies.
     */

    template<typename _TpVertex, typename _TpEdge>
      class _GraphTSNode
      {
		  private:
			  typedef _GraphTSNode<_TpVertex, _TpEdge> _Self;

        private:
          typedef _GraphVertex<_TpVertex>           _Vertex;
          typedef _GraphNode<_TpVertex, _TpEdge>    _Node;
          typedef _GraphEdge<_TpVertex, _TpEdge>    _Edge;
          typedef _GraphAdjList<_TpVertex, _TpEdge> _AdjList;
          typedef _GraphTSNode<_TpVertex, _TpEdge>  _TSNode;

          typedef typename _AdjList::iterator       _AdjIterator;
          typedef typename _AdjList::const_iterator _AdjCIterator;

        public:
          explicit _GraphTSNode (_Node& _n) : _node (_n) { }

		public:
		  _Self& operator=(const _Self& _s);

        public:
          const bool operator==(const _TSNode& _ts_node)
          {
            return (_node.vertex () == _ts_node.node ().vertex ());
          }

          const bool operator!=(const _TSNode& _ts_node)
          {
            return !(*this == _ts_node);
          }

        public:
          void _insert_inverse (_Edge& _e, _Node& _n) { _invAdjList._insert (_e, _n); }
          void _remove_in_edge (const _TSNode& _ts_node) { _invAdjList._remove_adj_by_node (_ts_node.node ()); }

        public:
          _Node& node () const { return _node; }
          const _Vertex& vertex () const { return _node.vertex (); }
          const _AdjList& iadjlist () const { return _invAdjList; }

        private:
          _Node&    _node;
          _AdjList  _invAdjList;
      };

    template<typename _TpVertex, typename _TpEdge>
      _GraphTSNode<_TpVertex, _TpEdge>& _GraphTSNode<_TpVertex, _TpEdge>::operator=(const _GraphTSNode<_TpVertex, _TpEdge>& _s)
	  {
		  _node = _s._node;
		  _invAdjList = _s._invAdjList;

		  return *this;
	  }

  }
}

#endif // __CGTL__CGT_STCONNCOMP__GRAPH_TS_NODE_H_
