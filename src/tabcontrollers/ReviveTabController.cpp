#include "ReviveTabController.h"
#include <QQuickWindow>
#include "../overlaycontroller.h"

// application namespace
namespace advsettings {

	const char* appkey_overlay = "revive.dashboard.overlay";
	const char* section_revive = "revive";
	const char* key_pixelsPerDisplayPixel = "pixelsPerDisplayPixel";
	const char* key_toggleGrip = "ToggleGrip";
	const char* key_thumbDeadzone = "ThumbDeadzone";
	const char* key_thumbSensitivity = "ThumbSensitivity";
	const char* key_touchPitch = "TouchPitch";
	const char* key_touchYaw = "TouchYaw";
	const char* key_touchRoll = "TouchRoll";
	const char* key_touchX = "TouchX";
	const char* key_touchY = "TouchY";
	const char* key_touchZ = "TouchZ";
	const char* key_playerHeight = "PlayerHeight";
	const char* key_eyeHeight = "EyeHeight";
	const char* key_piUser = "User";
	const char* key_piName = "Name";
	const char* key_piGender = "Gender";


	void ReviveTabController::initStage1() {
		m_isOverlayInstalled = vr::VRApplications()->IsApplicationInstalled(appkey_overlay);
		if (m_isOverlayInstalled) {
			vr::EVRSettingsError vrSettingsError;

			float valuef = vr::VRSettings()->GetFloat(section_revive, key_pixelsPerDisplayPixel, &vrSettingsError);
			if (vrSettingsError != vr::VRSettingsError_None) {
				LOG(WARNING) << "Could not read \"revive::" << key_pixelsPerDisplayPixel << "\" setting: " << vr::VRSettings()->GetSettingsErrorNameFromEnum(vrSettingsError);
			} else {
				if (m_pixelsPerDisplayPixelOverride == 0.0) {
					m_pixelsPerDisplayPixelOverrideEnabled = false;
					m_pixelsPerDisplayPixelOverride = 1.0;
				} else {
					m_pixelsPerDisplayPixelOverrideEnabled = true;
					m_pixelsPerDisplayPixelOverride = valuef;
				}
			}

			int valuei = vr::VRSettings()->GetInt32(section_revive, key_toggleGrip, &vrSettingsError);
			if (vrSettingsError != vr::VRSettingsError_None) {
				LOG(WARNING) << "Could not read \"revive::" << key_toggleGrip << "\" setting: " << vr::VRSettings()->GetSettingsErrorNameFromEnum(vrSettingsError);
			} else {
				m_gripButtonMode = valuei;
			}

			valuef = vr::VRSettings()->GetFloat(section_revive, key_thumbDeadzone, &vrSettingsError);
			if (vrSettingsError != vr::VRSettingsError_None) {
				LOG(WARNING) << "Could not read \"revive::" << key_thumbDeadzone << "\" setting: " << vr::VRSettings()->GetSettingsErrorNameFromEnum(vrSettingsError);
			} else {
				m_thumbDeadzone = valuef;
			}

			valuef = vr::VRSettings()->GetFloat(section_revive, key_thumbSensitivity, &vrSettingsError);
			if (vrSettingsError != vr::VRSettingsError_None) {
				LOG(WARNING) << "Could not read \"revive::" << key_thumbSensitivity << "\" setting: " << vr::VRSettings()->GetSettingsErrorNameFromEnum(vrSettingsError);
			} else {
				m_thumbRange = valuef;
			}

			valuef = vr::VRSettings()->GetFloat(section_revive, key_touchPitch, &vrSettingsError);
			if (vrSettingsError != vr::VRSettingsError_None) {
				LOG(WARNING) << "Could not read \"revive::" << key_touchPitch << "\" setting: " << vr::VRSettings()->GetSettingsErrorNameFromEnum(vrSettingsError);
			} else {
				m_touchPitch = valuef;
			}

			valuef = vr::VRSettings()->GetFloat(section_revive, key_touchYaw, &vrSettingsError);
			if (vrSettingsError != vr::VRSettingsError_None) {
				LOG(WARNING) << "Could not read \"revive::" << key_touchYaw << "\" setting: " << vr::VRSettings()->GetSettingsErrorNameFromEnum(vrSettingsError);
			} else {
				m_touchYaw = valuef;
			}

			valuef = vr::VRSettings()->GetFloat(section_revive, key_touchRoll, &vrSettingsError);
			if (vrSettingsError != vr::VRSettingsError_None) {
				LOG(WARNING) << "Could not read \"revive::" << key_touchRoll << "\" setting: " << vr::VRSettings()->GetSettingsErrorNameFromEnum(vrSettingsError);
			} else {
				m_touchRoll = valuef;
			}

			valuef = vr::VRSettings()->GetFloat(section_revive, key_touchX, &vrSettingsError);
			if (vrSettingsError != vr::VRSettingsError_None) {
				LOG(WARNING) << "Could not read \"revive::" << key_touchX << "\" setting: " << vr::VRSettings()->GetSettingsErrorNameFromEnum(vrSettingsError);
			} else {
				m_touchX = valuef;
			}

			valuef = vr::VRSettings()->GetFloat(section_revive, key_touchY, &vrSettingsError);
			if (vrSettingsError != vr::VRSettingsError_None) {
				LOG(WARNING) << "Could not read \"revive::" << key_touchY << "\" setting: " << vr::VRSettings()->GetSettingsErrorNameFromEnum(vrSettingsError);
			} else {
				m_touchY = valuef;
			}

			valuef = vr::VRSettings()->GetFloat(section_revive, key_touchZ, &vrSettingsError);
			if (vrSettingsError != vr::VRSettingsError_None) {
				LOG(WARNING) << "Could not read \"revive::" << key_touchZ << "\" setting: " << vr::VRSettings()->GetSettingsErrorNameFromEnum(vrSettingsError);
			} else {
				m_touchZ = valuef;
			}

			valuef = vr::VRSettings()->GetFloat(section_revive, key_playerHeight, &vrSettingsError);
			if (vrSettingsError != vr::VRSettingsError_None) {
				LOG(WARNING) << "Could not read \"revive::" << key_playerHeight << "\" setting: " << vr::VRSettings()->GetSettingsErrorNameFromEnum(vrSettingsError);
			} else {
				m_piPlayerHeight = valuef;
			}

			valuef = vr::VRSettings()->GetFloat(section_revive, key_eyeHeight, &vrSettingsError);
			if (vrSettingsError != vr::VRSettingsError_None) {
				LOG(WARNING) << "Could not read \"revive::" << key_eyeHeight << "\" setting: " << vr::VRSettings()->GetSettingsErrorNameFromEnum(vrSettingsError);
			} else {
				m_piEyeHeight = valuef;
			}

			char buffer[1024];
			vr::VRSettings()->GetString(section_revive, key_piUser, buffer, 1024, &vrSettingsError);
			if (vrSettingsError != vr::VRSettingsError_None) {
				LOG(WARNING) << "Could not read \"revive::" << key_piUser << "\" setting: " << vr::VRSettings()->GetSettingsErrorNameFromEnum(vrSettingsError);
			} else {
				m_piUsername = buffer;
			}

			vr::VRSettings()->GetString(section_revive, key_piName, buffer, 1024, &vrSettingsError);
			if (vrSettingsError != vr::VRSettingsError_None) {
				LOG(WARNING) << "Could not read \"revive::" << key_piName << "\" setting: " << vr::VRSettings()->GetSettingsErrorNameFromEnum(vrSettingsError);
			} else {
				m_piName = buffer;
			}

			vr::VRSettings()->GetString(section_revive, key_piGender, buffer, 1024, &vrSettingsError);
			if (vrSettingsError != vr::VRSettingsError_None) {
				LOG(WARNING) << "Could not read \"revive::" << key_piGender << "\" setting: " << vr::VRSettings()->GetSettingsErrorNameFromEnum(vrSettingsError);
			} else {
				if (QString(buffer).compare("male", Qt::CaseInsensitive) == 0) {
					m_piGender = 1;
				} else if (QString(buffer).compare("female", Qt::CaseInsensitive) == 0) {
					m_piGender = 2;
				} else {
					m_piGender = 0;
				}
			}
		}
	}

