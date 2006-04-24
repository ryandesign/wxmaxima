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

#include "Plot2dWiz.h"

#include <wx/artprov.h>

enum {
  parametric,
  combobox,
  file_browse_2d
};

enum {
  cartesian,
  polar
};

Plot2DWiz::Plot2DWiz(wxWindow* parent, int id, const wxString& title,
                     const wxPoint& pos, const wxSize& size, long style):
    wxDialog(parent, id, title, pos, size, wxDEFAULT_DIALOG_STYLE)
{
  label_1 = new wxStaticText(this, -1, _("Plot 2D"));
  label_2 = new wxStaticText(this, -1, _("Expression(s):"));
  text_ctrl_1 = new BTextCtrl(this, -1, wxEmptyString, wxDefaultPosition,
                              wxSize(250, -1));
  button_3 = new wxButton(this, parametric, _("Parametric"));
  label_3 = new wxStaticText(this, -1, _("Variable:"));
  text_ctrl_2 = new BTextCtrl(this, -1, wxT("x"), wxDefaultPosition,
                              wxSize(40, -1));
  label_4 = new wxStaticText(this, -1, _("from:"));
  text_ctrl_3 = new BTextCtrl(this, -1, wxT("-5"), wxDefaultPosition,
                              wxSize(70, -1));
  label_5 = new wxStaticText(this, -1, _("to:"));
  text_ctrl_4 = new BTextCtrl(this, -1, wxT("5"), wxDefaultPosition,
                              wxSize(70, -1));
  label_6 = new wxStaticText(this, -1, _("Variable:"));
  text_ctrl_5 = new BTextCtrl(this, -1, wxT("y"), wxDefaultPosition,
                              wxSize(40, -1), wxTE_READONLY);
  label_7 = new wxStaticText(this, -1, _("from:"));
  text_ctrl_6 = new BTextCtrl(this, -1, wxT("-5"), wxDefaultPosition,
                              wxSize(70, -1));
  label_8 = new wxStaticText(this, -1, _("to:"));
  text_ctrl_7 = new BTextCtrl(this, -1, wxT("5"), wxDefaultPosition,
                              wxSize(70, -1));
  checkbox_1 = new wxCheckBox(this, -1, _("Send ranges to gnuplot"));
  label_9 = new wxStaticText(this, -1, _("Ticks:"));
  text_ctrl_8 = new wxSpinCtrl(this, -1, wxEmptyString, wxDefaultPosition,
                               wxDefaultSize, wxSP_ARROW_KEYS, 0, 1000);
  label_10 = new wxStaticText(this, -1, _("Format:"));
  const wxString combo_box_1_choices[] =
    {
      _("default"),
      wxT("gnuplot"),
      wxT("openmath")
    };
  combo_box_1 = new wxComboBox(this, -1, wxEmptyString, wxDefaultPosition,
                               wxSize(150, -1), 3,
                               combo_box_1_choices, wxCB_DROPDOWN);
  label_11 = new wxStaticText(this, -1, _("Options:"));
  const wxString combo_box_2_choices[] =
    {
      wxT("set zeroaxis;"),
      wxT("set size ratio 1; set zeroaxis;"),
      wxT("set grid;"),
      wxT("set polar; set zeroaxis;"),
      wxT("set logscale y; set grid;"),
      wxT("set logscale x; set grid;")
    };
  combo_box_2 = new wxComboBox(this, combobox, wxEmptyString, wxDefaultPosition,
                               wxSize(280, -1), 6,
                               combo_box_2_choices, wxCB_DROPDOWN);
  label_12 = new wxStaticText(this, -1, _("Plot to file:"));
  text_ctrl_9 = new BTextCtrl(this, -1, wxEmptyString, wxDefaultPosition,
                              wxSize(280, -1));
  button_4 = new wxBitmapButton(this, file_browse_2d,
                                wxArtProvider::GetBitmap(wxART_FILE_OPEN,
                                                         wxART_HELP_BROWSER));
  static_line_1 = new wxStaticLine(this, -1);
#if defined __WXMSW__
  button_1 = new wxButton(this, wxID_OK, _("OK"));
  button_2 = new wxButton(this, wxID_CANCEL, _("Cancel"));
#else
  button_1 = new wxButton(this, wxID_CANCEL, _("Cancel"));
  button_2 = new wxButton(this, wxID_OK, _("OK"));
#endif

  type = cartesian;

  set_properties();
  do_layout();
}


