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
 * \file cgt/shortpath/single/bellford/bellford_info.h
 * \brief Contains definition of a structure where we put node's informations about Bellman-Ford algorithm execution.
 * \author Leandro Costa
 * \date 2009
 *
 * $LastChangedDate: 2011-02-14 19:16:22 -0200 (Seg, 14 Fev 2011) $
 * $LastChangedBy: leandro.costa@gmail.com $
 * $Revision: 123 $
 */

#ifndef __CGTL__CGT_SHORTPATH_SINGLE_BELLFORD_BELLFORD_INFO_H_
#define __CGTL__CGT_SHORTPATH_SINGLE_BELLFORD_BELLFORD_INFO_H_

#include "cgt/shortpath/single/bellford/bellford_distance.h"
#include "cgt/graph_node.h"


namespace cgt
{
  namespace shortpath
  {
    namespace single
    {
      namespace bellford
      {
        /*!
         * \class _BellfordInfo
         * \brief A structure used to keep information about each node by Bellman-Ford iterator.
         * \author Leandro Costa
         * \date 2009
         *
         * This structure keeps informations about nodes while executing
         * Bellman-Ford Algorithm, like distance.
         */

        template<typename _TpVertex, typename _TpEdge>
          class _BellfordInfo
          {
            private:
			  /*
              typedef _BellfordInfo<_TpVertex, _TpEdge> _Self;
			  */
              typedef _GraphNode<_TpVertex, _TpEdge>    _Node;
              typedef _BellfordDistance<_TpEdge>        _Distance;

            public:
              _BellfordInfo (_Node& _n) : _node (_n), _ptr_previous (NULL) { }
			  /*
              _BellfordInfo (const _BellfordInfo& _d) : _node (_d._node), _distance (_d._distance), _ptr_previous (_d._ptr_previous) { }

			public:
			  _Self& operator=(const _Self& _s);

            public:
              const bool operator==(const _BellfordInfo& _d) const { return (_node.vertex () == _d._node.vertex ()); }
              const bool operator!=(const _BellfordInfo& _d) const { return ! (*this == _d); }
              const bool operator<(const _BellfordInfo& _d) const { return (! inf_distance () && (_d.inf_distance () || distance () < _d.distance ())); }
              const bool operator<=(const _BellfordInfo& _d) const { return (! inf_distance () && (_d.inf_distance () || distance () <= _d.distance ())); }
              const bool operator>(const _BellfordInfo& _d) const { return ! operator<=(_d); }
              const bool operator>=(const _BellfordInfo& _d) const { return ! operator<(_d); }

			  */
            public:
              _Node& node () const { return _node; }
			  void set_origin () { _distance.set_origin (); }
              void set_distance (const _TpEdge &_d) { _distance._set_distance (_d); }
              const _TpEdge& distance () const { return _distance.distance (); }
			  /*
              const bool &inf_distance () const { return _distance.inf_distance (); }
			  */
              void set_previous (const _Node* const _ptr) { _ptr_previous = _ptr; }
			  /*
              const _Node* const previous () const { return _ptr_previous; }
			  */

            private:
              _Node&        _node;
              _Distance     _distance;
              const _Node*  _ptr_previous;
          };

		/*
		template<typename _TpVertex, typename _TpEdge>
			_BellfordInfo<_TpVertex, _TpEdge>& _BellfordInfo<_TpVertex, _TpEdge>::operator=(const _BellfordInfo<_TpVertex, _TpEdge>& _s)
			{
				_node = _s._node;
				_distance = _s._distance;
				_ptr_previous = _s._ptr_previous;

				return *this;
			}
			*/
      }
    }
  }
}

#endif // __CGTL__CGT_SHORTPATH_SINGLE_BELLFORD_BELLFORD_INFO_H_
