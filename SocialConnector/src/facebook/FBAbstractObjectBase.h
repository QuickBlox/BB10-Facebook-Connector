/*
 * FBAbstractObjectBase.h
 *
 *  Created on: Feb 18, 2013
 *      Author: Vladimir
 */

#ifndef FBABSTRACTOBJECTBASE_H_
#define FBABSTRACTOBJECTBASE_H_

#include <QtCore/QObject>
#include <QtCore/QVariantMap>
#include <QtCore/QVariantList>
#include <QMetaType>

class FBAbstractObjectBase : public QObject {
	Q_OBJECT
	Q_PROPERTY(QString id READ getId CONSTANT)
public:
	enum ObjectType { Empty, PlacesObjs, PostsObjs, ProfilesObjs, CommentsObjs};

	FBAbstractObjectBase();
	virtual ~FBAbstractObjectBase();

	Q_INVOKABLE QString getId();
	Q_INVOKABLE	QVariantMap getMap();
	Q_INVOKABLE bool getResult();
	void setResult(bool);

	virtual void parse(QVariantMap) =0;
	virtual void parse(QVariantMap, ObjectType) =0;

protected:
	QString id;
	bool result;
	ObjectType type;
	QVariantMap map;
};
Q_DECLARE_METATYPE(FBAbstractObjectBase*)
#endif /* FBABSTRACTOBJECTBASE_H_ */
