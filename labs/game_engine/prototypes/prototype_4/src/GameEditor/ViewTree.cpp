
#include "stdafx.h"
#include "ViewTree.h"

#include "AppContext.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewTree

CViewTree::CViewTree()
{
}

CViewTree::~CViewTree()
{
	DeleteTree();
}

BEGIN_MESSAGE_MAP(CViewTree, CTreeCtrl)
	ON_WM_DESTROY()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewTree 消息处理程序

BOOL CViewTree::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	BOOL bRes = CTreeCtrl::OnNotify(wParam, lParam, pResult);

	NMHDR* pNMHDR = (NMHDR*)lParam;
	ASSERT(pNMHDR != NULL);

	if (pNMHDR && pNMHDR->code == TTN_SHOW && GetToolTips() != NULL)
	{
		GetToolTips()->SetWindowPos(&wndTop, -1, -1, -1, -1, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSIZE);
	}

	return bRes;
}
void CViewTree::UpdateGameObjectTree()
{
	using namespace engine;

	DeleteTree();

	GameObjectPtr pRoot = AppContext::GetCoreApi()->GetRoot();

	HTREEITEM hRoot = InsertItem(pRoot->GetName().c_str(), 5, 5);
	
	_update_object_tree(pRoot, hRoot);
}
void CViewTree::_update_object_tree(engine::GameObjectPtr pRoot, HTREEITEM hRoot)
{
	if(pRoot == NULL)
	{
		return;
	}
	
	using namespace engine;
	GameObjectPtr pObj = pRoot->GetFirstChild();

	while(pObj)
	{
		HTREEITEM hObj = InsertItem(pObj->GetName().c_str(), 5, 5, hRoot);

		GameObjectPtr* pContext = new GameObjectPtr;
		*pContext = pObj;

		SetItemData(hObj, (DWORD_PTR)pContext);
		_update_object_tree(pObj, hObj);
		pObj = pObj->GetNextNode();
	}
}
void CViewTree::DeleteTree()
{
	_delete_gameobject_tree(GetRootItem());

	DeleteAllItems();
}
void CViewTree::_delete_gameobject_tree(HTREEITEM hRoot)
{
	if(hRoot == NULL)
	{
		return;
	}

	using namespace engine;
	GameObjectPtr* pObj = (GameObjectPtr*)GetItemData(hRoot);

	if(pObj != NULL)
	{
		(*pObj)->Clear();
		delete pObj;
	}

	HTREEITEM hItem = GetNextItem(hRoot, TVGN_CHILD);
	while(hItem)
	{
		_delete_gameobject_tree(hItem);
		hItem = GetNextSiblingItem(hItem);
	}
}
engine::GameObjectPtr CViewTree::GetGameObject(HTREEITEM hObj)
{
	using namespace engine;
	GameObjectPtr* pObj = (GameObjectPtr*)GetItemData(hObj);

	return *pObj;
}
void CViewTree::EraseItem(HTREEITEM hItem)
{
	using namespace engine;
	GameObjectPtr* pObj = (GameObjectPtr*)GetItemData(hItem);

	(*pObj)->Clear();
	delete pObj;

	DeleteItem(hItem);

}

void CViewTree::OnDestroy()
{

	DeleteTree();
	CTreeCtrl::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
}
