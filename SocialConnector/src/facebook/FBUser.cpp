/*
 * FBUser.cpp
 *
 *  Created on: Feb 22, 2013
 *      Author: Vladimir Slatvinskiy
 */

#include "FBUser.h"

FBUser::FBUser():
m_Hometown(0x0),
m_Location(0x0),
m_SignificantOther(0x0),
m_timezone(0),
m_verified(false)
{

}

FBUser::~FBUser() {
}

void FBUser::parse(QVariantMap map)
{
	if(map.contains("id")){
		id = map["id"].toString();
	}

	if(map.contains("name")){
		m_name = map["name"].toString();
	}

	if(map.contains("first_name")){
		m_first_name = map["first_name"].toString();
	}

	if(map.contains("last_name")){
		m_last_name = map["last_name"].toString();
	}

	if(map.contains("gender")){
		m_gender = map["gender"].toString();
	}

	if(map.contains("locale")){
		m_locale = map["locale"].toString();
	}

	if(map.contains("link")){
		m_link = map["link"].toString();
	}

	if(map.contains("website")){
		m_website = map["website"].toString();
	}

	if(map.contains("updated_time")){
		m_updated_time = map["updated_time"].toString();
	}

	if(map.contains("about")){
		m_about = map["about"].toString();
	}

	if(map.contains("bio")){
		m_bio = map["bio"].toString();
	}

	if(map.contains("birthday")){
		m_birthday = map["birthday"].toString();
	}

	if(map.contains("email")){
		m_email = map["email"].toString();
	}

	if(map.contains("political")){
		m_political = map["political"].toString();
	}

	if(map.contains("quotes")){
		m_quotes = map["quotes"].toString();
	}

	if(map.contains("relationship_status")){
		m_relationship_status = map["relationship_status"].toString();
	}

	if(map.contains("religion")){
		m_religion = map["religion"].toString();
	}

	if(map.contains("third_party_id")){
		m_third_party_id = map["third_party_id"].toString();
	}

	if(map.contains("updated_time")){
		m_updated_time = map["updated_time"].toString();
	}

	if(map.contains("birthday")){
		m_birthday = map["birthday"].toString();
	}

	if(map.contains("timezone")){
		m_timezone = map["timezone"].toDouble();
	}

	if(map.contains("verified")){
		m_verified = map["verified"].toBool();
	}

	if(map.contains("hometown")){
		QVariant v = map["hometown"];
		m_Hometown = new FBProfile();
		m_Hometown->parse(v.toMap());
	}

	if(map.contains("location")){
		QVariant v = map["location"];
		m_Location = new FBProfile();
		m_Location->parse(v.toMap());
	}

	if(map.contains("significant_other")){
		QVariant v = map["significant_other"];
		m_SignificantOther  = new FBProfile();
		m_SignificantOther->parse(v.toMap());
	}

	if(map.contains("work")){
		QList<QVariant> list = map["work"].toList();
		foreach(const QVariant &b, list) {
			FBWork *w = new FBWork();
			w->parse(b.toMap());
			m_work.append(w);
		}
	}

	if(map.contains("education")){
		QList<QVariant> list = map["education"].toList();
		foreach(const QVariant &b, list) {
			FBEducation *e = new FBEducation();
			e->parse(b.toMap());
			m_education.append(e);
		}
	}

	if(map.contains("meeting_for")){
		QVariantList blogList = map["meeting_for"].toList();
		foreach(const QVariant &item, blogList) {
			m_meeting_for.append(item);
		}
	}

	if(map.contains("interested_in")){
		QVariantList blogList = map["interested_in"].toList();
		foreach(const QVariant &item, blogList) {
			m_interested_in.append(item);
		}
	}
}

void FBUser::parse(QVariantMap map, ObjectType _type)
{

}

QString FBUser::getName()
{
	return QString(m_name);
}

QString FBUser::getFirstName()
{
	return QString(m_first_name);
}

QString FBUser::getLastName()
{
	return QString(m_last_name);
}

QString FBUser::getGender()
{
	return QString(m_gender);
}

QString FBUser::getLocale()
{
	return QString(m_locale);
}

QString FBUser::getLink()
{
	return QString(m_link);
}

QString FBUser::getWebsite()
{
	return QString(m_website);
}

QString FBUser::getUpdatedTimeAsString()
{
	return QString(m_updated_time_as_string);
}

QString FBUser::getAbout()
{
	return QString(m_about);
}

QString FBUser::getBio()
{
	return QString(m_bio);
}

QString FBUser::getBirthdayAsString()
{
	return QString(m_birthday_as_string);
}

QString FBUser::getEmail()
{
	return QString(m_email);
}

QString FBUser::getPolitical()
{
	return QString(m_political);
}

QString FBUser::getQuotes()
{
	return QString(m_quotes);
}

QString FBUser::getRelationshipStatus()
{
	return QString(m_relationship_status);
}

QString FBUser::getReligion()
{
	return QString(m_religion);
}

QString FBUser::getThirdPartyId()
{
	return QString(m_third_party_id);
}

QString FBUser::getUpdatedTime()
{
	return QString(m_updated_time);
}

QString FBUser::getBirthday()
{
	return QString(m_birthday);
}

FBProfile* FBUser::getHometown()
{
	return m_Hometown;
}

FBProfile* FBUser::getLocation()
{
	return m_Location;
}

FBProfile* FBUser::getSignificantOther()
{
	return m_SignificantOther;
}

QVariantList FBUser::getMeetingFor()
{
	return m_meeting_for;
}

QVariantList FBUser::getInterestedIn()
{
	return m_interested_in;
}

QList<FBEducation*> FBUser::getEducation()
{
	return m_education;
}

QList<FBWork*> FBUser::getWork()
{
	return m_work;
}

double FBUser::getTimezone()
{
	return m_timezone;
}

bool FBUser::getVerified()
{
	return m_verified;
}


