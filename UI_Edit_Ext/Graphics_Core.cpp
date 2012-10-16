/// @file
/// Internal graphics system for renderer

#include "UI_Edit_Ext.h"
#include "Graphics_Imp.h"
#include <iostream>
#include <cassert>

using namespace UI_Edit_Ext;

/// Global graphics core object
GraphicsCore g_Core;

/// Red mask constant
Uint32 const c_Rmask = SDL_BYTEORDER == SDL_BIG_ENDIAN ? 0xFF000000 : 0x000000FF;
/// Green mask constant
Uint32 const c_Gmask = SDL_BYTEORDER == SDL_BIG_ENDIAN ? 0x00FF0000 : 0x0000FF00;
/// Blue mask constant
Uint32 const c_Bmask = SDL_BYTEORDER == SDL_BIG_ENDIAN ? 0x0000FF00 : 0x00FF0000;
/// Alpha mask constant
Uint32 const c_Amask = SDL_BYTEORDER == SDL_BIG_ENDIAN ? 0x000000FF : 0xFF000000;

/// @brief Constructs an Image object
/// @note Tested
Image::Image (void) : mCount(0)
{
	/////////////////////////////////////////////////////////////////////
	// We give the image's texture a name. If this fails, the name is 0.
	/////////////////////////////////////////////////////////////////////
	glGenTextures(1, &mTexture);
}

/// @brief Destructs an Image object
/// @note Tested
Image::~Image (void)
{
	assert(0 == mCount);

	/////////////////////////////////////
	// We first remove the texture name.
	/////////////////////////////////////
	glDeleteTextures(1, &mTexture);

	//////////////////////////////////////////////////////////////////////////////////////
	// We now remove the image from the graphics core. For our needs, there should not be
	// any issue with huge maps, so we just iteratively find our image and pluck it out.
	//////////////////////////////////////////////////////////////////////////////////////
	for (std::map<std::string, Image*>::iterator iter = g_Core.mImages.begin(); iter != g_Core.mImages.end(); ++iter)
	{
		if (iter->second != this) continue;
		
		g_Core.mImages.erase(iter);

		return;
	}
}

/// @brief Constructs a Picture object
/// @note Tested
Picture::Picture (Image * image) : mImage(image)
{
	assert(image != 0);

	///////////////////////////////////////////////////////////////////////////////////
	// A picture is always bound to an image. Thus, we increment its image's reference
	// count on construction.
	///////////////////////////////////////////////////////////////////////////////////
	++mImage->mCount;
}

/// @brief Destructs a Picture object
/// @note Tested
Picture::~Picture (void)
{
	assert(mImage != 0);
	assert(mImage->mCount > 0);

	//////////////////////////////////////////////////////////////////////////////////////
	// On destruction, we decrement the image's reference count. If this leaves the image
	// unreferenced, we also destroy the image.
	//////////////////////////////////////////////////////////////////////////////////////
	if (0 == --mImage->mCount) delete mImage;
}

/// @brief Constructs a TextImage object
/// @param texture Name of texture containing text image data
/// @note Tested
TextImage::TextImage (GLuint texture) : mTexture(texture)
{
}

/// @brief Destructs a TextImage object
/// @note Tested
TextImage::~TextImage (void)
{
}

/// @brief Constructs a GraphicsCore object
/// @note Tested
GraphicsCore::GraphicsCore (void) : mResW(0), mResH(0)
{
}

/// @brief Destructs a GraphicsCore object
/// @note Tested
GraphicsCore::~GraphicsCore (void)
{
}

