#include <pthread.h>

#include "../util/cache.h"
#include "../util/debug.h"
#include "../util/hist.h"

pthread_mutex_t ui__lock = PTHREAD_MUTEX_INITIALIZER;

void setup_browser(bool fallback_to_pager)
{
	if (use_browser < 2 && (!isatty(1) || dump_trace))
		use_browser = 0;

	
	if (use_browser < 0)
		use_browser = 1;

	switch (use_browser) {
	case 2:
		if (perf_gtk__init() == 0)
			break;
		
	case 1:
		use_browser = 1;
		if (ui__init() == 0)
			break;
		
	default:
		use_browser = 0;
		if (fallback_to_pager)
			setup_pager();

		perf_hpp__init();
		break;
	}
}

void exit_browser(bool wait_for_ok)
{
	switch (use_browser) {
	case 2:
		perf_gtk__exit(wait_for_ok);
		break;

	case 1:
		ui__exit(wait_for_ok);
		break;

	default:
		break;
	}
}