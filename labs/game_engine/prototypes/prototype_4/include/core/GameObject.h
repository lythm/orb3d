#pragma once

#include <boost\enable_shared_from_this.hpp>
namespace engine
{
	class EXPORT_CLASS GameObject : public boost::enable_shared_from_this<GameObject>
	{
	public:
		GameObject(void);
		virtual ~GameObject(void);
		
		void										Update();
		void										AddComponent(GameObjectComponentPtr pCom);
		
		GameObjectComponentPtr						GetComponent(const char* szName);
		GameObjectPtr								ThisPtr();

		void										ClearComponents();
		void										Clear();

		// local transform operation
		void										SetLocalTransform(const math::Matrix44& Local);
		const math::Matrix44&						GetLocalTransform() const;

		// translation
		void										SetTranslation(const math::Vector3& t);
		void										SetTranslation(Real x, Real y, Real z);

		void										Translate(const math::Vector3& t);
		void										Translate(Real x, Real y, Real z);

		math::Vector3								GetTranslation() const;

		// rotation
		void										SetRotationAxis(const math::Vector3& axis, Real rad);
		void										SetRotationAxisX(Real rad);
		void										SetRotationAxisY(Real rad);
		void										SetRotationAxisZ(Real rad);
		void										SetRotation(const math::Quat& r);
		void										SetRotation(const math::Matrix44& rot);

		void										Rotate(const math::Quat& r);
		void										Rotate(const math::Matrix44& rot);
		void										RotateAxis(const math::Vector3& axis, Real rad);
		void										RotateAxisX(Real rad);
		void										RotateAxisY(Real rad);
		void										RotateAxisZ(Real rad);

		math::Quat									GetRotation() const;

		// scale
		void										SetScale(const math::Vector3& s);
		void										SetScale(Real x, Real y, Real z);
		math::Vector3								GetScale() const;
		void										SetUnitformScale(Real s);

		void										LookAt(GameObjectPtr pObj);
		void										LookAt(const math::Vector3& at);

		// parent/child operatio					n
		void										LinkTo(GameObjectPtr pParent);
		void										UnLink();
		GameObjectPtr								GetFirstChild();

		GameObjectPtr								GetParent();

		GameObjectPtr								GetPrevNode();
		GameObjectPtr								GetNextNode();
		void										SetPrevNode(GameObjectPtr pNode);
		void										SetNextNode(GameObjectPtr pNode);



		// world transform operation
		const math::Matrix44&						GetWorldTransform();

	private:
		void										UpdateWorldTransform();

		void										UpdateComponents();

	private:
		math::Matrix44								m_LocalTransform;
		math::Matrix44								m_WorldTransform;

		GameObjectPtr								m_pParent;
		GameObjectPtr								m_pFirstChild;

		GameObjectPtr								m_pNext;
		GameObjectPtr								m_pPrev;

		std::vector<GameObjectComponentPtr>			m_components;

	};
}