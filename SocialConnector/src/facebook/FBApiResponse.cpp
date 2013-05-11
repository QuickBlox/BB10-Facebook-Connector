/*
 * ApiResponse.cpp
 *
 *  Created on: Feb 18, 20132
 *      Author: Vladimir
 */

#include "FBApiResponse.h"
#include <QtCore/QVariant>
#include <QtCore/QVariantMap>
#include <QtCore>
#include <QDir>
#include <QObject>
#include <QtGui/QImage>
#include "FBJson.h"

FBApiResponse::FBApiResponse(FBApiResponseObjectFactory::ApiType targetType) {
	response = FBApiResponseObjectFactory::createApiResponseObject(targetType);
	type = targetType;
	object_type = FBAbstractObjectBase::Empty;
}

FBApiResponse::FBApiResponse(FBApiResponseObjectFactory::ApiType targetType, FBAbstractObjectBase::ObjectType objectTargetType) {
	response = FBApiResponseObjectFactory::createApiResponseObject(targetType);
	type = targetType;
	object_type = objectTargetType;
}

FBApiResponse::~FBApiResponse() {
}

FBAbstractObjectBase* FBApiResponse::getResponse() {
	return response;
}

FBResponseMeta* FBApiResponse::getMeta() {
	return meta;
}

FBApiResponseObjectFactory::ApiType FBApiResponse::getType() {
	return type;
}

void FBApiResponse::parse(QByteArray data) {
	QString json(data);
	bool ok;
	QVariant resp = QtJson::FBJson::parse(json,ok);
	if (response != NULL)
	{
        if(resp.canConvert(QVariant::Map))
		{
        	if(object_type ==  FBAbstractObjectBase::Empty)
        	{
        		response->parse(resp.toMap());
        	}
        	else
        	{
        		response->parse(resp.toMap(), object_type);
        	}
		}
        else if(resp.canConvert(QVariant::Bool))
        {
        	bool res = resp.toBool();
        	response->setResult(res);
        }
	}
}

