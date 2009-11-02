#ifndef _HASH_H_
#define _HASH_H_

#include <string.h>
#include "hash_iterator.h"
#include "../alloc/allocator.h"
#include "hash_func.h"


namespace cgt
{
  namespace base
  {
    namespace hash
    {
      template<typename _TpKey, typename _TpItem>
        class _HashItem
        {
          public:
            _HashItem (const _TpKey& _k, const _TpItem& _i) : _key (_k), _item (_i), _next (NULL) { }

          public:
            _TpKey      _key;
            _TpItem     _item;
            _HashItem*  _next;
        };

      template<typename _TpKey, typename _TpItem, typename _Alloc = cgt::base::alloc::_Allocator<_HashItem<_TpKey, _TpItem> > >
        class _Hash
        {
          private:
            typedef _HashItem<_TpKey, _TpItem>  _Item;
            typedef _HashFunc<_TpKey>           _Func;

          private:
            typedef typename _Alloc::template rebind<_Item>::other allocator_type;

          public:
            typedef _HashIterator<_TpItem>            iterator;
            typedef _HashIterator<_TpItem, _TpConst>  const_iterator;

          public:
            _Hash () : _size (0), _tabsize (2) { _init (); }
            virtual ~_Hash () { _remove_all (); free (_table); }

          private:
            void _init ();
            void _increase ();
            void _insert (_Item* const _p);
            _Item* _pop (_Item** const _p);
            void _remove_all ();
            const size_t _get_position (const _TpKey& _key) const;
            _TpItem** _get_head ();
            _TpItem** _get_tail ();

          public:
            void insert (const _TpKey& _key, const _TpItem& _item);

          public:
            _TpItem* operator[](const _TpKey& _key);

          public:
            void dump () const;

//            iterator begin () { return iterator (_get_head ()); }
//            iterator end () { return iterator (_get_tail ()); }
//            const_iterator begin () const { return const_iterator (_get_head ()); }
//            const_iterator end () const { return const_iterator (_get_tail ()); }

          private:
            _Item** _table;
            size_t  _size;
            size_t  _tabsize;

            _Func           _hash_func;
            allocator_type  _alloc;
        };


      template<typename _TpKey, typename _TpItem, typename _Alloc>
        void _Hash<_TpKey, _TpItem, _Alloc>::_init ()
        {
          _table = (_Item **) malloc (_tabsize * sizeof (_Item **));
          bzero (_table, _tabsize * sizeof (_Item **));
        }

      template<typename _TpKey, typename _TpItem, typename _Alloc>
        void _Hash<_TpKey, _TpItem, _Alloc>::_increase ()
        {
          _tabsize *= 2;
          _table = (_Item **) realloc (_table, _tabsize * sizeof (_Item **));
          bzero (&(_table [_size]), (_tabsize/2) * sizeof (_Item **));

          for (size_t i = 0; i < _tabsize/2; i++)
          {
            _Item** _ptr = &(_table [i]);

            while (*_ptr)
            {
              if (_get_position ((*_ptr)->_key) != i)
                _insert (_pop (_ptr));
              else
                _ptr = &((*_ptr)->_next);
            }
          }
        }

      template<typename _TpKey, typename _TpItem, typename _Alloc>
        void _Hash<_TpKey, _TpItem, _Alloc>::_insert (_Item* const _p)
        {
          _Item** _ptr = &(_table [_get_position (_p->_key)]);
          while (*_ptr)
            _ptr = &((*_ptr)->_next);
          *_ptr = _p;

          _size++;
        }

      template<typename _TpKey, typename _TpItem, typename _Alloc>
        _HashItem<_TpKey, _TpItem>* _Hash<_TpKey, _TpItem, _Alloc>::_pop (_Item** const _p)
        {
          _Item* _ptr = *_p;
          *_p = (*_p)->_next;
          _ptr->_next = NULL;
          _size--;

          return _ptr;
        }

      template<typename _TpKey, typename _TpItem, typename _Alloc>
        void _Hash<_TpKey, _TpItem, _Alloc>::_remove_all ()
        {
          for (size_t i = 0; i < _tabsize; i++)
          {
            while (_table [i])
            {
              _Item* _ptr = _table [i];
              _table [i] = _table [i]->_next;
              _alloc.destroy (_ptr);
              _alloc.deallocate (_ptr, 1);
            }
          }
        }

      template<typename _TpKey, typename _TpItem, typename _Alloc>
        const size_t _Hash<_TpKey, _TpItem, _Alloc>::_get_position (const _TpKey& _key) const
        {
          return (_hash_func (_key) % _tabsize);
        }

      template<typename _TpKey, typename _TpItem, typename _Alloc>
        _TpItem** _Hash<_TpKey, _TpItem, _Alloc>::_get_head ()
        {
          _TpItem** _ptr = &(_table [0]);

          while (! *_ptr)
            _ptr++;

          return _ptr;
        }

      template<typename _TpKey, typename _TpItem, typename _Alloc>
        _TpItem** _Hash<_TpKey, _TpItem, _Alloc>::_get_tail ()
        {
          _TpItem** _ptr = &(_table [0]);

          while (! *_ptr)
            _ptr++;

          return _ptr;
        }

      template<typename _TpKey, typename _TpItem, typename _Alloc>
        void _Hash<_TpKey, _TpItem, _Alloc>::insert (const _TpKey& _key, const _TpItem& _item)
        {
          if (_size == _tabsize)
            _increase ();

          _Item* _ptr = _alloc.allocate (1);
          _alloc.construct (_ptr, _Item (_key, _item));
          _insert (_ptr);
        }

      template<typename _TpKey, typename _TpItem, typename _Alloc>
        _TpItem* _Hash<_TpKey, _TpItem, _Alloc>::operator[](const _TpKey& _key)
        {
          _TpItem* _ptr = NULL;

          _Item* _p = _table [_get_position (_key)];

          while (_p && _p->_key != _key)
            _p = _p->_next;

          if (_p)
            _ptr = &(_p->_item);

          return _ptr;
        }

      template<typename _TpKey, typename _TpItem, typename _Alloc>
        void _Hash<_TpKey, _TpItem, _Alloc>::dump () const
        {
          cout << "dump - _tabsize: " << _tabsize << endl;

          for (size_t i = 0; i < _tabsize; i++)
          {
            _Item* _ptr = _table [i];

            while (_ptr)
            {
              cout << "dump - pos: " << i << ", key: " << _ptr->_key << ", value: " << _ptr->_item << ", _get_position (): " << _get_position (_ptr->_key) << endl;
              _ptr = _ptr->_next;
            }
          }
        }

      template<typename _TpKey, typename _TpItem>
        class hash : public _Hash<_TpKey, _TpItem> { };
    }
  }
}


#endif