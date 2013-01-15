
#pragma once

/////////////////////////////////////////////////////////////////////////////
// CObjectViewTree 窗口

class CObjectViewTree : public CTreeCtrl
{
// 构造
public:
	CObjectViewTree();

	void							UpdateGameObjectTree(ld3d::GameObjectPtr pRoot);
	void							DeleteTree();
	ld3d::GameObjectPtr			GetGameObject(HTREEITEM hObj);
	void							EraseItem(HTREEITEM hItem);
private:
	void							_update_object_tree(ld3d::GameObjectPtr pRoot, HTREEITEM hRoot);
	void							_delete_gameobject_tree(HTREEITEM hRoot);
// 重写
protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);

// 实现
public:
	virtual ~CObjectViewTree();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
	afx_msg void OnTvnBeginlabeledit(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnEndlabeledit(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnBegindrag(NMHDR *pNMHDR, LRESULT *pResult);


private:
	bool							m_bDragging;
	HTREEITEM						m_hDragItem;
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};
