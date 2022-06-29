#ifndef STUBS_H__INCLUDED
#define STUBS_H__INCLUDED

#include <simPlusPlus/Lib.h>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/format.hpp>
#include <boost/optional.hpp>

class FuncTracer
{
    int l_;
    std::string f_;
public:
    FuncTracer(const std::string &f, int l = sim_verbosity_trace);
    ~FuncTracer();
};

#ifndef __FUNC__
#ifdef __PRETTY_FUNCTION__
#define __FUNC__ __PRETTY_FUNCTION__
#else
#define __FUNC__ __func__
#endif
#endif // __FUNC__

#define TRACE_FUNC FuncTracer __funcTracer__##__LINE__((boost::format("%s:%d:%s:") % __FILE__ % __LINE__ % __FUNC__).str())

#ifdef QT_COMPIL
#include <QThread>

extern Qt::HANDLE UI_THREAD;
extern Qt::HANDLE SIM_THREAD;

std::string threadNickname();
void uiThread();
void simThread();

#define ASSERT_THREAD(ID) \
    if(UI_THREAD == NULL) {\
        sim::addLog(sim_verbosity_debug, "warning: cannot check ASSERT_THREAD(" #ID ") because global variable UI_THREAD is not set yet.");\
    } else if(strcmp(#ID, "UI") == 0) {\
        if(QThread::currentThreadId() != UI_THREAD) {\
            sim::addLog(sim_verbosity_errors, "%s:%d %s should be called from UI thread", __FILE__, __LINE__, __FUNC__);\
            exit(1);\
        }\
    } else if(strcmp(#ID, "!UI") == 0) {\
        if(QThread::currentThreadId() == UI_THREAD) {\
            sim::addLog(sim_verbosity_errors, "%s:%d %s should NOT be called from UI thread", __FILE__, __LINE__, __FUNC__);\
            exit(1);\
        }\
    } else {\
        sim::addLog(sim_verbosity_debug, "warning: cannot check ASSERT_THREAD(" #ID "). Can check only UI and !UI.");\
    }
#endif // QT_COMPIL

template<typename T>
struct Grid
{
    std::vector<int> dims;
    std::vector<T> data;
};

struct ReadOptions
{
    std::vector<size_t> minSize;
    std::vector<size_t> maxSize;

    ReadOptions& setBounds(size_t dim, size_t minSize_, size_t maxSize_)
    {
        while(minSize.size() <= dim) minSize.push_back(0);
        while(maxSize.size() <= dim) maxSize.push_back(std::numeric_limits<size_t>::max());
        minSize[dim] = minSize_;
        maxSize[dim] = maxSize_;
        return *this;
    }

    ReadOptions& setBounds(size_t dim, const std::string &s)
    {
        if(s == "*") return setBounds(dim, 0, -1);
        auto n = s.find("..");
        if(n == std::string::npos)
        {
            int f = std::stoi(s);
            return setBounds(dim, f, f);
        }
        else
        {
            std::string smin = s.substr(0, n);
            std::string smax = s.substr(n + 2);
            int min = std::stoi(smin);
            int max = smax == "*" ? -1 : std::stoi(smax);
            return setBounds(dim, min, max);
        }
    }

    ReadOptions& setBounds(const std::string &s)
    {
        if(s != "")
        {
            std::vector<std::string> ss;
            boost::split(ss, s, boost::is_any_of(", "));
            for(size_t dim = 0; dim < ss.size(); dim++)
                setBounds(dim, ss.at(dim));
        }
        return *this;
    }

    void validateTableSize(size_t sz) const
    {
        if(minSize.empty() || maxSize.empty()) return;
        if(minSize[0] == maxSize[0])
        {
            if(sz != minSize[0])
                throw sim::exception("must have exactly %d elements", minSize[0]);
        }
        else
        {
            if(sz < minSize[0])
                throw sim::exception("must have at least %d elements", minSize[0]);
            if(sz > maxSize[0])
                throw sim::exception("must have at most %d elements", maxSize[0]);
        }
    }

    void validateSize(size_t dim, size_t sz) const
    {
        if(dim >= minSize.size() || dim >= maxSize.size()) return;
        if(minSize[dim] == maxSize[dim])
        {
            if(sz != minSize[dim])
                throw sim::exception("dimension %d must have exactly %d elements", dim + 1, minSize[dim]);
        }
        else
        {
            if(sz < minSize[dim])
                throw sim::exception("dimension %d must have at least %d elements", dim + 1, minSize[dim]);
            if(sz > maxSize[dim])
                throw sim::exception("dimension %d must have at most %d elements", dim + 1, maxSize[dim]);
        }
    }

    template<typename T>
    void validateSize(const std::vector<T> &szs) const
    {
        size_t n = std::min(minSize.size(), maxSize.size());
        if(n && szs.size() != n)
            throw sim::exception("incorrect dimension count: %d (should be %d)", szs.size(), n);
        for(size_t dim = 0; dim < n; dim++)
            validateSize(dim, szs.at(dim));
    }
};

struct WriteOptions
{
    void *dummy{nullptr};
};

struct transport_hints
{
    std::vector< std::string > transports;
    bool tcpNoDelay;
    int maxDatagramSize;

    transport_hints();
    transport_hints(const std::vector< std::string > &transports_, const bool &tcpNoDelay_, const int &maxDatagramSize_) : transports(transports_), tcpNoDelay(tcpNoDelay_), maxDatagramSize(maxDatagramSize_) {}
};

void readFromStack(int stack, bool *value, const ReadOptions &rdopt = {});
void readFromStack(int stack, int *value, const ReadOptions &rdopt = {});
void readFromStack(int stack, long *value, const ReadOptions &rdopt = {});
void readFromStack(int stack, float *value, const ReadOptions &rdopt = {});
void readFromStack(int stack, double *value, const ReadOptions &rdopt = {});
void readFromStack(int stack, std::string *value, const ReadOptions &rdopt = {});
void readFromStack(int stack, transport_hints *value, const ReadOptions &rdopt = {});
void writeToStack(const bool &value, int stack, const WriteOptions &wropt = {});
void writeToStack(const int &value, int stack, const WriteOptions &wropt = {});
void writeToStack(const long &value, int stack, const WriteOptions &wropt = {});
void writeToStack(const float &value, int stack, const WriteOptions &wropt = {});
void writeToStack(const double &value, int stack, const WriteOptions &wropt = {});
void writeToStack(const std::string &value, int stack, const WriteOptions &wropt = {});
void writeToStack(const transport_hints &value, int stack, const WriteOptions &wropt = {});

bool registerScriptStuff();

struct subscribe_in
{
    SScriptCallBack _;
    std::string topicName;
    std::string topicType;
    std::string topicCallback;
    int queueSize;
    transport_hints transportHints;

    subscribe_in();
};

struct subscribe_out
{
    std::string subscriberHandle;

    subscribe_out();
};

void subscribe(SScriptCallBack *p, subscribe_in *in, subscribe_out *out);
std::string subscribe(SScriptCallBack *p, std::string topicName, std::string topicType, std::string topicCallback, int queueSize = 1, transport_hints transportHints = {});
void subscribe(SScriptCallBack *p, subscribe_out *out, std::string topicName, std::string topicType, std::string topicCallback, int queueSize = 1, transport_hints transportHints = {});
void subscribe_callback(SScriptCallBack *p);

struct shutdownSubscriber_in
{
    SScriptCallBack _;
    std::string subscriberHandle;

    shutdownSubscriber_in();
};

struct shutdownSubscriber_out
{

    shutdownSubscriber_out();
};

void shutdownSubscriber(SScriptCallBack *p, shutdownSubscriber_in *in, shutdownSubscriber_out *out);
void shutdownSubscriber(SScriptCallBack *p, std::string subscriberHandle);
void shutdownSubscriber(SScriptCallBack *p, shutdownSubscriber_out *out, std::string subscriberHandle);
void shutdownSubscriber_callback(SScriptCallBack *p);

struct subscriberTreatUInt8ArrayAsString_in
{
    SScriptCallBack _;
    std::string subscriberHandle;

    subscriberTreatUInt8ArrayAsString_in();
};

struct subscriberTreatUInt8ArrayAsString_out
{

    subscriberTreatUInt8ArrayAsString_out();
};

void subscriberTreatUInt8ArrayAsString(SScriptCallBack *p, subscriberTreatUInt8ArrayAsString_in *in, subscriberTreatUInt8ArrayAsString_out *out);
void subscriberTreatUInt8ArrayAsString(SScriptCallBack *p, std::string subscriberHandle);
void subscriberTreatUInt8ArrayAsString(SScriptCallBack *p, subscriberTreatUInt8ArrayAsString_out *out, std::string subscriberHandle);
void subscriberTreatUInt8ArrayAsString_callback(SScriptCallBack *p);

struct advertise_in
{
    SScriptCallBack _;
    std::string topicName;
    std::string topicType;
    int queueSize;
    bool latch;

    advertise_in();
};

struct advertise_out
{
    std::string publisherHandle;

    advertise_out();
};

void advertise(SScriptCallBack *p, advertise_in *in, advertise_out *out);
std::string advertise(SScriptCallBack *p, std::string topicName, std::string topicType, int queueSize = 1, bool latch = false);
void advertise(SScriptCallBack *p, advertise_out *out, std::string topicName, std::string topicType, int queueSize = 1, bool latch = false);
void advertise_callback(SScriptCallBack *p);

struct shutdownPublisher_in
{
    SScriptCallBack _;
    std::string publisherHandle;

    shutdownPublisher_in();
};

struct shutdownPublisher_out
{

    shutdownPublisher_out();
};

void shutdownPublisher(SScriptCallBack *p, shutdownPublisher_in *in, shutdownPublisher_out *out);
void shutdownPublisher(SScriptCallBack *p, std::string publisherHandle);
void shutdownPublisher(SScriptCallBack *p, shutdownPublisher_out *out, std::string publisherHandle);
void shutdownPublisher_callback(SScriptCallBack *p);

struct publisherTreatUInt8ArrayAsString_in
{
    SScriptCallBack _;
    std::string publisherHandle;

    publisherTreatUInt8ArrayAsString_in();
};

struct publisherTreatUInt8ArrayAsString_out
{

    publisherTreatUInt8ArrayAsString_out();
};

void publisherTreatUInt8ArrayAsString(SScriptCallBack *p, publisherTreatUInt8ArrayAsString_in *in, publisherTreatUInt8ArrayAsString_out *out);
void publisherTreatUInt8ArrayAsString(SScriptCallBack *p, std::string publisherHandle);
void publisherTreatUInt8ArrayAsString(SScriptCallBack *p, publisherTreatUInt8ArrayAsString_out *out, std::string publisherHandle);
void publisherTreatUInt8ArrayAsString_callback(SScriptCallBack *p);

struct publish_in
{
    SScriptCallBack _;
    std::string publisherHandle;

    publish_in();
};

struct publish_out
{

    publish_out();
};

void publish(SScriptCallBack *p, publish_in *in, publish_out *out);
void publish(SScriptCallBack *p, std::string publisherHandle);
void publish(SScriptCallBack *p, publish_out *out, std::string publisherHandle);
void publish_callback(SScriptCallBack *p);

struct serviceClient_in
{
    SScriptCallBack _;
    std::string serviceName;
    std::string serviceType;

    serviceClient_in();
};

struct serviceClient_out
{
    std::string serviceClientHandle;

    serviceClient_out();
};

void serviceClient(SScriptCallBack *p, serviceClient_in *in, serviceClient_out *out);
std::string serviceClient(SScriptCallBack *p, std::string serviceName, std::string serviceType);
void serviceClient(SScriptCallBack *p, serviceClient_out *out, std::string serviceName, std::string serviceType);
void serviceClient_callback(SScriptCallBack *p);

struct shutdownServiceClient_in
{
    SScriptCallBack _;
    std::string serviceClientHandle;

    shutdownServiceClient_in();
};

struct shutdownServiceClient_out
{

    shutdownServiceClient_out();
};

void shutdownServiceClient(SScriptCallBack *p, shutdownServiceClient_in *in, shutdownServiceClient_out *out);
void shutdownServiceClient(SScriptCallBack *p, std::string serviceClientHandle);
void shutdownServiceClient(SScriptCallBack *p, shutdownServiceClient_out *out, std::string serviceClientHandle);
void shutdownServiceClient_callback(SScriptCallBack *p);

struct serviceClientTreatUInt8ArrayAsString_in
{
    SScriptCallBack _;
    std::string serviceClientHandle;

    serviceClientTreatUInt8ArrayAsString_in();
};

struct serviceClientTreatUInt8ArrayAsString_out
{

    serviceClientTreatUInt8ArrayAsString_out();
};

void serviceClientTreatUInt8ArrayAsString(SScriptCallBack *p, serviceClientTreatUInt8ArrayAsString_in *in, serviceClientTreatUInt8ArrayAsString_out *out);
void serviceClientTreatUInt8ArrayAsString(SScriptCallBack *p, std::string serviceClientHandle);
void serviceClientTreatUInt8ArrayAsString(SScriptCallBack *p, serviceClientTreatUInt8ArrayAsString_out *out, std::string serviceClientHandle);
void serviceClientTreatUInt8ArrayAsString_callback(SScriptCallBack *p);

struct call_in
{
    SScriptCallBack _;
    std::string serviceClientHandle;

    call_in();
};

struct call_out
{

    call_out();
};

void call(SScriptCallBack *p, call_in *in, call_out *out);
void call(SScriptCallBack *p, std::string serviceClientHandle);
void call(SScriptCallBack *p, call_out *out, std::string serviceClientHandle);
void call_callback(SScriptCallBack *p);

struct advertiseService_in
{
    SScriptCallBack _;
    std::string serviceName;
    std::string serviceType;
    std::string serviceCallback;

    advertiseService_in();
};

struct advertiseService_out
{
    std::string serviceServerHandle;

    advertiseService_out();
};

void advertiseService(SScriptCallBack *p, advertiseService_in *in, advertiseService_out *out);
std::string advertiseService(SScriptCallBack *p, std::string serviceName, std::string serviceType, std::string serviceCallback);
void advertiseService(SScriptCallBack *p, advertiseService_out *out, std::string serviceName, std::string serviceType, std::string serviceCallback);
void advertiseService_callback(SScriptCallBack *p);

struct shutdownServiceServer_in
{
    SScriptCallBack _;
    std::string serviceServerHandle;

    shutdownServiceServer_in();
};

struct shutdownServiceServer_out
{

    shutdownServiceServer_out();
};

void shutdownServiceServer(SScriptCallBack *p, shutdownServiceServer_in *in, shutdownServiceServer_out *out);
void shutdownServiceServer(SScriptCallBack *p, std::string serviceServerHandle);
void shutdownServiceServer(SScriptCallBack *p, shutdownServiceServer_out *out, std::string serviceServerHandle);
void shutdownServiceServer_callback(SScriptCallBack *p);

struct serviceServerTreatUInt8ArrayAsString_in
{
    SScriptCallBack _;
    std::string serviceServerHandle;

    serviceServerTreatUInt8ArrayAsString_in();
};

struct serviceServerTreatUInt8ArrayAsString_out
{

    serviceServerTreatUInt8ArrayAsString_out();
};

void serviceServerTreatUInt8ArrayAsString(SScriptCallBack *p, serviceServerTreatUInt8ArrayAsString_in *in, serviceServerTreatUInt8ArrayAsString_out *out);
void serviceServerTreatUInt8ArrayAsString(SScriptCallBack *p, std::string serviceServerHandle);
void serviceServerTreatUInt8ArrayAsString(SScriptCallBack *p, serviceServerTreatUInt8ArrayAsString_out *out, std::string serviceServerHandle);
void serviceServerTreatUInt8ArrayAsString_callback(SScriptCallBack *p);

struct sendTransform_in
{
    SScriptCallBack _;

    sendTransform_in();
};

struct sendTransform_out
{

    sendTransform_out();
};

void sendTransform(SScriptCallBack *p, sendTransform_in *in, sendTransform_out *out);
void sendTransform(SScriptCallBack *p);
void sendTransform(SScriptCallBack *p, sendTransform_out *out);
void sendTransform_callback(SScriptCallBack *p);

struct sendTransforms_in
{
    SScriptCallBack _;

    sendTransforms_in();
};

struct sendTransforms_out
{

    sendTransforms_out();
};

void sendTransforms(SScriptCallBack *p, sendTransforms_in *in, sendTransforms_out *out);
void sendTransforms(SScriptCallBack *p);
void sendTransforms(SScriptCallBack *p, sendTransforms_out *out);
void sendTransforms_callback(SScriptCallBack *p);

struct imageTransportSubscribe_in
{
    SScriptCallBack _;
    std::string topicName;
    std::string topicCallback;
    int queueSize;

    imageTransportSubscribe_in();
};

struct imageTransportSubscribe_out
{
    std::string subscriberHandle;

    imageTransportSubscribe_out();
};

void imageTransportSubscribe(SScriptCallBack *p, imageTransportSubscribe_in *in, imageTransportSubscribe_out *out);
std::string imageTransportSubscribe(SScriptCallBack *p, std::string topicName, std::string topicCallback, int queueSize = 1);
void imageTransportSubscribe(SScriptCallBack *p, imageTransportSubscribe_out *out, std::string topicName, std::string topicCallback, int queueSize = 1);
void imageTransportSubscribe_callback(SScriptCallBack *p);

struct imageTransportShutdownSubscriber_in
{
    SScriptCallBack _;
    std::string subscriberHandle;

    imageTransportShutdownSubscriber_in();
};

struct imageTransportShutdownSubscriber_out
{

    imageTransportShutdownSubscriber_out();
};

void imageTransportShutdownSubscriber(SScriptCallBack *p, imageTransportShutdownSubscriber_in *in, imageTransportShutdownSubscriber_out *out);
void imageTransportShutdownSubscriber(SScriptCallBack *p, std::string subscriberHandle);
void imageTransportShutdownSubscriber(SScriptCallBack *p, imageTransportShutdownSubscriber_out *out, std::string subscriberHandle);
void imageTransportShutdownSubscriber_callback(SScriptCallBack *p);

struct imageTransportAdvertise_in
{
    SScriptCallBack _;
    std::string topicName;
    int queueSize;

    imageTransportAdvertise_in();
};

struct imageTransportAdvertise_out
{
    std::string publisherHandle;

    imageTransportAdvertise_out();
};

void imageTransportAdvertise(SScriptCallBack *p, imageTransportAdvertise_in *in, imageTransportAdvertise_out *out);
std::string imageTransportAdvertise(SScriptCallBack *p, std::string topicName, int queueSize = 1);
void imageTransportAdvertise(SScriptCallBack *p, imageTransportAdvertise_out *out, std::string topicName, int queueSize = 1);
void imageTransportAdvertise_callback(SScriptCallBack *p);

struct imageTransportShutdownPublisher_in
{
    SScriptCallBack _;
    std::string publisherHandle;

    imageTransportShutdownPublisher_in();
};

struct imageTransportShutdownPublisher_out
{

    imageTransportShutdownPublisher_out();
};

void imageTransportShutdownPublisher(SScriptCallBack *p, imageTransportShutdownPublisher_in *in, imageTransportShutdownPublisher_out *out);
void imageTransportShutdownPublisher(SScriptCallBack *p, std::string publisherHandle);
void imageTransportShutdownPublisher(SScriptCallBack *p, imageTransportShutdownPublisher_out *out, std::string publisherHandle);
void imageTransportShutdownPublisher_callback(SScriptCallBack *p);

struct imageTransportPublish_in
{
    SScriptCallBack _;
    std::string publisherHandle;
    std::string data;
    int width;
    int height;
    std::string frame_id;

    imageTransportPublish_in();
};

struct imageTransportPublish_out
{

    imageTransportPublish_out();
};

void imageTransportPublish(SScriptCallBack *p, imageTransportPublish_in *in, imageTransportPublish_out *out);
void imageTransportPublish(SScriptCallBack *p, std::string publisherHandle, std::string data, int width, int height, std::string frame_id);
void imageTransportPublish(SScriptCallBack *p, imageTransportPublish_out *out, std::string publisherHandle, std::string data, int width, int height, std::string frame_id);
void imageTransportPublish_callback(SScriptCallBack *p);

struct getTime_in
{
    SScriptCallBack _;
    int flag;

    getTime_in();
};

struct getTime_out
{
    double time;

    getTime_out();
};

void getTime(SScriptCallBack *p, getTime_in *in, getTime_out *out);
double getTime(SScriptCallBack *p, int flag = 0);
void getTime(SScriptCallBack *p, getTime_out *out, int flag = 0);
void getTime_callback(SScriptCallBack *p);

struct getParamString_in
{
    SScriptCallBack _;
    std::string name;
    std::string defaultValue;

    getParamString_in();
};

struct getParamString_out
{
    bool exists;
    std::string value;

    getParamString_out();
};

void getParamString(SScriptCallBack *p, getParamString_in *in, getParamString_out *out);
void getParamString(SScriptCallBack *p, getParamString_out *out, std::string name, std::string defaultValue = "");
void getParamString_callback(SScriptCallBack *p);

struct getParamInt_in
{
    SScriptCallBack _;
    std::string name;
    int defaultValue;

    getParamInt_in();
};

struct getParamInt_out
{
    bool exists;
    int value;

    getParamInt_out();
};

void getParamInt(SScriptCallBack *p, getParamInt_in *in, getParamInt_out *out);
void getParamInt(SScriptCallBack *p, getParamInt_out *out, std::string name, int defaultValue = 0);
void getParamInt_callback(SScriptCallBack *p);

struct getParamDouble_in
{
    SScriptCallBack _;
    std::string name;
    double defaultValue;

    getParamDouble_in();
};

struct getParamDouble_out
{
    bool exists;
    double value;

    getParamDouble_out();
};

void getParamDouble(SScriptCallBack *p, getParamDouble_in *in, getParamDouble_out *out);
void getParamDouble(SScriptCallBack *p, getParamDouble_out *out, std::string name, double defaultValue = 0.0);
void getParamDouble_callback(SScriptCallBack *p);

struct getParamBool_in
{
    SScriptCallBack _;
    std::string name;
    bool defaultValue;

    getParamBool_in();
};

struct getParamBool_out
{
    bool exists;
    bool value;

    getParamBool_out();
};

void getParamBool(SScriptCallBack *p, getParamBool_in *in, getParamBool_out *out);
void getParamBool(SScriptCallBack *p, getParamBool_out *out, std::string name, bool defaultValue = false);
void getParamBool_callback(SScriptCallBack *p);

struct setParamString_in
{
    SScriptCallBack _;
    std::string name;
    std::string value;

    setParamString_in();
};

struct setParamString_out
{

    setParamString_out();
};

void setParamString(SScriptCallBack *p, setParamString_in *in, setParamString_out *out);
void setParamString(SScriptCallBack *p, std::string name, std::string value);
void setParamString(SScriptCallBack *p, setParamString_out *out, std::string name, std::string value);
void setParamString_callback(SScriptCallBack *p);

struct setParamInt_in
{
    SScriptCallBack _;
    std::string name;
    int value;

    setParamInt_in();
};

struct setParamInt_out
{

    setParamInt_out();
};

void setParamInt(SScriptCallBack *p, setParamInt_in *in, setParamInt_out *out);
void setParamInt(SScriptCallBack *p, std::string name, int value);
void setParamInt(SScriptCallBack *p, setParamInt_out *out, std::string name, int value);
void setParamInt_callback(SScriptCallBack *p);

struct setParamDouble_in
{
    SScriptCallBack _;
    std::string name;
    double value;

    setParamDouble_in();
};

struct setParamDouble_out
{

    setParamDouble_out();
};

void setParamDouble(SScriptCallBack *p, setParamDouble_in *in, setParamDouble_out *out);
void setParamDouble(SScriptCallBack *p, std::string name, double value);
void setParamDouble(SScriptCallBack *p, setParamDouble_out *out, std::string name, double value);
void setParamDouble_callback(SScriptCallBack *p);

struct setParamBool_in
{
    SScriptCallBack _;
    std::string name;
    bool value;

    setParamBool_in();
};

struct setParamBool_out
{

    setParamBool_out();
};

void setParamBool(SScriptCallBack *p, setParamBool_in *in, setParamBool_out *out);
void setParamBool(SScriptCallBack *p, std::string name, bool value);
void setParamBool(SScriptCallBack *p, setParamBool_out *out, std::string name, bool value);
void setParamBool_callback(SScriptCallBack *p);

struct hasParam_in
{
    SScriptCallBack _;
    std::string name;

    hasParam_in();
};

struct hasParam_out
{
    bool exists;

    hasParam_out();
};

void hasParam(SScriptCallBack *p, hasParam_in *in, hasParam_out *out);
bool hasParam(SScriptCallBack *p, std::string name);
void hasParam(SScriptCallBack *p, hasParam_out *out, std::string name);
void hasParam_callback(SScriptCallBack *p);

struct deleteParam_in
{
    SScriptCallBack _;
    std::string name;

    deleteParam_in();
};

struct deleteParam_out
{

    deleteParam_out();
};

void deleteParam(SScriptCallBack *p, deleteParam_in *in, deleteParam_out *out);
void deleteParam(SScriptCallBack *p, std::string name);
void deleteParam(SScriptCallBack *p, deleteParam_out *out, std::string name);
void deleteParam_callback(SScriptCallBack *p);

struct searchParam_in
{
    SScriptCallBack _;
    std::string name;

    searchParam_in();
};

struct searchParam_out
{
    bool found;
    std::string name;

    searchParam_out();
};

void searchParam(SScriptCallBack *p, searchParam_in *in, searchParam_out *out);
void searchParam(SScriptCallBack *p, searchParam_out *out, std::string name);
void searchParam_callback(SScriptCallBack *p);

struct subscriberCallback_in
{

    subscriberCallback_in();
};

struct subscriberCallback_out
{

    subscriberCallback_out();
};

void subscriberCallback(simInt scriptId, const char *func);
bool subscriberCallback(simInt scriptId, const char *func, subscriberCallback_in *in_args, subscriberCallback_out *out_args);

struct imageTransportCallback_in
{
    std::string data;
    int width;
    int height;

    imageTransportCallback_in();
};

struct imageTransportCallback_out
{

    imageTransportCallback_out();
};

void imageTransportCallback(simInt scriptId, const char *func, std::string data, int width, int height);
bool imageTransportCallback(simInt scriptId, const char *func, imageTransportCallback_in *in_args, imageTransportCallback_out *out_args);

// following functions must be implemented in the plugin

void subscribe(SScriptCallBack *p, const char *cmd, subscribe_in *in, subscribe_out *out);
void shutdownSubscriber(SScriptCallBack *p, const char *cmd, shutdownSubscriber_in *in, shutdownSubscriber_out *out);
void subscriberTreatUInt8ArrayAsString(SScriptCallBack *p, const char *cmd, subscriberTreatUInt8ArrayAsString_in *in, subscriberTreatUInt8ArrayAsString_out *out);
void advertise(SScriptCallBack *p, const char *cmd, advertise_in *in, advertise_out *out);
void shutdownPublisher(SScriptCallBack *p, const char *cmd, shutdownPublisher_in *in, shutdownPublisher_out *out);
void publisherTreatUInt8ArrayAsString(SScriptCallBack *p, const char *cmd, publisherTreatUInt8ArrayAsString_in *in, publisherTreatUInt8ArrayAsString_out *out);
void publish(SScriptCallBack *p, const char *cmd, publish_in *in, publish_out *out);
void serviceClient(SScriptCallBack *p, const char *cmd, serviceClient_in *in, serviceClient_out *out);
void shutdownServiceClient(SScriptCallBack *p, const char *cmd, shutdownServiceClient_in *in, shutdownServiceClient_out *out);
void serviceClientTreatUInt8ArrayAsString(SScriptCallBack *p, const char *cmd, serviceClientTreatUInt8ArrayAsString_in *in, serviceClientTreatUInt8ArrayAsString_out *out);
void call(SScriptCallBack *p, const char *cmd, call_in *in, call_out *out);
void advertiseService(SScriptCallBack *p, const char *cmd, advertiseService_in *in, advertiseService_out *out);
void shutdownServiceServer(SScriptCallBack *p, const char *cmd, shutdownServiceServer_in *in, shutdownServiceServer_out *out);
void serviceServerTreatUInt8ArrayAsString(SScriptCallBack *p, const char *cmd, serviceServerTreatUInt8ArrayAsString_in *in, serviceServerTreatUInt8ArrayAsString_out *out);
void sendTransform(SScriptCallBack *p, const char *cmd, sendTransform_in *in, sendTransform_out *out);
void sendTransforms(SScriptCallBack *p, const char *cmd, sendTransforms_in *in, sendTransforms_out *out);
void imageTransportSubscribe(SScriptCallBack *p, const char *cmd, imageTransportSubscribe_in *in, imageTransportSubscribe_out *out);
void imageTransportShutdownSubscriber(SScriptCallBack *p, const char *cmd, imageTransportShutdownSubscriber_in *in, imageTransportShutdownSubscriber_out *out);
void imageTransportAdvertise(SScriptCallBack *p, const char *cmd, imageTransportAdvertise_in *in, imageTransportAdvertise_out *out);
void imageTransportShutdownPublisher(SScriptCallBack *p, const char *cmd, imageTransportShutdownPublisher_in *in, imageTransportShutdownPublisher_out *out);
void imageTransportPublish(SScriptCallBack *p, const char *cmd, imageTransportPublish_in *in, imageTransportPublish_out *out);
void getTime(SScriptCallBack *p, const char *cmd, getTime_in *in, getTime_out *out);
void getParamString(SScriptCallBack *p, const char *cmd, getParamString_in *in, getParamString_out *out);
void getParamInt(SScriptCallBack *p, const char *cmd, getParamInt_in *in, getParamInt_out *out);
void getParamDouble(SScriptCallBack *p, const char *cmd, getParamDouble_in *in, getParamDouble_out *out);
void getParamBool(SScriptCallBack *p, const char *cmd, getParamBool_in *in, getParamBool_out *out);
void setParamString(SScriptCallBack *p, const char *cmd, setParamString_in *in, setParamString_out *out);
void setParamInt(SScriptCallBack *p, const char *cmd, setParamInt_in *in, setParamInt_out *out);
void setParamDouble(SScriptCallBack *p, const char *cmd, setParamDouble_in *in, setParamDouble_out *out);
void setParamBool(SScriptCallBack *p, const char *cmd, setParamBool_in *in, setParamBool_out *out);
void hasParam(SScriptCallBack *p, const char *cmd, hasParam_in *in, hasParam_out *out);
void deleteParam(SScriptCallBack *p, const char *cmd, deleteParam_in *in, deleteParam_out *out);
void searchParam(SScriptCallBack *p, const char *cmd, searchParam_in *in, searchParam_out *out);

#endif // STUBS_H__INCLUDED
