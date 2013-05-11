/*
 * FBEducation.cpp
 *
 *  Created on: Feb 24, 2013
 *      Author: Vladimir
 */

#include "FBEducation.h"

FBEducation::FBEducation() {
	// TODO Auto-generated constructor stub

}

FBEducation::~FBEducation() {
	// TODO Auto-generated destructor stub
}


void FBEducation::parse(QVariantMap _map)
{
	map = _map;
	if(map.contains("id")){
		id = map["id"].toString();
	}

	if(map.contains("type")){
		type = map["type"].toString();
	}

	if(map.contains("school")){
		QVariant v = map["school"];
		school = new FBProfile();
		school->parse(v.toMap());
	}

	if(map.contains("degree")){
		QVariant v = map["degree"];
		degree = new FBProfile();
		degree->parse(v.toMap());
	}

	if(map.contains("year")){
		QVariant v = map["year"];
		year = new FBProfile();
		year->parse(v.toMap());
	}

	if(map.contains("concentration")){
		QList<QVariant> list = map["concentration"].toList();
		foreach(const QVariant &b, list) {
			FBProfile *p = new FBProfile();
			p->parse(b.toMap());
			concentration.append(p);
		}
	}
}

void FBEducation::parse(QVariantMap map, ObjectType _type)
{

}

QString  FBEducation::getType()
{
	return type;
}

FBProfile* FBEducation::getSchool()
{
	return school;
}

FBProfile* FBEducation::getDegree()
{
	return degree;
}

FBProfile* FBEducation::getYear()
{
	return year;
}

QList<FBProfile*> FBEducation::getConcentration()
{
	return concentration;
}

