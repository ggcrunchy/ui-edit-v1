#ifndef USER_INTERFACE_WIDGET_H
#define USER_INTERFACE_WIDGET_H

#include <SDL/SDL_types.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

int Widget_Destroy (Uint32 name);
int Widget_SetTag (Uint32 name, wchar_t const * tag);
int Widget_GetTag (Uint32 name, wchar_t * tag);
int Widget_Untag (Uint32 name);
int Widget_SetXY (Uint32 name, float fX, float fY);
int Widget_SetWH (Uint32 name, float fW, float fH);
int Widget_GetXYWH (Uint32 name, float * fX, float * fY, float * fW, float * fH, SDL_bool bGlobal);
int Widget_SetDraw (Uint32 name, void (*draw)(Uint32, void *));
int Widget_SetHitTest (Uint32 name, void (*hitTest)(Uint32, float, float, void *));
int Widget_SetProcessEvent (Uint32 name, void (*processEvent)(Uint32, enum _WidgetEventType, void *));

void Widget_SignalCursorOver (void);

SDL_bool Widget_IsGrabbed (Uint32 name);
SDL_bool Widget_IsEntered (Uint32 name);
SDL_bool Widget_IsTagged (Uint32 name);
SDL_bool Widget_IsLoaded (Uint32 name);
SDL_bool Widget_IsValid (Uint32 name);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // USER_INTERFACE_WIDGET_H
