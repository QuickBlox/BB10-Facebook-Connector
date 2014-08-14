/*
 * Facebook.hpp
 *
 *  Created on: Feb 17, 2013
 *      Author: Vladimir
 */

#ifndef FACEBOOK_HPP_
#define FACEBOOK_HPP_

#include <iostream>
#include <QtCore>
#include <QtCore/QObject>
#include <QSettings>
#include "../oauth/kqoauthmanager.h"
#include "../oauth/kqoauth2request.h"
#include "../oauth/kqoauthrequest.h"

#include "FBAbstractObjectBase.h"
#include "FBUser.h"
#include "FBPlace.h"
#include "FBPost.h"
#include "FBComment.h"
#include "FBResponseMeta.h"
#include "FBRequestEnvelope.h"

class Facebook : public QObject {
	Q_OBJECT

public:
	Facebook();
	virtual ~Facebook();
	static Facebook* instance();

	bool hasToken();
	KQOAuthManager* getRequestManager();
	void addAuth(KQOAuthRequest* req);

private:
	QString getUserDataPermissions();
	QString getFriendsDataPermissions();
	QString getExtendedPermissions();
	QString getCustomPermissions();
	QString getPagePermissions();
	QString getAllPermissions();

	void disconnectFromAll();

	static const QString API_BASE;
	static const QString APPLICATION_ID;
	static const QString APPLICATION_SECRET;


	struct FacebookProfileTypes
	{
		enum Type {
			User = 0,
			Page
		};
	};

	static const QString GRAPH_URL;
	static const QString VIDEO_GRAPH_URL;

	static const QString POSTTYPE_PHOTO;
	static const QString POSTTYPE_VIDEO;
	static const QString POSTTYPE_STATUS;
	static const QString POSTTYPE_LINK;
	static const QString POSTTYPE_SWF;

	//User Data Permissions
	static const QString PUBLIC_PROFILE;
	static const QString FRIENDS;
	static const QString EMAIL;

	static const QString USER_ABOUT_ME;
	static const QString USER_ACTIVITIES;
	static const QString USER_BIRTHDAY;
	static const QString USER_EDUCATION_HISTORY;
	static const QString USER_EVENTS;
	static const QString USER_GROUPS;
	static const QString USER_HOMETOWN;
	static const QString USER_INTERESTS;
	static const QString USER_LIKES;
	static const QString USER_LOCATION;
	static const QString USER_PHOTOS;
	static const QString USER_RELATIONSHIPS;
	static const QString USER_RELATIONSHIP_DETAILS;
	static const QString USER_RELIGION_POLITICS;
	static const QString USER_STATUS;
	static const QString USER_VIDEOS;
	static const QString USER_TRIGGED_PLACES;
	static const QString USER_WEBSITE;
	static const QString USER_WORK_HISTORY;

	static const QString READ_FRIENDLISTS;
	static const QString READ_INSIGHTS;
	static const QString READ_MAILBOX;
	static const QString READ_STREAM;

	static const QString MANAGE_NOTIFICATION;
	static const QString PUBLISH_ACTIONS;
	static const QString RSVP_EVENT;
	static const QString MANAGE_PAGES;
	static const QString READ_PAGE_MAILBOXES;

	static Facebook* m_instance;
    KQOAuthManager *oauthManager;
    KQOAuth2Request *oauthRequest;
    QSettings oauthSettings;


    FBUser* m_user;

public:
    Q_PROPERTY(FBUser* user READ currentUser)
    Q_INVOKABLE FBUser* currentUser();                                        //current user object

