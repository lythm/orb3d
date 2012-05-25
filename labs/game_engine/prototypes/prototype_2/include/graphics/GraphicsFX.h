#pragma once


namespace engine
{
	class GraphicsFX
	{
	public:

		virtual void									Release()									= 0;
		
		virtual bool									Begin(uint32& passCount)					= 0;

		virtual void									ApplyPass(uint32 iPass)						= 0;

		virtual void									End()										= 0;

	protected:
		GraphicsFX(void)
		{
		}

		virtual ~GraphicsFX(void)
		{
		}
	};


}
