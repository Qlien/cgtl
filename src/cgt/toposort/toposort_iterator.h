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
 * \file cgt/toposort/toposort_iterator.h
 * \brief Contains definition of an iterator that implements topological sort algorithm.
 * \author Leandro Costa
 * \date 2009
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CGTL__CGT_TOPOSORT__TOPOSORT_ITERATOR_H_
#define __CGTL__CGT_TOPOSORT__TOPOSORT_ITERATOR_H_

#include "cgt/base/iterator/iterator_ptr.h"
#include "cgt/toposort/graph_ts_graph.h"

namespace cgt
{
    /*!
     * \namespace cgt::toposort
     * \brief Where are defined structures related to topological sort algorithms.
     * \author Leandro Costa
     * \date 2009
     */

  namespace toposort
  {
    /*!
     * \class _ToposortIterator
     * \brief An iterator that implements topological sort algorithm.
     * \author Leandro Costa
     * \date 2009
     *
     * This iterator executes topological sort algorithm and returns nodes
     * in the order found by the algorithm.
     *
     * Algorithm (Kahn) [source: http://en.wikipedia.org/wiki/Topological_sorting]:
     *
     * L ← Empty list that will contain the sorted elements
     * S ← Set of all nodes with no incoming edges
     * while S is non-empty do
     *   remove a node n from S
     *   insert n into L
     *   for each node m with an edge e from n to m do
     *     remove edge e from the graph
     *     if m has no other incoming edges then
     *       insert m into S
     * if graph has edges then
     *   output error message (graph has at least one cycle)
     * else 
     *   output message (proposed topologically sorted order: L)
     */

    template<typename _TpVertex, typename _TpEdge, template<typename> class _TpIterator = cgt::base::iterator::_TpCommon>
      class _ToposortIterator : public cgt::base::iterator::_IteratorPtr<_GraphNode<_TpVertex, _TpEdge>, _TpIterator>
      {
        private:
          friend class _ToposortIterator<_TpVertex, _TpEdge, cgt::base::iterator::_TpConst>;

        private:
          typedef cgt::base::iterator::_IteratorPtr<_GraphNode<_TpVertex, _TpEdge>, _TpIterator>  _Base;
          typedef _ToposortIterator<_TpVertex, _TpEdge, _TpIterator>                              _Self;
          typedef _ToposortIterator<_TpVertex, _TpEdge, cgt::base::iterator::_TpCommon>           _SelfCommon;

          typedef _GraphNode<_TpVertex, _TpEdge>            _Node;
#ifdef CGTL_DO_NOT_USE_STL
          typedef typename cgt::base::list<_Node>::iterator _NodeIterator;
#else
          typedef typename std::list<_Node>::iterator _NodeIterator;
#endif
          typedef _GraphEdge<_TpVertex, _TpEdge>            _Edge;

          typedef _GraphTSNode<_TpVertex, _TpEdge>    _TSNode;
          typedef _GraphTSGraph<_TpVertex, _TpEdge>   _TSGraph;

          typedef typename _TSGraph::iterator        _TSGraphIterator;
          typedef typename _TSGraph::const_iterator  _TSGraphCIterator;

        private:
          typedef typename _TpIterator<_Node>::pointer    pointer;
          typedef typename _TpIterator<_Node>::reference  reference;

        private:
          using _Base::_ptr;

        public:
          _ToposortIterator () : _Base () { }

          _ToposortIterator (const _NodeIterator& _it_begin, const _NodeIterator& _it_end)
            : _Base () 
          {
            _init (_it_begin, _it_end);
          }

          _ToposortIterator (const _SelfCommon& _it) { *this = _it; }

        public:
          const _Self& operator=(const _SelfCommon& _it)
          {
            _ptr      = _it._ptr;
            _auxGraph = _it._auxGraph;

            return *this;
          }

        private:
          void _init (const _NodeIterator& _it_begin, const _NodeIterator& _it_end);
          void _incr ();

        public:
          reference operator*() const { return *_ptr; }
          pointer operator->() const { return _ptr; }
          _Self& operator++();
          const _Self operator++(int);

        private:
          _TSGraph  _auxGraph;  /*!< initial set of nodes and edges, initialized by _init () */
      };

    template<typename _TpVertex, typename _TpEdge, template<typename> class _TpIterator>
      void _ToposortIterator<_TpVertex, _TpEdge, _TpIterator>::_init (const _NodeIterator& _it_begin, const _NodeIterator& _it_end)
      {
        /*! insert all nodes into auxiliary graph */
        for (_NodeIterator _it = _it_begin; _it != _it_end; ++_it)
#ifdef CGTL_DO_NOT_USE_STL
          _auxGraph.insert (_TSNode (*_it));
#else
          _auxGraph.insert (_auxGraph.end (), _TSNode (*_it));
#endif

        /*! insert all edges into auxiliary graph */

        _Edge* _ptr_edge = NULL;
        _TSGraphIterator _itEnd = _auxGraph.end ();

        for (_TSGraphIterator _it1 = _auxGraph.begin (); _it1 != _itEnd; ++_it1)
        {
          _TSNode& _tsn1 = *_it1;

          for (_TSGraphIterator _it2 = _auxGraph.begin (); _it2 != _itEnd; ++_it2)
          {
            if (_it1 != _it2)
            {
              _TSNode& _tsn2 = *_it2;

              /*! if there is an edge between _ts1 and _ts2, insert edge to auxiliary graph */
              if ((_ptr_edge = _tsn1.node ().get_edge (_tsn2.node ().vertex ())))
                _tsn2._insert_inverse (*_ptr_edge, _tsn1.node ());
            }
          }
        }

        _incr ();
      }

    template<typename _TpVertex, typename _TpEdge, template<typename> class _TpIterator>
      void _ToposortIterator<_TpVertex, _TpEdge, _TpIterator>::_incr ()
      {
        _TSGraphIterator _it = _auxGraph._find_safe ();

        if (_it != _auxGraph.end ())
        {
          _ptr = &(_it->node ());
          _auxGraph.remove (*_it);
        }
        else
          _ptr = NULL;
      }

    template<typename _TpVertex, typename _TpEdge, template<typename> class _TpIterator>
      _ToposortIterator<_TpVertex, _TpEdge, _TpIterator>& _ToposortIterator<_TpVertex, _TpEdge, _TpIterator>::operator++ ()
      {
        _incr ();
        return *this;
      }

    template<typename _TpVertex, typename _TpEdge, template<typename> class _TpIterator>
      const _ToposortIterator<_TpVertex, _TpEdge, _TpIterator> _ToposortIterator<_TpVertex, _TpEdge, _TpIterator>::operator++(int)
      {
        _Self _it = *this;
        _incr ();
        return _it;
      }
  }
}

#endif // __CGTL__CGT_TOPOSORT__TOPOSORT_ITERATOR_H_
