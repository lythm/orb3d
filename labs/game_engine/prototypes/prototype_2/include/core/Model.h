#pragma once

namespace engine
{
	class Model
	{
	public:
		Model(void);
		virtual ~Model(void);


		void												Update();

	private:

		MeshPtr												m_pMesh;
	};
}
