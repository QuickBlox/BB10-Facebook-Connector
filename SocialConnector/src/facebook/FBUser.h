/*
 * FBUser.h
 *
 *  Created on: Feb 22, 2013
 *      Author: Vladimir Slatvinskiy
 */

#ifndef FBUSER_H_
#define FBUSER_H_

#include "FBAbstractObjectBase.h"
#include <QtCore>
#include <QtCore/QList>
#include <QMetaType>

#include "FBProfile.h"
#include "FBEducation.h"
#include "FBWork.h"

class FBUser: public FBAbstractObjectBase {
	Q_OBJECT
	Q_PROPERTY(QString name READ getName)
	Q_PROPERTY(QString first_name READ getFirstName)
	Q_PROPERTY(QString last_name READ getLastName)
	Q_PROPERTY(QString gender READ getGender)
	Q_PROPERTY(QString locale READ getLocale)
	Q_PROPERTY(QString link READ getLink)
	Q_PROPERTY(QString website READ getWebsite)
	Q_PROPERTY(QString updated_time_as_string READ getUpdatedTimeAsString)
	Q_PROPERTY(QString about READ getAbout)
	Q_PROPERTY(QString bio READ getBio)
	Q_PROPERTY(QString birthday_as_string READ getBirthdayAsString)
	Q_PROPERTY(QString email READ getEmail)
	Q_PROPERTY(QString political READ getPolitical)
	Q_PROPERTY(QString quotes READ getQuotes)
	Q_PROPERTY(QString relationship_status READ getRelationshipStatus)
	Q_PROPERTY(QString religion READ getReligion)
	Q_PROPERTY(QString third_party_id READ getThirdPartyId)
	Q_PROPERTY(QString updated_time READ getUpdatedTime)
	Q_PROPERTY(QString birthday READ getBirthday)
	Q_PROPERTY(FBProfile* hometown READ getHometown)
	Q_PROPERTY(FBProfile* location READ getLocation)
	Q_PROPERTY(FBProfile* significantOther READ getSignificantOther)
	Q_PROPERTY(QVariantList meeting_for READ getMeetingFor)
	Q_PROPERTY(QVariantList interested_in READ getInterestedIn)
	Q_PROPERTY(QList<FBEducation*> education READ getEducation)
	Q_PROPERTY(QList<FBWork*> work READ getWork)
	Q_PROPERTY(double timezone READ getTimezone)
	Q_PROPERTY(bool verified READ getVerified)

public:
	FBUser();
	virtual ~FBUser();
	void parseSearch(QVariantMap);
	void parse(QVariantMap);
	void parse(QVariantMap, ObjectType);

	Q_INVOKABLE QString getName();
	Q_INVOKABLE QString getFirstName();
	Q_INVOKABLE QString getLastName();
	Q_INVOKABLE QString getGender();
	Q_INVOKABLE QString getLocale();
	Q_INVOKABLE QString getLink();
	Q_INVOKABLE QString getWebsite();
	Q_INVOKABLE QString getUpdatedTimeAsString();
	Q_INVOKABLE QString getAbout();
	Q_INVOKABLE QString getBio();
	Q_INVOKABLE QString getBirthdayAsString();
	Q_INVOKABLE QString getEmail();
	Q_INVOKABLE QString getPolitical();
	Q_INVOKABLE QString getQuotes();
	Q_INVOKABLE QString getRelationshipStatus();
	Q_INVOKABLE QString getReligion();
	Q_INVOKABLE QString getThirdPartyId();
	Q_INVOKABLE QString getUpdatedTime();
	Q_INVOKABLE QString getBirthday();
	Q_INVOKABLE FBProfile* getHometown();
	Q_INVOKABLE FBProfile* getLocation();
	Q_INVOKABLE FBProfile* getSignificantOther();
	Q_INVOKABLE QVariantList getMeetingFor();
	Q_INVOKABLE QVariantList getInterestedIn();
	Q_INVOKABLE QList<FBEducation*> getEducation();
	Q_INVOKABLE QList<FBWork*> getWork();
	Q_INVOKABLE double getTimezone();
	Q_INVOKABLE bool getVerified();

private:
	QString m_name;
	QString m_first_name;
	QString m_last_name;
	QString m_gender;
	QString m_locale;
	QString m_link;
	QString m_website;
	QString m_updated_time_as_string;
	QString m_about;
	QString m_bio;
	QString m_birthday_as_string;
	QString m_email;
	QString m_political;
	QString m_quotes;
	QString m_relationship_status;
	QString m_religion;
	QString m_third_party_id;
	QString m_updated_time;
	QString m_birthday;

	FBProfile* m_Hometown;
	FBProfile* m_Location;
	FBProfile* m_SignificantOther;

    QVariantList      m_meeting_for;
    QVariantList      m_interested_in;
    QList<FBEducation*> m_education;
    QList<FBWork*>      m_work;
    double            m_timezone;
    bool              m_verified;
};

#endif /*FB USER_H_ */
