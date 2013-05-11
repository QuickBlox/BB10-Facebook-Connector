/*
 * FBRequestEnvelope.cpp
 *
 *  Created on: Feb 19, 2013
 *      Author: Vladimir
 */

#include "FBRequestEnvelope.h"

FBRequestEnvelope::FBRequestEnvelope(FBApiResponseObjectFactory::ApiType type,KQOAuthRequest* apiRequest) {
	response = new FBApiResponse(type);
	request = apiRequest;
}

FBRequestEnvelope::FBRequestEnvelope(FBApiResponseObjectFactory::ApiType type, FBAbstractObjectBase::ObjectType object_type, KQOAuthRequest* apiRequest) {
	response = new FBApiResponse(type, object_type);
	request = apiRequest;
}

FBRequestEnvelope::FBRequestEnvelope(QString data_param1, FBApiResponseObjectFactory::ApiType type,KQOAuthRequest* apiRequest) {
	response = new FBApiResponse(type);
	request = apiRequest;
	param1 = data_param1;
}

FBRequestEnvelope::FBRequestEnvelope(QString data_param1, FBApiResponseObjectFactory::ApiType type, FBAbstractObjectBase::ObjectType object_type, KQOAuthRequest* apiRequest) {
	response = new FBApiResponse(type, object_type);
	request = apiRequest;
	param1 = data_param1;
}

FBRequestEnvelope::~FBRequestEnvelope() {
	delete request;
}

KQOAuthRequest* FBRequestEnvelope::getRequest() {
	return request;
}

void FBRequestEnvelope::makeRequest() {
	connect(Facebook::instance()->getRequestManager(), SIGNAL(requestReady(QByteArray)), this, SLOT(onRequestCallback(QByteArray)));
	request->setEnableDebugOutput(true);
	Facebook::instance()->getRequestManager()->executeRequest(request);
}

void FBRequestEnvelope::onRequestCallback(QByteArray resp) {
	disconnect(Facebook::instance()->getRequestManager(), SIGNAL(requestReady(QByteArray)), this, SLOT(onRequestCallback(QByteArray)));
	if(resp.isEmpty())
	{
		//error need to tell the UI
		emit requestError(0x0);
		return;
	}
	response->parse(resp);

	if(response->getType() == FBApiResponseObjectFactory::Empty)
	{
		emit requestComplete(NULL);
	}
	else if(response->getResponse() != NULL)
	{
		if(param1 == NULL)
		{
			emit requestComplete(response->getResponse());
		}
		else
		{
			emit requestComplete(param1, response->getResponse());
		}
	}
	else
	{
		emit requestError(response->getMeta());
	}
}
