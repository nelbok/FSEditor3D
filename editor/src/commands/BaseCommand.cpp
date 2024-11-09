#include <fse/commands/BaseCommand.hpp>

namespace fse {
BaseCommand::BaseCommand(QObject* parent)
	: QObject(parent) {}

void BaseCommand::finalize() {
	// Nothing to do
}

void BaseCommand::clean() {
	// Nothing to do
}

} // namespace fse
