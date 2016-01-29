/* Released under the BSD-3 license.

Copyright (c) 2016, Navié (Samir Kharchi)
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

* Neither the name of c4d_bitmapbutton nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */

#include "DialogBitmapButton.h"
#include "customgui_bitmapbutton.h"

NAVIE_MAXON::DialogBitmapButton::DialogBitmapButton(const Int32_C4D element_id, const Int32_C4D iconsize_x, const Int32_C4D iconsize_y) 
	: m_id(element_id)
	, m_sx(iconsize_x)
	, m_sy(iconsize_y)
{

}

NAVIE_MAXON::DialogBitmapButton::DialogBitmapButton(const Int32_C4D element_id) : m_id(element_id)
{

}

bool NAVIE_MAXON::DialogBitmapButton::AddToLayout(  GeDialog* dlg, const BBMode button_type, const Int32_C4D default_state_iconid
      , const Int32_C4D pressed_state_iconid /*= NOTOK */, const Int32_C4D bordertype /*= BORDER_THIN_OUT */, const Int32_C4D flags = /*BFH_FIT|BFV_FIT*/, void(*RMBCallback)(void *data) /*= nullptr */, void* callback_data /*= nullptr*/)
{
	m_mode = button_type;

	BaseContainer settings;
	settings.SetLong(BITMAPBUTTON_BORDER, bordertype);
	settings.SetLong(BITMAPBUTTON_ICONID1, default_state_iconid);
	settings.SetBool(BITMAPBUTTON_DRAWPOPUPBUTTON, RMBCallback != nullptr);

	switch(button_type) {
		case BBMode::Image:
		settings.SetBool(BITMAPBUTTON_BUTTON, FALSE);
		settings.SetBool(BITMAPBUTTON_TOGGLE, FALSE);
		break;
		case BBMode::Toggable:
		settings.SetBool(BITMAPBUTTON_BUTTON, FALSE);
		settings.SetBool(BITMAPBUTTON_TOGGLE, TRUE);
		settings.SetLong(BITMAPBUTTON_ICONID2, pressed_state_iconid == NOTOK ? default_state_iconid : pressed_state_iconid);
		break;
		default:
		case BBMode::Clickable:
		settings.SetBool(BITMAPBUTTON_BUTTON, TRUE);
		settings.SetBool(BITMAPBUTTON_TOGGLE, TRUE);
		settings.SetLong(BITMAPBUTTON_ICONID2, pressed_state_iconid == NOTOK ? default_state_iconid : pressed_state_iconid);
		break;
	}

	bbcg = static_cast<BitmapButtonCustomGui*>(dlg->AddCustomGui(m_id, CUSTOMGUI_BITMAPBUTTON, String(), flags, m_sx, m_sy, settings));
	if(bbcg) {
		if(RMBCallback != nullptr) {
			BitmapButtonCallback bbc;
			bbc.ShowPopup = RMBCallback;
			bbc.data = callback_data ? callback_data : &m_id;
			bbcg->SetCallback(bbc);
		}
		bbcg->SetToggleState(false);
	}
	return bbcg != nullptr;
}

bool NAVIE_MAXON::DialogBitmapButton::HandleInitValues()
{
	if(!bbcg) return false;

	bbcg->SetToggleState(false);
	return true;
}

void NAVIE_MAXON::DialogBitmapButton::HandleMessage(const BaseContainer& msg)
{
	if(bbcg && m_mode == BBMode::Clickable) 
	{
		switch(msg.GetId())
		{
			case BFM_INTERACTSTART: t_clickpotential = true; break;
			case BFM_INTERACTEND: t_clickpotential = false;  bbcg->SetToggleState(false); break;
		}
	}
}

void NAVIE_MAXON::DialogBitmapButton::HandleCommand(const Int32_C4D id)
{
	if(bbcg && id == m_id) {
		if(m_mode == BBMode::Clickable && t_clickpotential && !t_state)
			bbcg->SetToggleState(t_state = !t_state);
		else if(m_mode == BBMode::Toggable)
			bbcg->SetToggleState(t_state = !t_state);
	}
}
