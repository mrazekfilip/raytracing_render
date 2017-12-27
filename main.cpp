#include <iostream>

#include "Model.h"

int main() {
    std::cout << "raytracing render" << std::endl;
    Model model;
    bool success = model.load(FormatTypeModel::OBJ, "test_models/man.obj");
    if (success) {
        std::cout << "model loaded successfully" << std::endl;
    }
    return 0;
}