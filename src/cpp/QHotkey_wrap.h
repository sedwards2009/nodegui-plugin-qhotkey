#pragma once

//#include <napi.h>
#include "Extras/Utils/nutils.h"
// ^ FIXME: For some reason napi.h and nutils.h don't link ok on MSVC when used together.

#include "qhotkey.h"
#include "QtCore/QObject/qobject_macro.h"
#include "nhotkey.hpp"

class DLL_EXPORT QHotkeyWrap : public Napi::ObjectWrap<QHotkeyWrap> {
  QOBJECT_WRAPPED_METHODS_DECLARATION

 private:
  QPointer<QHotkey> instance;

 public:
  static Napi::FunctionReference constructor;
  static Napi::Object init(Napi::Env env, Napi::Object exports);
  QHotkeyWrap(const Napi::CallbackInfo& info);
  ~QHotkeyWrap();

  QHotkey* getInternalInstance();

  // Wrapped methods
  Napi::Value isRegistered(const Napi::CallbackInfo& info);
  Napi::Value setRegistered(const Napi::CallbackInfo& info);
};
