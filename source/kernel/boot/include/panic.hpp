#pragma once
#include "../../ng.hpp"
#include "../../console/include/console.hpp"

enum PanicType {
    LoadingError = 0x1
};

struct PanicMessage {
    const char* Message;
    PanicType Type;
    PanicMessage(const char* Text, PanicType);
    PanicMessage(const char* Text);
};

struct PanicController : LoadContradiction<PanicController*, PanicMessage*>{
    Console* DebugScreen;
    PanicController(Console* DebugScreen);
    PanicController * LoadResolve(PanicMessage *Object) override;
};
