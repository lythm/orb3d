#pragma once

namespace graphics
{

	class Effect
	{
	public:

		Effect(void)
		{
		}

		virtual ~Effect(void)
		{
		}

		virtual unsigned int						Begin()						= 0;
		virtual void								End()						= 0;
		virtual void								ApplyPass()					= 0;

	};


}
