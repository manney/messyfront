/*****************************************************************************
 *                                                                           *
 *   MessyFront - signals.c                                                  *
 *   (C) 2005 - 2007 Aaron Sebold                                            *
 *   Version 19                                                              *
 *                                                                           *
 *****************************************************************************
 *                                                                           *
 *   This program is free software; you can redistribute it and/or modify    *
 *   it under the terms of the GNU General Public License as published by    *
 *   the Free Software Foundation; either version 2 of the License, or       *
 *   (at your option) any later version.                                     *
 *                                                                           *
 *   This program is distributed in the hope that it will be useful,         *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the            *
 *   GNU General Public License for more details.                            *
 *                                                                           *
 *   You should have received a copy of the GNU General Public License       *
 *   along with this program; if not, write to the Free Software             *
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA *
 *                                                                           *
 *****************************************************************************/

#include "messy.h"

void connect_signals (PREFS *images)
{
	/* Handles signals emitted by the GTK side of the program */
	GtkWidget *button, *window;

	/* Handle the "Images Assignment" tab's buttons */
	button = glade_xml_get_widget (images->xml, WIDGET_BIOS_IMAGE_BUTTON);
	g_signal_connect (GTK_BUTTON (button), "clicked", G_CALLBACK (on_bios_image_button_clicked), &images[0]);
	g_signal_connect (GTK_BUTTON (button), "clicked", G_CALLBACK (on_get_filename), &images[0]);

	button = glade_xml_get_widget (images->xml, WIDGET_CARTRIDGE_IMAGE_BUTTON);
	g_signal_connect (GTK_BUTTON (button), "clicked", G_CALLBACK (on_cartridge_image_button_clicked), &images[0]);
	g_signal_connect (GTK_BUTTON (button), "clicked", G_CALLBACK (on_get_filename), &images[0]);
	
	button = glade_xml_get_widget (images->xml, WIDGET_FLOPPY_IMAGES_BUTTON);
	g_signal_connect (GTK_BUTTON (button), "clicked", G_CALLBACK (on_floppy_images_button_clicked), &images[0]);
	g_signal_connect (GTK_BUTTON (button), "clicked", G_CALLBACK (on_get_filename), &images[0]);	

	button = glade_xml_get_widget (images->xml, WIDGET_HDD_IMAGE_BUTTON);
	g_signal_connect (GTK_BUTTON (button), "clicked", G_CALLBACK (on_hdd_image_button_clicked), &images[0]);
	g_signal_connect (GTK_BUTTON (button), "clicked", G_CALLBACK (on_get_filename), &images[0]);	

	/* Handle the "Preferences" tab's buttons */
	button = glade_xml_get_widget (images->xml, WIDGET_MESS_EXECUTABLE_BUTTON);
	g_signal_connect (GTK_BUTTON (button), "clicked", G_CALLBACK (on_mess_executable_button_clicked), &images[0]);
	g_signal_connect (GTK_BUTTON (button), "clicked", G_CALLBACK (on_get_filename), &images[0]);	

	button = glade_xml_get_widget (images->xml, WIDGET_IMAGES_DIRECTORY_BUTTON);
	g_signal_connect (GTK_BUTTON (button), "clicked", G_CALLBACK (on_images_directory_button_clicked), &images[0]);
	g_signal_connect (GTK_BUTTON (button), "clicked", G_CALLBACK (on_get_directory), &images[0]);

	button = glade_xml_get_widget (images->xml, WIDGET_BIOS_DIRECTORY_BUTTON);
	g_signal_connect (GTK_BUTTON (button), "clicked", G_CALLBACK (on_bios_directory_button_clicked), &images[0]);
	g_signal_connect (GTK_BUTTON (button), "clicked", G_CALLBACK (on_get_directory), &images[0]);


	/* Handle the play, about, quit, and window buttons */
	button = glade_xml_get_widget (images->xml, WIDGET_PLAY_BUTTON);
	g_signal_connect (GTK_BUTTON (button), "clicked", G_CALLBACK (on_play_button_clicked), &images[0]);

	button = glade_xml_get_widget (images->xml, WIDGET_ABOUT_BUTTON);
	g_signal_connect (GTK_BUTTON (button), "clicked", G_CALLBACK (on_about_button_clicked), NULL);

	button = glade_xml_get_widget (images->xml, WIDGET_QUIT_BUTTON);
	g_signal_connect (GTK_BUTTON (button), "clicked", G_CALLBACK (on_quit), &images[0]);

	window = glade_xml_get_widget (images->xml, WIDGET_MESSY_MAIN_WINDOW);
	g_signal_connect (GTK_WINDOW (window), "delete_event", G_CALLBACK (on_quit), &images[0]);
}
