# ImLogDetective
[![Build and test (Release-Ubuntu)](https://github.com/bilal614/ImLogDetective/actions/workflows/build.yml/badge.svg?branch=master)](https://github.com/bilal614/ImLogDetective/actions/workflows/build.yml)

The ImLogDetective is a developer tool for developers and engineers. This tool is intended for viewing log files and logging data. It allows copying of logs from remote hosts and configuring text highlighting for ease of reading logging data. The tool is built using the popular dearimgui library for its UI.

ImLogDetective is heavily based on the excellent dearimgui API and thus relies on immediate mode rendering. As such, the tool is also a great way to learn and become familiar with dearimgui and immediate mode GUIs in general. For building, this repository relies on cmake(to be followed up with build instructions).   

### Screenshots 
![image](https://github.com/bilal614/ImLogDetective/assets/15609233/7bfa6a84-bccd-4f3f-afef-2b2d00fe71f8)
*Tabbed log file view*

![image](https://github.com/bilal614/ImLogDetective/assets/15609233/5e560cb1-e014-4154-af50-85ee02fd9b3b)
*Easy text filtering*

## Features
* View log files with text highlights
* Decompress log files on the fly (only gzip)
* Quick and easy text filtering
* Configure text highlighting (WIP)
* Copy log files from remote hosts with proxy jump
* Viewport scaling

## Development
The tool is built on top of the handy dearimgui library. Current implementation is only limited for linux based targets.

### Dependencies
* OpenGL
* GLFW
* Zlib
* Gtest+Gmock
* Scp
