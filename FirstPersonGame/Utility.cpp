#include "Utility.h"

void Utility::Start()
{
	dotTexture = LoadTexture("../resources/Dot.png");
}

void Utility::AddModel(Model* model)
{
	cubesModels.push_back(model);
}



void Utility::Unload()
{
	for (Model* cube : cubesModels)
	{
		UnloadModel(*cube);
	}
	UnloadTexture(dotTexture);
	UnloadShader(*shader);
}