	void ReviveTabController::initStage2(OverlayController * parent, QQuickWindow * widget) {
		this->parent = parent;
		this->widget = widget;
	}

	void ReviveTabController::eventLoopTick() {
		if (m_isOverlayInstalled) {
			if (settingsUpdateCounter >= 50) {
				settingsUpdateCounter = 0;
				vr::EVRSettingsError vrSettingsError;

				float valuef = vr::VRSettings()->GetFloat(section_revive, key_pixelsPerDisplayPixel, &vrSettingsError);
				if (vrSettingsError == vr::VRSettingsError_None) {
					if (valuef == 0.0) {
						setPixelsPerDisplayPixelOverrideEnabled(false);
					} else {
						setPixelsPerDisplayPixelOverride(valuef);
					}
				}

				int valuei = vr::VRSettings()->GetInt32(section_revive, key_toggleGrip, &vrSettingsError);
				if (vrSettingsError == vr::VRSettingsError_None) {
					setGripButtonMode(valuei);
				}

				valuef = vr::VRSettings()->GetFloat(section_revive, key_thumbDeadzone, &vrSettingsError);
				if (vrSettingsError == vr::VRSettingsError_None) {
					setThumbDeadzone(valuef);
				}

				valuef = vr::VRSettings()->GetFloat(section_revive, key_thumbSensitivity, &vrSettingsError);
				if (vrSettingsError == vr::VRSettingsError_None) {
					setThumbRange(valuef);
				}

				valuef = vr::VRSettings()->GetFloat(section_revive, key_touchPitch, &vrSettingsError);
				if (vrSettingsError == vr::VRSettingsError_None) {
					setTouchPitch(valuef);
				}

				valuef = vr::VRSettings()->GetFloat(section_revive, key_touchYaw, &vrSettingsError);
				if (vrSettingsError == vr::VRSettingsError_None) {
					setTouchYaw(valuef);
				}

				valuef = vr::VRSettings()->GetFloat(section_revive, key_touchRoll, &vrSettingsError);
				if (vrSettingsError == vr::VRSettingsError_None) {
					setTouchRoll(valuef);
				}

				valuef = vr::VRSettings()->GetFloat(section_revive, key_touchX, &vrSettingsError);
				if (vrSettingsError == vr::VRSettingsError_None) {
					setTouchX(valuef);
				}

				valuef = vr::VRSettings()->GetFloat(section_revive, key_touchY, &vrSettingsError);
				if (vrSettingsError == vr::VRSettingsError_None) {
					setTouchY(valuef);
				}

				valuef = vr::VRSettings()->GetFloat(section_revive, key_touchZ, &vrSettingsError);
				if (vrSettingsError == vr::VRSettingsError_None) {
					setTouchZ(valuef);
				}

				valuef = vr::VRSettings()->GetFloat(section_revive, key_playerHeight, &vrSettingsError);
				if (vrSettingsError == vr::VRSettingsError_None) {
					setPiPlayerHeight(valuef);
				}

				valuef = vr::VRSettings()->GetFloat(section_revive, key_eyeHeight, &vrSettingsError);
				if (vrSettingsError == vr::VRSettingsError_None) {
					setPiEyeHeight(valuef);
				}

				char buffer[1024];
				vr::VRSettings()->GetString(section_revive, key_piUser, buffer, 1024, &vrSettingsError);
				if (vrSettingsError == vr::VRSettingsError_None) {
					setPiUsername(buffer);
				}

				vr::VRSettings()->GetString(section_revive, key_piName, buffer, 1024, &vrSettingsError);
				if (vrSettingsError == vr::VRSettingsError_None) {
					setPiName(buffer);
				}

				vr::VRSettings()->GetString(section_revive, key_piGender, buffer, 1024, &vrSettingsError);
				if (vrSettingsError == vr::VRSettingsError_None) {
					if (QString(buffer).compare("male", Qt::CaseInsensitive) == 0) {
						valuei = 1;
					} else if (QString(buffer).compare("female", Qt::CaseInsensitive) == 0) {
						valuei = 2;
					} else {
						valuei = 0;
					}
					setPiGender(valuei);
				}
			} else {
				settingsUpdateCounter++;
			}
		}
	}

