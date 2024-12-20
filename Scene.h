#ifndef SCENE_H
#define SCENE_H
/*
The Scene class stores a list the list of objects and renders them.
TO_DO: Write implementationfor Scene class
*/


#include "RenderedObject.h"
#include "vector"


class Scene
{
public:
	Scene();
	~Scene();

	void renderScene();
private:
	int sceneId;
	std::vector<RenderedObject> objectsToRender;
};
#endif // !SCENE_H

