
// include this file after calling the SIM_PLUGIN(...) macro

void subscribe(SScriptCallBack *p, const char *cmd, subscribe_in *in, subscribe_out *out)
{
    sim::plugin->subscribe(in, out);
}
void shutdownSubscriber(SScriptCallBack *p, const char *cmd, shutdownSubscriber_in *in, shutdownSubscriber_out *out)
{
    sim::plugin->shutdownSubscriber(in, out);
}
void subscriberTreatUInt8ArrayAsString(SScriptCallBack *p, const char *cmd, subscriberTreatUInt8ArrayAsString_in *in, subscriberTreatUInt8ArrayAsString_out *out)
{
    sim::plugin->subscriberTreatUInt8ArrayAsString(in, out);
}
void advertise(SScriptCallBack *p, const char *cmd, advertise_in *in, advertise_out *out)
{
    sim::plugin->advertise(in, out);
}
void shutdownPublisher(SScriptCallBack *p, const char *cmd, shutdownPublisher_in *in, shutdownPublisher_out *out)
{
    sim::plugin->shutdownPublisher(in, out);
}
void publisherTreatUInt8ArrayAsString(SScriptCallBack *p, const char *cmd, publisherTreatUInt8ArrayAsString_in *in, publisherTreatUInt8ArrayAsString_out *out)
{
    sim::plugin->publisherTreatUInt8ArrayAsString(in, out);
}
void publish(SScriptCallBack *p, const char *cmd, publish_in *in, publish_out *out)
{
    sim::plugin->publish(in, out);
}
void serviceClient(SScriptCallBack *p, const char *cmd, serviceClient_in *in, serviceClient_out *out)
{
    sim::plugin->serviceClient(in, out);
}
void shutdownServiceClient(SScriptCallBack *p, const char *cmd, shutdownServiceClient_in *in, shutdownServiceClient_out *out)
{
    sim::plugin->shutdownServiceClient(in, out);
}
void serviceClientTreatUInt8ArrayAsString(SScriptCallBack *p, const char *cmd, serviceClientTreatUInt8ArrayAsString_in *in, serviceClientTreatUInt8ArrayAsString_out *out)
{
    sim::plugin->serviceClientTreatUInt8ArrayAsString(in, out);
}
void call(SScriptCallBack *p, const char *cmd, call_in *in, call_out *out)
{
    sim::plugin->call(in, out);
}
void advertiseService(SScriptCallBack *p, const char *cmd, advertiseService_in *in, advertiseService_out *out)
{
    sim::plugin->advertiseService(in, out);
}
void shutdownServiceServer(SScriptCallBack *p, const char *cmd, shutdownServiceServer_in *in, shutdownServiceServer_out *out)
{
    sim::plugin->shutdownServiceServer(in, out);
}
void serviceServerTreatUInt8ArrayAsString(SScriptCallBack *p, const char *cmd, serviceServerTreatUInt8ArrayAsString_in *in, serviceServerTreatUInt8ArrayAsString_out *out)
{
    sim::plugin->serviceServerTreatUInt8ArrayAsString(in, out);
}
void sendTransform(SScriptCallBack *p, const char *cmd, sendTransform_in *in, sendTransform_out *out)
{
    sim::plugin->sendTransform(in, out);
}
void sendTransforms(SScriptCallBack *p, const char *cmd, sendTransforms_in *in, sendTransforms_out *out)
{
    sim::plugin->sendTransforms(in, out);
}
void imageTransportSubscribe(SScriptCallBack *p, const char *cmd, imageTransportSubscribe_in *in, imageTransportSubscribe_out *out)
{
    sim::plugin->imageTransportSubscribe(in, out);
}
void imageTransportShutdownSubscriber(SScriptCallBack *p, const char *cmd, imageTransportShutdownSubscriber_in *in, imageTransportShutdownSubscriber_out *out)
{
    sim::plugin->imageTransportShutdownSubscriber(in, out);
}
void imageTransportAdvertise(SScriptCallBack *p, const char *cmd, imageTransportAdvertise_in *in, imageTransportAdvertise_out *out)
{
    sim::plugin->imageTransportAdvertise(in, out);
}
void imageTransportShutdownPublisher(SScriptCallBack *p, const char *cmd, imageTransportShutdownPublisher_in *in, imageTransportShutdownPublisher_out *out)
{
    sim::plugin->imageTransportShutdownPublisher(in, out);
}
void imageTransportPublish(SScriptCallBack *p, const char *cmd, imageTransportPublish_in *in, imageTransportPublish_out *out)
{
    sim::plugin->imageTransportPublish(in, out);
}
void getTime(SScriptCallBack *p, const char *cmd, getTime_in *in, getTime_out *out)
{
    sim::plugin->getTime(in, out);
}
void getParamString(SScriptCallBack *p, const char *cmd, getParamString_in *in, getParamString_out *out)
{
    sim::plugin->getParamString(in, out);
}
void getParamInt(SScriptCallBack *p, const char *cmd, getParamInt_in *in, getParamInt_out *out)
{
    sim::plugin->getParamInt(in, out);
}
void getParamDouble(SScriptCallBack *p, const char *cmd, getParamDouble_in *in, getParamDouble_out *out)
{
    sim::plugin->getParamDouble(in, out);
}
void getParamBool(SScriptCallBack *p, const char *cmd, getParamBool_in *in, getParamBool_out *out)
{
    sim::plugin->getParamBool(in, out);
}
void setParamString(SScriptCallBack *p, const char *cmd, setParamString_in *in, setParamString_out *out)
{
    sim::plugin->setParamString(in, out);
}
void setParamInt(SScriptCallBack *p, const char *cmd, setParamInt_in *in, setParamInt_out *out)
{
    sim::plugin->setParamInt(in, out);
}
void setParamDouble(SScriptCallBack *p, const char *cmd, setParamDouble_in *in, setParamDouble_out *out)
{
    sim::plugin->setParamDouble(in, out);
}
void setParamBool(SScriptCallBack *p, const char *cmd, setParamBool_in *in, setParamBool_out *out)
{
    sim::plugin->setParamBool(in, out);
}
void hasParam(SScriptCallBack *p, const char *cmd, hasParam_in *in, hasParam_out *out)
{
    sim::plugin->hasParam(in, out);
}
void deleteParam(SScriptCallBack *p, const char *cmd, deleteParam_in *in, deleteParam_out *out)
{
    sim::plugin->deleteParam(in, out);
}
void searchParam(SScriptCallBack *p, const char *cmd, searchParam_in *in, searchParam_out *out)
{
    sim::plugin->searchParam(in, out);
}

