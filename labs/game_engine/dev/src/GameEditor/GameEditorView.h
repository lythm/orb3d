
// GameEditorView.h : CGameEditorView 类的接口
//

#pragma once

class GridMesh;

class CGameEditorView : public CView
{
protected: // 仅从序列化创建
	CGameEditorView();
	DECLARE_DYNCREATE(CGameEditorView)

// 特性
public:
	CGameEditorDoc* GetDocument() const;

// 操作
public:

// 重写
public:

	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

	
// 实现
public:
	virtual ~CGameEditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	
private:
	
	
private:
	
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
	afx_msg void OnDestroy();
	afx_msg void OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

};

#ifndef _DEBUG  // GameEditorView.cpp 中的调试版本
inline CGameEditorDoc* CGameEditorView::GetDocument() const
   { return reinterpret_cast<CGameEditorDoc*>(m_pDocument); }
#endif

