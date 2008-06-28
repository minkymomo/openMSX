// $Id$

#ifndef MSXCPU_HH
#define MSXCPU_HH

#include "CPU.hh"
#include "Observer.hh"
#include "EmuTime.hh"
#include "noncopyable.hh"
#include <memory>

namespace openmsx {

class MSXMotherBoard;
class MSXCPUInterface;
class BooleanSetting;
class Z80TYPE;
class R800TYPE;
template <typename T> class CPUCore;
class Setting;
class TimeInfoTopic;
class MSXCPUDebuggable;

class MSXCPU : private Observer<Setting>, private noncopyable
{
public:
	enum CPUType { CPU_Z80, CPU_R800 };

	explicit MSXCPU(MSXMotherBoard& motherboard);
	~MSXCPU();

	/** Reset CPU.
	  * Requires CPU is not in the middle of an instruction,
	  * so exitCPULoop was called and execute() method returned.
	 */
	void doReset(const EmuTime& time);

	/**
	 * Switch between Z80 / R800
	 */
	void setActiveCPU(CPUType cpu);

	/**
	 * Sets DRAM or ROM mode (influences memory access speed for R800)
	 */
	void setDRAMmode(bool dram);

	/**
	 * Inform CPU of bank switch. This will invalidate memory cache and
	 * update memory timings on R800.
	 */
	void updateVisiblePage(byte page, byte primarySlot, byte secondarySlot);

	/**
	 * Invalidate the CPU its cache for the interval [start, start + size)
	 * For example MSXMemoryMapper and MSXGameCartrigde need to call this
	 * method when a 'memory switch' occurs.
	 */
	void invalidateMemCache(word start, unsigned size);

	/**
	 * This method raises a maskable interrupt. A device may call this
	 * method more than once. If the device wants to lower the
	 * interrupt again it must call the lowerIRQ() method exactly as
	 * many times.
	 * Before using this method take a look at IRQHelper.
	 */
	void raiseIRQ();

	/**
	 * This methods lowers the maskable interrupt again. A device may never
	 * call this method more often than it called the method
	 * raiseIRQ().
	 * Before using this method take a look at IRQHelper.
	 */
	void lowerIRQ();

	/**
	 * This method raises a non-maskable interrupt. A device may call this
	 * method more than once. If the device wants to lower the
	 * interrupt again it must call the lowerNMI() method exactly as
	 * many times.
	 * Before using this method take a look at IRQHelper.
	 */
	void raiseNMI();

	/**
	 * This methods lowers the non-maskable interrupt again. A device may never
	 * call this method more often than it called the method
	 * raiseNMI().
	 * Before using this method take a look at IRQHelper.
	 */
	void lowerNMI();

	/** See CPU::exitCPULoopsync() */
	void exitCPULoopSync();
	/** See CPU::exitCPULoopAsync() */
	void exitCPULoopAsync();

	/**
	 * Is the R800 currently active
	 */
	bool isR800Active();

	/**
	 * Switch the Z80 clock freq
	 */
	void setZ80Freq(unsigned freq);

	void setInterface(MSXCPUInterface* interf);

	void disasmCommand(const std::vector<TclObject*>& tokens,
                           TclObject& result) const;

	// Breakpoint stuff
	void doStep();
	void doContinue();
	void doBreak();
	bool isBreaked();
	void insertBreakPoint(std::auto_ptr<BreakPoint> bp);
	void removeBreakPoint(const BreakPoint& bp);
	const CPU::BreakPoints& getBreakPoints() const;

	// Pause
	void setPaused(bool paused);

	void setNextSyncPoint(const EmuTime& time);

	template<typename Archive>
	void serialize(Archive& ar, unsigned version);

private:
	// only for MSXMotherBoard
	void execute();
	friend class MSXMotherBoardImpl;

	void wait(const EmuTime& time);
	void waitCycles(unsigned cycles);
	friend class VDPIODelay;

	/**
	 * The time returned by this method is not safe to use for Scheduler
	 * or IO related stuff (because it can sometimes already be higher then
	 * still to be scheduled sync points). Use Scheduler::getCurrentTime()
	 * instead.
	 * TODO is this comment still true?
	 */
	const EmuTime& getCurrentTime() const;

	// Observer<Setting>
	void update(const Setting& setting);

	MSXMotherBoard& motherboard;
	const std::auto_ptr<BooleanSetting> traceSetting;
	const std::auto_ptr<CPUCore<Z80TYPE> > z80;
	const std::auto_ptr<CPUCore<R800TYPE> > r800;

	CPU* activeCPU;
	CPU* newCPU;
	EmuTime reference;

	friend class TimeInfoTopic;
	friend class MSXCPUDebuggable;
	const std::auto_ptr<TimeInfoTopic> timeInfo;
	const std::auto_ptr<MSXCPUDebuggable> debuggable;
};

} // namespace openmsx

#endif
