#include "program.h"

#include "utility.h"

#include <sstream>
#include <fstream>

Program::Program() :
    isCompiled(false),
    programId_(0)
{
}

Program::Program(const string& vsPath, const string& fsPath) :
    isCompiled(false),
    programId_(0),
    vsPath_(vsPath),
    fsPath_(fsPath)
{

}

Program::~Program()
{

}

GLuint Program::Id()
{
    return programId_;
}

bool Program::IsBuild()
{
    return programId_ != 0;
}

bool Program::Build()
{
    GLuint vs, fs;

    if (! LoadShader(fsPath_, GL_FRAGMENT_SHADER, fs))
    {
        isCompiled = false;
        return false;
    }

    if (! LoadShader(vsPath_, GL_VERTEX_SHADER, vs))
    {
        isCompiled = false;
        return false;
    }


    GLuint programID = glCreateProgram(); return_check_gl_error();
    glAttachShader(programID, vs); return_check_gl_error();
    glAttachShader(programID, fs); return_check_gl_error();
    glLinkProgram(programID); return_check_gl_error();
    writeProgramLog(programID); return_check_gl_error();

    programId_ = programID;
    isCompiled = true;
    return true;
}

GLint Program::Camera()
{
    return GetLoc("camera");
}

GLint Program::GetLoc(const string& name)
{
    return glGetUniformLocation(programId_, name.c_str());
}

bool Program::Use()
{
    if (isCompiled)
    {
        glUseProgram(programId_);
        return true;
    }
    else
    {
        return false;
    }
}

GLuint Program::LoadShader(const string& path, GLuint type, GLuint &shader)
{
    GLuint shaderProgram = glCreateShader(type); check_gl_error();

    string source;
    bool isLoaded = LoadSource(path, source);

    if (!isLoaded)
    {
        string shaderTypeName = GetShaderTypeName(type);
        std::cerr << "Processing of " << shaderTypeName << std::endl;
        std::cerr << "can't load shader " << path << std::endl;
        return false;
    }

    const char* sourceCStr = source.c_str();

    glShaderSource(shaderProgram, 1, &sourceCStr, 0); check_gl_error();
    glCompileShader(shaderProgram); check_gl_error();

    if (!shaderCompiled(shaderProgram))
    {
        writeShaderLog(shaderProgram);
        return false;
    }

    check_gl_error();
    shader = shaderProgram;
    return true;
}

bool Program::LoadSource(const string& shaderPath, string& source)
{
    std::ifstream file(shaderPath);
    if (!file.is_open())
    {
        return false;
    }
    std::stringstream  strstream;
    strstream << file.rdbuf();
    source = strstream.str();
    return true;
}

string Program::GetShaderTypeName(GLuint type)
{
    if (type == GL_VERTEX_SHADER)
    {
        return "Vertex shader";
    }
    else if (type == GL_FRAGMENT_SHADER)
    {
        return "Fragment shader";
    }

    return "Unknown shader";
}
