#ifndef EXAMPLE_APP_WIN_H
#define EXAMPLE_APP_WIN_H

#include <gtk/gtk.h>
#include "example_app.h"

#define EXAMPLE_APP_WINDOW_TYPE ( example_app_window_get_type( ) )

G_DECLARE_FINAL_TYPE( ExampleAppWindow, example_app_window, EXAMPLE, APP_WINDOW,
                      GtkApplicationWindow )

extern ExampleAppWindow *example_app_window_new( ExampleApp * );

extern void              example_app_window_open( ExampleAppWindow *, GFile * );


#endif
