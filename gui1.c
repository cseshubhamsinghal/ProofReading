/*include the header files*/
#include<gtk/gtk.h>
#include<string.h>

#include "client.c"
#include "validate.c"


 GtkWidget *entry;
 GtkTextBuffer *buffer;
 char data[25500];
 char dd[1];
 void on_window_destroy (GtkWidget *widget, gpointer data)
 {
  gtk_main_quit (); 
 }

 //button click event
 void on_btn1_clicked(GtkWidget *widget,gpointer data)
 {
  data=gtk_entry_get_text(GTK_ENTRY(entry));
  dd[0]=' ';
  
  GtkTextIter start;
  GtkTextIter end;
  
  gchar *text;
  
  gtk_text_buffer_get_start_iter (buffer, &start);
  gtk_text_buffer_get_end_iter (buffer, &end);
  
  text = gtk_text_buffer_get_text (buffer, &start, &end, FALSE);
  
  int flag = check(data);//validation is performed
  if(flag==0){ 
  if((strlen(data)!=0)&&(strlen(text)!=0)&&(strlen(data)==9)) //other validations
  { 
   data=strcat(data,dd);
   data=strcat(data,text);
   puts(data);
   main2(data);

   gtk_main_quit (); //gui window is closed
  }}
}

int main(int argc,char *argv[])
{
 GtkWidget *window;
 GtkWidget *fixed;
 GtkWidget *btn1;
 GtkWidget *align1;
 GtkWidget *lbl1,*lbl2;
 GtkWidget *vbox;
 GtkWidget *text_view;

 gtk_init(&argc,&argv);

 window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
 gtk_window_set_title(GTK_WINDOW(window),"ProofReading Bot");
 gtk_window_set_default_size(GTK_WINDOW(window),330,300);
 gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
 g_signal_connect (G_OBJECT (window), "destroy", 
                   G_CALLBACK (on_window_destroy),
                   NULL);

 fixed=gtk_fixed_new();
 gtk_container_add(GTK_CONTAINER(window),fixed);

 //designing label1
 align1=gtk_alignment_new(0,0,0,1);
 lbl1=gtk_label_new("ASSIGNMENT SUBMISSION HERE");
 gtk_fixed_put(GTK_FIXED(fixed),lbl1,8,20);
 gtk_widget_set_size_request(lbl1,310,20);
 gtk_container_add(GTK_CONTAINER(align1),lbl1);
 gtk_container_add(GTK_CONTAINER(window),align1);
 gtk_label_set_justify (lbl1,GTK_JUSTIFY_CENTER);
 g_signal_connect(G_OBJECT(window),"destroy",
                  G_CALLBACK(gtk_main_quit),
                  NULL);

 //designing label2
 lbl2=gtk_label_new("ENTER SAP ID");
 gtk_fixed_put(GTK_FIXED(fixed),lbl2,20,60);
 gtk_widget_set_size_request(lbl2,95,25);
 gtk_container_add(GTK_CONTAINER(align1),lbl2);
 gtk_container_add(GTK_CONTAINER(window),align1);
 g_signal_connect(G_OBJECT(window),"destroy",
                  G_CALLBACK(gtk_main_quit),
                  NULL);

 //designing textbox
 entry=gtk_entry_new();
 gtk_fixed_put(GTK_FIXED(fixed),entry,130,60);
 gtk_widget_set_size_request(entry,83,25);

 //designing textarea
 text_view = gtk_text_view_new ();
 gtk_fixed_put(GTK_FIXED(fixed),text_view,20,105);
 gtk_widget_set_size_request(text_view,290,140);

 buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (text_view));
 gtk_text_buffer_set_text (buffer, "Enter your assignment here", -1);

 //designing button
 btn1=gtk_button_new_with_label("submit");
 gtk_fixed_put(GTK_FIXED(fixed),btn1,125,260);
 gtk_widget_set_size_request(btn1,80,30);
 g_signal_connect(G_OBJECT(btn1),"clicked",
                  G_CALLBACK(on_btn1_clicked),
                  buffer);

 gtk_widget_show_all(window);
 gtk_main();
 return 0;
}
