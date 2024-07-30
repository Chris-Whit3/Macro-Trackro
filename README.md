# Macro-Trackro


## Dependency Installation Instructions:

### ZXing

```

git clone https://github.com/zxing-cpp/zxing-cpp.git --recursive --single-branch --depth 1
cmake -S zxing-cpp -B zxing-cpp.release -DCMAKE_BUILD_TYPE=Release
cmake --build zxing-cpp.release -j8 --config Release

cmake --install zxing-cpp.release --prefix /usr/local

```

### OpenCV (Linux)

`sudo apt install libopencv-dev`

### OpenCV (Windows)

Follow this link: https://docs.opencv.org/4.x/d3/d52/tutorial_windows_install.html

Use the instructions specified in 'Installation by Using git-bash (version>=2.14.1) and cmake (version >=3.9.1)'

Then set system and local environment variables in 'PATH' so include:

```

C:\lib\install\opencv\x64\vc17\lib
C:\lib\install\opencv\x64\vc17\bin

```
