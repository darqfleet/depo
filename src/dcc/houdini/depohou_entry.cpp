#include <OP/OP_OperatorTable.h>
#include <UT/UT_DSOVersion.h>
#include "sop_node_template.h"

void newSopOperator(OP_OperatorTable* table) {
    table->addOperator(depo::hou::crateSopNodeTemplate());
}
