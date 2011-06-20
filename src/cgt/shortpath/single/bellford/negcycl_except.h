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
 * \file cgt/shortpath/single/bellford/negcycl_exception.h
 * \brief Exception class for negative cycle.
 * \author Leandro Costa
 * \date 2011
 *
 * $LastChangedDate: 2011-02-21 17:48:12 -0300 (Seg, 21 Fev 2011) $
 * $LastChangedBy: leandro.costa@gmail.com $
 * $Revision: 128 $
 */

#ifndef __CGTL__CGT_SHORTPATH_SINGLE_BELLFORD_NEGCYCL_EXCEPT_H_
#define __CGTL__CGT_SHORTPATH_SINGLE_BELLFORD_NEGCYCL_EXCEPT_H_

#include "cgt/base/exception/exception.h"

namespace cgt
{
	namespace shortpath
	{
		namespace single
		{
			namespace bellford
			{
				 /*!
				  * \class negcycl_except
				  * \brief Exception thrown by allocator where it's not possible to allocate memory.
				  * \author Leandro Costa
				  * \date 2009
				  *
				  * \exception negcycl_except It was not possible to allocate memory.
				  */
				class negcycl_except : public cgt::base::exception::exception
				{
					public:
						negcycl_except (const char* _m) : cgt::base::exception::exception (_m) { }
				};
			}
		}
	}
}

#endif // __CGTL__CGT_SHORTPATH_SINGLE_BELLFORD_NEGCYCL_EXCEPT_H_
