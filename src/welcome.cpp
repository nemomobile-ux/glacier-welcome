/*
 * Copyright (C) 2022 Chupligin Sergey <neochapay@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "welcome.h"
#include <QDBusPendingCall>
#include <QDBusVariant>
#include <QFile>
#include <QDebug>
#include <QStandardPaths>

Welcome::Welcome()
{
    QFile doneFile(QStandardPaths::writableLocation(QStandardPaths::HomeLocation)+"/.glacerWelcomeDone");
    m_needToStart = !doneFile.exists();
    qDebug() << QStandardPaths::writableLocation(QStandardPaths::HomeLocation)+"/.glacerWelcomeDone";
    m_mceDbus = new QDBusInterface("com.nokia.mce", "/com/nokia/mce/request", "com.nokia.mce.request", QDBusConnection::systemBus());
}

bool Welcome::isFirstRun()
{
    return m_needToStart;
}

void Welcome::startWelcome()
{
    m_mceDbus->asyncCall("set_config", QDBusObjectPath("/system/osso/dsm/display/inhibit_blank_mode").path(), QVariant::fromValue(QDBusVariant(3)));
    m_mceDbus->asyncCall("req_tklock_mode_change", "unlocked");
    m_mceDbus->asyncCall("set_config", QDBusObjectPath("/system/osso/dsm/locks/tklock_blank_disable").path(), QVariant::fromValue(QDBusVariant(1)));
}

void Welcome::endWelcome()
{
    m_mceDbus->asyncCall("set_config", QDBusObjectPath("/system/osso/dsm/display/inhibit_blank_mode").path(), QVariant::fromValue(QDBusVariant(0)));
    m_mceDbus->asyncCall("req_tklock_mode_change", "locked");
    m_mceDbus->asyncCall("set_config", QDBusObjectPath("/system/osso/dsm/locks/tklock_blank_disable").path(), QVariant::fromValue(QDBusVariant(0)));

    QFile doneFile(QStandardPaths::writableLocation(QStandardPaths::HomeLocation)+"/.glacerWelcomeDone");
    doneFile.open(QIODevice::WriteOnly);
    doneFile.close();
}
