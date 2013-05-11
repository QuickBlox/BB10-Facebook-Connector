/*
 * FBWork.h
 *
 *  Created on: Feb 24, 2013
 *      Author: Vladimir
 */

#ifndef FBWORK_H_
#define FBWORK_H_

#include "FBAbstractObjectBase.h"
#include "FBProfile.h"
#include <QMetaType>
class FBWork: public FBAbstractObjectBase {
		Q_OBJECT
		Q_PROPERTY(FBProfile* employer READ getEmployer CONSTANT)
		Q_PROPERTY(FBProfile* position READ getPosition CONSTANT)
		Q_PROPERTY(FBProfile* location READ getLocation CONSTANT)
		Q_PROPERTY(QString start_date READ getStartDate CONSTANT)
		Q_PROPERTY(QString end_date READ getEndDate CONSTANT)
public:
	FBWork();
	virtual ~FBWork();
	void parse(QVariantMap);
	void parse(QVariantMap, ObjectType);

	Q_INVOKABLE FBProfile* getEmployer();
	Q_INVOKABLE FBProfile* getLocation();
	Q_INVOKABLE FBProfile* getPosition();
	Q_INVOKABLE QString getStartDate();
	Q_INVOKABLE QString getEndDate();

private:
	FBProfile* employer;
	FBProfile* location;
	FBProfile* position;
	QString  start_date;
	QString  end_date;
};
Q_DECLARE_METATYPE(FBWork*)
#endif /* FBWORK_H_ */
