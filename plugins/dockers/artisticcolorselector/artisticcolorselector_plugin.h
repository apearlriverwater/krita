/*
 *  Copyright (c) 2009 Cyrille Berger <cberger@cberger.net>
 *
 *  This library is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation; version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#ifndef H_ARTISTIC_COLOR_SELECTOR_PLUGIN_H
#define H_ARTISTIC_COLOR_SELECTOR_PLUGIN_H

#include <QObject>
#include <QVariant>

class ArtisticColorSelectorPlugin: public QObject
{
public:
    ArtisticColorSelectorPlugin(QObject *parent, const QVariantList &);
};

#endif // H_ARTISTIC_COLOR_SELECTOR_PLUGIN_H
