/// @file
/// Interface for pane layers

#include "Pane_Imp.h"
#include "PaneLayer_Imp.h"
#include "UserInterface_Imp.h"
#include "Pane.h"
#include "PaneLayer.h"
#include "UserInterface.h"
#include <cassert>

/// @brief Instantiates a pane layer
/// @param name [out] On success, the name used to reference the layer
/// @return 0 on failure, non-0 for success
/// @note Tested
int PaneLayer_Create (Uint32 * name)
{
	assert(name != 0);

	////////////////////////////////////////////////////////////////////////////////
	// We first find an open slot in the layer vector. We then construct the layer.
	// Finally, we give the layer's name back to the user.
	////////////////////////////////////////////////////////////////////////////////
	try {
		Uint32 slot = UserInterface::Get().GetFreeLayerSlot();

		UserInterface::Get().mLayers[slot] = new PaneLayer();

		*name = slot;
	} catch (std::bad_alloc &) { return 0; }

	return 1;
}

/// @brief Terminates a pane layer instance
/// @param name Name used to reference the layer
/// @return 0 on failure, non-0 for success
/// @note Tested
int PaneLayer_Destroy (Uint32 name)
{
	if (!PaneLayer_IsValid(name)) return 0;

	UserInterface & UI = UserInterface::Get();

	////////////////////////////////////////////////////////////////////////////////////
	// We invoke the layer's destructor. We then add the layer name to the list of free
	// layers, and nullify the spot to preserve validity.
	////////////////////////////////////////////////////////////////////////////////////
	delete UI.mLayers[name];

	UI.mFreeLayers.push_back(name);

	UI.mLayers[name] = 0;

	return 1;
}

/// @brief Adds a pane to a given region of a pane layer
/// @param name Name used to reference the layer
/// @param pane Name used to reference the pane
/// @param fX Relative x coordinate, in [0,1]
/// @param fY Relative y coordinate, in [0,1]
/// @param fW Relative width, in [0,1]
/// @param fH Relative height, in [0,1]
/// @return 0 on failure, non-0 for success
/// @note Tested
int PaneLayer_AddPane (Uint32 name, Uint32 pane, float fX, float fY, float fW, float fH)
{
	if (!PaneLayer_IsValid(name)) return 0;
	if (!Pane_IsValid(pane)) return 0;
	if (fX >= 1.0f || fW <= 0.0f) return 0;
	if (fY >= 1.0f || fH <= 0.0f) return 0;

	Pane & rPane = Pane::Get(pane);

	/////////////////////////////////////////////////////////////////////////////////////
	// If the pane is already loaded into the layer, we can ignore this step. Otherwise,
	// we first remove the pane from the layer it is currently in, if it is loaded. We
	// then add its name to the layer's list of pane names, and give the pane back an
	// iterator so that it may later be easily removed from the layer. Finally, we give
	// the pane the layer name as reference.
	///////////////////////////////////////////////////////////////////////////////////
	if (rPane.mLayer != name)
	{
		Pane_RemoveFromLayer(pane);

		PaneLayer & layer = PaneLayer::Get(name);

		layer.mPanes.push_front(pane);

		rPane.mIter = layer.mPanes.begin();
		rPane.mLayer = name;
	}

	////////////////////////////////////////////////////////////////////////////////////
	// We first ensure that the coordinates and dimensions will confine the pane to the
	// user interface region. We then set the coordinates and dimensions.
	////////////////////////////////////////////////////////////////////////////////////
	if (fX < 0.0f) fX = 0.0f;
	if (fX + fW > 1.0f) fW = 1.0f - fX;
	if (fY < 0.0f) fY = 0.0f;
	if (fY + fH > 1.0f) fH = 1.0f - fY;

	rPane.mX = fX;
	rPane.mY = fY;
	rPane.mW = fW;
	rPane.mH = fH;

	return 1;
}

/// @brief Sets the tag of a pane layer
/// @param name Name used to reference the layer
/// @param tag Unicode tag to associate with layer
/// @return 0 on failure, non-0 for success
/// @note Tested
int PaneLayer_SetTag (Uint32 name, wchar_t const * tag)
{
	assert(tag != 0);

	if (!PaneLayer_IsValid(name)) return 0;

	UserInterface & UI = UserInterface::Get();

	//////////////////////////////////////////////////////////////////////////////////////
	// We first remove any tag currently associated with the layer. We then check whether
	// the tag itself is in use. If it is, we indicate that the layer associated with it
	// no longer acknowledges it.
	//////////////////////////////////////////////////////////////////////////////////////
	PaneLayer_Untag(name);

	std::map<std::basic_string<wchar_t>, Uint32>::iterator item = UI.mLayerTags.find(tag);
	
	if (item != UI.mLayerTags.end())
	{
		assert(UI.mLayers[item->second] != 0);

		UI.mLayers[item->second]->mTagged = false;
	}

	//////////////////////////////////////////////////////////////////////////////////////
	// We now associate the name with the tag. In order to facilitate easy disassociation
	// at a later time, we cache an iterator into the tag map. Finally, we indicate that
	// this layer is tagged.
	//////////////////////////////////////////////////////////////////////////////////////
	UI.mLayerTags[tag] = name;

	UI.mLayers[name]->mTagPos = UI.mLayerTags.find(tag);

	UI.mLayers[name]->mTagged = true;

	return 1;
}

