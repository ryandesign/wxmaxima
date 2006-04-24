///
///  Copyright (C) 2004-2006 Andrej Vodopivec <andrejv@users.sourceforge.net>
///
///  This program is free software; you can redistribute it and/or modify
///  it under the terms of the GNU General Public License as published by
///  the Free Software Foundation; either version 2 of the License, or
///  (at your option) any later version.
///
///  This program is distributed in the hope that it will be useful,
///  but WITHOUT ANY WARRANTY; without even the implied warranty of
///  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
///  GNU General Public License for more details.
///
///
///  You should have received a copy of the GNU General Public License
///  along with this program; if not, write to the Free Software
///  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
///

#ifndef INTEGRATEWIZ_H
#define INTEGRATEWIZ_H

#include <wx/wx.h>
#include <wx/statline.h>

#include "BTextCtrl.h"

enum {
  special_from,
  special_to
};

class IntegrateWiz: public wxDialog
{
public:
  IntegrateWiz(wxWindow* parent, int id, const wxString& title,
               const wxPoint& pos = wxDefaultPosition,
               const wxSize& size = wxDefaultSize,
               long style = wxDEFAULT_DIALOG_STYLE);
  void SetValue(wxString s)
  {
    text_ctrl_1->SetValue(s);
  }
  wxString GetValue();
private:
  void set_properties();
  void do_layout();
  void OnButton(wxCommandEvent& event);
  void OnCheckbox(wxCommandEvent& event);
protected:
  wxStaticText* label_1;
  wxStaticText* label_2;
  BTextCtrl* text_ctrl_1;
  wxStaticText* label_3;
  BTextCtrl* text_ctrl_2;
  wxCheckBox* checkbox_1;
  wxStaticText* label_4;
  BTextCtrl* text_ctrl_3;
  wxButton* button_3;
  wxStaticText* label_5;
  BTextCtrl* text_ctrl_4;
  wxButton* button_4;
  wxStaticLine* static_line_1;
  wxButton* button_1;
  wxButton* button_2;
  wxCheckBox* checkbox_2;
  DECLARE_EVENT_TABLE()
};

#endif // INTEGRATEWIZ_H
