/*
 * Facebook.cpp
 *
 *  Created on: Feb 17, 2013
 *      Author: Vladimir
 */

#include "Facebook.hpp"

#include <bb/data/JsonDataAccess>
#include <bb/system/InvokeRequest>
#include <bb/system/InvokeManager>
#include <bb/system/InvokeTargetReply>

using namespace bb::system;
using namespace bb::data;

Facebook* Facebook::m_instance = NULL;

/* READ ME!!!
 * On developer Facebook site:
 * 1) Register your application on Facebook and receive "Application ID" and "Application Secret" keys.
 * 2) Define callback URL for application: http://quickblox.github.io/BB10-Facebook-Connector/redirect?
 *
 * In this source code:
 * 1) Setup variables APPLICATION_ID and APPLICATION_SECRET in source code (Facebook.cpp), like:
 * 		   const QString Facebook::APPLICATION_ID = QString("475257765857500");
           const QString Facebook::APPLICATION_SECRET = QString("7fd7172563886ea51c730ebd8dfa6260");
   3) Build and run! You can uncomment any function that you need in main.qml file and see how it works!
 */

const QString Facebook::APPLICATION_ID = QString("xxxxxxxxxxxxxx"); // setup here your Application ID key
const QString Facebook::APPLICATION_SECRET = QString("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"); // setup here your Application Secret key

//facebook URLs
const QString Facebook::GRAPH_URL = "https://graph.facebook.com/v2.0/";
const QString Facebook::VIDEO_GRAPH_URL = "https://graph-video.facebook.com/me/videos/";

//facebook post types
const QString Facebook::POSTTYPE_PHOTO = "photo";
const QString Facebook::POSTTYPE_VIDEO = "video";
const QString Facebook::POSTTYPE_STATUS = "status";
const QString Facebook::POSTTYPE_LINK = "link";
const QString Facebook::POSTTYPE_SWF = "swf";

// Public Profile (Default)
const QString Facebook::PUBLIC_PROFILE = "public_profile";
const QString Facebook::FRIENDS = "user_friends";
const QString Facebook::EMAIL = "email";
const QString Facebook::USER_ABOUT_ME = "user_about_me";
const QString Facebook::USER_ACTIVITIES = "user_activities";
const QString Facebook::USER_BIRTHDAY = "user_birthday";
const QString Facebook::USER_EDUCATION_HISTORY = "user_education_history";
const QString Facebook::USER_EVENTS = "user_events";
const QString Facebook::USER_GROUPS = "user_groups";
const QString Facebook::USER_HOMETOWN = "user_hometown";
const QString Facebook::USER_INTERESTS = "user_interests";
const QString Facebook::USER_LIKES = "user_likes";
const QString Facebook::USER_LOCATION = "user_location";
const QString Facebook::USER_PHOTOS = "user_photos";
const QString Facebook::USER_RELATIONSHIPS = "user_relationships";
const QString Facebook::USER_RELATIONSHIP_DETAILS = "user_relationship_details";
const QString Facebook::USER_RELIGION_POLITICS = "user_religion_politics";
const QString Facebook::USER_STATUS = "user_status";
const QString Facebook::USER_VIDEOS = "user_videos";
const QString Facebook::USER_TRIGGED_PLACES = "user_tagged_places";
const QString Facebook::USER_WEBSITE = "user_website";
const QString Facebook::USER_WORK_HISTORY = "user_work_history";

const QString Facebook::READ_FRIENDLISTS = "read_friendlists";
const QString Facebook::READ_INSIGHTS = "read_insights";
const QString Facebook::READ_MAILBOX = "read_mailbox";
const QString Facebook::READ_STREAM = "read_stream";

const QString Facebook::MANAGE_NOTIFICATION = "manage_notifications";
const QString Facebook::PUBLISH_ACTIONS = "publish_actions";
const QString Facebook::RSVP_EVENT = "rsvp_event";
const QString Facebook::MANAGE_PAGES = "manage_pages";
const QString Facebook::READ_PAGE_MAILBOXES = "read_page_mailboxes";


Facebook::Facebook() {
    oauthRequest = new KQOAuth2Request;
    oauthManager = new KQOAuthManager(this);

    //this file should be a file path relative to the assets directory
    oauthManager->setSuccessHtmlFile("loginSuccess.html");
    oauthRequest->setEnableDebugOutput(true);

}

Facebook::~Facebook() {
    delete oauthRequest;
    delete oauthManager;
    delete m_user;
}

Facebook* Facebook::instance() {
	if(!m_instance) {
		m_instance = new Facebook;
	}
	return m_instance;
}

KQOAuthManager* Facebook::getRequestManager() {
	return oauthManager;
}

void Facebook::onAuthorizationReceived(QString token, QString verifier) {
    qDebug() << "User authorization received: " << token;

    if(token == NULL) {
    	emit loginComplete(false);
        return;
    }
    if( oauthManager->lastError() != KQOAuthManager::NoError) {
        emit loginComplete(false);
    }
    oauthSettings.setValue("fb_oauth_token", token);

    emit loginComplete(token.length() > 0);
    qDebug() << "Access tokens now stored. Get current user...";

    disconnect(oauthManager, SIGNAL(authorizationReceived(QString,QString)), this, SLOT(onAuthorizationReceived(QString,QString)));

    getCurrentUser();
}

void Facebook::onTemporaryTokenReceived(QString token, QString tokenSecret)
{
    qDebug() << "Temporary token received: " << token << tokenSecret;

    QUrl userAuthURL("www.facebook.com/dialog/oauth?");

    if( oauthManager->lastError() == KQOAuthManager::NoError) {
        qDebug() << "Asking for user's permission to access protected resources. Opening URL: " << userAuthURL;
        oauthManager->getUserAuthorization(userAuthURL);
    }

}

void Facebook::onAccessTokenReceived(QString token, QString tokenSecret) {
    qDebug() << "Access token received: " << token << tokenSecret;

    disconnect(oauthManager, SIGNAL(accessTokenReceived(QString,QString)), this, SLOT(onAccessTokenReceived(QString,QString)));

    if(token == NULL) {
    	emit loginComplete(false);
    	return;
    }
    oauthSettings.setValue("fb_oauth_token", token);
    oauthSettings.setValue("fb_oauth_token_secret", tokenSecret);

    emit loginComplete(token.length() > 0);
    qDebug() << "Access tokens now stored.";
}

void Facebook::onAuthorizedRequestDone() {
    qDebug() << "Request sent to Facebook!";
}