void Plot2DWiz::set_properties()
{
  SetTitle(_("Plot 2D"));
  label_1->SetFont(wxFont(20, wxROMAN, wxITALIC, wxNORMAL, 0, wxEmptyString));
  text_ctrl_3->SetValue(wxT("-5"));
  text_ctrl_4->SetValue(wxT("5"));
  text_ctrl_6->SetValue(wxT("0"));
  text_ctrl_7->SetValue(wxT("0"));
  text_ctrl_8->SetValue(wxT("10"));

  button_4->SetToolTip(_("Browse"));
#if defined __WXMSW__
  button_1->SetDefault();
#else
  button_2->SetDefault();
#endif

  combo_box_1->SetSelection(0);
}


void Plot2DWiz::do_layout()
{
  wxFlexGridSizer* grid_sizer_1 = new wxFlexGridSizer(4, 1, 3, 3);
  wxBoxSizer* sizer_1 = new wxBoxSizer(wxHORIZONTAL);
  wxFlexGridSizer* grid_sizer_2 = new wxFlexGridSizer(7, 2, 3, 3);
  wxBoxSizer* sizer_2 = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer* sizer_3 = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer* sizer_4 = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer* sizer_5 = new wxBoxSizer(wxHORIZONTAL);
  grid_sizer_1->Add(label_1, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 2);
  grid_sizer_2->Add(label_2, 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL | wxALL, 2);
  sizer_2->Add(text_ctrl_1, 0, wxALL | wxALIGN_CENTER_VERTICAL, 2);
  sizer_2->Add(button_3, 0, wxALL, 2);
  grid_sizer_2->Add(sizer_2, 1, wxEXPAND, 0);
  grid_sizer_2->Add(label_3, 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL | wxALL, 2);
  sizer_3->Add(text_ctrl_2, 0, wxALL | wxALIGN_CENTER_VERTICAL, 2);
  sizer_3->Add(label_4, 0, wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, 2);
  sizer_3->Add(text_ctrl_3, 0, wxALL | wxALIGN_CENTER_VERTICAL, 2);
  sizer_3->Add(label_5, 0, wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, 2);
  sizer_3->Add(text_ctrl_4, 0, wxALL | wxALIGN_CENTER_VERTICAL, 2);
  grid_sizer_2->Add(sizer_3, 1, 0, 0);
  grid_sizer_2->Add(label_6, 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL | wxALL, 2);
  sizer_4->Add(text_ctrl_5, 0, wxALL, 2);
  sizer_4->Add(label_7, 0, wxALL | wxALIGN_CENTER_VERTICAL | wxALL, 2);
  sizer_4->Add(text_ctrl_6, 0, wxALL, 2);
  sizer_4->Add(label_8, 0, wxALL | wxALIGN_CENTER_VERTICAL | wxALL, 2);
  sizer_4->Add(text_ctrl_7, 0, wxALL, 2);
  grid_sizer_2->Add(sizer_4, 1, wxEXPAND, 0);
  grid_sizer_2->Add(10, 10);
  grid_sizer_2->Add(checkbox_1, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxALL, 2);
  grid_sizer_2->Add(label_9, 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL | wxALL, 2);
  grid_sizer_2->Add(text_ctrl_8, 0, wxALL, 2);
  grid_sizer_2->Add(label_10, 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL | wxALL, 2);
  grid_sizer_2->Add(combo_box_1, 0, wxALL, 2);
  grid_sizer_2->Add(label_11, 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL | wxALL, 2);
  grid_sizer_2->Add(combo_box_2, 0, wxALL, 2);
  sizer_5->Add(text_ctrl_9, 0, wxALL | wxALIGN_CENTER_VERTICAL, 2);
  sizer_5->Add(button_4, 0, wxALL, 2);
  grid_sizer_2->Add(label_12, 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL | wxALL, 2);
  grid_sizer_2->Add(sizer_5, 1, wxEXPAND, 0);
  grid_sizer_1->Add(grid_sizer_2, 1, wxEXPAND, 0);
  grid_sizer_1->Add(static_line_1, 0, wxEXPAND | wxLEFT | wxRIGHT, 2);
  sizer_1->Add(button_1, 0, wxLEFT | wxRIGHT, 5);
  sizer_1->Add(button_2, 0, wxLEFT | wxRIGHT, 5);
  grid_sizer_1->Add(sizer_1, 1, wxALIGN_RIGHT | wxTOP | wxBOTTOM, 3);
  SetAutoLayout(true);
  SetSizer(grid_sizer_1);
  grid_sizer_1->Fit(this);
  grid_sizer_1->SetSizeHints(this);
  Layout();
}

