#include <jni.h>
#include <time.h>
#include <android/log.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include <moaicore/moaicore.h>
#include <moaiext-android/moaiext-android.h>
#include <aku/AKU.h>
#include <aku/AKU-untz.h>
#include <aku/AKU-luaext.h>


template <class T>
class LockingQueue {
public:
	pthread_mutex_t mutex;
	int tail;
	int num;

	static const int kMaxMessages = 100;

	T messages [ kMaxMessages ];

	//----------------------------------------------------------------//
	void Push ( const T &message ) {

		pthread_mutex_lock( &mutex );

		if ( num >= LockingQueue::kMaxMessages ) {
			printf ("ERROR: g_MessageQueue, kMaxMessages (%d) exceeded\n", LockingQueue::kMaxMessages );
		} 
		else {
			int head = ( tail + num) % LockingQueue::kMaxMessages;

			 messages [ head ] = message;
			++num;

			if ( num >= LockingQueue::kMaxMessages )  {
				 num -= LockingQueue::kMaxMessages;
			}

		}

		pthread_mutex_unlock( &mutex );
	}

	int PopMessage ( T &message ) {

		pthread_mutex_lock( &mutex );

		int result = 0;

		if ( num > 0) {

			result = 1;
			message = messages [ tail ];
			++tail;

			if ( tail >=  LockingQueue::kMaxMessages) {
				tail -=  LockingQueue::kMaxMessages;
			}
			--num;
		}

		pthread_mutex_unlock( &mutex );

		return result;
	}
};

struct InputEvent {

	enum {
		INPUTEVENT_LEVEL,
		INPUTEVENT_COMPASS,
		INPUTEVENT_LOCATION,
		INPUTEVENT_TOUCH,
	};

	int 	m_type;
	int 	m_deviceId;
	int 	m_sensorId;

	// touch, level
	float 	m_x;
	float 	m_y;
	
	// level
	float 	m_z;

	// compass
	int 	m_heading;

	// touch
	int  	m_touchId;
	bool 	m_down;
	int  	m_tapCount;
	
	// location
	double 	m_longitude;
	double 	m_latitude;
	double 	m_altitude;
	float  	m_hAccuracy;
	float  	m_vAccuracy;
	float  	m_speed;
};

LockingQueue<InputEvent> *g_InputQueue = NULL;

//================================================================//
// Utility macros
//================================================================//

	#define GET_ENV() 	\
		JNIEnv* env; 	\
		jvm->GetEnv (( void** )&env, JNI_VERSION_1_4 );
		
	#define GET_CSTRING(jstr, cstr) \
		const char* cstr = env->GetStringUTFChars ( jstr, NULL );

	#define RELEASE_CSTRING(jstr, cstr) \
		env->ReleaseStringUTFChars ( jstr, cstr );
		
	#define GET_JSTRING(cstr, jstr) \
		jstring jstr = env->NewStringUTF (( const char* )cstr );
		
	#define PRINT(str) \
		__android_log_write ( ANDROID_LOG_INFO, "MoaiLog", str );
		
//================================================================//
// JNI set up
//================================================================//

	JavaVM* 		jvm;
	JNIEnv* 		gEnv;

	jobject			mMoaiActivity;
	jobject			mMoaiView;

	jmethodID 		mCheckBillingSupportedFunc;
	jmethodID		mConfirmNotificationFunc;
	jmethodID 		mGenerateGuidFunc;
	jmethodID		mOpenURLFunc;
	jmethodID		mRegisterNotificationsFunc;
	jmethodID		mRequestPurchaseFunc;
	jmethodID		mRestoreTransactionsFunc;
	jmethodID		mSetMarketPublicKeyFunc;
	jmethodID		mShowDialogFunc;
	jmethodID		mShareFunc;
	
	jclass			mFlurryClass;
	jmethodID		mFlurryLogEvent;
	jmethodID		mFlurryLogEventTimed;
	jmethodID		mFlurryLogEventWithParameters;
	jmethodID		mFlurryLogEventWithParametersTimed;
	jmethodID		mFlurryEndTimedEvent;
	jmethodID		mFlurryOnError;
	jmethodID		mFlurrySetUserID;
	jmethodID		mFlurrySetAge;
	jmethodID		mFlurrySetGender;
	jmethodID		mMoaiFlurryLogEvent;
	
	jmethodID		mSixWavesCrossSell;
	jmethodID   	mSixWavesHideAdBanner;
	jmethodID	 	mSixWavesHideCrossSellBtn;
	jmethodID		mSixWavesShowAdBanner;
	jmethodID		mSixWavesShowCrossSellBtn;
	jmethodID		mSixWavesTrackPurchaseEvent;
	jmethodID		mSixWavesTrackInGameItemPurchase;
	jmethodID		mSixWavesTrackTutorialEvent;
	
		// FB
	jclass			mFBClass;
	jobject			mFBObject;
	jmethodID		mFBAPIFunc;
	jmethodID		mFBGetLoginStatusFunc;
	jmethodID		mFBIsInitializedFunc;
	jmethodID		mFBIsSessionValidFunc;
	jmethodID		mFBInitFunc;
	jmethodID		mFBLoginFunc;
	jmethodID		mFBLogoutFunc;
	MOAILuaRef fbLoginCallback;
	map<long, MOAILuaRef> mFBCallbackMap;
	
	//----------------------------------------------------------------//
	int JNI_OnLoad ( JavaVM* vm, void* reserved ) {
    
		jvm = vm;		
		return JNI_VERSION_1_4;
	}
	
