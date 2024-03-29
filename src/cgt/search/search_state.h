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
 * \file cgt/search/search_state.h
 * \brief Contains definition of a structure used by breadth-first and depth-first searches.
 * \author Leandro Costa
 * \date 2009
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CGTL__CGT_SEARCH__SEARCH_STATE_H_
#define __CGTL__CGT_SEARCH__SEARCH_STATE_H_

#include "cgt/graph_node.h"
#include "cgt/graph_adjacency.h"
#ifdef CGTL_DO_NOT_USE_STL
#include "cgt/base/list_iterator.h"
#endif


namespace cgt
{
  namespace search
  {
    /*!
     * \class _SearchState
     * \brief The _SearchState class template.
     * \author Leandro Costa
     * \date 2009
     *
     * This structure keeps informations about depth-first search and
     * breadth-first search cycles used by _DepthIterator and _BreadthIterator.
     */

    template<typename _TpVertex, typename _TpEdge>
      class _SearchState
      {
		  private:
			  typedef _SearchState<_TpVertex, _TpEdge> _Self;

        private:
          typedef _GraphNode<_TpVertex, _TpEdge>             _Node;
          typedef _GraphAdjacency<_TpVertex, _TpEdge>        _Adjacency;
#ifdef CGTL_DO_NOT_USE_STL
          typedef typename cgt::base::list<_Adjacency>::const_iterator _AdjIterator;
#else
          typedef typename std::list<_Adjacency>::const_iterator _AdjIterator;
#endif

        public:
          _SearchState (_Node& _n) : _node (_n), _it_adj (_node.adjlist ().begin ()), _it_adj_end (_node.adjlist ().end ()) { };

		_Self& operator=(const _Self& _s);

        public:
          const _Node& node () { return _node; }
          const bool adj_finished () const { return (_it_adj == _it_adj_end); }
          void adj_incr () { ++_it_adj; }
          _Node& _adj_node () { return _it_adj->node (); }
          const _TpVertex& value () const { return _node.vertex ().value (); }

        private:
          _Node&       _node;
          _AdjIterator       _it_adj;
          _AdjIterator _it_adj_end;
      };

	template<typename _TpVertex, typename _TpEdge>
		_SearchState<_TpVertex, _TpEdge>& _SearchState<_TpVertex, _TpEdge>::operator=(const _SearchState<_TpVertex, _TpEdge>& _s)
		{
			_node = _s._node;
			_it_adj = _s._it_adj;
			_it_adj_end = _s._it_adj_end;

			return *this;
		}
  }
}

#endif // __CGTL__CGT_SEARCH__SEARCH_STATE_H_
