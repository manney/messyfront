/*****************************************************************************
 *                                                                           *
 *   MessyFront - messy.h                                                    *
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <glade/glade.h>

/* Main Structure (Object) */
struct prefs
{
	GladeXML *xml;
	int button_pushed;
	gchar *bios_image;
	gchar *cartridge_image;
	gchar *floppy_images;
	gchar *hdd_image;
	gchar *mess_executable;
	gchar *images_directory;
	gchar *bios_directory;
	gboolean display_command;
};
typedef struct prefs PREFS;

/* General Setup Constants */
#define XML_FILENAME											"messyfront.glade"
#define XML_DIRECTORY											"share/messyfront/glade"
#define PYTHON_COMMAND										"/usr/bin/env python"
#define PYTHON_DIRECTORY									"share/messyfront/python"
#define PYTHON_MESS_SCRIPT								"readmess.py"
#define ICON_PATH													"share/pixmaps/messyfront"
#define ICON_NAME													"messyfront48.png"
#define PREFS_FILENAME										".messyfront"
#define MESSY_APP_NAME										"MESSyFront"
#define MESSY_VERSION											"19"
#define MESSY_BETA_VERSION								"19\nBuild 112207"

/* MESS' Command Line Option Switches */
#define MESS_SWITCH_BIOS_DIRECTORY				"-bp"
#define MESS_SWITCH_CARTRIDGE_IMAGE				"-cart"
#define MESS_SWITCH_FLOPPY_IMAGES					"-floppydisk"
#define MESS_SWITCH_HDD_IMAGE							"-harddisk"

/* Preferences Setup Constants */
#define DEFAULT_MESS_EXECUTABLE						"/usr/games/xmess"
#define DEFAULT_BIOS_IMAGE								"coco3"
#define DEFAULT_CARTRIDGE_IMAGE						""
#define DEFAULT_FLOPPY_IMAGES							"os9hd.dsk"
#define DEFAULT_HDD_IMAGE									"os9hd.vhd"
#define DEFAULT_IMAGES_DIRECTORY					"mess_images"
#define DEFAULT_BIOS_DIRECTORY						"mess_bios"
#define DEFAULT_DISPLAY_COMMAND						"FALSE"

/* Preference File's Key Words and Size Constants */
#define KEY_BIOS_IMAGE										"BIOS_IMAGE "
#define KEY_CARTRIDGE_IMAGE								"CARTRIDGE_IMAGE "
#define KEY_FLOPPY_IMAGES									"FLOPPY_IMAGES "
#define KEY_HDD_IMAGE											"HDD_IMAGE "
#define KEY_MESS_EXECUTABLE								"MESS_EXECUTABLE "
#define KEY_IMAGES_DIRECTORY							"IMAGES_DIRECTORY "
#define KEY_BIOS_DIRECTORY								"BIOS_DIRECTORY "
#define KEY_DISPLAY_COMMAND								"DISPLAY_COMMAND "
#define KEY_WORDS													8
#define KEY_WORDS_MAX_SIZE								20

/* GTK Widget Names Constants */
#define WIDGET_MESSY_MAIN_WINDOW					"window1"
#define WIDGET_BIOS_IMAGE									"bios_image"
#define WIDGET_BIOS_IMAGE_BUTTON					"bios_image_button"
#define WIDGET_CARTRIDGE_IMAGE						"cartridge_image"
#define WIDGET_CARTRIDGE_IMAGE_BUTTON			"cartridge_image_button"
#define WIDGET_FLOPPY_IMAGES							"floppy_images"
#define WIDGET_FLOPPY_IMAGES_BUTTON				"floppy_images_button"
#define WIDGET_HDD_IMAGE									"hdd_image"
#define WIDGET_HDD_IMAGE_BUTTON						"hdd_image_button"
#define WIDGET_MESS_EXECUTABLE						"mess_executable"
#define WIDGET_MESS_EXECUTABLE_BUTTON			"mess_executable_button"
#define WIDGET_IMAGES_DIRECTORY						"images_directory"
#define WIDGET_IMAGES_DIRECTORY_BUTTON		"images_directory_button"
#define WIDGET_BIOS_DIRECTORY							"bios_directory"
#define WIDGET_BIOS_DIRECTORY_BUTTON			"bios_directory_button"
#define WIDGET_DISPLAY_COMMAND						"display_command"
#define WIDGET_PLAY_BUTTON								"play_button"
#define WIDGET_ABOUT_BUTTON								"about_button"
#define WIDGET_QUIT_BUTTON								"quit_button"

/* Pressed Button Assigned Number Constants */
#define NUMBER_NO_BUTTON									0
#define NUMBER_BIOS_IMAGE_BUTTON					1
#define NUMBER_CARTRIDGE_IMAGE_BUTTON			2
#define NUMBER_FLOPPY_IMAGES_BUTTON				3
#define NUMBER_HDD_IMAGE_BUTTON						4
#define NUMBER_MESS_EXECUTABLE_BUTTON			5
#define NUMBER_IMAGES_DIRECTORY_BUTTON		6
#define NUMBER_BIOS_DIRECTORY_BUTTON			7

/* About Dialog Constants */
#define MESSY_AUTHORS											"Aaron Sebold <bugs@invigorated.org>"
#define MESSY_COPYRIGHT										"(C) 2005 - 2007 Aaron Sebold"
#define MESSY_COMMENTS										"A simple frontend for the MESS emulator."
#define MESSY_HOMEPAGE										"http://mannequin.invigorated.org/messyfront/"
#define MESSY_LICENSE											"This program is free software; you can redistribute it and/or modify\nit under the terms of the GNU General Public License as published by\nthe Free Software Foundation; either version 2 of the License, or\n(at your option) any later version.\n\nThis program is distributed in the hope that it will be useful,\nbut WITHOUT ANY WARRANTY; without even the implied warranty of\nMERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the\nGNU General Public License for more details.\n\nYou should have received a copy of the GNU General Public License\nalong with this program; if not, write to:\n\nFree Software Foundation, Inc.\n59 Temple Place, Suite 330\nBoston, MA 02111-1307 USA"
#define LOGO_NAME													"messyfront96.png"

/* Other Constants */
#define BIOS_IMAGE_COMMON_EXTENSION				".zip"
#define FLOPPY_IMAGES_COMMON_SEPARATOR		", "
#define MAX_LINE_CHARACTERS								1024
#define DIR_SEP														"/"

/* Include Source File Headers */
#include "common.h"
#include "signals.h"
#include "base_buttons.h"
#include "button_common.h"
#include "messy_buttons.h"
#include "prefs.h"
