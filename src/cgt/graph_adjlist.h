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
 * \file cgt/graph_adjlist.h
 * \brief Contains definition of an adjacency's list.
 * \author Leandro Costa
 * \date 2009
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CGTL__CGT__GRAPH_ADJLIST_H_
#define __CGTL__CGT__GRAPH_ADJLIST_H_

#include "cgt/graph_adjacency.h"
#include "cgt/graph_vertex.h"
#ifdef CGTL_DO_NOT_USE_STL
#include "cgt/base/list.h"
#else
#include <list>
#endif


namespace cgt
{
  namespace stconncomp
  {
    template<typename _TpVertex, typename _TpEdge>
      class _GraphSCCNode;
  }

  namespace toposort
  {
    template<typename _TpVertex, typename _TpEdge>
      class _GraphTSNode;
  }

  template<typename _TpVertex, typename _TpEdge>
    class _GraphNode;

  /*!
   * \class _GraphAdjList
   * \brief It belongs to a node and contains its list of adjacencies (each one composed by reference to edge and linked node).
   * \author Leandro Costa
   * \date 2009
   *
   * A \b _GraphAdjList is a list of objects from type _GraphAdjacency.
   * Each \b _GraphNode has a list of adjacencies, and from this list
   * it is possible to visit all nodes that are linked to the node
   * to which the adjacency list belongs.
   *
   * The structure is a list of adjacencies. Each list has an overhead of <b>12 + 8n bytes</b>.
   * Each adjacency is composed by two references. So, we need <b>12 + 16n bytes</b> to represent
   * a _GraphAdjList structure.
   *
   * \code
   *  ______________________
   * | _GraphAdjList's size |
   * |______________________|
   * |       12 + 16n       |
   * |______________________|
   *
   * \endcode
   */

  template<typename _TpVertex, typename _TpEdge>
#ifdef CGTL_DO_NOT_USE_STL
    class _GraphAdjList : public cgt::base::list<_GraphAdjacency<_TpVertex, _TpEdge> >
#else
    class _GraphAdjList : public std::list<_GraphAdjacency<_TpVertex, _TpEdge> >
#endif
  {
    private:
      friend class _GraphNode<_TpVertex, _TpEdge>;
      friend class cgt::toposort::_GraphTSNode<_TpVertex, _TpEdge>;
      friend class cgt::stconncomp::_GraphSCCNode<_TpVertex, _TpEdge>;

    private:
      typedef _GraphNode<_TpVertex, _TpEdge>      _Node;
      typedef _GraphEdge<_TpVertex, _TpEdge>      _Edge;
      typedef _GraphVertex<_TpVertex>             _Vertex;
      typedef _GraphAdjacency<_TpVertex, _TpEdge> _Adjacency;
#ifdef CGTL_DO_NOT_USE_STL
      typedef cgt::base::list<_Adjacency>         _Base;
#else
	  typedef std::list<_Adjacency>         _Base;
#endif
      typedef typename _Base::const_iterator      _Iterator;

    private:
      void _insert (_Edge& _e, _Node& _n);
      void _remove_adj_by_node (const _Node& _n);

    public:
      _Edge* get_edge (const _Vertex& _v) const;
  };

  template<typename _TpVertex, typename _TpEdge>
    _GraphEdge<_TpVertex, _TpEdge>* _GraphAdjList<_TpVertex, _TpEdge>::get_edge (const _Vertex& _v) const
    {
      _Edge *_ptr_edge = NULL;

      _Iterator itEnd = _Base::end ();

      for (_Iterator _it = _Base::begin (); _it != itEnd; ++_it)
      {
        if (_it->vertex () == _v)
        {
          _ptr_edge = &(_it->edge ());
          break;
        }
      }

      return _ptr_edge;
    }

  template<typename _TpVertex, typename _TpEdge>
    void _GraphAdjList<_TpVertex, _TpEdge>::_insert (_Edge& _e, _Node& _n)
    {
      _Base::push_back (_Adjacency (_e, _n));
    }

  template<typename _TpVertex, typename _TpEdge>
    void _GraphAdjList<_TpVertex, _TpEdge>::_remove_adj_by_node (const _Node& _n)
    {
      _Iterator itEnd = _Base::end ();

      for (_Iterator _it = _Base::begin (); _it != itEnd; ++_it)
      {
        if (_it->node ().vertex () == _n.vertex ())
        {
          _Base::remove (*_it);
          break;
        }
      }
    }
}

#endif // __CGTL__CGT__GRAPH_ADJLIST_H_
