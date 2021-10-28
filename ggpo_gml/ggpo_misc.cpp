#include "stdafx.h"

/// ->ggpo_errorcode
dllx double gml_ggpo_set_disconnect_timeout(double timeout) {
	return ggpo_set_disconnect_timeout(ggpo, (int)timeout);
}

/// ->ggpo_errorcode
dllx double gml_ggpo_set_disconnect_notify_start(double timeout) {
	return ggpo_set_disconnect_notify_start(ggpo, (timeout));
}