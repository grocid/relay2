/* main_entry.c generated by valac 0.34.4, the Vala compiler
 * generated from main_entry.vala, do not modify */

/* -*- Mode: vala; indent-tabs-mode: nil; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * main-entry.vala
 * Copyright (C) 2015 Kyle Agronick <agronick@gmail.com>
 *
 * Relay is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Relay is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <glib.h>
#include <glib-object.h>
#include <gtk/gtk.h>
#include <gee.h>
#include <stdlib.h>
#include <string.h>
#include <gdk/gdk.h>


#define TYPE_MAIN_ENTRY (main_entry_get_type ())
#define MAIN_ENTRY(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_MAIN_ENTRY, MainEntry))
#define MAIN_ENTRY_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_MAIN_ENTRY, MainEntryClass))
#define IS_MAIN_ENTRY(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_MAIN_ENTRY))
#define IS_MAIN_ENTRY_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_MAIN_ENTRY))
#define MAIN_ENTRY_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_MAIN_ENTRY, MainEntryClass))

typedef struct _MainEntry MainEntry;
typedef struct _MainEntryClass MainEntryClass;
typedef struct _MainEntryPrivate MainEntryPrivate;
#define _g_object_unref0(var) ((var == NULL) ? NULL : (var = (g_object_unref (var), NULL)))
#define _g_free0(var) (var = (g_free (var), NULL))

struct _MainEntry {
	GtkEntry parent_instance;
	MainEntryPrivate * priv;
};

struct _MainEntryClass {
	GtkEntryClass parent_class;
};

struct _MainEntryPrivate {
	gint last_pos;
	GeeArrayList* history;
};


static gpointer main_entry_parent_class = NULL;

GType main_entry_get_type (void) G_GNUC_CONST;
#define MAIN_ENTRY_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), TYPE_MAIN_ENTRY, MainEntryPrivate))
enum  {
	MAIN_ENTRY_DUMMY_PROPERTY
};
MainEntry* main_entry_new (void);
MainEntry* main_entry_construct (GType object_type);
gboolean main_entry_press_event (MainEntry* self, GdkEventKey* event);
static gboolean _main_entry_press_event_gtk_widget_key_press_event (GtkWidget* _sender, GdkEventKey* event, gpointer self);
void main_entry_do_activate (MainEntry* self);
static void _main_entry_do_activate_gtk_entry_activate (GtkEntry* _sender, gpointer self);
static void main_entry_up_arrow (MainEntry* self);
static void main_entry_down_arrow (MainEntry* self);
static void main_entry_write_history (MainEntry* self, gint index);
static void main_entry_finalize (GObject* obj);


static gboolean _main_entry_press_event_gtk_widget_key_press_event (GtkWidget* _sender, GdkEventKey* event, gpointer self) {
	gboolean result;
	result = main_entry_press_event ((MainEntry*) self, event);
	return result;
}


static void _main_entry_do_activate_gtk_entry_activate (GtkEntry* _sender, gpointer self) {
	main_entry_do_activate ((MainEntry*) self);
}


MainEntry* main_entry_construct (GType object_type) {
	MainEntry * self = NULL;
	self = (MainEntry*) g_object_new (object_type, NULL);
	g_signal_connect_object ((GtkWidget*) self, "key-press-event", (GCallback) _main_entry_press_event_gtk_widget_key_press_event, self, 0);
	g_signal_connect_object ((GtkEntry*) self, "activate", (GCallback) _main_entry_do_activate_gtk_entry_activate, self, 0);
	return self;
}


MainEntry* main_entry_new (void) {
	return main_entry_construct (TYPE_MAIN_ENTRY);
}


gboolean main_entry_press_event (MainEntry* self, GdkEventKey* event) {
	gboolean result = FALSE;
	gchar* keyval = NULL;
	GdkEventKey* _tmp0_ = NULL;
	guint _tmp1_ = 0U;
	const gchar* _tmp2_ = NULL;
	gchar* _tmp3_ = NULL;
	const gchar* _tmp4_ = NULL;
	const gchar* _tmp5_ = NULL;
	GQuark _tmp7_ = 0U;
	static GQuark _tmp6_label0 = 0;
	static GQuark _tmp6_label1 = 0;
	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (event != NULL, FALSE);
	_tmp0_ = event;
	_tmp1_ = _tmp0_->keyval;
	_tmp2_ = gdk_keyval_name (_tmp1_);
	_tmp3_ = g_strdup (_tmp2_);
	keyval = _tmp3_;
	_tmp4_ = keyval;
	_tmp5_ = _tmp4_;
	_tmp7_ = (NULL == _tmp5_) ? 0 : g_quark_from_string (_tmp5_);
	if (_tmp7_ == ((0 != _tmp6_label0) ? _tmp6_label0 : (_tmp6_label0 = g_quark_from_static_string ("Up")))) {
		switch (0) {
			default:
			{
				main_entry_up_arrow (self);
				result = TRUE;
				_g_free0 (keyval);
				return result;
				break;
			}
		}
	} else if (_tmp7_ == ((0 != _tmp6_label1) ? _tmp6_label1 : (_tmp6_label1 = g_quark_from_static_string ("Down")))) {
		switch (0) {
			default:
			{
				main_entry_down_arrow (self);
				break;
			}
		}
	}
	result = FALSE;
	_g_free0 (keyval);
	return result;
}


static void main_entry_up_arrow (MainEntry* self) {
	gint _tmp0_ = 0;
	gint _tmp6_ = 0;
	g_return_if_fail (self != NULL);
	_tmp0_ = self->priv->last_pos;
	if (_tmp0_ == -1) {
		GeeArrayList* _tmp1_ = NULL;
		gint _tmp2_ = 0;
		gint _tmp3_ = 0;
		_tmp1_ = self->priv->history;
		_tmp2_ = gee_abstract_collection_get_size ((GeeCollection*) _tmp1_);
		_tmp3_ = _tmp2_;
		self->priv->last_pos = _tmp3_ - 1;
	} else {
		gint _tmp4_ = 0;
		_tmp4_ = self->priv->last_pos;
		if (_tmp4_ == 0) {
			return;
		} else {
			gint _tmp5_ = 0;
			_tmp5_ = self->priv->last_pos;
			self->priv->last_pos = _tmp5_ - 1;
		}
	}
	_tmp6_ = self->priv->last_pos;
	main_entry_write_history (self, _tmp6_);
}


static void main_entry_down_arrow (MainEntry* self) {
	GeeArrayList* _tmp0_ = NULL;
	gint _tmp1_ = 0;
	gint _tmp2_ = 0;
	gint _tmp3_ = 0;
	gint _tmp5_ = 0;
	g_return_if_fail (self != NULL);
	_tmp0_ = self->priv->history;
	_tmp1_ = gee_abstract_collection_get_size ((GeeCollection*) _tmp0_);
	_tmp2_ = _tmp1_;
	_tmp3_ = self->priv->last_pos;
	if (_tmp2_ > (_tmp3_ + 1)) {
		gint _tmp4_ = 0;
		_tmp4_ = self->priv->last_pos;
		self->priv->last_pos = _tmp4_ + 1;
	} else {
		gtk_entry_set_text ((GtkEntry*) self, "");
		return;
	}
	_tmp5_ = self->priv->last_pos;
	main_entry_write_history (self, _tmp5_);
}


static void main_entry_write_history (MainEntry* self, gint index) {
	gboolean _tmp0_ = FALSE;
	gint _tmp1_ = 0;
	GeeArrayList* _tmp2_ = NULL;
	gint _tmp3_ = 0;
	gint _tmp4_ = 0;
	GeeArrayList* _tmp6_ = NULL;
	gint _tmp7_ = 0;
	gpointer _tmp8_ = NULL;
	gchar* _tmp9_ = NULL;
	const gchar* _tmp10_ = NULL;
	gint _tmp11_ = 0;
	gint _tmp12_ = 0;
	g_return_if_fail (self != NULL);
	_tmp1_ = index;
	_tmp2_ = self->priv->history;
	_tmp3_ = gee_abstract_collection_get_size ((GeeCollection*) _tmp2_);
	_tmp4_ = _tmp3_;
	if (_tmp1_ > _tmp4_) {
		_tmp0_ = TRUE;
	} else {
		gint _tmp5_ = 0;
		_tmp5_ = index;
		_tmp0_ = _tmp5_ < 0;
	}
	if (_tmp0_) {
		return;
	}
	_tmp6_ = self->priv->history;
	_tmp7_ = index;
	_tmp8_ = gee_abstract_list_get ((GeeAbstractList*) _tmp6_, _tmp7_);
	_tmp9_ = (gchar*) _tmp8_;
	gtk_entry_set_text ((GtkEntry*) self, _tmp9_);
	_g_free0 (_tmp9_);
	_tmp10_ = gtk_entry_get_text ((GtkEntry*) self);
	_tmp11_ = strlen (_tmp10_);
	_tmp12_ = _tmp11_;
	gtk_editable_set_position ((GtkEditable*) self, _tmp12_);
}


static gchar* string_strip (const gchar* self) {
	gchar* result = NULL;
	gchar* _result_ = NULL;
	gchar* _tmp0_ = NULL;
	const gchar* _tmp1_ = NULL;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp0_ = g_strdup (self);
	_result_ = _tmp0_;
	_tmp1_ = _result_;
	g_strstrip (_tmp1_);
	result = _result_;
	return result;
}


void main_entry_do_activate (MainEntry* self) {
	const gchar* _tmp0_ = NULL;
	gchar* _tmp1_ = NULL;
	gchar* _tmp2_ = NULL;
	gboolean _tmp3_ = FALSE;
	GeeArrayList* _tmp4_ = NULL;
	const gchar* _tmp5_ = NULL;
	g_return_if_fail (self != NULL);
	_tmp0_ = gtk_entry_get_text ((GtkEntry*) self);
	_tmp1_ = string_strip (_tmp0_);
	_tmp2_ = _tmp1_;
	_tmp3_ = g_strcmp0 (_tmp2_, "") == 0;
	_g_free0 (_tmp2_);
	if (_tmp3_) {
		return;
	}
	_tmp4_ = self->priv->history;
	_tmp5_ = gtk_entry_get_text ((GtkEntry*) self);
	gee_abstract_collection_add ((GeeAbstractCollection*) _tmp4_, _tmp5_);
	self->priv->last_pos = -1;
}


static void main_entry_class_init (MainEntryClass * klass) {
	main_entry_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (MainEntryPrivate));
	G_OBJECT_CLASS (klass)->finalize = main_entry_finalize;
}


static void main_entry_instance_init (MainEntry * self) {
	GeeArrayList* _tmp0_ = NULL;
	self->priv = MAIN_ENTRY_GET_PRIVATE (self);
	self->priv->last_pos = -1;
	_tmp0_ = gee_array_list_new (G_TYPE_STRING, (GBoxedCopyFunc) g_strdup, g_free, NULL, NULL, NULL);
	self->priv->history = _tmp0_;
}


static void main_entry_finalize (GObject* obj) {
	MainEntry * self;
	self = G_TYPE_CHECK_INSTANCE_CAST (obj, TYPE_MAIN_ENTRY, MainEntry);
	_g_object_unref0 (self->priv->history);
	G_OBJECT_CLASS (main_entry_parent_class)->finalize (obj);
}


GType main_entry_get_type (void) {
	static volatile gsize main_entry_type_id__volatile = 0;
	if (g_once_init_enter (&main_entry_type_id__volatile)) {
		static const GTypeInfo g_define_type_info = { sizeof (MainEntryClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) main_entry_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (MainEntry), 0, (GInstanceInitFunc) main_entry_instance_init, NULL };
		GType main_entry_type_id;
		main_entry_type_id = g_type_register_static (gtk_entry_get_type (), "MainEntry", &g_define_type_info, 0);
		g_once_init_leave (&main_entry_type_id__volatile, main_entry_type_id);
	}
	return main_entry_type_id__volatile;
}



