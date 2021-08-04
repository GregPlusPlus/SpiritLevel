#include "app.h"

void registerApps(Apps_t *apps, ...) {
		va_list appList;
		size_t count = 0;
		
		va_start(appList, apps);

		while(va_arg(appList, App_t*)) {
				count ++;
		}

		va_end(appList);

		va_start(appList, apps);

		apps->count = count;
		apps->apps = (App_t**)malloc(sizeof(App_t*) * apps->count);

		if(!apps->apps) {
						API_DispERROR("ERROR :\nUnable to allocate\napp list.");

						while(1);
		}

		for(size_t i = 0; i < apps->count; i++) {
				apps->apps[i] = va_arg(appList, App_t*);
		}

		va_end(appList);
}

void initAppMenu(Menu_t *menu, Apps_t *apps, char *name) {
	menu->name = name;
	menu->count = apps->count;
	menu->entries = (MenuEntry_t**)malloc(sizeof(MenuEntry_t*) * apps->count);

	if(!menu->entries) {
		API_DispERROR("ERROR :\nUnable to allocate\nmenu list.");

		while(1);
	}

	for(size_t i = 0; i < apps->count; i++) {
		menu->entries[i] = (MenuEntry_t*)malloc(sizeof(MenuEntry_t));

		if(!menu->entries[i]) {
			API_DispERROR("ERROR :\nUnable to allocate\nmenu entry.");

			while(1);
		}

		menu->entries[i]->name = apps->apps[i]->name;
		menu->entries[i]->index = i;
	}
}
