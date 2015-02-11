#ifndef MATERIAL_H
#define MATERIAL_H

#include "geometry.h"
#include "program.h"

#include <memory>

class Material
{
public:
    Material();
    virtual ~Material();

    virtual ProgramPtr& GetProgram();

protected:
    ProgramPtr program_;
};
typedef std::shared_ptr<Material> MaterialPtr;

class SolidColorMaterial : public Material
{
public:
    SolidColorMaterial(/*const vec3& color*/);
    virtual ~SolidColorMaterial();

private:
};
typedef std::shared_ptr<SolidColorMaterial> SolidColorMaterialPtr;

class ShadedMaterial : public Material
{
public:
    ShadedMaterial(/*const vec3& color*/);
    virtual ~ShadedMaterial();

private:
};
typedef std::shared_ptr<SolidColorMaterial> SolidColorMaterialPtr;


#endif // MATERIAL_H
