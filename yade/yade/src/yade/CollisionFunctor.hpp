/***************************************************************************
 *   Copyright (C) 2004 by Olivier Galizzi                                 *
 *   olivier.galizzi@imag.fr                                               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __COLLISIONFUNCTOR_H__
#define __COLLISIONFUNCTOR_H__

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>
#include <set>

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "ClassFactory.hpp"
#include "Indexable.hpp"
#include "CollisionModel.hpp"
#include "Se3.hpp"
#include "Contact.hpp"
#include "Serializable.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

/*! \brief Abstract interface for all collision functor.

	Every functions that describe collision between two CollisionModels must derived from CollisionFunctor.
*/
class CollisionFunctor : public Indexable , public Serializable
{

	private : bool reverse;

	public : void setReverse(bool r) { reverse = r; };
	public : bool isReverse() { return reverse; };

	// construction
	public : CollisionFunctor () {};
	public : virtual ~CollisionFunctor () {};

	protected : virtual bool collide(const shared_ptr<CollisionModel> , const shared_ptr<CollisionModel> , const Se3& , const Se3& , shared_ptr<Contact> ) { throw; };
	protected : virtual bool reverseCollide(const shared_ptr<CollisionModel> , const shared_ptr<CollisionModel> ,  const Se3& , const Se3& , shared_ptr<Contact> ) { throw; };

	public    : inline bool operator() (const shared_ptr<CollisionModel> cm1, const shared_ptr<CollisionModel> cm2, const Se3& se31, const Se3& se32, shared_ptr<Contact> c)
	{
		if (reverse)
			return reverseCollide(cm1,cm2,se31,se32,c);
		else
			return collide(cm1,cm2,se31,se32,c);
	}

// FIXME : this should be just Factorable, not Serializable !!
	public    : virtual void registerAttributes() {};

};

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////


#endif // __COLLISIONFUNCTOR_H__

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
