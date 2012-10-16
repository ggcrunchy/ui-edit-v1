#ifndef USER_INTERFACE_WIDGET_IMP_H
#define USER_INTERFACE_WIDGET_IMP_H

#include <SDL/SDL_types.h>
#include <bitset>
#include <map>
#include <string>

/// @brief Base type for user interface elements
struct Widget {
// Types
	/// @brief Descriptor for a widget type
	enum WidgetType {
		ePane,	///< Widget is a pane
		eButton,///< Widget is a button
		eSlider,///< Widget is a slider
		eListbox,	///< Widget is a listbox
		eTextbox,	///< Widget is a textbox
		eCheckbox,	///< Widget is a checkbox
		eRadiobox,	///< Widget is a radiobox
		eNumTypes	///< Count of widget types
	};
// Members
	std::map<std::basic_string<wchar_t>, Uint32>::iterator mTagPos;	///< Tag lookup position of widget
	std::bitset<32> mStatus;///< Current status of widget
	void (*mDraw)(Uint32, void *);	///< Widget draw routine
	void (*mHitTest)(Uint32, float, float, void *);	///< Widget hit test routine
	void (*mProcessEvent)(Uint32, enum _WidgetEventType, void *);///< Widget event handling routine
	float mX;	///< Relative x coordinate, in [0,1]
	float mY;	///< Relative y coordinate, in [0,1]
	float mW;	///< Relative width, in [0,1]
	float mH;	///< Relative height, in [0,1]
	WidgetType mType;///< Type assigned to widget
// Enumerations
	enum {
		eTagged,///< The widget is tagged
		eUnder,	///< The widget is beneath the cursor
		eHeld,	///< The widget is held by the cursor
		eIn,///< The widget was beneath the cursor on the previous input propagation
		eWidgetNext	///< Used to continue the bits in derived types
	};
// Methods
	Widget (WidgetType type);
	virtual ~Widget (void);

	static Widget & Get (Uint32 name);

	void Grab (void * pContext);
	void Drop (void * pContext);
	void Enter (void * pContext);
	void Leave (void * pContext);

	virtual void Clear (void);
	virtual void CleanTemps (void);

	virtual void Choose (float fCursorX, float fCursorY, bool bPressed, void * pContext) = 0;	///< Implemented by individual panes and pane items
	virtual bool Update (float fCursorX, float fCursorY, bool bPressed, void * pContext) = 0;	///< Implemented by individual panes and pane items
};

#endif // USER_INTERFACE_WIDGET_IMP_H