//================================================================//
// 6 Waves Funcs
//================================================================//
	static int SixWaves_crossSell(lua_State *L)
	{
		GET_ENV();
		env->CallVoidMethod( mMoaiActivity, mSixWavesCrossSell );
		return 0;
	}
	
	static int SixWaves_hideAdBanner(lua_State *L)
	{
		return 0;
	}
	
	static int SixWaves_hideCrossSellBtn(lua_State *L)
	{
		GET_ENV();
		env->CallVoidMethod( mMoaiActivity, mSixWavesHideCrossSellBtn );
		return 0;
	}
	
	static int SixWaves_showAdBanner(lua_State *L)
	{
		return 0;
	}
	
	static int SixWaves_showCrossSellBtn(lua_State *L)
	{
		GET_ENV();
		env->CallVoidMethod( mMoaiActivity, mSixWavesShowCrossSellBtn );
		return 0;
	}
	
	static int SixWaves_trackPurchaseEvent(lua_State *L)
	{
		GET_ENV()
		if( lua_type(L, 1) != LUA_TSTRING )
			return 0;
		
		if( lua_type(L, 2) != LUA_TNUMBER )
			return 0;
			
		jstring itemID = env->NewStringUTF(lua_tostring(L,1));	
		float val = lua_tonumber(L, 2);
		env->CallVoidMethod( mMoaiActivity, mSixWavesTrackPurchaseEvent, itemID,  val);
		env->DeleteLocalRef(itemID);
		return 0;
	}
	
	static int SixWaves_trackInGameItemPurchaseWithItem(lua_State *L)
	{
		GET_ENV();
		if( lua_type(L, 1) != LUA_TSTRING )
			return 0;

		jstring itemID = env->NewStringUTF(lua_tostring(L,1));
		int table_count = 0;
		
		jobjectArray items;
		int idx = 2;
		if(lua_type(L,2) == LUA_TTABLE )
		{
			lua_pushnil( L );

			while( lua_next( L, idx)  != 0 )
			{
				int keyType = lua_type(L, -2);
				int valType = lua_type(L, -1);

				if(( keyType == LUA_TSTRING || keyType == LUA_TNUMBER) &&
				  ( valType == LUA_TSTRING || valType == LUA_TNUMBER))
				  table_count +=2;
				  
				lua_pop( L, 1 );
			}

			jstring keyList[table_count];
			
			if( table_count > 1 )
			{
				items = (jobjectArray)env->NewObjectArray(table_count,
						 env->FindClass("java/lang/String"),
						 env->NewStringUTF(""));
				lua_pushnil( L );
				int count = 0;
				idx = 2;
				while( lua_next( L, idx)  != 0 )
				{
					int keyType = lua_type(L, -2);
					int valType = lua_type(L, -1);
					if( (keyType != LUA_TSTRING && keyType != LUA_TNUMBER) || 
						(valType != LUA_TSTRING && valType != LUA_TNUMBER))
						continue;
						
					if( keyType == LUA_TSTRING )
						env->SetObjectArrayElement( items,count,env->NewStringUTF(lua_tostring(L,-2)));
					else
					{
						float value = lua_tonumber(L, -2);
						char string[512];
						sprintf( string, "%f", value );
						env->SetObjectArrayElement( items,count,env->NewStringUTF(string));
					}	
					
					if( valType == LUA_TSTRING )
						env->SetObjectArrayElement( items,count+1,env->NewStringUTF(lua_tostring(L,-1)));
					else
					{
						float value = lua_tonumber(L, -1);
						char string[512];
						sprintf( string, "%f", value );
						env->SetObjectArrayElement( items,count+1,env->NewStringUTF(string));
					}
					const char *value;
					
					count +=2;
					lua_pop( L, 1 );
				}
			}
		}

		env->CallVoidMethod( mMoaiActivity, mSixWavesTrackInGameItemPurchase, itemID,  items);
		env->DeleteLocalRef(itemID);
		if( table_count > 1 )
			env->DeleteLocalRef(items);
		return 0;
	}
	
	static int SixWaves_trackTutorialEvent(lua_State *L)
	{
		GET_ENV()
		if( lua_type(L, 1) != LUA_TSTRING &&  lua_type(L, 1) != LUA_TNUMBER)
			return 0;
		
		jstring eventString;
		if(lua_type(L, 1) == LUA_TSTRING)
			eventString = env->NewStringUTF(lua_tostring(L,1));	
		else
		{
			float value = lua_tonumber(L, 1);
			char string[512];
			sprintf( string, "%f", value );
			eventString = env->NewStringUTF( string );
		}
		env->CallVoidMethod( mMoaiActivity, mSixWavesTrackTutorialEvent, eventString );
		env->DeleteLocalRef(eventString);
		return 0;
	}
	
//================================================================//
// Flurry Funcs
//================================================================//
	static int Flurry_logEvent(lua_State *L)
	{
		if( lua_type(L, 1) != LUA_TSTRING )
		{
			PRINT("ERROR: AnalyticsAPI.logEvent() param #1 must be a string");
			return 0;
		}
		
		GET_ENV();
		jstring evt = env->NewStringUTF(lua_tostring(L, 1));
		
		jobjectArray items;
		int idx = 2;
		int table_count = 0;
		if( lua_type(L, 2) == LUA_TTABLE )
		{
			// TODO: Implement parameter parsing at some point
			//PRINT("WARNING: Dropping parameters for Flurry.logEvent()");
			//env->CallStaticVoidMethod( mFlurryClass, mFlurryLogEvent, evt );
			lua_pushnil( L );

			while( lua_next( L, idx)  != 0 )
			{
				int keyType = lua_type(L, -2);
				int valType = lua_type(L, -1);

				if(( keyType == LUA_TSTRING || keyType == LUA_TNUMBER) &&
				  ( valType == LUA_TSTRING || valType == LUA_TNUMBER))
				  table_count +=2;
				  
				lua_pop( L, 1 );
			}

			jstring keyList[table_count];
			
			if( table_count > 1 )
			{
				items = (jobjectArray)env->NewObjectArray(table_count,
						 env->FindClass("java/lang/String"),
						 env->NewStringUTF(""));
				lua_pushnil( L );
				int count = 0;
				idx = 2;
				while( lua_next( L, idx)  != 0 )
				{
					int keyType = lua_type(L, -2);
					int valType = lua_type(L, -1);
					if( (keyType != LUA_TSTRING && keyType != LUA_TNUMBER) || 
						(valType != LUA_TSTRING && valType != LUA_TNUMBER))
						continue;
						
					if( keyType == LUA_TSTRING )
						env->SetObjectArrayElement( items,count,env->NewStringUTF(lua_tostring(L,-2)));
					else
					{
						float value = lua_tonumber(L, -2);
						char string[512];
						sprintf( string, "%f", value );
						env->SetObjectArrayElement( items,count,env->NewStringUTF(string));
					}	
					
					if( valType == LUA_TSTRING )
						env->SetObjectArrayElement( items,count+1,env->NewStringUTF(lua_tostring(L,-1)));
					else
					{
						float value = lua_tonumber(L, -1);
						char string[512];
						sprintf( string, "%f", value );
						env->SetObjectArrayElement( items,count+1,env->NewStringUTF(string));
					}
					const char *value;
					
					count +=2;
					lua_pop( L, 1 );
				}
			}
			
			//Log event here
			env->CallVoidMethod( mMoaiActivity, mMoaiFlurryLogEvent, evt, items);
			if( table_count > 1 )
				env->DeleteLocalRef(items);
		}
		else
		{
			env->CallStaticVoidMethod( mFlurryClass, mFlurryLogEvent, evt );
		}

		env->DeleteLocalRef(evt);
		
		return 0;
	}
	
	static int Flurry_logTimedEvent(lua_State *L)
	{
		if( lua_type(L, 1) != LUA_TSTRING )
		{
			PRINT("ERROR: AnalyticsAPI.logTimedEvent() param #1 must be a string");
			return 0;
		}
		
		GET_ENV();
		jstring evt = env->NewStringUTF(lua_tostring(L, 1));
		
		if( lua_type(L, 2) == LUA_TTABLE )
		{
			// TODO: Implement parameter parsing at some point
			PRINT("WARNING: Dropping parameters for Flurry.logEvent()");
			env->CallStaticVoidMethod( mFlurryClass, mFlurryLogEventTimed, evt, true );
		}
		else
		{
			env->CallStaticVoidMethod( mFlurryClass, mFlurryLogEventTimed, evt, true );
		}
		
		env->DeleteLocalRef(evt);

		return 0;
	}
	
	static int Flurry_endTimedEvent(lua_State *L)
	{
		if( lua_type(L, 1) != LUA_TSTRING )
		{
			PRINT("ERROR: AnalyticsAPI.endTimedEvent() param #1 must be a string\n");
			return 0;
		}
		
		GET_ENV();
		jstring evt = env->NewStringUTF(lua_tostring(L, 1));
		env->CallStaticVoidMethod( mFlurryClass, mFlurryEndTimedEvent, evt );
		env->DeleteLocalRef(evt);
		
		return 0;
	}
	
	static int Flurry_logError(lua_State *L)
	{
		if( lua_type(L, 1) != LUA_TSTRING )
		{
			printf("ERROR: AnalyticsAPI.logError() param #1 must be a string\n");
			return 0;
		}
		
		GET_ENV();
		jstring err = env->NewStringUTF( lua_tostring(L, 1) );
		jstring msg = env->NewStringUTF( lua_type(L, 2) == LUA_TSTRING ? lua_tostring(L, 2) : "" );
		jstring exc = env->NewStringUTF( "" );
		
		env->CallStaticVoidMethod( mFlurryClass, mFlurryOnError, err, msg, exc );
		
		env->DeleteLocalRef(err);
		env->DeleteLocalRef(msg);
		env->DeleteLocalRef(exc);
		
		return 0;
	}
	
	static int Flurry_userInfo(lua_State *L)
	{
		GET_ENV();
	
		if( lua_type(L, 1) == LUA_TSTRING )
		{
			env->CallStaticVoidMethod( mFlurryClass, mFlurrySetUserID, env->NewStringUTF(lua_tostring(L, 1)) );
		}
		
		if( lua_type(L, 2) == LUA_TSTRING )
		{
			// TODO: skipping age for now.
			PRINT("WARNING: Flurry.userInfo() skipping age setting via string for now");
		}
		else if( lua_type(L, 2) == LUA_TNUMBER )
		{
			jbyte age = (jbyte)lua_tonumber(L, 2);
			env->CallStaticVoidMethod( mFlurryClass, mFlurrySetAge, age );
		}
		
		if( lua_type(L, 3) == LUA_TSTRING )
		{
			cc8* gender = lua_tostring(L, 3);
			if( tolower(gender[0]) == 'm' )
			{
				env->CallStaticVoidMethod( mFlurryClass, mFlurrySetGender, (jbyte)'m' );
			}
			else if( tolower(gender[0]) == 'f' )
			{
				env->CallStaticVoidMethod( mFlurryClass, mFlurrySetGender, (jbyte)'f' );
			}
		}
		
		return 0;
	}
		
