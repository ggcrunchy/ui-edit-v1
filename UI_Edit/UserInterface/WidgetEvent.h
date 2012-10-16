/// @file
/// Widget event information

#ifndef USER_INTERFACE_EVENT_H
#define USER_INTERFACE_EVENT_H

#include <SDL/SDL_types.h>

#ifdef __cplusplus
extern "C" {
#endif	// __cplusplus

/// @brief Descriptors for the events associated with widgets
typedef enum _WidgetEventType {
/* General */
	eWidgetEvent_Grab,	///< Basic: The cursor was over the widget during a press
	eWidgetEvent_Drop,	///< Basic: A release following a widget grab
	eWidgetEvent_Enter,	///< Basic: The cursor entered the widget region
	eWidgetEvent_Leave,	///< Basic: The cursor left the widget region
/* Pane */
	ePaneEvent_Catch,///< Point: The cursor was over the pane during a press
	ePaneEvent_Release,	///< Basic: A release following a pane catch
	ePaneEvent_Drag,	///< Basic: The cursor was moved following a pane catch, before a pane release
/* Button */
	eButtonEvent_Push,	///< Point: The cursor was over the button during a press
	eButtonEvent_Release,///< Basic: A release following a button push
/* Checkbox */
	eCheckboxEvent_Check,///< Basic: A release following a grab, while unchecked
	eCheckboxEvent_Uncheck,	///< Basic: A release following a grab, while checked
/* Listbox */
	eListboxEvent_GrabItem,	///< Index: The cursor was over an item during a press
	eListboxEvent_DropItem,	///< Range: A release following an item grab
	eListboxEvent_EnterItem,///< Index: The cursor entered the item region
	eListboxEvent_LeaveItem,///< Index: The cursor left the item region
	eListboxEvent_DragOver,	///< Range: The cursor was moved following an item grab, before an item drop
/* Radiobox */
	eRadioboxEvent_GrabOption,	///< Index: The cursor was over an option during a press
	eRadioboxEvent_DropOption,	///< Index: A release following an option grab
	eRadioboxEvent_EnterOption,	///< Index: The cursor entered the option region
	eRadioboxEvent_LeaveOption,	///< Index: The cursor left the option region
/* Slider */
	eSliderEvent_GrabThumb,	///< Basic: The cursor was over the thumb during a press
	eSliderEvent_DropThumb,	///< Basic: A release following a thumb grab
	eSliderEvent_EnterThumb,///< Basic: The cursor entered the thumb region
	eSliderEvent_LeaveThumb,///< Basic: The cursor left the thumb region
	eSliderEvent_SnapThumb,	///< Basic: The cursor was over the slider, but not the thumb, while pressed
	eSliderEvent_CatchThumb,///< Point: The cursor was over the thumb during a press
	eSliderEvent_ReleaseThumb,	///< Basic: A release following a thumb catch
	eSliderEvent_DragThumb,	///< Basic: The cursor was moved following a thumb catch, before a thumb release
/* Textbox */
	eTextboxEvent_GrabSpot,	///< Index: The cursor was over a spot during a press
	eTextboxEvent_DropSpot,	///< Range: A release following a spot grab
	eTextboxEvent_DragOver	///< Range: The cursor was moved following a spot grab, before a spot drop
} WidgetEventType;

#ifdef __cplusplus
}
#endif	// __cplusplus

#endif // USER_INTERFACE_EVENT_H
