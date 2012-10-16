/// @file
/// Interface for textbox widgets

#include "Textbox_Imp.h"
#include "UserInterface_Imp.h"
#include "PaneItem.h"
#include "Textbox.h"
#include "UserInterface.h"
#include <cassert>

/// @brief Instantiates a textbox
/// @param name [out] On success, the name used to reference the textbox
/// @return 0 on failure, non-0 for success
/// @note Tested
int Textbox_Create (Uint32 * name)
{
	assert(name != 0);

	if (!UserInterface_WasInit()) return 0;

	return UserInterface::Get().CreateWidget(Widget::eTextbox, name);
}

/// @brief Sets the offset from which to begin drawing and hit testing text
/// @param name Name used to reference the textbox
/// @param offset Offset at which to begin
/// @return 0 on failure, non-0 for success
/// @note Tested
int Textbox_SetOffset (Uint32 name, Uint32 offset)
{
	if (!Textbox_IsSpotValid(name, offset, SDL_FALSE)) return 0;

	Textbox::Get(name).mOffset = offset;

	return 1;
}

/// @brief Gets the offset from which to begin drawing and hit testing text
/// @param name Name used to reference the textbox
/// @param offset [out] On success, the offset at which to begin
/// @return 0 on failure, non-0 for success
/// @note Tested
int Textbox_GetOffset (Uint32 name, Uint32 * offset)
{
	assert(offset != 0);

	if (!Textbox_IsValid(name)) return 0;

	*offset = Textbox::Get(name).mOffset;

	return 1;
}

/// @brief Sets the offset of the cursor
/// @param name Name used to reference the textbox
/// @param cursor The cursor offset; this can be equal to the size of the textbox's string,
///				  in which case the cursor is after the string
/// @return 0 on failure, non-0 for success
/// @note Tested
int Textbox_SetCursor (Uint32 name, Uint32 cursor)
{
	if (!Textbox_IsSpotValid(name, cursor, SDL_TRUE)) return 0;

	Textbox::Get(name).mCursor = cursor;

	return 1;
}

/// @brief Gets the offset of the cursor
/// @param name Name used to reference the textbox
/// @param cursor [out] On success, the cursor offset
/// @return 0 on failure, non-0 for success
/// @note Tested
int Textbox_GetCursor (Uint32 name, Uint32 * cursor)
{
	assert(cursor != 0);

	if (!Textbox_IsValid(name)) return 0;

	*cursor = Textbox::Get(name).mCursor;

	return 1;
}

/// @brief Gets the textbox's currently held spot
/// @param name Name used to reference the textbox
/// @param spot [out] On success, the held spot
/// @return 0 on failure, non-0 for success
/// @note Tested
int Textbox_GetHeldSpot (Uint32 name, Uint32 * spot)
{
	assert(spot != 0);

	if (!Textbox_IsValid(name)) return 0;

	Textbox & textbox = Textbox::Get(name);

	if (Textbox::eNoSpot == textbox.mHeldSpot) return 0;

	*spot = textbox.mHeldSpot;

	return 1;
}

/// @brief Sets the maximum permissible string length; this may truncate the current text
///		   string, and will unselect any truncated characters
/// @param name Name used to reference the textbox
/// @param max The maximum length allowed for strings
/// @return 0 on failure, non-0 for success
/// @note Tested
int Textbox_SetMaxCharCount (Uint32 name, Uint32 max)
{
	if (!Textbox_IsValid(name)) return 0;

	Textbox & textbox = Textbox::Get(name);

	/////////////////////////////////////////////////////////////////////////////////////
	// If the new maximum is less than the current one, we trim any excess text. We then
	// set the new maximum string length.
	/////////////////////////////////////////////////////////////////////////////////////
	if (max < textbox.mMaxLength)
	{
		Uint32 count = textbox.mMaxLength - max;

		Textbox_DeleteSubstr(name, max, &count);
	}

	textbox.mMaxLength = max;

	return 1;
}

/// @brief Gets the maximum permissible string length
/// @param name Name used to reference the textbox
/// @param max [out] On success, the maximum length allowed
/// @return 0 on failure, non-0 for success
/// @note Tested
int Textbox_GetMaxCharCount (Uint32 name, Uint32 * max)
{
	assert(max != 0);

	if (!Textbox_IsValid(name)) return 0;

	*max = Textbox::Get(name).mMaxLength;

	return 1;
}

