
#include "jimk.h"
#include "errcodes.h"
#include "fontdev.h"
#include "resource.h"
#include "softmenu.h"

Errcode init_pj_resources(void)
{
Errcode err;

	if((err = init_menu_parts()) < Success)
		goto error;
	init_font_dev();	/* set up font handling */
error:
	return(softerr(err,"resource_init"));
}
void cleanup_resources(void)
{
	cleanup_menu_parts();
}
