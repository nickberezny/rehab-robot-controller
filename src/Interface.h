#include <gtk/gtk.h>

struct interfaceData 
{
	GtkWidget *text_entry[10];
};

struct paramRange
{
	double min;
	double max;
};

void activate (GtkApplication *app, gpointer user_data);
void addTextAndEntry(GtkWidget * grid, GtkWidget * text, GtkWidget ** entry, char * str, gint row, double min, double max, struct paramRange * ranges);
static void getValues(GtkWidget *widget, gpointer data);
static void destroy_window( GtkWidget *widget, gpointer data );
static void checkParameter(GtkWidget *widget, gpointer data);
void addHeaderText(GtkWidget * grid, GtkWidget * text, char * str, gint row);