	bool ReviveTabController::isOverlayInstalled() const {
		return m_isOverlayInstalled;
	}

	int ReviveTabController::gripButtonMode() const {
		return m_gripButtonMode;
	}

	bool ReviveTabController::isPixelsPerDisplayPixelOverrideEnabled() const {
		return m_pixelsPerDisplayPixelOverrideEnabled;
	}

	float ReviveTabController::pixelsPerDisplayPixelOverride() const {
		return m_pixelsPerDisplayPixelOverride;
	}

	float ReviveTabController::thumbDeadzone() const {
		return m_thumbDeadzone;
	}

	float ReviveTabController::thumbRange() const {
		return m_thumbRange;
	}

	float ReviveTabController::touchPitch() const {
		return m_touchPitch;
	}

	float ReviveTabController::touchYaw() const {
		return m_touchYaw;
	}

	float ReviveTabController::touchRoll() const {
		return m_touchRoll;
	}

	float ReviveTabController::touchX() const {
		return m_touchX;
	}

	float ReviveTabController::touchY() const {
		return m_touchY;
	}

	float ReviveTabController::touchZ() const {
		return m_touchZ;
	}

	float ReviveTabController::piPlayerHeight() const {
		return m_piPlayerHeight;
	}

	float ReviveTabController::piEyeHeight() const {
		return m_piEyeHeight;
	}

