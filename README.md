# ImLogDetective
[![Build](https://github.com/bilal614/ImLogDetective/actions/workflows/build.yml/badge.svg)](https://github.com/bilal614/ImLogDetective/actions/workflows/build.yml)
![Code Coverage](https://img.shields.io/badge/Code%20Coverage-61%25-yellow?style=flat)

The ImLogDetective is a developer tool for developers and engineers. This tool is intended for viewing log files and logging data. It allows copying of logs from remote hosts and configuring text highlighting for ease of reading logging data. The tool is built using the popular dearimgui library for its UI.

ImLogDetective is heavily based on the excellent dearimgui API and thus relies on immediate mode rendering. As such, the tool is also a great way to learn and become familiar with dearimgui and immediate mode GUIs in general. For building, this repository relies on cmake(to be followed up with build instructions).

### The Sales Pitch
Do you often find yourself browsing through logs on remote hosts by Ssh'ing in a terminal? And, do you find it unwieldy reading those incomprehensible logs on an unembellished terminal? Like tons of similar developer tools, the ImLogDetective can lend itself to make reading, especially remote logs, a little less awkward.

### Screenshots 
![image](https://github.com/bilal614/ImLogDetective/assets/15609233/3fcc5e47-bdef-4078-a976-400831fc2233)
*Tabbed log file view*

![ImLogDetective_filtering](https://github.com/bilal614/ImLogDetective/assets/15609233/ff26a475-0ff8-4e11-ade8-48730d60e412)
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
