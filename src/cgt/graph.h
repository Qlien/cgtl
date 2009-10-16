#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "list/list.h"
#include "graph_vertex.h"
#include "graph_edge.h"
#include "graph_adjacency.h"
#include "graph_node.h"
#include "adj_list.h"
#include "adj_matrix.h"
#include "vertex_iterator.h"
#include "depth_iterator.h"
#include "graph_type.h"


namespace cgt
{
  template<typename _TpVertex, typename _TpEdge, typename _TpGraphType = _Directed>
    class graph : private _AdjMatrix<_TpVertex, _TpEdge, _TpGraphType>
  {
    private:
      typedef _AdjMatrix<_TpVertex, _TpEdge, _TpGraphType> _Base;

    public:
      typedef _GraphVertex<_TpVertex>         vertex;
      typedef _GraphEdge<_TpVertex, _TpEdge>  edge;
      typedef _GraphNode<_TpVertex, _TpEdge>  node;
      typedef _AdjList<_TpVertex, _TpEdge>    adjlist;

      typedef typename _Base::iterator                        iterator;
      typedef typename _Base::const_iterator                  const_iterator;

      typedef _VertexIterator<_TpVertex, _TpEdge>             viterator;
      typedef _VertexIterator<_TpVertex, _TpEdge, _TpConst>   const_viterator;

      typedef typename _List<edge>::iterator                  eiterator;
      typedef typename _List<edge>::const_iterator            const_eiterator;

      typedef _DepthIterator<_TpVertex, _TpEdge>              diterator;
      typedef _DepthIterator<_TpVertex, _TpEdge, _TpConst>    const_diterator;

      typedef typename diterator::_DepthInfo             depth_info;

    public:
      void insert_vertex (const _TpVertex &_vertex) { _insert_vertex (_vertex); }
      void insert_edge (const _TpEdge &_e, const _TpVertex &_v1, const _TpVertex &_v2) { _insert_edge (_e, _v1, _v2); }

    public:
      const node* get_node (const _TpVertex &_vertex) { return _Base::_get_node (_vertex); }
      iterator find (const _TpVertex &_vertex) { return _Base::_find (_vertex); }

    public:
      const bool is_directed () const { return _Base::_is_directed (); }
      const bool is_undirected () const { return _Base::_is_undirected (); }

    public:
      iterator begin () { return _Base::begin (); }
      iterator end () { return _Base::end (); }
      const_iterator begin () const { return _Base::begin (); }
      const_iterator end () const { return _Base::end (); }

      eiterator edge_begin () { return eiterator (_Base::_edge_list.begin ()); }
      eiterator edge_end () { return eiterator (_Base::_edge_list.end ()); }

      viterator vertex_begin () { return viterator (_Base::begin ()); }
      viterator vertex_end () { return viterator (_Base::end ()); }

      diterator depth_begin () { return diterator (&(*_Base::begin ()), _Base::begin (), _Base::end ()); }
      diterator depth_begin (const iterator _it) { return diterator (&(*_it), _Base::begin (), _Base::end ()); }
      diterator depth_end () { return diterator (NULL, _Base::begin (), _Base::end ()); }
  };
}

#endif
