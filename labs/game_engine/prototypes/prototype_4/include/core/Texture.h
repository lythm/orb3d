#pragma once


namespace engine
{
	class EXPORT_CLASS Texture
	{
	public:
		enum TEXTURE_TYPE
		{
			TEXTURE_1D,
			TEXTURE_2D,
			TEXTURE_3D,
		};
		Texture(void){}
		virtual ~Texture(void){}

		virtual TEXTURE_TYPE								GetType()								= 0;

	};


}
