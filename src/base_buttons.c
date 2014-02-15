/*****************************************************************************
 *                                                                           *
 *   MessyFront - base_buttons.c                                             *
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

void on_play_button_clicked (GtkWidget *widget, PREFS *images)
{
	gchar *prefsname, *pythonpath, *commandline;

	/* Make sure that the main struct is updated */
	populate_object_from_fields (&images[0]);
	
	/* Save everything to the config file */
	save_prefs (&images[0]);
	
	/* Get the path and filename of the prefs file */
	prefsname = g_strjoin (DIR_SEP, g_get_home_dir (), PREFS_FILENAME, NULL);
	
	/* Get the path and filename of the python script */
	pythonpath = g_strjoin (DIR_SEP, INSTALL_PREFIX, PYTHON_DIRECTORY, PYTHON_MESS_SCRIPT, NULL);
	
	/* Run the script that will run xMESS */
	commandline = g_strjoin (" ", PYTHON_COMMAND, pythonpath, prefsname, "&", NULL);
	system (commandline);
}

void on_about_button_clicked (GtkWidget *widget)
{
	/* Display about dialog with an "Author's" button and a "License" button */
	GtkWidget *about;
	const gchar *authors[] = {MESSY_AUTHORS, NULL};
	gchar *logo_path;													/* Path to 'messyfront96.png' */
	GdkPixbuf *logo;													/* The fat logo in the dialog */
	
	/* Setup the logo that is deplayed in the about box */
	logo_path = g_strjoin (DIR_SEP, INSTALL_PREFIX, ICON_PATH, LOGO_NAME, NULL);
	logo = gdk_pixbuf_new_from_file (logo_path, NULL);
	
	/* Set the about dialog up */
	about = gtk_about_dialog_new ();
	gtk_about_dialog_set_name (GTK_ABOUT_DIALOG (about), MESSY_APP_NAME);
	gtk_about_dialog_set_version (GTK_ABOUT_DIALOG (about), MESSY_VERSION);
	gtk_about_dialog_set_comments (GTK_ABOUT_DIALOG (about), MESSY_COMMENTS);
	gtk_about_dialog_set_copyright (GTK_ABOUT_DIALOG (about), MESSY_COPYRIGHT);
	gtk_about_dialog_set_website (GTK_ABOUT_DIALOG (about), MESSY_HOMEPAGE);
	gtk_about_dialog_set_authors (GTK_ABOUT_DIALOG (about), authors);
	gtk_about_dialog_set_license (GTK_ABOUT_DIALOG (about), MESSY_LICENSE);
	gtk_about_dialog_set_logo (GTK_ABOUT_DIALOG (about), logo);
	gtk_dialog_run (GTK_DIALOG (about));
	gtk_widget_destroy (GTK_WIDGET (about));
}

void on_quit (GtkWidget *widget, PREFS *images)
{
	/* Save preferences and quit */
	populate_object_from_fields (&images[0]);
	save_prefs (&images[0]);
	gtk_main_quit ();
}
