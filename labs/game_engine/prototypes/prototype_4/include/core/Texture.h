#pragma once


namespace engine
{
	class EXPORT_CLASS Texture
	{
	public:
		enum TEXTURE_TYPE
		{
			TEX_1D,
			TEX_2D,
			TEX_3D,

			TEX_UNKNOWN,
		};

		

		Texture(void){}
		virtual ~Texture(void){}

		virtual TEXTURE_TYPE								GetType()								= 0;

		virtual void										Release()								= 0;

	};


}
