INCLUDES = \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\"\
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\"\
	@PACKAGE_CFLAGS@

AM_CFLAGS = \
	-Wall\
	-DINSTALL_PREFIX=\"$(prefix)\"

bin_PROGRAMS = \
	messyfront

EXTRA_DIST = \
	$(messyfrontglade_DATA)

messyfrontgladedir = \
	$(prefix)/share/messyfront/glade

messyfrontglade_DATA = \
	messyfront.glade

messyfront_LDADD = \
	@PACKAGE_LIBS@

messyfront_SOURCES = \
	base_buttons.c\
	base_buttons.h\
	button_common.c\
	button_common.h\
	common.c\
	common.h\
	main.c\
	messy.h\
	messy_buttons.c\
	messy_buttons.h\
	prefs.c\
	prefs.h\
	signals.c\
	signals.h

