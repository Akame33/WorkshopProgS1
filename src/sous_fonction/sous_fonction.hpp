#pragma once
#include <sil/sil.hpp>

float brightness(glm::vec3 const&color);


struct Lab {float L; float a; float b;};
struct RGB {float r; float g; float b;};
glm::vec3 linear_to_oklab(glm::vec3 c);
glm::vec3 oklab_to_linear(glm::vec3 c);