/// @brief Sets up the renderer used by the editor
/// @param width Screen width of mode
/// @param height Screen height of mode
/// @param bpp Bits per pixel of mode
/// @param bFullscreen If true, this is a full-screen video mode
/// @return 0 on failure, non-0 for success
/// @note Tested
DECLSPEC int SetupGraphics (int width, int height, int bpp, SDL_bool bFullscreen)
{
	//////////////////////////////////////////////////////
	// We set up the video subsystem, enabling rendering.
	//////////////////////////////////////////////////////
	if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0)
	{
		std::cerr << "Unable to initialize SDL video: " << SDL_GetError() << std::endl;

		return 0;
	}

	////////////////////////////////////////
	// We set up the TrueType font support.
	////////////////////////////////////////
	if (TTF_Init() < 0)
	{
		std::cerr << "Unable to initialize SDL_ttf: " << TTF_GetError() << std::endl;

		return 0;
	}

	/////////////////////////////////////////////////////////////////////////////////////
	// We set some properties we will use to configure OpenGL. We then set the requested
	// video mode.
	/////////////////////////////////////////////////////////////////////////////////////
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	if (SetVideoMode(width, height, bpp, bFullscreen) == 0) return 0;

	////////////////////////////////////////////////////////
	// We now set some "nice" initial graphical properties.
	////////////////////////////////////////////////////////
    glShadeModel(GL_SMOOTH);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return 1;
}

/// @brief Closes the renderer used by the editor
/// @return 0 on failure, non-0 for success
/// @note Tested
DECLSPEC int CloseGraphics (void)
{
	/////////////////////////////////////////////////////////////
	// We unload all pictures; doing so unloads images, as well.
	/////////////////////////////////////////////////////////////
	while (!g_Core.mPictures.empty())
	{
		UnloadPicture(*g_Core.mPictures.begin());
	}

	assert(g_Core.mImages.empty());

	////////////////////////////////////////////
	// We now unload all fonts and text images.
	////////////////////////////////////////////
	while (!g_Core.mFonts.empty())
	{
		UnloadFont(g_Core.mFonts.begin()->second);
	}

	while (!g_Core.mTextImages.empty())
	{
		UnloadTextImage(*g_Core.mTextImages.begin());
	}

	///////////////////////////////////
	// We close TrueType font support.
	///////////////////////////////////
	if (TTF_WasInit()) TTF_Quit();

	/////////////////////////////////
	// We close the video subsystem.
	/////////////////////////////////
	if (SDL_WasInit(SDL_INIT_VIDEO)) SDL_QuitSubSystem(SDL_INIT_VIDEO);

	return 1;
}

/// @brief Sets the renderer's video mode
/// @param width Screen width of mode
/// @param height Screen height of mode
/// @param bpp Bits per pixel of mode
/// @param bFullscreen If true, this is a full-screen video mode
/// @return 0 on failure, non-0 for success
/// @note Tested
DECLSPEC int SetVideoMode (int width, int height, int bpp, SDL_bool bFullscreen)
{
	////////////////////////////////////////////////////////////////////////////////////
	// We first attempt to set an OpenGL video mode, either windowed or full-screen. If
	// we succeed, we assign the window title.
	////////////////////////////////////////////////////////////////////////////////////
	Uint32 flags = SDL_OPENGL | (bFullscreen ? SDL_FULLSCREEN : 0);

	if (SDL_SetVideoMode(width, height, bpp, flags) == 0)
	{
		std::cerr << "Unable to set video mode: " << SDL_GetError() << std::endl;

		return 0;
	}

	SDL_WM_SetCaption("UI Editor Version 1.0", "");

	///////////////////////////////////////////////////////////////////////////////
	// We record the resolution. We then assign OpenGL's viewport, and use the new
	// dimensions to set an orthographic projection.
	///////////////////////////////////////////////////////////////////////////////
	g_Core.mResW = width;
	g_Core.mResH = height;

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0.0, double(width), 0.0, double(height), +1.0, -1.0);

	return 1;
}

/// @brief Gets the video dimensions
/// @param width [out] On success, the video width
/// @param height [out] On success, the video height
/// @return 0 on failure, non-0 for success
/// @note Tested
DECLSPEC int GetVideoSize (Uint32 * width, Uint32 * height)
{
	assert(width != 0);
	assert(height != 0);

	///////////////////////////////////////////////////////
	// For the mode, we need only set the assigned values.
	///////////////////////////////////////////////////////
	*width = g_Core.mResW;
	*height = g_Core.mResH;

	return 1;
}