//================================================================//
// Facebook
//================================================================//
static void PushErrorTable(lua_State *L, int errorCode, cc8* errorMessage)
{
	lua_newtable(L);
	
	lua_pushnumber(L, errorCode);
	lua_setfield(L, -2, "code");
	
	lua_pushstring(L, errorMessage);
	lua_setfield(L, -2, "message");
}
static int FB_api(lua_State *L)
{
	// Check for operational facebook
	MOAILuaState state ( L );
	GET_ENV();
	if(!env->CallBooleanMethod(mFBObject, mFBIsInitializedFunc))
		return 0;
	if(lua_type(L, 1) != LUA_TSTRING)
	{
		return 0;
	}
	cc8* path = state.GetValue<cc8*>(1, "");
	int idx = 2;
	cc8* method = "GET";
	if(lua_type(L, 2) == LUA_TSTRING)
	{
		method = state.GetValue<cc8*>(2, "GET");
		idx++;
	}

	cc8* json = "";
	if( lua_type(L, idx) == LUA_TTABLE )
	{
		u32 itr = state.PushTableItr ( idx );
		while ( state.TableItrNext ( itr ))
		{
			json = lua_tostring(state, -1);
		}
		idx++;
	}

	MOAILuaRef callback;

	if(lua_type(L, idx) != LUA_TFUNCTION)
	{
		return 0;
	}

	callback.SetStrongRef(state, idx);
	long addr = (long)&callback;
	mFBCallbackMap[addr] = callback;
	
	jstring jPath = env->NewStringUTF(path);
	jstring jMethod = env->NewStringUTF(method);
	jstring jParams = env->NewStringUTF(json);
	env->CallVoidMethod(mFBObject, mFBAPIFunc, jPath, jMethod, jParams, addr);
	if(jPath)
		env->DeleteLocalRef(jPath);
	if(jMethod)
		env->DeleteLocalRef(jMethod);
	if(jParams)
		env->DeleteLocalRef(jParams);
	return 0;
}
static int FB_getLoginStatus(lua_State *L)
{
	MOAILuaState state ( L );
	GET_ENV();
	if(!env->CallBooleanMethod(mFBObject, mFBIsInitializedFunc))
		return 0;

	if(lua_type(L, 1) != LUA_TFUNCTION)
	{
		return 0;
	}
	MOAILuaRef callback;
	callback.SetStrongRef(state, 1);
	//long addr = (long)&callback;

	// If there isn't a valid session, abort early
	if(!env->CallBooleanMethod(mFBObject, mFBIsSessionValidFunc))
	{
		MOAILuaStateHandle state = callback.GetSelf();
		lua_newtable(L);
		lua_pushstring(L, "not connected");
		lua_setfield(L, -2, "status");
		PushErrorTable(L, 0, "Existing sesssion is invalid");
		lua_setfield(L, -2, "error");

		state.DebugCall(1, 0);
		callback.Clear();
		return 0;
	}
	fbLoginCallback = callback;
	env->CallVoidMethod(mFBObject, mFBGetLoginStatusFunc);
	return 0;
}
static int FB_init(lua_State *L)
{
	MOAILuaState state ( L );
	GET_ENV();

	if(!lua_isstring(L, 1) )
	{

		return 0;
	}

	jstring jAppID = env->NewStringUTF(state.GetValue< cc8* >(1, ""));

	env->CallVoidMethod(mFBObject, mFBInitFunc, jAppID);
	if(jAppID)
		env->DeleteLocalRef(jAppID);
	


	return 0;
}
static int FB_login(lua_State *L)
{
	MOAILuaState state ( L );
	GET_ENV();
	if(!env->CallBooleanMethod(mFBObject, mFBIsInitializedFunc))
		return 0;
	if(lua_type(L, 1) != LUA_TFUNCTION)
	{
		return 0;
	}
	cc8* scope = NULL;

	if( lua_type(L, 2) == LUA_TTABLE )
	{
		lua_getfield(state, 2, "scope");
		scope = lua_tostring(state, -1);
		lua_pop(state, 1);
	}
	MOAILuaRef callback;
	callback.SetStrongRef(state, 1);
	fbLoginCallback = callback;
	
	jstring jScope = env->NewStringUTF(scope);
	env->CallVoidMethod(mFBObject, mFBLoginFunc, jScope);
	if(jScope)
		env->DeleteLocalRef(jScope);
	
	
	return 0;
}
static int FB_logout(lua_State *L)
{
	MOAILuaState state ( L );
	GET_ENV();
	env->CallVoidMethod(mFBObject, mFBLogoutFunc);
	return 0;
}
	
