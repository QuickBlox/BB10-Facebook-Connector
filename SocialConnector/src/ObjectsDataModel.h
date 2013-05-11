/*
 * ObjectsDataModel.h
 *
 *  Created on: Feb 27, 2013
 *      Author: Vladimir
 */

#ifndef OBJECTSDATAMODEL_H_
#define OBJECTSDATAMODEL_H_

#include <QObject>
#include <QString>
#include <QVariant>
#include <QMetaType>
#include <bb/data/JsonDataAccess>
#include <bb/cascades/DataModel>
#include <bb/cascades/QListDataModel>

class ObjectsDataModel : public bb::cascades::QVariantListDataModel
{
	Q_OBJECT
public:
	ObjectsDataModel();
	virtual ~ObjectsDataModel();

	Q_INVOKABLE void appendData(QVariantList list);
};

#endif /* OBJECTSDATAMODEL_H_ */