/// @brief Prepares a render frame used by the editor
/// @return 0 on failure, non-0 for success
/// @note Tested
DECLSPEC int PrepareFrame (void)
{
	/////////////////////////////////////////////////////////////////////
	// All the editor requires is that we clear out what has been drawn.
	/////////////////////////////////////////////////////////////////////
	glClear(GL_COLOR_BUFFER_BIT);

	return 1;
}

/// @brief Performs the rendering for the editor
/// @return 0 on failure, non-0 for success
/// @note Tested
DECLSPEC int DrawFrame (void)
{
	/////////////////////////////////////////////////////////////////////
	// In order to render, we need only swap the back and front buffers.
	/////////////////////////////////////////////////////////////////////
	SDL_GL_SwapBuffers();

	return 1;
}

/// @brief Reloads graphical data for a given image
/// @param name Name of file containing graphical data
/// @return 0 on failure, non-0 for success
/// @note Tested
DECLSPEC int ReloadImage (char const * name)
{
	assert(name != 0);

	///////////////////////////////////////////////////////////////////////////////////
	// We first find the record for the image loaded (or at least configured) for this
	// file's data. If we cannot find a valid record, we fail.
	///////////////////////////////////////////////////////////////////////////////////
	std::map<std::string, Image *>::iterator iter = g_Core.mImages.find(name);

	if (iter == g_Core.mImages.end() || 0 == iter->second->mTexture) return 0;

	//////////////////////////////////////////////////////////
	// We attempt to load the image data, given the filename.
	//////////////////////////////////////////////////////////
	SDL_Surface * pImage = IMG_Load(name);

	if (0 == pImage) return 0;

	/////////////////////////////////////////////////////////////////////////////////////
	// We will be using OpenGL in RGBA mode. Thus, we need power-of-2, RGBA textures. We
	// convert our image to the nearest fit, if it does not comply, and free the old,
	// intermediate SDL surface.
	/////////////////////////////////////////////////////////////////////////////////////
	int w;	for (w = 1; w < pImage->w; w += w);
	int h;	for (h = 1; h < pImage->h; h += h);

	SDL_Surface * pSafe = pImage;

	if (w != pImage->w || h != pImage->h || pImage->format->BytesPerPixel != 4)
	{
		pSafe = SDL_CreateRGBSurface(0, w, h, 32, c_Rmask, c_Gmask, c_Bmask, c_Amask);

		SDL_BlitSurface(pImage, 0, pSafe, 0);

		SDL_FreeSurface(pImage);
	}

	///////////////////////////////////////////////////////////////////////////////////
	// Finally, we reload the image data into the texture, and set some properties. We
	// then free our temporary SDL surface.
	///////////////////////////////////////////////////////////////////////////////////
	glBindTexture(GL_TEXTURE_2D, iter->second->mTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pSafe->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	SDL_FreeSurface(pSafe);

	return 1;
}

/// @brief Instantiates a picture object
/// @param name Name of file used to load picture's image data
/// @param fS0 Initial texture s-coordinate
/// @param fT0 Initial texture t-coordinate
/// @param fS1 Terminal texture s-coordinate
/// @param fT1 Terminal texture t-coordinate
/// @param picture [out] On success, handle to a picture object
/// @return 0 on failure, non-0 for success
/// @note Tested
DECLSPEC int LoadPicture (char const * name, float fS0, float fT0, float fS1, float fT1, Picture_h * picture)
{
	assert(name != 0);
	assert(picture != 0);

	//////////////////////////////////////////////////////////////////////////////////////
	// We look for the image associated with the file name. If we cannot find it, we make
	// a new image, and load it into the image map. We then attempt to load data into it.
	// If this fails, we pluck the image out of the map, destroy it, and fail. Otherwise,
	// we get the image's iterator, and proceed to the next step.
	//////////////////////////////////////////////////////////////////////////////////////
	std::map<std::string, Image *>::iterator iter = g_Core.mImages.find(name);

	if (iter == g_Core.mImages.end())
	{
		Image * image = new Image();

		g_Core.mImages[name] = image;

		if (ReloadImage(name) == 0)
		{
			g_Core.mImages.erase(name);

			delete image;

			return 0;
		}

		iter = g_Core.mImages.find(name);
	}

	///////////////////////////////////////////////////////////////////////////////////
	// We now create a new picture bound to the image, assign its texture coordinates,
	// and add it to the core's picture list. We then give the user its handle.
	///////////////////////////////////////////////////////////////////////////////////
	Picture * Pic = new Picture(iter->second);

    Pic->mS0 = fS0;
	Pic->mT0 = fT0;
	Pic->mS1 = fS1;
	Pic->mT1 = fT1;

	g_Core.mPictures.push_back(Pic);

	*picture = Pic;

	return 1;
}

/// @brief Renders a picture
/// @param picture Handle to the picture object
/// @param fX Screen x coordinate, in [0,1]
/// @param fY Screen y coordinate, in [0,1]
/// @param fW Screen width, in [0,1]
/// @param fH Screen height, in [0,1]
/// @return 0 on failure, non-0 for success
/// @note Tested
DECLSPEC int DrawPicture (Picture_h picture, float fX, float fY, float fW, float fH)
{
	assert(picture != 0);

	////////////////////////////////////////////////////////////////////////////////////
	// We transform the provided coordinates and dimensions into a form OpenGL expects.
	// We then scale them to the current resolution.
	////////////////////////////////////////////////////////////////////////////////////
	float fSX = fX;
	float fEX = fX + fW;
	float fSY = 1.0f - fY - fH;
	float fEY = 1.0f - fY;

	fSX *= g_Core.mResW;
	fEX *= g_Core.mResW;
	fSY *= g_Core.mResH;
	fEY *= g_Core.mResH;

	////////////////////////////////////////////////////////////////////////////////////
	// We convert the handle to a usable form. We set OpenGL up to render the picture's
	// image texture, and draw a quad with the requested properties, using the texture
	// data assigned to the picture.
	////////////////////////////////////////////////////////////////////////////////////
	Picture * Pic = static_cast<Picture*>(picture);

	assert(Pic->mImage != 0);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Pic->mImage->mTexture);

	glBegin(GL_QUADS);
		glTexCoord2f(Pic->mS0, Pic->mT1);	glVertex2f(fSX, fSY);
		glTexCoord2f(Pic->mS1, Pic->mT1);	glVertex2f(fEX, fSY);
		glTexCoord2f(Pic->mS1, Pic->mT0);	glVertex2f(fEX, fEY);
		glTexCoord2f(Pic->mS0, Pic->mT0);	glVertex2f(fSX, fEY);
	glEnd();

	return 1;
}