//================================================================//
// In-App Billing callbacks
//================================================================//

	//----------------------------------------------------------------//
	bool CheckBillingSupported () {

		GET_ENV ();

		bool retVal = env->CallBooleanMethod ( mMoaiActivity , mCheckBillingSupportedFunc );
		return retVal;
	}

	//----------------------------------------------------------------//
	bool ConfirmNotification ( const char* notification ) {

		GET_ENV ();
		GET_JSTRING ( notification, jstr );
		
		bool retVal = ( bool )env->CallBooleanMethod ( mMoaiActivity , mConfirmNotificationFunc, jstr );
		return retVal;
	}

	//----------------------------------------------------------------//
	void RequestNotifications( int types ){
	
		GET_ENV ();
		env->CallVoidMethod( mMoaiActivity, mRegisterNotificationsFunc);
	}
	
	//----------------------------------------------------------------//
	bool RequestPurchase ( const char* identifier, const char* payload ) {

		GET_ENV ();
		GET_JSTRING ( identifier, jidentifier );
		GET_JSTRING ( payload, jpayload );

		bool retVal = ( bool )env->CallBooleanMethod ( mMoaiActivity , mRequestPurchaseFunc, jidentifier, jpayload );
		return retVal;
	}	
		
	//----------------------------------------------------------------//
	bool RestoreTransactions () {

		GET_ENV ();
		
		bool retVal = ( bool )env->CallBooleanMethod ( mMoaiActivity , mRestoreTransactionsFunc );
		return retVal;
	}
	
	//----------------------------------------------------------------//
	void SetMarketPublicKey ( const char* key ) {

		GET_ENV ();
		GET_JSTRING ( key, jstr );
		
		env->CallVoidMethod ( mMoaiActivity, mSetMarketPublicKeyFunc, jstr );
	}
	
	//----------------------------------------------------------------//
	void ShowDialog ( const char* title , const char* message , const char* positive , const char* neutral , const char* negative , bool cancelable ) {

		GET_ENV ();

		GET_JSTRING ( title, jtitle );
		GET_JSTRING ( message, jmessage );
		GET_JSTRING ( positive, jpositive );
		GET_JSTRING ( neutral, jneutral );
		GET_JSTRING ( negative, jnegative );

		env->CallVoidMethod ( mMoaiActivity , mShowDialogFunc, jtitle, jmessage, jpositive, jneutral, jnegative, cancelable );
	}
	
	//----------------------------------------------------------------//
	void Share ( const char* prompt , const char* subject , const char* text ) {

		GET_ENV ();

		GET_JSTRING ( prompt, jprompt );
		GET_JSTRING ( subject, jsubject );
		GET_JSTRING ( text, jtext );

		env->CallVoidMethod ( mMoaiActivity , mShareFunc, jprompt, jsubject, jtext );
	}
	
//================================================================//
// Generate GUID callback
//================================================================//

	//----------------------------------------------------------------//
	const char* GenerateGUID () {

		GET_ENV ();

	    // call generate guid method in java
		jstring jguid = ( jstring )env->CallObjectMethod ( mMoaiView, mGenerateGuidFunc );

		// convert jstring to cstring
		GET_CSTRING ( jguid, guid );

		char buf [ 512 ];
		strcpy ( buf, guid );
		const char* retVal = buf;
		
		RELEASE_CSTRING ( jguid, guid );

		// return guid string
		return retVal;
	}

//================================================================//
// Open Url External callback
//================================================================//

	//----------------------------------------------------------------//
	void OpenURL ( const char* url ) {

		GET_ENV ();
		GET_JSTRING ( url, jstr );
		
		env->CallVoidMethod ( mMoaiActivity, mOpenURLFunc, jstr );
	}

