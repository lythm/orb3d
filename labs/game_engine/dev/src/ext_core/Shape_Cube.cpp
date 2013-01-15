#include "core_ext_pch.h"
#include "..\..\include\core\ext\Shape_Cube.h"

namespace ld3d
{
	Shape_Cube::Shape_Cube(GameObjectManagerPtr pManager):GameObjectComponent(L"Shape_Cube", pManager)
	{

	}


	Shape_Cube::~Shape_Cube(void)
	{
	}
	void Shape_Cube::Update()
	{
		
	}

	
	bool Shape_Cube::OnAttach()
	{
		PropertyManagerPtr pPM = boost::shared_dynamic_cast<PropertyManager>(m_pObject->GetComponent(L"PropertyManager"));

		pPM->Begin(L"Shape_Cube");
		{
		}
		pPM->End();

		return true;
	}
	void Shape_Cube::OnDetach()
	{
		
	}
}