void Plot2DWiz::SetValue(wxString s)
{
  if (s.StartsWith(wxT("plot2d")))
    Parse(s);
  else
    text_ctrl_1->SetValue(s);
}

void Plot2DWiz::Parse(wxString s)
{
  int depth = 0;
  unsigned int i = 0;
  wxString curr;
  s = s.SubString(7, s.Length());
  // Function to plot
  do
  {
    if (s.GetChar(i) == '[')
    {
      depth++;
      if (depth > 1)
        curr += s.GetChar(i);
    }
    else if (s.GetChar(i) == ']')
    {
      depth--;
      if (depth > 0)
        curr += s.GetChar(i);
    }
    else
      curr += s.GetChar(i);
    i++;
  }
  while (depth > 0);
  text_ctrl_1->SetValue(curr);
  // Independent variable
  while (i < s.Length() && s.GetChar(i) != '[')
    i++;
  i++;
  curr = wxEmptyString;
  while (i < s.Length() && s.GetChar(i) != ',')
  {
    curr += s.GetChar(i);
    i++;
  }
  text_ctrl_2->SetValue(curr);
  i++;
  curr = wxEmptyString;
  while (i < s.Length() && s.GetChar(i) != ',')
  {
    curr += s.GetChar(i);
    i++;
  }
  text_ctrl_3->SetValue(curr);
  i++;
  curr = wxEmptyString;
  while (i < s.Length() && s.GetChar(i) != ']')
  {
    curr += s.GetChar(i);
    i++;
  }
  text_ctrl_4->SetValue(curr);
  i++;
  // Optional parameters
  while (i < s.Length())
  {
    if (s.GetChar(i) == '[')
    {
      i++;
      curr = wxEmptyString;
      while (i < s.Length() && s.GetChar(i) != ',')
      {
        curr += s.GetChar(i);
        i++;
      }
      curr.Trim();
      curr.Trim(false);
      if (curr == wxT("y"))
      {
        curr = wxEmptyString;
        i++;
        while (i < s.Length() && s.GetChar(i) != ',')
        {
          curr += s.GetChar(i);
          i++;
        }
        text_ctrl_6->SetValue(curr);
        i++;
        curr = wxEmptyString;
        while (i < s.Length() && s.GetChar(i) != ']')
        {
          curr += s.GetChar(i);
          i++;
        }
        text_ctrl_7->SetValue(curr);
        i++;
      }
      else if (curr == wxT("gnuplot_preamble"))
      {
        while (i < s.Length() && s.GetChar(i) != '"')
          i++;
        i++;
        curr = wxEmptyString;
        while (i < s.Length() && s.GetChar(i) != '"')
        {
          curr += s.GetChar(i);
          i++;
        }
        combo_box_2->SetValue(curr);
      }
      else if (curr == wxT("gnuplot_out_file"))
      {
        while (i < s.Length() && s.GetChar(i) != '"')
          i++;
        i++;
        curr = wxEmptyString;
        while (i < s.Length() && s.GetChar(i) != '"')
        {
          curr += s.GetChar(i);
          i++;
        }
        text_ctrl_9->SetValue(curr);
      }
      else if (curr == wxT("nticks"))
      {
        curr = wxEmptyString;
        while (i < s.Length() && s.GetChar(i) != ',')
          i++;
        i++;
        while (i < s.Length() && s.GetChar(i) != ']')
        {
          curr += s.GetChar(i);
          i++;
        }
        text_ctrl_8->SetValue(curr);
      }
    }
    i++;
  }
}