/// @brief Gets the count of characters in the textbox's string
/// @param name Name used to reference the textbox
/// @param count [out] On success, the count of characters
/// @return 0 on failure, non-0 for success
/// @note Tested
int Textbox_GetCharCount (Uint32 name, Uint32 * count)
{
	assert(count != 0);

	if (!Textbox_IsValid(name)) return 0;

	*count = static_cast<Uint32>(Textbox::Get(name).mString.size());

	return 1;
}

/// @brief Gets the index from which the selected text begins
/// @param name Name used to reference the textbox
/// @param start [out] On success, the starting index
/// @return 0 on failure, non-0 for success
/// @note Tested
int Textbox_GetSelectStart (Uint32 name, Uint32 * start)
{
	assert(start != 0);

	if (!Textbox_IsValid(name)) return 0;

	Textbox & textbox = Textbox::Get(name);

	/////////////////////////////////////////////////////////////
	// If no text is selected, there is no valid start position.
	/////////////////////////////////////////////////////////////
	if (0 == textbox.mNumSelect) return 0;

	*start = textbox.mSelect;

	return 1;
}

/// @brief Gets the count of selected characters
/// @param name Name used to reference the textbox
/// @param count [out] On success, the count of selected characters
/// @return 0 on failure, non-0 for success
/// @note Tested
int Textbox_GetSelectCount (Uint32 name, Uint32 * count)
{
	assert(count != 0);

	if (!Textbox_IsValid(name)) return 0;

	*count = Textbox::Get(name).mNumSelect;

	return 1;
}

/// @brief Sets a character in the textbox's string
/// @param name Name used to reference the textbox
/// @param where Index at which character is added; this can be equal to the size of the
///				 textbox's string, in which case the character is appended
/// @param Char The Unicode character to add
/// @param bInsert If true, the character is inserted; otherwise, it overwrites
/// @return 0 on failure, non-0 for success
/// @note Tested
int Textbox_SetChar (Uint32 name, Uint32 where, wchar_t Char, SDL_bool bInsert)
{
	if (!Textbox_IsSpotValid(name, where, SDL_TRUE)) return 0;

	Textbox & textbox = Textbox::Get(name);

	//////////////////////////////////////////////////////////////////////////////////////
	// If we do not want to insert, we simply overwrite the character at the given index.
	// We must resort to insertion if the index corresponds to the entry after the text.
	//////////////////////////////////////////////////////////////////////////////////////
	if (!bInsert && where != textbox.mString.size())
	{
		textbox.mString[where] = Char;
	}
	
	////////////////////////////////////////////////////////////////////////////////////
	// If we insert, we first ensure that we do not have a string of maximum length. If
	// not, we then insert, and follow up by modifying selection properties as needed.
	// If the offset or cursor is after the point of insertion, we need to move the
	// index ahead one place. Similarly, if a spot is held and follows the point of
	// insertion, we move it ahead one place.
	////////////////////////////////////////////////////////////////////////////////////
	else
	{
		if (textbox.mString.size() == textbox.mMaxLength) return 0;

		textbox.mString.insert(where, 1, Char);

		if (textbox.mNumSelect != 0) textbox.AdjustForInsert(where, 1);

		if (textbox.mOffset > where) ++textbox.mOffset;
		if (textbox.mCursor > where) ++textbox.mCursor;

		if (textbox.mHeldSpot != Textbox::eNoSpot)
		{
			if (textbox.mHeldSpot > where) ++textbox.mHeldSpot;
		}
	}

	return 1;
}

/// @brief Gets a character in the textbox's string
/// @param name Name used to reference the textbox
/// @param where Index of character to get
/// @param Char [out] On success, the Unicode character
/// @return 0 on failure, non-0 for success
/// @note Tested
int Textbox_GetChar (Uint32 name, Uint32 where, wchar_t * Char)
{
	assert(Char != 0);

	if (!Textbox_IsSpotValid(name, where, SDL_FALSE)) return 0;

	*Char = Textbox::Get(name).mString[where];

	return 1;
}

