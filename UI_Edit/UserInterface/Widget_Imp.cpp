#include "UserInterface_Imp.h"
#include "Widget_Imp.h"
#include "WidgetEvent.h"

/// @brief Constructs a Widget object
/// @param type The type of widget being constructed
/// @note Tested
Widget::Widget (WidgetType type) : mDraw(0), mHitTest(0), mProcessEvent(0), mType(type)
{
}

/// @brief Destructs a Widget object
/// @note Tested
Widget::~Widget (void)
{
	//////////////////////////////////////
	// If necessary, we untag the widget.
	//////////////////////////////////////
	if (mStatus[eTagged]) UserInterface::Get().mWidgetTags.erase(mTagPos);
}

/// @brief Acquires a Widget object
/// @param name Name used to reference the widget
/// @return Reference to the Widget object
/// @note Tested
Widget & Widget::Get (Uint32 name)
{
	return *UserInterface::Get().mWidgets[name];
}

/// @brief Grabs the widget and issues a widget grab event
/// @param pContext [in-out] User-defined context parameter
/// @note Tested
void Widget::Grab (void * pContext)
{
	///////////////////////////////
	// We flag the widget as held.
	///////////////////////////////
	mStatus[eHeld] = true;

	////////////////////////////////
	// We now issue the grab event.
	////////////////////////////////
	UserInterface::Get().IssueBasicEvent(eWidgetEvent_Grab, pContext);
}

/// @brief Drops the widget and issues a widget drop event
/// @param pContext [in-out] User-defined context parameter
/// @note Tested
void Widget::Drop (void * pContext)
{
	///////////////////////////////////
	// We flag the widget as not held.
	///////////////////////////////////
	mStatus[eHeld] = false;

	////////////////////////////////
	// We now issue the drop event.
	////////////////////////////////
	UserInterface::Get().IssueBasicEvent(eWidgetEvent_Drop, pContext);
}

/// @brief Enters the widget and issues a widget enter event
/// @param pContext [in-out] User-defined context parameter
/// @note Tested
void Widget::Enter (void * pContext)
{
	//////////////////////////////////
	// We flag the widget as entered.
	//////////////////////////////////
	mStatus[eIn] = true;

	/////////////////////////////////
	// We now issue the enter event.
	/////////////////////////////////
	UserInterface::Get().IssueBasicEvent(eWidgetEvent_Enter, pContext);
}

/// @brief Leaves the widget and issues a widget leave event
/// @param pContext [in-out] User-defined context parameter
/// @note Tested
void Widget::Leave (void * pContext)
{
	//////////////////////////////////////
	// We flag the widget as not entered.
	//////////////////////////////////////
	mStatus[eIn] = false;

	/////////////////////////////////
	// We now issue the leave event.
	/////////////////////////////////
	UserInterface::Get().IssueBasicEvent(eWidgetEvent_Leave, pContext);
}

/// @brief Clears all important input state
/// @note Tested
void Widget::Clear (void)
{
	mStatus[eHeld] = false;
	mStatus[eIn] = false;
}

/// @brief Cleans all temporary input state
/// @note Tested
void Widget::CleanTemps (void)
{
	mStatus[eUnder] = false;
}