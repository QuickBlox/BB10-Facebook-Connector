/*
 * FBComment.cpp
 *
 *  Created on: Mar 3, 2013
 *      Author: Vladimir
 */

#include "FBComment.h"

FBComment::FBComment(): m_can_remove(false), m_user_likes(false){
	// TODO Auto-generated constructor stub

}

FBComment::~FBComment() {
	// TODO Auto-generated destructor stub
}

void FBComment::parse(QVariantMap _map)
{
	map = _map;

	if(map.contains("id")){
		id = map["id"].toString();
	}

	if(map.contains("created_time")){
		m_created_time = map["created_time"].toString();
	}

	if(map.contains("message")){
		m_message = map["message"].toString();
	}

	if(map.contains("like_count")){
		m_likes_count = map["like_count"].toString();
	}

	if(map.contains("can_remove")){
		m_can_remove = map["can_remove"].toBool();
	}

	if(map.contains("user_likes")){
		m_user_likes = map["can_remove"].toBool();
	}

	if(map.contains("from")){
		QVariant v = map["from"];
		m_from = new FBProfile();
		m_from->parse(v.toMap());
	}
}

void FBComment::parse(QVariantMap, ObjectType)
{

}

QString FBComment::getCreatedTime()
{
	return m_created_time;
}

QString FBComment::getMessage()
{
	return m_message;
}

QString FBComment::getLikesCount()
{
	return m_likes_count;
}

bool FBComment::isCanRemove()
{
	return m_can_remove;
}

bool FBComment::isUserLikes()
{
	return m_user_likes;
}

FBProfile* FBComment::getFrom()
{
	return m_from;
}
