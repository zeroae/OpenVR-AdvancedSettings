#include "overlaycontroller.h"
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQmlEngine>
#include <QQmlComponent>
#include <QSettings>
#include <iostream>
#include "logging.h"

const char* logConfigFileName = "logging.conf";

const char* logConfigDefault =
"* GLOBAL:\n"
"	FORMAT = \"[%level] %datetime{%Y-%M-%d %H:%m:%s}: %msg\"\n"
"	FILENAME = \"AdvancedSettings.log\"\n"
"	ENABLED = true\n"
"	TO_FILE = true\n"
"	TO_STANDARD_OUTPUT = true\n"
"	MAX_LOG_FILE_SIZE = 2097152 ## 2MB\n"
"* TRACE:\n"
"	ENABLED = false\n"
"* DEBUG:\n"
"	ENABLED = false\n";

INITIALIZE_EASYLOGGINGPP

void myQtMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
	QByteArray localMsg = msg.toLocal8Bit();
	switch (type) {
		case QtDebugMsg:
			LOG(DEBUG) << localMsg.constData() << " (" << context.file << ":" << context.line << ")";
			break;
		case QtInfoMsg:
			LOG(INFO) << localMsg.constData() << " (" << context.file << ":" << context.line << ")";
			break;
		case QtWarningMsg:
			LOG(WARNING) << localMsg.constData() << " (" << context.file << ":" << context.line << ")";
			break;
		case QtCriticalMsg:
			LOG(ERROR) << localMsg.constData() << " (" << context.file << ":" << context.line << ")";
			break;
		case QtFatalMsg:
			LOG(FATAL) << localMsg.constData() << " (" << context.file << ":" << context.line << ")";
			break;
	}
}


int main(int argc, char *argv[]) {

	// Configure logger
	START_EASYLOGGINGPP(argc, argv);
	el::Loggers::addFlag(el::LoggingFlag::DisableApplicationAbortOnFatalLog);
	auto logconfigfile = QFileInfo(logConfigFileName).absoluteFilePath();
	if (QFile::exists(logconfigfile)) {
		el::Configurations conf(logconfigfile.toStdString());
		el::Loggers::reconfigureAllLoggers(conf);
		LOG(INFO) << "Log Config: " << QDir::toNativeSeparators(logconfigfile).toStdString();
	} else {
		el::Configurations conf;
		conf.parseFromText(logConfigDefault);
		el::Loggers::reconfigureAllLoggers(conf);
	}
	
	bool desktopMode = false;
	bool noSound = false;
	bool noManifest = false;

	// Parse command line arguments
	for (int i = 1; i < argc; i++) {
		if (std::string(argv[i]).compare("-desktop") == 0) {
			LOG(INFO) << "Desktop mode enabled.";
			desktopMode = true;
		} else if (std::string(argv[i]).compare("-nosound") == 0) {
			LOG(INFO) << "Sound effects disabled.";
			noSound = true;
		} else if (std::string(argv[i]).compare("-nomanifest") == 0) {
			LOG(INFO) << "vrmanifest disabled.";
			noManifest = true;
		}
	}

	LOG(INFO) << "Starting Application.";
	try {
		QApplication a(argc, argv);
		qInstallMessageHandler(myQtMessageHandler);

		QSettings appSettings(QSettings::IniFormat, QSettings::UserScope, "matzman666", "OpenVRAdvancedSettings");
		advsettings::OverlayController::setAppSettings(&appSettings);
		LOG(INFO) << "Settings File: " << appSettings.fileName().toStdString();

		QQmlEngine qmlEngine;

		advsettings::OverlayController* controller = advsettings::OverlayController::createInstance(desktopMode, noSound);
		controller->Init(&qmlEngine);

		QQmlComponent component(&qmlEngine, QUrl::fromLocalFile("res/qml/mainwidget.qml"));
		auto errors = component.errors();
		for (auto& e : errors) {
			LOG(ERROR) << "QML Error: " << e.toString().toStdString() << std::endl;
		}
		auto quickObj = component.create();
		controller->SetWidget(qobject_cast<QQuickItem*>(quickObj), advsettings::OverlayController::applicationName, advsettings::OverlayController::applicationKey);

		if (!desktopMode && !noManifest) {
			auto manifestQPath = QDir(QApplication::applicationDirPath()).absoluteFilePath("manifest.vrmanifest");
			//std::string manifestPath = QDir::toNativeSeparators(QApplication::applicationDirPath()).toStdString() + "\\manifest.vrmanifest";
			if (QFile::exists(manifestQPath)) {
				bool firstTime = false;
				if (!vr::VRApplications()->IsApplicationInstalled(advsettings::OverlayController::applicationKey)) {
					firstTime;
				}
				auto apperror = vr::VRApplications()->AddApplicationManifest(QDir::toNativeSeparators(manifestQPath).toStdString().c_str());
				if (apperror != vr::VRApplicationError_None) {
					LOG(ERROR) << "Could not add application manifest: " << vr::VRApplications()->GetApplicationsErrorNameFromEnum(apperror);
				} else if (firstTime) {
					auto apperror = vr::VRApplications()->SetApplicationAutoLaunch(advsettings::OverlayController::applicationKey, true);
					if (apperror != vr::VRApplicationError_None) {
						LOG(ERROR) << "Could not set auto start: " << vr::VRApplications()->GetApplicationsErrorNameFromEnum(apperror);
					}
				}
			} else {
				LOG(ERROR) << "Could not find application manifest: " << manifestQPath;
			}
		}

		if (desktopMode) {
			auto m_pWindow = new QQuickWindow();
			qobject_cast<QQuickItem*>(quickObj)->setParentItem(m_pWindow->contentItem());
			m_pWindow->setGeometry(0, 0, qobject_cast<QQuickItem*>(quickObj)->width(), qobject_cast<QQuickItem*>(quickObj)->height());
			m_pWindow->show();
		}

		return a.exec();

	} catch (const std::exception& e) {
		LOG(FATAL) << e.what();
		return -1;
	}
	return 0;
}
