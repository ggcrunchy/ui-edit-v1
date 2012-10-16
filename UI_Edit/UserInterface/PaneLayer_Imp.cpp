#include "PaneLayer_Imp.h"
#include "UserInterface_Imp.h"
#include "Pane.h"
#include "UserInterface.h"

/// @brief Constructs a PaneLayer object
/// @note Tested
PaneLayer::PaneLayer (void) : mSlot(eNoSlot), mTagged(false)
{
}

/// @brief Destructs a PaneLayer object
/// @note Tested
PaneLayer::~PaneLayer (void)
{
	//////////////////////////////////////////////////////////////////////////////////////
	// If necessary, we untag the layer. If the layer is loaded into the frame, we unload
	// it. Finally, we unload all the layer's panes.
	//////////////////////////////////////////////////////////////////////////////////////
	if (mTagged) UserInterface::Get().mLayerTags.erase(mTagPos);

	if (mSlot != eNoSlot) UserInterface_RemoveFrameLayer(mSlot);

	while (!mPanes.empty())
	{
		Pane_RemoveFromLayer(mPanes.front());
	}
}

/// @brief Acquires a PaneLayer object
/// @param name Name used to reference the pane layer
/// @return Reference to the PaneLayer object
/// @note Tested
PaneLayer & PaneLayer::Get (Uint32 name)
{
	return *UserInterface::Get().mLayers[name];
}