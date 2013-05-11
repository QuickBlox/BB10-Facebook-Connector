/*
 * FBListObject.h
 *
 *  Created on: Feb 25, 2013
 *      Author: Vladimir
 */

#ifndef FBLISTOBJECT_H_
#define FBLISTOBJECT_H_

#include <QtCore>
#include <QtCore/QList>
#include <QMetaType>

#include "FBAbstractObjectBase.h"

class FBListObject: public FBAbstractObjectBase {
	Q_OBJECT
public:
	FBListObject();
	virtual ~FBListObject();
	void parse(QVariantMap);
	void parse(QVariantMap, ObjectType);

	Q_INVOKABLE QVariantList  getList();

private:
	QVariantList m_objects;
};
Q_DECLARE_METATYPE(FBListObject*)
#endif /* FBLISTOBJECT_H_ */