void Facebook::onRequestReady(QByteArray response) {
    qDebug() << "Response from the service: " << response;
    switch(oauthManager->lastError()){
    case KQOAuthManager::NoError:
    	break;
	case KQOAuthManager::NetworkError:
    	qDebug() << "NetworkError";
    	break;
    case KQOAuthManager::RequestEndpointError:
		qDebug() << "RequestEndpointError";
		break;
    case KQOAuthManager::RequestValidationError:
		qDebug() << "RequestValidationError";
		break;
    case KQOAuthManager::RequestUnauthorized:
		qDebug() << "RequestUnauthorized";
		break;
    case KQOAuthManager::RequestError:
		qDebug() << "RequestError";
		break;
    case KQOAuthManager::ManagerError:
		qDebug() << "ManagerError";
		break;
    default:
    	qDebug() << "There was an error";
    	break;
    }
    disconnect(oauthManager, SIGNAL(requestReady(QByteArray)), this, SLOT(onRequestReady(QByteArray)));
}


void Facebook::login()
{
	if(!hasToken())
	{
		connect(oauthManager, SIGNAL(authorizationReceived(QString,QString)), this, SLOT( onAuthorizationReceived(QString, QString)));
		KQOAuthParameters params;
		params.insert("scope", getAllPermissions());

		oauthManager->setHandleUserAuthorization(true);
		oauthManager->getOauth2UserAuthorization(QUrl("http://m.facebook.com/v2.0/dialog/oauth"), APPLICATION_ID, params);
	}
	else
	{
		if(currentUser() == NULL)
		{
			getCurrentUser();
		}
	}
}

bool Facebook::hasToken() {
	bool res = true;
	QString t = oauthSettings.value("fb_oauth_token").toString();
	if(oauthSettings.value("fb_oauth_token").toString().isEmpty() == true)
	{
		res = false;
	}
	return res;
}

void Facebook::addAuth(KQOAuthRequest* req) {
	req->setToken(oauthSettings.value("fb_oauth_token").toString());
}

void Facebook::logout() {
	if(hasToken())
	{
		//this code logout facebook in browser
		InvokeManager invokeManager;
		InvokeRequest request;

		request.setTarget("sys.browser");
		request.setAction("bb.action.OPEN");
		request.setMimeType("text/html");
		request.setUri(QUrl("https://www.facebook.com/logout.php?next=http://facebook.com/&access_token=" + oauthSettings.value("fb_oauth_token").toString()));

		InvokeTargetReply *reply = invokeManager.invoke(request);
		//=================================================================

		oauthSettings.setValue("fb_oauth_token","");
		emit logoutComplete(false);
	}
}

bool Facebook::isAuthorized() {
	return hasToken();
}


QString Facebook::getCustomPermissions()
{
	QString out = USER_ABOUT_ME; //define here all permissions that you need
	return out;
}

QString Facebook::getAllPermissions()
{
	QString out = PUBLIC_PROFILE + "," + FRIENDS + "," + EMAIL + "," + USER_ABOUT_ME + "," + USER_ACTIVITIES + "," + USER_BIRTHDAY + "," + USER_EDUCATION_HISTORY + "," + USER_EVENTS + "," + USER_GROUPS +
			"," + USER_HOMETOWN + "," + USER_INTERESTS + "," + USER_LIKES + "," + USER_LOCATION + "," + USER_PHOTOS + "," + USER_RELATIONSHIPS + "," + USER_RELATIONSHIP_DETAILS + "," + USER_RELIGION_POLITICS +
			"," + USER_STATUS + "," + USER_VIDEOS + "," + USER_TRIGGED_PLACES + "," + USER_WEBSITE + "," + USER_WORK_HISTORY + "," + READ_FRIENDLISTS + "," + READ_INSIGHTS + "," + READ_MAILBOX + "," + READ_STREAM +
			"," + MANAGE_NOTIFICATION + "," + PUBLISH_ACTIONS + "," + RSVP_EVENT + "," + MANAGE_PAGES + "," + READ_PAGE_MAILBOXES;

	qDebug()<<out;
	return out;
}

void Facebook::onError(FBResponseMeta *respMeta)
{
	if (respMeta)
		Q_UNUSED(respMeta);

	disconnectFromAll();
	qDebug() << "Error was handled";

	emit error(respMeta);
}

void Facebook::disconnectFromAll()
{

}

void Facebook::getCurrentUser()
{
	if(hasToken())
	{
		qDebug() << "hasToken! ";
		KQOAuth2Request *req = new KQOAuth2Request(this);
		req->initRequest(KQOAuth2Request::AuthorizedRequest, QUrl(GRAPH_URL + "me"));
		addAuth(req);
		req->setHttpMethod(KQOAuthRequest::GET);

		KQOAuthParameters params;
		params.insert("format", "JSON");
		req->setAdditionalParameters(params);


		FBRequestEnvelope *env = new FBRequestEnvelope(FBApiResponseObjectFactory::UserObj, req);
		connect(env, SIGNAL(requestComplete(FBAbstractObjectBase*)), this, SLOT(onCurrentUserReceived(FBAbstractObjectBase*)));
		connect(env, SIGNAL(requestError(FBResponseMeta*)), this, SLOT(onError(FBResponseMeta*)));
		env->makeRequest();
	}
}

void Facebook::onCurrentUserReceived(FBAbstractObjectBase* _user)
{
	disconnect(sender(), SIGNAL(requestError(FBResponseMeta*)), this, SLOT(onError(FBResponseMeta*)));
	disconnect(sender(), SIGNAL(requestComplete(FBAbstractObjectBase*)), this, SLOT(onCurrentUserReceived(FBAbstractObjectBase*)));

	m_user = qobject_cast<FBUser*>(_user);

	qDebug() << "onCurrentUserReceived";
	Q_UNUSED(_user);
	emit getCurrentUserComplete(m_user);
}

FBUser* Facebook::currentUser()
{
	return m_user;
}

void Facebook::getPlaces(QString lat, QString lon, QString distance)
{
	if(hasToken() && !lat.isEmpty() && !lon.isEmpty() && !distance.isEmpty())
	{
		getPlaces(lat, lon, distance, "0", "25");
	}
}

void Facebook::getPlaces(QString lat, QString lon, QString distance, QString offset, QString limit)
{
	if(hasToken() && !lat.isEmpty() && !lon.isEmpty() && !distance.isEmpty() && !offset.isEmpty() && !limit.isEmpty())
	{
		KQOAuth2Request *req = new KQOAuth2Request(this);
		req->initRequest(KQOAuth2Request::AuthorizedRequest, QUrl(GRAPH_URL + "search?"));
		addAuth(req);
		req->setHttpMethod(KQOAuthRequest::GET);

		KQOAuthParameters params;
		params.insert("type", "place");
		params.insert("center", lat + "," + lon );
		params.insert("distance", distance);
		params.insert("offset", offset);
		params.insert("limit", limit);
		params.insert("format", "JSON");
		req->setAdditionalParameters(params);


		FBRequestEnvelope *env = new FBRequestEnvelope(FBApiResponseObjectFactory::ListObj, FBAbstractObjectBase::PlacesObjs, req);
		connect(env, SIGNAL(requestComplete(FBAbstractObjectBase*)), this, SLOT(onPlacesReceived(FBAbstractObjectBase*)));
		connect(env, SIGNAL(requestError(FBResponseMeta*)), this, SLOT(onError(FBResponseMeta*)));
		env->makeRequest();
	}
}

