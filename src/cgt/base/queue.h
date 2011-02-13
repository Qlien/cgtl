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
 * \file cgt/base/queue.h
 * \brief Contains definition of queue container (based on list container) for general use.
 * \author Leandro Costa
 * \date 2009
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CGTL__CGT_BASE_QUEUE_H_
#define __CGTL__CGT_BASE_QUEUE_H_

#ifdef CGTL_DO_NOT_USE_STL
#include "cgt/base/list.h"
#else
#include <list>
#endif


namespace cgt
{
  namespace base
  {
    /*!
     * \class queue
     * \brief A queue container based on cgt::base::list.
     * \author Leandro Costa
     * \date 2009
     *
     * A queue container implemented as a list. It's just a wrapper for
     * the list container that exposes only a few set of methods in the
     * interface.
     */

    template<typename _TpItem>
#ifdef CGTL_DO_NOT_USE_STL
      class queue : private cgt::base::list<_TpItem>
#else
      class queue : public std::list<_TpItem>
#endif
    {
#ifdef CGTL_DO_NOT_USE_STL
      private:
        typedef cgt::base::list<_TpItem> _Base;

      public:
        using _Base::find;
        using _Base::clear;
        using _Base::size;
        using _Base::empty;
        using _Base::iterator;
        using _Base::const_iterator;
        using _Base::begin;
        using _Base::end;

      public:
        void insert (const _TpItem &_item) { _Base::_push_back (_item); }
        void enqueue (const _TpItem &_item) { _Base::_push_back (_item); }
        _TpItem* dequeue () { return _Base::_pop (_Base::_head); }
        _TpItem* first () { return _Base::_get (_Base::_head); }
#else
      private:
        typedef std::list<_TpItem> _Base;

	  public:
        void insert (const _TpItem &_item) { _Base::push_back (_item); }
        void enqueue (const _TpItem &_item) { _Base::push_back (_item); }
        //_TpItem* dequeue () { _TpItem* p = &(_Base::front ()); _Base::pop_front (); return p; }
        _TpItem* dequeue () { _TpItem* p = new _TpItem (_Base::front ()); _Base::pop_front (); return p; }
        _TpItem* first () { return &(_Base::front ()); }
#endif
    };
  }
}

#endif // __CGTL__CGT_BASE_QUEUE_H_