/// @brief Unloads a picture object from the renderer
/// @param picture Handle to the picture object
/// @return 0 on failure, non-0 for success
/// @note Tested
DECLSPEC int UnloadPicture (Picture_h picture)
{
	assert(picture != 0);

	////////////////////////////////////////////////////////////////////////////////////
	// We convert the handle to a usable form. We then invoke the picture's destructor,
	// which will manage the image to which it is bound, and remove it from the picture
	// list.
	////////////////////////////////////////////////////////////////////////////////////
	Picture * Pic = static_cast<Picture*>(picture);

	delete Pic;

	g_Core.mPictures.remove(Pic);

	return 1;
}

/// @brief Instantiates a font object
/// @param name Name of file used to load font data
/// @param size Size in which to load font
/// @param font [out] On success, handle to a font object
/// @return 0 on failure, non-0 for success
/// @note Tested
DECLSPEC int LoadFont (char const * name, int size, Font_h * font)
{
	assert(name != 0);
	assert(font != 0);

	if (size <= 0) return 0;

	////////////////////////////////////////////////////////////////////////////////////
	// We first build a key for the font--most of the key consists of the filename; the
	// remainder is built up from the bytes in the size argument.
	////////////////////////////////////////////////////////////////////////////////////
	std::string key(name);

	for (size_t numBytes = sizeof(int); numBytes != 0; --numBytes)
	{
		size_t shift = (sizeof(int) - numBytes) * 8;

		key += static_cast<char>(size >> shift);
	}

	////////////////////////////////////////////////////////////////////////////////////
	// Fonts can be expensive, so we first check whether the font is already loaded. If 
	// so, we give its handle back to the user and return.
	////////////////////////////////////////////////////////////////////////////////////
	std::map<std::string, TTF_Font*>::iterator iter = g_Core.mFonts.find(key);

	if (iter == g_Core.mFonts.end())
	{
		/////////////////////////////////////////////////////////
		// We attempt to load the font data, given the filename.
		/////////////////////////////////////////////////////////
		TTF_Font * pFont = TTF_OpenFont(name, size);

		if (0 == pFont) return 0;

		////////////////////////////////////////////////////////////////////////////////
		// We now load the font into the core's map, and return its handle to the user.
		////////////////////////////////////////////////////////////////////////////////
		g_Core.mFonts[key] = pFont;

		*font = pFont;
	}

	else
	{
		*font = iter->second;
	}

	return 1;
}

