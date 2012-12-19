#pragma once

namespace engine
{
	class PropertyManager;
	class MeshRenderer;
	class MeshData;
	class WorldMeshRenderer;
	class LightData;

	typedef boost::shared_ptr<PropertyManager>									PropertyManagerPtr;
	typedef boost::shared_ptr<MeshData>											MeshDataPtr;
	typedef boost::shared_ptr<MeshRenderer>										MeshRendererPtr;
	typedef boost::shared_ptr<LightData>										LightDataPtr;
	typedef boost::shared_ptr<WorldMeshRenderer>								WorldMeshRendererPtr;
}