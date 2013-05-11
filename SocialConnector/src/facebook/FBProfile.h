/*
 * FBProfile.h
 *
 *  Created on: Feb 24, 2013
 *      Author: Vladimir
 */

#ifndef FBPROFILE_H_
#define FBPROFILE_H_

#include "FBAbstractObjectBase.h"
#include <QMetaType>

class FBProfile: public FBAbstractObjectBase {
	Q_OBJECT
	Q_PROPERTY(QString name READ getName CONSTANT)
public:
	FBProfile();
	virtual ~FBProfile();
	void parse(QVariantMap);
	void parse(QVariantMap, ObjectType);

	Q_INVOKABLE QString getName();

private:
	QString name;
};
Q_DECLARE_METATYPE(FBProfile*)
#endif /* FBPROFILE_H_ */
