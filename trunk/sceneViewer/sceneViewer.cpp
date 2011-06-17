//
// SceneViewer.cpp
//

#include "Common.h"
#include "sceneViewer.h"

void SceneViewer::Init()
{
    _params.Init("parameters.txt");

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    _time = 0.0f;
    _m = new Model("C:\\SceneModeling\\", "exportTest");

    _scene.Load(_params, _params.defaultScene, _assets);

    _camera.Reset(Vec3f(100.0f, 100.0f, 100.0f), Vec3f(0.0f, 0.0f, 1.0f), Vec3f(0.0f, 0.0f, 0.0f));

    std::cout << "Initialization done\n";
}

void SceneViewer::ReSize(int windowWidth, int windowHeight)
{
    _windowWidth = windowWidth;
    _windowHeight = windowHeight;
}

void SceneViewer::Update(float seconds)
{
    _time += seconds;
}

void SceneViewer::MouseDown(int button, int x, int y)
{
    _mouseButton = button;
    _mouseX = x;
    _mouseY = y;
}

void SceneViewer::MouseMove(int x, int y)
{
    const float angleScale = 0.02f;
    const float moveScale = 1.0f;

    const int mouseDiffX = x - _mouseX;
    const int mouseDiffY = y - _mouseY;

    _mouseX = x;
    _mouseY = y;

    if(_mouseButton == GLUT_LEFT_BUTTON)
    {
        _camera.LookRight(-angleScale * mouseDiffX);
        _camera.LookUp(angleScale * mouseDiffY);
    }
    if(_mouseButton == GLUT_RIGHT_BUTTON)
    {
        _camera.Strafe(-moveScale * mouseDiffX);
        _camera.Jump(-moveScale * mouseDiffY);
    }
}

void SceneViewer::KeyPress(unsigned char key)
{
    const float moveDistance = 15.0f;
    const float angleDistance = 0.15f;

    switch(key)
    {
    case 'w':
        _camera.Move(-moveDistance);
        break;
    case 's':
        _camera.Move(moveDistance);
        break;
    case 'a':
        _camera.Strafe(moveDistance);
        break;
    case 'd':
        _camera.Strafe(-moveDistance);
        break;
    case '2':
        _camera.LookUp(angleDistance);
        break;
    case '8':
        _camera.LookUp(-angleDistance);
        break;
    case '4':
        _camera.LookRight(angleDistance);
        break;
    case '6':
        _camera.LookRight(-angleDistance);
        break;
    default:
        //std::cout << key << ' ' << int(key) << std::endl;
        break;
    }
}

void SceneViewer::Render()
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, _windowWidth, _windowHeight);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    float aspectRatio = float(_windowWidth) / float(_windowHeight);
    gluPerspective(60.0f, aspectRatio, 0.1f, 1000.0f);
  
    glMatrixMode(GL_MODELVIEW);
    _camera.Update();
    glLoadMatrixf(_camera.Matrix()[0]);
    //glRotatef(_time * 180.0f, 1.0f, 0.0f, 0.0f);

    //_m->Render();
    _scene.Render();

    glutSwapBuffers();
}
