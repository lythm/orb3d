#include "core_pch.h"

#include "core\Node.h"

namespace engine
{
	Node::Node(void)
	{
		m_LocalTransform.SetIdentity();

		m_pParent						= NULL;
		m_pFirstChild					= NULL;

		m_pNext							= NULL;
		m_pPrev							= NULL;
	}

	Node::~Node(void)
	{
		UnLink();
		Node* pNode = NULL;
		while(pNode = GetFirstChild())
		{
			pNode->UnLink();
			delete pNode;
		}
	}
	void Node::SetLocalTransform(const math::Matrix44& Local)
	{
		m_LocalTransform = Local;
	}
	const math::Matrix44& Node::GetLocalTransform() const
	{
		return m_LocalTransform;
	}
	const math::Matrix44& Node::GetWorldTransform()
	{
		UpdateWorldTransform();
		return m_WorldTransform;
	}
	void Node::SetTranslation(const math::Vector3& t)
	{
		m_LocalTransform.SetTranslation(t);
	}
	void Node::SetTranslation(Real x, Real y, Real z)
	{
		SetTranslation(math::Vector3(x, y, z));
	}
	void Node::Translate(const math::Vector3& t)
	{
		math::Vector3 ot = m_LocalTransform.GetTranslation();
		ot += t;
		m_LocalTransform.SetTranslation(ot);
	}
	void Node::Translate(Real x, Real y, Real z)
	{
		Translate(math::Vector3(x, y, z));
	}
	math::Vector3 Node::GetTranslation() const
	{
		return m_LocalTransform.GetTranslation();
	}
	void Node::SetRotation(const math::Quat& r)
	{
		m_LocalTransform = MatrixRotationQuat(r);
		
	}
	void Node::SetRotation(const math::Matrix44& rot)
	{
		m_LocalTransform.SetRow3(0, rot.GetRow3(0));
		m_LocalTransform.SetRow3(1, rot.GetRow3(1));
		m_LocalTransform.SetRow3(2, rot.GetRow3(2));
	}
	void Node::Rotate(const math::Quat& r)
	{
		using namespace math;
		Matrix44 rot = MatrixRotationQuat(GetRotation());
		rot *= MatrixRotationQuat(r);
		SetRotation(rot);
	}
	void Node::Rotate(const math::Matrix44& rot)
	{
		using namespace math;
		Matrix44 r = MatrixRotationQuat(GetRotation());
		r *= rot;
		SetRotation(r);
	}
	void Node::RotateAxis(const math::Vector3& axis, Real rad)
	{
		Rotate(math::QuatRotationAxis(axis, rad));
	}
	void Node::RotateAxisX(Real rad)
	{
		RotateAxis(math::Vector3(1, 0, 0), rad);
	}
	void Node::RotateAxisY(Real rad)
	{
		RotateAxis(math::Vector3(0, 1, 0), rad);
	}
	void Node::RotateAxisZ(Real rad)
	{
		RotateAxis(math::Vector3(0, 0, 1), rad);
	}

	void Node::SetRotationAxis(const math::Vector3& axis, Real rad)
	{
		SetRotation(math::QuatRotationAxis(axis, rad));
	}
	void Node::SetRotationAxisX(Real rad)
	{
		SetRotationAxis(math::Vector3(1, 0, 0), rad);
	}
	void Node::SetRotationAxisY(Real rad)
	{
		SetRotationAxis(math::Vector3(0, 1, 0), rad);
	}
	void Node::SetRotationAxisZ(Real rad)
	{
		SetRotationAxis(math::Vector3(0, 0, 1), rad);
	}
	math::Quat Node::GetRotation() const
	{
		return QuatRotationMatrix(m_LocalTransform);
	}
	void Node::SetScale(const math::Vector3& s)
	{
		m_LocalTransform.SetScale(s);
	}
	void Node::SetScale(Real x, Real y, Real z)
	{
		SetScale(math::Vector3(x, y, z));
	}
	math::Vector3 Node::GetScale() const
	{
		return m_LocalTransform.GetScale();
	}
	void Node::SetUnitformScale(Real s)
	{
		SetScale(math::Vector3(s, s, s));
	}
	void Node::LinkTo(Node* pParent)
	{
		if(m_pParent)
		{
			UnLink();
		}
		m_pParent = pParent;
		m_pNext = m_pParent->m_pFirstChild;
		if(m_pParent->m_pFirstChild)
		{
			m_pParent->m_pFirstChild->m_pPrev = this;
		}
		m_pPrev = NULL;
		m_pParent->m_pFirstChild = this;
	}
	void Node::UnLink()
	{
		if(m_pParent == NULL)
			return;

		if(m_pPrev)
		{
			m_pPrev->m_pNext = m_pNext;
		}
		if(m_pNext)
		{
			m_pNext->m_pPrev = m_pPrev;
		}
		if(m_pParent->m_pFirstChild == this)
		{
			m_pParent->m_pFirstChild = m_pNext;
		}
		m_pParent = NULL;
		m_pPrev = NULL;
		m_pNext = NULL;
	}
	Node* Node::GetFirstChild()
	{
		return m_pFirstChild;
	}
	void Node::UpdateWorldTransform()
	{
		m_WorldTransform = m_LocalTransform;
		if(m_pParent)
		{
			m_WorldTransform *= m_pParent->GetWorldTransform();
		}
	}
	Node* Node::GetPrevNode()
	{
		return m_pPrev;
	}
	Node* Node::GetNextNode()
	{
		return m_pNext;
	}
	void Node::SetPrevNode(Node* pNode)
	{
		m_pPrev = pNode;
	}
	void Node::SetNextNode(Node* pNode)
	{
		m_pNext = pNode;
	}
	void Node::LookAt(Node* pNode)
	{
		if(pNode == NULL)
			return;
		const math::Vector3& at = pNode->GetWorldTransform().GetTranslation();
		LookAt(at);
	}
	void Node::LookAt(const math::Vector3& at)
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
	Node* Node::GetParent()
	{
		return m_pParent;
	}
}