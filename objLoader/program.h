#ifndef PROGRAM_H
#define PROGRAM_H

#include <memory>

#include <string>

using std::string;

#define GLM_FORCE_RADIANS
#define GLFW_INCLUDE_GLCOREARB
#include "GLFW/glfw3.h"

class Program
{
public:
    Program();

    Program(const string& vsPath, const string& fsPath);

    ~Program();

    bool Use();

    bool IsBuild();
    bool Build();

    GLint GetLoc(const string& name);
    GLuint Id();

    GLint Camera();

private:

    GLuint LoadShader(const string& path, GLuint type, GLuint &shader);
    string GetShaderTypeName(GLuint type);
    bool LoadSource(const string& shaderPath, string& source);

    bool isCompiled;
    GLuint programId_;

    string vsPath_;
    string fsPath_;
};

typedef std::shared_ptr<Program> ProgramPtr;

#endif // PROGRAM_H
