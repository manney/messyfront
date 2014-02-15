/*****************************************************************************
 *                                                                           *
 *   MessyFront - common.h                                                   *
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

/* Function Prototypes */
void change_window_name (PREFS *images, gchar *window_name);
void change_window_icon (PREFS *images, gchar *icon);
void populate_object_from_fields (PREFS *images);
void populate_fields_from_object (PREFS *images);
void common_message_dialog (char *message);
char *lefts (char *dest, gchar *source, int noc);
char *rights (char *dest, gchar *source, int noc);
