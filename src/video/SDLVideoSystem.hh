// $Id$

#ifndef __SDLVIDEOSYSTEM_HH__
#define __SDLVIDEOSYSTEM_HH__

#include "VideoSystem.hh"
#include "RendererFactory.hh"

struct SDL_Surface;


namespace openmsx {

class VDP;
class Rasterizer;

class SDLVideoSystem: public VideoSystem
{
public:
	SDLVideoSystem(RendererFactory::RendererID id);
	virtual ~SDLVideoSystem();
	Rasterizer* createRasterizer(VDP* vdp, RendererFactory::RendererID id);

	// VideoSystem interface:
	virtual bool checkSettings();
	virtual bool prepare();
	virtual void flush();
	virtual void takeScreenShot(const string& filename);

private:
	SDL_Surface* screen;
};

} // namespace openmsx

#endif // __SDLVIDEOSYSTEM_HH__
