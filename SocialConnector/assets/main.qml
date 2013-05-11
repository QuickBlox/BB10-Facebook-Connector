import bb.system 1.0
import bb.cascades 1.0
import com.injoit.sc 1.0

/* READ ME!!!
 * On developer Facebook site:
 * 1) Register your application on Facebook and receive "Application ID" and "Application Secret" keys.
 * 2) Define callback URL for application: http://localhost:61793/
 * 
 * In this source code (file Facebook.cpp):
 * 1) Setup variables APPLICATION_ID and APPLICATION_SECRET in source code (Facebook.cpp), like:
 * 		   const QString Facebook::APPLICATION_ID = QString("475257765857500");
 *         const QString Facebook::APPLICATION_SECRET = QString("7fd7172563886ea51c730ebd8dfa6260");
 * 3) Build and run! You can uncomment any function that you need in main.qml file and see how it works!
 */

// creates one page with a label
Page {
    Container {
        id: rootContainer
        onCreationCompleted: {
           // login to Facebook
           facebook.login();
        }
        
        function showPlaces(list)
        {
            placesModel.appendData(list);
        }
        
        Label {
            id: labelUserName
            text: qsTr("This is Facebook Library demo application")
        }
        
         Button {
            text: "Request"
            onClicked:
            {
                
                /*  READ ME!!!
                 *  Uncomment function that you need. For example to load Facebook  places uncomment function: facebook.getPlaces
                 *  Loaded facebook palces will be availeble in "onGetPlacesComplete" slot.
                 */
                
                
                //Get  user's own posts (default first 25 posts)
                facebook.getPosts(facebook.currentUser().id)
                
                //Get user's own posts (offset=0 limit=20)
                //facebook.getPosts(facebook.currentUser().id, "0", "20");
                
                //Get posts from user's wall (default first 25 posts)
                //facebook.getFeed(facebook.currentUser().id);
                
                //Get posts from user's wall (offset=0 limit=20)
                //facebook.getFeed(facebook.currentUser().id, "0", "20");
                
                //Get comments for post with ID=67920382572_129280803918851 (default first 25 comments)
                //facebook.getComments("67920382572_129280803918851");
                
                //Get comments for post with ID=67920382572_129280803918851 (offset=0 limit=20)
                //facebook.getComments("67920382572_129280803918851", "0", "20");
                
                //Get facebook places near defined coordinates (latitude=53.3932885 longitude=-2.9185925 distance=1000m). Default first 25 places
                //facebook.getPlaces("53.3932885", "-2.9185925", "1000");
                
                //Get facebook places near defined coordinates (latitude=53.3932885 longitude=-2.9185925 distance=1000m offset=0 limit=20
                //facebook.getPlaces("53.3932885", "-2.9185925", "1000", "0", "20");
                
                //Get user's news feed (default first 25)
                //facebook.getHome(facebook.currentUser().id); 
                
                //Get user's news feed (offset=0 limit=20)
                //facebook.getHome(facebook.currentUser().id, "0", "20");
                
                //Get user's friends (default first 25)
                //facebook.getFriends(facebook.currentUser().id);
                
                //Get user's friends (offset=0 limit=20)
                //facebook.getFriends(facebook.currentUser().id, "0", "20");
                
                //Get users who liked post with ID = 67920382572_129280803918851 (default first 25)
                //facebook.getLikedUsers("67920382572_129280803918851");
                
                //Get users who liked post with ID = 67920382572_129280803918851 ((offset=0 limit=20)
                //facebook.getLikedUsers("67920382572_129280803918851", "0", "20");
                
                //Publish comment for post with ID = 67920382572_129280803918851
                //facebook.publishComment("67920382572_129280803918851", "This is cool!!!");
                
                //Publish picture 
                //facebook.publishPhoto("app/native/assets/images/leonardo.jpg", "This is Leo", "", "");
                
                //Publish video file 
                //facebook.publishVideo("app/native/assets/videos/bomb.mp4", "Published Video", "This is my video file!");
                //facebook.publishVideo("app/native/assets/videos/bomb.3gp", "Published Video", "This is my video file!");
                
                //Publish Note
                //facebook.publishNote("This is note subject", "This is note body!");
                
                //Publish Status
                //facebook.publishStatus("This is status text");
                
                //Publish Link
                //facebook.publishLink("http://google.com/", "GOOGLE!");
                
                //Like post with ID = "67920382572_10151599256077573"
                // facebook.like("67920382572_10151599256077573");
                
                //Unike post with ID = "67920382572_10151599256077573"
                //facebook.unlike("67920382572_10151599256077573");
                
                //Is this post (ID = 67920382572_617112321647738) liked by current user earlier
                //facebook.isLiked("67920382572_617112321647738");
             
                //Search plcases with word: "coffee"                
                //facebook.search("any string here to handle answer", "place", "coffee");
                
                //Search posts with word: "football"  
                //facebook.search("any string here to handle answer", "post", "football");
                
                //Search peoples with name: "Denis"  
                //facebook.search("any string here to handle answer", "user", "Denis");
                
                //Load current user picture
                //facebook.getPicture("normal")
                
                //Logout from facebook
                //facebook.logout();
            }
        }
        
        //result label
        Label{
            id: resultLabel
            text: "result string"
        }
                
        //ListView for results
        ListView 
	    {
	        id: listView
	        dataModel: placesModel
	        listItemComponents: 
			[
				ListItemComponent 
	            {
	                type: "item"
					Label{
					    text: ListItemData.id
					}
		        }
	        ]
	        function itemType(data, indexPath)
	        {
	            return ("item")
            }
	        
	        horizontalAlignment: HorizontalAlignment.Fill
	        verticalAlignment: VerticalAlignment.Fill
	    }
    }
    attachedObjects: [
        Facebook {
            id: facebook
            onLoginComplete:
            {
                loginToast.show();
            }
            onLogoutComplete:
            {
                logoutToast.show();
            }
            onGetCurrentUserComplete:
            {
                resultLabel.text = user.getName();
            }
            onGetPlacesComplete:
            {
                rootContainer.showPlaces(list);
            }
            onGetHomeComplete:
            {
                rootContainer.showPlaces(list);
            }
            onGetPostsComplete:
            {
                rootContainer.showPlaces(list);
            }
            onGetFeedComplete:
            {
                rootContainer.showPlaces(list);
            }
            onPublishNoteComplete:
            {
                resultLabel.text = resultObject.id;
            }
            onPublishLinkComplete:
            {
                resultLabel.text = resultObject.id;
            }
            onPublishStatusComplete:
            {
                resultLabel.text = resultObject.id;
            }
            onGetFriendsComplete:
            {
                rootContainer.showPlaces(list);
                
                //CHECKIN
                //  145974975442140 - facebook place ID
                //  53.3932885 - latitude
                //  -2.9185925 - longitude
                //  list - current user friends
                //  "Drinking beer" - comment
                //
                //facebook.publishCheckin("145974975442140","53.3932885", "-2.9185925", list, "Doing something...", "", ""); 
            }
            onPublishCheckinComplete:
            {
                resultLabel.text = resultObject.id;
            }
            onPublishPhotoComplete:
            {
                resultLabel.text = resultObject.id;
            }
            onPublishVideoComplete:
            {
                resultLabel.text = resultObject.id;
            }
            onLikeComplete:
            {
                resultLabel.text = "liked";
            }
            onUnlikeComplete:
            {
                resultLabel.text = "unliked";
            }
            onGetCommentsComplete:
            {
                rootContainer.showPlaces(list);
            }
            onGetLikedUsersComplete:
            {
                rootContainer.showPlaces(list);
            }
            onPublishCommentComplete:
            {
                resultLabel.text = resultObject.id;
            }
            onGetPictureComplete:
            {
               resultLabel.text = resultObject.url;
            }
            onIsLikedComplete:
            {
               resultLabel.text = is_liked;
            }
            onSearchComplete:
            {
                rootContainer.showPlaces(list);
            }
        },
        SystemToast {
            id: loginToast
            body: "You are logged in!"
        },
        SystemToast {
            id: logoutToast
            body: "You are logged out!"
        },
        ObjectsDataModel{
            id: placesModel
        }
    ]
}