	Q_INVOKABLE void login();                                                 //login
	Q_INVOKABLE void logout();                                                //logout
	Q_INVOKABLE bool isAuthorized();                                          //is logged in
	Q_INVOKABLE void getCurrentUser();                                        //The user's profile
	Q_INVOKABLE void getPlaces(QString lat, QString lon, QString distance) ;  //Facebook places near defined coordinates (latitude, longitude)
	Q_INVOKABLE void getPlaces(QString lat, QString lon, QString distance, QString offset, QString limit);  //Facebook places near defined coordinates (latitude, longitude) with pagination
	Q_INVOKABLE void getHome(QString user_id);                                //The user's news feed.
	Q_INVOKABLE void getHome(QString user_id, QString offset, QString limit); //The user's news feed with pagination
	Q_INVOKABLE void getPosts(QString user_id);                               //The user's own posts.
	Q_INVOKABLE void getPosts(QString user_id, QString offset, QString limit);//The user's own posts with pagination
	Q_INVOKABLE void getFeed(QString user_id);                                //The user's wall.
	Q_INVOKABLE void getFeed(QString user_id, QString offset, QString limit); //The user's wall with pagination
	Q_INVOKABLE void getFriends(QString user_id);                             //The user's friends
	Q_INVOKABLE void getFriends(QString user_id, QString offset, QString limit);//The user's friends with pagination
	Q_INVOKABLE void publishLink(QString url, QString message);               //Publish link to user's wall.
	Q_INVOKABLE void publishNote(QString subject, QString message);           //Publish node to user's wall.
	Q_INVOKABLE void publishStatus(QString message);                          //Publish status to user's wall.
	Q_INVOKABLE void publishCheckin(QString place_id, QString latitude, QString longitude, QVariantList tagged_friends, QString message, QString link, QString picture);//Publish checkin
	Q_INVOKABLE void publishPhoto(QString filepath, QString message, QString place_id, QString no_story);                                                               //Publish photo file
	Q_INVOKABLE void publishVideo(QString filepath, QString title, QString description);                                                                                //Publish video file
	Q_INVOKABLE void like(QString post_id);
	Q_INVOKABLE void unlike(QString post_id);
	Q_INVOKABLE void getComments(QString post_id);
	Q_INVOKABLE void getComments(QString post_id, QString offset, QString limit);
	Q_INVOKABLE void getLikedUsers(QString post_id);
	Q_INVOKABLE void getLikedUsers(QString post_id, QString offset, QString limit);
	Q_INVOKABLE void publishComment(QString post_id, QString message);
	Q_INVOKABLE void getPicture(QString type);                                //current user photo
	Q_INVOKABLE void isLiked(QString post_id);
	Q_INVOKABLE void search(QString handle, QString type, QString q);         //search request

signals:
	void urlReady(QUrl);
	void error(FBResponseMeta*);
	void loginComplete(bool);
	void logoutComplete(bool);
	void getCurrentUserComplete(FBUser* user);
	void getPlacesComplete(QList<QVariant> list);
	void getHomeComplete(QString user_id, QList<QVariant> list);
	void getPostsComplete(QString user_id, QList<QVariant> list);
	void getFeedComplete(QString user_id, QList<QVariant> list);
	void getFriendsComplete(QString user_id, QList<QVariant> list);
	void publishLinkComplete(FacebookObject* resultObject);
	void publishNoteComplete(FacebookObject* resultObject);
    void publishStatusComplete(FacebookObject* resultObject);
    void publishCheckinComplete(FacebookObject* resultObject);
    void publishPhotoComplete(FacebookObject* resultObject);
	void publishVideoComplete(FacebookObject* resultObject);
	void likeComplete(bool);
	void unlikeComplete(bool);
	void getCommentsComplete(QString post_id, QList<QVariant> list);
    void getLikedUsersComplete(QString post_id, QList<QVariant> list);
    void publishCommentComplete(FacebookObject* resultObject);
    void getPictureComplete(FacebookObject* resultObject);
    void isLikedComplete(bool is_liked);
    void searchComplete(QString handle, QList<QVariant> list);

private slots:
    void onError(FBResponseMeta*);
	void onTemporaryTokenReceived(QString, QString);
	void onAuthorizationReceived(QString, QString);
	void onAccessTokenReceived(QString, QString);
	void onAuthorizedRequestDone();
	void onRequestReady(QByteArray);
	void onCurrentUserReceived(FBAbstractObjectBase*);
	void onPlacesReceived(FBAbstractObjectBase*);
	void onHomeReceived(QString, FBAbstractObjectBase*);
	void onPostsReceived(QString, FBAbstractObjectBase*);
	void onFeedReceived(QString, FBAbstractObjectBase*);
	void onFriendsReceived(QString, FBAbstractObjectBase*);
	void onPublishLinkReceived(FBAbstractObjectBase*);
	void onPublishNoteReceived(FBAbstractObjectBase*);
    void onPublishStatusReceived(FBAbstractObjectBase*);
    void onPublishCheckinReceived(FBAbstractObjectBase*);
    void onPublishPhotoReceived(FBAbstractObjectBase*);
	void onPublishVideoReceived(FBAbstractObjectBase*);
	void onLikeReceived(FBAbstractObjectBase*);
    void onUnlikeReceived(FBAbstractObjectBase*);
    void onCommentsReceived(QString, FBAbstractObjectBase*);
    void onLikedUsersReceived(QString, FBAbstractObjectBase*);
    void onPublishCommentReceived(FBAbstractObjectBase*);
    void onGetPictureReceived(FBAbstractObjectBase*);
    void onIsLikedReceived(FBAbstractObjectBase*);
    void onSearchReceived(QString, FBAbstractObjectBase*);
};
#endif /* FACEBOOK_HPP_ */