wxString Plot2DWiz::GetValue()
{
  wxString f = combo_box_1->GetValue();     // function
  wxString p = combo_box_2->GetValue();     // preamble
  wxString s = wxT("plot2d([");             // result
  wxString x1 = text_ctrl_3->GetValue();
  wxString x2 = text_ctrl_4->GetValue();
  wxString y1 = text_ctrl_6->GetValue();
  wxString y2 = text_ctrl_7->GetValue();
  int t = text_ctrl_8->GetValue();          // Number of ticks
  wxString file = text_ctrl_9->GetValue();  // plot to file
  wxString r;                               // range
  if (checkbox_1->IsChecked())
  {
    r = wxT("set xrange [") + x1 + wxT(":") + x2 + wxT("];");
    if (y1 != wxT("0") || y2 != wxT("0"))
      r += wxT(" set yrange [") + y1 + wxT(":") + y2 + wxT("];");
    if (p.Length())
      p = r + wxT(" ") + p;
    else
      p = r;
  }

  s += text_ctrl_1->GetValue();
  s += wxT("], [");
  s += text_ctrl_2->GetValue();
  s += wxT(",");
  if (x1 != wxT("0") || x2 != wxT("0"))
    s += x1 + wxT(",") + x2;
  else if (type == polar)
    s += wxT("0,2*%pi");
  else
    s += wxT("-5,5");
  s += wxT("]");
  if (y1 != wxT("0") || y2 != wxT("0"))
  {
    s += wxT(", [");
    s += text_ctrl_5->GetValue();
    s += wxT(",") + y1 + wxT(",") + y2 + wxT("]");
  }
  if (f != _("default"))
    s += wxT(", [plot_format, ") + f + wxT("]");
  if (p.Length() > 0)
    s += wxT(", [gnuplot_preamble, \"") + p + wxT("\"]");
  if (t != 10)
  {
    s += wxT(", [nticks,");
    s += wxString::Format(wxT("%d"), t);
    s += wxT("]");
  }
  if (file.Length())
  {
    s += wxT(", [gnuplot_term, ps]");
#if defined (__WXMSW__)
    file.Replace(wxT("\\"), wxT("/"));
#endif

    if (file.Right(4) != wxT(".eps") && file.Right(3) != wxT(".ps"))
      file = file + wxT(".eps");
    s += wxT(", [gnuplot_out_file, \"") + file + wxT("\"]");
  }
  s += wxT(")$");

  return s;
}

void Plot2DWiz::OnButton(wxCommandEvent& event)
{
  Plot2dPar *wiz = new Plot2dPar(this, -1, _("Plot 2D"));
  wiz->Centre(wxBOTH);
  if (wiz->ShowModal() == wxID_OK)
  {
    if (text_ctrl_1->GetValue() == wxT("%"))
      text_ctrl_1->SetValue(wxEmptyString);
    if (((text_ctrl_1->GetValue()).Strip()).Length())
      text_ctrl_1->AppendText(wxT(", "));
    text_ctrl_1->AppendText(wiz->GetValue());
    if (text_ctrl_8->GetValue() == 10)
      text_ctrl_8->SetValue(300);
  }
}

void Plot2DWiz::OnCombobox(wxCommandEvent &event)
{
  wxString selection = combo_box_2->GetStringSelection();
  if (selection.StartsWith(wxT("set polar")))
  {
    text_ctrl_2->SetValue(wxT("ph"));
    text_ctrl_3->SetValue(wxT("0"));
    text_ctrl_4->SetValue(wxT("2*%pi"));
    type = polar;
  }
  else
    type = cartesian;

  if (selection.StartsWith(wxT("set logscale x")))
  {
    text_ctrl_3->SetValue(wxT("0"));
    text_ctrl_4->SetValue(wxT("100"));
  }
}

void Plot2DWiz::OnFileBrowse(wxCommandEvent& event)
{
  wxString file = wxFileSelector(_("Save plot to file"), wxEmptyString,
                                 wxT("plot2d.eps"), wxT("eps"),
                                 _("Postscript file (*.eps)|*.eps|All|*"),
                                 wxSAVE | wxOVERWRITE_PROMPT);
  if (file.Length() > 0)
    text_ctrl_9->SetValue(file);
}

BEGIN_EVENT_TABLE(Plot2DWiz, wxDialog)
  EVT_COMBOBOX(combobox, Plot2DWiz::OnCombobox)
  EVT_BUTTON(parametric, Plot2DWiz::OnButton)
  EVT_BUTTON(file_browse_2d, Plot2DWiz::OnFileBrowse)
END_EVENT_TABLE()

///////////////////////
//
// Plot2dPar
//
///////////////////////