void Facebook::onPlacesReceived(FBAbstractObjectBase* _list)
{
	disconnect(sender(), SIGNAL(requestError(FBResponseMeta*)), this, SLOT(onError(FBResponseMeta*)));
	disconnect(sender(), SIGNAL(requestComplete(FBAbstractObjectBase*)), this, SLOT(onPlacesReceived(FBAbstractObjectBase*)));

	FBListObject* list = qobject_cast<FBListObject*>(_list);

	Q_UNUSED(_list);

	QVariantList l = list->getList();
	foreach(const QVariant &item, l)
	{
		FBPlace* p = qvariant_cast<FBPlace*>(item);
		qDebug() << p->getName();
	}

	emit getPlacesComplete(l);
}

void Facebook::getHome(QString user_id)
{
	if(hasToken() && !user_id.isEmpty())
	{
		getHome(user_id, "0", "25");
	}
}

void Facebook::getHome(QString user_id, QString offset, QString limit)
{
	if(hasToken() && !user_id.isEmpty() && !offset.isEmpty() && !limit.isEmpty())
	{
		KQOAuth2Request *req = new KQOAuth2Request(this);
		req->initRequest(KQOAuth2Request::AuthorizedRequest, QUrl(GRAPH_URL + user_id + "/home?"));
		addAuth(req);
		req->setHttpMethod(KQOAuthRequest::GET);

		KQOAuthParameters params;
		params.insert("format", "JSON");
		params.insert("offset", offset);
		params.insert("limit", limit);
		req->setAdditionalParameters(params);

		FBRequestEnvelope *env = new FBRequestEnvelope(user_id, FBApiResponseObjectFactory::ListObj, FBAbstractObjectBase::PostsObjs, req);
		connect(env, SIGNAL(requestComplete(QString, FBAbstractObjectBase*)), this, SLOT(onHomeReceived(QString, FBAbstractObjectBase*)));
		connect(env, SIGNAL(requestError(FBResponseMeta*)), this, SLOT(onError(FBResponseMeta*)));
		env->makeRequest();
	}
}

void Facebook::onHomeReceived(QString _id, FBAbstractObjectBase* _list)
{
	disconnect(sender(), SIGNAL(requestComplete(QString, FBAbstractObjectBase*)), this, SLOT(onHomeReceived(QString, FBAbstractObjectBase*)));
	disconnect(sender(), SIGNAL(requestError(FBResponseMeta*)), this, SLOT(onError(FBResponseMeta*)));

	FBListObject* list = qobject_cast<FBListObject*>(_list);

	QVariantList l = list->getList();
	foreach(const QVariant &item, l)
	{
		FBPost* p = qvariant_cast<FBPost*>(item);
		if(!p->getMessage().isEmpty())
		{
			qDebug() << p->getMessage();
		}
	}

	emit getHomeComplete(_id, l);

	Q_UNUSED(_list);
	Q_UNUSED(_id);
}

void Facebook::getPosts(QString user_id)
{
	if(hasToken() && !user_id.isEmpty())
	{
		getPosts(user_id, "0", "25");
	}
}

void Facebook::getPosts(QString user_id, QString offset, QString limit)
{
	if(hasToken() && !user_id.isEmpty() && !limit.isEmpty() && !offset.isEmpty())
	{
		KQOAuth2Request *req = new KQOAuth2Request(this);
		req->initRequest(KQOAuth2Request::AuthorizedRequest, QUrl(GRAPH_URL + user_id + "/posts?"));
		addAuth(req);
		req->setHttpMethod(KQOAuthRequest::GET);

		KQOAuthParameters params;
		params.insert("format", "JSON");
		params.insert("limit", limit);
		params.insert("offset", offset);
		req->setAdditionalParameters(params);

		FBRequestEnvelope *env = new FBRequestEnvelope(user_id, FBApiResponseObjectFactory::ListObj, FBAbstractObjectBase::PostsObjs, req);
		connect(env, SIGNAL(requestComplete(QString, FBAbstractObjectBase*)), this, SLOT(onPostsReceived(QString, FBAbstractObjectBase*)));
		connect(env, SIGNAL(requestError(FBResponseMeta*)), this, SLOT(onError(FBResponseMeta*)));
		env->makeRequest();
	}
}

void Facebook::onPostsReceived(QString _id, FBAbstractObjectBase* _list)
{
	disconnect(sender(), SIGNAL(requestComplete(QString, FBAbstractObjectBase*)), this, SLOT(onPostsReceived(QString, FBAbstractObjectBase*)));
	disconnect(sender(), SIGNAL(requestError(FBResponseMeta*)), this, SLOT(onError(FBResponseMeta*)));

	FBListObject* list = qobject_cast<FBListObject*>(_list);

	QVariantList l = list->getList();
	foreach(const QVariant &item, l)
	{
		FBPost* p = qvariant_cast<FBPost*>(item);
		if(!p->getMessage().isEmpty())
		{
			qDebug() << p->getMessage();
		}
	}

	emit getPostsComplete(_id, l);

	Q_UNUSED(_list);
	Q_UNUSED(_id);
}

void Facebook::getFeed(QString user_id)
{
	if(hasToken() && !user_id.isEmpty())
	{
		getFeed(user_id, "0", "25");
	}
}

void Facebook::getFeed(QString user_id, QString offset, QString limit)
{
	if(hasToken() && !user_id.isEmpty() && !limit.isEmpty() && !offset.isEmpty())
	{
		KQOAuth2Request *req = new KQOAuth2Request(this);
		req->initRequest(KQOAuth2Request::AuthorizedRequest, QUrl(GRAPH_URL + user_id + "/feed?"));
		addAuth(req);
		req->setHttpMethod(KQOAuthRequest::GET);

		KQOAuthParameters params;
		params.insert("format", "JSON");
		params.insert("limit", limit);
		params.insert("offset", offset);
		req->setAdditionalParameters(params);

		FBRequestEnvelope *env = new FBRequestEnvelope(user_id, FBApiResponseObjectFactory::ListObj, FBAbstractObjectBase::PostsObjs, req);
		connect(env, SIGNAL(requestComplete(QString, FBAbstractObjectBase*)), this, SLOT(onFeedReceived(QString, FBAbstractObjectBase*)));
		connect(env, SIGNAL(requestError(FBResponseMeta*)), this, SLOT(onError(FBResponseMeta*)));
		env->makeRequest();
	}
}

