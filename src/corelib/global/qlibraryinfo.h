// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#ifndef QLIBRARYINFO_H
#define QLIBRARYINFO_H

#if defined(__cplusplus)
#include <QtCore/qstring.h>
#include <QtCore/qdatetime.h>
#include <QtCore/qversionnumber.h>
#else
#include <QtCore/qglobal.h>
#endif

QT_BEGIN_NAMESPACE

#if defined(__cplusplus)

class Q_CORE_EXPORT QLibraryInfo
{
public:
    static const char *build() noexcept;

    [[nodiscard]] static bool isDebugBuild() noexcept Q_DECL_CONST_FUNCTION;
    [[nodiscard]] static bool isSharedBuild() noexcept Q_DECL_CONST_FUNCTION;

#ifndef QT_BOOTSTRAPPED
    static QVersionNumber version() noexcept Q_DECL_CONST_FUNCTION;
#endif

    enum LibraryPath {
        PrefixPath = 0,
        DocumentationPath,
        HeadersPath,
        LibrariesPath,
        LibraryExecutablesPath,
        BinariesPath,
        PluginsPath,
        QmlImportsPath,
        Qml2ImportsPath = QmlImportsPath,
        ArchDataPath,
        DataPath,
        TranslationsPath,
        ExamplesPath,
        TestsPath,
        // Insert new values above this line
        // Please read the comments in qconfig.cpp.in before adding
        SettingsPath = 100
    };
    static QString path(LibraryPath p);
#if QT_DEPRECATED_SINCE(6, 0)
    using LibraryLocation = LibraryPath;
    QT_DEPRECATED_VERSION_X_6_0("Use path()")
    static QString location(LibraryLocation location)
    { return path(location); }
#endif
    static QStringList platformPluginArguments(const QString &platformName);

private:
    QLibraryInfo();
};

#if QT_DEPRECATED_SINCE(6, 9)

QT_DEPRECATED_VERSION_X_6_9("Use QLibraryInfo::isSharedBuild() instead.")
Q_CORE_EXPORT Q_DECL_CONST_FUNCTION bool qSharedBuild() noexcept;

#endif

#endif // __cplusplus

/*
 * If we're compiling C++ code:
 *  - and this is a non-namespace build, declare qVersion as extern "C"
 *  - and this is a namespace build, declare it as a regular function
 *    (we're already inside QT_BEGIN_NAMESPACE / QT_END_NAMESPACE)
 * If we're compiling C code, simply declare the function. If Qt was compiled
 * in a namespace, qVersion isn't callable anyway.
 */
#if !defined(QT_NAMESPACE) && defined(__cplusplus) && !defined(Q_QDOC)
extern "C"
#endif
Q_CORE_EXPORT Q_DECL_CONST_FUNCTION const char *qVersion(void) Q_DECL_NOEXCEPT;

QT_END_NAMESPACE

#endif // QLIBRARYINFO_H
