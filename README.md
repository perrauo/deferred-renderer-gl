# Game Engine + Deferred Renderer (GL)
![image](https://github.com/user-attachments/assets/aeedee75-629f-4342-ad8e-7197e225657d)

# **WORK IN PROGRESS**
## About
Project showcasing a game loop deferred and rendering technique in OpenGL
* Deferred rendering
    * [engine::draw](https://github.com/perrauo/ghostgame-deferredrend-gl/blob/main/src/framework/engine.cpp#L191)
    * [gbuffer.vert](https://github.com/perrauo/ghostgame-deferredrend-gl/blob/main/resources/framework/shaders/gbuffer.vert)
    * [gbuffer.frag](https://github.com/perrauo/ghostgame-deferredrend-gl/blob/main/resources/framework/shaders/gbuffer.frag)
    * [light.vert](https://github.com/perrauo/ghostgame-deferredrend-gl/blob/main/resources/framework/shaders/light.vert)
    * [light.frag](https://github.com/perrauo/ghostgame-deferredrend-gl/blob/main/resources/framework/shaders/light.frag)
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



