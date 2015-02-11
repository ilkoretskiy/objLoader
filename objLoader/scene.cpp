#include "scene.h"

#include "program.h"

#include "utility.h"

Scene::Scene()
{

}

Scene::~Scene()
{

}

bool Scene::AddObject(const DrawableObjectPtr& drawableObject)
{
    objects_.push_back(drawableObject);
    return true;
}

bool Scene::Draw(const glm::mat4& projection, const glm::mat4 &view)
{
    for (DrawableObjectPtr& object : objects_)
    {
        MaterialPtr& material = object->GetMaterial();
        ProgramPtr& program = material->GetProgram();
        check_gl_error();
        if (!program->IsBuild())
        {
                return false;
        }
    }

    vec4 lightDir = light_->GetDir();

    for (DrawableObjectPtr& object : objects_)
    {
        MaterialPtr& material = object->GetMaterial();
        ProgramPtr& program = material->GetProgram();

        program->Use();
        GLint cameraLoc = program->Camera();
        glUniformMatrix4fv(cameraLoc, 1, GL_FALSE, glm::value_ptr(projection) ); check_gl_error();
        glUniform4fv(program->GetLoc("LightDirection"), 1, glm::value_ptr(lightDir) ); check_gl_error();

        glm::mat4& model = object->Model();
        glm::mat4 modelView = view * model;
        glUniformMatrix4fv(program->GetLoc("ModelView"), 1, GL_FALSE, glm::value_ptr(modelView ) ); check_gl_error();
        object->Draw();
    }

#define DEBUG_LIGHT 1
#if (DEBUG_LIGHT)
    DrawableObjectPtr lightObj = light_->GetRepr();

    MaterialPtr material = lightObj->GetMaterial();
    ProgramPtr program = material->GetProgram();
    program->Use();
    GLint cameraLoc = program->Camera();
    glUniformMatrix4fv(cameraLoc, 1, GL_FALSE, glm::value_ptr(projection) ); check_gl_error();

    glm::mat4& model = lightObj->Model();
    glm::mat4 modelView = view * model;
    glUniformMatrix4fv(program->GetLoc("ModelView"), 1, GL_FALSE, glm::value_ptr(modelView) ); check_gl_error();
    lightObj->Draw();
#endif

    return true;
}

void Scene::SetLight(const LightPtr& light)
{
    light_ = light;
}
