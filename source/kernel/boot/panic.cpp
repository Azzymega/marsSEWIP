#include "include/panic.hpp"

PanicController::PanicController(Console *DebugScreen) {
  this->DebugScreen = DebugScreen;
}

PanicController *PanicController::LoadResolve(PanicMessage *Object) {
  this->DebugScreen->LoadResolve(Object->Message);
  return nullptr;
}

PanicMessage::PanicMessage(const char *Text, PanicType Type) {
  this->Message = Text;
  this->Type = Type;
}

PanicMessage::PanicMessage(const char *Text) { this->Message = Text; }
