#include <jni.h>
#include <android/native_window_jni.h>
#include "JniHelper.h"
#include "TriangleManager.h"

#ifndef _Included_com_zone_triangle_TriangleRenderer
#define _Included_com_zone_triangle_TriangleRenderer
#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void JNICALL Java_com_zone_triangle_TriangleRenderer_nativeOnCreate(JNIEnv *env, jclass thiz)
{
	if (TriangleManager::getSingletonPtr() == nullptr) {
        new TriangleManager();
    }
    TriangleManager::getSingleton().onCreate();
}

JNIEXPORT void JNICALL Java_com_zone_triangle_TriangleRenderer_nativeOnResume(JNIEnv *env, jclass thiz)
{
	 TriangleManager::getSingleton().onResume();
}

JNIEXPORT void JNICALL Java_com_zone_triangle_TriangleRenderer_nativeOnPause(JNIEnv *env, jclass thiz)
{
	TriangleManager::getSingleton().onPause();
}

JNIEXPORT void JNICALL Java_com_zone_triangle_TriangleRenderer_nativeOnStop(JNIEnv *env, jclass thiz)
{
	TriangleManager::getSingleton().onStop();
}

JNIEXPORT void JNICALL Java_com_zone_triangle_TriangleRenderer_nativeOnDestroy(JNIEnv *env, jclass thiz)
{
	TriangleManager::getSingleton().onDestroy();
}

JNIEXPORT void JNICALL Java_com_zone_triangle_TriangleRenderer_nativeInitGL(JNIEnv *env, jobject thiz, jint width, jint height)
{
	TriangleManager::getSingleton().initGL(width, height);
}

JNIEXPORT void JNICALL Java_com_zone_triangle_TriangleRenderer_nativeDrawFrame(JNIEnv *env, jclass thiz)
{
	 TriangleManager::getSingleton().drawFrame();
}

JNIEXPORT void JNICALL Java_com_zone_triangle_TriangleRenderer_nativeOnSurfaceChanged(JNIEnv *env, jobject thiz, jint width, jint height)
{
	TriangleManager::getSingleton().onChange(width, height);
}

JNIEXPORT jintArray JNICALL Java_com_zone_triangle_TriangleRenderer_nativeGetTextures(JNIEnv *env, jclass thiz)
{
    jintArray textures = env->NewIntArray(2);
    jint *elems = env->GetIntArrayElements(textures, NULL);
    elems[0] = TriangleManager::getSingleton().getCameraTextureId();
    elems[1] = TriangleManager::getSingleton().getTextureId();
    env->ReleaseIntArrayElements(textures, elems, 0);
    return textures;
}

JNIEXPORT void JNICALL Java_com_zone_triangle_TriangleRenderer_nativeSetAssetBmp(JNIEnv *env, jobject thiz, jobject assetManager, jstring fileName)
{
    AAssetManager* mgr = AAssetManager_fromJava(env, assetManager);
    const char* textureFilePath = env->GetStringUTFChars(fileName, JNI_FALSE);
    TriangleManager::getSingleton().setAssetsBmp(mgr, textureFilePath);
    env->ReleaseStringUTFChars(fileName, textureFilePath);
}

#ifdef __cplusplus
}
#endif
#endif
