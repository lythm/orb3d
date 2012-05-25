#pragma once


namespace engine
{
	class RenderQueue
	{
	public:
		RenderQueue(void);
		virtual ~RenderQueue(void);

		void								Push(RenderDataPtr pData);
		void								Clear();
		RenderDataPtr						GetAt(uint32 index);
		uint32								GetLength();

	private:

		std::vector<RenderDataPtr>			m_queue;
	};
}