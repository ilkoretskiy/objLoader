#include "wavefrontobjloader.h"

#include <fstream>
#include <sstream>

WavefrontObjLoader::WavefrontObjLoader()
{
    Init();
}

WavefrontObjLoader::WavefrontObjLoader(const string& path)
{
    Init();
    Load(path);
}

void WavefrontObjLoader::Init()
{
    vnExist_ = false;
    vtExist_ = false;
    smoothEnabled_ = false;
}

WavefrontObjLoader::~WavefrontObjLoader()
{

}

bool WavefrontObjLoader::SmoothEnabled()
{
    return smoothEnabled_;
}

bool WavefrontObjLoader::PrecomputedNormals()
{
    return vnExist_;
}


#define DEBUG 1

void WavefrontObjLoader::Load(const string& path)
{
    std::ifstream input(path);
    if (!input.is_open())
    {
        std::cerr << "can't load model, failure open " << path;
        return;
    }

    std::stringstream stream;

    while (!input.eof())
    {
        std::string line;
        std::getline(input, line);

        if (line[0] == '#')
        {
#if (DEBUG)
            std::cout << "Comment : " << line << std::endl;
            continue;
#endif
        }

        stream.clear();
        stream.str(line);

        string descriptor;
        stream >> descriptor;

        if (descriptor == "mtllib")
        {
            string libname;
            stream >> libname;
#if (DEBUG)
            std::cout << "lib name " << libname << std::endl;
#endif
        }
        else if(descriptor == "o")
        {
            string name;
            stream >> name;
#if (DEBUG)
            std::cout << "object name " << name <<  std::endl;
#endif
        }
        else if (descriptor == "v")
        {
            float x, y, z;
            stream >> x >> y >> z;
            vertecies_.push_back(glm::vec3(x, y, z));
            colors_.push_back(glm::vec3( 1., 1., 1.));

            //std::cout << "v:"<< x << " " << y << " " << z << " " << std::endl;
        }
        else if (descriptor == "f")
        {
            // in wavefront indecies start from 1
            Face face{};
            if (!vnExist_ && !vtExist_)
            {
                // format v

                for (int i = 0; i < 3; ++i)
                {
                    stream >> face.vInd[i];
                    face.vInd[i]--;
                }

            }
            else if (vnExist_ && !vtExist_)
            {
                char skip;
                // format v//n
                for (int i = 0; i < 3; ++i)
                {
                    stream >> face.vInd[i] >> skip >> skip >> face.nInd[i];
                    face.vInd[i]--;
                    face.nInd[i]--;
                }
            }
            else if (!vnExist_ && vtExist_)
            {
                // format v/t
                for (int i = 0; i < 3; ++i)
                {
                    stream >> face.vInd[i]; stream.ignore(1);
                    stream >> face.tInd[i];

                    face.vInd[i] --;
                    face.tInd[i] --;
                }
            }
            faces_.push_back(face);
        }
        else if (descriptor == "vn")
        {
            vnExist_ = true;
            float x, y, z;
            stream >> x >> y >> z;
            normals_.push_back(vec3(x, y, z));

        }
        else if (descriptor == "vt")
        {
            vtExist_ = true;
        }
        else if (descriptor == "s")
        {
            string isEnabled;
            stream >> isEnabled;
            if (isEnabled == "off")
            {
                smoothEnabled_ = false;
            }
        }
    }

    std::cout << "model loaded " << std::endl;
}

void WavefrontObjLoader::Fill(
        vector<vec3>& data,
        vector<vec3>& normals,
        vector<vec3>& colors)
{
    const int VertexPerFace = 3;
    const int VertexCount = faces_.size() * VertexPerFace;

    data.resize(VertexCount);
    normals.resize(VertexCount);
    colors.resize(VertexCount);

    int counter = 0;
    for (Face& face : faces_)
    {
        for (int i = 0; i < 3; ++i)
        {
            vec3& vertex = vertecies_[face.vInd[i]];
            vec3& normal = normals_[face.nInd[i]];
            vec3 color(1., 1., 1.);//vertecies_[face.cInd[i]];

            data[counter] = vertex;
            normals[counter] = normal;
            colors[counter] = color;

            ++counter;
        }
    }
}
