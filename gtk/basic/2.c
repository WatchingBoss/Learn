#include <gtk/gtk.h>

const int WIDTH = 400, HEIGHT = 400;

static void button_1_print( GtkWidget *widget, gpointer data ) {
	g_print( "\nThis button will not close window\n\n" );

	(void)widget;
	(void)data;
}

static void button_2_print( GtkWidget *widget, gpointer data ) {
	g_print( "\nThw window just has been closed\n\n" );

	(void)widget;
	(void)data;
}

static void activate( GtkApplication *app, gpointer user_data ) {
	GtkWidget *window = gtk_application_window_new( app );
	gtk_window_set_title( GTK_WINDOW( window ), "My first button" );
	gtk_window_set_default_size( GTK_WINDOW( window ), WIDTH, HEIGHT );

	GtkWidget *button_box = gtk_button_box_new( GTK_ORIENTATION_HORIZONTAL );
	gtk_container_add( GTK_CONTAINER( window ), button_box );

	GtkWidget *button_1 = gtk_button_new_with_label( "Printing to console" );
	g_signal_connect( button_1, "clicked", G_CALLBACK( button_1_print ), NULL );
	gtk_container_add( GTK_CONTAINER( button_box ), button_1 );

	GtkWidget *button_2 = gtk_button_new_with_label( "Printing and closign window" );
	g_signal_connect( button_2, "clicked", G_CALLBACK( button_2_print ), NULL );
	g_signal_connect_swapped( button_2, "clicked", G_CALLBACK( gtk_widget_destroy ), window );
	gtk_container_add( GTK_CONTAINER( button_box ), button_2 );

	gtk_widget_show_all( window );

	(void)user_data;
}

int main( int argc, char *argv[] ) {
	GtkApplication *app = gtk_application_new( "org.gtk.button", G_APPLICATION_FLAGS_NONE );
	g_signal_connect( app, "activate", G_CALLBACK( activate ), NULL );
	int status = g_application_run( G_APPLICATION( app ), argc, argv );
	g_object_unref( app );

	return status;
}
