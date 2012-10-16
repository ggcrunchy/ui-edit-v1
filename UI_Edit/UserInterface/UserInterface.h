#ifndef USER_INTERFACE_USER_INTERFACE_H
#define USER_INTERFACE_USER_INTERFACE_H

#include <SDL/SDL_types.h>

#ifdef __cplusplus
extern "C" {
#endif	// __cplusplus

int UserInterface_InitSystem (void);
int UserInterface_PropagateInput (float fCursorX, float fCursorY, SDL_bool bPressed, void * pContext);
int UserInterface_ClearInput (void);
int UserInterface_Draw (void * pContext);
int UserInterface_RemoveFrameLayer (Uint32 slot);
int UserInterface_ClearFrameLayers (void);
int UserInterface_LoadFrameLayers (Uint32 const * layers, Uint32 count);
int UserInterface_SwapFrameLayers (Uint32 one, Uint32 two);
int UserInterface_GetFrameLayer (Uint32 slot, Uint32 * layer);
int UserInterface_GetFrameSize (Uint32 * size);
int UserInterface_FindLayer (wchar_t const * tag, Uint32 * layer);
int UserInterface_FindWidget (wchar_t const * tag, Uint32 * widget);
int UserInterface_GetChoice (Uint32 * widget);
int UserInterface_GetEventIndex (Uint32 * index);
int UserInterface_GetEventRange (Uint32 * start, Uint32 * count);
int UserInterface_GetEventPoint (float * fX, float * fY);

void UserInterface_QuitSystem (void);

SDL_bool UserInterface_IsFrameSlotValid (Uint32 slot);
SDL_bool UserInterface_WasInit (void);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // USER_INTERFACE_USER_INTERFACE_H
