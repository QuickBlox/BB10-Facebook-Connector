/*
 * FacebookObject.h
 *
 *  Created on: Feb 28, 2013
 *      Author: Vladimir
 */

#ifndef FACEBOOKOBJECT_H_
#define FACEBOOKOBJECT_H_

#include "FBAbstractObjectBase.h"
#include <QMetaType>

class FacebookObject : public FBAbstractObjectBase {
		Q_OBJECT
		Q_PROPERTY(QString url READ getUrl)
		Q_PROPERTY(bool is_silhouette READ getSilhuette)
		Q_PROPERTY(QString object_id READ getObjectId)

public:
	FacebookObject();
	virtual ~FacebookObject();

	void parse(QVariantMap);
	void parse(QVariantMap, ObjectType);

	Q_INVOKABLE QString getUrl();
	void setUrl(QString);
	Q_INVOKABLE QString getObjectId();
	void setObjectId(QString);

	Q_INVOKABLE bool getSilhuette();
	void setSilhuette(bool);

private:
	QString url;
	bool is_silhouette;
	QString object_id;
};
Q_DECLARE_METATYPE(FacebookObject*)
#endif /* FACEBOOKOBJECT_H_ */
