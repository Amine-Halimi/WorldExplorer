#include "RenderedObject.h"

RenderedObject::RenderedObject(Model* model, 
	                           glm::vec3 translate, 
	                           glm::vec3 rotationAngles,
	                           glm::vec3 scale
                               )
{
	translateVector = translate;
	rotationVector = rotationAngles;
	scaleVector = scale;
	this->modelToRender = model;
}

RenderedObject::~RenderedObject()
{

}

void RenderedObject::renderObject(Shader& shader)
{
	// render the loaded model
	glm::mat4 spaceModel = glm::mat4(1.0f);
	spaceModel = glm::translate(spaceModel, translateVector);
	spaceModel = glm::rotate(spaceModel, glm::radians(rotationVector.x), glm::vec3(1.0f, 0.0f, 0.0f));
	spaceModel = glm::rotate(spaceModel, glm::radians(rotationVector.y), glm::vec3(0.0f, 1.0f, 0.0f));
	spaceModel = glm::rotate(spaceModel, glm::radians(rotationVector.z), glm::vec3(0.0f, 0.0f, 1.0f));

	spaceModel = glm::scale(spaceModel, scaleVector);
	shader.setMat4("model", spaceModel);

	modelToRender->Draw(shader);
}