void Facebook::onFeedReceived(QString _id, FBAbstractObjectBase* _list)
{
	disconnect(sender(), SIGNAL(requestComplete(QString, FBAbstractObjectBase*)), this, SLOT(onFeedReceived(QString, FBAbstractObjectBase*)));
	disconnect(sender(), SIGNAL(requestError(FBResponseMeta*)), this, SLOT(onError(FBResponseMeta*)));

	FBListObject* list = qobject_cast<FBListObject*>(_list);

	QVariantList l = list->getList();
	foreach(const QVariant &item, l)
	{
		FBPost* p = qvariant_cast<FBPost*>(item);
		if(!p->getMessage().isEmpty())
		{
			qDebug() << p->getMessage();
		}
	}

	emit getFeedComplete(_id, l);

	Q_UNUSED(_list);
	Q_UNUSED(_id);
}

void Facebook::publishLink(QString url, QString message)
{
	if(hasToken() && !m_user->getId().isEmpty() && !url.isEmpty())
	{
		KQOAuth2Request *req = new KQOAuth2Request(this);
		req->initRequest(KQOAuth2Request::AuthorizedRequest, QUrl(GRAPH_URL + m_user->getId() + "/feed"));
		addAuth(req);
		req->setHttpMethod(KQOAuthRequest::POST);

		KQOAuthParameters params;
		params.insert("format", "JSON");
		params.insert("link", url);
		params.insert("message", message);
		params.insert("access_token", oauthSettings.value("fb_oauth_token").toString());
		req->setAdditionalParameters(params);


		FBRequestEnvelope *env = new FBRequestEnvelope(FBApiResponseObjectFactory::FacebookObj, req);
		connect(env, SIGNAL(requestComplete(FBAbstractObjectBase*)), this, SLOT(onPublishLinkReceived(FBAbstractObjectBase*)));
		connect(env, SIGNAL(requestError(FBResponseMeta*)), this, SLOT(onError(FBResponseMeta*)));
		env->makeRequest();
	}
}

void Facebook::onPublishLinkReceived(FBAbstractObjectBase* _obj)
{
	disconnect(sender(), SIGNAL(requestComplete(FBAbstractObjectBase*)), this, SLOT(onPublishLinkReceived(FBAbstractObjectBase*)));
	disconnect(sender(), SIGNAL(requestError(FBResponseMeta*)), this, SLOT(onError(FBResponseMeta*)));

	FacebookObject* fo = qobject_cast<FacebookObject*>(_obj);
	emit publishLinkComplete(fo);

	qDebug() << "published link id: " << fo->getId();
	Q_UNUSED(_obj);
}

void Facebook::publishNote(QString subject, QString message)
{
	if(hasToken() && !m_user->getId().isEmpty())
	{
		KQOAuth2Request *req = new KQOAuth2Request(this);
		req->initRequest(KQOAuth2Request::AuthorizedRequest, QUrl(GRAPH_URL + m_user->getId() + "/notes?"));
		addAuth(req);
		req->setHttpMethod(KQOAuthRequest::POST);

		KQOAuthParameters params;
		params.insert("format", "JSON");
		params.insert("subject", subject);
		params.insert("message", message);
		params.insert("access_token", oauthSettings.value("fb_oauth_token").toString());
		req->setAdditionalParameters(params);


		FBRequestEnvelope *env = new FBRequestEnvelope(FBApiResponseObjectFactory::FacebookObj, req);
		connect(env, SIGNAL(requestComplete(FBAbstractObjectBase*)), this, SLOT(onPublishNoteReceived(FBAbstractObjectBase*)));
		connect(env, SIGNAL(requestError(FBResponseMeta*)), this, SLOT(onError(FBResponseMeta*)));
		env->makeRequest();
	}
}

void Facebook::onPublishNoteReceived(FBAbstractObjectBase* _obj)
{
	disconnect(sender(), SIGNAL(requestComplete(FBAbstractObjectBase*)), this, SLOT(onPublishNoteReceived(FBAbstractObjectBase*)));
	disconnect(sender(), SIGNAL(requestError(FBResponseMeta*)), this, SLOT(onError(FBResponseMeta*)));

	FacebookObject* fo = qobject_cast<FacebookObject*>(_obj);
	emit publishNoteComplete(fo);

	qDebug() << "published note id: " << fo->getId();
	Q_UNUSED(_obj);
}

void Facebook::publishStatus(QString message)
{
	if(hasToken() && !m_user->getId().isEmpty())
	{
		KQOAuth2Request *req = new KQOAuth2Request(this);
		req->initRequest(KQOAuth2Request::AuthorizedRequest, QUrl(GRAPH_URL + m_user->getId() + "/feed?"));
		addAuth(req);
		req->setHttpMethod(KQOAuthRequest::POST);

		KQOAuthParameters params;
		params.insert("message", message);
		params.insert("access_token", oauthSettings.value("fb_oauth_token").toString());
		req->setAdditionalParameters(params);


		FBRequestEnvelope *env = new FBRequestEnvelope(FBApiResponseObjectFactory::FacebookObj, req);
		connect(env, SIGNAL(requestComplete(FBAbstractObjectBase*)), this, SLOT(onPublishStatusReceived(FBAbstractObjectBase*)));
		connect(env, SIGNAL(requestError(FBResponseMeta*)), this, SLOT(onError(FBResponseMeta*)));
		env->makeRequest();
	}
}

void Facebook::onPublishStatusReceived(FBAbstractObjectBase* _obj)
{
	disconnect(sender(), SIGNAL(requestComplete(FBAbstractObjectBase*)), this, SLOT(onPublishStatusReceived(FBAbstractObjectBase*)));
	disconnect(sender(), SIGNAL(requestError(FBResponseMeta*)), this, SLOT(onError(FBResponseMeta*)));

	FacebookObject* fo = qobject_cast<FacebookObject*>(_obj);
	emit publishStatusComplete(fo);

	qDebug() << "published status id: " << fo->getId();
	Q_UNUSED(_obj);
}

