/*****************************************************************************
 *                                                                           *
 *   MessyFront - button_common.c                                            *
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

void on_get_directory (GtkWidget *widget, PREFS *images)
{
	/* Get the user selected directory */
	GtkWidget *directory, *field;

	/* Switch statement based on images->button_pushed */
	switch (images->button_pushed)
	{
		case NUMBER_IMAGES_DIRECTORY_BUTTON:
			/* This is for the "Main Image Directory" field */
			field = glade_xml_get_widget (images->xml, WIDGET_IMAGES_DIRECTORY);
			break;
		case NUMBER_BIOS_DIRECTORY_BUTTON:
			/* This is for the "BIOS ROM Image Directory" field */
			field = glade_xml_get_widget (images->xml, WIDGET_BIOS_DIRECTORY);
			break;
		default:
			break;
	}

	/* Bring up the directory (file) chooser dialog */
	directory = gtk_file_chooser_dialog_new ("Select a Directory", NULL, GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT, NULL);

	/* Set where the file chooser starts from */
	switch (images->button_pushed)
	{
		case NUMBER_IMAGES_DIRECTORY_BUTTON:
			if (!strcmp (images->images_directory, ""))
				gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER (directory), g_get_home_dir ());
			else
				gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER (directory), images->images_directory);
			break;
		case NUMBER_BIOS_DIRECTORY_BUTTON:
			if (!strcmp (images->bios_directory, ""))
				gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER (directory), g_get_home_dir ());
			else
				gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER (directory), images->bios_directory);
			break;
		default:
			gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER (directory), g_get_home_dir ());
			break;
	}

	/* Finish bringing up the file chooser */
	if (gtk_dialog_run (GTK_DIALOG (directory)) == GTK_RESPONSE_ACCEPT)
		gtk_entry_set_text (GTK_ENTRY (field), gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (directory)));

	/* Kill the file chooser */
	gtk_widget_destroy (directory);

	/* Reset the images->button_pushed flag */
	images->button_pushed = NUMBER_NO_BUTTON;

	/* Make sure to re-populate the main structure (object) */
	populate_object_from_fields (&images[0]);
}

void on_get_filename (GtkWidget *widget, PREFS *images)
{
	/* Get the user selected filename */
	GtkWidget *filename, *field;

	/* Switch statement based on images->button_pushed */
	switch (images->button_pushed)
	{
		case NUMBER_BIOS_IMAGE_BUTTON:
			/* This is for the "Bios Image" field */
			field = glade_xml_get_widget (images->xml, WIDGET_BIOS_IMAGE);
			break;
		case NUMBER_CARTRIDGE_IMAGE_BUTTON:
			/* This is for the "Cartridge Image" field */
			field = glade_xml_get_widget (images->xml, WIDGET_CARTRIDGE_IMAGE);
			break;
		case NUMBER_FLOPPY_IMAGES_BUTTON:
			/* This is for the "Floppy Image(s)" field */
			field = glade_xml_get_widget (images->xml, WIDGET_FLOPPY_IMAGES);
			break;
		case NUMBER_HDD_IMAGE_BUTTON:
			/* This is for the "Hard Disk Image" field */
			field = glade_xml_get_widget (images->xml, WIDGET_HDD_IMAGE);
			break;
		case NUMBER_MESS_EXECUTABLE_BUTTON:
			/* This is for the "MESS' Executable Location" field */
			field = glade_xml_get_widget (images->xml, WIDGET_MESS_EXECUTABLE);
			break;
		default:
			break;
	}

	/* Bring up the file chooser dialog */
	filename = gtk_file_chooser_dialog_new ("Select a File", NULL, GTK_FILE_CHOOSER_ACTION_OPEN, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT, NULL);

	/* Set where the file chooser starts from */
	switch (images->button_pushed)
	{
		case NUMBER_MESS_EXECUTABLE_BUTTON:
			gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER (filename), g_get_home_dir ());
			break;
		case NUMBER_BIOS_IMAGE_BUTTON:
			if (!strcmp (images->bios_directory, ""))
				gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER (filename), g_get_home_dir ());
			else
				gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER (filename), images->bios_directory);
			break; 
		default:
			if (!strcmp (images->images_directory, ""))
				gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER (filename), g_get_home_dir ());
			else
				gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER (filename), images->images_directory);
			break;
	}

	/* Allow user to select multiple items if appropriate */
	if (images->button_pushed == NUMBER_FLOPPY_IMAGES_BUTTON)
		gtk_file_chooser_set_select_multiple (GTK_FILE_CHOOSER (filename), TRUE);

	/* Finish bringing up the file chooser */
	if (gtk_dialog_run (GTK_DIALOG (filename)) == GTK_RESPONSE_ACCEPT)
	{
		if (images->button_pushed != NUMBER_FLOPPY_IMAGES_BUTTON)
			gtk_entry_set_text (GTK_ENTRY (field), gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (filename)));
		else
		{
			GSList *filenames = NULL;
			gchar *all_filenames = NULL;
			int x;

			filenames = gtk_file_chooser_get_filenames (GTK_FILE_CHOOSER (filename));

			for (x = 0; x < g_slist_length (filenames); x++)
				all_filenames = g_strjoin (FLOPPY_IMAGES_COMMON_SEPARATOR, (gchar *)g_slist_nth_data (filenames, x), all_filenames, NULL);

			gtk_entry_set_text (GTK_ENTRY (field), all_filenames);
			g_slist_free (filenames);
		}
	}

	/* Kill the file chooser */
	gtk_widget_destroy (filename);

	/* Reset the images->button_pushed flag */
	images->button_pushed = NUMBER_NO_BUTTON;

	/* Make sure to re-populate the main structure (object) */
	populate_object_from_fields (&images[0]);
}
