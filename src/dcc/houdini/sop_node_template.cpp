#include "sop_node_template.h"
#include "OP/OP_AutoLockInputs.h"
#include "OP/OP_Operator.h"
#include <iostream>
#include "logger.h"


using namespace depo::hou;
using namespace depo::util;
using namespace depo::core;

OP_Operator* depo::hou::crateSopNodeTemplate() {
    OP_Operator* op = new OP_Operator(
    "depo_container",
    "depoContainer",
    SOP_Node_Template::ctor,
    SOP_Node_Template::parms,
    1,1);
    op->setOpTabSubMenuPath("depo");
    return op;
}

SOP_Node_Template::SOP_Node_Template(OP_Network *net, const char *name, OP_Operator *op)
: SOP_Node(net, name, op) {
    std::cout << "ctor SopNodeTemplate" << std::endl;
}

OP_Node *SOP_Node_Template::ctor(OP_Network *net, const char *name, OP_Operator *op) {
    return new SOP_Node_Template(net, name, op);
}

static PRM_Name names[] = {
    PRM_Name{"path", "Path"}
};

PRM_Template SOP_Node_Template::parms[] = {
    PRM_Template{PRM_STRING, 1, &names[0]},
    PRM_Template{}
};

OP_ERROR SOP_Node_Template::cookMySop(OP_Context &context) {
    OP_AutoLockInputs inputs{this};
    if (inputs.lock(context) >= UT_ERROR_ABORT) {
        return error();
    }
    fpreal t{context.getTime()};
    duplicateSource(0, context);
    Logger& logger{Logger::get()};
    logger.put(LogLevel::CRITICAL, "critical from houdini");
    logger.put(LogLevel::ERROR, "error from houdini");
    logger.put(LogLevel::INFO, "info from houdini");
    logger.put(LogLevel::MESSAGE, "MESSAGE from houdini");
    logger.put(LogLevel::WARNING, "warning from houdini");
    logger.setLevel(LogLevel::DEBUG);
    logger.put(LogLevel::DEBUG, "debug from houdini");
    return error();
}

