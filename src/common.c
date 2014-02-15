/*****************************************************************************
 *                                                                           *
 *   MessyFront - common.c                                                   *
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

void change_window_name (PREFS *images, gchar *window_name)
{
	GtkWidget *window;													/* Window's widget */

	/* Get the widget from Glade's XML file */
	window = glade_xml_get_widget (images->xml, WIDGET_MESSY_MAIN_WINDOW);

	/* Set the window's name */
	gtk_window_set_title (GTK_WINDOW (window), window_name);
}

void change_window_icon (PREFS *images, gchar *icon)
{
	GtkWidget *window;													/* Window's widget */
	
	/* Get the widget from Glade's XML file */
	window = glade_xml_get_widget (images->xml, WIDGET_MESSY_MAIN_WINDOW);
	
	/* Set window's icon */
	gtk_window_set_icon_from_file (GTK_WINDOW (window), icon, NULL);
}

void populate_object_from_fields (PREFS *images)
{
	/* Populate the main structure (object) from MESSyFronts's widgets */
	GtkWidget *widget;													/* Pointer to widget(s) */

	/* Get the selected entry from the bios combobox */
	widget = glade_xml_get_widget (images->xml, WIDGET_BIOS_IMAGE);
	images->bios_image = g_strjoin ("", gtk_entry_get_text (GTK_ENTRY (widget)), NULL);

	/* Get the cartridge from the entry field */
	widget = glade_xml_get_widget (images->xml, WIDGET_CARTRIDGE_IMAGE);
	images->cartridge_image = g_strjoin ("", gtk_entry_get_text (GTK_ENTRY (widget)), NULL);

	/* Get the floppies from the entry field */
	widget = glade_xml_get_widget (images->xml, WIDGET_FLOPPY_IMAGES);
	images->floppy_images = g_strjoin ("", gtk_entry_get_text (GTK_ENTRY (widget)), NULL);

	/* Get the hdd from the entry field */
	widget = glade_xml_get_widget (images->xml, WIDGET_HDD_IMAGE);
	images->hdd_image = g_strjoin ("", gtk_entry_get_text (GTK_ENTRY (widget)), NULL);

	/* Get the MESS executable from the entry field */
	widget = glade_xml_get_widget (images->xml, WIDGET_MESS_EXECUTABLE);
	images->mess_executable = g_strjoin ("", gtk_entry_get_text (GTK_ENTRY (widget)), NULL);

	/* Get the images directory from the entry field */
	widget = glade_xml_get_widget (images->xml, WIDGET_IMAGES_DIRECTORY);
	images->images_directory = g_strjoin ("", gtk_entry_get_text (GTK_ENTRY (widget)), NULL);

	/* Get the bios directory from the entry field */
	widget = glade_xml_get_widget (images->xml, WIDGET_BIOS_DIRECTORY);
	images->bios_directory = g_strjoin ("", gtk_entry_get_text (GTK_ENTRY (widget)), NULL);

	/* Get the status of the display command checkbox from the checkbox */
	widget = glade_xml_get_widget (images->xml, WIDGET_DISPLAY_COMMAND);
	if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (widget)))
		images->display_command = TRUE;
	else
		images->display_command = FALSE;
}

void populate_fields_from_object (PREFS *images)
{
	/* Populate MESSyFront's widgets from the main structure (object) */
	GtkWidget *widget;													/* Pointer to widget(s) */

	/* Get the text from images->bios_image */
	widget = glade_xml_get_widget (images->xml, WIDGET_BIOS_IMAGE);
	gtk_entry_set_text (GTK_ENTRY (widget), images->bios_image);

	/* Get the text from images->cartridge_image */
	widget = glade_xml_get_widget (images->xml, WIDGET_CARTRIDGE_IMAGE);
	gtk_entry_set_text (GTK_ENTRY (widget), images->cartridge_image);

	/* Get the text from images->floppy_images */
	widget = glade_xml_get_widget (images->xml, WIDGET_FLOPPY_IMAGES);
	gtk_entry_set_text (GTK_ENTRY (widget), images->floppy_images);

	/* Get the text from images->hdd_image */
	widget = glade_xml_get_widget (images->xml, WIDGET_HDD_IMAGE);
	gtk_entry_set_text (GTK_ENTRY (widget), images->hdd_image);

	/* Get the text from images->mess_executable */
	widget = glade_xml_get_widget (images->xml, WIDGET_MESS_EXECUTABLE);
	gtk_entry_set_text (GTK_ENTRY (widget), images->mess_executable);

	/* Get the text from images->images_directory */
	widget = glade_xml_get_widget (images->xml, WIDGET_IMAGES_DIRECTORY);
	gtk_entry_set_text (GTK_ENTRY (widget), images->images_directory);

	/* Get the text from images->bios_directory */
	widget = glade_xml_get_widget (images->xml, WIDGET_BIOS_DIRECTORY);
	gtk_entry_set_text (GTK_ENTRY (widget), images->bios_directory);

	/* Get the status of images->display_command */
	widget = glade_xml_get_widget (images->xml, WIDGET_DISPLAY_COMMAND);
	if (images->display_command)
		gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (widget), TRUE);
	else
		gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (widget), FALSE);
}

void common_message_dialog (char *message)
{
	/* Create an informational dialog with the variable "message" as it's text. */
	GtkWidget *dialog;
	
	dialog = gtk_message_dialog_new (NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, message);
	gtk_dialog_run (GTK_DIALOG (dialog));
	gtk_widget_destroy (dialog);
}

char *lefts (char *dest, gchar *source, int noc)
{
	/* Grabs 'noc' characters from the beginning of a string */
	/* and copies them to 'dest'                             */
	int x, y = 0;

	for (x = 0; x < noc; x++)
	{
		dest[y] = source[x];
		y++;
	}
	dest[y] = '\0';

	return dest;
}

char *rights (char *dest, gchar *source, int noc)
{
	/* Grabs 'noc' characters from the end of a string */
	/* and copies them to 'dest'                       */
	int source_len;
	int x, y = 0;

	source_len = strlen (source);
	for (x = source_len - noc; x < source_len; x++)
	{
		dest[y] = source[x];
		y++;
	}
	dest[y] = '\0';

	return dest;
}
