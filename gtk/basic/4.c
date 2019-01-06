#include <gtk/gtk.h>

#define UNUSED( first, second ) \
	{                           \
		(void)first;            \
		(void)second;           \
	}

static void quit_button( GtkWidget *widget, gpointer data ) {
	g_print( "\nQuit app\n" );
	UNUSED( widget, data );
}

static void button2( GtkWidget *widget, gpointer data ) {
	g_print( "\nPressed button 2\n" );
	UNUSED( widget, data );
}

static void button1( GtkWidget *widget, gpointer data ) {
	g_print( "\nPressed button 1\n" );
	UNUSED( widget, data );
}

int main( int argc, char *argv[] ) {
	GError *error = NULL;

	gtk_init( &argc, &argv );

	GtkBuilder *builder = gtk_builder_new( );
	if ( !gtk_builder_add_from_file( builder, "4c_xml.glade", &error ) ) {
		g_printerr( "Error loading file: %s\n", error->message );
		g_clear_error( &error );
		exit( EXIT_FAILURE );
	}

	GtkWidget *window = GTK_WIDGET( gtk_builder_get_object( builder, "window" ) );
	g_signal_connect( window, "destroy", G_CALLBACK( gtk_main_quit ), NULL );

	GtkWidget *button = GTK_WIDGET( gtk_builder_get_object( builder, "button1" ) );
	g_signal_connect( button, "clicked", G_CALLBACK( button1 ), NULL );

	button = GTK_WIDGET( gtk_builder_get_object( builder, "button2" ) );
	g_signal_connect( button, "clicked", G_CALLBACK( button2 ), NULL );

	button = GTK_WIDGET( gtk_builder_get_object( builder, "quit_button" ) );
	g_signal_connect( button, "clicked", G_CALLBACK( quit_button ), NULL );
	g_signal_connect_swapped( button, "clicked", G_CALLBACK( gtk_main_quit ), window );

	g_object_unref( G_OBJECT( builder ) );

	gtk_widget_show_all( window );

	gtk_main( );

	return 0;
}
