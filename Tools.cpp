//
// Created by ita on 25/09/17.
//

#include "Tools.h"


explicit Tools::Tools(toolType cat): category(cat){
    std::string details;
    switch(category){
        case(toolType::medicine):
            details="Potrei usarlo per alleviare il dolore";
            break;

        case(toolType::key):
            details="Sembra una chiave antica..";
            break;

        case(toolType::message):
            details="All'interno sembra esserci scritto qualcosa";
            break;

        case(toolType::torch):
            details="Puo' essere accesa per fare luce!";
            break;
    }
    Tools::description=details;
}

