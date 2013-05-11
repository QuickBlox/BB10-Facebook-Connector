/*
 * FBPost.h
 *
 *  Created on: Feb 28, 2013
 *      Author: Vladimir
 */

#ifndef FBPOST_H_
#define FBPOST_H_

#include "FBAbstractObjectBase.h"
#include "FBProfile.h"
#include <QMetaType>
#include <QtCore>
#include <QtCore/QList>
#include <QMetaType>

class FBPost: public FBAbstractObjectBase {
		Q_OBJECT
		Q_PROPERTY(QString likes_count READ getLikesCount CONSTANT)
		Q_PROPERTY(QString comments_count READ getCommentsCount CONSTANT)
		Q_PROPERTY(QString shares_count READ getSharesCount CONSTANT)
		Q_PROPERTY(QString message READ getMessage CONSTANT)
		Q_PROPERTY(QString picture READ getPicture CONSTANT)
		Q_PROPERTY(QString link READ getLink CONSTANT)
		Q_PROPERTY(QString name READ getName CONSTANT)
		Q_PROPERTY(QString caption READ getCaption CONSTANT)
		Q_PROPERTY(QString description READ getDescription CONSTANT)
		Q_PROPERTY(QString source READ getSource CONSTANT)
		Q_PROPERTY(QString story READ getStory CONSTANT)
		Q_PROPERTY(QString icon READ getIcon CONSTANT)
		Q_PROPERTY(QString attribution READ getAttribution CONSTANT)
		Q_PROPERTY(QString created_time READ getCreatedTime CONSTANT)
		Q_PROPERTY(QString updated_time READ getUpdatedTime CONSTANT)
		Q_PROPERTY(QString type READ getType CONSTANT)

		Q_PROPERTY(FBProfile* from READ getFrom)

		Q_PROPERTY(QList<FBProfile*> to READ getTo)
public:
	FBPost();
	virtual ~FBPost();
	void parse(QVariantMap);
	void parse(QVariantMap, ObjectType);

	Q_INVOKABLE QString getLikesCount();
	Q_INVOKABLE QString getCommentsCount();
	Q_INVOKABLE QString getSharesCount();
	Q_INVOKABLE QString getMessage();
	Q_INVOKABLE QString getPicture();
	Q_INVOKABLE QString getLink();
	Q_INVOKABLE QString getName();
	Q_INVOKABLE QString getCaption();
	Q_INVOKABLE QString getDescription();
	Q_INVOKABLE QString getSource();
	Q_INVOKABLE QString getStory();
	Q_INVOKABLE QString getIcon();
	Q_INVOKABLE QString getAttribution();
	Q_INVOKABLE QString getCreatedTime();
	Q_INVOKABLE QString getUpdatedTime();
	Q_INVOKABLE QString getType();

	Q_INVOKABLE FBProfile* getFrom();

	Q_INVOKABLE QList<FBProfile*> getTo();

private:
	QString m_likes_count;
	QString m_comments_count;
	QString m_shares_count;
	QString m_message;
	QString m_picture;
	QString m_link;
	QString m_name;
	QString m_caption;
	QString m_description;
	QString m_source;
	QString m_story;
	QString m_icon;
	QString m_attribution;
	QString m_created_time;
	QString m_updated_time;
	QString m_type;

	FBProfile* m_from;

	QList<FBProfile*> m_to;
};
Q_DECLARE_METATYPE(FBPost*)
#endif /* FBPOST_H_ */
