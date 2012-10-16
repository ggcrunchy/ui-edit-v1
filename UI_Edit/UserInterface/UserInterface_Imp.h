#ifndef USER_INTERFACE_USER_INTERFACE_IMP_H
#define USER_INTERFACE_USER_INTERFACE_IMP_H

#include <SDL/SDL_types.h>
#include "Widget_Imp.h"
#include "WidgetEvent.h"
#include <bitset>
#include <list>
#include <map>
#include <string>
#include <vector>

/// @brief Structure used to represent the user interface manager
struct UserInterface {
	// Types
	/// @brief Descriptor for an event type
	enum EventType {
		eBasicEvent,///< Event with no extra data
		eIndexEvent,///< Event with index-type datum
		eRangeEvent,///< Event with range-type datum
		ePointEvent	///< Event with point-type datum
	};
	/// @brief Structure used to represent a range-type event datum
	struct EventRange {
	// Members
		Uint32 mStart;	///< Start of range
		Uint32 mCount;	///< Count of items in range
	};
	/// @brief Structure used to represent a point-type event datum
	struct EventPoint {
	// Members
		float mX;	///< General x coordinate, in [0,1]
		float mY;	///< General y coordinate, in [0,1]
	};
	/// @brief Union used to represent a general event
	union Event {
		Uint32 mIndex;	///< Index-type datum
		EventRange mRange;	///< Range-type datum
		EventPoint mPoint;	///< Point-type datum
	};
// Members
	Event mEvent;///< Event currently being processed
	std::vector<struct PaneLayer *> mLayers;///< Storage for pane layers
	std::vector<struct Widget *> mWidgets;	///< Storage for widgets
	std::vector<Uint32> mFrame;	///< Range of active menu layer indices
	std::list<Uint32> mFreeLayers;	///< List of free indices in pane layer vector
	std::list<Uint32> mFreeWidgets;	///< List of free indices in widget vector
	std::map<std::basic_string<wchar_t>, Uint32> mLayerTags;///< Associative labels for pane layers
	std::map<std::basic_string<wchar_t>, Uint32> mWidgetTags;	///< Associative labels for widgets
	std::bitset<32> mStatus;///< Current status of system
	EventType mEventType;///< Type of current event
	Uint32 mChoice;	///< Widget chosen by cursor
	Uint32 mCurrentHit;	///< Widget currently being hit tested
// Enumerations
	enum {
		eNullWidget = 0xFFFFFFFF	///< Reserved for null widget
	};
	enum {
		eInitialized,	///< The system is initialized
		ePressed	///< The cursor was pressed on the previous input propagation
	};
// Methods
	UserInterface (void);
	~UserInterface (void);

	static UserInterface & Get (void);

	Uint32 GetFreeLayerSlot (void);
	Uint32 GetFreeWidgetSlot (void);

	int CreateWidget (Widget::WidgetType type, Uint32 * name);

	void CheckForHits (float fCursorX, float fCursorY, void * pContext);
	void ResolveHits (float fCursorX, float fCursorY, bool bPressed, void * pContext);

	void IssueBasicEvent (WidgetEventType type, void * pContext);
	void IssueIndexEvent (WidgetEventType type, Uint32 index, void * pContext);
	void IssueRangeEvent (WidgetEventType type, Uint32 start, Uint32 count, void * pContext);
	void IssuePointEvent (WidgetEventType type, float fX, float fY, void * pContext);
};

#endif // USER_INTERFACE_USER_INTERFACE_IMP_H
