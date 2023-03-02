#include "Trigger.h"

Trigger::Trigger()
{
	collision.SetParent(&transform);
	collision.id = 17;
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
	collision.checkingCollision = true;
	collision.collideWithLayer = Layer3;
}

void Trigger::Draw()
{
	collision.Draw();
}

void Trigger::Update()
{
	if (collision.IsColliding())
	{
		triggered();
	}
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
	
}
