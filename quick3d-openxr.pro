requires(qtHaveModule(quick3d-private))

load(qt_parts)

TEMPLATE = subdirs
SUBDIRS += src examples
src.subdir = src
examples.subdir = examples

examples.depends = src
