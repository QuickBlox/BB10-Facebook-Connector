// Default empty project template
#include "SocialConnector.hpp"

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>
#include <facebook/Facebook.hpp>
#include <facebook/FBUser.h>
#include <facebook/FBPlace.h>
#include <facebook/FBPost.h>
#include <facebook/FBComment.h>
#include <facebook/FacebookObject.h>



#include <ObjectsDataModel.h>

using namespace bb::cascades;

SocialConnector::SocialConnector(bb::cascades::Application *app)
: QObject(app)
{
	qmlRegisterType<Facebook>("com.injoit.sc", 1, 0, "Facebook");
	qmlRegisterType<FBUser>("com.injoit.sc", 1, 0, "FBUser");
	qmlRegisterType<FBPlace>("com.injoit.sc",1,0,"FBPlace");
	qmlRegisterType<FBPost>("com.injoit.sc",1,0,"FBPost");
	qmlRegisterType<FBComment>("com.injoit.sc",1,0,"FBComment");
	qmlRegisterType<FacebookObject>("com.injoit.sc",1,0,"FacebookObject");
	qmlRegisterType<ObjectsDataModel>("com.injoit.sc",1,0,"ObjectsDataModel");

    // create scene document from main.qml asset
    // set parent to created document to ensure it exists for the whole application lifetime
    QmlDocument *qml = QmlDocument::create("asset:///main.qml").parent(this);

    // create root object for the UI
    AbstractPane *root = qml->createRootObject<AbstractPane>();
    // set created root object as a scene
    app->setScene(root);
}