void Facebook::publishCheckin(QString place_id, QString latitude, QString longitude, QVariantList tagged_friends, QString message, QString link, QString picture)
{
	if(hasToken() && !m_user->getId().isEmpty() && !place_id.isEmpty() && !latitude.isEmpty() && !longitude.isEmpty())
	{
		KQOAuth2Request *req = new KQOAuth2Request(this);
		req->initRequest(KQOAuth2Request::AuthorizedRequest, QUrl(GRAPH_URL + m_user->getId() + "/checkins?"));
		addAuth(req);
		req->setHttpMethod(KQOAuthRequest::POST);

		KQOAuthParameters params;
		params.insert("access_token", oauthSettings.value("fb_oauth_token").toString());
		params.insert("place", place_id);
		params.insert("coordinates", "{\"latitude\":\"" + latitude + "\", \"longitude\":\"" + longitude + "\"}");

		if(!message.isEmpty())
		{
			params.insert("message", message);
		}

		if(!link.isEmpty())
		{
			params.insert("link", link);
		}

		if(!picture.isEmpty())
		{
			params.insert("picture", link);
		}

		qDebug() << "List: " << tagged_friends;
		if(!tagged_friends.isEmpty())
		{
			QString friends;
			foreach(const QVariant &item, tagged_friends)
			{
				FBProfile* p = qvariant_cast<FBProfile*>(item);
				if(!p->getId().isEmpty())
				{
					friends += p->getId();
					friends += ",";
				}
			}
			if(!friends.isEmpty())
			{
			    QString out = friends.left(friends.length()-1);
				qDebug() << "Tagged friends: " << out;
				params.insert("tags", out);//Comma separated list of USER_IDs
			}
		}

		req->setAdditionalParameters(params);


		FBRequestEnvelope *env = new FBRequestEnvelope(FBApiResponseObjectFactory::FacebookObj, req);
		connect(env, SIGNAL(requestComplete(FBAbstractObjectBase*)), this, SLOT(onPublishCheckinReceived(FBAbstractObjectBase*)));
		connect(env, SIGNAL(requestError(FBResponseMeta*)), this, SLOT(onError(FBResponseMeta*)));
		env->makeRequest();
	}
}

void Facebook::onPublishCheckinReceived(FBAbstractObjectBase* _obj)
{
	disconnect(sender(), SIGNAL(requestComplete(FBAbstractObjectBase*)), this, SLOT(onPublishCheckinReceived(FBAbstractObjectBase*)));
	disconnect(sender(), SIGNAL(requestError(FBResponseMeta*)), this, SLOT(onError(FBResponseMeta*)));

	FacebookObject* fo = qobject_cast<FacebookObject*>(_obj);
	emit publishCheckinComplete(fo);

	qDebug() << "published checkin id: " << fo->getId();
	Q_UNUSED(_obj);
}

void Facebook::getFriends(QString user_id)
{
	if(hasToken() && !user_id.isEmpty())
	{
		getFriends(user_id, "0", "25");
	}
}

void Facebook::getFriends(QString user_id, QString offset, QString limit)
{
	if(hasToken() && !user_id.isEmpty()  && !offset.isEmpty()  && !limit.isEmpty())
	{
		KQOAuth2Request *req = new KQOAuth2Request(this);
		req->initRequest(KQOAuth2Request::AuthorizedRequest, QUrl(GRAPH_URL + user_id + "/friends"));
		addAuth(req);
		req->setHttpMethod(KQOAuthRequest::GET);

		KQOAuthParameters params;
		params.insert("format", "JSON");
		params.insert("offset", offset);
		params.insert("limit", limit);
		req->setAdditionalParameters(params);

		FBRequestEnvelope *env = new FBRequestEnvelope(user_id, FBApiResponseObjectFactory::ListObj, FBAbstractObjectBase::ProfilesObjs, req);
		connect(env, SIGNAL(requestComplete(QString, FBAbstractObjectBase*)), this, SLOT(onFriendsReceived(QString, FBAbstractObjectBase*)));
		connect(env, SIGNAL(requestError(FBResponseMeta*)), this, SLOT(onError(FBResponseMeta*)));
		env->makeRequest();
	}
}

void Facebook::onFriendsReceived(QString _id, FBAbstractObjectBase* _list)
{
	disconnect(sender(), SIGNAL(requestComplete(QString, FBAbstractObjectBase*)), this, SLOT(onFriendsReceived(QString, FBAbstractObjectBase*)));
	disconnect(sender(), SIGNAL(requestError(FBResponseMeta*)), this, SLOT(onError(FBResponseMeta*)));

	FBListObject* list = qobject_cast<FBListObject*>(_list);

	QVariantList l = list->getList();
	foreach(const QVariant &item, l)
	{
		FBProfile* p = qvariant_cast<FBProfile*>(item);
		if(!p->getName().isEmpty())
		{
			qDebug() << p->getName();
		}
	}

	emit getFriendsComplete(_id, l);

	Q_UNUSED(_list);
	Q_UNUSED(_id);
}

void Facebook::publishPhoto(QString filepath, QString message, QString place_id, QString no_story)
{
	if(hasToken() && !m_user->getId().isEmpty() && !filepath.isEmpty())
	{
		if(QFile::exists(filepath))
		{
			KQOAuth2Request *req = new KQOAuth2Request(this);
			req->initRequest(KQOAuth2Request::AuthorizedRequest, QUrl(GRAPH_URL + m_user->getId() + "/photos"));
			addAuth(req);
			req->setHttpMethod(KQOAuthRequest::POST);

			QString boundary = "--" + QString::number(qrand()*(90000000000)/(RAND_MAX+1)+10000000000, 16);
			req->setContentType("multipart/form-data; boundary=" + boundary);


			QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
			multiPart->setBoundary(boundary.toAscii());

			QHttpPart textTokenPart;
			textTokenPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"access_token\""));
			textTokenPart.setBody(oauthSettings.value("fb_oauth_token").toByteArray());

			multiPart->append(textTokenPart);

			QHttpPart imagePart;
			QFile *file = new QFile(filepath);
			file->open(QIODevice::ReadOnly);
			QFileInfo fi(file->fileName());

			imagePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/" + fi.suffix()));
			imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"photo\"; filename=\"" + file->fileName() + "\""));
			imagePart.setBodyDevice(file);
			file->setParent(multiPart); // we cannot delete the file now, so delete it with the multiPart

			multiPart->append(imagePart);

			if(!message.isEmpty())
			{
				QHttpPart textPart;
				textPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"message\""));
				textPart.setBody(message.toAscii ());

				multiPart->append(textPart);
			}

			if(!place_id.isEmpty())
			{
				QHttpPart textPart;
				textPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"place\""));
				textPart.setBody(place_id.toAscii ());

				multiPart->append(textPart);
			}

			if(!no_story.isEmpty())
			{
				QHttpPart textPart;
				textPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"no_story\""));
				textPart.setBody(no_story.toAscii ());

				multiPart->append(textPart);
			}

			req->setMultiPartData(multiPart);

			FBRequestEnvelope *env = new FBRequestEnvelope(FBApiResponseObjectFactory::FacebookObj, req);
			connect(env, SIGNAL(requestComplete(FBAbstractObjectBase*)), this, SLOT(onPublishPhotoReceived(FBAbstractObjectBase*)));
			connect(env, SIGNAL(requestError(FBResponseMeta*)), this, SLOT(onError(FBResponseMeta*)));
			env->makeRequest();
		}
	}
}

