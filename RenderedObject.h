#ifndef RENDEREDOBJECT_H
#define RENDEREDOBJECT_H

#include "Model.h"

/*
Class RenderedObject contains the properties of an object to be rendered
TO_DO: Write implementation of the class
*/
class RenderedObject 
{
public:
	RenderedObject();
	~RenderedObject();
	void renderObject();
private:
	const int objectID; 
	Model* modelToRender;
};
#endif