/// @brief Unloads a font object from the renderer
/// @param font Handle to a font object
/// @return 0 on failure, non-0 for success
/// @note Tested
DECLSPEC int UnloadFont (Font_h font)
{
	assert(font != 0);

	/////////////////////////////////////////////////////////////////////////////////////
	// We now remove the font from the graphics core. For our needs, there should not be
	// any issue with huge maps, so we just iteratively find our font and pluck it out.
	/////////////////////////////////////////////////////////////////////////////////////
	for (std::map<std::string, TTF_Font*>::iterator iter = g_Core.mFonts.begin(); iter != g_Core.mFonts.end(); ++iter)
	{
		if (iter->second != static_cast<TTF_Font*>(font)) continue;
		
		g_Core.mFonts.erase(iter);

		return 1;
	}

	return 0;
}

/// @brief Gets the dimensions of a text string constructed from a given font object
/// @param font Handle to a font object
/// @param text Text string whose size is being determined
/// @param width [out] On success, the string's width
/// @param height [out] On success, the string's height
/// @return 0 on failure, non-0 for success
/// @note Tested
DECLSPEC int GetTextSize (Font_h font, char const * text, int * width, int * height)
{
	assert(font != 0);
	assert(text != 0);
	assert(width != 0);
	assert(height != 0);

	/////////////////////////////////////////////////////
	// We need only request the dimensions from SDL_ttf.
	/////////////////////////////////////////////////////
	TTF_SizeText(static_cast<TTF_Font*>(font), text, width, height);

	return 1;
}

