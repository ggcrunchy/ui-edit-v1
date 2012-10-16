#ifndef USER_INTERFACE_SLIDER_H
#define USER_INTERFACE_SLIDER_H

#include <SDL/SDL_types.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

int Slider_Create (Uint32 * name);
int Slider_SetOffset (Uint32 name, float fOffset);
int Slider_GetOffset (Uint32 name, float * fOffset);
int Slider_AllowSnap (Uint32 name, SDL_bool bAllow);
int Slider_AllowThumbDrag (Uint32 name, SDL_bool bAllow);
int Slider_SetFitBestOffset (Uint32 name, float (*fitBestOffset)(Uint32, float, float, void *));

void Slider_SignalCursorOverThumb (void);

SDL_bool Slider_IsThumbGrabbed (Uint32 name);
SDL_bool Slider_IsThumbEntered (Uint32 name);
SDL_bool Slider_IsSnapAllowed (Uint32 name);
SDL_bool Slider_IsThumbDragAllowed (Uint32 name);
SDL_bool Slider_IsThumbCaught (Uint32 name);
SDL_bool Slider_IsValid (Uint32 name);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // USER_INTERFACE_SLIDER_H
