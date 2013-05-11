/*
 * FBPlace.h
 *
 *  Created on: Feb 25, 2013
 *      Author: Vladimir
 */

#ifndef FBPLACE_H_
#define FBPLACE_H_

#include "FBAbstractObjectBase.h"
#include "FBLocation.h"
#include <QMetaType>

class FBPlace : public FBAbstractObjectBase {
		Q_OBJECT
		Q_PROPERTY(QString name READ getName CONSTANT)
		Q_PROPERTY(QString category READ getCategory CONSTANT)
		Q_PROPERTY(FBLocation* location READ getLocation CONSTANT)
public:
	FBPlace();
	virtual ~FBPlace();
	void parse(QVariantMap);
	void parse(QVariantMap, ObjectType);

	Q_INVOKABLE QString getName();
	Q_INVOKABLE QString getCategory();
	Q_INVOKABLE FBLocation* getLocation();

private:
	QString name;
	QString category;
	FBLocation* location;
};
Q_DECLARE_METATYPE(FBPlace*)
#endif /* FBPLACE_H_ */
