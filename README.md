# KWin Expie Pet
Welcome! This is a work in progress, so expect some things to be broken.

This project lets you have an Expie from Casualties Unknown as a pet on your desktop.
Currently, there is some fun physics, kinematics and inverse kinematics, and some placeholder animation,
but this will be updated as I work on it more, and I do review and accept pull requests.

### Requirements
- KWin Wayland window manager
### Build instructions
**I forgot to change the filepaths for the images, you will have to do this yourself until I fix it. They are located in mainsprite.h**
- Install the KWinScript input handler from [here](https://github.com/AwesomeTornado/ExpiePet3KWinService)
- Download/extract or clone the source code
- Make a new folder for your build files, and open a command line there. ```mkdir ./build;cd ./build```
- Build the project with cmake and make. ```cmake ../CMakeLists.txt;make```
- Execute the `ExpiePet3` file to run it!

Do note, there is no way to close it without using a task manager yet. Sorry for the inconvenience, this will be fixed eventually.

