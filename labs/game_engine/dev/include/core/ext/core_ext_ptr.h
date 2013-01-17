#pragma once

namespace ld3d
{
	class PropertyManager;
	class MeshRenderer;
	class MeshData;
	class WorldMeshRenderer;
	class Behavior;
	class Light_Dir;
	class Light_Point;
	class Light_Spot;
	class Light_Sky;
	class CameraData;

	typedef boost::shared_ptr<CameraData>										CameraDataPtr;
	typedef boost::shared_ptr<Light_Sky>										Light_SkyPtr;
	typedef boost::shared_ptr<Light_Spot>										Light_SpotPtr;
	typedef boost::shared_ptr<Light_Point>										Light_PointPtr;
	typedef boost::shared_ptr<Light_Dir>										Light_DirPtr;
	typedef boost::shared_ptr<Behavior>											BehaviorPtr;
	typedef boost::shared_ptr<PropertyManager>									PropertyManagerPtr;
	typedef boost::shared_ptr<MeshData>											MeshDataPtr;
	typedef boost::shared_ptr<MeshRenderer>										MeshRendererPtr;
	typedef boost::shared_ptr<WorldMeshRenderer>								WorldMeshRendererPtr;
}