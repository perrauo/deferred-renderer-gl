# ghostgame-deferredrend-gl

BOOST_INCLUDE_DIRS
BOOST_LIBRARYDIR
BOOST_ROOT
GLEW_ROOT C:\glew\glew_2_1_0
GLUT_ROOT C:\freeglut\freeglut_3_6_0


cd boost/bost_1_85_0
bootstrap
b2

cd C:\glew\glew_2_1_0
OK!

cd C:\freeglut\freeglut_3_6_0
ninja -G
ninja .

https://stackoverflow.com/questions/20746936/what-use-is-find-package-when-you-need-to-specify-cmake-module-path
cmake -G "Visual Studio 17 2022" -A x64 -DBoost_ARCHITECTURE=-x64 -DBoost_LIB_PREFIX=lib .



