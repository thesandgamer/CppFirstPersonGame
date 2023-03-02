#include "Trigger.h"

Trigger::Trigger()
{
}

Trigger::Trigger(Vector3 posP, Vector3 sizeP )
{
	transform.translation = posP;
	transform.scale = sizeP;

	collision.SetParent(&transform);
	collision.id = 17;
}

Trigger::~Trigger()
{
}

void Trigger::Start()
{
	collision.trigger = true;
	collision.collideWithLayer = Layer3;
	triggered();
}

void Trigger::Draw()
{
	collision.Draw();
}

void Trigger::Update()
{
}

void Trigger::AddFunctionToTrigger(std::function<void()> function)
{

	functionsTriggered.push_back(function);

}

void Trigger::triggered()
{
	for (auto i = functionsTriggered.begin(); i != functionsTriggered.end(); ++i)
	{
		(*i)();
	}
	/*
	for (int i = 0; i > functionsTriggered.size(); i++)
	{
		functionsTriggered.at(i)();
	}*/
}
