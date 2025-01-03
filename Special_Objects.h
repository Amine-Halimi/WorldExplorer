#ifndef SPECIAL_OBJECTS_H
#define SPECIAL_OBJECTS_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Shader.h"

struct componentObject
{
    int componentId;
};

struct LightObject: componentObject{
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    virtual void applyLightOnShader(Shader &shader)
    {

    }
};
//
struct DirectionalLightObject: LightObject {
    glm::vec3 direction;

    void applyLightOnShader(Shader& shader)
    {
        shader.setVec3("dirLight.direction", direction);
        shader.setVec3("dirLight.ambient", ambient);
        shader.setVec3("dirLight.diffuse", diffuse);
        shader.setVec3("dirLight.specular", specular);
    }
};


struct PointLightObject: LightObject {
    int indexOfPointLight;
    glm::vec3 position;

    float constant;
    float linear;
    float quadratic;

    void applyLightOnShader(Shader& shader)
    {
        std::string name = "pointlights[" + std::to_string(indexOfPointLight) + "].";
        shader.setVec3(name + "position", position);
        shader.setVec3(name + "ambient", ambient);
        shader.setVec3(name + "diffuse", diffuse);
        shader.setVec3(name + "specular", specular);

        shader.setFloat(name + "constant", constant);
        shader.setFloat(name + "linear", linear);
        shader.setFloat(name + "quadratic", quadratic);
    }
};

struct SpotLightObject: LightObject {
    glm::vec3 viewDirection;
    glm::vec3 viewPosition;

    float constant;
    float linear;
    float quadratic;
    float cutOffAngle;
    float outerCutOffAngle;

    void applyLightOnShader(Shader& shader)
    {
        shader.setVec3("spotlight.position", viewPosition);
        shader.setVec3("spotlight.direction", viewDirection);
        shader.setFloat("spotlight.cutOff", glm::cos(glm::radians(cutOffAngle)));
        shader.setFloat("spotlight.outerCutOff", glm::cos(glm::radians(outerCutOffAngle)));
        shader.setVec3("spotlight.ambient", ambient);
        shader.setVec3("spotlight.diffuse", diffuse);
        shader.setVec3("spotlight.specular", specular);
        shader.setFloat("spotlight.constant", constant);
        shader.setFloat("spotlight.linear", linear);
        shader.setFloat("spotlight.quadratic", quadratic);
    }
};





#endif
