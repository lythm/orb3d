
// GameEditorDoc.cpp : CGameEditorDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "GameEditor.h"
#endif

#include "GameEditorDoc.h"

#include <propkey.h>
#include "StartDialog.h"
#include "ProgressDlg.h"
#include "ProjectWizard.h"
#include "editor_utils.h"
#include "MainFrm.h"
#include "Project.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CGameEditorDoc

IMPLEMENT_DYNCREATE(CGameEditorDoc, CDocument)

BEGIN_MESSAGE_MAP(CGameEditorDoc, CDocument)
END_MESSAGE_MAP()


// CGameEditorDoc 构造/析构

CGameEditorDoc::CGameEditorDoc()
{
	// TODO: 在此添加一次性构造代码

}

CGameEditorDoc::~CGameEditorDoc()
{
}

BOOL CGameEditorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;


	CProjectWizard pw(util_get_main_frame());
	if(IDOK != pw.DoModal())
	{
		return FALSE;
	}

	util_update_object_view(Project::Instance()->Root());
	util_update_assets_view();

	SetTitle(Project::Instance()->GetGameSceneFile().c_str());

	return CDocument::OnNewDocument();
}


// CGameEditorDoc 序列化

void CGameEditorDoc::Serialize(CArchive& ar)
{
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CGameEditorDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CGameEditorDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:  strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CGameEditorDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CGameEditorDoc 诊断

#ifdef _DEBUG
void CGameEditorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGameEditorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CGameEditorDoc 命令


BOOL CGameEditorDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	using namespace ld3d;

	util_update_obj_property_grid(GameObjectPtr());
	util_update_object_view(GameObjectPtr());

	ProjectPtr pProject = Project::Instance();

	pProject->Close();
	
	if(pProject->Load(lpszPathName) == false)
	{
		util_log_info(L"Failed to open project.");
		return FALSE;
	}

	util_log_info(L"Project openned.");
	util_update_object_view(Project::Instance()->Root());
	return CDocument::OnOpenDocument(lpszPathName);
}



BOOL CGameEditorDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: 在此添加专用代码和/或调用基类


	ProjectPtr pProject =Project::Instance();

		
	if(pProject->Save(lpszPathName) == false)
	{
		util_log_info(L"Failed to save project.");
		return FALSE;
	}
	util_log_info(L"Project saved.");
	

	return CDocument::OnSaveDocument(lpszPathName);
}
