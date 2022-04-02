#include "Controls.h"

namespace Controls {

	void globalControlsUpdate() {
		if (input::keyF1) {
			input::keyF1 = false;
			if (I_WIN.isFullScreen()) {
				I_WIN.exitFullScreen();
			}
			else {
				I_WIN.setWindowFullScreen();
			}
		}
#ifdef _DEBUG
		if (input::keyF9) {
			DebugSettings::I_SHOWCOLLISIONBOXES = !DebugSettings::I_SHOWCOLLISIONBOXES;
			input::keyF9 = false;
		}
#endif
	}
}