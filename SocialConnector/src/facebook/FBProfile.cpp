/*
 * FBProfile.cpp
 *
 *  Created on: Feb 24, 2013
 *      Author: Vladimir
 */

#include "FBProfile.h"

FBProfile::FBProfile() {
	// TODO Auto-generated constructor stub

}

FBProfile::~FBProfile() {
	// TODO Auto-generated destructor stub
}

void FBProfile::parse(QVariantMap _map)
{
	map = _map;
	if(map.contains("id")){
		id = map["id"].toString();
	}

	if(map.contains("name")){
		name = map["name"].toString();
	}
}

void FBProfile::parse(QVariantMap map, ObjectType _type)
{

}

QString FBProfile::getName()
{
	return name;
}


