#ifndef USER_INTERFACE_TEXTBOX_H
#define USER_INTERFACE_TEXTBOX_H

#include <SDL/SDL_types.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

int Textbox_Create (Uint32 * name);
int Textbox_SetOffset (Uint32 name, Uint32 offset);
int Textbox_GetOffset (Uint32 name, Uint32 * offset);
int Textbox_SetCursor (Uint32 name, Uint32 cursor);
int Textbox_GetCursor (Uint32 name, Uint32 * cursor);
int Textbox_GetHeldSpot (Uint32 name, Uint32 * spot);
int Textbox_SetMaxCharCount (Uint32 name, Uint32 max);
int Textbox_GetMaxCharCount (Uint32 name, Uint32 * max);
int Textbox_GetCharCount (Uint32 name, Uint32 * count);
int Textbox_GetSelectStart (Uint32 name, Uint32 * start);
int Textbox_GetSelectCount (Uint32 name, Uint32 * count);
int Textbox_SetChar (Uint32 name, Uint32 where, wchar_t Char, SDL_bool bInsert);
int Textbox_GetChar (Uint32 name, Uint32 where, wchar_t * Char);
int Textbox_DeleteChar (Uint32 name, Uint32 where);
int Textbox_SetSubstr (Uint32 name, Uint32 where, wchar_t const * str, Uint32 * numChars, SDL_bool bInsert);
int Textbox_GetSubstr (Uint32 name, Uint32 where, wchar_t * str, Uint32 * numChars);
int Textbox_DeleteSubstr (Uint32 name, Uint32 where, Uint32 * numChars);
int Textbox_SelectChar (Uint32 name, Uint32 where);
int Textbox_SelectSubstr (Uint32 name, Uint32 where, Uint32 * numChars);
int Textbox_GetSelectionSubstr (Uint32 name, wchar_t * str);
int Textbox_RemoveSelection (Uint32 name);
int Textbox_AllowSpotClick (Uint32 name, SDL_bool bAllow);
int Textbox_AllowDragOver (Uint32 name, SDL_bool bAllow);
int Textbox_SetFitBestSpot (Uint32 name, Uint32 (*fitBestSpot)(Uint32, float, float, void *));

void Textbox_SignalCursorOverSpot (Uint32 where);

SDL_bool Textbox_IsSpotClickAllowed (Uint32 name);
SDL_bool Textbox_IsDragOverAllowed (Uint32 name);
SDL_bool Textbox_IsSpotValid (Uint32 name, Uint32 where, SDL_bool bAddSpot);
SDL_bool Textbox_IsValid (Uint32 name);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // USER_INTERFACE_TEXTBOX_H
