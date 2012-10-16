#ifndef UI_EDIT_EXT_GRAPHICS_IMP_H
#define UI_EDIT_EXT_GRAPHICS_IMP_H

#include <SDL/SDL_error.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_opengl.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_types.h>
#include <SDL/SDL_video.h>
#include <functional>
#include <list>
#include <map>
#include <string>

namespace UI_Edit_Ext
{
	/// Internal image representation
	struct Image {
	// Members
		GLuint mTexture;///< Texture used by image
		Uint32 mCount;	///< Reference count for image sprites
	// Methods
		Image (void);
		~Image (void);
	};

	/// Internal picture representation
	struct Picture {
	// Members
		Image * mImage;	///< Image used by picture
		GLfloat mS0;///< Initial s-coordinate
		GLfloat mS1;///< Terminal s-coordinate
		GLfloat mT0;///< Initial t-coordinate
		GLfloat mT1;///< Terminal t-coordinate
	// Methods
		Picture (Image * image);
		~Picture (void);
	};

	/// Internal text image representation
	struct TextImage {
	// Members
		GLuint mTexture;///< Texture used by text image
	// Methods
		TextImage (GLuint texture);
		~TextImage (void);
	};

	/// Rendering core of editor's GL renderer
	struct GraphicsCore {
	// Members
		std::map<std::string, Image*> mImages;	///< Images stored in the core
		std::map<std::string, TTF_Font*> mFonts;///< Fonts stored in the core
		std::list<Picture*> mPictures;	///< Pictures stored in the core
		std::list<TextImage*> mTextImages;	///< Text images stored in the core
		GLsizei mResW;	///< Resolution width
		GLsizei mResH;	///< Resolution height
	// Methods
		GraphicsCore (void);
		~GraphicsCore (void);
	};
};

#endif // UI_EDIT_EXT_GRAPHICS_IMP_H
