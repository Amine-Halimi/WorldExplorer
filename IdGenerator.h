#ifndef IDGENERATOR_H
#define IDGENERATOR_H

/*
* TO_DO Create a function that generate an ID for each of the objects rendered in a specific project. 
* 
*/

class IdGenerator
{
public:
	IdGenerator()
	{

	};
	~IdGenerator()
	{

	};

	const int inline createObjectId()
	{
		return objectIdNum++;
	}

	const int inline createSceneId()
	{
		return sceneIdNum++;
	}

	const int inline createWindowId()
	{
		return windowIdNum++;
	}
private:
	int objectIdNum{ 1 };
	int sceneIdNum{ 1 };
	int windowIdNum{ 1 };
};



#endif
