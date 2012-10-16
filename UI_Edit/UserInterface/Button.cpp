/// @file
/// Interface for button widgets

#include "Button_Imp.h"
#include "UserInterface_Imp.h"
#include "Button.h"
#include "PaneItem.h"
#include "UserInterface.h"
#include <cassert>

/// @brief Instantiates a button
/// @param name [out] On success, the name used to reference the button
/// @return 0 on failure, non-0 for success
/// @note Tested
int Button_Create (Uint32 * name)
{
	assert(name != 0);

	if (!UserInterface_WasInit()) return 0;

	return UserInterface::Get().CreateWidget(Widget::eButton, name);
}

/// @brief Allows or disallows pushing of a button
/// @param name Name used to reference the button
/// @param bAllow If true, we allow pushes
/// @return 0 on failure, non-0 for success
/// @note Tested
int Button_AllowPush (Uint32 name, SDL_bool bAllow)
{
	if (!Button_IsValid(name)) return 0;

	Button & button = Button::Get(name);

	/////////////////////////////////////////////////////////////////////////////////////
	// We clear or set the pushable flag as called for. If we are disallowing pushes, we
	// undo any push that has already occurred.
	/////////////////////////////////////////////////////////////////////////////////////
	if (bAllow)
	{
		button.mStatus[Button::eCannotPush] = false;
	}

	else
	{
		button.mStatus[Button::eCannotPush] = true;
		button.mStatus[Button::ePushed] = false;
	}

	return 1;
}

/// @brief Indicates whether a button can be pushed
/// @param name Named used to reference the button
/// @return A boolean indicating whether the button can be pushed
/// @note Tested
SDL_bool Button_IsPushAllowed (Uint32 name)
{
	if (!Button_IsValid(name)) return SDL_FALSE;
	if (Button::Get(name).mStatus[Button::eCannotPush]) return SDL_FALSE;
	
	return SDL_TRUE;
}

/// @brief Indicates whether a button is pushed
/// @param name Name used to reference the button
/// @return A boolean indicating whether the button is pushed
/// @note Tested
SDL_bool Button_IsPushed (Uint32 name)
{
	if (!Button_IsValid(name)) return SDL_FALSE;
	if (!Button::Get(name).mStatus[Button::ePushed]) return SDL_FALSE;
	
	return SDL_TRUE;
}

/// @brief Indicates whether a name corresponds to a valid button
/// @param name Name used to reference the button
/// @return A boolean indicating name validity
/// @note Tested
SDL_bool Button_IsValid (Uint32 name)
{
	/////////////////////////////////////////////////////////////////////////////////////
	// A button is valid if it is first a valid pane item and also is typed as a button.
	/////////////////////////////////////////////////////////////////////////////////////
	if (!PaneItem_IsValid(name)) return SDL_FALSE;
	if (Widget::Get(name).mType != Widget::eButton) return SDL_FALSE;

	return SDL_TRUE;
}