	const QString& ReviveTabController::piUsername() const {
		return m_piUsername;
	}

	const QString& ReviveTabController::piName() const {
		return m_piName;
	}

	int ReviveTabController::piGender() const {
		return m_piGender;
	}

	void ReviveTabController::setGripButtonMode(int value, bool notify) {
		if (m_gripButtonMode != value) {
			m_gripButtonMode = value;
			vr::EVRSettingsError vrSettingsError;
			vr::VRSettings()->SetInt32(section_revive, key_toggleGrip, m_gripButtonMode, &vrSettingsError);
			if (vrSettingsError != vr::VRSettingsError_None) {
				LOG(WARNING) << "Could not set \"revive::" << key_toggleGrip << "\" setting: " << vr::VRSettings()->GetSettingsErrorNameFromEnum(vrSettingsError);
			}
			vr::VRSettings()->Sync();
			if (notify) {
				emit gripButtonModeChanged(m_gripButtonMode);
			}
		}
	}

	void ReviveTabController::setPixelsPerDisplayPixelOverrideEnabled(bool value, bool notify) {
		if (m_pixelsPerDisplayPixelOverrideEnabled != value) {
			m_pixelsPerDisplayPixelOverrideEnabled = value;
			if (m_pixelsPerDisplayPixelOverrideEnabled) {
				vr::EVRSettingsError vrSettingsError;
				vr::VRSettings()->SetFloat(section_revive, key_pixelsPerDisplayPixel, m_pixelsPerDisplayPixelOverride, &vrSettingsError);
				if (vrSettingsError != vr::VRSettingsError_None) {
					LOG(WARNING) << "Could not set \"revive::" << key_pixelsPerDisplayPixel << "\" setting: " << vr::VRSettings()->GetSettingsErrorNameFromEnum(vrSettingsError);
				}
			} else {
				vr::EVRSettingsError vrSettingsError;
				vr::VRSettings()->RemoveKeyInSection(section_revive, key_pixelsPerDisplayPixel, &vrSettingsError);
				if (vrSettingsError != vr::VRSettingsError_None) {
					LOG(WARNING) << "Could not remove \"revive::" << key_pixelsPerDisplayPixel << "\" setting: " << vr::VRSettings()->GetSettingsErrorNameFromEnum(vrSettingsError);
				}
			}
			vr::VRSettings()->Sync();
			if (notify) {
				emit pixelsPerDisplayPixelOverrideEnabledChanged(m_pixelsPerDisplayPixelOverrideEnabled);
			}
		}
	}

	void ReviveTabController::setPixelsPerDisplayPixelOverride(float value, bool notify) {
		if (m_pixelsPerDisplayPixelOverride != value) {
			m_pixelsPerDisplayPixelOverride = value;
			if (m_pixelsPerDisplayPixelOverrideEnabled) {
				vr::EVRSettingsError vrSettingsError;
				vr::VRSettings()->SetFloat(section_revive, key_pixelsPerDisplayPixel, m_pixelsPerDisplayPixelOverride, &vrSettingsError);
				if (vrSettingsError != vr::VRSettingsError_None) {
					LOG(WARNING) << "Could not set \"revive::" << key_pixelsPerDisplayPixel << "\" setting: " << vr::VRSettings()->GetSettingsErrorNameFromEnum(vrSettingsError);
				}
				vr::VRSettings()->Sync();
			}
			if (notify) {
				emit pixelsPerDisplayPixelOverrideChanged(m_pixelsPerDisplayPixelOverride);
			}
		}
	}

	void ReviveTabController::setThumbDeadzone(float value, bool notify) {
		if (m_thumbDeadzone != value) {
			m_thumbDeadzone = value;
			vr::EVRSettingsError vrSettingsError;
			vr::VRSettings()->SetFloat(section_revive, key_thumbDeadzone, m_thumbDeadzone, &vrSettingsError);
			if (vrSettingsError != vr::VRSettingsError_None) {
				LOG(WARNING) << "Could not set \"revive::" << key_thumbDeadzone << "\" setting: " << vr::VRSettings()->GetSettingsErrorNameFromEnum(vrSettingsError);
			}
			vr::VRSettings()->Sync();
			if (notify) {
				emit thumbDeadzoneChanged(m_thumbDeadzone);
			}
		}
	}

