/*
 * FBPost.cpp
 *
 *  Created on: Feb 28, 2013
 *      Author: Vladimir
 */

#include "FBPost.h"

FBPost::FBPost() {
	// TODO Auto-generated constructor stub

}

FBPost::~FBPost() {
	// TODO Auto-generated destructor stub
}


void FBPost::parse(QVariantMap _map)
{
	map = _map;

	if(map.contains("id")){
		id = map["id"].toString();
	}

	if(map.contains("comments")){
		QVariant comments = map["comments"];
		if(comments.canConvert(QVariant::Map))
		{
			QVariantMap comments_map = comments.toMap();
			if(comments_map.contains("count"))
			{
				m_comments_count = comments_map["count"].toString();
			}
		}
	}

	if(map.contains("likes")){
		QVariant likes = map["likes"];
		if(likes.canConvert(QVariant::Map))
		{
			QVariantMap likes_map = likes.toMap();
			if(likes_map.contains("count"))
			{
				m_likes_count = likes_map["count"].toString();
			}
		}
	}

	if(map.contains("shares")){
		QVariant shares = map["shares"];
		if(shares.canConvert(QVariant::Map))
		{
			QVariantMap shares_map = shares.toMap();
			if(shares_map.contains("count"))
			{
				m_shares_count = shares_map["count"].toString();
			}
		}
	}

	if(map.contains("message")){
		m_message = map["message"].toString();
	}

	if(map.contains("picture")){
		m_picture = map["picture"].toString();
	}

	if(map.contains("link")){
		m_link = map["link"].toString();
	}

	if(map.contains("name")){
		m_name = map["name"].toString();
	}

	if(map.contains("caption")){
		m_caption = map["caption"].toString();
	}

	if(map.contains("description")){
		m_description = map["description"].toString();
	}

	if(map.contains("source")){
		m_source = map["source"].toString();
	}

	if(map.contains("story")){
		m_story = map["story"].toString();
	}

	if(map.contains("icon")){
		m_icon = map["icon"].toString();
	}

	if(map.contains("attribution")){
		m_attribution = map["attribution"].toString();
	}

	if(map.contains("created_time")){
		m_created_time = map["created_time"].toString();
	}

	if(map.contains("updated_time")){
		m_updated_time = map["updated_time"].toString();
	}

	if(map.contains("type")){
		m_type = map["type"].toString();
	}

	if(map.contains("from")){
		QVariant v = map["from"];
		m_from = new FBProfile();
		m_from->parse(v.toMap());
	}

	if(map.contains("to")){
		QList<QVariant> list = map["to"].toList();
		foreach(const QVariant &b, list) {
			FBProfile *w = new FBProfile();
			w->parse(b.toMap());
			m_to.append(w);
		}
	}
}

void FBPost::parse(QVariantMap, ObjectType)
{

}

QString FBPost::getLikesCount()
{
	return m_likes_count;
}

QString FBPost::getCommentsCount()
{
	return m_comments_count;
}

QString FBPost::getSharesCount()
{
	return m_shares_count;
}

QString FBPost::getMessage()
{
	return m_message;
}

QString FBPost::getPicture()
{
	return m_picture;
}

QString FBPost::getLink()
{
	return m_link;
}

QString FBPost::getName()
{
	return m_name;
}

QString FBPost::getCaption()
{
	return m_caption;
}

QString FBPost::getDescription()
{
	return m_description;
}

QString FBPost::getSource()
{
	return m_source;
}

QString FBPost::getStory()
{
	return m_story;
}

QString FBPost::getIcon()
{
	return m_icon;
}

QString FBPost::getAttribution()
{
	return m_attribution;
}

QString FBPost::getCreatedTime()
{
	return m_created_time;
}

QString FBPost::getUpdatedTime()
{
	return m_updated_time;
}

QString FBPost::getType()
{
	return m_type;
}

FBProfile* FBPost::getFrom()
{
	return m_from;
}

QList<FBProfile*> FBPost::getTo()
{
	return m_to;
}

