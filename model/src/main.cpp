#include "Matrix.h"
#include "Vector4.h"
#include "SimpleContext.h"
#include <iostream>
#include <thread>
#include "SceneManager.h"

int main(int argc, char** argv) {

    //Send the width and height in pixel units and the near and far plane to describe the view frustum
    SceneManager sceneManager(&argc, argv, screenPixelWidth, screenPixelHeight, 0.1f, 1000.0f); //Manages the camera view and models in scene
    return 0;
}

#if defined(_WIN32)

int CALLBACK WinMain(
  _In_ HINSTANCE hInstance,
  _In_ HINSTANCE hPrevInstance,
  _In_ LPSTR     lpCmdLine,
  _In_ int       nCmdShow
)
{
    main(__argc, __argv);
}

#endif
