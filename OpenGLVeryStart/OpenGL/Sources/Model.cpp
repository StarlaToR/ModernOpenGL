#include <Model.h>
using namespace Resources;
using namespace std;

void Model::loadSource(const std::string& path)
{
	Core::Debug::Log log;
	ifstream file;

	file.open(path);

	ASSERT(file.is_open(), "Can't open file");

    log.Print("%s is open\n", path);

    vector<unsigned int> vertexIndices, normalIndices, uvIndices;

    vector<Vec3> temp_vertices;
    vector<Vec3> temp_normals;
    vector<Vec2> temp_uvs;

    string lineHeader;
    stringstream ss;
    string prefix;
    GLint temp_glint;


    while (getline(file, lineHeader))
    {
        ss.clear();
        ss.str(lineHeader);
        ss >> prefix;

        if (prefix == "v")
        {
            Vec3 vertex;
            ss >> vertex.x >> vertex.y >> vertex.z;
            temp_vertices.push_back(vertex);
        }
        else if (prefix == "vt")
        {
            Vec2 uv;
            ss >> uv.x >> uv.y;
            temp_uvs.push_back(uv);

        }
        else if (prefix == "vn")
        {
            Vec3 normal;
            ss >> normal.x >> normal.y >> normal.z;
            temp_normals.push_back(normal);
        }
        else if (prefix == "f")
        {
            int counter = 0;
            while (ss >> temp_glint)
            {
                if (counter == 0)
                    vertexIndices.push_back(temp_glint);
                else if (counter == 1)
                    uvIndices.push_back(temp_glint);
                else if (counter == 2)
                    normalIndices.push_back(temp_glint);

                if (ss.peek() == '/')
                {
                    ++counter;
                    ss.ignore(1, '/');
                }
                else if (ss.peek() == ' ')
                {
                    ++counter;
                    ss.ignore(1, ' ');
                }

                if (counter > 2)
                    counter = 0;
            }
        }
    }

    vertices.resize(vertexIndices.size(), Vertex());

    for (size_t i = 0; i < vertices.size(); ++i)
    {
        vertices[i].Position = temp_vertices[vertexIndices[i] - 1];
        vertices[i].TextureUV = temp_uvs[uvIndices[i] - 1];
        vertices[i].Normal = temp_normals[normalIndices[i] - 1];
    }
    log.Print("%s is loaded\n", path);
}

void Model::unloadSource()
{
	vertices.clear();
	indexes.clear();
}