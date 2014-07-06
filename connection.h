#if !defined(AFX_CONNECTION_H__E463C6A1_1A65_47E1_B9A8_80AAFCC94FB4__INCLUDED_)
#define AFX_CONNECTION_H__E463C6A1_1A65_47E1_B9A8_80AAFCC94FB4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// connection.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// Cconnection command target

class Cconnection : public CAsyncSocket
{
// Attributes
public:

// Operations
public:
	Cconnection();
	virtual ~Cconnection();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Cconnection)
	public:
	virtual void OnAccept(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(Cconnection)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONNECTION_H__E463C6A1_1A65_47E1_B9A8_80AAFCC94FB4__INCLUDED_)
