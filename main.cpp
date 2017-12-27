#include <iostream>

#include "Model.h"
#include "ModelOBJ.h"

int main() {
    std::cout << "raytracing render" << std::endl;
    const Model& model = ModelOBJ();
    return 0; 
}