/// @brief Gets the tag of a pane layer
/// @param name Name used to reference the layer
/// @param tag [out] On success, the Unicode tag associated with the layer
/// @return 0 on failure, non-0 for success
/// @note Tested
int PaneLayer_GetTag (Uint32 name, wchar_t * tag)
{
	assert(tag != 0);

	if (!PaneLayer_IsTagged(name)) return 0;

	std::basic_string<wchar_t> const & rTag = PaneLayer::Get(name).mTagPos->first;

	rTag.copy(tag, rTag.size());

	tag[rTag.size()] = 0;

	return 1;
}

/// @brief Removes the tag, if any, from a pane layer
/// @param name Name used to reference the layer
/// @return 0 on failure, non-0 for success
/// @note Tested
int PaneLayer_Untag (Uint32 name)
{
	if (!PaneLayer_IsValid(name)) return 0;

	PaneLayer & layer = PaneLayer::Get(name);

	/////////////////////////////////////////////////////////////////////////////////////
	// We remove the tag mapped to the layer, and indicate that it is untagged. If there
	// is no tag, this is a NOP.
	/////////////////////////////////////////////////////////////////////////////////////
	if (layer.mTagged)
	{
		UserInterface::Get().mLayerTags.erase(layer.mTagPos);

		layer.mTagged = false;
	}

	return 1;
}

/// @brief Gets the slot into which a pane layer is loaded
/// @param name Name used to reference the layer
/// @param slot [out] On success, the layer's slot
/// @return 0 on failure, non-0 for success
/// @note Tested
int PaneLayer_GetSlot (Uint32 name, Uint32 * slot)
{
	assert(slot != 0);

	if (!PaneLayer_IsLoaded(name)) return 0;

	*slot = PaneLayer::Get(name).mSlot;

	return 1;
}

/// @brief Gets the count of panes loaded into the pane layer
/// @param name Name used to reference the layer
/// @param count [out] On success, the pane count
/// @return 0 on failure, non-0 for success
/// @note Tested
int PaneLayer_GetPaneCount (Uint32 name, Uint32 * count)
{
	assert(count != 0);

	if (!PaneLayer_IsValid(name)) return 0;

	*count = static_cast<Uint32>(PaneLayer::Get(name).mPanes.size());

	return 1;
}

/// @brief Indicates whether a layer is loaded into the frame
/// @param name Name used to reference the layer
/// @return A boolean indicating whether the layer is loaded
/// @note Tested
SDL_bool PaneLayer_IsLoaded (Uint32 name)
{
	//////////////////////////////////////////////
	// A layer is loaded if its slot is not null.
	//////////////////////////////////////////////
	if (!PaneLayer_IsValid(name)) return SDL_FALSE;
	if (PaneLayer::eNoSlot == PaneLayer::Get(name).mSlot) return SDL_FALSE;

	return SDL_TRUE;
}

/// @brief Indicates whether a layer is tagged
/// @param name Name used to reference the layer
/// @return A boolean indicating whether the layer is tagged
/// @note Tested
SDL_bool PaneLayer_IsTagged (Uint32 name)
{
	if (!PaneLayer_IsValid(name)) return SDL_FALSE;
	if (!PaneLayer::Get(name).mTagged) return SDL_FALSE;

	return SDL_TRUE;
}

/// @brief Indicates whether a name corresponds to a valid pane layer
/// @param name Name used to reference the layer
/// @return A boolean indicating name validity
/// @note Tested
SDL_bool PaneLayer_IsValid (Uint32 name)
{
	///////////////////////////////////////////////////////////////////////////////////////
	// A layer name is invalid if it is out of range of the user interface manager's layer
	// vector or there is no entry corresponding to its name in said vector.
	///////////////////////////////////////////////////////////////////////////////////////
	if (name >= UserInterface::Get().mLayers.size()) return SDL_FALSE;
	if (0 == UserInterface::Get().mLayers[name]) return SDL_FALSE;

	assert(UserInterface_WasInit());

	return SDL_TRUE;
}