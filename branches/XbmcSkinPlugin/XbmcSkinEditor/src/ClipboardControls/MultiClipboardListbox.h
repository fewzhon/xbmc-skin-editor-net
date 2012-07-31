/*
This file is part of MultiClipboard Plugin for Notepad++
Copyright (C) 2009 LoonyChewy

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either
version 2 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#ifndef MULTI_CLIPBOARD_LIST_BOX_H
#define MULTI_CLIPBOARD_LIST_BOX_H


#ifndef UNITY_BUILD_SINGLE_INCLUDE
#include "Window.h"
#include <string>
#include <vector>
#endif


// Notification to parent that delete key is pressed
#define LBN_DELETEITEM LB_MSGMAX+0x100


class MultiClipboardListbox : public Window
{
public:
	virtual void init(HINSTANCE hInst, HWND parent);
	virtual void destroy();

	virtual void AddItem( std::wstring item );
	virtual void ClearAll();
	virtual INT GetItemCount();

  virtual std::wstring GetCurrentSelectionText();

	virtual INT GetCurrentSelectionIndex();
	// Selects the specified list box item.
	// If index out of bounds, and bStrictSelect is TRUE, nothing is selected
	// else the last item in the list, if available, is selected
	virtual void SetCurrentSelectedItem( INT NewSelectionIndex, BOOL bStrictSelect=TRUE );

private:
  std::vector<std::wstring> lstText;
	HFONT hNewFont;

	WNDPROC oldWndProc;
	// Subclass the list box's wnd proc for customised behavior
	static LRESULT CALLBACK StaticListboxProc( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam )
	{
		return ((MultiClipboardListbox *)(::GetWindowLongPtr(hwnd, GWL_USERDATA)))->runProc( hwnd, message, wParam, lParam );
	};
	LRESULT runProc( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam );
};


#endif