#ifndef C4D_NAVIE_BITMAPBUTTON
#define C4D_NAVIE_BITMAPBUTTON

//C4D
#include "c4d_gui.h"
typedef Int32 Int32_C4D;

class BitmapButtonCustomGui;

namespace NAVIE_MAXON
{
	enum BBMode { Clickable, Toggable, Image };
	
	//Handles addition of a Cinema 4D BitmapButton to a GeDialog
	class DialogBitmapButton
	{
	private:
		Int32_C4D				m_id;
		Int32_C4D				m_sx{}, m_sy{};
		BBMode					m_mode{Clickable};

		BitmapButtonCustomGui*	bbcg {nullptr};
		bool					t_clickpotential {false};
		bool					t_state{ false };

	public:
		DialogBitmapButton(const Int32_C4D element_id);
		DialogBitmapButton(const Int32_C4D element_id, const Int32_C4D iconsize_x, const Int32_C4D iconsize_y);
		
		/********************************************/
		//Call in GeDialog::CreateLayout
		//
		//DLG:					the dialog to add the button to
		//BUTTON_TYPE:			BBMode::x
		//default_state_iconid: The default state image. Must be an icon id registered with RegisterIcon()
		//pressed_state_iconid: The image shown in pressed state. Must be an icon id registered with RegisterIcon(). Unused if button_type==BBMode::Image.
		//bordertype:			BORDER_xxx. Default is BORDER_THIN_OUT
		//RMBCallback:			pass here the callback function that is triggered when user clicks with right-mouse on the bitmap button. optional
		//callback_data:		pass here the custom data that is accessed in the RMB callback as the passed (void* data) variable. Only required if RMBCallback is defined.
		//						Note: if RMBCallback is defined but callback_data is nullptr, the custom_data will automatically be filled with the element_id.
		/********************************************/
		bool AddToLayout ( GeDialog* dlg
						  , const BBMode button_type
						  , const Int32_C4D default_state_iconid
						  , const Int32_C4D pressed_state_iconid = NOTOK
						  , const Int32_C4D bordertype = BORDER_THIN_OUT
						  , void (*RMBCallback)(void *data) = nullptr
						  , void* callback_data = nullptr);

		/***********************************************************************/
		//Call in GeDialog::InitValues. Returns false if sth went wrong
		bool HandleInitValues();
		
		/***********************************************************************/
		//Call in GeDialog::Message
		void HandleMessage(const BaseContainer& msg);
		
		/***********************************************************************/
		//Call in GeDialog::Command
		void HandleCommand(const Int32_C4D id);
		
		//The original c4d data ptr (though you shouldn't mess with this pointer from the outside)
		BitmapButtonCustomGui* get_ptr() { return bbcg; }
	};

	/***********************************************************************/
	//Example callback function defined like this:
	//
	//This method is called when the user clicks with the right-mouse-button
	//void YourBitmapButtonCallbackFunction(void *data)
	//{
	//  Int32 element_id = *static_cast<Int32*>(data);
	//	GePrint("User clicked on Bitmap Button with id: " + String::IntToString(element_id));
	//}
	/***********************************************************************/
}

#endif // !C4D_DIALOG_HELPERS