//================================================================//
// JNI Functions
//================================================================//

	//----------------------------------------------------------------//
	extern "C" int Java_@PACKAGE_UNDERSCORED@_MoaiView_AKUCreateContext ( JNIEnv* env, jclass obj ) {
		return AKUCreateContext ();
	}

	//----------------------------------------------------------------//
	extern "C" void Java_@PACKAGE_UNDERSCORED@_MoaiView_AKUDeleteContext ( JNIEnv* env, jclass obj, jint akuContextId ) {
		AKUDeleteContext ( akuContextId );
	}

	//----------------------------------------------------------------//
	extern "C" void Java_@PACKAGE_UNDERSCORED@_MoaiView_AKUDetectGfxContext ( JNIEnv* env, jclass obj ) {
		AKUDetectGfxContext ();
	}

	//----------------------------------------------------------------//
	extern "C" void Java_@PACKAGE_UNDERSCORED@_MoaiActivity_AKUAppDidStartSession ( JNIEnv* env, jclass obj ) {
		MOAIApp::Get ().DidStartSession ();
	}

	//----------------------------------------------------------------//
	extern "C" void Java_@PACKAGE_UNDERSCORED@_MoaiActivity_AKUAppWillEndSession ( JNIEnv* env, jclass obj ) {
		MOAIApp::Get ().WillEndSession ();
	}
	
	//----------------------------------------------------------------//
	extern "C" void Java_@PACKAGE_UNDERSCORED@_MoaiActivity_AKUEnqueueCompassEvent ( JNIEnv* env, jclass obj, jint deviceId, jint sensorId, jint heading ) {

		InputEvent ievent;

		ievent.m_type = InputEvent::INPUTEVENT_COMPASS;

		ievent.m_deviceId = deviceId;
		ievent.m_sensorId = sensorId;

		ievent.m_heading = heading;

		g_InputQueue->Push ( ievent );
		//AKUEnqueueCompassEvent ( deviceId, sensorId, heading );
	}

	//----------------------------------------------------------------//
	extern "C" void Java_@PACKAGE_UNDERSCORED@_MoaiActivity_AKUEnqueueLevelEvent ( JNIEnv* env, jclass obj, jint deviceId, jint sensorId, jfloat x, jfloat y, jfloat z ) {
		
		InputEvent ievent;

		ievent.m_type = InputEvent::INPUTEVENT_LEVEL;

		ievent.m_deviceId = deviceId;
		ievent.m_sensorId = sensorId;

		ievent.m_x = x;
		ievent.m_y = y;
		ievent.m_z = z;

		g_InputQueue->Push ( ievent );
		//AKUEnqueueLevelEvent ( deviceId, sensorId, x, y, z );
	}

	//----------------------------------------------------------------//
	extern "C" void Java_@PACKAGE_UNDERSCORED@_MoaiActivity_AKUEnqueueLocationEvent ( JNIEnv* env, jclass obj, jint deviceId, jint sensorId, jdouble longitude, jdouble latitude, jdouble altitude, jfloat hAccuracy, jfloat vAccuracy, jfloat speed ) {
		
		InputEvent ievent;

		ievent.m_type = InputEvent::INPUTEVENT_LOCATION;

		ievent.m_deviceId = deviceId;
		ievent.m_sensorId = sensorId;

		ievent.m_longitude = longitude;
		ievent.m_latitude = latitude;
		ievent.m_altitude = altitude;
		ievent.m_hAccuracy = hAccuracy;
		ievent.m_vAccuracy = vAccuracy;
		ievent.m_speed = speed ;
		
		g_InputQueue->Push ( ievent );
		//AKUEnqueueLocationEvent ( deviceId, sensorId, longitude, latitude, altitude, hAccuracy, vAccuracy, speed );
	}

	//----------------------------------------------------------------//
	extern "C" void Java_@PACKAGE_UNDERSCORED@_MoaiView_AKUEnqueueTouchEvent ( JNIEnv* env, jclass obj, jint deviceId, jint sensorId, jint touchId, jboolean down, jint x, jint y, jint tapCount ) {
		InputEvent ievent;

		ievent.m_type = InputEvent::INPUTEVENT_TOUCH;

		ievent.m_deviceId = deviceId;
		ievent.m_sensorId = sensorId;

		ievent.m_touchId = touchId;
		ievent.m_down = down;
		ievent.m_x = x;
		ievent.m_y = y;
		ievent.m_tapCount = tapCount;

		g_InputQueue->Push ( ievent );
		//AKUEnqueueTouchEvent ( deviceId, sensorId, touchId, down, x, y, tapCount );
	}

	//----------------------------------------------------------------//
	extern "C" void Java_@PACKAGE_UNDERSCORED@_MoaiActivity_AKUFinalize	( JNIEnv* env, jclass obj ) {
		AKUFinalize ();
	}

	//----------------------------------------------------------------//
	extern "C" void Java_@PACKAGE_UNDERSCORED@_MoaiView_AKUExtLoadLuacrypto ( JNIEnv* env, jclass obj ) {
		AKUExtLoadLuacrypto ();
	}

	//----------------------------------------------------------------//
	extern "C" void Java_@PACKAGE_UNDERSCORED@_MoaiView_AKUExtLoadLuacurl ( JNIEnv* env, jclass obj ) {
		AKUExtLoadLuacurl ();
	}

	//----------------------------------------------------------------//
	extern "C" void Java_@PACKAGE_UNDERSCORED@_MoaiView_AKUExtLoadLuasocket ( JNIEnv* env, jclass obj ) {
		AKUExtLoadLuasocket ();
	}

	//----------------------------------------------------------------//
	extern "C" void Java_@PACKAGE_UNDERSCORED@_MoaiView_AKUExtLoadLuasql ( JNIEnv* env, jclass obj ) {
		AKUExtLoadLuasql ();
	}

	//----------------------------------------------------------------//
	extern "C" void Java_@PACKAGE_UNDERSCORED@_MoaiView_AKUInit ( JNIEnv* env, jclass obj, jobject moaiView, jobject moaiActivity, jobject moaiFacebook ) {

		// create MOAIApp class
		MOAIApp::Affirm ();
		REGISTER_LUA_CLASS ( MOAIApp );

#ifndef DISABLE_TAPJOY
		MOAITapjoy::Affirm ();
		REGISTER_LUA_CLASS ( MOAITapjoy );
#endif

#ifndef DISABLE_CRITTERCISM
		MOAICrittercism::Affirm ();
		REGISTER_LUA_CLASS ( MOAICrittercism );
#endif

		// register callbacks into Java
		mMoaiView = ( jobject ) env->NewGlobalRef ( moaiView );
		jclass moaiViewClass = env->GetObjectClass ( mMoaiView );
		
		g_InputQueue = new LockingQueue<InputEvent> ();
		mGenerateGuidFunc = env->GetMethodID ( moaiViewClass, "getGUID", "()Ljava/lang/String;" );

		MOAIApp::Get ().SetCheckBillingSupportedFunc( &CheckBillingSupported );
		MOAIApp::Get ().SetConfirmNotificationFunc( &ConfirmNotification );
		MOAIApp::Get ().SetOpenURLFunc( &OpenURL );
		MOAIApp::Get ().SetMarketPublicKeyFunc( &SetMarketPublicKey );
		MOAIApp::Get ().SetRegisterNotificationsFunc( &RequestNotifications );
		MOAIApp::Get ().SetRequestPurchaseFunc( &RequestPurchase );
		MOAIApp::Get ().SetRestoreTransactionsFunc( &RestoreTransactions );
		MOAIApp::Get ().SetShowDialogFunc( &ShowDialog );
		MOAIApp::Get ().SetShareFunc( &Share );

		mMoaiActivity = ( jobject ) env->NewGlobalRef ( moaiActivity );
		jclass moaiActivityClass = env->GetObjectClass ( mMoaiActivity );

		mCheckBillingSupportedFunc = env->GetMethodID ( moaiActivityClass, "checkBillingSupported", "()Z" );
		mConfirmNotificationFunc = env->GetMethodID ( moaiActivityClass, "confirmNotification", "(Ljava/lang/String;)Z" );
		mOpenURLFunc = env->GetMethodID ( moaiActivityClass, "openURL", "(Ljava/lang/String;)V" );
		mRegisterNotificationsFunc =  env->GetMethodID ( moaiActivityClass, "registerNotifications", "(I)V");
		mRequestPurchaseFunc = env->GetMethodID ( moaiActivityClass, "requestPurchase", "(Ljava/lang/String;Ljava/lang/String;)Z" );
		mRestoreTransactionsFunc = env->GetMethodID ( moaiActivityClass, "restoreTransactions", "()Z" );
		mSetMarketPublicKeyFunc = env->GetMethodID ( moaiActivityClass, "setMarketPublicKey", "(Ljava/lang/String;)V" );
		mShowDialogFunc = env->GetMethodID ( moaiActivityClass, "showDialog", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Z)V" );
		mShareFunc = env->GetMethodID ( moaiActivityClass, "share", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V" );

		lua_State* state  = AKUGetLuaState();

#ifndef DISABLE_FLURRY
		// Flurry
		mFlurryClass = (jclass)env->NewGlobalRef( env->FindClass ( "com/flurry/android/FlurryAgent" ) );
		mFlurryLogEvent = env->GetStaticMethodID ( mFlurryClass, "logEvent", "(Ljava/lang/String;)V" );
		mFlurryLogEventTimed = env->GetStaticMethodID ( mFlurryClass, "logEvent", "(Ljava/lang/String;Z)V" );
		mFlurryOnError = env->GetStaticMethodID ( mFlurryClass, "onError", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V" );
		mFlurryEndTimedEvent = env->GetStaticMethodID ( mFlurryClass, "endTimedEvent", "(Ljava/lang/String;)V" );
		mFlurrySetUserID = env->GetStaticMethodID ( mFlurryClass, "setUserId", "(Ljava/lang/String;)V" );
		mFlurrySetAge = env->GetStaticMethodID ( mFlurryClass, "setAge", "(I)V");
		mFlurrySetGender = env->GetStaticMethodID ( mFlurryClass, "setGender", "(B)V");

		{		
			luaL_Reg regTable [] = {
				{ "logEvent",		Flurry_logEvent },
				{ "logTimedEvent",	Flurry_logTimedEvent },
				{ "endTimedEvent",	Flurry_endTimedEvent },
				{ "logError",		Flurry_logError },
				{ "userInfo",		Flurry_userInfo },
				{ NULL, NULL }
			};
	
			luaL_register( state, "Flurry", regTable );
			lua_pop(state, 1);
		}
#endif

#ifndef DISABLE SIXWAVES
		// SixWaves
		mSixWavesCrossSell  = env->GetMethodID ( moaiActivityClass, "swCrossSell", "()V" );
		mSixWavesHideAdBanner = env->GetMethodID ( moaiActivityClass, "swHideAdBanner", "()V" );
		mSixWavesHideCrossSellBtn = env->GetMethodID ( moaiActivityClass, "swHideCrossSellBtn", "()V" );
		mSixWavesShowAdBanner = env->GetMethodID ( moaiActivityClass, "swShowAdBanner", "()V" );
		mSixWavesShowCrossSellBtn = env->GetMethodID ( moaiActivityClass, "swShowCrossSellBtn", "()V" );
		mSixWavesTrackPurchaseEvent = env->GetMethodID ( moaiActivityClass, "swTrackPurchaseEvent", "(Ljava/lang/String;F)V" );
		mSixWavesTrackInGameItemPurchase = env->GetMethodID ( moaiActivityClass, "swTrackInGameItemPurchase", "(Ljava/lang/String;[Ljava/lang/Object;)V" );
		mSixWavesTrackTutorialEvent = env->GetMethodID ( moaiActivityClass, "swTrackTutorialEvent", "(Ljava/lang/String;)V" );
		{
			luaL_Reg regTable [] = {
				{ "crossSell",		SixWaves_crossSell },
				{ "hideAdBanner",   SixWaves_hideAdBanner },
				{ "hideCrossSellBtn", SixWaves_hideCrossSellBtn },
				{ "showAdBanner",   SixWaves_showAdBanner },
				{ "showCrossSellBtn", SixWaves_showCrossSellBtn },
				{ "trackPurchaseEvent", SixWaves_trackPurchaseEvent },
				{ "trackInGameItemPurchase", SixWaves_trackInGameItemPurchaseWithItem },
				{ "trackTutorialEvent", SixWaves_trackTutorialEvent },
				{ NULL, NULL }
			};
			
			
			luaL_register(state, "SixWaves", regTable);
			lua_pop(state, 1);
		}
#endif

#ifndef DIABLE_FACEBOOK
		// Facebook social connect
		mFBClass = env->FindClass ( "com/sixwaves/strikefleetomega/MoaiFacebook" );
		mFBObject = ( jobject ) env->NewGlobalRef(moaiFacebook);
		mFBAPIFunc = env->GetMethodID ( mFBClass, "api", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;J)V" );
		mFBGetLoginStatusFunc = env->GetMethodID ( mFBClass, "getLoginStatus", "()V" );
		mFBIsInitializedFunc = env->GetMethodID ( mFBClass, "isInitialized", "()Z" );
		mFBIsSessionValidFunc = env->GetMethodID ( mFBClass, "isSessionValid", "()Z" );
		mFBInitFunc = env->GetMethodID ( mFBClass, "init", "(Ljava/lang/String;)V" );
		mFBLoginFunc = env->GetMethodID ( mFBClass, "login", "(Ljava/lang/String;)V" );
		mFBLogoutFunc = env->GetMethodID ( mFBClass, "logout", "()V" );
		mMoaiFlurryLogEvent  = env->GetMethodID ( moaiActivityClass, "FlurryLogEvent", "(Ljava/lang/String;[Ljava/lang/Object;)V" );
		{
			luaL_Reg regTable [] = {
				{ "api",	FB_api },
				{ "getLoginStatus", FB_getLoginStatus},
				{ "init", FB_init},
				{ "login", FB_login},
				{ "logout", FB_logout},
				{ NULL, NULL }
			};
			luaL_register( state, "FB", regTable );
		}
#endif
	}

	//----------------------------------------------------------------//
	extern "C" void Java_@PACKAGE_UNDERSCORED@_MoaiActivity_AKUMountVirtualDirectory ( JNIEnv* env, jclass obj, jstring jvirtualPath, jstring jarchive ) {
		GET_CSTRING ( jvirtualPath, virtualPath );
		GET_CSTRING ( jarchive, archive );
		AKUMountVirtualDirectory ( virtualPath, archive );
		RELEASE_CSTRING ( jvirtualPath, virtualPath );
		RELEASE_CSTRING ( jarchive, archive );
	}

	//----------------------------------------------------------------//
	extern "C" void Java_@PACKAGE_UNDERSCORED@_MoaiActivity_AKUNotifyBillingSupported ( JNIEnv* env, jclass obj, jboolean supported ) {
		MOAIApp::Get ().NotifyBillingSupported ( supported );
	}
	
	//----------------------------------------------------------------//
	extern "C" void Java_@PACKAGE_UNDERSCORED@_MoaiActivity_AKUNotifyDidRegisterNotifications ( JNIEnv* env, jclass obj, jstring jtoken ) {
		GET_CSTRING ( jtoken, token );
		MOAIApp::Get ().NotifyDidRegisterNotifications ( token );
		RELEASE_CSTRING ( jtoken, token );
	}
	
	//----------------------------------------------------------------//
	extern "C" void Java_@PACKAGE_UNDERSCORED@_MoaiActivity_AKUNotifyOnRemoteNotification  ( JNIEnv* env, jclass obj, jstring jdata ) {
		GET_CSTRING ( jdata, data );
		MOAIApp::Get ().NotifyOnRemoteNotification ( data );
		RELEASE_CSTRING ( jdata, data );
	}
	
	//----------------------------------------------------------------//
	extern "C" void Java_@PACKAGE_UNDERSCORED@_MoaiActivity_AKUNotifyPurchaseResponseReceived ( JNIEnv* env, jclass obj, jstring jidentifier, jint code ) {
		GET_CSTRING ( jidentifier, identifier );

		MOAIApp::Get ().NotifyPurchaseResponseReceived ( identifier, code );

		RELEASE_CSTRING ( jidentifier, identifier );
	}

	//----------------------------------------------------------------//
	extern "C" void Java_@PACKAGE_UNDERSCORED@_MoaiActivity_AKUNotifyPurchaseStateChanged ( JNIEnv* env, jclass obj, jstring jidentifier, jint code, jstring jorder, jstring jnotification, jstring jpayload ) {
		GET_CSTRING ( jidentifier, identifier );
		GET_CSTRING ( jorder, order );
		GET_CSTRING ( jnotification, notification );
		GET_CSTRING ( jpayload, payload );
		
		MOAIApp::Get ().NotifyPurchaseStateChanged ( identifier, code, order, notification, payload );

		RELEASE_CSTRING ( jidentifier, identifier );
		RELEASE_CSTRING ( jorder, order );
		RELEASE_CSTRING ( jnotification, notification );
		RELEASE_CSTRING ( jpayload, payload );
	}
		
	//----------------------------------------------------------------//
	extern "C" void Java_@PACKAGE_UNDERSCORED@_MoaiActivity_AKUNotifyRestoreResponseReceived ( JNIEnv* env, jclass obj, jint code ) {
		MOAIApp::Get ().NotifyRestoreResponseReceived ( code );
	}

	//----------------------------------------------------------------//
	extern "C" bool Java_@PACKAGE_UNDERSCORED@_MoaiActivity_AKUNotifyBackButtonPressed ( JNIEnv* env, jclass obj ) {
		return MOAIApp::Get ().NotifyBackButtonPressed ();
	}
	
	//----------------------------------------------------------------//
	extern "C" void Java_@PACKAGE_UNDERSCORED@_MoaiActivity_AKUNotifyOnPauseCalled ( JNIEnv* env, jclass obj ) {
		MOAIApp::Get ().NotifyOnPauseCalled ();
	}
	
	//----------------------------------------------------------------//
	extern "C" void Java_@PACKAGE_UNDERSCORED@_MoaiActivity_AKUNotifyDialogDismissed ( JNIEnv* env, jclass obj, jint code ) {
		MOAIApp::Get ().NotifyDialogDismissed ( code );
	}

	//----------------------------------------------------------------//
	extern "C" void Java_@PACKAGE_UNDERSCORED@_MoaiActivity_AKUNotifyVideoAdReady ( JNIEnv* env, jclass obj ) {
		MOAITapjoy::Get ().NotifyVideoAdReady ();
	}

	//----------------------------------------------------------------//
	extern "C" void Java_@PACKAGE_UNDERSCORED@_MoaiActivity_AKUNotifyVideoAdError ( JNIEnv* env, jclass obj, jint code ) {
		MOAITapjoy::Get ().NotifyVideoAdError ( code );
	}
	
	//----------------------------------------------------------------//
	extern "C" void Java_@PACKAGE_UNDERSCORED@_MoaiActivity_AKUNotifyVideoAdClose ( JNIEnv* env, jclass obj ) {
		MOAITapjoy::Get ().NotifyVideoAdClose ();
	}
	
	//----------------------------------------------------------------//
	extern "C" void Java_@PACKAGE_UNDERSCORED@_MoaiView_AKUPause ( JNIEnv* env, jclass obj, jboolean paused ) {
		AKUPause ( paused );

		if ( paused ) {
		
			AKUUntzSuspend ();
		} else {
		
			AKUUntzResume ();
		}		
	}

	//----------------------------------------------------------------//
	extern "C" void Java_@PACKAGE_UNDERSCORED@_MoaiView_AKURender ( JNIEnv* env, jclass obj ) {
		AKURender ();
	}

	//----------------------------------------------------------------//
	extern "C" void Java_@PACKAGE_UNDERSCORED@_MoaiView_AKUReserveInputDevices ( JNIEnv* env, jclass obj, jint total ) {
		AKUReserveInputDevices ( total );
	}

	//----------------------------------------------------------------//
	extern "C" void Java_@PACKAGE_UNDERSCORED@_MoaiView_AKUReserveInputDeviceSensors ( JNIEnv* env, jclass obj, jint deviceId, jint total ) {
		AKUReserveInputDeviceSensors ( deviceId, total );
	}

	//----------------------------------------------------------------//
	extern "C" void Java_@PACKAGE_UNDERSCORED@_MoaiView_AKURunScript ( JNIEnv* env, jclass obj, jstring jfilename ) {
		GET_CSTRING ( jfilename, filename );
		AKURunScript ( filename );
		RELEASE_CSTRING ( jfilename, filename );
	}

	//----------------------------------------------------------------//
	extern "C" void Java_@PACKAGE_UNDERSCORED@_MoaiActivity_AKUSetConnectionType ( JNIEnv* env, jclass obj, jlong connectionType ) {
		MOAIEnvironment::Get ().SetConnectionType ( connectionType );
	}

	//----------------------------------------------------------------//
	extern "C" void Java_@PACKAGE_UNDERSCORED@_MoaiView_AKUSetContext ( JNIEnv* env, jclass obj, jint akuContextId ) {
		AKUSetContext ( akuContextId );
	}
	
	//----------------------------------------------------------------//
	extern "C" void Java_@PACKAGE_UNDERSCORED@_MoaiView_AKUSetDeviceProperties ( JNIEnv* env, jclass obj, jstring jappName, jstring jappId, jstring jappVersion, jstring jabi, jstring jdevBrand, jstring jdevName, jstring jdevManufacturer, jstring jdevModel, jstring jdevProduct, jint jnumProcessors, jstring josBrand, jstring josVersion, jstring judid ) {

		// get the environment
		MOAIEnvironment& moaiEnv = MOAIEnvironment::Get ();
	
		// set up environment callbacks
		moaiEnv.SetGUIDFunc ( &GenerateGUID );

		// convert jstrings to cstrings
		GET_CSTRING ( jappName, appName );
		GET_CSTRING ( jappId, appId );
		GET_CSTRING ( jappVersion, appVersion );
		GET_CSTRING ( jabi, abi );
		GET_CSTRING ( jdevBrand, devBrand );
		GET_CSTRING ( jdevName, devName );
		GET_CSTRING ( jdevManufacturer, devManufacturer );
		GET_CSTRING ( jdevModel, devModel );
		GET_CSTRING ( jdevProduct, devProduct );
		GET_CSTRING ( josBrand, osBrand );
		GET_CSTRING ( josVersion, osVersion );
		GET_CSTRING ( judid, udid );
	
		// set environment properties
		moaiEnv.SetAppDisplayName 	( appName );
		moaiEnv.SetAppID 			( appId );
		moaiEnv.SetAppVersion		( appVersion );
		moaiEnv.SetCPUABI 			( abi );
		moaiEnv.SetDevBrand 		( devBrand );
		moaiEnv.SetDevName 			( devName );
		moaiEnv.SetDevManufacturer	( devManufacturer );
		moaiEnv.SetDevModel			( devModel );
		moaiEnv.SetDevProduct		( devProduct );
		moaiEnv.SetNumProcessors	( jnumProcessors );
		moaiEnv.SetOSBrand			( osBrand );
		moaiEnv.SetOSVersion		( osVersion );
		moaiEnv.SetUDID				( udid );

		// release jstrings
		RELEASE_CSTRING ( jappName, appName );
		RELEASE_CSTRING ( jappId, appId );
		RELEASE_CSTRING ( jappVersion, appVersion );
		RELEASE_CSTRING ( jabi, abi );
		RELEASE_CSTRING ( jdevBrand, devBrand );
		RELEASE_CSTRING ( jdevName, devName );
		RELEASE_CSTRING ( jdevManufacturer, devManufacturer );
		RELEASE_CSTRING ( jdevModel, devModel );
		RELEASE_CSTRING ( jdevProduct, devProduct );
		RELEASE_CSTRING ( josBrand, osBrand );
		RELEASE_CSTRING ( josVersion, osVersion );
		RELEASE_CSTRING ( judid, udid );
	}

	//----------------------------------------------------------------//
	extern "C" void Java_@PACKAGE_UNDERSCORED@_MoaiActivity_AKUSetDocumentDirectory ( JNIEnv* env, jclass obj, jstring jpath ) {
		GET_CSTRING ( jpath, path );
		MOAIEnvironment::Get ().SetDocumentDirectory ( path );
		RELEASE_CSTRING ( jpath, path );
	}

	//----------------------------------------------------------------//
	extern "C" void Java_@PACKAGE_UNDERSCORED@_MoaiView_AKUSetInputConfigurationName ( JNIEnv* env, jclass obj, jstring jname ) {
		GET_CSTRING ( jname, name );
		AKUSetInputConfigurationName ( name );
		RELEASE_CSTRING ( jname, name );
	}

	//----------------------------------------------------------------//
	extern "C" void Java_@PACKAGE_UNDERSCORED@_MoaiView_AKUSetInputDevice ( JNIEnv* env, jclass obj, jint deviceId, jstring jname ) {
		GET_CSTRING ( jname, name );
		AKUSetInputDevice ( deviceId, name );
		RELEASE_CSTRING ( jname, name );
	}
	//----------------------------------------------------------------//
	extern "C" void Java_@PACKAGE_UNDERSCORED@_MoaiView_AKUSetInputDeviceCompass ( JNIEnv* env, jclass obj, jint deviceId, jint sensorId, jstring jname ) {
		GET_CSTRING ( jname, name );
		AKUSetInputDeviceCompass ( deviceId, sensorId, name );
		RELEASE_CSTRING ( jname, name );
	}

	//----------------------------------------------------------------//
	extern "C" void Java_@PACKAGE_UNDERSCORED@_MoaiView_AKUSetInputDeviceLevel ( JNIEnv* env, jclass obj, jint deviceId, jint sensorId, jstring jname ) {
		GET_CSTRING ( jname, name );
		AKUSetInputDeviceLevel ( deviceId, sensorId, name );
		RELEASE_CSTRING ( jname, name );
	}

	//----------------------------------------------------------------//
	extern "C" void Java_@PACKAGE_UNDERSCORED@_MoaiView_AKUSetInputDeviceLocation ( JNIEnv* env, jclass obj, jint deviceId, jint sensorId, jstring jname ) {
		GET_CSTRING ( jname, name );
		AKUSetInputDeviceLocation ( deviceId, sensorId, name );
		RELEASE_CSTRING ( jname, name );
	}
	
	//----------------------------------------------------------------//
	extern "C" void Java_@PACKAGE_UNDERSCORED@_MoaiView_AKUSetInputDeviceTouch ( JNIEnv* env, jclass obj, jint deviceId, jint sensorId, jstring jname ) {
		GET_CSTRING ( jname, name );
		AKUSetInputDeviceTouch ( deviceId, sensorId, name );
		RELEASE_CSTRING ( jname, name );
	}
	//----------------------------------------------------------------//
	extern "C" void Java_@PACKAGE_UNDERSCORED@_MoaiView_AKUSetScreenDpi ( JNIEnv* env, jclass obj, jint dpi ) {
		AKUSetScreenDpi ( dpi );
	}
	//----------------------------------------------------------------//
	extern "C" void Java_@PACKAGE_UNDERSCORED@_MoaiView_AKUSetScreenSize ( JNIEnv* env, jclass obj, jint width, jint height ) {
		AKUSetScreenSize ( width, height );
	}

	//----------------------------------------------------------------//
	extern "C" void Java_@PACKAGE_UNDERSCORED@_MoaiView_AKUSetViewSize ( JNIEnv* env, jclass obj, jint width, jint height ) {
		AKUSetViewSize ( width, height );
	}

	//----------------------------------------------------------------//
	extern "C" void Java_@PACKAGE_UNDERSCORED@_MoaiView_AKUSetWorkingDirectory ( JNIEnv* env, jclass obj, jstring jpath ) {

		GET_CSTRING ( jpath, path );

		USFileSys::SetCurrentPath ( path );
		MOAILuaRuntime::Get ().SetPath ( path );
	
		RELEASE_CSTRING ( jpath, path );
	}

	//----------------------------------------------------------------//
	extern "C" void Java_@PACKAGE_UNDERSCORED@_MoaiView_AKUUntzInit ( JNIEnv* env, jclass obj ) {
		AKUUntzInit ();
	}
	
	//----------------------------------------------------------------//
	extern "C" void Java_@PACKAGE_UNDERSCORED@_MoaiView_AKUUpdate ( JNIEnv* env, jclass obj ) {

		InputEvent ievent;
		while ( g_InputQueue->PopMessage ( ievent )) {
			switch ( ievent.m_type ) {
			case InputEvent::INPUTEVENT_TOUCH:
				AKUEnqueueTouchEvent ( ievent.m_deviceId, ievent.m_sensorId, ievent.m_touchId, ievent.m_down, ievent.m_x, ievent.m_y, ievent.m_tapCount );
				break;
			case InputEvent::INPUTEVENT_LEVEL:
				AKUEnqueueLevelEvent ( ievent.m_deviceId, ievent.m_sensorId, ievent.m_x, ievent.m_y, ievent.m_z );
				break;
			case InputEvent::INPUTEVENT_COMPASS:
				AKUEnqueueCompassEvent ( ievent.m_deviceId, ievent.m_sensorId, ievent.m_heading );
				break;
			case InputEvent::INPUTEVENT_LOCATION:
				AKUEnqueueLocationEvent ( ievent.m_deviceId, ievent.m_sensorId, ievent.m_longitude, ievent.m_latitude, ievent.m_altitude, ievent.m_hAccuracy, ievent.m_vAccuracy, ievent.m_speed );
				break;
			}
		}

		AKUUpdate ();
	}
	
	//----------------------------------------------------------------//
	extern "C" void Java_@PACKAGE_UNDERSCORED@_MoaiFacebook_FBAPICallback ( JNIEnv* env, jclass obj, jstring jresult, long callbackAddr ) {
		
		//std::map<long, MOAILuaRef>::iterator entry = mFBCallbackMap.find(callbackAddr);
		if(mFBCallbackMap.find(callbackAddr) != mFBCallbackMap.end())
		{
			MOAILuaRef& callback = mFBCallbackMap[callbackAddr];
			if( callback && !callback.IsNil() ) {
				MOAILuaStateHandle state = callback.GetSelf();
				callback.Clear();
				GET_CSTRING ( jresult, result );
				lua_pushstring(state, result);
				state.DebugCall( 1 , 0 );
				RELEASE_CSTRING ( jresult, result );
			}
		}
	}
	//----------------------------------------------------------------//
	extern "C" void Java_@PACKAGE_UNDERSCORED@_MoaiFacebook_FBLoginStatusCallback ( JNIEnv* env, jclass obj, jstring jresult ) {
		MOAILuaRef& callback = fbLoginCallback;
		if( callback && !callback.IsNil() ) {
			MOAILuaStateHandle state = callback.GetSelf();
			callback.Clear();
			GET_CSTRING ( jresult, result );
			lua_pushstring(state, result);
			state.DebugCall( 1 , 0 );
			RELEASE_CSTRING ( jresult, result );
		}
	}
	//----------------------------------------------------------------//
	extern "C" void Java_@PACKAGE_UNDERSCORED@_MoaiFacebook_FBLoginCallback ( JNIEnv* env, jclass obj, jstring jresult ) {
		MOAILuaRef& callback = fbLoginCallback;
		if( callback  && !callback.IsNil() ) {
			MOAILuaStateHandle state = callback.GetSelf();
			callback.Clear();
			GET_CSTRING ( jresult, result );
			lua_pushstring(state, result);
			state.DebugCall( 1 , 0 );
			RELEASE_CSTRING ( jresult, result );
		}
	}
