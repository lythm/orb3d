#include "core_ext_pch.h"
#include "..\..\include\core\ext\Behavior.h"
#include "Package.h"

namespace engine
{
	Behavior::Behavior(void):GameObjectComponent(L"Behavior")
	{
	}


	Behavior::~Behavior(void)
	{
	}
	void Behavior::Update()
	{
	}
	bool Behavior::OnAttach()
	{
		return true;
	}
	void Behavior::OnDetach()
	{
	}
}