	void ReviveTabController::setThumbRange(float value, bool notify) {
		if (m_thumbRange != value) {
			m_thumbRange = value;
			vr::EVRSettingsError vrSettingsError;
			vr::VRSettings()->SetFloat(section_revive, key_thumbSensitivity, m_thumbRange, &vrSettingsError);
			if (vrSettingsError != vr::VRSettingsError_None) {
				LOG(WARNING) << "Could not set \"revive::" << key_thumbSensitivity << "\" setting: " << vr::VRSettings()->GetSettingsErrorNameFromEnum(vrSettingsError);
			}
			vr::VRSettings()->Sync();
			if (notify) {
				emit thumbRangeChanged(m_thumbRange);
			}
		}
	}

	void ReviveTabController::setTouchPitch(float value, bool notify) {
		if (m_touchPitch != value) {
			m_touchPitch = value;
			vr::EVRSettingsError vrSettingsError;
			vr::VRSettings()->SetFloat(section_revive, key_touchPitch, m_touchPitch, &vrSettingsError);
			if (vrSettingsError != vr::VRSettingsError_None) {
				LOG(WARNING) << "Could not set \"revive::" << key_touchPitch << "\" setting: " << vr::VRSettings()->GetSettingsErrorNameFromEnum(vrSettingsError);
			}
			vr::VRSettings()->Sync();
			if (notify) {
				emit touchPitchChanged(m_touchPitch);
			}
		}
	}

	void ReviveTabController::setTouchYaw(float value, bool notify) {
		if (m_touchYaw != value) {
			m_touchYaw = value;
			vr::EVRSettingsError vrSettingsError;
			vr::VRSettings()->SetFloat(section_revive, key_touchYaw, m_touchYaw, &vrSettingsError);
			if (vrSettingsError != vr::VRSettingsError_None) {
				LOG(WARNING) << "Could not set \"revive::" << key_touchYaw << "\" setting: " << vr::VRSettings()->GetSettingsErrorNameFromEnum(vrSettingsError);
			}
			vr::VRSettings()->Sync();
			if (notify) {
				emit touchYawChanged(m_touchYaw);
			}
		}
	}

	void ReviveTabController::setTouchRoll(float value, bool notify) {
		if (m_touchRoll != value) {
			m_touchRoll = value;
			vr::EVRSettingsError vrSettingsError;
			vr::VRSettings()->SetFloat(section_revive, key_touchRoll, m_touchRoll, &vrSettingsError);
			if (vrSettingsError != vr::VRSettingsError_None) {
				LOG(WARNING) << "Could not set \"revive::" << key_touchRoll << "\" setting: " << vr::VRSettings()->GetSettingsErrorNameFromEnum(vrSettingsError);
			}
			vr::VRSettings()->Sync();
			if (notify) {
				emit touchRollChanged(m_touchRoll);
			}
		}
	}

	void ReviveTabController::setTouchX(float value, bool notify) {
		if (m_touchX != value) {
			m_touchX = value;
			vr::EVRSettingsError vrSettingsError;
			vr::VRSettings()->SetFloat(section_revive, key_touchX, m_touchX, &vrSettingsError);
			if (vrSettingsError != vr::VRSettingsError_None) {
				LOG(WARNING) << "Could not set \"revive::" << key_touchX << "\" setting: " << vr::VRSettings()->GetSettingsErrorNameFromEnum(vrSettingsError);
			}
			vr::VRSettings()->Sync();
			if (notify) {
				emit touchXChanged(m_touchX);
			}
		}
	}

	void ReviveTabController::setTouchY(float value, bool notify) {
		if (m_touchY != value) {
			m_touchY = value;
			vr::EVRSettingsError vrSettingsError;
			vr::VRSettings()->SetFloat(section_revive, key_touchY, m_touchY, &vrSettingsError);
			if (vrSettingsError != vr::VRSettingsError_None) {
				LOG(WARNING) << "Could not set \"revive::" << key_touchY << "\" setting: " << vr::VRSettings()->GetSettingsErrorNameFromEnum(vrSettingsError);
			}
			vr::VRSettings()->Sync();
			if (notify) {
				emit touchYChanged(m_touchY);
			}
		}
	}

