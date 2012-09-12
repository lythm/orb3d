#include "core_pch.h"
#include "..\..\include\core\GameObject.h"
#include "core\GameObjectComponent.h"

namespace engine
{
	GameObject::GameObject(void)
	{
		m_LocalTransform.SetIdentity();

		m_pParent						= GameObjectPtr();
		m_pFirstChild					= GameObjectPtr();

		m_pNext							= GameObjectPtr();
		m_pPrev							= GameObjectPtr();
	}


	GameObject::~GameObject(void)
	{
		Clear();

		ClearComponents();
	}
	void GameObject::ClearComponents()
	{
		for(size_t i = 0; i < m_components.size(); ++i)
		{
			m_components[i]->Attach(GameObjectPtr());
			m_components[i].reset();
		}

		m_components.clear();
	}
	void GameObject::Update()
	{
		GameObjectPtr pObj = boost::shared_dynamic_cast<GameObject>(GetFirstChild());

		while(pObj)
		{
			pObj->Update();
			pObj = boost::shared_dynamic_cast<GameObject>(pObj->GetNextNode());
		}

		UpdateComponents();
	}
	GameObjectPtr GameObject::ThisPtr()
	{
		return GameObjectPtr(boost::shared_dynamic_cast<GameObject>(shared_from_this()));
	}
	void GameObject::AddComponent(GameObjectComponentPtr pCom)
	{
		pCom->Attach(ThisPtr());

		m_components.push_back(pCom);
	}
	void GameObject::UpdateComponents()
	{
		for(size_t i = 0; i < m_components.size(); ++i)
		{
			m_components[i]->Update();
		}
	}
	GameObjectComponentPtr GameObject::GetComponent(const char* szName)
	{
		for(size_t i = 0; i < m_components.size(); ++i)
		{
			if(m_components[i]->GetName() == std::string(szName))
			{
				return m_components[i];
			}
		}

		return GameObjectComponentPtr();
	}

	void GameObject::Clear()
	{
		GameObjectPtr pObj = GetFirstChild();
				
		if(pObj == nullptr)
		{
			ClearComponents();
			UnLink();

			return;
		}

		while(pObj != nullptr)
		{
			GameObjectPtr pTmp = pObj->GetNextNode();

			pObj->Clear();
			
			pObj = pTmp;
		}

		ClearComponents();
		UnLink();
		
		m_pFirstChild.reset();
	}

	
	
	void GameObject::SetLocalTransform(const math::Matrix44& Local)
	{
		m_LocalTransform = Local;
	}
	const math::Matrix44& GameObject::GetLocalTransform() const
	{
		return m_LocalTransform;
	}
	const math::Matrix44& GameObject::GetWorldTransform()
	{
		UpdateWorldTransform();
		return m_WorldTransform;
	}
	void GameObject::SetTranslation(const math::Vector3& t)
	{
		m_LocalTransform.SetTranslation(t);
	}
	void GameObject::SetTranslation(Real x, Real y, Real z)
	{
		SetTranslation(math::Vector3(x, y, z));
	}
	void GameObject::Translate(const math::Vector3& t)
	{
		math::Vector3 ot = m_LocalTransform.GetTranslation();
		ot += t;
		m_LocalTransform.SetTranslation(ot);
	}
	void GameObject::Translate(Real x, Real y, Real z)
	{
		Translate(math::Vector3(x, y, z));
	}
	math::Vector3 GameObject::GetTranslation() const
	{
		return m_LocalTransform.GetTranslation();
	}
	void GameObject::SetRotation(const math::Quat& r)
	{
		m_LocalTransform = MatrixRotationQuat(r);
		
	}
	void GameObject::SetRotation(const math::Matrix44& rot)
	{
		m_LocalTransform.SetRow3(0, rot.GetRow3(0));
		m_LocalTransform.SetRow3(1, rot.GetRow3(1));
		m_LocalTransform.SetRow3(2, rot.GetRow3(2));
	}
	void GameObject::Rotate(const math::Quat& r)
	{
		using namespace math;
		Matrix44 rot = MatrixRotationQuat(GetRotation());
		rot *= MatrixRotationQuat(r);
		SetRotation(rot);
	}
	void GameObject::Rotate(const math::Matrix44& rot)
	{
		using namespace math;
		Matrix44 r = MatrixRotationQuat(GetRotation());
		r *= rot;
		SetRotation(r);
	}
	void GameObject::RotateAxis(const math::Vector3& axis, Real rad)
	{
		Rotate(math::QuatRotationAxis(axis, rad));
	}
	void GameObject::RotateAxisX(Real rad)
	{
		RotateAxis(math::Vector3(1, 0, 0), rad);
	}
	void GameObject::RotateAxisY(Real rad)
	{
		RotateAxis(math::Vector3(0, 1, 0), rad);
	}
	void GameObject::RotateAxisZ(Real rad)
	{
		RotateAxis(math::Vector3(0, 0, 1), rad);
	}

