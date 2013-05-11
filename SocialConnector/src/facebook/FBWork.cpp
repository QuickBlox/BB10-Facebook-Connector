/*
 * FBWork.cpp
 *
 *  Created on: Feb 24, 2013
 *      Author: Vladimir
 */

#include "FBWork.h"

FBWork::FBWork() {
	// TODO Auto-generated constructor stub

}

FBWork::~FBWork() {
	// TODO Auto-generated destructor stub
}

void FBWork::parse(QVariantMap _map)
{
	map = _map;
	if(map.contains("id")){
		id = map["id"].toString();
	}

	if(map.contains("start_date")){
		start_date = map["start_date"].toString();
	}

	if(map.contains("end_date")){
		end_date = map["end_date"].toString();
	}

	if(map.contains("employer")){
		QVariant v = map["employer"];
		employer = new FBProfile();
		employer->parse(v.toMap());
	}

	if(map.contains("location")){
		QVariant v = map["location"];
		location = new FBProfile();
		location->parse(v.toMap());
	}

	if(map.contains("position")){
		QVariant v = map["position"];
		position = new FBProfile();
		position->parse(v.toMap());
	}
}

void FBWork::parse(QVariantMap map, ObjectType _type)
{

}

QString  FBWork::getStartDate()
{
	return start_date;
}

QString  FBWork::getEndDate()
{
	return end_date;
}

FBProfile* FBWork::getEmployer()
{
	return employer;
}

FBProfile* FBWork::getLocation()
{
	return location;
}

FBProfile* FBWork::getPosition()
{
	return position;
}




