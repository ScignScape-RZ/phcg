
PROJECT_NAME = rz-ngml


include(../build-group.pri)

INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR $$RZ_CORE_SRC_GROUP_DIR $$RZ_ROOT_SRC_DIR

INCLUDEPATH += $$SRC_ROOT_DIR

message($$SRC_ROOT_DIR)

message(SRC_ROOT_DIR)

DEFINES += CAON_DEBUG
DEFINES += RELAE_LABEL_NODES

DEFINES += USE_RZNS


HEADERS += \
 $$SRC_DIR/kernel/rz-ngml-dominion.h \
 $$SRC_DIR/kernel/rz-ngml-root.h \
 $$SRC_DIR/kernel/document/rz-ngml-document.h \
 $$SRC_DIR/kernel/document/rz-ngml-document-info.h \
 $$SRC_DIR/kernel/document/rz-ngml-document-light-xml.h \
 $$SRC_DIR/kernel/document/rz-ngml-folder.h \
 $$SRC_DIR/kernel/dominion/connectors.h \
 $$SRC_DIR/kernel/dominion/types.h \
 $$SRC_DIR/kernel/frame/rz-ngml-frame.h \
 $$SRC_DIR/kernel/grammar/rz-ngml-grammar.h \
 $$SRC_DIR/kernel/grammar/rz-ngml-graph-build.h \
 $$SRC_DIR/kernel/grammar/rz-ngml-parser.h \
 $$SRC_DIR/kernel/grammar/rz-ngml-parsing-mode.h \
 $$SRC_DIR/kernel/grammar/rz-ngml-parse-context.h \
 $$SRC_DIR/kernel/graph/rz-ngml-graph.h \
 $$SRC_DIR/kernel/graph/rz-ngml-node.h \
 $$SRC_DIR/kernel/graph/rz-ngml-markup-position.h \
 $$SRC_DIR/kernel/query/rz-ngml-query.h \
 $$SRC_DIR/kernel/output/rz-ngml-connection-descriptor.h \
 $$SRC_DIR/kernel/output/rz-ngml-output-bundle.h \
 $$SRC_DIR/tile/rz-ngml-token.h \
 $$SRC_DIR/tile/rz-ngml-tile.h \
 $$SRC_DIR/tile/rz-ngml-attribute-tile.h \
 $$SRC_DIR/tile/rz-ngml-paralex-tile.h \
 $$SRC_DIR/annotation/rz-ngml-annotation-tile.h \
 $$SRC_DIR/annotation/rz-ngml-annotation-filter.h \
 $$SRC_DIR/tag-command/rz-ngml-tag-command.h \
 $$SRC_DIR/tag-command/rz-ngml-command-callback.h \
 $$SRC_DIR/output/rz-ngml-output-base.h \
 $$SRC_DIR/output/rz-ngml-output-event-handler.h \
 $$SRC_DIR/output/rz-ngml-output-event-generator.h \
 $$SRC_DIR/output/rz-ngml-output-latex.h \
 $$SRC_DIR/output/rz-ngml-output-html.callbacks.h \
 $$SRC_DIR/output/rz-ngml-output-latex.callbacks.h \
 $$SRC_DIR/output/rz-ngml-output-html.h \
 $$SRC_DIR/output/rz-ngml-output-xml.h \
 $$SRC_DIR/output/rz-ngml-output-khif.h \
 $$SRC_DIR/whitespace/rz-ngml-whitespace.h \
 $$SRC_DIR/whitespace/rz-ngml-whitespace-holder.h \




SOURCES += \
 $$SRC_DIR/kernel/rz-ngml-dominion.cpp \
 $$SRC_DIR/kernel/document/rz-ngml-document.cpp \
 $$SRC_DIR/kernel/document/rz-ngml-document-info.cpp \
 $$SRC_DIR/kernel/document/rz-ngml-document-light-xml.cpp \
 $$SRC_DIR/kernel/document/rz-ngml-folder.cpp \
 $$SRC_DIR/kernel/frame/rz-ngml-frame.cpp \
 $$SRC_DIR/kernel/grammar/rz-ngml-grammar.cpp \
 $$SRC_DIR/kernel/grammar/rz-ngml-graph-build.cpp \
 $$SRC_DIR/kernel/grammar/rz-ngml-parser.cpp \
 $$SRC_DIR/kernel/grammar/rz-ngml-parse-context.cpp \
 $$SRC_DIR/kernel/graph/rz-ngml-graph.cpp \
 $$SRC_DIR/kernel/graph/rz-ngml-node.cpp \
 $$SRC_DIR/kernel/graph/rz-ngml-markup-position.cpp \
 $$SRC_DIR/kernel/query/rz-ngml-query.cpp \
 $$SRC_DIR/kernel/output/rz-ngml-connection-descriptor.cpp \
 $$SRC_DIR/kernel/output/rz-ngml-output-bundle.cpp \
 $$SRC_DIR/tile/rz-ngml-token.cpp \
 $$SRC_DIR/tile/rz-ngml-tile.cpp \
 $$SRC_DIR/tile/rz-ngml-attribute-tile.cpp \
 $$SRC_DIR/tile/rz-ngml-paralex-tile.cpp \
 $$SRC_DIR/annotation/rz-ngml-annotation-tile.cpp \
 $$SRC_DIR/annotation/rz-ngml-annotation-filter.cpp \
 $$SRC_DIR/tag-command/rz-ngml-tag-command.cpp \
 $$SRC_DIR/tag-command/rz-ngml-command-callback.cpp \
 $$SRC_DIR/output/rz-ngml-output-base.cpp \
 $$SRC_DIR/output/rz-ngml-output-event-handler.cpp \
 $$SRC_DIR/output/rz-ngml-output-event-generator.cpp \
 $$SRC_DIR/output/rz-ngml-output-html.cpp \
 $$SRC_DIR/output/rz-ngml-output-xml.cpp \
 $$SRC_DIR/output/rz-ngml-output-latex.cpp \
 $$SRC_DIR/output/rz-ngml-output-khif.cpp \
 $$SRC_DIR/whitespace/rz-ngml-whitespace.cpp \
 $$SRC_DIR/whitespace/rz-ngml-whitespace-holder.cpp \

