#ifndef _SEARCH_INFO__H_
#define _SEARCH_INFO__H_

#include "graph_node.h"


namespace cgt
{
  /*
   * keep informations about depth-first search and breadth-first search visited node
   * like color, parent, discovery time, finish time, etc.
   */

  template<typename _TpVertex, typename _TpEdge>
    class _SearchInfo
    {
      private:
        typedef _GraphNode<_TpVertex, _TpEdge> _Node;

      public:
        typedef enum { WHITE, GRAY, BLACK } _color_t;

      public:
        _SearchInfo (const _Node& _n) : _node (_n), _ptr_parent (NULL), _color (WHITE), _discovery (0), _finish (0) { }
        _SearchInfo (const _Node& _n, const _color_t &_c, const unsigned long &_d) : _node (_n), _ptr_parent (NULL), _color (_c), _discovery (_d), _finish (0) { }

      public:
        void set_parent (const _Node* const _ptr) { _ptr_parent = _ptr; }
        void set_color (const _color_t& _c) { _color = _c; }
        void set_discovery (const unsigned long& _d) { _discovery = _d; }
        void set_finish (const unsigned long& _f) { _finish = _f; }

        const _Node& node () const { return _node; }
        const _Node* const parent () const { return _ptr_parent; }
        const _color_t& color () const { return _color; }
        const unsigned long& discovery () const { return _discovery; }
        const unsigned long& finish () const { return _finish; }

      private:
        const _Node&  _node;
        const _Node*  _ptr_parent;
        _color_t      _color;
        unsigned long _discovery;
        unsigned long _finish;
    };
}

#endif
