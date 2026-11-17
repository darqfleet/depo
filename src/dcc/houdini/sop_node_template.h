#pragma once
#include "SOP/SOP_Node.h"


namespace depo::hou {
    OP_Operator* crateSopNodeTemplate();
    class SOP_Node_Template : SOP_Node {
    public:
        static OP_Node* ctor(OP_Network* net, const char* name, OP_Operator* op);
        static PRM_Template parms[];
        SOP_Node_Template(OP_Network* net, const char* name, OP_Operator* op);
        ~SOP_Node_Template() = default;
        OP_ERROR cookMySop(OP_Context &context) override;

    };
}


