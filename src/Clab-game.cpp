/*
 * Clab-game.cpp
 * 07/18/2019
 * jmb
 */

#include <string>
#include "Clab-game.h"
#include "Manager.h"
#include "Video.h"
#include "Types.h"
#include "config.h"
#include "toaster.h"

using std::string;
using jmb::common::Manager;
using jmb::common::Video;
using jmb::common::Types::AddMapping;

namespace jmb {
	namespace common {
		int ClabGameInit() {
			int retval = 0;  // TODO:  something meaningful with this?
			AddMapping("Manager", Manager::CtorWrapper);
			AddMapping("Video", Video::CtorWrapper);
			return retval;
		}

		string ClabGameVersionString() {
			return string(TOASTER(PACKAGE_NAME)) + " " + string(TOASTER(PACKAGE_VERSION)) + " built on " + __DATE__ + " at " + __TIME__;
		}

		int ClabGameVersionMajor() {
			return CLAB_GAME_VERSION_MAJOR;
		}

		int ClabGameVersionMinor() {
			return CLAB_GAME_VERSION_MINOR;
		}
	}
}
