
#pragma once

#include <QObject>
#include <openvr.h>

class QQuickWindow;
// application namespace
namespace advsettings {

// forward declaration
class OverlayController;

class FixFloorTabController : public QObject {
	Q_OBJECT
	Q_PROPERTY(bool canUndo READ canUndo WRITE setCanUndo NOTIFY canUndoChanged)

private:
	OverlayController* parent;
	QQuickWindow* widget;

	float controllerUpOffsetCorrection = 0.06f; // Controller touchpad facing upwards
	float controllerDownOffsetCorrection = 0.0f; // Controller touchpad facing downwards (not implemented yet)

	int state = 0; // 0 .. idle, 1 .. measurement in progress
	vr::TrackedDeviceIndex_t referenceController = vr::k_unTrackedDeviceIndexInvalid;
	unsigned measurementCount = 0;
	double tempOffset = 0.0;
	float floorOffset = 0.0f;
	QString statusMessage = "";
	float statusMessageTimeout = 0.0f;
	bool m_canUndo = false;


public:
	void initStage1();
	void initStage2(OverlayController* parent, QQuickWindow* widget);

	void eventLoopTick(vr::TrackedDevicePose_t* devicePoses);

	Q_INVOKABLE QString currentStatusMessage();
	Q_INVOKABLE float currentStatusMessageTimeout();

	bool canUndo() const;

public slots:
	void fixFloorClicked();
	void undoFixFloorClicked();

	void setCanUndo(bool value, bool notify = true);

signals:
	void statusMessageSignal();
	void measureStartSignal();
	void measureEndSignal();
	void canUndoChanged(bool value);
};

} // namespace advsettings
