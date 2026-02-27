# Qt + QxOrm Example Project

This repository contains a Qt application that uses QxOrm for object-relational mapping.

## Project Structure

- **qtApp** – Qt QML application
- **cpp_model / cpp_view_model** – generated ORM and view models (not stored in git)
- **QxOrm** – ORM framework (provided separately)
- **.qxee** – Qx Entity Editor project file (used to generate models)

## Generating Models

The model code is generated using:

**Qx Entity Editor (.qxee file)**

To generate models:

1. Open Qx Entity Editor
2. Load project file:
3. In Qx Entity Editor:
- Select all entities
- Click EXPORT -> export to.. cpp project, cpp model/view project, DDL SQL script file
4. Generated code will appear in:
- cpp_model
- cpp_view_model
- other generated directories (not committed to git)

⚠️ Generated code is not stored in this repository. You must regenerate it after cloning.

## Building

After generation:

```bash
cmake ..
cmake --build .
