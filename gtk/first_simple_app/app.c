#include <gtk/gtk.h>

#define UNUSED( first, second ) \
	{                           \
		(void)first;            \
		(void)second;           \
	}

#define WIDGET_FROM_BUILDER( builder, ID ) GTK_WIDGET( gtk_builder_get_object( builder, ID ) )

static void button_print( GtkWidget *widget, gpointer data ) {
	g_print( "\nButton pressed\n" );
	UNUSED( widget, data );
}

int main( int argc, char *argv[] ) {
	GError *error = NULL;

	gtk_init( &argc, &argv );

	GtkBuilder *builder = gtk_builder_new( );
	if ( !gtk_builder_add_from_file( builder, "app_xml.glade", &error ) ) {
		g_printerr( "Error loading file: %s\n", error->message );
		g_clear_error( &error );
		exit( EXIT_FAILURE );
	}

	GtkWidget *window = WIDGET_FROM_BUILDER( builder, "window" );
	g_signal_connect( window, "destroy", G_CALLBACK( gtk_main_quit ), NULL );

	GtkWidget *button = WIDGET_FROM_BUILDER( builder, "button1" );
	g_signal_connect( button, "clicked", G_CALLBACK( button_print ), NULL );

	g_object_unref( G_OBJECT( builder ) );

	gtk_widget_show_all( window );

	gtk_main( );

	return 0;
}
