/*
This file is part of Xbmc skin editor for notepad++
Copyright (C) 2009 LoonyChewy

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#ifndef XBMC_CONTROL_DIALOG_H
#define XBMC_CONTROL_DIALOG_H


#include "ModelViewController.h"
#include "DockingDlgInterface.h"
#include "SplitterPanel.h"
#include "ToolbarPanel.h"
#include "ToolBar.h"
#include "MultiClipboardListbox.h"
#include "MultiClipboardEditbox.h"
#include "MultiClipOLEDragDrop.h"
#include "ExtractionDialog.h"

// ID for dockable window
#define  MULTICLIPBOARD_DOCKABLE_WINDOW_INDEX 0


class XbmcControllerDialog : public DockingDlgInterface, public IController
{
public:
  XbmcControllerDialog();
  ~XbmcControllerDialog();
  // Not inherited from DockingDlgInterface
  virtual void Init( IModel * pNewModel, MultiClipboardProxy * pClipboardProxy, LoonySettingsManager * pSettings );
  virtual void Shutdown();
  // Inherited from DockingDlgInterface
  virtual void destroy() {}

  void ShowDialog( bool Show = TRUE );

  virtual void OnModelModified();

  void SetCurrentFile(std::wstring file) { m_pCurrentFile = file; }
  void SetHidden() { IsShown = false; }

protected:
  // Overload DockingDlgInterface's dialog procedure
  virtual BOOL CALLBACK run_dlgProc( HWND hWnd, UINT msg, WPARAM wp, LPARAM lp );

  // Initialise dialog here
  void InitialiseDialog();

  // Toolbar commands
  void tb_cmd(UINT message);

  void SetSplitterOrientation();

private:
  tTbData TBData;
  bool IsShown;
  UINT DragListMessage;
  MultiClipOLEDataObject * pDataObject;
  MultiClipOLEDropSource * pDropSource;

  std::wstring m_pCurrentFile;
  std::wstring m_pXbmcIp;
  std::wstring m_pXbmcLogin;
  std::wstring m_pXbmcPassword;
  std::wstring m_pWgetPath;

  CExtractionDialog extractDlg;
  SplitterPanel MultiClipViewerPanel;
  ToolbarPanel ListBoxPanel;
  ToolbarPanel EditBoxPanel;
  ToolBar ListBoxToolBar;
  MultiClipboardListbox MultiClipViewerListbox;
  MultiClipboardEditbox MultiClipViewerEditBox;

  void ShowClipText();
  void OnListSelectionChanged();
  void OnListDoubleClicked();
  void OnEditBoxUpdated();

  void PasteSelectedItem();
  void PasteAllItems();
  void DeleteSelectedItem();
  void DeleteAllItems();
  void CopySelectedItemToClipboard();

  CStdString ShowFolderBrowser();
  CStdString ShowFileBrowser();
  void CreateDirs(CStdString folder);
  virtual void OnObserverAdded( LoonySettingsManager * SettingsManager );
  virtual void OnSettingsChanged( const stringType & GroupName, const stringType & SettingName );
};


#endif