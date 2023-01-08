#pragma once
#include <QObject>

#include "Extras/Export/export.h"
#include "QtCore/QObject/qobject_macro.h"
#include "napi.h"

class NHotkey : public QHotkey, public EventWidget {
  Q_OBJECT
  EVENTWIDGET_IMPLEMENTATIONS(QHotkey)
 public:
  using QHotkey::QHotkey;

  virtual void connectSignalsToEventEmitter() {
    QOBJECT_SIGNALS
    QObject::connect(this, &QHotkey::activated, [=]() {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({Napi::String::New(env, "activated")});
    });
    QObject::connect(this, &QHotkey::released, [=]() {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({Napi::String::New(env, "released")});
    });
  }
};