	void ReviveTabController::setTouchZ(float value, bool notify) {
		if (m_touchZ != value) {
			m_touchZ = value;
			vr::EVRSettingsError vrSettingsError;
			vr::VRSettings()->SetFloat(section_revive, key_touchZ, m_touchZ, &vrSettingsError);
			if (vrSettingsError != vr::VRSettingsError_None) {
				LOG(WARNING) << "Could not set \"revive::" << key_touchZ << "\" setting: " << vr::VRSettings()->GetSettingsErrorNameFromEnum(vrSettingsError);
			}
			vr::VRSettings()->Sync();
			if (notify) {
				emit touchZChanged(m_touchZ);
			}
		}
	}

	void ReviveTabController::setPiPlayerHeight(float value, bool notify) {
		if (m_piPlayerHeight != value) {
			m_piPlayerHeight = value;
			vr::EVRSettingsError vrSettingsError;
			vr::VRSettings()->SetFloat(section_revive, key_playerHeight, m_piPlayerHeight, &vrSettingsError);
			if (vrSettingsError != vr::VRSettingsError_None) {
				LOG(WARNING) << "Could not set \"revive::" << key_playerHeight << "\" setting: " << vr::VRSettings()->GetSettingsErrorNameFromEnum(vrSettingsError);
			}
			vr::VRSettings()->Sync();
			if (notify) {
				emit piPlayerHeightChanged(m_piPlayerHeight);
			}
		}
	}

	void ReviveTabController::setPiEyeHeight(float value, bool notify) {
		if (m_piEyeHeight != value) {
			m_piEyeHeight = value;
			vr::EVRSettingsError vrSettingsError;
			vr::VRSettings()->SetFloat(section_revive, key_eyeHeight, m_piEyeHeight, &vrSettingsError);
			if (vrSettingsError != vr::VRSettingsError_None) {
				LOG(WARNING) << "Could not set \"revive::" << key_eyeHeight << "\" setting: " << vr::VRSettings()->GetSettingsErrorNameFromEnum(vrSettingsError);
			}
			vr::VRSettings()->Sync();
			if (notify) {
				emit piEyeHeightChanged(m_piEyeHeight);
			}
		}
	}

	void ReviveTabController::setPiUsername(const QString& value, bool notify) {
		if (m_piUsername.compare(value) != 0) {
			m_piUsername = value;
			vr::EVRSettingsError vrSettingsError;
			vr::VRSettings()->SetString(section_revive, key_piUser, m_piUsername.toStdString().c_str(), &vrSettingsError);
			if (vrSettingsError != vr::VRSettingsError_None) {
				LOG(WARNING) << "Could not set \"revive::" << key_piUser << "\" setting: " << vr::VRSettings()->GetSettingsErrorNameFromEnum(vrSettingsError);
			}
			vr::VRSettings()->Sync();
			if (notify) {
				emit piUsernameChanged(m_piUsername);
			}
		}
	}

	void ReviveTabController::setPiName(const QString& value, bool notify) {
		if (m_piName.compare(value) != 0) {
			m_piName = value;
			vr::EVRSettingsError vrSettingsError;
			vr::VRSettings()->SetString(section_revive, key_piName, m_piName.toStdString().c_str(), &vrSettingsError);
			if (vrSettingsError != vr::VRSettingsError_None) {
				LOG(WARNING) << "Could not set \"revive::" << key_piName << "\" setting: " << vr::VRSettings()->GetSettingsErrorNameFromEnum(vrSettingsError);
			}
			vr::VRSettings()->Sync();
			if (notify) {
				emit piNameChanged(m_piName);
			}
		}
	}

	void ReviveTabController::setPiGender(int value, bool notify) {
		if (m_piGender != value) {
			m_piGender = value;
			vr::EVRSettingsError vrSettingsError;
			char* txt;
			switch (value) {
				case 1:
					txt = (char*)"Male";
					break;
				case 2:
					txt = (char*)"Female";
					break;
				default:
					txt = (char*)"Unknown";
					break;
			}
			vr::VRSettings()->SetString(section_revive, key_piGender, txt, &vrSettingsError);
			if (vrSettingsError != vr::VRSettingsError_None) {
				LOG(WARNING) << "Could not set \"revive::" << key_piGender << "\" setting: " << vr::VRSettings()->GetSettingsErrorNameFromEnum(vrSettingsError);
			}
			vr::VRSettings()->Sync();
			if (notify) {
				emit piGenderChanged(m_piGender);
			}
		}
	}

} // namespace advconfig
