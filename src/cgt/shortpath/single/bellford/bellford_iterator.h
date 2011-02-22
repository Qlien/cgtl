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
 * \file cgt/shortpath/single/bellford/bellford_iterator.h
 * \brief Contains definition of an iterator that implements Bellman-Ford algorithm.
 * \author Leandro Costa
 * \date 2009
 *
 * $LastChangedDate: 2011-02-21 17:48:12 -0300 (Seg, 21 Fev 2011) $
 * $LastChangedBy: leandro.costa@gmail.com $
 * $Revision: 128 $
 */

#ifndef __CGTL__CGT_SHORTPATH_SINGLE_BELLFORD_BELLFORD_ITERATOR_H_
#define __CGTL__CGT_SHORTPATH_SINGLE_BELLFORD_BELLFORD_ITERATOR_H_

namespace cgt
{
	/*!
	 * \namespace cgt::shortpath
	 * \brief Where are defined structures related to shortest-path algorithms.
	 * \author Leandro Costa
	 * \date 2009
	 */

	namespace shortpath
	{
		/*!
		 * \namespace cgt::shortpath::single
		 * \brief Where are defined structures related to single-source shortest-path algorithms.
		 * \author Leandro Costa
		 * \date 2009
		 */

		namespace single
		{
			/*!
			 * \namespace cgt::shortpath::single::bellford
			 * \brief Where are defined structures related to bellman-ford iterator.
			 * \author Leandro Costa
			 * \date 2009
			 */

			namespace bellford
			{
				/*!
				 * \class _BellmanFordIterator
				 * \brief An iterator that implements bellman-ford algorithm.
				 * \author Leandro Costa
				 * \date 2009
				 *
				 * This iterator executes Bellman-Ford Algorithm and returns nodes
				 * in the order found by the algorithm.
				 */

				template<typename _TpVertex, typename _TpEdge, template<typename> class _TpIterator = cgt::base::iterator::_TpCommon>
					class _BellmanFordIterator
					{
						private:
							typedef _GraphNode<_TpVertex, _TpEdge>	_Node;

#ifdef CGTL_DO_NOT_USE_STL
							typedef typename cgt::base::list<_Node>::iterator	_NodeIterator;
#else
							typedef typename std::list<_Node>::iterator	_NodeIterator;
#endif

						public:
							_BellmanFordIterator (const _NodeIterator& _it, const _NodeIterator& _it_begin, const _NodeIterator& _it_end) { }
					};
			}
		}
	}
}

#endif // __CGTL__CGT_SHORTPATH_SINGLE_BELLFORD_BELLFORD_ITERATOR_H_