/// @brief Removes a character from the textbox's string
/// @param name Name used to reference the textbox
/// @param where Index of character to remove
/// @return 0 on failure, non-0 for success
/// @note Tested
int Textbox_DeleteChar (Uint32 name, Uint32 where)
{
	if (!Textbox_IsSpotValid(name, where, SDL_FALSE)) return 0;

	Textbox & textbox = Textbox::Get(name);

	///////////////////////////////////////////////////////////////////////////
	// We first perform the actual character deletion, and cache the new size.
	///////////////////////////////////////////////////////////////////////////
	textbox.mString.erase(where, 1);

	Uint32 size = static_cast<Uint32>(textbox.mString.size());

	///////////////////////////////////////////////////////////////////////////////////
	// If there is a selection, we then modify selection properties: If we remove from
	// within the selection, we reduce the selection count by one; otherwise, if we
	// remove before the selection, we reduce the start of the selection by one.
	///////////////////////////////////////////////////////////////////////////////////
	if (textbox.mNumSelect != 0)
	{
		if (where >= textbox.mSelect && where < textbox.mSelect + textbox.mNumSelect)
		{
			--textbox.mNumSelect;
		}

		else if (where < textbox.mSelect)
		{
			--textbox.mSelect;
		}
	}

	///////////////////////////////////////////////////////////////////////////////////
	// If the offset or cursor follows the point of removal, we need to move the index
	// one place. We do similar upkeep if a held spot follows the point of removal. If
	// the held spot is at the point of removal, we nullify the spot. If we deleted
	// the offset, and it was at the end of the string, we move the offset back one.
	///////////////////////////////////////////////////////////////////////////////////
	if (textbox.mOffset > where) --textbox.mOffset;
	if (textbox.mCursor > where) --textbox.mCursor;

	if (textbox.mOffset == size && size != 0) --textbox.mOffset;

	if (textbox.mHeldSpot != Textbox::eNoSpot)
	{
		if (textbox.mHeldSpot > where) --textbox.mHeldSpot;

		else if (textbox.mHeldSpot == where) textbox.mHeldSpot = Textbox::eNoSpot;
	}

	return 1;
}

/// @brief Sets a substring in the textbox's string
/// @param name Name used to reference the textbox
/// @param where Index from which to begin adding the substring; this can be equal to the
///				 size of the textbox's string, in which case the string is appended
/// @param str Zero-terminated Unicode substring to add
/// @param numChars [in-out] The count of characters to add; on success, the count of
///					characters actually added
/// @param bInsert If true, the substring is inserted; otherwise, it overwrites
/// @return 0 on failure, non-0 for success
/// @note Tested
int Textbox_SetSubstr (Uint32 name, Uint32 where, wchar_t const * str, Uint32 * numChars, SDL_bool bInsert)
{
	assert(str != 0);
	assert(numChars != 0);

	if (!Textbox_IsSpotValid(name, where, SDL_TRUE)) return 0;

	Textbox & textbox = Textbox::Get(name);

	/////////////////////////////////////////////////////////////////////////////////////
	// If the requested count will extend beyond the maximum string length, we bound it.
	/////////////////////////////////////////////////////////////////////////////////////
	*numChars = textbox.TrimToMax(where, *numChars);
	
	////////////////////////////////////////////////////////////////////////////////////
	// If we insert, we first check whether our modified count will cause the string to
	// exceed the maximum length. If so, we bound the count. We insert the substring of
	// the given length, and follow up by modifying selection properties as needed. If
	// the offset or cursor follow the point of insertion, we need to move the index
	// ahead by the modified count. Similarly, if a spot is held and follows the point
	// of insertion, we move the spot ahead by the modified count.
	////////////////////////////////////////////////////////////////////////////////////
	if (bInsert)
	{
		if (textbox.mString.size() + *numChars > textbox.mMaxLength)
		{
			*numChars = textbox.mMaxLength - static_cast<Uint32>(textbox.mString.size());
		}

		textbox.mString.insert(where, str, *numChars);

		if (textbox.mNumSelect != 0) textbox.AdjustForInsert(where, *numChars);

		if (textbox.mOffset > where) textbox.mOffset += *numChars;
		if (textbox.mCursor > where) textbox.mCursor += *numChars;

		if (textbox.mHeldSpot != Textbox::eNoSpot)
		{
			if (textbox.mHeldSpot > where) textbox.mHeldSpot += *numChars;
		}
	}

	////////////////////////////////////////////////////////////
	// If we overwrite, we replace and/or append to the string.
	////////////////////////////////////////////////////////////
	else
	{
		textbox.mString.replace(where, *numChars, str, *numChars);
	}

	return 1;
}

