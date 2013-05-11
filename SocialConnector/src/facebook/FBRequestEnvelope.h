/*
 * FBRequestEnvelope.h
 *
 *  Created on: Feb 19, 2013
 *      Author: Vladimir
 */

#ifndef FBREQUESTENVELOPE_H_
#define FBREQUESTENVELOPE_H_

#include <qobject.h>
#include <QtCore>
#include "FBApiResponseObjectFactory.h"
#include "FBApiResponse.h"
#include "../oauth/kqoauthrequest.h"
#include "Facebook.hpp"

class FBRequestEnvelope: public QObject {
	Q_OBJECT
public:
	FBRequestEnvelope(FBApiResponseObjectFactory::ApiType,KQOAuthRequest*);
	FBRequestEnvelope(FBApiResponseObjectFactory::ApiType, FBAbstractObjectBase::ObjectType, KQOAuthRequest*);
	FBRequestEnvelope(QString, FBApiResponseObjectFactory::ApiType,KQOAuthRequest*);
	FBRequestEnvelope(QString, FBApiResponseObjectFactory::ApiType, FBAbstractObjectBase::ObjectType, KQOAuthRequest*);
	~FBRequestEnvelope();
	KQOAuthRequest* getRequest();
	void makeRequest();
public slots:
	void onRequestCallback(QByteArray);
signals:
	void requestComplete(FBAbstractObjectBase*);
	void requestComplete(QString, FBAbstractObjectBase*);
	void requestError(FBResponseMeta*);
private:
	KQOAuthRequest* request;
	FBApiResponse* response;
	QString param1;
};

#endif /* FBREQUESTENVELOPE_H_ */
