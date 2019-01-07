#include "example_app_win.h"

struct _ExampleAppWindow {
	GtkApplicationWindow parent;
};

G_DEFINE_TYPE( ExampleAppWindow, example_app_window, GTK_TYPE_APPLICATION_WINDOW );

static void example_app_window_init( ExampleAppWindow *app ) { (void)app; }

static void example_app_window_class_init( ExampleAppWindowClass *win_class ) {
	(void)win_class;
}

ExampleAppWindow *example_app_window_new( ExampleApp *app ) {
	return (ExampleAppWindow *)g_object_new( EXAMPLE_APP_WINDOW_TYPE, "application", app,
	                                         NULL );
}

void example_app_window_open( ExampleAppWindow *win, GFile *file ) {
	(void)win;
	(void)file;
}
