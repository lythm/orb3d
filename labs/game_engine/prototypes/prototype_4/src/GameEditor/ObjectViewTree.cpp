
#include "stdafx.h"
#include "ObjectViewTree.h"

#include "AppContext.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CObjectViewTree

CObjectViewTree::CObjectViewTree()
{
	m_bDragging= false;
}

CObjectViewTree::~CObjectViewTree()
{
	//DeleteTree();
}

BEGIN_MESSAGE_MAP(CObjectViewTree, CTreeCtrl)
	ON_WM_DESTROY()
	ON_NOTIFY_REFLECT(TVN_BEGINLABELEDIT, &CObjectViewTree::OnTvnBeginlabeledit)
	ON_NOTIFY_REFLECT(TVN_ENDLABELEDIT, &CObjectViewTree::OnTvnEndlabeledit)
	//	ON_COMMAND(ID_OV_RENAME, &CObjectViewTree::OnOvRename)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CObjectViewTree::OnTvnSelchanged)
	ON_NOTIFY_REFLECT(TVN_BEGINDRAG, &CObjectViewTree::OnTvnBegindrag)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CObjectViewTree 消息处理程序

BOOL CObjectViewTree::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
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
void CObjectViewTree::UpdateGameObjectTree()
{
	using namespace engine;

	DeleteTree();

	GameObjectPtr pRoot = AppContext::GetCoreApi()->Root();

	HTREEITEM hRoot = InsertItem(pRoot->GetName().c_str(), 5, 5);

	_update_object_tree(pRoot, hRoot);

	//Expand(hRoot, TVM_EXPAND);
}
void CObjectViewTree::_update_object_tree(engine::GameObjectPtr pRoot, HTREEITEM hRoot)
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
void CObjectViewTree::DeleteTree()
{
	_delete_gameobject_tree(GetRootItem());

	DeleteAllItems();
}
void CObjectViewTree::_delete_gameobject_tree(HTREEITEM hRoot)
{
	if(hRoot == NULL)
	{
		return;
	}

	using namespace engine;
	GameObjectPtr* pObj = (GameObjectPtr*)GetItemData(hRoot);

	delete pObj;

	SetItemData(hRoot, (DWORD_PTR)nullptr);

	HTREEITEM hItem = GetNextItem(hRoot, TVGN_CHILD);
	while(hItem)
	{
		_delete_gameobject_tree(hItem);
		hItem = GetNextSiblingItem(hItem);
	}
}
engine::GameObjectPtr CObjectViewTree::GetGameObject(HTREEITEM hObj)
{
	using namespace engine;

	if(hObj == nullptr)
	{
		return GameObjectPtr();
	}

	GameObjectPtr* pObj = (GameObjectPtr*)GetItemData(hObj);
	if(pObj == NULL)
	{
		return GameObjectPtr();
	}
	return *pObj;
}
void CObjectViewTree::EraseItem(HTREEITEM hItem)
{
	using namespace engine;
	GameObjectPtr* pObj = (GameObjectPtr*)GetItemData(hItem);

	delete pObj;
	DeleteItem(hItem);
}

void CObjectViewTree::OnDestroy()
{
	DeleteTree();
	CTreeCtrl::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
}


void CObjectViewTree::OnTvnBeginlabeledit(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTVDISPINFO pTVDispInfo = reinterpret_cast<LPNMTVDISPINFO>(pNMHDR);

	// TODO: 在此添加控件通知处理程序代码

	engine::GameObjectPtr pObj = GetGameObject(pTVDispInfo->item.hItem);
	if(pObj == NULL || pObj->IsRoot())
	{
		*pResult = 1;
		return;
	}

	*pResult = 0;
}


void CObjectViewTree::OnTvnEndlabeledit(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTVDISPINFO pTVDispInfo = reinterpret_cast<LPNMTVDISPINFO>(pNMHDR);

	engine::GameObjectPtr pObj = GetGameObject(pTVDispInfo->item.hItem);

	if(pObj == NULL || pTVDispInfo->item.pszText == nullptr)
	{
		*pResult = 0;
		return;
	}

	CString str = pTVDispInfo->item.pszText;

	if(str.GetLength() == 0)
	{
		*pResult = 0;
		return;
	}


	pObj->SetName(pTVDispInfo->item.pszText);

	AppContext::UpdatePropGrid(pObj);

	*pResult = 1;
}


//void CObjectViewTree::OnOvRename()
//{
//	// TODO: 在此添加命令处理程序代码
//
//	HTREEITEM hItem = GetSelectedItem();
//	if(hItem == NULL)
//	{
//		return;
//	}
//}


void CObjectViewTree::OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);

	engine::GameObjectPtr pObj = GetGameObject(pNMTreeView->itemNew.hItem);

	AppContext::UpdatePropGrid(pObj);
	AppContext::SetSelectedObject(pObj);

	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CObjectViewTree::OnTvnBegindrag(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);

	CRect rcItem;
	m_hDragItem = pNMTreeView->itemNew.hItem;

	if(GetGameObject(m_hDragItem) == nullptr)
	{
		m_hDragItem = nullptr;
		return;
	}

	GetItemRect(pNMTreeView->itemNew.hItem, rcItem, true);

	GetImageList(0)->BeginDrag(5, CPoint(0, 0));
	CImageList::DragEnter(this, pNMTreeView->ptDrag);

	ShowCursor(FALSE); 
	GetParent()->SetCapture();
	m_bDragging = true; 

	*pResult = 0;
}


void CObjectViewTree::OnMouseMove(UINT nFlags, CPoint point)
{
	HTREEITEM htiTarget;  // Handle to target item. 
	TVHITTESTINFO tvht;   // Hit test information. 

	if (m_bDragging) 
	{ 
		// Drag the item to the current position of the mouse pointer. 
		// First convert the dialog coordinates to control coordinates. 
		CPoint pt = point;
		GetParent()->ClientToScreen(&pt);
		ScreenToClient(&pt);

		CImageList::DragMove(point);

		CImageList::DragShowNolock(FALSE);

		// Find out if the pointer is on the item. If it is, 
		// highlight the item as a drop target. 
		tvht.pt.x = point.x; 
		tvht.pt.y = point.y; 
		if ((htiTarget = HitTest(&tvht)) != NULL) 
		{ 
			SelectDropTarget(htiTarget); 
		} 
		CImageList::DragShowNolock(TRUE);
	} 

	CTreeCtrl::OnMouseMove(nFlags, point);
}


void CObjectViewTree::OnLButtonUp(UINT nFlags, CPoint point)
{
	using namespace engine;

	bool bDropped = false;

	
	if (m_bDragging) 
	{ 
		// Get destination item.
		HTREEITEM htiDest = GetDropHilightItem();
		if (htiDest != NULL)
		{
			GameObjectPtr pSrc = GetGameObject(m_hDragItem);

			GameObjectPtr pDest = GetGameObject(htiDest);

			pDest == nullptr ? pDest = AppContext::GetCoreApi()->Root() : pDest;

			if(pDest != pSrc)
			{
				if(pDest->IsAncestor(pSrc) == false)
				{
					pSrc->UnLink();
					pSrc->LinkTo(pDest);
					bDropped = true;

				}
			}
		}

		Expand(htiDest, TVE_EXPAND );
		CImageList::EndDrag(); 
		SelectDropTarget(NULL);
		ReleaseCapture(); 
		ShowCursor(TRUE); 
		m_bDragging = false;
		m_hDragItem = NULL;

		if (bDropped)
		{
			AppContext::UpdateObjectView();
		}
	} 
	
	CTreeCtrl::OnLButtonUp(nFlags, point);
}
