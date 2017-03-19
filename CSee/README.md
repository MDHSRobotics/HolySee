#CSee Build Settings

##install commands
```
sudo apt-get install libgstreamer-plugins*
sudo apt-get install gir1.2-gstreamer-1.0 
pkg-config --cflags --libs opencv
pkg-config --cflags --libs gstreamer-1.0
pkg-config --cflags --libs gstreamer-plugins-base-1.0
pkg-config --cflags --libs gstreamer-base-0.10
```

##compile options
```
-O2;-std=c++11;-pthread;-fPIC
```

##include paths
```
/usr/local/include/opencv 
/usr/local/include
/usr/include/gstreamer-1.0 
/usr/lib/x86_64-linux-gnu/gstreamer-1.0/include 
/usr/include/gstreamer-0.10 
/usr/include/glib-2.0 
/usr/lib/x86_64-linux-gnu/glib-2.0/include 
/usr/include/libxml2
```

##linker options
```
-O2;-pthread
```

##library search paths
```
/usr/local/lib 
/usr/lib/x86_64-linux-gnu/gstreamer-1.0
```

##libraries
```
opencv_shape 
opencv_stitching 
opencv_objdetect 
opencv_superres 
opencv_videostab 
opencv_calib3d 
opencv_features2d 
opencv_highgui 
opencv_videoio 
opencv_imgcodecs 
opencv_video 
opencv_photo 
opencv_ml 
opencv_imgproc 
opencv_flann 
opencv_core
gstreamer-1.0
gstapp-1.0
gstcoreelements
gstbase-1.0
gobject-2.0
gmodule-2.0 
pthread 
gthread-2.0 
glib-2.0 
xml2
PocoFoundation
PocoUtil
PocoJSON
rplidar_sdk
```
