// $Id$

#ifndef __DISPLAY_HH__
#define __DISPLAY_HH__

//#include "VideoSystem.hh"
#include "EventListener.hh"
#include "Command.hh"
#include "openmsx.hh"
#include <memory>
#include <string>
#include <vector>

using std::auto_ptr;
using std::string;
using std::vector;




namespace openmsx {

class VideoSystem;


/** Interface for display layers.
  */
class Layer
{
public:
	virtual ~Layer();

	/** Paint this layer.
	  */
	virtual void paint() = 0;

	/** Returns the name of this layer. Used for debugging.
	  */
	virtual const string& getName() = 0;
};


/** Represents the output window/screen of openMSX.
  * A display contains several layers.
  */
class Display: private EventListener
{
public:
	enum {
		Z_BACKGROUND = 0,
		Z_MSX_PASSIVE = 30,
		Z_MSX_ACTIVE = 40,
		Z_CONSOLE = 100,
	};

	/** Describes how much of the screen is currently covered by a particular
	  * layer.
	  */
	enum Coverage {
		/** Layer fully covers the screen: any underlying layers are invisible.
		  */
		COVER_FULL,
		/** Layer partially covers the screen: it may cover only part of the
		  * screen area, or it may be (semi-)transparent in places.
		  */
		COVER_PARTIAL,
		/** Layer is not visible, that is completely transparent.
		  */
		COVER_NONE,
	};

	// TODO: Keep as singleton?
	static auto_ptr<Display> INSTANCE;

	Display(auto_ptr<VideoSystem> videoSystem);
	virtual ~Display();

	virtual bool signalEvent(const Event& event);

	const auto_ptr<VideoSystem>& getVideoSystem() {
		return videoSystem;
	}

	/** Redraw the display.
	  */
	void repaint();

	// TODO: Add as methods to LayerInfo and expose LayerInfo to outside.
	void addLayer(Layer* layer, int z);
	bool isActive(Layer* layer);
	void setZ(Layer* layer, int z);
	void setCoverage(Layer* layer, Coverage coverage);

private:

	class LayerInfo {
	public:
		LayerInfo(Layer* layer, int z);
		Layer* layer;
		Coverage coverage;
		int z;
	};

	// TODO: Add as methods to LayerInfo and expose LayerInfo to outside.
	vector<LayerInfo*>::iterator findLayer(Layer* layer);

	/** Find frontmost opaque layer.
	  */
	vector<LayerInfo*>::iterator baseLayer();

	vector<LayerInfo*> layers;

	auto_ptr<VideoSystem> videoSystem;

	void addLayer(LayerInfo* info);

	class ScreenShotCmd : public SimpleCommand {
	public:
		ScreenShotCmd(Display& display);
		virtual string execute(const vector<string>& tokens);
		virtual string help(const vector<string>& tokens) const;
	private:
		Display& display;
	} screenShotCmd;

};

} // namespace openmsx

#endif //__DISPLAY_HH__

