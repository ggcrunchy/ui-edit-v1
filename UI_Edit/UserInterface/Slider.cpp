/// @file
/// Interface for slider widgets

#include "Slider_Imp.h"
#include "UserInterface_Imp.h"
#include "PaneItem.h"
#include "Slider.h"
#include "UserInterface.h"
#include <cassert>

/// @brief Instantiates a slider
/// @param name [out] On success, the name used to reference the slider
/// @return 0 on failure, non-0 for success
/// @note Tested
int Slider_Create (Uint32 * name)
{
	assert(name != 0);

	if (!UserInterface_WasInit()) return 0;

	return UserInterface::Get().CreateWidget(Widget::eSlider, name);
}

/// @brief Sets a slider's thumb offset; the offset is clamped to lie in [0,1]
/// @param name Name used to reference the slider
/// @param fOffset Relative offset, in [0,1]
/// @return 0 on failure, non-0 for success
/// @note Tested
int Slider_SetOffset (Uint32 name, float fOffset)
{
	if (!Slider_IsValid(name)) return 0;

	////////////////////////////////////////////////////////////////////////////////
	// We ensure that the offset will lie in unit range. We then assign the offset.
	////////////////////////////////////////////////////////////////////////////////
	if (fOffset < 0.0f) fOffset = 0.0f;
	if (fOffset > 1.0f) fOffset = 1.0f;

	Slider::Get(name).mOffset = fOffset;

	return 1;
}

/// @brief Gets a slider's thumb offset
/// @param name Name used to reference the slider
/// @param fOffset [out] On success, the thumb offset
/// @return 0 on failure, non-0 for success
/// @note Tested
int Slider_GetOffset (Uint32 name, float * fOffset)
{
	assert(fOffset != 0);

	if (!Slider_IsValid(name)) return 0;

	*fOffset = Slider::Get(name).mOffset;

	return 1;
}

/// @brief Allows or disallows snapping a slider's thumb to an offset
/// @param name Name used to reference the slider
/// @param bAllow If true, we allow snapping
/// @return 0 on failure, non-0 for success
/// @note Tested
int Slider_AllowSnap (Uint32 name, SDL_bool bAllow)
{
	if (!Slider_IsValid(name)) return 0;

	Slider::Get(name).mStatus[Slider::eThumbCannotSnap] = !bAllow;

	return 1;
}

/// @brief Allows or disallows dragging of the slider thumb
/// @param name Name used to reference the slider
/// @param bAllow If true, we allow dragging
/// @return 0 on failure, non-0 for success
/// @note Tested
int Slider_AllowThumbDrag (Uint32 name, SDL_bool bAllow)
{
	if (!Slider_IsValid(name)) return 0;

	Slider::Get(name).mStatus[Slider::eThumbCannotDrag] = !bAllow;

	return 1;
}

/// @brief Sets a slider's fit best offset callback
/// @param name Name used to reference the slider
/// @param fitBestOffset Callback used to fit an offset, in [0,1]
/// @return 0 on failure, non-0 for success
/// @note Tested
int Slider_SetFitBestOffset (Uint32 name, float (*fitBestOffset)(Uint32, float, float, void *))
{
	if (!Slider_IsValid(name)) return 0;

	Slider::Get(name).mFitBestOffset = fitBestOffset;

	return 1;
}

/// @brief Used to signal that the cursor is over a slider thumb
/// @note Function will NOP if not called from a hit test callback during input propagation,
///		  after the slider itself has been signaled as beneath the cursor
/// @note Tested
void Slider_SignalCursorOverThumb (void)
{
	UserInterface & UI = UserInterface::Get();

	if (!Slider_IsValid(UI.mCurrentHit)) return;

	Slider & slider = Slider::Get(UI.mCurrentHit);

	if (slider.mStatus[Widget::eUnder]) slider.mStatus[Slider::eThumbUnder] = true;
}

/// @brief Indicates whether a slider's thumb is grabbed
/// @param name Name used to reference the slider
/// @return A boolean indicating whether the thumb is grabbed
/// @note Tested
SDL_bool Slider_IsThumbGrabbed (Uint32 name)
{
	if (!Slider_IsValid(name)) return SDL_FALSE;
	if (!Slider::Get(name).mStatus[Slider::eThumbHeld]) return SDL_FALSE;
	
	return SDL_TRUE;
}

/// @brief Indicates whether a slider's thumb is entered
/// @param name Name used to reference the slider
/// @return A boolean indicating whether the thumb is entered
/// @note Tested
SDL_bool Slider_IsThumbEntered (Uint32 name)
{
	if (!Slider_IsValid(name)) return SDL_FALSE;
	if (!Slider::Get(name).mStatus[Slider::eThumbIn]) return SDL_FALSE;

	return SDL_TRUE;
}

/// @brief Indicates whether a slider's thumb can be snapped
/// @param name Name used to reference the slider
/// @return A boolean indicating whether the thumb can be snapped
/// @note Tested
SDL_bool Slider_IsSnapAllowed (Uint32 name)
{
	if (!Slider_IsValid(name)) return SDL_FALSE;
	if (Slider::Get(name).mStatus[Slider::eThumbCannotSnap]) return SDL_FALSE;
	
	return SDL_TRUE;
}

/// @brief Indicates whether the thumb can be dragged
/// @param name Name used to reference the slider
/// @return A boolean indicating whether the thumb can be dragged
/// @note Tested
SDL_bool Slider_IsThumbDragAllowed (Uint32 name)
{
	if (!Slider_IsValid(name)) return SDL_FALSE;
	if (Slider::Get(name).mStatus[Slider::eThumbCannotDrag]) return SDL_FALSE;
	
	return SDL_TRUE;
}

/// @brief Indicates whether a slider's thumb is caught
/// @param name Name used to reference the slider
/// @return A boolean indicating whether the thumb is caught
/// @note Tested
SDL_bool Slider_IsThumbCaught (Uint32 name)
{
	if (!Slider_IsValid(name)) return SDL_FALSE;
	if (!Slider::Get(name).mStatus[Slider::eThumbCaught]) return SDL_FALSE;
	
	return SDL_TRUE;
}

/// @brief Indicates whether a name corresponds to a valid slider
/// @param name Name used to reference the slider
/// @return A boolean indicating name validity
/// @note Tested
SDL_bool Slider_IsValid (Uint32 name)
{
	/////////////////////////////////////////////////////////////////////////////////////
	// A slider is valid if it is first a valid pane item and also is typed as a slider.
	/////////////////////////////////////////////////////////////////////////////////////
	if (!PaneItem_IsValid(name)) return SDL_FALSE;
	if (Widget::Get(name).mType != Widget::eSlider) return SDL_FALSE;

	return SDL_TRUE;
}