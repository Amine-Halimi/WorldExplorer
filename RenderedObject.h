#ifndef RENDEREDOBJECT_H
#define RENDEREDOBJECT_H

#include "Model.h"
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
