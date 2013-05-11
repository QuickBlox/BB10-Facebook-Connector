/*
 * FBApiResponseObjectFactory.h
 *
 *  Created on: Feb 19, 2013
 *      Author: Vladimir
 */

#ifndef FBAPIRESPONSEOBJECTFACTORY_H_
#define FBAPIRESPONSEOBJECTFACTORY_H_

#include "FBAbstractObjectBase.h"
#include "FBUser.h"
#include "FBListObject.h"
#include "FacebookObject.h"

class FBApiResponseObjectFactory {
public:
	enum ApiType { Empty, FacebookObj, UserObj, ListObj};

	FBApiResponseObjectFactory();
	virtual ~FBApiResponseObjectFactory();
	static FBAbstractObjectBase* createApiResponseObject(ApiType type) {
		switch(type) {
		default:
		case UserObj:
			return new FBUser;
		case ListObj:
			return new FBListObject;
		case FacebookObj:
			return new FacebookObject;
		case Empty:
			return NULL;
		}
	}
};

#endif /* FBAPIRESPONSEOBJECTFACTORY_H_ */
