// Pegasus Frontend
// Copyright (C) 2017-2019  Mátyás Mustoha
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.


#include "Api.h"

#include "parser/Parser.h"


namespace {
void build_qml_layer(parser::Entries& data, Api& api)
{
#define GENERATE(type, field) \
    { \
        QVector<model::type*> new_##field; \
        new_##field.reserve(static_cast<int>(data.field.size())); \
        \
        for (modeldata::type& dataitem : data.field) \
            new_##field.append(new model::type(std::move(dataitem))); \
        \
        api.field()->clear(); \
        api.field()->append(new_##field); \
    }

    GENERATE(Collection, collections)
    GENERATE(Game, games)

#undef GENERATE
}
} // namespace


Api::Api(QObject* parent)
    : QObject(parent)
{
}

void Api::openFile(QString path)
{
    QStringList errors;

    const auto render_line_error = [&errors](const size_t linenum, const QString& message) {
        errors += QStringLiteral("Line %1: %2").arg(QString::number(linenum), message);
    };


    parser::Entries parsed;
    const bool success = parser::parse(path, parsed, render_line_error);
    if (!success)
        m_error_log = QStringLiteral("Error: Could not open the file");

    m_error_log = errors.join(QChar('\n'));
    emit errorLogChanged();

    if (!m_error_log.isEmpty())
        qWarning().noquote() << m_error_log;

    if (success)
        build_qml_layer(parsed, *this);
}