#pragma once

#include <vector>
#include <iostream>

enum class FormatTypeModel {
    OBJ,
    FBX,
    STL
};

struct Vec4{
    float x_, y_, z_, w_;

    Vec4(float x, float y, float z, float w = 1.0f)
        : x_(x), y_(y), z_(z), w_(w) {
    }
};

struct Vec3{
    float x_, y_, z_;

    Vec3(float x, float y, float z = 0.0f)
        : x_(x), y_(y), z_(z) {
    }
};

class Vertex {
private:
    Vec4* position_;
    Vec3* textureCoord_;
    Vec3* normal_;
public:
    Vertex() = default;

    Vertex(Vec4* position, Vec3* textureCoord, Vec3* normal)
        : position_(position), textureCoord_(textureCoord), normal_(normal) {
    }

    const Vec4* position() const {
        return position_;
    }

    void position(Vec4* position) {
        position_ = position;
    }

    const Vec3* textureCoord() const {
        return textureCoord_;
    }

    void textureCoord(Vec3* textureCoord) {
        textureCoord_ = textureCoord;
    }

    const Vec3* normal() const {
        return normal_;
    }

    void normal(Vec3* normal) {
        normal_ = normal;
    }   
};

struct Polygon {
    std::vector<Vertex> vertices_;

    void addVertex(const Vertex& vertex) {
        vertices_.push_back(vertex);
    }
};

struct BoundingBox {
    Vec3 center_;
    Vec3 size_;

    BoundingBox(const Vec3& center, const Vec3& size)
        : center_(center), size_(size) {
    }
};

class Model {
public:
    bool load(FormatTypeModel type, const std::string& filename);
    bool save(FormatTypeModel type, const std::string& filename) const;

    const std::vector<Polygon>& getPolygons() const {
        return polygons_;
    }
    
    void normalizeNormals();
    BoundingBox getBoundingBox() const;

private:
    std::vector<Vec4> vertexPositions_;
    std::vector<Vec3> textureCoord_;
    std::vector<Vec3> vertexNormals_;
    std::vector<Polygon> polygons_;

    bool loadOBJ(const std::string& filename);
    bool loadOBJVertexPosition(std::stringstream& stream);
    bool loadOBJTextureCoord(std::stringstream& stream);
    bool loadOBJNormal(std::stringstream& stream);
    Vertex loadOBJVertex(std::stringstream& stream);
    bool loadOBJPolygon(std::stringstream& stream);
    bool saveOBJ(const std::string& filename) const;
    void infoLog(std::ostream& o) const;
    
};