#pragma once

#include "utils\PropertySet.h"

namespace ld3d
{
	enum
	{
		property_type_internal = property_type_custum + 0,
		property_type_matrix44,
		property_type_vector3,
		property_type_vector2,
		property_type_color,
		property_type_mesh,
		property_type_light,

	};

	
	template <>
	PropType PropTypeId<math::Matrix44>::m_type		= PropType(property_type_matrix44);
	template <>
	PropType PropTypeId<math::Vector3>::m_type		= PropType(property_type_vector3);
	template <>
	PropType PropTypeId<math::Vector2>::m_type		= PropType(property_type_vector2);
	template <>
	PropType PropTypeId<math::Color4>::m_type		= PropType(property_type_color);
	template <>
	PropType PropTypeId<Mesh>::m_type				= PropType(property_type_mesh);
	template <>
	PropType PropTypeId<Light>::m_type				= PropType(property_type_light);



	// general
	typedef Property_T<std::wstring>				StringProperty;
	typedef Property_T<bool>						BoolProperty;
	typedef Property_T<int>							IntProperty;
	typedef Property_T<float>						FloatProperty;
	typedef Property_T<void*>						PointerProperty;

	// used by core
	typedef Property_T<math::Matrix44>				Matrix44Property;
	typedef Property_T<math::Vector3>				Vector3Property;
	typedef Property_T<math::Vector2>				Vector2Property;
	typedef Property_T<math::Color4>				ColorProperty;
	typedef Property_T<Mesh>						MeshProperty;
	typedef Property_T<Light>						LightProperty;

	
}