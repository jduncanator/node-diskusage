#include "diskusage.h"

#include <nan.h>
#include <stdexcept>

static v8::Local<v8::Object> ConvertDiskUsage(const DiskUsage& usage)
{
    v8::Local<v8::Object> obj = Nan::New<v8::Object>();
    obj->Set(Nan::New<v8::String>("available").ToLocalChecked(), Nan::New<v8::Number>(usage.available));
    obj->Set(Nan::New<v8::String>("free").ToLocalChecked(), Nan::New<v8::Number>(usage.free));
    obj->Set(Nan::New<v8::String>("total").ToLocalChecked(), Nan::New<v8::Number>(usage.total));

    return obj;
}

static v8::Local<v8::Value> ConvertSystemError(const SystemError& error)
{
    return Nan::ErrnoException(error.errorno(), error.syscall(), error.message(), error.path());
}

static NAN_METHOD(GetDiskUsage)
{
    Nan::HandleScope scope;

    try {
        DiskUsage result = GetDiskUsage(*v8::String::Utf8Value(info[0]));
        info.GetReturnValue().Set(ConvertDiskUsage(result));
    }
    catch (const SystemError &error) {
        Nan::ThrowError(ConvertSystemError(error));
    }
    catch (const std::exception &ex) {
        Nan::ThrowError(ex.what());
    }
}

void Init(v8::Handle<v8::Object> exports)
{
    Nan::SetMethod(exports, "getDiskUsage", GetDiskUsage);
}

NODE_MODULE(diskusage, Init)
