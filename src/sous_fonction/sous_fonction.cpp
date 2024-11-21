#include <sil/sil.hpp>

// pour l'exercice du tri de pixel 
float brightness(glm::vec3 const&color){
    float gray = color.r * 0.21 + color.g *0.72 + color.b * 0.07;

    return gray;
}


// Dégradé couleur - OkLab 
struct Lab {float L; float a; float b;};
struct RGB {float r; float g; float b;};

    // Conversion des formats de couleur 
        // 1 - srgb en linear 
            // srgb = format lu en c++
        // 2 - linear en oklab
        // 3 - oklab to linear (inverser dans le code pcq pour l'appel de fonction)
        // 4 - linear to srgb 
glm::vec3 srgb_to_linear(glm::vec3 c){
    for(int i = 0; i < 3; i++ ){
        if (c[i] <= 0.04045){
            c[i] = c[i] / 12.92;
        }
        else{
            c[i] = pow((c[i] + 0.055) / 1.055, 2.4);
        }
    } 
    return c;
}

glm::vec3 linear_to_oklab(glm::vec3 c) 
{
    c = srgb_to_linear(c);
    float l = 0.4121656120f * c.r + 0.5362752080f * c.g + 0.0514575653f * c.b;
    float m = 0.2118591070f * c.r + 0.6807189584f * c.g + 0.1074065790f * c.b;
    float s = 0.0883097947f * c.r + 0.2818474174f * c.g + 0.6302613616f * c.b;

    float l_ = cbrtf(l);
    float m_ = cbrtf(m);
    float s_ = cbrtf(s);

    return {
        0.2104542553f*l_ + 0.7936177850f*m_ - 0.0040720468f*s_,
        1.9779984951f*l_ - 2.4285922050f*m_ + 0.4505937099f*s_,
        0.0259040371f*l_ + 0.7827717662f*m_ - 0.8086757660f*s_,
    };
}

glm::vec3 linear_to_srgb(glm::vec3 c){
    for(int i = 0; i < 3; i++ ){
        if (c[i] <= 0.0031308){
            c[i] = c[i] * 12.92;
        }
        else{
            c[i] = 1.055 * pow(c[i], 1.0/2.4) - 0.055; 
        }
    } 
    return c;
    
}

glm::vec3 oklab_to_linear(glm::vec3 c) 
{
    float l_ = c.r + 0.3963377774f * c.g + 0.2158037573f * c.b;
    float m_ = c.r - 0.1055613458f * c.g - 0.0638541728f * c.b;
    float s_ = c.r - 0.0894841775f * c.g - 1.2914855480f * c.b;

    float l = l_*l_*l_;
    float m = m_*m_*m_;
    float s = s_*s_*s_;

    return linear_to_srgb({
        + 4.0767245293f*l - 3.3072168827f*m + 0.2307590544f*s,
        - 1.2681437731f*l + 2.6093323231f*m - 0.3411344290f*s,
        - 0.0041119885f*l - 0.7034763098f*m + 1.7068625689f*s,
    });
}



