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
 * \file cgt/stconncomp/graph_scc_component.h
 * \brief Contains definition of a structure that represents a Strongly Connected Component.
 * \author Leandro Costa
 * \date 2009
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CGTL__CGT_STCONNCOMP__GRAPH_SCC_COMPONENT_H_
#define __CGTL__CGT_STCONNCOMP__GRAPH_SCC_COMPONENT_H_

#include "cgt/stconncomp/graph_scc_node.h"
#ifdef CGTL_DO_NOT_USE_STL
#include "cgt/base/list.h"
#else
#include <list>
#endif


namespace cgt
{
  namespace stconncomp
  {
    /*!
     * \class _GraphSCCComponent
     * \brief A strongly connected component: a list of _GraphSCCNode.
     * \author Leandro Costa
     * \date 2009
     *
     * This is the structure returned by SCC iterator. It is a list of
     * _GraphSCCNode, that is a special node with a reference to the
     * real node and a list of adjacencies.
     */

    template<typename _TpVertex, typename _TpEdge>
#ifdef CGTL_DO_NOT_USE_STL
      class _GraphSCCComponent : public cgt::base::list<_GraphSCCNode<_TpVertex, _TpEdge> >
#else
      class _GraphSCCComponent : public std::list<_GraphSCCNode<_TpVertex, _TpEdge> >
#endif
      {
        private:
#ifdef CGTL_DO_NOT_USE_STL
          typedef cgt::base::list<_GraphSCCNode<_TpVertex, _TpEdge> > _Base;
#else
          typedef std::list<_GraphSCCNode<_TpVertex, _TpEdge> > _Base;
#endif
          typedef typename _Base::iterator                  _Iterator;

        private:
          typedef _GraphSCCNode<_TpVertex, _TpEdge> _SCCNode;
          typedef _GraphNode<_TpVertex, _TpEdge>    _Node;
          typedef _GraphEdge<_TpVertex, _TpEdge>    _Edge;

        public:
#ifdef CGTL_DO_NOT_USE_STL
          _GraphSCCComponent (const _SCCNode& _n) { _Base::insert (_n); }
#else
          _GraphSCCComponent (const _SCCNode& _n) { _Base::insert (_Base::end (), _n); }
#endif

        public:
          void insert (const _SCCNode& _n);
      };


    template<typename _TpVertex, typename _TpEdge>
      void _GraphSCCComponent<_TpVertex, _TpEdge>::insert (const _SCCNode& _n)
      {
#ifdef CGTL_DO_NOT_USE_STL
        _Base::insert (_n);
#else
        _Base::insert (_Base::end (), _n);
#endif

        /*!
         * We need to add adjacencies between nodes that are linked in the
         * same SCC. In order to do it, we need to visit all nodes of the
         * SCC and ask for edges linking _n and these nodes. If we find some,
         * we insert it in the SCC node at the end of the list.
         *
         * _SCCNode has a reference to _Node, but it's impossible
         * to reuse the _Adjacencies. So, we reuse only the edges.
         */

        _Edge* _ptr_edge = NULL;
#ifdef CGTL_DO_NOT_USE_STL
        _SCCNode* _ptr_node = _Base::back ();
#else
        _SCCNode* _ptr_node = &(_Base::back ());
#endif
        _Node& _n1 = _ptr_node->node ();

        _Iterator _itEnd = _Base::end ();

        for (_Iterator _it = _Base::begin (); _it != _itEnd; ++_it)
        {
          _Node& _n2 = _it->node ();

          if ((_ptr_edge = _n1.get_edge (_n2.vertex ())))
            _ptr_node->_insert (*_ptr_edge, _n2);

          if ((_ptr_edge = _n2.get_edge (_n1.vertex ())))
            _it->_insert (*_ptr_edge, _n1);
        }
      }
  }
}

#endif // __CGTL__CGT_STCONNCOMP__GRAPH_SCC_COMPONENT_H_
