#include <fse/Application.hpp>

#include <QtCore/QCommandLineParser>
#include <QtGui/QIcon>
#include <QtQml/QQmlApplicationEngine>

#include <fsd/data/Link.hpp>
#include <fsd/data/Model.hpp>
#include <fsd/data/Object.hpp>
#include <fsd/data/Place.hpp>
#include <fsd/data/Project.hpp>

#include <fse/managers/CommandsManager.hpp>
#include <fse/managers/ErrorsManager.hpp>
#include <fse/managers/FileManager.hpp>
#include <fse/managers/ModelsManager.hpp>
#include <fse/managers/PreviewManager.hpp>
#include <fse/managers/SelectionManager.hpp>
#include <fse/managers/StylesManager.hpp>
#include <fse/managers/TranslationsManager.hpp>
#include <fse/models/ProxyModel.hpp>
#include <fse/models/SelectionWrapper.hpp>
#include <fse/Manager.hpp>

#include "Config.hpp"

// Q_INIT_RESOURCE must be called outside a namespace
void initResources() {
	Q_INIT_RESOURCE(resources);
}

namespace fse {

struct Application::Impl {
	fse::Manager* manager{ nullptr };
	QQmlApplicationEngine* engine{ nullptr };
};

Application::Application(int& argc, char** argv)
	: QGuiApplication(argc, argv)
	, _impl{ std::make_unique<Impl>() } {}

Application::~Application() {
	// Delete the engine before QGuiApplication to avoid issue with QSGRenderThread
	delete _impl->engine;
	delete _impl->manager;
}

void Application::init() {
	::initResources();
	initApp();

	_impl->manager = new fse::Manager(this);
	_impl->manager->init();

	if (!initParser()) {
		return;
	}

	_impl->engine = new QQmlApplicationEngine(this);

	initRegister();

	// Translations
	QObject::connect(_impl->manager->translationsManager(), &fse::TranslationsManager::currentUpdated, _impl->engine, &QQmlApplicationEngine::retranslate);

	QObject::connect(
		_impl->engine, &QQmlApplicationEngine::objectCreationFailed, this,
		[]() {
			QCoreApplication::exit(-1);
		},
		Qt::QueuedConnection);
	_impl->engine->loadFromModule("editor", "Main");
}

void Application::initApp() {
	setOrganizationName(fse::Config::organization);
	setApplicationName(fse::Config::name);
	setApplicationVersion(fse::Config::version);
	setWindowIcon(QIcon(":/logo/logo.png"));
}

bool Application::initParser() const {
	QCommandLineParser parser;
	parser.setApplicationDescription(fse::Config::description);
	parser.addHelpOption();
	parser.addVersionOption();

	QCommandLineOption generateStyleOption({ "s", "generate-style" }, "Generate an empty style json file");
	parser.addOption(generateStyleOption);

	// Process the actual command line arguments given by the user
	parser.process(arguments());

	if (parser.isSet(generateStyleOption)) {
		_impl->manager->stylesManager()->createJson();
		return false;
	}

	return true;
}

void Application::initRegister() const {
	// FSData
	qmlRegisterSingletonInstance("editor", 1, 0, "MyProject", _impl->manager->project());

	qmlRegisterUncreatableType<fsd::Entity>("editor", 1, 0, "MyEntity", "Attempt to create an Entity");
	qmlRegisterUncreatableType<fsd::Geometry>("editor", 1, 0, "MyGeometry", "Attempt to create a Geometry");
	qmlRegisterUncreatableType<fsd::Placement>("editor", 1, 0, "MyPlacement", "Attempt to create a Placement");
	qmlRegisterUncreatableType<fsd::Shape>("editor", 1, 0, "MyShape", "Attempt to create a Shape");

	qmlRegisterType<fsd::Link>("editor", 1, 0, "MyLink");
	qmlRegisterType<fsd::Model>("editor", 1, 0, "MyModel");
	qmlRegisterType<fsd::Object>("editor", 1, 0, "MyObject");
	qmlRegisterType<fsd::Place>("editor", 1, 0, "MyPlace");

	qmlRegisterType<fsd::FileManager>("editor", 1, 0, "MyFileManager");

	// FSEditor
	qmlRegisterSingletonInstance("editor", 1, 0, "MyManager", _impl->manager);
	qmlRegisterSingletonInstance("editor", 1, 0, "MyCommands", _impl->manager->commandsManager());
	qmlRegisterSingletonInstance("editor", 1, 0, "MyErrors", _impl->manager->errorsManager());
	qmlRegisterSingletonInstance("editor", 1, 0, "MyFile", _impl->manager->fileManager());
	qmlRegisterSingletonInstance("editor", 1, 0, "MyModels", _impl->manager->modelsManager());
	qmlRegisterSingletonInstance("editor", 1, 0, "MyPreview", _impl->manager->previewManager());
	qmlRegisterSingletonInstance("editor", 1, 0, "MySelection", _impl->manager->selectionManager());
	qmlRegisterSingletonInstance("editor", 1, 0, "MyStyles", _impl->manager->stylesManager());
	qmlRegisterSingletonInstance("editor", 1, 0, "MyTranslations", _impl->manager->translationsManager());
	qmlRegisterType<fse::ProxyModel>("editor", 1, 0, "MyProxyModel");
	qmlRegisterType<fse::SelectionWrapper>("editor", 1, 0, "MySelectionWrapper");
}

} // namespace fse