/// @brief Generates a renderable text image from a font
/// @param font Handle to a font object, used to generate the text image
/// @param text The text to render in the text image
/// @param color The color of the rendered text image
/// @param textImage [out] On success, handle to a text image object
/// @return 0 on failure, non-0 for success
/// @note Tested
DECLSPEC int LoadTextImage (Font_h font, char const * text, SDL_Color color, TextImage_h * textImage)
{
	assert(font != 0);
	assert(text != 0);
	assert(textImage != 0);

	/////////////////////////////////////////////////////////////////////////////////////
	// We convert the handle to a usable form. We then render the text, with the desired
	// color, to an image, and set the image's alpha value.
	/////////////////////////////////////////////////////////////////////////////////////
	TTF_Font * Font = static_cast<TTF_Font*>(font);

	SDL_Surface * pText = TTF_RenderText_Blended(Font, text, color);

	SDL_SetAlpha(pText, 0, 0);

	/////////////////////////////////////////////////////////////////////////////////////
	// We will be using OpenGL in RGBA mode. Thus, we need power-of-2, RGBA textures. In
	// addition, we want properly alpha-blended text images. Thus, we convert our image
	// to the nearest fit and free the intermediate SDL surface.
	/////////////////////////////////////////////////////////////////////////////////////
	int w;	for (w = 1; w < pText->w; w += w);
	int h;	for (h = 1; h < pText->h; h += h);

	SDL_Surface * pImage = SDL_CreateRGBSurface(0, w, h, 32, c_Rmask, c_Gmask, c_Bmask, c_Amask);

	SDL_BlitSurface(pText, 0, pImage, 0);

	SDL_FreeSurface(pText);

	////////////////////////////////////////////////////////////////////////////////////
	// We now load the image data into a text texture, and set some properties. We then
	// free our temporary SDL surface.
	////////////////////////////////////////////////////////////////////////////////////
	GLuint text;	glGenTextures(1, &text);

	glBindTexture(GL_TEXTURE_2D, text);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pImage->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	SDL_FreeSurface(pImage);

	////////////////////////////////////////////////////////////////////////////////
	// We now create a new text image with the generated texture, and add it to the
	// core's text image list. We then give the user its handle.
	////////////////////////////////////////////////////////////////////////////////
	TextImage * Text = new TextImage(text);

	g_Core.mTextImages.push_back(Text);

	*textImage = Text;

	return 1;
}

/// @brief Renders a text image
/// @param textImage Handle to a text image object
/// @param fX Screen x coordinate, in [0,1]
/// @param fY Screen y coordinate, in [0,1]
/// @param fW Screen width, in [0,1]
/// @param fH Screen height, in [0,1]
/// @return 0 on failure, non-0 for success
/// @note Tested
DECLSPEC int DrawTextImage (TextImage_h textImage, float fX, float fY, float fW, float fH)
{
	assert(textImage != 0);

	////////////////////////////////////////////////////////////////////////////////////
	// We transform the provided coordinates and dimensions into a form OpenGL expects.
	// We then scale them to the current resolution.
	////////////////////////////////////////////////////////////////////////////////////
	float fSX = fX;
	float fEX = fX + fW;
	float fSY = 1.0f - fY - fH;
	float fEY = 1.0f - fY;

	fSX *= g_Core.mResW;
	fEX *= g_Core.mResW;
	fSY *= g_Core.mResH;
	fEY *= g_Core.mResH;

	///////////////////////////////////////////////////////////////////////////////
	// We convert the handle to a usable form. We set OpenGL up to render the text
	// image's texture, and draw a quad with the requested properties.
	///////////////////////////////////////////////////////////////////////////////
	TextImage * Text = static_cast<TextImage*>(textImage);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Text->mTexture);

	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f);	glVertex2f(fSX, fSY);
		glTexCoord2f(1.0f, 1.0f);	glVertex2f(fEX, fSY);
		glTexCoord2f(1.0f, 0.0f);	glVertex2f(fEX, fEY);
		glTexCoord2f(0.0f, 0.0f);	glVertex2f(fSX, fEY);
	glEnd();

	return 1;
}

