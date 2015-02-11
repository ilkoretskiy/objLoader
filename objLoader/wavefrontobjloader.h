#ifndef WAVEFRONTOBJLOADER_H
#define WAVEFRONTOBJLOADER_H

#include <string>
#include <vector>
#include "utility.h"

#define GLM_FORCE_RADIANS
#include <glm/vec3.hpp>

using glm::vec3;
using std::string;
using std::vector;

struct Face
{
    int vInd[3];
    int nInd[3];
    int tInd[3];
};

class WavefrontObjLoader
{
public:
    WavefrontObjLoader();
    WavefrontObjLoader(const string& path);
    void Load(const string& path);

    void Fill(vector<vec3>& data, vector<vec3>& normals, vector<vec3>& colors);

    ~WavefrontObjLoader();

    bool SmoothEnabled();
    bool PrecomputedNormals();

private:
    void Init();

    bool vnExist_;
    bool vtExist_;
    bool smoothEnabled_;

    vector<vec3> vertecies_;
    vector<vec3> normals_;
    vector<Face> faces_;
    vector<vec3> colors_;

};

#endif // WAVEFRONTOBJLOADER_H
