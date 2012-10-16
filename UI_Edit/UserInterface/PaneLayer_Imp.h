#ifndef USER_INTERFACE_PANE_LAYER_IMP_H
#define USER_INTERFACE_PANE_LAYER_IMP_H

#include <SDL/SDL_types.h>
#include <list>
#include <map>
#include <string>

/// @brief Structure used to represent a layer into which panes may be loaded, and which
///		   can be used to set up the user interface frame
struct PaneLayer {
// Members
	std::list<Uint32> mPanes;	///< Panes loaded into the layer
	std::map<std::basic_string<wchar_t>, Uint32>::iterator mTagPos;	///< Tag lookup position of layer
	Uint32 mSlot;	///< Slot layer is occupying
	bool mTagged;	///< If true, the layer is tagged
// Enumerations
	enum {
		eNoSlot = 0xFFFFFFFF	///< Index reserved for null slot
	};
// Methods
	PaneLayer (void);
	~PaneLayer (void);

	static PaneLayer & Get (Uint32 name);
};

#endif // USER_INTERFACE_PANE_LAYER_IMP_H
