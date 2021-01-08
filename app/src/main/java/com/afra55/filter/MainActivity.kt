package com.afra55.filter

import android.app.Activity
import android.content.ContentValues
import android.content.Intent
import android.content.pm.PackageManager
import android.graphics.Bitmap
import android.graphics.drawable.Drawable
import android.media.MediaScannerConnection
import android.net.Uri
import android.os.Build
import android.os.Bundle
import android.os.Environment
import android.provider.MediaStore
import android.util.Log
import android.view.MotionEvent
import android.view.View
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import androidx.core.app.ActivityCompat
import androidx.core.view.isVisible
import com.bumptech.glide.Glide
import com.bumptech.glide.request.RequestListener
import com.bumptech.glide.request.target.CustomTarget
import com.bumptech.glide.request.transition.Transition
import kotlinx.android.synthetic.main.activity_main.*
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.GlobalScope
import kotlinx.coroutines.launch
import java.io.File
import java.io.FileOutputStream
import java.io.OutputStream
import java.lang.Exception
import java.util.concurrent.ConcurrentLinkedDeque


class MainActivity : AppCompatActivity() {

    var photoBitmap: Bitmap? = null
    var originBitmap: Bitmap? = null
    var cacheBitmapList: ConcurrentLinkedDeque<Bitmap> = ConcurrentLinkedDeque()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        // Example of a call to a native method
        sample_text.text = stringFromJNI()

        checkPermission()

        sample_text.setOnClickListener {
            if (checkPermission()) {

                val contentSelectionIntent = Intent(Intent.ACTION_GET_CONTENT)
                contentSelectionIntent.addCategory(Intent.CATEGORY_OPENABLE)
                contentSelectionIntent.type = "image/*"
                val chooserIntent = Intent(Intent.ACTION_CHOOSER)
                chooserIntent.putExtra(Intent.EXTRA_INTENT, contentSelectionIntent)
                chooserIntent.putExtra(Intent.EXTRA_TITLE, "Image Chooser")
                startActivityForResult(chooserIntent, 1)
            }
        }


        sample_image_container.setOnTouchListener { v, event ->
            when (event.action) {
                MotionEvent.ACTION_DOWN -> {
                    sample_image.visibility = View.GONE
                }
                MotionEvent.ACTION_UP -> {
                    sample_image.visibility = View.VISIBLE
                }
                -999 -> {
                    v.performClick()
                }
            }
            true
        }

        test_pixel.setOnClickListener {
            if (photoBitmap != null) {
                logicBitmap(photoBitmap!!) {
                    if (it != null && !it.isRecycled) {
                        if (!isFinishing) {
                            val ob = photoBitmap
                            photoBitmap = it
                            Glide.with(this).load(it).into(sample_image)

                            if (ob != photoBitmap && ob?.isRecycled != true) {
                                ob?.recycle()
                            }
                        }
                    }
                }
            }
        }
        // GlobalScope.launch(Dispatchers.IO)

