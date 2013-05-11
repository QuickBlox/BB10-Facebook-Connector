/*
 * FBLocation.h
 *
 *  Created on: Feb 25, 2013
 *      Author: Vladimir
 */

#ifndef FBLOCATION_H_
#define FBLOCATION_H_

#include "FBAbstractObjectBase.h"
#include <QMetaType>

class FBLocation : public FBAbstractObjectBase {
		Q_OBJECT
		Q_PROPERTY(QString street READ getStreet CONSTANT)
		Q_PROPERTY(QString city READ getCity CONSTANT)
		Q_PROPERTY(QString state READ getState CONSTANT)
		Q_PROPERTY(QString country READ getCountry CONSTANT)
		Q_PROPERTY(QString zip READ getZip CONSTANT)
		Q_PROPERTY(QString latitude READ getLatitude CONSTANT)
		Q_PROPERTY(QString longitude READ getLongitude CONSTANT)
public:
	FBLocation();
	virtual ~FBLocation();
	void parse(QVariantMap);
	void parse(QVariantMap, ObjectType);

	Q_INVOKABLE QString getStreet();
	Q_INVOKABLE QString getCity();
	Q_INVOKABLE QString getState();
	Q_INVOKABLE QString getCountry();
	Q_INVOKABLE QString getZip();
	Q_INVOKABLE QString getLatitude();
	Q_INVOKABLE QString getLongitude();

private:
	QString street;
	QString city;
	QString state;
	QString country;
	QString zip;
	QString latitude;
	QString longitude;
};
Q_DECLARE_METATYPE(FBLocation*)
#endif /* FBLOCATION_H_ */
