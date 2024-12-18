#ifndef SCENE_H
#define SCENE_H
/*
The Scene class contains the list of objects and renders them in a scene.
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
	std::vector<RenderedObject> objectsToRender;
};
#endif // !SCENE_H