void Facebook::onPublishPhotoReceived(FBAbstractObjectBase* _obj)
{
	disconnect(sender(), SIGNAL(requestComplete(FBAbstractObjectBase*)), this, SLOT(onPublishPhotoReceived(FBAbstractObjectBase*)));
	disconnect(sender(), SIGNAL(requestError(FBResponseMeta*)), this, SLOT(onError(FBResponseMeta*)));

	FacebookObject* fo = qobject_cast<FacebookObject*>(_obj);
	emit publishPhotoComplete(fo);

	qDebug() << "published photo id: " << fo->getId();
	Q_UNUSED(_obj);
}

void Facebook::publishVideo(QString filepath, QString title, QString description)
{
	if(hasToken() && !m_user->getId().isEmpty() && !filepath.isEmpty())
	{
		if(QFile::exists(filepath))
		{
			KQOAuth2Request *req = new KQOAuth2Request(this);
			req->initRequest(KQOAuth2Request::AuthorizedRequest, QUrl("https://graph.facebook.com/" + m_user->getId() + "/videos"));
			addAuth(req);
			req->setHttpMethod(KQOAuthRequest::POST);

			QString boundary = "--" + QString::number(qrand()*(90000000000)/(RAND_MAX+1)+10000000000, 16);
			req->setContentType("multipart/form-data; boundary=" + boundary);


			QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
			multiPart->setBoundary(boundary.toAscii());

			QHttpPart textTokenPart;
			textTokenPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"access_token\""));
			textTokenPart.setBody(oauthSettings.value("fb_oauth_token").toByteArray());

			multiPart->append(textTokenPart);

			QHttpPart imagePart;
			QFile *file = new QFile(filepath);
			file->open(QIODevice::ReadOnly);
			QFileInfo fi(file->fileName());

			imagePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("video/" + fi.suffix()));
			imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"video\"; filename=\"" + file->fileName() + "\""));
			imagePart.setBodyDevice(file);
			file->setParent(multiPart); // we cannot delete the file now, so delete it with the multiPart

			multiPart->append(imagePart);

			if(!title.isEmpty())
			{
				QHttpPart textPart;
				textPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"title\""));
				textPart.setBody(title.toAscii ());

				multiPart->append(textPart);
			}

			if(!description.isEmpty())
			{
				QHttpPart textPart;
				textPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"description\""));
				textPart.setBody(description.toAscii ());

				multiPart->append(textPart);
			}

			req->setMultiPartData(multiPart);

			FBRequestEnvelope *env = new FBRequestEnvelope(FBApiResponseObjectFactory::FacebookObj, req);
			connect(env, SIGNAL(requestComplete(FBAbstractObjectBase*)), this, SLOT(onPublishVideoReceived(FBAbstractObjectBase*)));
			connect(env, SIGNAL(requestError(FBResponseMeta*)), this, SLOT(onError(FBResponseMeta*)));
			env->makeRequest();
	    }
	}
}

void Facebook::onPublishVideoReceived(FBAbstractObjectBase* _obj)
{
	disconnect(sender(), SIGNAL(requestComplete(FBAbstractObjectBase*)), this, SLOT(onPublishVideoReceived(FBAbstractObjectBase*)));
	disconnect(sender(), SIGNAL(requestError(FBResponseMeta*)), this, SLOT(onError(FBResponseMeta*)));

	FacebookObject* fo = qobject_cast<FacebookObject*>(_obj);
	emit publishVideoComplete(fo);

	qDebug() << "published video id: " << fo->getId();
	Q_UNUSED(_obj);
}

void Facebook::like(QString post_id)
{
	if(hasToken() && !m_user->getId().isEmpty() && !post_id.isEmpty())
	{
		KQOAuth2Request *req = new KQOAuth2Request(this);
		req->initRequest(KQOAuth2Request::AuthorizedRequest, QUrl(GRAPH_URL + post_id + "/likes"));
		addAuth(req);
		req->setHttpMethod(KQOAuthRequest::POST);

		KQOAuthParameters params;
		params.insert("format", "JSON");
		params.insert("access_token", oauthSettings.value("fb_oauth_token").toString());
		req->setAdditionalParameters(params);


		FBRequestEnvelope *env = new FBRequestEnvelope(FBApiResponseObjectFactory::FacebookObj, req);
		connect(env, SIGNAL(requestComplete(FBAbstractObjectBase*)), this, SLOT(onLikeReceived(FBAbstractObjectBase*)));
		connect(env, SIGNAL(requestError(FBResponseMeta*)), this, SLOT(onError(FBResponseMeta*)));
		env->makeRequest();
	}
}

void Facebook::onLikeReceived(FBAbstractObjectBase* _obj)
{
	disconnect(sender(), SIGNAL(requestComplete(FBAbstractObjectBase*)), this, SLOT(onLikeReceived(FBAbstractObjectBase*)));
	disconnect(sender(), SIGNAL(requestError(FBResponseMeta*)), this, SLOT(onError(FBResponseMeta*)));

	FacebookObject* fo = qobject_cast<FacebookObject*>(_obj);
	emit likeComplete(true);

	qDebug() << "like result: " << fo->getResult();
	Q_UNUSED(_obj);
}

void Facebook::unlike(QString post_id)
{
	if(hasToken() && !m_user->getId().isEmpty())
	{
		KQOAuth2Request *req = new KQOAuth2Request(this);
		req->initRequest(KQOAuth2Request::AuthorizedRequest, QUrl(GRAPH_URL + post_id + "/likes"));
		addAuth(req);
		req->setHttpMethod(KQOAuthRequest::POST);

		KQOAuthParameters params;
		params.insert("format", "JSON");
		params.insert("method", "delete");
		params.insert("access_token", oauthSettings.value("fb_oauth_token").toString());
		req->setAdditionalParameters(params);

		FBRequestEnvelope *env = new FBRequestEnvelope(FBApiResponseObjectFactory::FacebookObj, req);
		connect(env, SIGNAL(requestComplete(FBAbstractObjectBase*)), this, SLOT(onUnlikeReceived(FBAbstractObjectBase*)));
		connect(env, SIGNAL(requestError(FBResponseMeta*)), this, SLOT(onError(FBResponseMeta*)));
		env->makeRequest();
	}
}

