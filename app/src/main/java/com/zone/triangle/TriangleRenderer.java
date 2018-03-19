package com.zone.triangle;

import android.content.Context;
import android.content.res.AssetManager;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.opengl.GLES20;
import android.opengl.GLSurfaceView;
import android.opengl.GLUtils;
import android.util.Log;

import java.io.IOException;
import java.io.InputStream;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;
import javax.security.auth.login.LoginException;

/**
 * @authon 赖忠安
 * Create on 2018/3/14.
 */

public class TriangleRenderer implements GLSurfaceView.Renderer {
    private static final String TAG = "TriangleRenderer";
    private static final int MAX_PREVIEW_WIDTH = 1080;
    private static final int MAX_PREVIEW_HEIGHT = 1920;
    private Context mContext;

    static {
        System.loadLibrary("Triangle");
    }

    public TriangleRenderer(Context context) {
        mContext = context;
        nativeOnCreate();
    }

    @Override
    public void onSurfaceCreated(GL10 gl10, EGLConfig eglConfig) {
        nativeInitGL(MAX_PREVIEW_WIDTH, MAX_PREVIEW_HEIGHT);
        try {
            InputStream inputStream = mContext.getAssets().open("cat.bmp");
            Bitmap bitmap = BitmapFactory.decodeStream(inputStream);
            GLES20.glBindTexture(GLES20.GL_TEXTURE_2D, nativeGetTextures()[0]);
            GLUtils.texImage2D(GLES20.GL_TEXTURE_2D, 0, bitmap, 0);
            bitmap.recycle();
            inputStream.close();

            InputStream inputStream1 = mContext.getAssets().open("wood.bmp");
            Bitmap bitmap1 = BitmapFactory.decodeStream(inputStream1);
            GLES20.glBindTexture(GLES20.GL_TEXTURE_2D, nativeGetTextures()[1]);
            GLUtils.texImage2D(GLES20.GL_TEXTURE_2D, 0, bitmap1, 0);
            bitmap1.recycle();
            inputStream1.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        nativeOnSurfaceChanged(width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl10) {
        nativeDrawFrame();
    }

    public void onStop() {
        nativeOnStop();
    }

    public void onDestroy() {
        nativeOnDestroy();
    }


    private static native void nativeOnCreate();

    private static native void nativeOnResume();

    private static native void nativeOnPause();

    private static native void nativeOnStop();

    private static native void nativeOnDestroy();

    private static native void nativeInitGL(int widgetWidth, int widgetHeight);

    private static native void nativeDrawFrame();

    private static native void nativeOnSurfaceChanged(int widgetWidth, int widgetHeight);

    private static native int[] nativeGetTextures();

    private static native void nativeSetAssetBmp(AssetManager assetManager, String fileName);
}
