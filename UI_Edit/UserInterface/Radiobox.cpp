/// @file
/// Interface for radiobox widgets

#include "Radiobox_Imp.h"
#include "UserInterface_Imp.h"
#include "Radiobox.h"
#include "PaneItem.h"
#include <cassert>

/// @brief Instantiates a radiobox
/// @param name [out] On success, the name used to reference the radiobox
/// @return 0 on failure, non-0 for success
/// @note Tested
int Radiobox_Create (Uint32 * name)
{
	assert(name != 0);

	return UserInterface::Get().CreateWidget(Widget::eRadiobox, name);
}

/// @brief Sets up a radiobox with a given count of options, one of which is chosen
/// @param name Name used to reference the radiobox
/// @param count Number of options to assign to the radiobox
/// @param choice Option in [0,count) to set as the current choice
/// @return 0 on failure, non-0 for success
/// @note Tested
int Radiobox_Setup (Uint32 name, Uint32 count, Uint32 choice)
{
	if (!Radiobox_IsValid(name)) return 0;
	if (choice >= count) return 0;

	Radiobox & radiobox = Radiobox::Get(name);

	///////////////////////////////////////////////////////////////////////
	// We first nullify all current option data, as it is no longer valid.
	///////////////////////////////////////////////////////////////////////
	radiobox.mHeldOption = Radiobox::eNoOption;
	radiobox.mInOption = Radiobox::eNoOption;

	/////////////////////////////
	// We now perform the setup.
	/////////////////////////////
	radiobox.mNumOptions = count;
	radiobox.mChoice = choice;

	return 1;
}

/// @brief Gets the number of options in a radiobox
/// @param name Name used to reference the radiobox
/// @param count [out] On success, the option count
/// @return 0 on failure, non-0 for success
/// @note Tested
int Radiobox_GetOptionCount (Uint32 name, Uint32 * count)
{
	assert(count != 0);

	if (!Radiobox_IsValid(name)) return 0;

	*count = Radiobox::Get(name).mNumOptions;

	return 1;
}

/// @brief Sets a radiobox's current choice
/// @param name Name used to reference the radiobox
/// @param choice Index of option to set as the choice
/// @return 0 on failure, non-0 for success
/// @note Tested
int Radiobox_SetChoice (Uint32 name, Uint32 choice)
{
	if (!Radiobox_IsOptionValid(name, choice)) return 0;

	Radiobox::Get(name).mChoice = choice;

	return 1;
}

/// @brief Gets a radiobox's current choice
/// @param name Name used to reference the radiobox
/// @param choice [out] On success, the index of the choice option
/// @return 0 on failure, non-0 for success
/// @note Tested
int Radiobox_GetChoice (Uint32 name, Uint32 * choice)
{
	assert(choice != 0);

	if (!Radiobox_IsValid(name)) return 0;
	if (!Radiobox_IsOptionValid(name, 0)) return 0;

	*choice = Radiobox::Get(name).mChoice;

	return 1;
}

/// @brief Gets the radiobox's currently held option
/// @param name Name used to reference the radiobox
/// @param option [out] On success, the held option
/// @return 0 on failure, non-0 for success
/// @note Tested
int Radiobox_GetHeldOption (Uint32 name, Uint32 * option)
{
	assert(option != 0);

	if (!Radiobox_IsValid(name)) return 0;

	Radiobox & radiobox = Radiobox::Get(name);

	if (Radiobox::eNoOption == radiobox.mHeldOption) return 0;

	*option = radiobox.mHeldOption;

	return 1;
}

/// @brief Gets the radiobox's currently entered option
/// @param name Name used to reference the radiobox
/// @param option [out] On success, the entered option
/// @return 0 on failure, non-0 for success
/// @note Tested
int Radiobox_GetInOption (Uint32 name, Uint32 * option)
{
	assert(option != 0);

	if (!Radiobox_IsValid(name)) return 0;

	Radiobox & radiobox = Radiobox::Get(name);

	if (Radiobox::eNoOption == radiobox.mInOption) return 0;

	*option = radiobox.mInOption;

	return 1;
}

/// @brief Allows or disallows clicking a radiobox's options
/// @param name Name used to reference the radiobox
/// @param bAllow If true, we allow clicking
/// @return 0 on failure, non-0 for success
/// @note Tested
int Radiobox_AllowClick (Uint32 name, SDL_bool bAllow)
{
	if (!Radiobox_IsValid(name)) return 0;

	Radiobox & radiobox = Radiobox::Get(name);

	//////////////////////////////////////////////////////////////////////////////////////
	// We clear or set the clickable flag as called for. If we are disallowing clicks, we
	// nullify any held options.
	//////////////////////////////////////////////////////////////////////////////////////
	if (bAllow)
	{
		radiobox.mStatus[Radiobox::eCannotClick] = false;
	}

	else
	{
		radiobox.mStatus[Radiobox::eCannotClick] = true;

		radiobox.mHeldOption = Radiobox::eNoOption;
	}

	return 1;
}

/// @brief Used to signal that the cursor is over a radiobox option
/// @param option The option beneath the cursor
/// @note Function will NOP if not called from a hit test callback during input propagation,
///		  after the radiobox itself has been signaled as beneath the cursor
/// @note Tested
void Radiobox_SignalCursorOverOption (Uint32 option)
{
	UserInterface & UI = UserInterface::Get();

	if (!Radiobox_IsOptionValid(UI.mCurrentHit, option)) return;

	Radiobox & radiobox = Radiobox::Get(UI.mCurrentHit);

	if (radiobox.mStatus[Widget::eUnder]) radiobox.mUnderOption = option;
}

/// @brief Indicates whether a radiobox's options can be clicked
/// @param name Name used to reference the radiobox
/// @return A boolean indicating whether options can be clicked
/// @note Tested
SDL_bool Radiobox_IsClickAllowed (Uint32 name)
{
	if (!Radiobox_IsValid(name)) return SDL_FALSE;
	if (Radiobox::Get(name).mStatus[Radiobox::eCannotClick]) return SDL_FALSE;

	return SDL_TRUE;
}

/// @brief Indicates whether an option is found in the radiobox
/// @param name Name used to reference the radiobox
/// @param option Index of option in the radiobox
/// @return A boolean indicating option validity
/// @note Tested
SDL_bool Radiobox_IsOptionValid (Uint32 name, Uint32 option)
{
	///////////////////////////////////////////////////////////////////////////////
	// An option is valid if it falls in the range of its radiobox's option count.
	///////////////////////////////////////////////////////////////////////////////
	if (!Radiobox_IsValid(name)) return SDL_FALSE;
	if (option >= Radiobox::Get(name).mNumOptions) return SDL_FALSE;

	return SDL_TRUE;
}

/// @brief Indicates whether a name corresponds to a valid radiobox
/// @param name Name used to reference the radiobox
/// @return A boolean indicating name validity
/// @note Tested
SDL_bool Radiobox_IsValid (Uint32 name)
{
	///////////////////////////////////////////////////////////////////////////////
	// A radiobox is valid if it is first a valid pane item and also is typed as a
	// radiobox.
	///////////////////////////////////////////////////////////////////////////////
	if (!PaneItem_IsValid(name)) return SDL_FALSE;
	if (Widget::Get(name).mType != Widget::eRadiobox) return SDL_FALSE;

	return SDL_TRUE;
}