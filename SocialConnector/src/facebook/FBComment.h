/*
 * FBComment.h
 *
 *  Created on: Mar 3, 2013
 *      Author: Vladimir
 */

#ifndef FBCOMMENT_H_
#define FBCOMMENT_H_

#include "FBAbstractObjectBase.h"
#include "FBProfile.h"
#include <QMetaType>
#include <QtCore>
#include <QtCore/QList>
#include <QMetaType>

class FBComment: public FBAbstractObjectBase {
	Q_OBJECT
	Q_PROPERTY(QString created_time READ getCreatedTime CONSTANT)
	Q_PROPERTY(QString message READ getMessage CONSTANT)
	Q_PROPERTY(QString likes_count READ getLikesCount CONSTANT)
	Q_PROPERTY(bool can_remove READ isCanRemove CONSTANT)
	Q_PROPERTY(bool user_likes READ isUserLikes CONSTANT)

	Q_PROPERTY(FBProfile* from READ getFrom)

public:
	FBComment();
	virtual ~FBComment();
	void parse(QVariantMap);
	void parse(QVariantMap, ObjectType);

	Q_INVOKABLE QString getCreatedTime();
	Q_INVOKABLE QString getMessage();
	Q_INVOKABLE QString getLikesCount();
	Q_INVOKABLE bool isCanRemove();
	Q_INVOKABLE bool isUserLikes();

	Q_INVOKABLE FBProfile* getFrom();

private:
	QString m_created_time;
	QString m_message;
	QString m_likes_count;
	bool m_can_remove;
	bool m_user_likes;

	FBProfile* m_from;

};
Q_DECLARE_METATYPE(FBComment*)
#endif /* FBCOMMENT_H_ */