/// @brief Gets a substring from the textbox's string
/// @param name Name used to reference the textbox
/// @param where Index from which to begin getting the substring
/// @param str [out] On success, the Unicode substring
/// @param numChars [in-out] The count of characters to get; on success, the count of
///					characters actually read
/// @return 0 on failure, non-0 for success
/// @note Tested
int Textbox_GetSubstr (Uint32 name, Uint32 where, wchar_t * str, Uint32 * numChars)
{
	assert(str != 0);
	assert(numChars != 0);

	if (!Textbox_IsSpotValid(name, where, SDL_TRUE)) return 0;

	Textbox & textbox = Textbox::Get(name);

	*numChars = textbox.TrimToSize(where, *numChars);

	textbox.mString.copy(str, *numChars, where);

	str[*numChars] = 0;

	return 1;
}

/// @brief Removes a substring from the textbox's string
/// @param name Name used to reference the textbox
/// @param where Index from which to begin removal
/// @param numChars [in-out] The count of characters to remove; on success, the count of
///					characters actually removed
/// @return 0 on failure, non-0 for success
/// @note Tested
int Textbox_DeleteSubstr (Uint32 name, Uint32 where, Uint32 * numChars)
{
	assert(numChars != 0);

	if (!Textbox_IsSpotValid(name, where, SDL_TRUE)) return 0;

	Textbox & textbox = Textbox::Get(name);

	////////////////////////////////////////////////////////////////////////////////////
	// If the requested count will extend beyond the string, we bound it. We then erase
	// the substring of the given length, and cache the new size.
	////////////////////////////////////////////////////////////////////////////////////
	*numChars = textbox.TrimToSize(where, *numChars);

	textbox.mString.erase(where, *numChars);

	Uint32 size = static_cast<Uint32>(textbox.mString.size());

	////////////////////////////////////////////////////////////////////////////////////
	// If the offset or cursor follows the point of removal, we need to move it back to
	// remain consistent. We reduce the index by the lesser of the count of characters
	// removed and the distance from the point of removal to the index.
	////////////////////////////////////////////////////////////////////////////////////
	if (textbox.mOffset > where)
	{
		Uint32 adjust = textbox.mOffset - where;

		if (*numChars < adjust) adjust = *numChars;

		textbox.mOffset -= adjust;
	}

	if (textbox.mCursor > where)
	{
		Uint32 adjust = textbox.mCursor - where;

		if (*numChars < adjust) adjust = *numChars;

		textbox.mCursor -= adjust;
	}

	///////////////////////////////////////////////////////////////////////////////////
	// If we deleted a block at the end of the string, and it included the offset, the
	// offset will now be after the string, so we move it back one spot.
	///////////////////////////////////////////////////////////////////////////////////
	if (textbox.mOffset == size && size > 0) --textbox.mOffset;

	/////////////////////////////////////////////////////////////////////////////////
	// If a spot is held, we need to do some special upkeep. If the spot follows the
	// interval being removed, we move the spot back by the number of items removed.
	// If the spot is within the interval being removed, we nullify the spot.
	/////////////////////////////////////////////////////////////////////////////////
	if (textbox.mHeldSpot != Textbox::eNoSpot)
	{
		if (textbox.mHeldSpot >= where + *numChars) textbox.mHeldSpot -= *numChars;

		else if (textbox.mHeldSpot >= where) textbox.mHeldSpot = Textbox::eNoSpot;
	}

	////////////////////////////////////////////////////////////////////
	// If there is a selection, we need to modify selection properties.
	////////////////////////////////////////////////////////////////////
	if (textbox.mNumSelect != 0)
	{
		///////////////////////////////////////////////////////////////////////////////////
		// We first check whether the substring and selection intervals overlap. If so, we
		// reduce the selection count by the amount of overlap.
		///////////////////////////////////////////////////////////////////////////////////
		Uint32 begin = where, end = begin + *numChars;

		if (end > textbox.mSelect && begin < textbox.mSelect + textbox.mNumSelect)
		{
			if (textbox.mSelect > begin)
			{
				begin = textbox.mSelect;
			}

			if (textbox.mSelect + textbox.mNumSelect < end)
			{
				end = textbox.mSelect + textbox.mNumSelect;
			}

			textbox.mNumSelect -= end - begin;
		}

		///////////////////////////////////////////////////////////////////////////////
		// If the selection interval follows the point of removal, we need to slide it 
		// back. We move it by the lesser of the count of characters removed and the
		// distance from the point of removal to the start of the interval.
		///////////////////////////////////////////////////////////////////////////////
		if (textbox.mSelect > where)
		{
			Uint32 adjust = textbox.mSelect - where;

			if (*numChars < adjust) adjust = *numChars;

			textbox.mSelect -= adjust;
		}
	}

	return 1;
}

