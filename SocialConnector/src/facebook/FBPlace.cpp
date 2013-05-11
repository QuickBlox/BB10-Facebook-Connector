/*
 * FBPlace.cpp
 *
 *  Created on: Feb 25, 2013
 *      Author: Vladimir
 */

#include "FBPlace.h"

FBPlace::FBPlace() {
	// TODO Auto-generated constructor stub

}

FBPlace::~FBPlace() {
	// TODO Auto-generated destructor stub
}

void FBPlace::parse(QVariantMap _map)
{
	map = _map;

	if(map.contains("id")){
		id = map["id"].toString();
	}

	if(map.contains("name")){
		name = map["name"].toString();
	}

	if(map.contains("category")){
		category = map["category"].toString();
	}

	if(map.contains("location")){
		QVariant v = map["location"];
		location = new FBLocation();
		location->parse(v.toMap());
	}
}

void FBPlace::parse(QVariantMap map, ObjectType _type)
{

}

QString FBPlace::getName()
{
	return name;
}

QString FBPlace::getCategory()
{
	return category;
}

FBLocation* FBPlace::getLocation()
{
	return location;
}
