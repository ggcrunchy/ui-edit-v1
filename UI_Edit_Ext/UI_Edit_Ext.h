#ifndef UI_EDIT_EXT_UI_EDIT_EXT_H
#define UI_EDIT_EXT_UI_EDIT_EXT_H

#include <SDL/SDL.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <lua.h>

/* Graphics */
typedef void * Picture_h;
typedef void * Font_h;
typedef void * TextImage_h;

extern DECLSPEC int SetupGraphics (int width, int height, int bpp, SDL_bool bFullscreen);
extern DECLSPEC int CloseGraphics (void);
extern DECLSPEC int SetVideoMode (int width, int height, int bpp, SDL_bool bFullscreen);
extern DECLSPEC int GetVideoSize (Uint32 * width, Uint32 * height);
extern DECLSPEC int PrepareFrame (void);
extern DECLSPEC int DrawFrame (void);
extern DECLSPEC int ReloadImage (char const * name);
extern DECLSPEC int LoadPicture (char const * name, float fS0, float fT0, float fS1, float fT1, Picture_h * picture);
extern DECLSPEC int DrawPicture (Picture_h picture, float fX, float fY, float fW, float fH);
extern DECLSPEC int GetPictureName (Picture_h picture, char * name);
extern DECLSPEC int GetPictureTexels (Picture_h picture, float * fS0, float * fT0, float * fS1, float * fT1);
extern DECLSPEC int UnloadPicture (Picture_h picture);
extern DECLSPEC int LoadFont (char const * name, int size, Font_h * font);
extern DECLSPEC int UnloadFont (Font_h font);
extern DECLSPEC int GetTextSize (Font_h font, char const * text, int * width, int * height);
extern DECLSPEC int LoadTextImage (Font_h font, char const * text, SDL_Color color, TextImage_h * textImage);
extern DECLSPEC int DrawTextImage (TextImage_h textImage, float fX, float fY, float fW, float fH);
extern DECLSPEC int DrawClippedTextImage (TextImage_h textImage, float fX, float fY, float fW, float fH, float fMW, float fMH);
extern DECLSPEC int UnloadTextImage (TextImage_h textImage);
extern DECLSPEC int DrawBox (float fX, float fY, float fW, float fH, float fR, float fG, float fB);
extern DECLSPEC int DrawLine (float fSX, float fSY, float fEX, float fEY, float fR, float fG, float fB);
extern DECLSPEC int DrawGrid (float fX, float fY, float fW, float fH, Uint32 xCuts, Uint32 yCuts);

/* Lua */
extern DECLSPEC int LoadLuaFunctions (lua_State * state);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // UI_EDIT_EXT_UI_EDIT_EXT_H
