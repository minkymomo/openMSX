#ifndef ROMINFOTOPIC_HH
#define ROMINFOTOPIC_HH

#include "InfoTopic.hh"

namespace openmsx {

class RomInfoTopic final : public InfoTopic
{
public:
	explicit RomInfoTopic(InfoCommand& openMSXInfoCommand);

	void execute(array_ref<TclObject> tokens,
	             TclObject& result) const override;
	std::string help(const std::vector<std::string>& tokens) const override;
	void tabCompletion(std::vector<std::string>& tokens) const override;
};

} // namespace openmsx

#endif
