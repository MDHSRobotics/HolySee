/*
 * CSee.cpp
 *
 *  Created on: Oct 28, 2016
 *      Author: team4141
 */



#include "CSee.h"
#include "team4141_robotvision_msee_CSee.h"
#include "Streamer.h"
#include "LidarSource.h"
#include "VideoSource.h"
#include <memory>

//Globals
// cached refs for later callbacks

jobject g_obj;
JavaVM* jvm;
Streamer streamer;

JNIEXPORT void JNICALL Java_team4141_robotvision_msee_CSee_registerVideoSource
  (JNIEnv *j_env, jobject j_obj, jstring j_name, jstring j_device, jboolean j_showRaw, jstring j_arName, jstring j_cvName){
	const char * _name = j_env->GetStringUTFChars(j_name,NULL);
	const char * _device = j_env->GetStringUTFChars(j_device,NULL);
	const char * _arName = j_env->GetStringUTFChars(j_arName,NULL);
	const char * _cvName = j_env->GetStringUTFChars(j_cvName,NULL);
	std::string name(_name);
	std::string device(_device);
	std::string arName(_arName);
	std::string cvName(_cvName);
	j_env->ReleaseStringUTFChars(j_name,_name);
	j_env->ReleaseStringUTFChars(j_device,_device);
	j_env->ReleaseStringUTFChars(j_arName,_arName);
	j_env->ReleaseStringUTFChars(j_cvName,_cvName);
	bool showRaw = (bool)j_showRaw;
	std::shared_ptr<Source> v(new VideoSource(name,device,showRaw,arName,cvName));
	streamer.registerSource(v);
	printf("csee registering video %s[%s,%d,%s,%s]\n",name.c_str(),device.c_str(),showRaw,arName.c_str(),cvName.c_str());
}

JNIEXPORT void JNICALL Java_team4141_robotvision_msee_CSee_registerLidarSource
(JNIEnv *j_env, jobject j_obj, jstring j_name, jstring j_arName, jstring j_cvName){
	const char * _name = j_env->GetStringUTFChars(j_name,NULL);
	const char * _arName = j_env->GetStringUTFChars(j_arName,NULL);
	const char * _cvName = j_env->GetStringUTFChars(j_cvName,NULL);
	std::string name(_name);
	std::string arName(_arName);
	std::string cvName(_cvName);
	j_env->ReleaseStringUTFChars(j_name,_name);
	j_env->ReleaseStringUTFChars(j_arName,_arName);
	j_env->ReleaseStringUTFChars(j_cvName,_cvName);
	std::shared_ptr<Source> l(new LidarSource(name,arName,cvName));
	streamer.registerSource(l);
	printf("csee registering video %s[%s,%s]\n",name.c_str(),arName.c_str(),cvName.c_str());
}

JNIEXPORT jobjectArray JNICALL Java_team4141_robotvision_msee_CSee_getChannels
  (JNIEnv *j_env, jobject j_obj){
	jobjectArray j_channels;
	if(streamer.countChannels()<1) return (jobjectArray)NULL;

	j_channels = (jobjectArray) j_env->NewObjectArray(streamer.countChannels(),j_env->FindClass("java/lang/String"),j_env->NewStringUTF(""));
	for(int s=0;s<streamer.countChannels();s++){
		j_env->SetObjectArrayElement(j_channels,s,j_env->NewStringUTF(streamer.getChannelNames().at(s).c_str()));
	}
	return j_channels;
}

JNIEXPORT void JNICALL Java_team4141_robotvision_msee_CSee_init (JNIEnv *env, jobject jObj){
	//convert local to global reference
	g_obj = env->NewGlobalRef(jObj);
	env->GetJavaVM(&jvm);

//	std::cout << "JNI globals cached" << std::endl;


	JNIEnv* myNewEnv;
	jint getEnvStat = jvm->GetEnv((void**)&myNewEnv, JNI_VERSION_1_8);

	if(getEnvStat == JNI_EDETACHED){
		std::cout << "GetEnv: not attached" << std::endl;
		if(jvm->AttachCurrentThread((void **)&myNewEnv,NULL)!=0){
			std::cout << "Failed to attach" << std::endl;
		}
	}
	else if(getEnvStat == JNI_OK){
//		std::cout << "GetEnv: JNI OK" << std::endl;
	}
	else if(getEnvStat == JNI_EVERSION){
		std::cout << "GetEnv: JNI version not supported" << std::endl;
	}

//	save refs for callback
	jclass g_class = myNewEnv->GetObjectClass(jObj);
	if(g_class == NULL){
		std::cout << "Failed to find class" << std::endl;
	}

	jmethodID g_mid = myNewEnv->GetMethodID(g_class,"onInitialized", "()V");
	if(g_mid == NULL){
		std::cout << "Unable to get onInitialized() method ref" << std::endl;
	}

	//do initialization here ----------------

	streamer.initialize();

	//---------------------------------------

	myNewEnv->CallVoidMethod(g_obj, g_mid);   //call back to signify initialization is completed

	if(myNewEnv->ExceptionCheck()){
		myNewEnv->ExceptionDescribe();
	}
}


JNIEXPORT void JNICALL Java_team4141_robotvision_msee_CSee_start
  (JNIEnv *, jobject){
	std::cout<<"start streaming"<<std::endl;
}

JNIEXPORT void JNICALL Java_team4141_robotvision_msee_CSee_stop
  (JNIEnv *, jobject){
	std::cout<<"stop streaming"<<std::endl;

}

JNIEXPORT void JNICALL Java_team4141_robotvision_msee_CSee_switchTo
  (JNIEnv * env, jobject jObj, jstring jStreamName){
	const char *resultCStr = env->GetStringUTFChars(jStreamName, NULL);
	std::string streamName(resultCStr);
	env->ReleaseStringUTFChars(jStreamName, resultCStr);
	std::cout<<"switch to "<< streamName << std::endl;
}
