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
 * \file cgt/base/heap.h
 * \brief Contains definition of a heap container (based on vector container) for general use.
 * \author Leandro Costa
 * \date 2009
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CGTL__CGT_BASE_HEAP_H_
#define __CGTL__CGT_BASE_HEAP_H_

#ifdef CGTL_DO_NOT_USE_STL
#include "cgt/base/vector.h"
#include "cgt/base/alloc/allocator.h"
#else
#include <vector>
#include <algorithm>
#include "cgt/base/compares.h"
#endif


namespace cgt
{
  namespace base
  {
    /*!
     * \class heap
     * \brief A heap container based on vector.
     * \author Leandro Costa
     * \date 2009
     *
     * A heap container based on vector. It's not just a wrapper since
     * it contains some methods that not exist in the vector container,
     * as \b modify and \b modify_by template. The heap container should
     * be used if you wants to maintain the heap invariant always true.
     */

#ifdef CGTL_DO_NOT_USE_STL
    template<typename _TpItem, template<typename> class _HeapInvariant = cgt::base::_LessThan, typename _Alloc = cgt::base::alloc::_Allocator<_TpItem> >
      class heap : private cgt::base::vector<_TpItem, _HeapInvariant, _Alloc>
#else
    template<typename _TpItem, template<typename> class _HeapInvariant = cgt::base::_GreaterThan, typename _Alloc = std::allocator<_TpItem> >
      class heap : private std::vector<_TpItem, _Alloc>
#endif
    {
      private:
#ifdef CGTL_DO_NOT_USE_STL
        typedef cgt::base::vector<_TpItem, _HeapInvariant, _Alloc>  _Base;
#else
        typedef std::vector<_TpItem, _Alloc>  _Base;
#endif

      private:
        typedef typename _Base::iterator        _Iterator;
        typedef typename _Base::const_iterator  _ConstIterator;

      public:
#ifdef CGTL_DO_NOT_USE_STL
        using _Base::find;
#endif
        using _Base::clear;
        using _Base::size;
        using _Base::empty;
        using _Base::iterator;
        using _Base::const_iterator;
        using _Base::begin;
        using _Base::end;

      private:
        void _rebuild (size_t _pos);

      public:
#ifdef CGTL_DO_NOT_USE_STL
        void push (const _TpItem& _i) { _Base::push_heap (_i); }
        _TpItem* pop () { return _Base::pop_heap (); }
#else
        void push (const _TpItem& _i) { _Base::push_back (_i); std::push_heap (_Base::begin (), _Base::end (), _HeapInvariant<_TpItem>()); }
        _TpItem* pop () { std::pop_heap (_Base::begin (), _Base::end (), _HeapInvariant<_TpItem>()); _TpItem* p = new _TpItem (_Base::back ()); _Base::pop_back (); return p; }
#endif
        void modify (_ConstIterator& _it, const _TpItem& _i);
        void modify (_Iterator& _it, const _TpItem& _i) { modify (reinterpret_cast<_ConstIterator&>(_it), _i); }
 
      public:
        template<typename _Modifier, typename _Parm>
          void modify_by (_ConstIterator& _it, _Modifier _modify, const _Parm& _parm)
          {
            if (_it >= begin () && _it < end ())
            {
#ifdef CGTL_DO_NOT_USE_STL
              _TpItem* _ptr = &(*(find (*_it)));
#else
              _TpItem* _ptr = &(*(std::find (_Base::begin (), _Base::end (), *_it)));
#endif
              _modify (*_ptr, _parm);
              _rebuild (_it - begin () + 1);

#ifdef CGTL_DO_NOT_USE_STL
              _it = find (*_ptr);
#else
              _it = std::find (_Base::begin (), _Base::end (), *_ptr);
#endif
            }
          }
    };


    template<typename _TpItem, template<typename> class _HeapInvariant, typename _Alloc>
      void heap<_TpItem, _HeapInvariant, _Alloc>::_rebuild (size_t _pos)
      {
#ifdef CGTL_DO_NOT_USE_STL
        while (_pos > 0)
          _Base::rebuild_heap (--_pos);
#else
		std::make_heap (_Base::begin (), _Base::end (), _HeapInvariant<_TpItem>());
#endif
      }

    template<typename _TpItem, template<typename> class _HeapInvariant, typename _Alloc>
      void heap<_TpItem, _HeapInvariant, _Alloc>::modify (_ConstIterator& _it, const _TpItem& _i)
      {
        if (_it >= begin () && _it < end ())
        {
#ifdef CGTL_DO_NOT_USE_STL
          *(find (*_it)) = _i;
#else
          *(std::find (begin (), end (), *_it)) = _i;
#endif
          _rebuild (_it - begin () + 1);
        }
      }
  }
}

#endif // __CGTL__CGT_BASE_HEAP_H_
