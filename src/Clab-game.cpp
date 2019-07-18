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

		string ClabGameVersionStr() {
			return string(TOASTER(PACKAGE_NAME)) + " built on " + __DATE__;
		}

		double ClabGameVersionNum() {
			return (double)PACKAGE_VERSION;
		}
	}
}
