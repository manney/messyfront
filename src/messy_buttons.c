/*****************************************************************************
 *                                                                           *
 *   MessyFront - messy_buttons.c                                            *
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

void on_bios_image_button_clicked (GtkWidget *widget, PREFS *images)
{
	/* Sets the images->button_pushed flag to NUMBER_BIOS_IMAGE_BUTTON */
	images->button_pushed = NUMBER_BIOS_IMAGE_BUTTON;
}

void on_cartridge_image_button_clicked (GtkWidget *widget, PREFS *images)
{
	/* Sets the images->button_pushed flag to NUMBER_CARTRIDGE_IMAGE_BUTTON */
	images->button_pushed = NUMBER_CARTRIDGE_IMAGE_BUTTON;

}

void on_floppy_images_button_clicked (GtkWidget *widget, PREFS *images)
{
	/* Sets the images->button_pushed flag to NUMBER_FLOPPY_IMAGES_BUTTON */
	images->button_pushed = NUMBER_FLOPPY_IMAGES_BUTTON;
}

void on_hdd_image_button_clicked (GtkWidget *widget, PREFS *images)
{
	/* Sets the images->button_pushed flag to NUMBER_HDD_IMAGE_BUTTON */
	images->button_pushed = NUMBER_HDD_IMAGE_BUTTON;
}

void on_mess_executable_button_clicked (GtkWidget *widget, PREFS *images)
{
	/* Sets the images->button_pushed flag to NUMBER_MESS_EXECUTABLE_BUTTON */
	images->button_pushed = NUMBER_MESS_EXECUTABLE_BUTTON;
}

void on_images_directory_button_clicked (GtkWidget *widget, PREFS *images)
{
	/* Sets the images->button_pushed flag to NUMBER_IMAGES_DIRECTORY_BUTTON */
	images->button_pushed = NUMBER_IMAGES_DIRECTORY_BUTTON;
}

void on_bios_directory_button_clicked (GtkWidget *widget, PREFS *images)
{
	/* Sets the images->button_pushed flag to NUMBER_BIOS_DIRECTORY_BUTTON */
	images->button_pushed = NUMBER_BIOS_DIRECTORY_BUTTON;
}
