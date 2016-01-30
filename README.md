# c4d_bitmapbutton
This is an example of adding a bitmap button to a GeDialog in Cinema 4D R13+

This small helper I came up with when I tried to add a BitmapButtonCustomGui to a GeDialog.
It was quite a pain to find a way of having it as a clickable button but eventually I found a way.
As others struggled before with this I thought sharing this might save some others from the trouble.

It's quite useful as it can be used for buttons, checkboxes (toggable) or for splash screens
and generally image display in a dialog.

The code is released under the BSD-3 license.

Requirements
------------
- Cinema 4D R13 (or higher) SDK.
- C++03/C++11 compliant compiler

By default it compiles for R15 SDK and a C++11 compiler (VS2013+/XCode 5+)
To support previous versions/compilers outcomment the preprocessor directives in DialogBitmapButton.h.

How to use
----------
Simply include the files in your project.

There is only one class: **DialogBitmapButton**

Basically all you need to do is construct it with an element ID and call the 4 public functions:
* DialogBitmapButton::AddToLayout
* DialogBitmapButton::HandleInitValues
* DialogBitmapButton::HandleMessage
* DialogBitmapButton::HandleCommand

Furthermore AddToLayout also allows to pass a popup callback. An example of how such a callback function might look like
can be found in the DialogBitmapButton header file (at the very bottom).

Example
--------
```
const int bitmapbutton_id = 2000; //Element ID of the bitmap button

class TestDialog : public GeDialog
{
 private:
    NAVIE_MAXON::DialogBitmapButton m_bmpbutton;
    [...]
 public:
    TestDialog() : m_bmpbutton(bitmapbutton_id) {}
}

Bool TestDialog::CreateLayout(void)
{
	[...]
	//Adds a clickable button (switches from sphere to cube icon). 
	m_bmpbutton.AddToLayout(this,NAVIE_MAXON::BBMode::Clickable, Osphere, Ocube, true, BORDER_OUT, BFH_CENTER|BFH_CENTER, "Tooltip Info");
	[...]
}

Bool TestDialog::InitValues(void)
{
	if (!Base::InitValues()) return false;
	m_bmpbutton.HandleInitValues();
	return true;
}

Bool TestDialog::Command(Int32 id, const BaseContainer& msg)
{	
	m_bmpbutton.HandleCommand(id);
}

Int32_C4D TestDialog::Message(const BaseContainer &msg, BaseContainer &result)
{
	m_bmpbutton.HandleMessage(msg);
	return Base::Message(msg,result);
}
```