/// @brief Renders a text image, clipped to maximal dimensions
/// @param textImage Handle to a text image object
/// @param fX Screen x coordinate, in [0,1]
/// @param fY Screen y coordinate, in [0,1]
/// @param fW Screen width, in [0,1]
/// @param fH Screen height, in [0,1]
/// @param fMW Maximal screen width, in [0, 1]
/// @param fMH Maximal screen height, in [0, 1]
/// @return 0 on failure, non-0 for success
/// @note Tested
DECLSPEC int DrawClippedTextImage (TextImage_h textImage, float fX, float fY, float fW, float fH, float fMW, float fMH)
{
	assert(textImage != 0);

	////////////////////////////////////////////////////////////////////
	// We first find the minimum of the desired and maximum dimensions.
	////////////////////////////////////////////////////////////////////
	float fMinW = fMW < fW ? fMW : fW;
	float fMinH = fMH < fH ? fMH : fH;

	////////////////////////////////////////////////////////////////////////////////////
	// We transform the provided coordinates and dimensions into a form OpenGL expects.
	// We then scale them to the current resolution.
	////////////////////////////////////////////////////////////////////////////////////
	float fSX = fX;
	float fEX = fX + fMinW;
	float fSY = 1.0f - fY - fMinH;
	float fEY = 1.0f - fY;

	fSX *= g_Core.mResW;
	fEX *= g_Core.mResW;
	fSY *= g_Core.mResH;
	fEY *= g_Core.mResH;

	///////////////////////////////////////////////////////////
	// If clipping, we need to adjust our texture coordinates.
	///////////////////////////////////////////////////////////
	float fW1 = fMinW / fW;
	float fH1 = fMinH / fH;

	///////////////////////////////////////////////////////////////////////////////
	// We convert the handle to a usable form. We set OpenGL up to render the text
	// image's texture, and draw a quad with the requested properties.
	///////////////////////////////////////////////////////////////////////////////
	TextImage * Text = static_cast<TextImage*>(textImage);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Text->mTexture);

	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, fH1);	glVertex2f(fSX, fSY);
		glTexCoord2f(fW1, 1.0f);	glVertex2f(fEX, fSY);
		glTexCoord2f(fW1, 0.0f);	glVertex2f(fEX, fEY);
		glTexCoord2f(0.0f, 0.0f);	glVertex2f(fSX, fEY);
	glEnd();

	return 1;
}

/// @brief Unloads a text image object from the renderer
/// @param textImage Handle to a text image object
/// @return 0 on failure, non-0 for success
/// @note Tested
DECLSPEC int UnloadTextImage (TextImage_h textImage)
{
	assert(textImage != 0);

	///////////////////////////////////////////////////////////////////////////
	// We convert the handle to a usable form. We then invoke the text image's
	// destructor, and remove it from the text image list.
	///////////////////////////////////////////////////////////////////////////
	TextImage * Text = static_cast<TextImage*>(textImage);

	delete Text;

	g_Core.mTextImages.remove(Text);

	return 1;
}

/// @brief Renders a square, unfilled box in the given color
/// @param fX Screen x coordinate, in [0,1]
/// @param fY Screen y coordinate, in [0,1]
/// @param fW Screen width, in [0,1]
/// @param fH Screen height, in [0,1]
/// @param fR Red value, in [0,1]
/// @param fG Green value, in [0,1]
/// @param fB Blue value, in [0,1]
/// @return 0 on failure, non-0 for success
/// @note Tested
DECLSPEC int DrawBox (float fX, float fY, float fW, float fH, float fR, float fG, float fB)
{
	////////////////////////////////////////////////////////////////////////////////////
	// We transform the provided coordinates and dimensions into a form OpenGL expects.
	// We then scale them to the current resolution.
	////////////////////////////////////////////////////////////////////////////////////
	float fSX = fX;
	float fEX = fX + fW;
	float fSY = 1.0f - fY - fH;
	float fEY = 1.0f - fY;

	fSX *= g_Core.mResW;
	fEX *= g_Core.mResW;
	fSY *= g_Core.mResH;
	fEY *= g_Core.mResH;

	/////////////////////////////////////////////////////////////////////////////////////
	// We turn off texturing, if it is enabled, and switch to the desired color. We then 
	// draw an unfilled box, and restore the original color.
	/////////////////////////////////////////////////////////////////////////////////////
	glDisable(GL_TEXTURE_2D);
	
	GLfloat color[4];	glGetFloatv(GL_CURRENT_COLOR, color);
	glColor3f(fR, fG, fB);

	glBegin(GL_LINE_LOOP);
		glVertex2f(fSX, fSY);
		glVertex2f(fEX, fSY);
		glVertex2f(fEX, fEY);
		glVertex2f(fSX, fEY);
	glEnd();

	glColor4fv(color);

	return 1;
}

