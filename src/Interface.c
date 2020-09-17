#include "Interface.h"
#include "SystemStructures.h"

extern struct controllerParameters * controllerParamBuffer;


void activate (GtkApplication *app, gpointer user_data)
{
  GtkWidget *window;
  GtkWidget *button_box;
  GtkWidget *button[2];
  GtkWidget *box;
  GtkWidget *grid;
  GtkWidget *text[10]; 

  static struct interfaceData InterfaceData;
  static struct paramRange ranges[10] = {0};

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Window");
  gtk_window_set_default_size (GTK_WINDOW (window), 800, 800);
  gtk_container_set_border_width(GTK_CONTAINER (window), 25);

  grid = gtk_grid_new ();
  gtk_grid_set_column_spacing (GTK_GRID(grid), 20);
  gtk_grid_set_row_spacing (GTK_GRID(grid), 20);

  for(int i = 0; i < 10; i++)
  {
    InterfaceData.text_entry[i] = gtk_entry_new();
  }

  button[0] = gtk_button_new_with_label ("Set");
  g_signal_connect (button[0], "clicked", G_CALLBACK (getValues), &InterfaceData);

  button[1] = gtk_button_new_with_label ("Run");
  g_signal_connect (button[1], "clicked", G_CALLBACK (destroy_window), window);


  addHeaderText(grid, text[0], "Session Parameters",1);
  addTextAndEntry(grid, text[1], &InterfaceData.text_entry[0], "Time (s)", 2, 0, 100, &ranges[0]);
  addTextAndEntry(grid, text[2], &InterfaceData.text_entry[1], "Velocity (m/s)", 3, 0.01, 10, &ranges[1]);
  addHeaderText(grid, text[3], "Impedance Parameters",4);
  addTextAndEntry(grid, text[4], &InterfaceData.text_entry[2], "K (N/m)", 5, 0, 10, &ranges[2]);
  addTextAndEntry(grid, text[5], &InterfaceData.text_entry[3], "B (Ns/m)", 6, 1, 10, &ranges[3]);

  gtk_grid_attach (GTK_GRID (grid), button[0], 1, 7, 2, 1);
  gtk_grid_attach (GTK_GRID (grid), button[1], 1, 8, 2, 1);

  gtk_container_add (GTK_CONTAINER (window), grid);
  gtk_widget_show_all (window);
}

void addTextAndEntry(GtkWidget * grid, GtkWidget * text, GtkWidget ** entry, char * str, gint row, double min, double max, struct paramRange * ranges)
{
  text = gtk_label_new (str);

  ranges->min = min;
  ranges->max = max;

  g_signal_connect(G_OBJECT(*entry), "changed", G_CALLBACK(checkParameter), ranges);
  gtk_grid_attach (GTK_GRID (grid), text, 1, row, 1, 1);
  gtk_grid_attach_next_to (GTK_GRID (grid), *entry, text, GTK_POS_RIGHT, 1, 1);

  char temp[50] = ""; 
  snprintf(temp, 50, "%f", (max-min)/2.0);
  gtk_entry_set_text(GTK_ENTRY(*entry), temp);

}


void addHeaderText(GtkWidget * grid, GtkWidget * text, char * str, gint row)
{
  const char *format = "<span size=\"x-large\">%s</span>";
  char *markup;

  markup = g_markup_printf_escaped (format, str);
  text = gtk_label_new (NULL);
  gtk_label_set_markup (GTK_LABEL (text), markup);
  g_free (markup);

  gtk_grid_attach (GTK_GRID (grid), text, 1, row, 2, 1);
}

static void getValues(GtkWidget *widget, gpointer data)
{

  struct interfaceData * InterfaceData = (struct interfaceData *) data;

  controllerParamBuffer->time = strtod(gtk_entry_get_text(GTK_ENTRY(InterfaceData->text_entry[0])), NULL);
  controllerParamBuffer->maxVelocity =  strtod(gtk_entry_get_text(GTK_ENTRY(InterfaceData->text_entry[1])), NULL);
  controllerParamBuffer->K =  strtod(gtk_entry_get_text(GTK_ENTRY(InterfaceData->text_entry[2])), NULL);
  controllerParamBuffer->B =  strtod(gtk_entry_get_text(GTK_ENTRY(InterfaceData->text_entry[3])), NULL);

  return;
}

static void destroy_window(GtkWidget *widget, gpointer data)
{
  gtk_window_close(GTK_WINDOW((GtkWidget*)data));
}

static void checkParameter(GtkWidget *widget, gpointer data)
{
  struct paramRange * ranges = (struct paramRange *) data;
  char * endptr; 
  double entryNum = strtod(gtk_entry_get_text(GTK_ENTRY(widget)), &endptr);
  GdkColor color;

  if(strcmp(endptr, "") != 0 || entryNum > ranges->max || entryNum < ranges->min)
  {
    G_GNUC_BEGIN_IGNORE_DEPRECATIONS
    gdk_color_parse( "#ff0000", &color );
    gtk_widget_modify_fg( GTK_WIDGET(widget), GTK_STATE_NORMAL, &color );
  }
  else 
  {
    gdk_color_parse( "#ffffff", &color );
    gtk_widget_modify_fg( GTK_WIDGET(widget), GTK_STATE_NORMAL, &color );
    G_GNUC_END_IGNORE_DEPRECATIONS
  }

}