void Facebook::onUnlikeReceived(FBAbstractObjectBase* _obj)
{
	disconnect(sender(), SIGNAL(requestComplete(FBAbstractObjectBase*)), this, SLOT(onUnlikeReceived(FBAbstractObjectBase*)));
	disconnect(sender(), SIGNAL(requestError(FBResponseMeta*)), this, SLOT(onError(FBResponseMeta*)));

	FacebookObject* fo = qobject_cast<FacebookObject*>(_obj);
	emit unlikeComplete(true);

	qDebug() << "unlike result: " << fo->getResult();
	Q_UNUSED(_obj);
}

void Facebook::getComments(QString post_id)
{
	if(hasToken() /*&& !m_user->getId().isEmpty()*/ && !post_id.isEmpty())
	{
		getComments(post_id, "0", "25");
	}
}

void Facebook::getComments(QString post_id, QString offset, QString limit)
{
	if(hasToken() /*&& !m_user->getId().isEmpty()*/ && !post_id.isEmpty() && !offset.isEmpty() && !limit.isEmpty())
	{
		KQOAuth2Request *req = new KQOAuth2Request(this);
		req->initRequest(KQOAuth2Request::AuthorizedRequest, QUrl(GRAPH_URL + post_id + "/comments?"));
		addAuth(req);
		req->setHttpMethod(KQOAuthRequest::GET);

		KQOAuthParameters params;
		params.insert("format", "JSON");
		params.insert("limit", limit);
		params.insert("offset", offset);
		req->setAdditionalParameters(params);

		FBRequestEnvelope *env = new FBRequestEnvelope(post_id, FBApiResponseObjectFactory::ListObj, FBAbstractObjectBase::CommentsObjs, req);
		connect(env, SIGNAL(requestComplete(QString, FBAbstractObjectBase*)), this, SLOT(onCommentsReceived(QString, FBAbstractObjectBase*)));
		connect(env, SIGNAL(requestError(FBResponseMeta*)), this, SLOT(onError(FBResponseMeta*)));
		env->makeRequest();
	}
}

void Facebook::onCommentsReceived(QString _id, FBAbstractObjectBase* _list)
{
	disconnect(sender(), SIGNAL(requestComplete(QString, FBAbstractObjectBase*)), this, SLOT(onCommentsReceived(QString, FBAbstractObjectBase*)));
	disconnect(sender(), SIGNAL(requestError(FBResponseMeta*)), this, SLOT(onError(FBResponseMeta*)));

	FBListObject* list = qobject_cast<FBListObject*>(_list);

	QVariantList l = list->getList();
	foreach(const QVariant &item, l)
	{
		FBComment* p = qvariant_cast<FBComment*>(item);
		if(!p->getMessage().isEmpty())
		{
			qDebug() << p->getMessage();
		}
	}

	emit getCommentsComplete(_id, l);

	Q_UNUSED(_list);
	Q_UNUSED(_id);
}

void Facebook::getLikedUsers(QString post_id)
{
	if(hasToken() /*&& !m_user->getId().isEmpty()*/ && !post_id.isEmpty())
	{
		getLikedUsers(post_id, "0", "25");
	}
}

void Facebook::getLikedUsers(QString post_id, QString offset, QString limit)
{
	if(hasToken() /*&& !m_user->getId().isEmpty()*/ && !post_id.isEmpty() && !offset.isEmpty() && !limit.isEmpty())
	{
		KQOAuth2Request *req = new KQOAuth2Request(this);
		req->initRequest(KQOAuth2Request::AuthorizedRequest, QUrl(GRAPH_URL + post_id + "/likes"));
		addAuth(req);
		req->setHttpMethod(KQOAuthRequest::GET);

		KQOAuthParameters params;
		params.insert("format", "JSON");
		params.insert("offset", offset);
		params.insert("limit", limit);
		req->setAdditionalParameters(params);

		FBRequestEnvelope *env = new FBRequestEnvelope(post_id, FBApiResponseObjectFactory::ListObj, FBAbstractObjectBase::ProfilesObjs, req);
		connect(env, SIGNAL(requestComplete(QString, FBAbstractObjectBase*)), this, SLOT(onLikedUsersReceived(QString, FBAbstractObjectBase*)));
		connect(env, SIGNAL(requestError(FBResponseMeta*)), this, SLOT(onError(FBResponseMeta*)));
		env->makeRequest();
	}
}

void Facebook::onLikedUsersReceived(QString _id, FBAbstractObjectBase* _list)
{
	disconnect(sender(), SIGNAL(requestComplete(QString, FBAbstractObjectBase*)), this, SLOT(onLikedUsersReceived(QString, FBAbstractObjectBase*)));
	disconnect(sender(), SIGNAL(requestError(FBResponseMeta*)), this, SLOT(onError(FBResponseMeta*)));

	FBListObject* list = qobject_cast<FBListObject*>(_list);

	QVariantList l = list->getList();
	foreach(const QVariant &item, l)
	{
		FBProfile* p = qvariant_cast<FBProfile*>(item);
		if(!p->getName().isEmpty())
		{
			qDebug() << p->getName();
		}
	}

	emit getLikedUsersComplete(_id, l);

	Q_UNUSED(_list);
	Q_UNUSED(_id);
}

void Facebook::publishComment(QString post_id, QString message)
{
	if(hasToken() && !post_id.isEmpty() &&!message.isEmpty())
	{
		KQOAuth2Request *req = new KQOAuth2Request(this);
		req->initRequest(KQOAuth2Request::AuthorizedRequest, QUrl(GRAPH_URL + post_id + "/comments"));
		addAuth(req);
		req->setHttpMethod(KQOAuthRequest::POST);

		KQOAuthParameters params;
		params.insert("message", message);
		params.insert("access_token", oauthSettings.value("fb_oauth_token").toString());
		req->setAdditionalParameters(params);


		FBRequestEnvelope *env = new FBRequestEnvelope(FBApiResponseObjectFactory::FacebookObj, req);
		connect(env, SIGNAL(requestComplete(FBAbstractObjectBase*)), this, SLOT(onPublishCommentReceived(FBAbstractObjectBase*)));
		connect(env, SIGNAL(requestError(FBResponseMeta*)), this, SLOT(onError(FBResponseMeta*)));
		env->makeRequest();
	}
}

void Facebook::onPublishCommentReceived(FBAbstractObjectBase* _obj)
{
	disconnect(sender(), SIGNAL(requestComplete(FBAbstractObjectBase*)), this, SLOT(onPublishCommentReceived(FBAbstractObjectBase*)));
	disconnect(sender(), SIGNAL(requestError(FBResponseMeta*)), this, SLOT(onError(FBResponseMeta*)));

	FacebookObject* fo = qobject_cast<FacebookObject*>(_obj);
	emit publishCommentComplete(fo);

	qDebug() << "published comment id: " << fo->getId();
	Q_UNUSED(_obj);
}

