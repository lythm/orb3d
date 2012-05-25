#pragma once


namespace engine
{
	class EXPORT_CLASS MeshUtil
	{
	public:

		static MeshPtr									CreateBox();

	private:
		MeshUtil(void);
		virtual ~MeshUtil(void);
	};


}
