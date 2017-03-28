# CSee Build Settings

## install commands

```
sudo apt-get install libgstreamer-plugins*
sudo apt-get install gir1.2-gstreamer-1.0 
pkg-config --cflags --libs opencv
pkg-config --cflags --libs gstreamer-1.0
pkg-config --cflags --libs gstreamer-plugins-base-1.0
```


## compile options

```
-O2;-std=c++11;-pthread;-fPIC
```


## include paths

```
/usr/include/opencv
/usr/local/include
/usr/include/gstreamer-1.0 
/usr/lib/x86_64-linux-gnu/gstreamer-1.0/include 
/usr/include/glib-2.0 
/usr/lib/x86_64-linux-gnu/glib-2.0/include 
```


## linker options

```
-O2;-pthread
```


## library search paths

```
/usr/local/cuda-8.0/lib64
/usr/local/lib
/usr/lib/aarch64-linux-gnu/gstreamer-1.0
```


## libraries

```
opencv_calib3d 
opencv_contrib 
opencv_core 
opencv_features2d 
opencv_flann 
opencv_gpu 
opencv_highgui 
opencv_imgproc 
opencv_legacy 
opencv_ml 
opencv_objdetect 
opencv_photo 
opencv_stitching 
opencv_superres 
opencv_ts 
opencv_video 
opencv_videostab 
opencv_detection_based_tracker 
opencv_esm_panorama 
opencv_facedetect 
opencv_imuvstab 
opencv_tegra 
opencv_vstab
cufft 
npps 
nppi 
nppc 
cudart 
atomic 
tbb 
rt 
pthread 
m 
dl
gstreamer-1.0
gstapp-1.0
gstcoreelements
gstbase-1.0
gobject-2.0
gmodule-2.0 
pthread 
gthread-2.0 
glib-2.0 
rplidar_sdk
```