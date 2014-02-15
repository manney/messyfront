/*****************************************************************************
 *                                                                           *
 *   MessyFront - main.c                                                     *
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

int main (int argc, char *argv[])
{
	PREFS images;															/* Create preferences object */
	gchar *window_name;												/* String to hold window's name */
	gchar *xmlpath;														/* Path to Glade's XML file */
	gchar *iconpath;													/* Path to MESSyFront's icon */

	gtk_init (&argc, &argv);									/* Initialize GTK */
	glade_init ();														/* Initialize Glade */

	/* Create Glade Interface */
	xmlpath = g_strjoin (DIR_SEP, INSTALL_PREFIX, XML_DIRECTORY, XML_FILENAME, NULL);
	images.xml = glade_xml_new (xmlpath, NULL, NULL);
	if (!images.xml)
	{
		g_warning ("MESSYFRONT: Unable to create interface with libglade!");
		exit (EXIT_FAILURE);
	}

	/* Connect homemade signals */
	connect_signals (&images);

	/* Connect Glade-made signals */
	glade_xml_signal_autoconnect (images.xml);

	/* Set window's name and icon */
	window_name = g_strjoin (" ", MESSY_APP_NAME, MESSY_VERSION, NULL);
	change_window_name (&images, window_name);
	iconpath = g_strjoin (DIR_SEP, INSTALL_PREFIX, ICON_PATH, ICON_NAME, NULL);
	change_window_icon (&images, iconpath);

	get_prefs_from_file (&images);						/* Get user's preferences */
	populate_object_from_fields (&images);		/* Initialize object "images" */

	gtk_main ();															/* Start the main event loop */

	return EXIT_SUCCESS;											/* End of story. */
}
