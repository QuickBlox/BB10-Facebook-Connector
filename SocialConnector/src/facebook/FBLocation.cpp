/*
 * FBLocation.cpp
 *
 *  Created on: Feb 25, 2013
 *      Author: Vladimir
 */

#include "FBLocation.h"

FBLocation::FBLocation() {
	// TODO Auto-generated constructor stub

}

FBLocation::~FBLocation() {
	// TODO Auto-generated destructor stub
}

void FBLocation::parse(QVariantMap _map)
{
	map = _map;
	if(map.contains("id")){
		id = map["id"].toString();
	}

	if(map.contains("street")){
		street = map["street"].toString();
	}

	if(map.contains("city")){
		city = map["city"].toString();
	}

	if(map.contains("state")){
		state = map["state"].toString();
	}

	if(map.contains("country")){
		country = map["country"].toString();
	}

	if(map.contains("zip")){
		zip = map["zip"].toString();
	}

	if(map.contains("latitude")){
		latitude = map["latitude"].toString();
	}

	if(map.contains("longitude")){
		longitude = map["longitude"].toString();
	}
}

void FBLocation::parse(QVariantMap map, ObjectType _type)
{

}

QString FBLocation::getStreet()
{
	return street;
}

QString FBLocation::getCity()
{
	return city;
}

QString FBLocation::getState()
{
	return state;
}

QString FBLocation::getCountry()
{
	return country;
}

QString FBLocation::getZip()
{
	return zip;
}

QString FBLocation::getLatitude()
{
	return latitude;
}

QString FBLocation::getLongitude()
{
	return longitude;
}
