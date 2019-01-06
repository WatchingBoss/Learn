#include <gtk/gtk.h>

#define UNUSED( x, y ) \
	{                  \
		(void)x;       \
		(void)y;       \
	}

static const int iWIDTH = 400, iHEIGHT = 400;

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

static void activate( GtkApplication *app, gpointer user_data ) {
	GtkWidget *window = gtk_application_window_new( app );
	gtk_window_set_title( GTK_WINDOW( window ), "Title of window" );
	gtk_window_set_default_size( GTK_WINDOW( window ), iWIDTH, iHEIGHT );

	GtkWidget *grid = gtk_grid_new( );
	gtk_container_add( GTK_CONTAINER( window ), grid );

	GtkWidget *button = gtk_button_new_with_label( "Button 1" );
	g_signal_connect( button, "clicked", G_CALLBACK( button1 ), NULL );
	gtk_grid_attach( GTK_GRID( grid ), button, 0, 0, 1, 1 );

	button = gtk_button_new_with_label( "Button 2" );
	g_signal_connect( button, "clicked", G_CALLBACK( button2 ), NULL );
	gtk_grid_attach( GTK_GRID( grid ), button, 1, 0, 1, 1 );

	button = gtk_button_new_with_label( "Quit" );
	g_signal_connect( button, "clicked", G_CALLBACK( quit_button ), NULL );
	g_signal_connect_swapped( button, "clicked", G_CALLBACK( gtk_widget_destroy ), window );
	gtk_grid_attach( GTK_GRID( grid ), button, 0, 1, 2, 1 );

	gtk_widget_show_all( window );

	(void)user_data;
}

int main( int argc, char *argv[] ) {
	GtkApplication *app = gtk_application_new( "org.gtk.example", G_APPLICATION_FLAGS_NONE );
	g_signal_connect( app, "activate", G_CALLBACK( activate ), NULL );
	int status = g_application_run( G_APPLICATION( app ), argc, argv );
	g_object_unref( app );

	return status;
}
