/*
 * FBEducation.h
 *
 *  Created on: Feb 24, 2013
 *      Author: Vladimir
 */

#ifndef FBEDUCATION_H_
#define FBEDUCATION_H_

#include <QtCore>
#include <QtCore/QList>

#include "FBAbstractObjectBase.h"
#include "FBProfile.h"
#include <QMetaType>

class FBEducation: public FBAbstractObjectBase {
	Q_OBJECT
	Q_PROPERTY(QString type READ getType CONSTANT)
	Q_PROPERTY(FBProfile* school READ getSchool CONSTANT)
	Q_PROPERTY(FBProfile* degree READ getDegree CONSTANT)
	Q_PROPERTY(FBProfile* year READ getYear CONSTANT)
	Q_PROPERTY(QList<FBProfile*> concentration READ getConcentration CONSTANT)

public:
	FBEducation();
	virtual ~FBEducation();
	void parse(QVariantMap);
	void parse(QVariantMap, ObjectType);

	Q_INVOKABLE QString  getType();
	Q_INVOKABLE FBProfile* getSchool();
	Q_INVOKABLE FBProfile* getDegree();
	Q_INVOKABLE FBProfile* getYear();
	Q_INVOKABLE QList<FBProfile*>getConcentration();

private:
	QString type;
	FBProfile* school;
	FBProfile* degree;
	FBProfile* year;
	QList<FBProfile*> concentration;
};
Q_DECLARE_METATYPE(FBEducation*)
#endif /* FBEDUCATION_H_ */