Plot2dPar::Plot2dPar(wxWindow* parent, int id, const wxString& title,
                     const wxPoint& pos, const wxSize& size, long style):
    wxDialog(parent, id, title, pos, size, wxDEFAULT_DIALOG_STYLE)
{
  label_1 = new wxStaticText(this, -1, _("Parametric plot"));
  label_2 = new wxStaticText(this, -1, wxT("x = "));
  text_ctrl_1 = new BTextCtrl(this, -1, wxEmptyString, wxDefaultPosition,
                              wxSize(230, -1));
  label_3 = new wxStaticText(this, -1, wxT("y = "));
  text_ctrl_2 = new BTextCtrl(this, -1, wxEmptyString, wxDefaultPosition,
                              wxSize(230, -1));
  label_4 = new wxStaticText(this, -1, _("Variable:"));
  text_ctrl_3 = new BTextCtrl(this, -1, wxT("t"), wxDefaultPosition,
                              wxSize(40, -1));
  label_5 = new wxStaticText(this, -1, _("from:"));
  text_ctrl_4 = new BTextCtrl(this, -1, wxEmptyString, wxDefaultPosition,
                              wxSize(70, -1));
  label_6 = new wxStaticText(this, -1, _("to:"));
  text_ctrl_5 = new BTextCtrl(this, -1, wxEmptyString, wxDefaultPosition,
                              wxSize(70, -1));
  static_line_1 = new wxStaticLine(this, -1);
#if defined __WXMSW__
  button_1 = new wxButton(this, wxID_OK, _("OK"));
  button_2 = new wxButton(this, wxID_CANCEL, _("Cancel"));
#else
  button_1 = new wxButton(this, wxID_CANCEL, _("Cancel"));
  button_2 = new wxButton(this, wxID_OK, _("OK"));
#endif

  set_properties();
  do_layout();
}

void Plot2dPar::set_properties()
{
  SetTitle(_("Parametric plot"));
  label_1->SetFont(wxFont(20, wxROMAN, wxITALIC, wxNORMAL, 0, wxEmptyString));
  text_ctrl_4->SetValue(wxT("-6"));
  text_ctrl_5->SetValue(wxT("6"));
#if defined __WXMSW__
  button_1->SetDefault();
#else
  button_2->SetDefault();
#endif
}

void Plot2dPar::do_layout()
{
  wxFlexGridSizer* grid_sizer_1 = new wxFlexGridSizer(4, 1, 3, 3);
  wxBoxSizer* sizer_1 = new wxBoxSizer(wxHORIZONTAL);
  wxFlexGridSizer* grid_sizer_2 = new wxFlexGridSizer(3, 2, 3, 3);
  wxBoxSizer* sizer_2 = new wxBoxSizer(wxHORIZONTAL);
  grid_sizer_1->Add(label_1, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 2);
  grid_sizer_2->Add(label_2, 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL | wxALL, 2);
  grid_sizer_2->Add(text_ctrl_1, 0, wxALL | wxEXPAND, 2);
  grid_sizer_2->Add(label_3, 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL | wxALL, 2);
  grid_sizer_2->Add(text_ctrl_2, 0, wxALL | wxEXPAND, 2);
  grid_sizer_2->Add(label_4, 0, wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, 2);
  sizer_1->Add(text_ctrl_3, 0, wxALL, 2);
  sizer_1->Add(label_5, 0, wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, 2);
  sizer_1->Add(text_ctrl_4, 0, wxALL, 2);
  sizer_1->Add(label_6, 0, wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, 2);
  sizer_1->Add(text_ctrl_5, 0, wxALL, 2);
  grid_sizer_2->Add(sizer_1, 1, 0, 0);
  grid_sizer_2->AddGrowableCol(1);
  grid_sizer_1->Add(grid_sizer_2, 1, wxEXPAND, 0);
  grid_sizer_1->Add(static_line_1, 0, wxEXPAND | wxLEFT | wxRIGHT, 2);
  sizer_2->Add(button_1, 0, wxLEFT | wxRIGHT, 5);
  sizer_2->Add(button_2, 0, wxLEFT | wxRIGHT, 5);
  grid_sizer_1->Add(sizer_2, 1, wxALIGN_RIGHT | wxTOP | wxBOTTOM, 3);
  SetAutoLayout(true);
  SetSizer(grid_sizer_1);
  grid_sizer_1->Fit(this);
  grid_sizer_1->SetSizeHints(this);
  Layout();
}

wxString Plot2dPar::GetValue()
{
  wxString s;
  s = wxT("[parametric, ");
  s += text_ctrl_1->GetValue();
  s += wxT(", ");
  s += text_ctrl_2->GetValue();
  s += wxT(", [");
  s += text_ctrl_3->GetValue();
  s += wxT(", ");
  s += text_ctrl_4->GetValue();
  s += wxT(", ");
  s += text_ctrl_5->GetValue();
  s += wxT("]]");

  return s;
}