/// @brief Selects a character in the textbox's string
/// @param name Name used to reference the textbox
/// @param where Index of character to select
/// @return 0 on failure, non-0 for success
/// @note Tested
int Textbox_SelectChar (Uint32 name, Uint32 where)
{
	if (!Textbox_IsSpotValid(name, where, SDL_FALSE)) return 0;

	Textbox & textbox = Textbox::Get(name);

	textbox.mSelect = where;
	textbox.mNumSelect = 1;

	return 1;
}

/// @brief Selects a substring in the textbox's string
/// @param name Name used to reference the textbox
/// @param where Index from which to begin selection
/// @param numChars [in-out] Count of characters to select; on success, the count of
///					characters actually selected
/// @return 0 on failure, non-0 for success
/// @note Tested
int Textbox_SelectSubstr (Uint32 name, Uint32 where, Uint32 * numChars)
{
	assert(numChars != 0);

	if (!Textbox_IsSpotValid(name, where, SDL_TRUE)) return 0;

	Textbox & textbox = Textbox::Get(name);

	/////////////////////////////////////////////////////////////////////////////////////
	// If the requested count will extend beyond the string, we bound it. We then select
	// a substring of the given length. 
	/////////////////////////////////////////////////////////////////////////////////////
	*numChars = textbox.TrimToSize(where, *numChars);

	textbox.mSelect = where;
	textbox.mNumSelect = *numChars;

	return 1;
}

/// @brief Gets the selected text from the textbox's string
/// @param name Name used to reference the textbox
/// @param str [out] On success, the zero-terminated Unicode substring
/// @return 0 on failure, non-0 for success
/// @note Tested
int Textbox_GetSelectionSubstr (Uint32 name, wchar_t * str)
{
	assert(str != 0);

	if (!Textbox_IsValid(name)) return 0;

	Textbox & textbox = Textbox::Get(name);

	/////////////////////////////////////////////////////
	// If no text is selected, there is no valid string.
	/////////////////////////////////////////////////////
	if (0 == textbox.mNumSelect) return 0;

	textbox.mString.copy(str, textbox.mNumSelect, textbox.mSelect);

	str[textbox.mNumSelect] = 0;

	return 1;
}

/// @brief Unselects all text
/// @param name Name used to reference the textbox
/// @return 0 on failure, non-0 for success
/// @note Tested
int Textbox_RemoveSelection (Uint32 name)
{
	if (!Textbox_IsValid(name)) return 0;

	///////////////////////////////////////////////////////////////////////////////
	// Text is effectively unselected by zeroing the count of selected characters.
	///////////////////////////////////////////////////////////////////////////////
	Textbox::Get(name).mNumSelect = 0;

	return 1;
}

/// @brief Allows or disallows clicking of a textbox's spots
/// @param name Name used to reference the textbox
/// @param bAllow If true, we allow clicks
/// @return 0 on failure, non-0 for success
/// @note Tested
int Textbox_AllowSpotClick (Uint32 name, SDL_bool bAllow)
{
	if (!Textbox_IsValid(name)) return 0;

	Textbox & textbox = Textbox::Get(name);

	//////////////////////////////////////////////////////////////////////////////////////
	// We clear or set the clickable flag as called for. If we are disallowing clicks, we
	// nullify any held spots.
	//////////////////////////////////////////////////////////////////////////////////////
	if (bAllow)
	{
		textbox.mStatus[Textbox::eCannotClickSpot] = false;
	}

	else
	{	
		textbox.mStatus[Textbox::eCannotClickSpot] = true;

		textbox.mHeldSpot = Textbox::eNoSpot;
	}

	return 1;
}

