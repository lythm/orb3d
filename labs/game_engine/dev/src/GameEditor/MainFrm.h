
// MainFrm.h : CMainFrame 类的接口
//

#pragma once
#include "FileView.h"
#include "ObjectView.h"
#include "OutputWnd.h"
#include "PropertiesWnd.h"
#include "TemplateView.h"
#include "InspectorView.h"

class CMainFrame : public CFrameWndEx
{
	
protected: // 仅从序列化创建
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// 特性
public:

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

	CObjectView*			GetObjectView();
	COutputWnd*				GetOutput();
	CPropertiesWnd*			GetPropGrid();

	void					SetFPS(float fps);

	bool					UpdateComClassMap();
	bool					UpdateTemplateMap();

	void					UpdateObjectView(ld3d::GameObjectPtr pRoot);
	void					UpdatePropGrid(ld3d::GameObjectPtr pObj);
	void					OutputInfo(const CString& info);
	void					outputBuild(const CString& build);
	void					UpdateAssetsView();
private:
	bool					UpdateComponentMenu(CMFCPopupMenu* pMenu);
	ld3d::ExtPackage::ComponentClass* FindClassByMenuID(UINT uID);

	bool					UpdateTemplateMenu(CMFCPopupMenu* pMenu);
	ld3d::GameObjectTemplate* FindTemplateByMenuID(UINT uID);
// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CMFCMenuBar       m_wndMenuBar;
	CMFCToolBar       m_wndToolBar;
	CMFCStatusBar     m_wndStatusBar;
	CMFCToolBarImages m_UserImages;
	CFileView         m_wndFileView;
	CObjectView        m_wndObjectView;
	COutputWnd        m_wndOutput;
	CPropertiesWnd    m_wndProperties;
	CMFCCaptionBar    m_wndCaptionBar;
	CTemplateView	  m_wndTplView;
	CInspectorView		m_wndInspectorView;
	boost::unordered_map<std::wstring, std::vector<ld3d::ExtPackage::ComponentClass*> >	m_ComClassMap;
	boost::unordered_map<std::wstring, std::vector<ld3d::GameObjectTemplate*> >			m_templateMap;
// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	afx_msg void OnViewCaptionBar();
	afx_msg void OnUpdateViewCaptionBar(CCmdUI* pCmdUI);
	afx_msg void OnOptions();
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	DECLARE_MESSAGE_MAP()

	BOOL CreateDockingWindows();
	void SetDockingWindowIcons(BOOL bHiColorIcons);
	BOOL CreateCaptionBar();
public:
	afx_msg void OnClose();
	afx_msg void OnGameobjectCreateempty();
	afx_msg void OnComponentMenu(UINT nID);
	afx_msg void OnCreateFromTemplateMenu(UINT nID);
	afx_msg void OnUpdateComponentMenuUI(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCreateFromTemplateMenuUI(CCmdUI* pCmdUI);
	
	afx_msg void OnViewShowgrid();
	afx_msg void OnUpdateViewShowgrid(CCmdUI *pCmdUI);
	afx_msg void OnEditAppsettings();
	afx_msg void OnImportImportmaxmesh();
	virtual BOOL OnShowPopupMenu(CMFCPopupMenu* pMenuPopup);
	virtual void OnUpdateFrameMenu(HMENU hMenuAlt);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	afx_msg void OnRenderingSetting();
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	afx_msg void OnBuildPreview();
	afx_msg void OnFileNew();
	afx_msg void OnFileOpen();
	afx_msg void OnFileSave();
	afx_msg void OnFileSaveAs();
	afx_msg void OnFileSaveScene();
	afx_msg void OnFileOpenScene();
	afx_msg void OnFileSaveSceneAs();
	afx_msg void OnFileNewScene();
	afx_msg void OnFileNewProject();
	afx_msg void OnFileOpenProject();
	afx_msg void OnFileSaveProject();
};


