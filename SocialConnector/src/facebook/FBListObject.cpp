/*
 * FBListObject.cpp
 *
 *  Created on: Feb 25, 2013
 *      Author: Vladimir
 */

#include "FBListObject.h"
#include "FBPlace.h"
#include "FBPost.h"
#include "FBComment.h"

FBListObject::FBListObject() {
	// TODO Auto-generated constructor stub
}

FBListObject::~FBListObject() {
	// TODO Auto-generated destructor stub
}

void FBListObject::parse(QVariantMap map)
{

}

void FBListObject::parse(QVariantMap _map, ObjectType type)
{
	map = _map;
	if(map.contains("data"))
	{
		QVariant list = map["data"];
		if(list.canConvert(QVariant::List))
		{
			foreach(const QVariant &b, list.toList())
			{
				switch(type)
				{
					case PlacesObjs:
					{
						FBPlace *p = new FBPlace();
						p->parse(b.toMap());
						QVariant pVar = QVariant::fromValue(p);
						//model->append(pVar);
						m_objects.append(pVar);
						break;
					}
					case PostsObjs:
					{
						FBPost *p = new FBPost();
						p->parse(b.toMap());
						QVariant pVar = QVariant::fromValue(p);
						m_objects.append(pVar);
						break;
					}
					case ProfilesObjs:
					{
						FBProfile *p = new FBProfile();
						p->parse(b.toMap());
						QVariant pVar = QVariant::fromValue(p);
						m_objects.append(pVar);
						break;
					}
					case CommentsObjs:
					{
						FBComment *p = new FBComment();
						p->parse(b.toMap());
						QVariant pVar = QVariant::fromValue(p);
						m_objects.append(pVar);
						break;
					}
					case Empty:
					default: break;
				}
			}
		}
	}
}

QVariantList  FBListObject::getList()
{
	return m_objects;
}

