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
 * \file cgt/graph_edge.h
 * \brief Contains definition of an edge.
 * \author Leandro Costa
 * \date 2009
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CGTL__CGT_GRAPH_EDGE_H_
#define __CGTL__CGT_GRAPH_EDGE_H_


namespace cgt
{
  /*!
   * \class _GraphEdge
   * \brief A wrapper for edge, contains \b _value of type \b _TpEdge and references to vertices: \b _vertex1 and \b _vertex2.
   * \author Leandro Costa
   * \date 2009
   *
   * A \b _GraphEdge is a structure that encapsulates the edge. Inside, it has
   * the object edge and the references for the vertices linked by the edge.
   * When an edge is inserted in the graph, an object of this type is created
   * and pushed in the edge's list of the structure \b _GraphAdjMatrix.
   *
   * The _GraphEdge's size has an overhead of 2 references to vertices. In 32-bits
   * architectures it means we need 8 more bytes to represent each edge in our graph.
   *
   * \code
   *  _______________________
   * |   _GraphEdge's size   |
   * |_______________________|
   * |  8 + sizeof(_TpEdge)  |
   * |_______________________|
   *
   * \endcode
   */

  template<typename _TpVertex, typename _TpEdge = void>
    class _GraphEdge
    {
      private:
        typedef _GraphVertex<_TpVertex>         _Vertex;
        typedef _GraphEdge<_TpVertex, _TpEdge>  _Edge;

      public:
        _GraphEdge (const _TpEdge& _e, _Vertex& _v1, _Vertex& _v2) : _value (_e), _vertex1 (_v1), _vertex2 (_v2) { }

	  public:
		_GraphEdge& operator=(const _GraphEdge& _o)
		{
			_value = _o._value;
			_vertex1 = _o._vertex1;
			_vertex2 = _o._vertex2;

			return *this;
		}

      public:
        inline const bool operator==(const _Edge& _edge) const
        {
          return (_value == _edge.value () && _vertex1 == _edge.v1 () && _vertex2 == _edge.v2 ());
        }

        inline const bool operator!=(const _Edge& _edge) const
        {
          return ! (*this == _edge);
        }

      public:
        inline const _TpEdge& value () const { return _value; }
        inline _Vertex& v1 () const { return _vertex1; }
        inline _Vertex& v2 () const { return _vertex2; }

      private:
        _TpEdge   _value;
        _Vertex&  _vertex1;
        _Vertex&  _vertex2;
    };


  /*
	template<typename _TpVertex>
		class _GraphEdge<_TpVertex, void>
		{
		};
		*/
  /*
	template<typename _TpVertex>
		_GraphEdge<_TpVertex, void>::_GraphEdge(_GraphVertex<_TpVertex>& _v1, _GraphVertex<_TpVertex>& _v2) : _vertex1 (_v1), _vertex2 (_v2) { }
		*/

	template<typename _TpVertex>
		class _GraphEdge<_TpVertex, void>
		{
			private:
				typedef _GraphVertex<_TpVertex> _Vertex;
				typedef _GraphEdge<_TpVertex, void> _Edge;

			public:
				_GraphEdge (_Vertex& _v1, _Vertex& _v2) : _vertex1 (_v1), _vertex2 (_v2) { }

			public:
				_GraphEdge& operator=(const _GraphEdge& _other)
				{
					_vertex1 = _other._vertex1;
					_vertex2 = _other._vertex2;

					return *this;
				}

			public:
				inline const bool operator==(const _Edge& _other) const
				{
					return (_vertex1 == _other.v1 () && _vertex2 == _other.v2 ());
				}

				inline const bool operator!=(const _Edge& _other) const
				{
					return !operator==(_other);
				}

			public:
				inline _Vertex& v1 () const { return _vertex1; }
				inline _Vertex& v2 () const { return _vertex2; }

			private:
				_Vertex&  _vertex1;
				_Vertex&  _vertex2;
		};
}

#endif // __CGTL__CGT_GRAPH_EDGE_H_
