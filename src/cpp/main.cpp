#include <napi.h>

#include "QHotkey_wrap.h"


Napi::Object Main(Napi::Env env, Napi::Object exports) {
  QHotkeyWrap::init(env, exports);
  return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Main)