/// @brief Allows or disallows dragging over a textbox's text
/// @param name Name used to reference the textbox
/// @param bAllow If true, we allow dragging
/// @return 0 on failure, non-0 for success
/// @note Tested
int Textbox_AllowDragOver (Uint32 name, SDL_bool bAllow)
{
	if (!Textbox_IsValid(name)) return 0;

	Textbox::Get(name).mStatus[Textbox::eCannotDragOver] = !bAllow;

	return 1;
}

/// @brief Sets a textbox's fit best spot callback
/// @param name Name used to reference the textbox
/// @param fitBestSpot Callback used to fit a spot, in [0,size]
/// @return 0 on failure, non-0 for success
/// @note Tested
int Textbox_SetFitBestSpot (Uint32 name, Uint32 (*fitBestSpot)(Uint32, float, float, void *))
{
	if (!Textbox_IsValid(name)) return 0;

	Textbox::Get(name).mFitBestSpot = fitBestSpot;

	return 1;
}

/// @brief Used to signal that the cursor is over a textbox spot
/// @note Function will NOP if not called from a hit test callback during input propagation,
///		  after the textbox itself has been signaled as beneath the cursor
/// @note Tested
void Textbox_SignalCursorOverSpot (Uint32 where)
{
	UserInterface & UI = UserInterface::Get();

	if (!Textbox_IsSpotValid(UI.mCurrentHit, where, SDL_TRUE)) return;

	Textbox & textbox = Textbox::Get(UI.mCurrentHit);

	if (textbox.mStatus[Widget::eUnder]) textbox.mUnderSpot = where;
}

/// @brief Indicates whether a textbox's spots may be clicked
/// @param name Name used to reference the textbox
/// @return A boolean indicating whether the textbox's spots may be clicked
/// @note Tested
SDL_bool Textbox_IsSpotClickAllowed (Uint32 name)
{
	if (!Textbox_IsValid(name)) return SDL_FALSE;
	if (Textbox::Get(name).mStatus[Textbox::eCannotClickSpot]) return SDL_FALSE;
	
	return SDL_TRUE;
}

/// @brief Indicates whether dragging is allowed over a textbox's text
/// @param name Name used to reference the textbox
/// @return A boolean indicating whether dragging is allowed
/// @note Tested
SDL_bool Textbox_IsDragOverAllowed (Uint32 name)
{
	if (!Textbox_IsValid(name)) return SDL_FALSE;
	if (Textbox::Get(name).mStatus[Textbox::eCannotDragOver]) return SDL_FALSE;
	
	return SDL_TRUE;
}

/// @brief Indicates whether a spot is within the textbox's string
/// @param name Name used to reference the textbox
/// @param where Index of spot in the textbox
/// @param bAddSpot If true, the spot after the text is considered valid
/// @return A boolean indicating spot validity
/// @note Tested
SDL_bool Textbox_IsSpotValid (Uint32 name, Uint32 where, SDL_bool bAddSpot)
{
	if (!Textbox_IsValid(name)) return SDL_FALSE;

	////////////////////////////////////////////////////////////////////////////////////
	// A spot is valid if it falls in the range of its textbox's string. In the case of 
	// add spots, we extend the range by one to allow for spots at the end.
	////////////////////////////////////////////////////////////////////////////////////
	Uint32 range = static_cast<Uint32>(Textbox::Get(name).mString.size());

	if (bAddSpot) ++range;

	if (where >= range) return SDL_FALSE;

	return SDL_TRUE;
}

/// @brief Indicates whether a name corresponds to a valid textbox
/// @param name Name used to reference the textbox
/// @return A boolean indicating name validity
/// @note Tested
SDL_bool Textbox_IsValid (Uint32 name)
{
	///////////////////////////////////////////////////////////////////////////////////////
	// A textbox is valid if it is first a valid pane item and also is typed as a textbox.
	///////////////////////////////////////////////////////////////////////////////////////
	if (!PaneItem_IsValid(name)) return SDL_FALSE;
	if (Widget::Get(name).mType != Widget::eTextbox) return SDL_FALSE;

	return SDL_TRUE;
}