	void GameObject::SetRotationAxis(const math::Vector3& axis, Real rad)
	{
		SetRotation(math::QuatRotationAxis(axis, rad));
	}
	void GameObject::SetRotationAxisX(Real rad)
	{
		SetRotationAxis(math::Vector3(1, 0, 0), rad);
	}
	void GameObject::SetRotationAxisY(Real rad)
	{
		SetRotationAxis(math::Vector3(0, 1, 0), rad);
	}
	void GameObject::SetRotationAxisZ(Real rad)
	{
		SetRotationAxis(math::Vector3(0, 0, 1), rad);
	}
	math::Quat GameObject::GetRotation() const
	{
		return QuatRotationMatrix(m_LocalTransform);
	}
	void GameObject::SetScale(const math::Vector3& s)
	{
		m_LocalTransform.SetScale(s);
	}
	void GameObject::SetScale(Real x, Real y, Real z)
	{
		SetScale(math::Vector3(x, y, z));
	}
	math::Vector3 GameObject::GetScale() const
	{
		return m_LocalTransform.GetScale();
	}
	void GameObject::SetUnitformScale(Real s)
	{
		SetScale(math::Vector3(s, s, s));
	}
	void GameObject::LinkTo(GameObjectPtr pParent)
	{
		if(m_pParent)
		{
			UnLink();
		}
		m_pParent = pParent;
		m_pNext = m_pParent->m_pFirstChild;
		if(m_pParent->m_pFirstChild)
		{
			m_pParent->m_pFirstChild->m_pPrev = shared_from_this();
		}
		m_pPrev = GameObjectPtr();
		m_pParent->m_pFirstChild = shared_from_this();
	}
	void GameObject::UnLink()
	{

		if(m_pPrev)
		{
			m_pPrev->m_pNext = m_pNext;
		}
		if(m_pNext)
		{
			m_pNext->m_pPrev = m_pPrev;
		}

		if(m_pParent != GameObjectPtr() && m_pParent->m_pFirstChild == shared_from_this())
		{
			m_pParent->m_pFirstChild = m_pNext;
		}
		m_pParent = GameObjectPtr();
		m_pPrev = GameObjectPtr();
		m_pNext = GameObjectPtr();
	}
	GameObjectPtr GameObject::GetFirstChild()
	{
		return m_pFirstChild;
	}
	void GameObject::UpdateWorldTransform()
	{
		m_WorldTransform = m_LocalTransform;
		if(m_pParent)
		{
			m_WorldTransform *= m_pParent->GetWorldTransform();
		}
	}
	GameObjectPtr GameObject::GetPrevNode()
	{
		return m_pPrev;
	}
	GameObjectPtr GameObject::GetNextNode()
	{
		return m_pNext;
	}
	void GameObject::SetPrevNode(GameObjectPtr pNode)
	{
		m_pPrev = pNode;
	}
	void GameObject::SetNextNode(GameObjectPtr pNode)
	{
		m_pNext = pNode;
	}
	void GameObject::LookAt(GameObjectPtr pNode)
	{
		if(pNode == GameObjectPtr())
			return;
		const math::Vector3& at = pNode->GetWorldTransform().GetTranslation();
		LookAt(at);
	}
	void GameObject::LookAt(const math::Vector3& at)
	{
		using namespace math;
		Vector3 pos = m_LocalTransform.GetTranslation();
		Vector3 axis_z = at - pos;
		axis_z.Normalize();

		Vector3 axis_y(0, 1, 0);
		Vector3 axis_x = Cross(axis_y, axis_z);
		axis_x.Normalize();
		axis_y = Cross(axis_x, axis_z);
		axis_y.Normalize();

		m_LocalTransform.SetRow3(0, axis_x);
		m_LocalTransform.SetRow3(1, axis_y);
		m_LocalTransform.SetRow3(2, axis_z);
	}
	GameObjectPtr GameObject::GetParent()
	{
		return m_pParent;
	}
}