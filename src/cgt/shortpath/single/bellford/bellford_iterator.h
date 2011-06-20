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

#include <glog/logging.h>
#include "cgt/base/heap.h"
#include "cgt/shortpath/single/bellford/bellford_info.h"
#include "cgt/shortpath/single/bellford/bellford_info_list.h"
#include "cgt/shortpath/single/bellford/negcycl_except.h"

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
				 * \class _BellfordIterator
				 * \brief An iterator that implements bellman-ford algorithm.
				 * \author Leandro Costa
				 * \date 2009
				 *
				 * This iterator executes Bellman-Ford Algorithm and returns nodes
				 * in the order found by the algorithm.
				 */

				template<typename _TpVertex, typename _TpEdge, template<typename> class _TpIterator = cgt::base::iterator::_TpCommon>
					class _BellfordIterator
					{
						public:
							typedef _BellfordInfo<_TpVertex, _TpEdge>	_Info;

						private:
							typedef _BellfordIterator<_TpVertex, _TpEdge, _TpIterator>  _Self;
							typedef _GraphNode<_TpVertex, _TpEdge>	_Node;

						private:
							typedef _BellfordInfoList<_TpVertex, _TpEdge> _InfoList;
							typedef _GraphVertex<_TpVertex>  _Vertex;
							typedef _GraphEdge<_TpVertex, _TpEdge>  _Edge;
#ifdef CGTL_DO_NOT_USE_STL
							typedef typename cgt::base::list<_Node>::iterator	_NodeIterator;
							typedef cgt::base::list<_Edge>  _EdgeList;
							typedef typename cgt::base::list<_Edge>::const_iterator const_eiterator;
#else
							typedef typename std::list<_Node>::iterator	_NodeIterator;
							typedef std::list<_Edge>    _EdgeList;
							typedef typename std::list<_Edge>::const_iterator const_eiterator;
#endif

						public:
							_BellfordIterator (const _NodeIterator& _it, const _NodeIterator& _it_begin, const _NodeIterator& _it_end, const _EdgeList& _elist, const size_t num_vertices) : _ptr_node (&(*_it)), _it_node (_it_begin), _it_node_end (_it_end), _edgeList (_elist)
						{
							DLOG(INFO) << "_ptr_node: " << _ptr_node << ", num_vertices: " << num_vertices;

							if (_ptr_node)
								_init (num_vertices);

							DLOG(INFO) << "_infoHeap.size(): " << _infoHeap.size();
						}

						private:
							void _init (const size_t num_vertices);
							const _Info* const _get_info_by_node (const _Node* const _ptr_node);
							const _Info* const _get_info_by_vertex (const _Vertex& _vertex);

						public:
							_Node& operator*() const { return *_ptr_node; }
							_Node* operator->() const { return _ptr_node; }

							_Self& operator++()
							{
								_infoList.push_back(*(_infoHeap.pop ()));
								_ptr_node = &(_infoList.back ().node ());

								return *this;
							}

						public:
							const _Info* const info (const _Node& _node) { return _get_info_by_node (&_node); }

						private:
							_Node*	_ptr_node;
							_NodeIterator _it_node;
							_NodeIterator _it_node_end;
							_InfoList _infoList;
							const _EdgeList& _edgeList;
							cgt::base::heap<_Info> _infoHeap;
					};


				template<typename _TpVertex, typename _TpEdge, template<typename> class _TpIterator>
					void _BellfordIterator<_TpVertex, _TpEdge, _TpIterator>::_init (const size_t num_vertices)
					{
						for (_NodeIterator it = _it_node; it != _it_node_end; ++it)
						{
							_Info _info (*it);

							if (&(*it) == _ptr_node)
							{
								DLOG(INFO) << "_info.set_origin ()";
								_info.set_origin ();
							}

							_infoList.push_back (_info);
						}

						for (size_t i = 0; i < num_vertices; i++)
						{
							//DLOG(INFO) << "iteration " << i;
							const_eiterator itEnd = _edgeList.end ();

							for (const_eiterator it = _edgeList.begin (); it != itEnd; ++it)
							{
								const _Vertex& v1 = it->v1 ();
								const _Vertex& v2 = it->v2 ();

								//DLOG(INFO) << "v1: " << v1.value () << ", v2: " << v2.value ();

								typename _InfoList::iterator _it_info_v1 = _infoList.get_by_vertex (v1);
								typename _InfoList::iterator _it_info_v2 = _infoList.get_by_vertex (v2);

								//DLOG(INFO) << "v1 infinite: " << _it_info_v1->inf_distance ();
								//DLOG(INFO) << "v1 distance: " << _it_info_v1->distance ();

								//DLOG(INFO) << "v2 distance: " << _it_info_v2->distance ();

								if (! _it_info_v1->inf_distance () && (_it_info_v2->inf_distance () || (_it_info_v1->distance () + it->value () < _it_info_v2->distance ())))
								{
									_it_info_v2->set_distance (_it_info_v1->distance () + it->value ());
									_it_info_v2->set_previous (&(_it_info_v1->node ()));
									//DLOG(INFO) << _it_info_v1->node ().vertex ().value () << ", " << _it_info_v2->node ().vertex ().value ();
								}
							}
						}

						/*
						 * // Step 3: check for negative-weight cycles
						 * for each edge uv in edges:
						 *   u := uv.source
						 *   v := uv.destination
						 *   if u.distance + uv.weight < v.distance:
						 *     error "Graph contains a negative-weight cycle"
						 */

						const_eiterator itEnd = _edgeList.end ();

						for (const_eiterator it = _edgeList.begin (); it != itEnd; ++it)
						{
							const _Vertex& v1 = it->v1 ();
							const _Vertex& v2 = it->v2 ();

							typename _InfoList::iterator _it_info_v1 = _infoList.get_by_vertex (v1);
							typename _InfoList::iterator _it_info_v2 = _infoList.get_by_vertex (v2);

							if (! _it_info_v1->inf_distance () && ! _it_info_v2->inf_distance () && _it_info_v1->distance () + it->value () < _it_info_v2->distance ())
								throw cgt::shortpath::single::bellford::negcycl_except ("Negative cycle found");
						}
							
						while (! _infoList.empty ())
						{
							_infoHeap.push (*(_infoList.pop_front ()));
						}

						_infoList.push_back(*(_infoHeap.pop ()));
					}

				template<typename _TpVertex, typename _TpEdge, template<typename> class _TpIterator>
					const _BellfordInfo<_TpVertex, _TpEdge>* const _BellfordIterator<_TpVertex, _TpEdge, _TpIterator>::_get_info_by_node (const _Node* const _ptr_node)
					{
						const _Info* _ptr = NULL;

						DLOG(INFO) << "_infoList.size(): " << _infoList.size();
						typename _InfoList::const_iterator _it = _infoList.get_by_node (_ptr_node);

						if (_it != _infoList.end ())
							_ptr = &(*_it);

						return _ptr;
					}

				template<typename _TpVertex, typename _TpEdge, template<typename> class _TpIterator>
					const _BellfordInfo<_TpVertex, _TpEdge>* const _BellfordIterator<_TpVertex, _TpEdge, _TpIterator>::_get_info_by_vertex (const _Vertex& _vertex)
					{
						const _Info* _ptr = NULL;

						typename _InfoList::const_iterator _it = _infoList.get_by_vertex (_vertex);

						if (_it != _infoList.end ())
							_ptr = &(*_it);

						return _ptr;
					}
			}
		}
	}
}

#endif // __CGTL__CGT_SHORTPATH_SINGLE_BELLFORD_BELLFORD_ITERATOR_H_
