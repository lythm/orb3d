#pragma once

namespace engine
{
	class Texture
	{
	public:

		virtual void										Release()							= 0;

	protected:
		Texture(void){}

		virtual ~Texture(void){}
	};

}