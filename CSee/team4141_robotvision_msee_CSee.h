/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class team4141_robotvision_msee_CSee */

#ifndef _Included_team4141_robotvision_msee_CSee
#define _Included_team4141_robotvision_msee_CSee
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     team4141_robotvision_msee_CSee
 * Method:    init
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_team4141_robotvision_msee_CSee_init
  (JNIEnv *, jobject);

/*
 * Class:     team4141_robotvision_msee_CSee
 * Method:    start
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_team4141_robotvision_msee_CSee_start
  (JNIEnv *, jobject);

/*
 * Class:     team4141_robotvision_msee_CSee
 * Method:    stop
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_team4141_robotvision_msee_CSee_stop
  (JNIEnv *, jobject);

/*
 * Class:     team4141_robotvision_msee_CSee
 * Method:    switchTo
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_team4141_robotvision_msee_CSee_switchTo
  (JNIEnv *, jobject, jstring);

/*
 * Class:     team4141_robotvision_msee_CSee
 * Method:    setCameraProperty
 * Signature: (IILjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_team4141_robotvision_msee_CSee_setCameraProperty
  (JNIEnv *, jobject, jint, jint, jstring);

/*
 * Class:     team4141_robotvision_msee_CSee
 * Method:    setFilter
 * Signature: (Ljava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_team4141_robotvision_msee_CSee_setFilter
  (JNIEnv *, jobject, jstring, jstring);

/*
 * Class:     team4141_robotvision_msee_CSee
 * Method:    getConfig
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_team4141_robotvision_msee_CSee_getConfig
  (JNIEnv *, jobject);

#ifdef __cplusplus
}
#endif
#endif
