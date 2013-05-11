/*
 * FBResponseMeta.cpp
 *
 *  Created on: Feb 18, 2013
 *      Author: Vladimir
 */

#include "FBResponseMeta.h"

FBResponseMeta::FBResponseMeta() {

}

FBResponseMeta::~FBResponseMeta() {
}

void FBResponseMeta::parse(QVariantMap obj) {
	setStatus(obj["status"].toInt());
	setMsg(obj["msg"].toString());
}

void FBResponseMeta::setStatus(const int respStatus) {
	status = respStatus;
}

void FBResponseMeta::setMsg(const QString& respMsg) {
	msg = respMsg;
}

int FBResponseMeta::getStatus() {
	return status;
}

QString FBResponseMeta::getMsg() {
	return msg;
}

