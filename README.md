# WIN-TEASER++
This repository is the unofficial win version of teaser++,only the C++ version was tested.
## Compared to the previous repository, added some header files under windows in win directory:
+ win
  + dirent.h
  + getopt.c
  + getopt.h
  + unistd.h
  + win_time.h

## Environment
+ PCL1.10
+ CMAKE 3.2.0
+ Eigen 3.4
+ Visual stdio 2019

## 1.Installation
I use cmake-gui to generate the project,but there was an error during the first configure, so I downloaded this part of the code ahead of time and put it in the build directory.


![configure_error](example\img\configure_error.png)

![source](example\img\ssource.jpg)


## 2.Generate dll

![install](example\img\install.jpg)


## 3.Test
In order to facilitate the reading of data, I modified the code and used PCL to read the point cloud

code path:
./example/teaser_cpp_fpfh/teaser_cpp_fpfh.cc

results:
```=====================================
          TEASER++ Results
=====================================
Estimated rotation:
  0.996344  0.0743931   0.042007
-0.0738955   0.997178 -0.0132802
-0.0428764  0.0101275   0.999029

Estimated translation:
-137.943
 30.9094
-33.1828

Time taken (s): 0.010525

```
