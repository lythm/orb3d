
#pragma once

/////////////////////////////////////////////////////////////////////////////
// CViewTree 窗口

class CViewTree : public CTreeCtrl
{
// 构造
public:
	CViewTree();

	void							UpdateGameObjectTree();
	void							DeleteTree();
	engine::GameObjectPtr			GetGameObject(HTREEITEM hObj);
	void							EraseItem(HTREEITEM hItem);
private:
	void							_update_object_tree(engine::GameObjectPtr pRoot, HTREEITEM hRoot);
	void							_delete_gameobject_tree(HTREEITEM hRoot);
// 重写
protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);

// 实现
public:
	virtual ~CViewTree();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
	afx_msg void OnTvnBeginlabeledit(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnEndlabeledit(NMHDR *pNMHDR, LRESULT *pResult);
//	afx_msg void OnOvRename();
};
