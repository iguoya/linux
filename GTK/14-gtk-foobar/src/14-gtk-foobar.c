/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * 14-gtk-foobar.c
 * Copyright (C) 2021 tiger <tiger@loongnix>
 * 
 * 14-gtk-foobar is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * 14-gtk-foobar is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "14-gtk-foobar.h"

#include <glib/gi18n.h>



/* For testing propose use the local (not installed) ui file */
/* #define UI_FILE PACKAGE_DATA_DIR"/ui/14_gtk_foobar.ui" */
#define UI_FILE "src/14_gtk_foobar.ui"
#define TOP_WINDOW "window"


G_DEFINE_TYPE (14gtkfoobar, 14_gtk_foobar, GTK_TYPE_APPLICATION);

/* ANJUTA: Macro _14_GTK_FOOBAR_APPLICATION gets 14gtkfoobar - DO NOT REMOVE */
struct _14gtkfoobarPrivate
{
	/* ANJUTA: Widgets declaration for 14_gtk_foobar.ui - DO NOT REMOVE */
};

/* Create a new window loading a file */
static void
14_gtk_foobar_new_window (GApplication *app,
                           GFile        *file)
{
	GtkWidget *window;

	GtkBuilder *builder;
	GError* error = NULL;

	14gtkfoobarPrivate *priv = _14_GTK_FOOBAR_APPLICATION(app)->priv;

	/* Load UI from file */
	builder = gtk_builder_new ();
	if (!gtk_builder_add_from_file (builder, UI_FILE, &error))
	{
		g_critical ("Couldn't load builder file: %s", error->message);
		g_error_free (error);
	}

	/* Auto-connect signal handlers */
	gtk_builder_connect_signals (builder, app);

	/* Get the window object from the ui file */
	window = GTK_WIDGET (gtk_builder_get_object (builder, TOP_WINDOW));
        if (!window)
        {
		g_critical ("Widget \"%s\" is missing in file %s.",
				TOP_WINDOW,
				UI_FILE);
        }

	
	/* ANJUTA: Widgets initialization for 14_gtk_foobar.ui - DO NOT REMOVE */

	g_object_unref (builder);
	
	
	gtk_window_set_application (GTK_WINDOW (window), GTK_APPLICATION (app));
	if (file != NULL)
	{
		/* TODO: Add code here to open the file in the new window */
	}

	gtk_widget_show_all (GTK_WIDGET (window));
}


/* GApplication implementation */
static void
14_gtk_foobar_activate (GApplication *application)
{
	14_gtk_foobar_new_window (application, NULL);
}

static void
14_gtk_foobar_open (GApplication  *application,
                     GFile        **files,
                     gint           n_files,
                     const gchar   *hint)
{
	gint i;

	for (i = 0; i < n_files; i++)
		14_gtk_foobar_new_window (application, files[i]);
}

static void
14_gtk_foobar_init (14gtkfoobar *object)
{
	object->priv = G_TYPE_INSTANCE_GET_PRIVATE (object, _14_GTK_FOOBAR_TYPE_APPLICATION, 14gtkfoobarPrivate);
}

static void
14_gtk_foobar_finalize (GObject *object)
{
	G_OBJECT_CLASS (14_gtk_foobar_parent_class)->finalize (object);
}

static void
14_gtk_foobar_class_init (14gtkfoobarClass *klass)
{
	G_APPLICATION_CLASS (klass)->activate = 14_gtk_foobar_activate;
	G_APPLICATION_CLASS (klass)->open = 14_gtk_foobar_open;

	g_type_class_add_private (klass, sizeof (14gtkfoobarPrivate));

	G_OBJECT_CLASS (klass)->finalize = 14_gtk_foobar_finalize;
}

14gtkfoobar *
14_gtk_foobar_new (void)
{
	return g_object_new (14_gtk_foobar_get_type (),
	                     "application-id", "org.gnome.14_gtk_foobar",
	                     "flags", G_APPLICATION_HANDLES_OPEN,
	                     NULL);
}

