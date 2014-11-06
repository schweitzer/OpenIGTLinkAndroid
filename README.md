OpenIGTLinkAndroid
==================
Here some test using OpenIGTLink and the NDK on android.

IGTLMobile send matrix on network and IGTLDesktop receive the matrix
IGTLDesktop is the server and IGTLMobile the client.

This is two seperated programs so make sure you have a build for each

IGTLDesktop
------------

CONFIGURATION

ccmake ../Your/Sources

You will need OpenIGTLink and that's all

configure then generate


BUILD

run make in the Build directory 

IGTLMobile
-----------

For this application I'm using a modified version of OpenIGTLink to be android compliant.
Modifications are described below :

-The first modification is in the /Sources/CMakelists.txt : you don't have to link with pthread lib
and the SET_TARGET_PROPERTIES is removed in order to generate only the .so file and no sym links of it

-The second modification is in the /Sources/igtlutil/CMakelists.txt :
you have to remove the link to pthread

The application is quite simple and does not do anything "visual"
The only informations you will have will be printed in the android log (use logcat)

CONFIGURATION

To Build the apk you will need the android toolchain made by champf (https://github.com/ChampF/android-cmake)
You need to pass the toolchain first

ccmake ../Your/Sources -DCMAKE_TOOCHAIN_FILE="/path/to/the/toolchain"

After that you will have to enter the android, ant, adb executables and the location of the OpenIGTLink library

Then configure and generate


BUILD

You only have to do "make" in  your build directory

make will compile the sources and build the apk, the apk will be installed on the device (or emulator) but you need to have it connected
