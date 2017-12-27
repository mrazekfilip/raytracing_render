#pragma once

#include <vector>
#include <iostream>

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
    std::vector<Vertex> vertices;
};

struct BoundingBox {
    Vec3 point;
    Vec3 size;
};

class Model {
protected:
    std::vector<Vec4> vertexPositions_;
    std::vector<Vec3> textureCoord_;
    std::vector<Vec3> vertexNormals_;
    std::vector<Polygon> vertices_;

public:
    Model() {
        std::cout << "Model created" << std::endl;
    }

    virtual ~Model() = default;
    virtual bool load() = 0;
    virtual bool save(const std::string& filename) const = 0;

    const std::vector<Polygon>& getVertices() const {
        return vertices_;
    }
    
    void normalizeNormals();
    BoundingBox getBoundingBox() const;
    
};