void Facebook::getPicture(QString type)
{
	if(hasToken())
	{
		KQOAuth2Request *req = new KQOAuth2Request(this);
		req->initRequest(KQOAuth2Request::AuthorizedRequest, QUrl(GRAPH_URL + m_user->getId() + "/picture?"));
		addAuth(req);
		req->setHttpMethod(KQOAuthRequest::GET);

		KQOAuthParameters params;
		params.insert("format", "JSON");
		params.insert("redirect", "false");
	    params.insert("type", type);


		req->setAdditionalParameters(params);


		FBRequestEnvelope *env = new FBRequestEnvelope(FBApiResponseObjectFactory::FacebookObj, req);
		connect(env, SIGNAL(requestComplete(FBAbstractObjectBase*)), this, SLOT(onGetPictureReceived(FBAbstractObjectBase*)));
		connect(env, SIGNAL(requestError(FBResponseMeta*)), this, SLOT(onError(FBResponseMeta*)));
		env->makeRequest();
	}
}

void Facebook::onGetPictureReceived(FBAbstractObjectBase* _obj)
{
	disconnect(sender(), SIGNAL(requestComplete(FBAbstractObjectBase*)), this, SLOT(onGetPictureReceived(FBAbstractObjectBase*)));
	disconnect(sender(), SIGNAL(requestError(FBResponseMeta*)), this, SLOT(onError(FBResponseMeta*)));

	FacebookObject* fo = qobject_cast<FacebookObject*>(_obj);

	qDebug() << "Picture URL:  " << fo->getUrl();
	Q_UNUSED(_obj);

	emit getPictureComplete(fo);
}

void Facebook::isLiked(QString post_id)
{
	if(hasToken() && !m_user->getId().isEmpty() && !post_id.isEmpty())
	{
		QString r_id;
		if(post_id.indexOf('_')<0)
		{
			r_id = post_id;
		}
		else
		{
			r_id = post_id.right(post_id.length() - post_id.indexOf('_') - 1);
		}
		KQOAuth2Request *req = new KQOAuth2Request(this);
		req->initRequest(KQOAuth2Request::AuthorizedRequest, QUrl(GRAPH_URL + "fql"));
		addAuth(req);
		req->setHttpMethod(KQOAuthRequest::GET);

		KQOAuthParameters params;
		params.insert("q", "SELECT object_id FROM like WHERE object_id=" + r_id + " and user_id=" + m_user->getId());
		req->setAdditionalParameters(params);


		FBRequestEnvelope *env = new FBRequestEnvelope(FBApiResponseObjectFactory::FacebookObj, req);
		connect(env, SIGNAL(requestComplete(FBAbstractObjectBase*)), this, SLOT(onIsLikedReceived(FBAbstractObjectBase*)));
		connect(env, SIGNAL(requestError(FBResponseMeta*)), this, SLOT(onError(FBResponseMeta*)));
		env->makeRequest();
	}
}

void Facebook::onIsLikedReceived(FBAbstractObjectBase* _obj)
{
	disconnect(sender(), SIGNAL(requestComplete(FBAbstractObjectBase*)), this, SLOT(onIsLikedReceived(FBAbstractObjectBase*)));
	disconnect(sender(), SIGNAL(requestError(FBResponseMeta*)), this, SLOT(onError(FBResponseMeta*)));

	FacebookObject* fo = qobject_cast<FacebookObject*>(_obj);
	emit isLikedComplete(!fo->getObjectId().isEmpty());

	qDebug() << "is liked: " << !fo->getObjectId().isEmpty();
	Q_UNUSED(_obj);
}

void Facebook::search(QString handle, QString type, QString q)
{
	if(hasToken() /*&& !m_user->getId().isEmpty()*/ && !type.isEmpty())
	{
		KQOAuth2Request *req = new KQOAuth2Request(this);
		req->initRequest(KQOAuth2Request::AuthorizedRequest, QUrl(GRAPH_URL+ "/search"));
		addAuth(req);
		req->setHttpMethod(KQOAuthRequest::GET);

		KQOAuthParameters params;
		params.insert("format", "JSON");
		if(!q.isEmpty())
		{
			params.insert("q", q);
		}

        if(type == "post")
        {
			req->setAdditionalParameters(params);

			FBRequestEnvelope *env = new FBRequestEnvelope(handle, FBApiResponseObjectFactory::ListObj, FBAbstractObjectBase::PostsObjs, req);
			connect(env, SIGNAL(requestComplete(QString, FBAbstractObjectBase*)), this, SLOT(onSearchReceived(QString, FBAbstractObjectBase*)));
			connect(env, SIGNAL(requestError(FBResponseMeta*)), this, SLOT(onError(FBResponseMeta*)));
			env->makeRequest();
        }
        else if(type == "place")
        {
        	req->setAdditionalParameters(params);

			FBRequestEnvelope *env = new FBRequestEnvelope(handle, FBApiResponseObjectFactory::ListObj, FBAbstractObjectBase::PlacesObjs, req);
			connect(env, SIGNAL(requestComplete(QString, FBAbstractObjectBase*)), this, SLOT(onSearchReceived(QString, FBAbstractObjectBase*)));
			connect(env, SIGNAL(requestError(FBResponseMeta*)), this, SLOT(onError(FBResponseMeta*)));
			env->makeRequest();
        }
        else if(type == "user")
		{
			req->setAdditionalParameters(params);

			FBRequestEnvelope *env = new FBRequestEnvelope(handle, FBApiResponseObjectFactory::ListObj, FBAbstractObjectBase::ProfilesObjs, req);
			connect(env, SIGNAL(requestComplete(QString, FBAbstractObjectBase*)), this, SLOT(onSearchReceived(QString, FBAbstractObjectBase*)));
			connect(env, SIGNAL(requestError(FBResponseMeta*)), this, SLOT(onError(FBResponseMeta*)));
			env->makeRequest();
		}
	}
}

void Facebook::onSearchReceived(QString handle, FBAbstractObjectBase* _list)
{
	disconnect(sender(), SIGNAL(requestComplete(QString, FBAbstractObjectBase*)), this, SLOT(onSearchReceived(QString, FBAbstractObjectBase*)));
	disconnect(sender(), SIGNAL(requestError(FBResponseMeta*)), this, SLOT(onError(FBResponseMeta*)));

	FBListObject* list = qobject_cast<FBListObject*>(_list);

	QVariantList l = list->getList();

	foreach(const QVariant &item, l)
	{
		FBProfile* p = qvariant_cast<FBProfile*>(item);
		qDebug() << p->getId();
	}

	emit searchComplete(handle, l);

	Q_UNUSED(_list);
	Q_UNUSED(handle);
}
