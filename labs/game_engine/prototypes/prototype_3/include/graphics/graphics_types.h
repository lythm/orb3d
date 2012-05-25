#pragma once

namespace engine
{
	class RenderData;
	class Texture;
	class Texture1D;
	class Texture2D;
	class Texture3D;

	class Shader;


	typedef boost::shared_ptr<Shader>						ShaderPtr;
	typedef boost::shared_ptr<Texture>						TexturePtr;
	typedef boost::shared_ptr<Texture1D>					Texture1DPtr;
	typedef boost::shared_ptr<Texture2D>					Texture2DPtr;
	typedef boost::shared_ptr<Texture3D>					Texture3DPtr;

	typedef boost::shared_ptr<RenderData>					RenderDataPtr;
}
