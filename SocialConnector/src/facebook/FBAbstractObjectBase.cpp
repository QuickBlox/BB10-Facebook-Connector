/*
 * FBAbstractObjectBase.cpp
 *
 *  Created on: Feb 18, 2013
 *      Author: Vladimir
 */

#include "FBAbstractObjectBase.h"

FBAbstractObjectBase::FBAbstractObjectBase():result(false) {
}

FBAbstractObjectBase::~FBAbstractObjectBase() {
}

QString FBAbstractObjectBase::getId() {
   return id;
}

QVariantMap FBAbstractObjectBase::getMap()
{
	return map;
}

bool FBAbstractObjectBase::getResult()
{
	return result;
}

void FBAbstractObjectBase::setResult(bool value)
{
	result = value;
}

