#include <iostream>

using namespace std;

#define GLM_FORCE_RADIANS
#define GLFW_INCLUDE_GLCOREARB
#include "GLFW/glfw3.h"


#define GLM_FORCE_RADIANS
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


#include "line.h"
#include "geometry.h"
#include "scene.h"
#include "program.h"
#include "surface.h"
#include "rectangle.h"
#include "cube.h"
#include "model.h"


#include <vector>

using std::vector;

#include "utility.h"

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

glm::vec3 g_angle(0., 0., 0.);

bool g_rotate = false;

glm::vec3 g_lightTranslate(0.f);

static void key_callback(GLFWwindow* fromWindow ,int key,int,int action,int)
{
    if (action != GLFW_PRESS)
        return;

    (void)fromWindow;
    std::cout << "key was pressed " <<  key << std::endl;

    if (key == 73)
    {
        g_angle.x += 1;
    }
    else if(key == 74)
    {
        g_angle.y += 1;
    }
    else if (key == 75)
    {
        g_angle.z += 1;
    }

    //N.B. inverted direction
    else if (key == 262)
    {
        g_lightTranslate.x -= 1;
    }
    else if (key == 263)
    {
        g_lightTranslate.x += 1;
    }
    else if (key == 265)
    {
        g_lightTranslate.y -= 1;
    }
    else if (key == 264)
    {
        g_lightTranslate.y += 1;
    }
    else
    {
        glfwSetWindowShouldClose(fromWindow, GL_TRUE);
    }
}

const int width = 1024;
const int height = 768;


bool Init(GLFWwindow ** ppWindow)
{
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
    {
        std::cerr << "Can't init glfw"  << std::endl;
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_DEPTH_BITS, 24);


    *ppWindow = glfwCreateWindow(width, height, "Line", NULL, NULL);

    GLFWwindow * pWindow = *ppWindow;

    if (!pWindow)
    {
        std::cerr << "Can't create window" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(pWindow);
    glfwSetKeyCallback(pWindow, key_callback);

    glViewport(0, 0, width, height);

    return true;
}

bool Process(GLFWwindow* window)
{
    float ratio = float(width) / height;

    glm::mat4 projection = glm::perspective( util::ToRad(45.f), ratio, 1.f, 100.f);

    //ModelPtr sphere = std::make_shared<Model>("../models/sphere.obj");
    //ModelPtr sphere = std::make_shared<Model>("../models/cube.obj");
    //ModelPtr sphere = std::make_shared<Model>("../models/foo.obj");
    //ModelPtr sphere = std::make_shared<Model>("../models/some.obj");
    //ModelPtr foo = std::make_shared<Model>("../models/plane_triangle.obj");

    MaterialPtr surfaceMaterial = std::make_shared<SolidColorMaterial>();
    SurfacePtr surface = std::make_shared<Surface>(surfaceMaterial, 20, 20);
    surface->Move(0, 0.01, -10);
    surface->Rotate(util::ToRad(-90), vec3(1., 0., 0.));

    MaterialPtr shadedMaterial = std::make_shared<ShadedMaterial>();
    RectanglePtr rectangle = std::make_shared<Rectangle>(shadedMaterial, 20, 20);
    rectangle->Move(0, 0., -10);
    rectangle->Rotate(util::ToRad(-90), vec3(1., 0., 0.));


    MaterialPtr solidColorMaterial = std::make_shared<SolidColorMaterial>();
    CubePtr cube = std::make_shared<Cube>(solidColorMaterial, vec3(4, 2, 1));
    cube->Move(0., -1, 1.);

    string path_compl = "../models/compl_triangulate_normals.obj";
    string path_head = "../models/head_triangulate_normals.obj";
    string path_torus = "../models/torus_triangulate_normals_smooth.obj";

    ModelPtr obj = std::make_shared<Model>(shadedMaterial, path_compl);
    obj->Move(0., 5., -20);

    Scene scene;
    scene.AddObject(obj);

    // they are must be linked
    {
        scene.AddObject(rectangle);
        scene.AddObject(surface);
    }

    vec3 directedIntoDepth(0., -5., -5.);
    LightPtr light = std::make_shared<Light>(directedIntoDepth);
    scene.SetLight(light);

    glm::mat4 view(1.f);
    view = glm::translate(view, glm::vec3(-0., -5., -10));
    //view = glm::rotate(view, util::ToRad(60) , glm::vec3(-1, 0., 0.));
    //view = glm::rotate(view, util::ToRad(180) , glm::vec3(0., 1., 0.));
    //view = glm::rotate(view, util::ToRad(15) , glm::vec3(0., 0., 1.));

    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    while (!glfwWindowShouldClose(window) )
    {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClearDepth(1.0f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (g_angle.x != 0 || g_angle.y != 0. || g_angle.z != 0.)
        {
            obj->Rotate(util::ToRad(1), g_angle);
            //view = glm::rotate(view, util::ToRad(1) , g_angle);
            //rectangle->Rotate(util::ToRad(1), g_angle);
            //cube->Rotate(util::ToRad(1), g_angle);
            //blenderCube->Rotate(util::ToRad(1), g_angle);
        }

        directedIntoDepth += g_lightTranslate;
        light->SetDir(directedIntoDepth);
        g_lightTranslate = vec3(0.);

        scene.Draw(projection, view);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return true;
}

/*
Renderer renderer;
renderer.render(scene, camera);

render(Scene, Camera)
{
    // get from camera view and projection matrix
    // for every item
    //     get model matrix
    //     set MVP matrix
    //     if
}
*/


int main()
{
    GLFWwindow* window = nullptr;

    if (!Init(&window))
    {
        exit(EXIT_FAILURE);
    }

    Process(window);

    return 0;
}