        test_save.setOnClickListener {
            if (photoBitmap != null) {
                saveImageToStorage(photoBitmap!!)
            }
        }
    }

    override fun onActivityResult(requestCode: Int, resultCode: Int, data: Intent?) {
        super.onActivityResult(requestCode, resultCode, data)
        if (resultCode == Activity.RESULT_OK) {
            val photo = data?.dataString
            if (photo != null) {

                Glide.with(this).asBitmap().load(photo).into(object : CustomTarget<Bitmap>() {
                    override fun onLoadCleared(placeholder: Drawable?) {

                    }

                    override fun onResourceReady(
                        resource: Bitmap,
                        transition: Transition<in Bitmap>?
                    ) {
                        recycledCachedBitmap()
                        photoBitmap = resource
                        originBitmap = resource
                        Glide.with(this@MainActivity).load(originBitmap).into(origin_image)
                        Glide.with(this@MainActivity).load(photoBitmap).into(sample_image)
                    }

                })
            }
        }
    }

    private fun logicBitmap(resource: Bitmap, l: (Bitmap?) -> Unit) {
//        if (loading.isVisible) {
//            return
//        }
        loading.visibility = View.VISIBLE
        GlobalScope.launch(Dispatchers.IO) {
            val result = try {
                val width = resource.width
                val height = resource.height
                val size = width * height
                val intArray = IntArray(size)
                resource.getPixels(intArray, 0, width, 0, 0, width, height)
                recycledCachedBitmap()
                val b = try {
                    Bitmap.createBitmap(width, height, Bitmap.Config.ARGB_8888)
                } catch (e: OutOfMemoryError) {
                    System.gc()
                    System.runFinalization()
                    Bitmap.createBitmap(width, height, Bitmap.Config.ARGB_8888)
                }
                cacheBitmapList.add(b)
                if (!b.isRecycled) {
                    bitmapLogicFromJNI(intArray, width, height, width)
                    if (!b.isRecycled) {
                        b.setPixels(intArray, 0, width, 0, 0, width, height)
                        b
                    } else {
                        null
                    }
                } else {
                    null
                }
            } catch (e: Throwable) {
                e.printStackTrace()
                null
            }

            GlobalScope.launch(Dispatchers.Main) {
                l.invoke(result)
                if (result != null) {
                    loading.visibility = View.GONE
                }
            }
        }


    }

    override fun onDestroy() {
        Glide.with(applicationContext).clear(sample_image);
        Glide.with(applicationContext).clear(origin_image);
        Glide.get(applicationContext).bitmapPool.clearMemory();
        if (photoBitmap?.isRecycled != true) {
            photoBitmap?.recycle()
        }
        if (originBitmap?.isRecycled != true) {
            originBitmap?.recycle()
        }
        recycledCachedBitmap()
        super.onDestroy()
    }

    private fun recycledCachedBitmap() {
        var cb: Bitmap? = cacheBitmapList.poll()
        while (cb != null) {
            if (!cb.isRecycled && cb != photoBitmap)  {
                cb.recycle()
            }
            cb = cacheBitmapList.poll()
        }
    }

    private fun checkPermission(): Boolean {
        if (ActivityCompat.checkSelfPermission(
                this,
                android.Manifest.permission.READ_EXTERNAL_STORAGE
            ) != PackageManager.PERMISSION_GRANTED
        ) {
            ActivityCompat.requestPermissions(
                this,
                arrayOf(
                    android.Manifest.permission.READ_EXTERNAL_STORAGE,
                    android.Manifest.permission.WRITE_EXTERNAL_STORAGE
                ),
                1111
            )
            return false
        }
        return true
    }

    private fun saveImageToStorage(
        bitmap: Bitmap,
        filename: String = "filter_${System.currentTimeMillis()}.jpg",
        mimeType: String = "image/jpeg",
        directory: String = Environment.DIRECTORY_PICTURES,
        mediaContentUri: Uri = MediaStore.Images.Media.EXTERNAL_CONTENT_URI
    ) {
        if (loading.isVisible) {
            return
        }
        loading.visibility = View.VISIBLE
        GlobalScope.launch(Dispatchers.IO) {

            try {
                val imageOutStream: OutputStream?
                var imageSavedPath: String? = null
                if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.Q) {
                    val values = ContentValues().apply {
                        put(MediaStore.Images.Media.DISPLAY_NAME, filename)
                        put(MediaStore.Images.Media.MIME_TYPE, mimeType)
                        put(MediaStore.Images.Media.RELATIVE_PATH, directory)
                    }

                    contentResolver.run {
                        val uri =
                            contentResolver.insert(mediaContentUri, values)
                        imageOutStream = uri?.let { openOutputStream(it) }
                    }
                } else {
                    val imagePath =
                        Environment.getExternalStoragePublicDirectory(directory).absolutePath
                    val image = File(imagePath, filename)
                    if (image.parentFile?.exists() != true) {
                        image.parentFile?.mkdirs()
                    }
                    imageOutStream = FileOutputStream(image)
                    imageSavedPath = image.absolutePath
                }

                if (imageOutStream != null) {
                    imageOutStream.use { bitmap.compress(Bitmap.CompressFormat.JPEG, 100, it) }

                    GlobalScope.launch(Dispatchers.Main) {

                        loading.visibility = View.GONE

                        try {
                            if (imageSavedPath != null) {
                                MediaScannerConnection.scanFile(
                                    this@MainActivity,
                                    arrayOf(imageSavedPath),
                                    arrayOf(mimeType)
                                ) { path, uri ->

                                }
                                Toast.makeText(
                                    this@MainActivity,
                                    imageSavedPath,
                                    Toast.LENGTH_SHORT
                                ).show()
                            } else {

                                Toast.makeText(
                                    this@MainActivity,
                                    "$filename saved",
                                    Toast.LENGTH_SHORT
                                ).show()
                            }
                        } catch (e: Exception) {
                        }
                    }
                }

            } catch (e: Exception) {
                e.printStackTrace()
            }
        }
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String
    external fun bitmapLogicFromJNI(src: IntArray, w: Int, h: Int, stride: Int)

    companion object {
        // Used to load the 'native-lib' library on application startup.
        init {
            System.loadLibrary("native-lib")
        }
    }
}