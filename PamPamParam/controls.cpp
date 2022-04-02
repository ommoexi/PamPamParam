#include "Controls.h"

namespace Controls {

	void globalControlsUpdate() {
		if (Input::keyF1) {
			Input::keyF1 = false;
			if (I_WIN.isFullScreen()) {
				I_WIN.exitFullScreen();
			}
			else {
				I_WIN.setWindowFullScreen();
			}
		}
#ifdef _DEBUG
		if (Input::keyF9) {
			DebugSettings::I_SHOWCOLLISIONBOXES = !DebugSettings::I_SHOWCOLLISIONBOXES;
			Input::keyF9 = false;
		}
#endif
	}
}