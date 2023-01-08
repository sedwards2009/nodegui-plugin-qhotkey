#include "QHotkey_wrap.h"

#include "Extras/Utils/nutils.h"
#include "QtCore/QObject/qobject_macro.h"
#include "QtGui/QKeySequence/qkeysequence_wrap.h"

Napi::FunctionReference QHotkeyWrap::constructor;

Napi::Object QHotkeyWrap::init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);
  char CLASSNAME[] = "QHotkey";
  Napi::Function func = DefineClass(
      env, CLASSNAME,
      {InstanceMethod("isRegistered", &QHotkeyWrap::isRegistered),
        InstanceMethod("setRegistered", &QHotkeyWrap::setRegistered),
        QOBJECT_WRAPPED_METHODS_EXPORT_DEFINE(QHotkeyWrap)
       });
  constructor = Napi::Persistent(func);
  exports.Set(CLASSNAME, func);
  QOBJECT_REGISTER_WRAPPER(QHotkey, QHotkeyWrap);
  return exports;
}

QHotkey* QHotkeyWrap::getInternalInstance() {
  return this->instance;
}

QHotkeyWrap::QHotkeyWrap(const Napi::CallbackInfo& info)
    : Napi::ObjectWrap<QHotkeyWrap>(info) {
  Napi::Env env = info.Env();

  if (info.Length() == 2) {
    // args: QKeySequence, autoRegister boolean
    Napi::Object shortcutSequence = info[0].As<Napi::Object>();
    QKeySequenceWrap* keysequence =
        Napi::ObjectWrap<QKeySequenceWrap>::Unwrap(shortcutSequence);
    Napi::Boolean autoRegister = info[1].As<Napi::Boolean>();
    this->instance = new NHotkey(*keysequence->getInternalInstance(), autoRegister);
  } else {
    // args: Qt::Key, Qt::KeyboardModifiers, autoRegister boolean
    uint32_t keyCode = info[0].As<Napi::Number>().Uint32Value();
    uint32_t modifiers = info[1].As<Napi::Number>().Uint32Value();
    Napi::Boolean autoRegister = info[2].As<Napi::Boolean>();
    this->instance = new NHotkey(static_cast<Qt::Key>(keyCode),
      static_cast<Qt::KeyboardModifiers>(modifiers), autoRegister);
  }

  this->rawData = extrautils::configureComponent(this->getInternalInstance());
}

QHotkeyWrap::~QHotkeyWrap() {
  if (!this->instance.isNull()) {
    delete this->instance;
  }
}

Napi::Value QHotkeyWrap::isRegistered(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  return Napi::Value::From(env, this->instance->isRegistered());
}

Napi::Value QHotkeyWrap::setRegistered(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::Boolean registered = info[0].As<Napi::Boolean>();
  return Napi::Value::From(env, this->instance->setRegistered(registered));
}
