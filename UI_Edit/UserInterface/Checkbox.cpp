/// @file
/// Interface for checkbox widgets

#include "Checkbox_Imp.h"
#include "UserInterface_Imp.h"
#include "Checkbox.h"
#include "PaneItem.h"
#include <cassert>

/// @brief Instantiates a checkbox
/// @param name [out] On success, the name used to reference the checkbox
/// @return 0 on failure, non-0 for success
/// @note Tested
int Checkbox_Create (Uint32 * name)
{
	assert(name != 0);

	return UserInterface::Get().CreateWidget(Widget::eCheckbox, name);
}

/// @brief Checks or unchecks a checkbox
/// @param name Name used to reference the checkbox
/// @param bCheck If true, checks the checkbox
/// @return 0 on failure, non-0 for success
/// @note Tested
int Checkbox_Check (Uint32 name, SDL_bool bCheck)
{
	if (!Checkbox_IsValid(name)) return 0;

	Checkbox::Get(name).mStatus[Checkbox::eChecked] = bCheck != SDL_FALSE;

	return 1;
}

/// @brief Flips the checkbox's check state
/// @param name Name used to reference the checkbox
/// @return 0 on failure, non-0 for success
/// @note Tested
int Checkbox_ToggleCheck (Uint32 name)
{
	if (!Checkbox_IsValid(name)) return 0;

	std::bitset<32> & status = Checkbox::Get(name).mStatus;

	status[Checkbox::eChecked] = !status[Checkbox::eChecked];

	return 1;
}

/// @brief Allows or disallows clicking a checkbox
/// @param name Name used to reference the checkbox
/// @param bAllow If true, we allow clicking
/// @return 0 on failure, non-0 for success
/// @note Tested
int Checkbox_AllowClick (Uint32 name, SDL_bool bAllow)
{
	if (!Checkbox_IsValid(name)) return 0;

	Checkbox & checkbox = Checkbox::Get(name);

	//////////////////////////////////////////////////////////////////////////////////////
	// We clear or set the clickable flag as called for. If we are disallowing clicks, we
	// undo any click that has already occurred.
	//////////////////////////////////////////////////////////////////////////////////////
	if (bAllow)
	{
		checkbox.mStatus[Checkbox::eCannotClick] = false;
	}

	else
	{
		checkbox.mStatus[Checkbox::eCannotClick] = true;
		checkbox.mStatus[Checkbox::eClicked] = false;
	}

	return 1;
}

/// @brief Indicates whether a checkbox can be clicked
/// @param name Name used to reference the checkbox
/// @return A boolean indicating whether the checkbox can be clicked
/// @note Tested
SDL_bool Checkbox_IsClickAllowed (Uint32 name)
{
	if (!Checkbox_IsValid(name)) return SDL_FALSE;
	if (Checkbox::Get(name).mStatus[Checkbox::eCannotClick]) return SDL_FALSE;

	return SDL_TRUE;
}

/// @brief Indicates whether a checkbox is checked
/// @param name Name used to reference the checkbox
/// @return A boolean indicating whether the checkbox is checked
/// @note Tested
SDL_bool Checkbox_IsChecked (Uint32 name)
{
	if (!Checkbox_IsValid(name)) return SDL_FALSE;
	if (!Checkbox::Get(name).mStatus[Checkbox::eChecked]) return SDL_FALSE;

	return SDL_TRUE;
}

/// @brief Indicates whether a name corresponds to a valid checkbox
/// @param name Name used to reference the checkbox
/// @return A boolean indicating name validity
/// @note Tested
SDL_bool Checkbox_IsValid (Uint32 name)
{
	///////////////////////////////////////////////////////////////////////////////
	// A checkbox is valid if it is first a valid pane item and also is typed as a
	// checkbox.
	///////////////////////////////////////////////////////////////////////////////
	if (!PaneItem_IsValid(name)) return SDL_FALSE;
	if (Widget::Get(name).mType != Widget::eCheckbox) return SDL_FALSE;

	return SDL_TRUE;
}