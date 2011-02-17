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
 * \file cgt/graph_adjacency.h
 * \brief Contains definition of a graph's adjacency, that is a reference to an edge and the node at right.
 * \author Leandro Costa
 * \date 2009
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CGTL__CGT_GRAPH_ADJACENCY_H_
#define __CGTL__CGT_GRAPH_ADJACENCY_H_


namespace cgt
{
	template<typename _TpVertex, typename _TpEdge>
		class _GraphNode; /** < \b We can't include \b graph_adjacency.h since \b _GraphAdjacency has a reference to \b _GraphNode, and \b _GraphNode has a list of adjacencies. */


	template<typename _TpVertex, typename _TpEdge>
		class _GraphAdjacencyBase
		{
			private:
				typedef _GraphAdjacencyBase<_TpVertex, _TpEdge> _Self;
				typedef _GraphVertex<_TpVertex>					_Vertex;

			protected:
				typedef _GraphNode<_TpVertex, _TpEdge>	_Node;
				typedef _GraphEdge<_TpVertex, _TpEdge>	_Edge;

			public:
				_GraphAdjacencyBase (_Edge& _e, _Node& _n) : _edge (_e), _node (_n)  { }

			public:
				_Self& operator=(const _Self& _s);

				inline const bool operator==(const _Self& _other) const
				{
					return (_edge == _other.edge () && _node.vertex () == _other.node ().vertex ());
				}

				inline const bool operator!=(const _Self& _other) const
				{
					return ! (*this == _other);
				}

				inline _Edge&  edge () const { return _edge; }
				inline _Node& node () const { return _node; }
				inline const _Vertex& vertex () const { return _node.vertex (); }

			protected:
				// Reference to the edge object (stored in _GraphAdjMatrix._edgeList)
				_Edge& _edge;

			private:
				// Reference to the node at the right
				_Node& _node;
		};

	template<typename _TpVertex, typename _TpEdge>
		_GraphAdjacencyBase<_TpVertex, _TpEdge>& _GraphAdjacencyBase<_TpVertex, _TpEdge>::operator=(const _GraphAdjacencyBase<_TpVertex, _TpEdge>& _other)
		{
			_edge = _other._edge;
			_node = _other._node;

			return *this;
		}


	/*!
	 * \class _GraphAdjacency
	 * \brief It belongs to a node and contains references to an edge and the other node linked by the edge.
	 * \author Leandro Costa
	 * \date 2009
	 *
	 * A \b _GraphAdjacency is a structure that belongs to a node (stored in its
	 * adjacency list) and contains a reference to an edge and a reference to the
	 * other node of the relationship. So, from an adjacency it is possible to visit
	 * all vertices reachable from the vertex to which the adjacency belongs.
	 *
	 * The structure is composed by two references, so we need 8 bytes to represent
	 * it in our graph.
	 *
	 * \code
	 *  ________________________
	 * | _GraphAdjacency's size |
	 * |________________________|
	 * |           8            |
	 * |________________________|
	 *
	 * \endcode
	 */

	template<typename _TpVertex, typename _TpEdge>
		class _GraphAdjacency : public _GraphAdjacencyBase<_TpVertex, _TpEdge>
	{
		private:
			typedef _GraphAdjacencyBase<_TpVertex, _TpEdge> _Base;

		private:
			typedef typename _Base::_Node	_Node;
			typedef typename _Base::_Edge	_Edge;

		public:
			_GraphAdjacency (_Edge& _e, _Node& _n) : _Base (_e, _n) { }

		public:
			inline const _TpEdge& value () const { return _Base::_edge.value (); }
	};


  /*
   * A simple graph, with no type for edges
   */

  template<typename _TpVertex>
    class _GraphAdjacency<_TpVertex, void> : public _GraphAdjacencyBase<_TpVertex, void>
    {
		private:
			typedef _GraphAdjacencyBase<_TpVertex, void> _Base;

		private:
			typedef typename _Base::_Node	_Node;
			typedef typename _Base::_Edge	_Edge;

		public:
			_GraphAdjacency (_Edge& _e, _Node& _n) : _Base (_e, _n) { }
	};
}

#endif // __CGTL__CGT_GRAPH_ADJACENCY_H_
