#include <algorithm>
#include <array>
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <string>
#include <fstream>

#include "Model.h"

bool Model::load(FormatTypeModel type, const std::string& filename) {
    switch(type) {
    case FormatTypeModel::OBJ:
        return loadOBJ(filename);
    default:
        std::cerr << "can not open file format" << std::endl;
        return false;
    }
}

bool Model::save(FormatTypeModel type, const std::string& filename) const {
    return false;
}

void Model::normalizeNormals() {
    std::for_each(
        vertexNormals_.begin(), 
        vertexNormals_.end(),
        [](Vec3& v) {
            float size = sqrt(v.x_ * v.x_ + v.y_ * v.y_ + v.z_ * v.z_);
            v.x_ /= size;
            v.y_ /= size;
            v.z_ /= size;
        }
    );
}

BoundingBox Model::getBoundingBox() const {
    if (vertexPositions_.empty()) {
        return BoundingBox({0,0,0}, {0,0,0});
    }
    std::array<float, 2> x, y, z;
    x.fill(vertexPositions_[0].x_);
    y.fill(vertexPositions_[0].y_);
    z.fill(vertexPositions_[0].z_);

    for (const Vec4& v : vertexPositions_) {
        if (v.x_ < x[0]) {
            x[0] = v.x_;
        } else if (v.x_ > x[1]) {
            x[1] = v.x_;
        }

        if (v.y_ < y[0]) {
            y[0] = v.y_;
        } else if (v.y_ > y[1]) {
            y[1] = v.y_;
        }

        if (v.z_ < z[0]) {
            z[0] = v.z_;
        } else if (v.z_ > z[1]) {
            z[1] = v.z_;
        }
    }
    return BoundingBox({(x[0] + x[1]) / 2, (y[0] + y[1]) / 2, (z[0] + z[1]) / 2}, 
        {abs(x[0] - x[1]), abs(y[0] - y[1]), abs(z[0] - z[1])});
}

bool Model::loadOBJ(const std::string& filename) {
    std::cout << "loading .obj file " << filename << std::endl;
    
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "file does not exist" << std::endl;
        return false;
    }

    std::string lineString;
    std::string descriptor;
    std::getline(file, lineString);
    while(!file.eof()) {
        std::stringstream line(lineString);
        line >> descriptor;

        if (descriptor == "v") {
            if (!loadOBJVertexPosition(line)) return false;
        } else if (descriptor == "vt") {
            if (!loadOBJTextureCoord(line)) return false;
        } else if (descriptor == "vn") {
            if (!loadOBJNormal(line)) return false;
        } else if (descriptor == "f") {
            if (!loadOBJPolygon(line)) return false;
        }

        std::getline(file, lineString);
    }

    infoLog(std::cout);

    return true;
}

bool Model::loadOBJVertexPosition(std::stringstream& stream) {
    float x, y, z, w;
    stream >> x >> y >> z;
    if (stream.fail()) {
        std::cerr << "ERROR: read vertex position: wrong format" << std::endl;
        return false;
    }
    stream >> w;
    if (stream.fail()) {
        w = 1;
    }
    vertexPositions_.emplace_back(x, y, z, w);
    return true;
}

bool Model::loadOBJTextureCoord(std::stringstream& stream) {
    float u, v, w;
    stream >> u >> v;
    if (stream.fail()) {
        std::cerr << "ERROR: read texture coordinate: wrong format" << std::endl;
        return false;
    }
    stream >> w;
    if (stream.fail()) {
        w = 0;
    }
    textureCoord_.emplace_back(u, v, w);
    return true;
}

bool Model::loadOBJNormal(std::stringstream& stream) {
    float x, y, z;
    stream >> x >> y >> z;
    if (stream.fail()) {
        std::cerr << "ERROR: read normal: wrong format" << std::endl;
        return false;
    }
    vertexNormals_.emplace_back(x, y, z);
    return true;
}

Vertex Model::loadOBJVertex(std::stringstream& stream) {
    Vec4* vPtr = nullptr;
    Vec3* vtPtr = nullptr;
    Vec3* vnPtr = nullptr;

    unsigned int v;
    stream >> v;
    vPtr = &vertexPositions_.at(v - 1);
    stream.get();

    unsigned int vt;
    stream >> vt;
    if (stream.good()) {
        vtPtr = &textureCoord_.at(vt - 1);
    }
    stream.get();
    
    unsigned int vn;
    stream >> vn;
    if (!stream.fail()) {
        vnPtr = &vertexNormals_.at(vn - 1);
    }

    return Vertex(vPtr, vtPtr, vnPtr);
}

bool Model::loadOBJPolygon(std::stringstream& stream) {
    Polygon p;
    std::string vertex;
    while (!stream.eof()) {
        stream >> vertex;
        std::stringstream vertexStream(vertex);
        Vertex v;
        try {
            v = loadOBJVertex(vertexStream);
        } catch (std::out_of_range& e) {
            std::cerr << "ERROR: read polygon: wrong format" << std::endl;
            return false;
        }
        p.addVertex(v);
    }
    polygons_.push_back(p);
    return true;
}



bool Model::saveOBJ(const std::string& filename) const {
    //TODO
    return true;
}

void Model::infoLog(std::ostream& o) const {
    o << "Model contains of:\n"
        << "vertex position count: " << vertexPositions_.size() << "\n"
        << "texture coordinates count: " << textureCoord_.size() << "\n"
        << "normals count: " << vertexNormals_.size() << "\n"
        << "polygons count: " << polygons_.size()
        << std::endl;
}