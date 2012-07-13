/**************************************************************************
**
** This file is part of Qt Creator
**
** Copyright (c) 2012 Nokia Corporation and/or its subsidiary(-ies).
**
** Contact: http://www.qt-project.org/
**
**
** GNU Lesser General Public License Usage
**
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this file.
** Please review the following information to ensure the GNU Lesser General
** Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** Other Usage
**
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**************************************************************************/

#ifndef REMOTEHELPFILTER_H
#define REMOTEHELPFILTER_H

#include "ui_remotehelpfilter.h"

#include <locator/ilocatorfilter.h>

#include <QIcon>

namespace Help {
    namespace Internal {

class RemoteHelpFilter : public Locator::ILocatorFilter
{
    Q_OBJECT
public:
    RemoteHelpFilter();
    ~RemoteHelpFilter();

    // ILocatorFilter
    QString displayName() const;
    QString id() const;
    Priority priority() const;
    QList<Locator::FilterEntry> matchesFor(QFutureInterface<Locator::FilterEntry> &future, const QString &entry);
    void accept(Locator::FilterEntry selection) const;
    void refresh(QFutureInterface<void> &future);
    QByteArray saveState() const;
    bool restoreState(const QByteArray &state);
    bool openConfigDialog(QWidget *parent, bool &needsRefresh);

    QStringList remoteUrls() const { return m_remoteUrls; }

signals:
    void linkActivated(const QUrl &url) const;

private:
    QIcon m_icon;
    QStringList m_remoteUrls;
};

class RemoteFilterOptions : public QDialog
{
    Q_OBJECT
    friend class RemoteHelpFilter;

public:
    explicit RemoteFilterOptions(RemoteHelpFilter *filter, QWidget *parent = 0);

private slots:
    void addNewItem();
    void removeItem();
    void updateRemoveButton();

private:
    RemoteHelpFilter *m_filter;
    Ui::RemoteFilterOptions m_ui;
};

    } // namespace Internal
} // namespace Help

#endif // REMOTEHELPFILTER_H
