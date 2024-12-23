#ifndef RENDEREDOBJECT_H
#define RENDEREDOBJECT_H

#include "Model.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Shader.h"
#include "IdGenerator.h"
/*
Class RenderedObject contains the properties of an object to be rendered
TO_DO: Write implementation of the class
*/

class RenderedObject 
{
public:
	RenderedObject(Model* model,
		glm::vec3 translate = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3 rotationAngles = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f)
	);
	~RenderedObject();
	void renderObject(Shader& shader);

	//Setters for the translation vector
	void inline setTranslationX(float xpos)
	{
		translateVector.x = xpos;
	}

	void inline setTranslationY(float ypos)
	{
		translateVector.y = ypos;
	}

	void inline setTranslationZ(float zpos)
	{
		translateVector.z = zpos;
	}

	//Setters for the rotation vector
	void inline setRotationX(float xAngle)
	{
		rotationVector.x = xAngle;
	}

	void inline setRotationY(float yAngle)
	{
		rotationVector.y = yAngle;
	}

	void inline setRotationZ(float zAngle)
	{
		rotationVector.z = zAngle;
	}

	//Setters for the scale vector
	void inline setScaleX(float xScale)
	{
		scaleVector.x = xScale;
	}

	void inline setScaleY(float yScale)
	{
		scaleVector.y = yScale;
	}

	void inline setScaleZ(float zScale)
	{
		scaleVector.z = zScale;

	}

	//Getters for the translation vector
	float inline getTranslateX()
	{
		return translateVector.x;
	}
	float inline getTranslateY()
	{
		return translateVector.y;
	}
	float inline getTranslateZ()
	{
		return translateVector.z;
	}

	//Getters for the rotation vector
	float inline getRotateX()
	{
		return rotationVector.x;
	}
	float inline getRotateY()
	{
		return rotationVector.y;
	}
	float inline getRotateZ()
	{
		return rotationVector.z;
	}

	//Getters for the rotation vector
	float inline getScaleX()
	{
		return scaleVector.x;
	}
	float inline getScaleY()
	{
		return scaleVector.y;
	}
	float inline getScaleZ()
	{
		return scaleVector.z;
	}

private:
	std::string objectID;
	glm::vec3 translateVector;
	glm::vec3 rotationVector;
	glm::vec3 scaleVector;

	float opacity;
	Model* modelToRender;
};
#endif
