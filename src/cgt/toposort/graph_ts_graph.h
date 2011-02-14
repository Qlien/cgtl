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
 * \file cgt/toposort/graph_ts_graph.h
 * \brief Contains definition of a thin graph used by topological sort iterator.
 * \author Leandro Costa
 * \date 2009
 *
 * $LastChangedDate: 2009-12-01 21:05:33 -0200 (Ter, 01 Dez 2009) $
 * $LastChangedBy: leandro.costa $
 * $Revision: 96 $
 */

#ifndef __CGTL__CGT_STCONNCOMP__GRAPH_TS_GRAPH_H_
#define __CGTL__CGT_STCONNCOMP__GRAPH_TS_GRAPH_H_

#include "cgt/toposort/graph_ts_node.h"

namespace cgt
{
  namespace toposort
  {
    /*!
     * \class _GraphTSGraph
     * \brief The graph used by topological sort iterator. It its a list of _GraphTSNodes.
     * \author Leandro Costa
     * \date 2009
     *
     * This is the graph used by topological sort algorithm. It's a
     * list of _GraphTSNodes.
     */

    template<typename _TpVertex, typename _TpEdge>
#ifdef CGTL_DO_NOT_USE_STL
      class _GraphTSGraph : public cgt::base::list<_GraphTSNode<_TpVertex, _TpEdge> >
#else
      class _GraphTSGraph : public std::list<_GraphTSNode<_TpVertex, _TpEdge> >
#endif
      {
        private:
          typedef _GraphTSNode<_TpVertex, _TpEdge>  _TSNode;

        private:
#ifdef CGTL_DO_NOT_USE_STL
          typedef cgt::base::list<_TSNode>  _Base;
#else
          typedef std::list<_TSNode>  _Base;
#endif

        private:
          typedef typename _Base::iterator  _Iterator;

        public:
          _Iterator _find_safe ()
          {
            _Iterator _it     = _Base::begin ();
            _Iterator _itEnd  = _Base::end ();

            while (_it != _itEnd)
            {
              if (_it->iadjlist ().empty ())
                break;

              ++_it;
            }

            return _it;
          }

          void remove (const _TSNode& _ts_node)
          {
            _Base::remove (_ts_node);

            _Iterator _itEnd = _Base::end ();

            for (_Iterator _it = _Base::begin (); _it != _itEnd; ++_it)
              _it->_remove_in_edge (_ts_node);
          }
      };
  }
}

#endif // __CGTL__CGT_STCONNCOMP__GRAPH_TS_GRAPH_H_
