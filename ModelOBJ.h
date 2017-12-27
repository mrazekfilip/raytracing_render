#pragma once

#include <string>
#include <iostream>
#include "Model.h"

class ModelOBJ : public Model {
public:
    ModelOBJ() {
        std::cout << "ModelOBJ created" << std::endl;
    }
    
    bool load() override {
        std::cout << "load function" << std::endl;
        return true;
    }
    
    bool save(const std::string& filename) const override {
        std::cout << "save function " << filename << std::endl;
        return true;
    }
};