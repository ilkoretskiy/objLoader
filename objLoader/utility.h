#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <string>

#define GLFW_INCLUDE_GLCOREARB
#include "OpenGL/gl3.h"

inline bool _check_gl_error(const char *file, int line) {
        GLenum err (glGetError());

        bool result = false;

        while(err!=GL_NO_ERROR) {
                std::string error;

                switch(err) {
                        case GL_INVALID_OPERATION:      error="INVALID_OPERATION";      break;
                        case GL_INVALID_ENUM:           error="INVALID_ENUM";           break;
                        case GL_INVALID_VALUE:          error="INVALID_VALUE";          break;
                        case GL_OUT_OF_MEMORY:          error="OUT_OF_MEMORY";          break;
                        case GL_INVALID_FRAMEBUFFER_OPERATION:  error="INVALID_FRAMEBUFFER_OPERATION";  break;
                }

                std::cerr << "GL_" << error.c_str() <<" - "<<file<<":"<<line<<std::endl;
                err=glGetError();
                result = true;
        }
        return result;
}

#define check_gl_error() _check_gl_error(__FILE__,__LINE__)

#define return_check_gl_error() if (_check_gl_error(__FILE__,__LINE__)) return false;

inline bool shaderCompiled(GLuint shaderId)
{
    GLint compile_ok = GL_TRUE;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compile_ok);
    return compile_ok;
}

inline void writeShaderLog(GLuint shaderId)
{
    GLint compile_ok = GL_FALSE;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compile_ok);
    std::cout << "compile shader is ok : " << (compile_ok ? "true" : "false") << std::endl;

    if (compile_ok == GL_FALSE)
    {
        char log[1024];
        GLsizei logLen;
        glGetShaderInfoLog(shaderId, sizeof(log), &logLen, log);
        std::cout << "log: "  << log << std::endl;
    }
}

inline void writeProgramLog(GLuint program)
{
    GLint link_status;
    glGetProgramiv(program, GL_LINK_STATUS, &link_status);
    std::cout << "link status is ok : " << (link_status ? "true" : "false") << std::endl;

    if (link_status == GL_FALSE)
    {
        char log[1024];
        GLsizei logLen;
        glGetProgramInfoLog(program, sizeof(log), &logLen, log);
        std::cout << "log: "  << log << std::endl;
    }
}

bool LoadSource(const std::string& shaderPath, std::string& source);
GLuint LoadShader(const std::string& path, GLuint type, GLuint &shader);
bool CreateProgram(const std::string& vsPath, const std::string& fsPath, GLuint& program);

#endif // UTILITY_H
