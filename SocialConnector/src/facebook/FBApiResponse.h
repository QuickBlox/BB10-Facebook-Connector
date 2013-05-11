/*
 * FBApiResponse.h
 *
 *  Created on: Feb 18, 2012
 *      Author: Vladimir
 */

#ifndef FBAPIRESPONSE_H_
#define FBAPIRESPONSE_H_

#include "FBApiResponseObjectFactory.h"
#include "FBResponseMeta.h"

class FBApiResponse {
public:
	FBApiResponse(FBApiResponseObjectFactory::ApiType);
	FBApiResponse(FBApiResponseObjectFactory::ApiType, FBAbstractObjectBase::ObjectType );
	virtual ~FBApiResponse();
	void parse(QByteArray);
	FBAbstractObjectBase* getResponse();
	FBResponseMeta* getMeta();
	FBApiResponseObjectFactory::ApiType getType();
private:
	FBResponseMeta* meta;
	FBAbstractObjectBase* response;
	FBApiResponseObjectFactory::ApiType type;
	FBAbstractObjectBase::ObjectType object_type;
};

#endif /* FBAPIRESPONSE_H_ */
