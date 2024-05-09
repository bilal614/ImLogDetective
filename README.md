This is a tool for viewing log files and logging data. It allows copying of logs from remote hosts and configuring text highlighting for ease of reading logging data. The tool is built using the popular dearimgui library for its UI. 

### Screenshots 
![image](https://github.com/bilal614/ImLogDetective/assets/15609233/7bfa6a84-bccd-4f3f-afef-2b2d00fe71f8)

## Features
* View log files with text highlights
* Decompress log files on the fly (only gzip)
* Configure text highlighting (WIP)
* Copy log files from remote hosts with proxy jump
* Viewport scaling

## Development
The tool is built on top of the handy dearimgui library. Current implementation is only limited for linux based targets.

### Dependencies
* OpenGL
* GLFW
* Zlib
* Gtest\Gmock
