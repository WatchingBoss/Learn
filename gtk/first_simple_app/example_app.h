#ifndef EXAMPLE_APP_H
#define EXAMPLE_APP_H

#include <gtk/gtk.h>

#define EXAMPLE_APP_TYPE ( example_app_get_type( ) )

G_DECLARE_FINAL_TYPE( ExampleApp, example_app, EXAMPLE, APP, GtkApplication )

extern ExampleApp *example_app_new( );

#endif
