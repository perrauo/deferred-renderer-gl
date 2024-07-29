# Ghost Game + Deferred Renderer (GL)
# **WORK IN PROGRESS**
## About
Project showcasing a game loop deferred and rendering technique in OpenGL
* Deferred rendering is not currently working
    * [engine::draw](https://github.com/perrauo/ghostgame-deferredrend-gl/blob/main/src/framework/engine.cpp#L191)
    * [lambertGeom.vert](https://github.com/perrauo/ghostgame-deferredrend-gl/blob/main/resources/framework/shaders/lambertGeom.vert)
    * [lambertGeom.frag](https://github.com/perrauo/ghostgame-deferredrend-gl/blob/main/resources/framework/shaders/lambertGeom.frag)
    * [lambertLight.vert](https://github.com/perrauo/ghostgame-deferredrend-gl/blob/main/resources/framework/shaders/lambertLight.vert)
    * [lambertLight.frag](https://github.com/perrauo/ghostgame-deferredrend-gl/blob/main/resources/framework/shaders/lambertLight.frag)
    * [pointLight.vert](https://github.com/perrauo/ghostgame-deferredrend-gl/blob/main/resources/framework/shaders/pointLight.vert)
    * [pointLight.frag](https://github.com/perrauo/ghostgame-deferredrend-gl/blob/main/resources/framework/shaders/pointLight.frag)
* Mesh
    * [MeshComponent::draw](https://github.com/perrauo/ghostgame-deferredrend-gl/blob/main/src/framework/mesh.cpp#L124)
* Point Light
    * [PointLightComponent::drawLight](https://github.com/perrauo/ghostgame-deferredrend-gl/blob/main/src/framework/light.cpp#L29)
* Entity Component System
    * [entity.h](https://github.com/perrauo/ghostgame-deferredrend-gl/blob/main/include/framework/entity.h)

## Build

* https://stackoverflow.com/questions/20746936/what-use-is-find-package-when-you-need-to-specify-cmake-module-path
    * cmake -G "Visual Studio 17 2022" -A x64 -DBoost_ARCHITECTURE=-x64 -DBoost_LIB_PREFIX=lib .
    * or
    * cmake -G Ninja -DBoost_ARCHITECTURE=-x64 -DBoost_LIB_PREFIX=lib .
        *  ninja


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



