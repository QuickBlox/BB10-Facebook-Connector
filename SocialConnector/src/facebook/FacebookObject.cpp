/*
 * FacebookObject.cpp
 *
 *  Created on: Feb 28, 2013
 *      Author: Vladimir
 */

#include "FacebookObject.h"
#include <QtCore>
#include <QtCore/QObject>

FacebookObject::FacebookObject():is_silhouette(false) {
	// TODO Auto-generated constructor stub

}

FacebookObject::~FacebookObject() {
	// TODO Auto-generated destructor stub
}

void FacebookObject::parse(QVariantMap _map)
{
	map = _map;

	if(map.contains("id")){
		id = map["id"].toString();
	}

	if(map.contains("data"))
	{
		QVariant obj = map["data"];
		if(obj.canConvert(QVariant::List))
		{
			QVariantList list = map["data"].toList();
			for(int i=0; i<list.size(); i++)
			{
				QVariant item = list.at(i);
				if(item.canConvert(QVariant::Map))
				{
					QVariantMap answerMap = item.toMap();

					if(answerMap.contains("object_id"))
					{
						object_id = answerMap["object_id"].toString();
					}
				}
			}
		}
		if(obj.canConvert(QVariant::Map))
		{
			QVariantMap answerMap = map["data"].toMap();

			if(answerMap.contains("url"))
			{
				url = answerMap["url"].toString();
			}

			if(answerMap.contains("is_silhouette"))
			{
				is_silhouette = answerMap["is_silhouette"].toBool();
			}

			if(answerMap.contains("object_id"))
			{
				object_id = answerMap["object_id"].toString();
			}
		}
	}

}

void FacebookObject::parse(QVariantMap, ObjectType)
{

}

QString FacebookObject::getUrl()
{
	return url;
}

void FacebookObject::setUrl(QString value)
{
	url = value;
}

bool FacebookObject::getSilhuette()
{
	return is_silhouette;
}

void FacebookObject::setSilhuette(bool value)
{
	is_silhouette = value;
}

QString FacebookObject::getObjectId()
{
	return object_id;
}

void FacebookObject::setObjectId(QString value)
{
	object_id = value;
}