/// @brief Renders a line in the given color
/// @param fSX Screen start x coordinate, in [0,1]
/// @param fSY Screen start y coordinate, in [0,1]
/// @param fEX Screen end x coordinate, in [0,1]
/// @param fEY Screen end y coordinate, in [0,1]
/// @param fR Red value, in [0,1]
/// @param fG Green value, in [0,1]
/// @param fB Blue value, in [0,1]
/// @return 0 on failure, non-0 for success
/// @note Tested
extern DECLSPEC int DrawLine (float fSX, float fSY, float fEX, float fEY, float fR, float fG, float fB)
{
	////////////////////////////////////////////////////////////////////////////////////
	// We transform the provided coordinates into a form OpenGL expects. We then scale 
	// them to the current resolution.
	////////////////////////////////////////////////////////////////////////////////////
	fSX *= g_Core.mResW;
	fEX *= g_Core.mResW;
	fSY = g_Core.mResH * (1.0f - fSY);
	fEY = g_Core.mResH * (1.0f - fEY);

	/////////////////////////////////////////////////////////////////////////////////////
	// We turn off texturing, if it is enabled, and switch to the desired color. We then 
	// draw a line, and restore the original color.
	/////////////////////////////////////////////////////////////////////////////////////
	glDisable(GL_TEXTURE_2D);
	
	GLfloat color[4];	glGetFloatv(GL_CURRENT_COLOR, color);
	glColor3f(fR, fG, fB);

	glBegin(GL_LINES);
		glVertex2f(fSX, fSY);
		glVertex2f(fEX, fEY);
	glEnd();

	glColor4fv(color);

	return 1;
}

/// @brief Renders a square, unfilled grid in the current color
/// @param fX Screen x coordinate, in [0,1]
/// @param fY Screen y coordinate, in [0,1]
/// @param fW Screen width, in [0,1]
/// @param fH Screen height, in [0,1]
/// @param xCuts Number of horizontal partitions
/// @param yCuts Number of vertical partitions
/// @return 0 on failure, non-0 for success
/// @note Tested
DECLSPEC int DrawGrid (float fX, float fY, float fW, float fH, Uint32 xCuts, Uint32 yCuts)
{
	////////////////////////////////////////////////////////////////////////////////////
	// We transform the provided coordinates and dimensions into a form OpenGL expects.
	// We then scale them to the current resolution.
	////////////////////////////////////////////////////////////////////////////////////
	float fSX = fX;
	float fEX = fX + fW;
	float fSY = 1.0f - fY - fH;
	float fEY = 1.0f - fY;

	fSX *= g_Core.mResW;
	fEX *= g_Core.mResW;
	fSY *= g_Core.mResH;
	fEY *= g_Core.mResH;

	//////////////////////////////////////////////////////////////////////////
	// We turn off texturing, if it is enabled. We then draw an unfilled box.
	//////////////////////////////////////////////////////////////////////////
	glDisable(GL_TEXTURE_2D);

	glBegin(GL_LINE_LOOP);
		glVertex2f(fSX, fSY);
		glVertex2f(fEX, fSY);
		glVertex2f(fEX, fEY);
		glVertex2f(fSX, fEY);
	glEnd();

	///////////////////////////////////////////////////////
	// Finally, we draw the horizontal and vertical lines.
	///////////////////////////////////////////////////////
	glBegin(GL_LINES);
		float fDW = (fEX - fSX) / (xCuts + 1);

		for (fX = fSX + fDW; xCuts-- != 0; fX += fDW)
		{
			glVertex2f(fX, fSY);
			glVertex2f(fX, fEY);
		}

		float fDH = (fEY - fSY) / (yCuts + 1);

		for (fY = fSY + fDH; yCuts-- != 0; fY += fDH)
		{
			glVertex2f(fSX, fY);
			glVertex2f(fEX, fY);
		}
	glEnd();

	return 1;
}
