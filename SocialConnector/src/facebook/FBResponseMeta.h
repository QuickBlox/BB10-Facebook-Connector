/*
 * FBResponseMeta.h
 *
 *  Created on: Feb 18, 2013
 *      Author: Vladimir
 */

#ifndef FBRESPONSEMETA_H_
#define FBRESPONSEMETA_H_

#include "FBAbstractObjectBase.h"
#include <QtCore>

class FBResponseMeta: public FBAbstractObjectBase {
public:
	FBResponseMeta();
	virtual ~FBResponseMeta();
	void parse(QVariantMap);
	void setStatus(const int);
	void setMsg(const QString&);
	int getStatus();
	QString getMsg();
private:
	int status;
	QString msg;
};

#endif /* FBRESPONSEMETA_H_ */
