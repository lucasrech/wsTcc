#include "stubs.h"
#include <simPlusPlus/Lib.h>

#include <cstring>
#include <string>
#include <vector>
#include <set>
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <boost/lexical_cast.hpp>

FuncTracer::FuncTracer(const std::string &f, int l)
    : f_(f),
      l_(l)
{
    sim::addLog(l_, f_ + " [enter]");
}

FuncTracer::~FuncTracer()
{
    sim::addLog(l_, f_ + " [leave]");
}

#ifndef NDEBUG

template<typename... Arguments>
void addStubsDebugLog(const std::string &fmt, Arguments&&... args)
{
    if(sim::isStackDebugEnabled())
    {
        auto msg = sim::util::sprintf(fmt, std::forward<Arguments>(args)...);
        sim::addLog(sim_verbosity_debug, "STUBS DEBUG: %s", msg);
    }
}

static void addStubsDebugStackDump(int stackHandle)
{
    if(sim::isStackDebugEnabled())
        sim::debugStack(stackHandle);
}

#else // RELEASE
#define addStubsDebugLog(...)
#define addStubsDebugStackDump(x)
#endif

#ifdef QT_COMPIL

Qt::HANDLE UI_THREAD = NULL;
Qt::HANDLE SIM_THREAD = NULL;

std::string threadNickname()
{
    Qt::HANDLE h = QThread::currentThreadId();
    if(h == UI_THREAD) return "UI";
    if(h == SIM_THREAD) return "SIM";
    std::stringstream ss;
    ss << h;
    return ss.str();
}

void uiThread()
{
    Qt::HANDLE h = QThread::currentThreadId();
    if(UI_THREAD != NULL && UI_THREAD != h)
        sim::addLog(sim_verbosity_warnings, "UI thread has already been set");
    UI_THREAD = h;
}

void simThread()
{
    Qt::HANDLE h = QThread::currentThreadId();
    if(SIM_THREAD != NULL && SIM_THREAD != h)
        sim::addLog(sim_verbosity_warnings, "SIM thread has already been set");
    SIM_THREAD = h;
}

#endif // QT_COMPIL

void readFromStack(int stack, bool *value, const ReadOptions &rdopt)
{
    simBool v;
    if(sim::getStackBoolValue(stack, &v) == 1)
    {
        *value = v;
        sim::popStackItem(stack, 1);
    }
    else
    {
        throw sim::exception("expected bool");
    }
}

void readFromStack(int stack, int *value, const ReadOptions &rdopt)
{
    int v;
    if(sim::getStackInt32Value(stack, &v) == 1)
    {
        *value = v;
        sim::popStackItem(stack, 1);
    }
    else
    {
        throw sim::exception("expected int");
    }
}

void readFromStack(int stack, long *value, const ReadOptions &rdopt)
{
    int v;
    if(sim::getStackInt32Value(stack, &v) == 1)
    {
        *value = v;
        sim::popStackItem(stack, 1);
    }
    else
    {
        throw sim::exception("expected int");
    }
}

void readFromStack(int stack, float *value, const ReadOptions &rdopt)
{
    simFloat v;
    if(sim::getStackFloatValue(stack, &v) == 1)
    {
        *value = v;
        sim::popStackItem(stack, 1);
    }
    else
    {
        throw sim::exception("expected float");
    }
}

void readFromStack(int stack, double *value, const ReadOptions &rdopt)
{
    simDouble v;
    if(sim::getStackDoubleValue(stack, &v) == 1)
    {
        *value = v;
        sim::popStackItem(stack, 1);
    }
    else
    {
        throw sim::exception("expected double");
    }
}

void readFromStack(int stack, std::string *value, const ReadOptions &rdopt)
{
    std::string v;
    if(sim::getStackStringValue(stack, &v) == 1)
    {
        *value = v;
        sim::popStackItem(stack, 1);
    }
    else
    {
        throw sim::exception("expected string");
    }
}

template<typename T>
void readFromStack(int stack, boost::optional<T> *value, const ReadOptions &rdopt = {})
{
    if(sim::isStackValueNull(stack) == 1)
    {
        *value = boost::none;
        sim::popStackItem(stack, 1);
    }
    else
    {
        T v;
        readFromStack(stack, &v, rdopt); // will call sim::popStackItem() by itself
        *value = v;
    }
}

template<typename T>
void readFromStack(int stack, std::vector<T> *vec, const ReadOptions &rdopt = {})
{
    int sz = sim::getStackTableInfo(stack, 0);
    if(sz < 0)
        throw sim::exception("expected array (simGetStackTableInfo(stack, 0) returned %d)", sz);

    rdopt.validateTableSize(sz);

    int oldsz = sim::getStackSize(stack);
    sim::unfoldStackTable(stack);
    int sz1 = (sim::getStackSize(stack) - oldsz + 1) / 2;
    if(sz != sz1)
        throw std::runtime_error("simUnfoldStackTable unpacked more elements than simGetStackTableInfo reported");

    vec->resize(sz);

    for(int i = 0; i < sz; i++)
    {
        sim::moveStackItemToTop(stack, oldsz - 1);
        int j;
        readFromStack(stack, &j);
        sim::moveStackItemToTop(stack, oldsz - 1);
        if constexpr(std::is_same<T, bool>::value)
        {
            T v;
            readFromStack(stack, &v);
            (*vec)[i] = v;
        }
        else
        {
            readFromStack(stack, &vec->at(i));
        }
    }
}

template<typename T>
void readFromStack(int stack, std::vector<T> *vec, simInt (*f)(simInt, std::vector<T>*), const ReadOptions &rdopt = {})
{
    int sz = sim::getStackTableInfo(stack, 0);
    if(sz < 0)
        throw sim::exception("expected array (simGetStackTableInfo(stack, 0) returned %d)", sz);

    rdopt.validateTableSize(sz);

    int chk = sim::getStackTableInfo(stack, 2);
    if(chk != 1)
        throw sim::exception("table contains non-numbers (simGetStackTableInfo(stack, 2) returned %d)", chk);

    vec->resize(sz);

    int ret = f(stack, vec);
    if(ret != 1)
        throw sim::exception("readFunc error %d", ret);

    sim::popStackItem(stack, 1);
}

template<>
void readFromStack(int stack, std::vector<float> *vec, const ReadOptions &rdopt)
{
    readFromStack(stack, vec, sim::getStackFloatTable, rdopt);
}

template<>
void readFromStack(int stack, std::vector<double> *vec, const ReadOptions &rdopt)
{
    readFromStack(stack, vec, sim::getStackDoubleTable, rdopt);
}

template<>
void readFromStack(int stack, std::vector<int> *vec, const ReadOptions &rdopt)
{
    readFromStack(stack, vec, sim::getStackInt32Table, rdopt);
}

template<typename T>
void readFromStack(int stack, Grid<T> *grid, const ReadOptions &rdopt = {})
{
    try
    {
        simInt info = sim::getStackTableInfo(stack, 0);
        if(info != sim_stack_table_map && info != sim_stack_table_empty)
        {
            throw sim::exception("expected a map");
        }

        int oldsz = sim::getStackSize(stack);
        sim::unfoldStackTable(stack);
        int numItems = (sim::getStackSize(stack) - oldsz + 1) / 2;

        std::set<std::string> requiredFields{"dims", "data"};

        while(numItems >= 1)
        {
            sim::moveStackItemToTop(stack, oldsz - 1); // move key to top
            std::string key;
            readFromStack(stack, &key);

            sim::moveStackItemToTop(stack, oldsz - 1); // move value to top
            try
            {
                if(0) {}
                else if(key == "dims")
                {
                    readFromStack(stack, &grid->dims, ReadOptions().setBounds(0, 1, -1));
                }
                else if(key == "data")
                {
                    readFromStack(stack, &grid->data, ReadOptions());
                }
                else
                {
                    throw sim::exception("unexpected key");
                }
            }
            catch(std::exception &ex)
            {
                throw sim::exception("field '%s': %s", key, ex.what());
            }

            requiredFields.erase(key);
            numItems = (sim::getStackSize(stack) - oldsz + 1) / 2;
        }

        for(const auto &field : requiredFields)
            throw sim::exception("missing required field '%s'", field);

        if(grid->dims.size() < 1)
            throw sim::exception("must have at least one dimension");

        size_t elemCount = 1;
        for(const int &i : grid->dims) elemCount *= i;
        if(grid->data.size() != elemCount)
            throw sim::exception("incorrect data length (expected %d elements)", elemCount);

        rdopt.validateSize(grid->dims);
    }
    catch(std::exception &ex)
    {
        throw sim::exception("readFromStack(Grid): %s", ex.what());
    }
}

void readFromStack(int stack, transport_hints *value, const ReadOptions &rdopt)
{
    addStubsDebugLog("readFromStack(transport_hints): begin reading...");
    addStubsDebugStackDump(stack);

    try
    {
        simInt info = sim::getStackTableInfo(stack, 0);
        if(info != sim_stack_table_map && info != sim_stack_table_empty)
        {
            throw sim::exception("expected a map");
        }

        int oldsz = sim::getStackSize(stack);
        sim::unfoldStackTable(stack);
        int numItems = (sim::getStackSize(stack) - oldsz + 1) / 2;

        std::set<std::string> requiredFields{};

        while(numItems >= 1)
        {
            sim::moveStackItemToTop(stack, oldsz - 1); // move key to top
            std::string key;
            readFromStack(stack, &key);

            sim::moveStackItemToTop(stack, oldsz - 1); // move value to top
            if(0) {}
            else if(key == "transports")
            {
                addStubsDebugLog("readFromStack(transport_hints): reading field \"transports\" (std::vector< std::string >)...");
                try
                {
                    readFromStack(stack, &(value->transports), ReadOptions().setBounds(""));
                }
                catch(std::exception &ex)
                {
                    throw sim::exception("field 'transports': %s", ex.what());
                }
            }
            else if(key == "tcpNoDelay")
            {
                addStubsDebugLog("readFromStack(transport_hints): reading field \"tcpNoDelay\" (bool)...");
                try
                {
                    readFromStack(stack, &(value->tcpNoDelay));
                }
                catch(std::exception &ex)
                {
                    throw sim::exception("field 'tcpNoDelay': %s", ex.what());
                }
            }
            else if(key == "maxDatagramSize")
            {
                addStubsDebugLog("readFromStack(transport_hints): reading field \"maxDatagramSize\" (int)...");
                try
                {
                    readFromStack(stack, &(value->maxDatagramSize));
                }
                catch(std::exception &ex)
                {
                    throw sim::exception("field 'maxDatagramSize': %s", ex.what());
                }
            }
            else
            {
                throw sim::exception("unexpected key: %s", key);
            }

            requiredFields.erase(key);
            numItems = (sim::getStackSize(stack) - oldsz + 1) / 2;
        }

        for(const auto &field : requiredFields)
            throw sim::exception("missing required field '%s'", field);
    }
    catch(std::exception &ex)
    {
        throw sim::exception("readFromStack(transport_hints): %s", ex.what());
    }

    addStubsDebugLog("readFromStack(transport_hints): finished reading");
}

void writeToStack(const bool &value, int stack, const WriteOptions &wropt)
{
    sim::pushBoolOntoStack(stack, value);
}

void writeToStack(const int &value, int stack, const WriteOptions &wropt)
{
    sim::pushInt32OntoStack(stack, value);
}

void writeToStack(const long &value, int stack, const WriteOptions &wropt)
{
    if(value < std::numeric_limits<int>::max() || value > std::numeric_limits<int>::max())
        throw std::runtime_error("stack doesn't support (yet) int64 values");
    sim::pushInt32OntoStack(stack, static_cast<int>(value));
}

void writeToStack(const float &value, int stack, const WriteOptions &wropt)
{
    sim::pushFloatOntoStack(stack, value);
}

void writeToStack(const double &value, int stack, const WriteOptions &wropt)
{
    sim::pushDoubleOntoStack(stack, value);
}

void writeToStack(const std::string &value, int stack, const WriteOptions &wropt)
{
    sim::pushStringOntoStack(stack, value);
}

template<typename T>
void writeToStack(const boost::optional<T> &value, int stack, const WriteOptions &wropt = {})
{
    if(!value)
    {
        sim::pushNullOntoStack(stack);
        return;
    }

    writeToStack(*value, stack, wropt);
}

template<typename T>
void writeToStack(const std::vector<T> &vec, int stack, const WriteOptions &wropt = {})
{
    sim::pushTableOntoStack(stack);
    for(size_t i = 0; i < vec.size(); i++)
    {
        writeToStack(int(i + 1), stack);
        writeToStack(vec.at(i), stack);
        sim::insertDataIntoStackTable(stack);
    }
}

template<>
void writeToStack(const std::vector<float> &vec, int stack, const WriteOptions &wropt)
{
    sim::pushFloatTableOntoStack(stack, vec);
}

template<>
void writeToStack(const std::vector<double> &vec, int stack, const WriteOptions &wropt)
{
    sim::pushDoubleTableOntoStack(stack, vec);
}

template<>
void writeToStack(const std::vector<int> &vec, int stack, const WriteOptions &wropt)
{
    sim::pushInt32TableOntoStack(stack, vec);
}

template<typename T>
void writeToStack(const Grid<T> &grid, int stack, const WriteOptions &wropt = {})
{
    try
    {
        sim::pushTableOntoStack(stack);

        try
        {
            writeToStack(std::string{"dims"}, stack);
            writeToStack(grid.dims, stack);
            sim::insertDataIntoStackTable(stack);
        }
        catch(std::exception &ex)
        {
            throw sim::exception("field 'dims': %s", ex.what());
        }
        try
        {
            writeToStack(std::string{"data"}, stack);
            writeToStack(grid.data, stack);
            sim::insertDataIntoStackTable(stack);
        }
        catch(std::exception &ex)
        {
            throw sim::exception("field 'data': %s", ex.what());
        }
    }
    catch(std::exception &ex)
    {
        throw sim::exception("writeToStack(Grid): %s", ex.what());
    }
}

void writeToStack(const transport_hints &value, int stack, const WriteOptions &wropt)
{
    addStubsDebugLog("writeToStack(transport_hints): begin writing...");

    try
    {
        sim::pushTableOntoStack(stack);

        addStubsDebugLog("writeToStack(transport_hints): writing field \"transports\" (std::vector< std::string >)...");
        try
        {
            writeToStack(std::string{"transports"}, stack);
            writeToStack(value.transports, stack);
            sim::insertDataIntoStackTable(stack);
        }
        catch(std::exception &ex)
        {
            throw sim::exception("field 'transports': %s", ex.what());
        }
        addStubsDebugLog("writeToStack(transport_hints): writing field \"tcpNoDelay\" (bool)...");
        try
        {
            writeToStack(std::string{"tcpNoDelay"}, stack);
            writeToStack(value.tcpNoDelay, stack);
            sim::insertDataIntoStackTable(stack);
        }
        catch(std::exception &ex)
        {
            throw sim::exception("field 'tcpNoDelay': %s", ex.what());
        }
        addStubsDebugLog("writeToStack(transport_hints): writing field \"maxDatagramSize\" (int)...");
        try
        {
            writeToStack(std::string{"maxDatagramSize"}, stack);
            writeToStack(value.maxDatagramSize, stack);
            sim::insertDataIntoStackTable(stack);
        }
        catch(std::exception &ex)
        {
            throw sim::exception("field 'maxDatagramSize': %s", ex.what());
        }
    }
    catch(std::exception &ex)
    {
        throw sim::exception("writeToStack(transport_hints): %s", ex.what());
    }

    addStubsDebugLog("writeToStack(transport_hints): finished writing");
}

transport_hints::transport_hints()
{
    transports = {};
    tcpNoDelay = false;
    maxDatagramSize = 0;
}

void checkRuntimeVersion()
{
    simInt simVer = sim::programVersion();

    // version required by simStubsGen:
    int minVer = 4010000; // 4.1.0rev0
    if(simVer < minVer)
        throw sim::exception("requires at least %s (libPlugin)", sim::versionString(minVer));

    // version required by plugin:
    if(simVer < SIM_REQUIRED_PROGRAM_VERSION_NB)
        throw sim::exception("requires at least %s", sim::versionString(SIM_REQUIRED_PROGRAM_VERSION_NB));

    // warn if the app older than the headers used to compile:
    if(simVer < SIM_PROGRAM_FULL_VERSION_NB)
        sim::addLog(sim_verbosity_warnings, "has been built for %s", sim::versionString(SIM_PROGRAM_FULL_VERSION_NB));
}

bool registerScriptStuff()
{
    try
    {
        checkRuntimeVersion();

        auto dbg = sim::getStringNamedParam("simStubsGen.debug");
        if(dbg && *dbg != "0")
            sim::enableStackDebug();

        try
        {
            sim::registerScriptVariable("simROS", "require('simROS-typecheck')", 0);
            sim::registerScriptVariable("_ROS_latest_version", "math.max(_ROS_latest_version or 0, 0)", 0);

            // register varables from enums:
            // register commands:
            sim::registerScriptCallbackFunction("simROS.subscribe@ROS", "string subscriberHandle=simROS.subscribe(string topicName,string topicType,string topicCallback,int queueSize=1,map transportHints={})\n\nSubscribe to a topic.", subscribe_callback);
            sim::registerScriptCallbackFunction("simROS.shutdownSubscriber@ROS", "simROS.shutdownSubscriber(string subscriberHandle)\n\nUnsubscribe the callback associated with this subscriber.", shutdownSubscriber_callback);
            sim::registerScriptCallbackFunction("simROS.subscriberTreatUInt8ArrayAsString@ROS", "simROS.subscriberTreatUInt8ArrayAsString(string subscriberHandle)\n\nAfter calling this function, this subscriber will treat uint8 arrays as string. Using strings should be in general much faster that using int arrays in Lua.", subscriberTreatUInt8ArrayAsString_callback);
            sim::registerScriptCallbackFunction("simROS.advertise@ROS", "string publisherHandle=simROS.advertise(string topicName,string topicType,int queueSize=1,bool latch=false)\n\nAdvertise a topic and create a topic publisher.", advertise_callback);
            sim::registerScriptCallbackFunction("simROS.shutdownPublisher@ROS", "simROS.shutdownPublisher(string publisherHandle)\n\nShutdown the advertisement associated with this publisher.", shutdownPublisher_callback);
            sim::registerScriptCallbackFunction("simROS.publisherTreatUInt8ArrayAsString@ROS", "simROS.publisherTreatUInt8ArrayAsString(string publisherHandle)\n\nAfter calling this function, this publisher will treat uint8 arrays as string. Using strings should be in general much faster that using int arrays in Lua.", publisherTreatUInt8ArrayAsString_callback);
            sim::registerScriptCallbackFunction("simROS.publish@ROS", "simROS.publish(string publisherHandle,map message)\n\nPublish a message on the topic associated with this publisher.", publish_callback);
            sim::registerScriptCallbackFunction("simROS.serviceClient@ROS", "string serviceClientHandle=simROS.serviceClient(string serviceName,string serviceType)\n\nCreate a service client.", serviceClient_callback);
            sim::registerScriptCallbackFunction("simROS.shutdownServiceClient@ROS", "simROS.shutdownServiceClient(string serviceClientHandle)\n\nShutdown the service client.", shutdownServiceClient_callback);
            sim::registerScriptCallbackFunction("simROS.serviceClientTreatUInt8ArrayAsString@ROS", "simROS.serviceClientTreatUInt8ArrayAsString(string serviceClientHandle)\n\nAfter calling this function, this service client will treat uint8 arrays as string. Using strings should be in general much faster that using int arrays in Lua.", serviceClientTreatUInt8ArrayAsString_callback);
            sim::registerScriptCallbackFunction("simROS.call@ROS", "map result=simROS.call(string serviceClientHandle,map request)\n\nCall the service associated with this service client.", call_callback);
            sim::registerScriptCallbackFunction("simROS.advertiseService@ROS", "string serviceServerHandle=simROS.advertiseService(string serviceName,string serviceType,string serviceCallback)\n\nAdvertise a service and create a service server.", advertiseService_callback);
            sim::registerScriptCallbackFunction("simROS.shutdownServiceServer@ROS", "simROS.shutdownServiceServer(string serviceServerHandle)\n\nShutdown the service server.", shutdownServiceServer_callback);
            sim::registerScriptCallbackFunction("simROS.serviceServerTreatUInt8ArrayAsString@ROS", "simROS.serviceServerTreatUInt8ArrayAsString(string serviceServerHandle)\n\nAfter calling this function, this service server will treat uint8 arrays as string. Using strings should be in general much faster that using int arrays in Lua.", serviceServerTreatUInt8ArrayAsString_callback);
            sim::registerScriptCallbackFunction("simROS.sendTransform@ROS", "simROS.sendTransform(map transform)\n\nPublish a TF transformation between frames.", sendTransform_callback);
            sim::registerScriptCallbackFunction("simROS.sendTransforms@ROS", "simROS.sendTransforms(map transforms)\n\nPublish several TF transformations between frames.", sendTransforms_callback);
            sim::registerScriptCallbackFunction("simROS.imageTransportSubscribe@ROS", "string subscriberHandle=simROS.imageTransportSubscribe(string topicName,string topicCallback,int queueSize=1)\n\nSubscribe to a topic using ImageTransport.", imageTransportSubscribe_callback);
            sim::registerScriptCallbackFunction("simROS.imageTransportShutdownSubscriber@ROS", "simROS.imageTransportShutdownSubscriber(string subscriberHandle)\n\nUnsubscribe the callback associated with this subscriber using ImageTransport.", imageTransportShutdownSubscriber_callback);
            sim::registerScriptCallbackFunction("simROS.imageTransportAdvertise@ROS", "string publisherHandle=simROS.imageTransportAdvertise(string topicName,int queueSize=1)\n\nAdvertise a topic and create a topic publisher using ImageTransport.", imageTransportAdvertise_callback);
            sim::registerScriptCallbackFunction("simROS.imageTransportShutdownPublisher@ROS", "simROS.imageTransportShutdownPublisher(string publisherHandle)\n\nShutdown the advertisement associated with this publisher using ImageTransport.", imageTransportShutdownPublisher_callback);
            sim::registerScriptCallbackFunction("simROS.imageTransportPublish@ROS", "simROS.imageTransportPublish(string publisherHandle,string data,int width,int height,string frame_id)\n\nPublish a message on the topic associated with this publisher using ImageTransport.", imageTransportPublish_callback);
            sim::registerScriptCallbackFunction("simROS.getTime@ROS", "float time=simROS.getTime(int flag=0)\n\nReturn the current ROS time (i.e. the time returned by ros::Time::now()).", getTime_callback);
            sim::registerScriptCallbackFunction("simROS.getParamString@ROS", "bool exists,string value=simROS.getParamString(string name,string defaultValue=\"\")\n\nRetrieve a string parameter from the ROS Parameter Server.", getParamString_callback);
            sim::registerScriptCallbackFunction("simROS.getParamInt@ROS", "bool exists,int value=simROS.getParamInt(string name,int defaultValue=0)\n\nRetrieve an integer parameter from the ROS Parameter Server.", getParamInt_callback);
            sim::registerScriptCallbackFunction("simROS.getParamDouble@ROS", "bool exists,float value=simROS.getParamDouble(string name,float defaultValue=0.0)\n\nRetrieve a double parameter from the ROS Parameter Server.", getParamDouble_callback);
            sim::registerScriptCallbackFunction("simROS.getParamBool@ROS", "bool exists,bool value=simROS.getParamBool(string name,bool defaultValue=false)\n\nRetrieve a boolean parameter from the ROS Parameter Server.", getParamBool_callback);
            sim::registerScriptCallbackFunction("simROS.setParamString@ROS", "simROS.setParamString(string name,string value)\n\nSet a string parameter in the ROS Parameter Server.", setParamString_callback);
            sim::registerScriptCallbackFunction("simROS.setParamInt@ROS", "simROS.setParamInt(string name,int value)\n\nSet a integer parameter in the ROS Parameter Server.", setParamInt_callback);
            sim::registerScriptCallbackFunction("simROS.setParamDouble@ROS", "simROS.setParamDouble(string name,float value)\n\nSet a double parameter in the ROS Parameter Server.", setParamDouble_callback);
            sim::registerScriptCallbackFunction("simROS.setParamBool@ROS", "simROS.setParamBool(string name,bool value)\n\nSet a boolean parameter in the ROS Parameter Server.", setParamBool_callback);
            sim::registerScriptCallbackFunction("simROS.hasParam@ROS", "bool exists=simROS.hasParam(string name)\n\nCheck wether a parameter exists in the ROS Parameter Server.", hasParam_callback);
            sim::registerScriptCallbackFunction("simROS.deleteParam@ROS", "simROS.deleteParam(string name)\n\nDelete a parameter in the ROS Parameter Server.", deleteParam_callback);
            sim::registerScriptCallbackFunction("simROS.searchParam@ROS", "bool found,string name=simROS.searchParam(string name)\n\nSearch a parameter in the ROS Parameter Server, looking in the closest namespace.", searchParam_callback);

#include "lua_calltips.cpp"
        }
        catch(std::exception &ex)
        {
            throw sim::exception("Initialization failed (registerScriptStuff): %s", ex.what());
        }
    }
    catch(sim::exception& ex)
    {
        sim::addLog(sim_verbosity_errors, ex.what());
        return false;
    }
    return true;
}

subscribe_in::subscribe_in()
{
    queueSize = 1;
    transportHints = {};
}

subscribe_out::subscribe_out()
{
}

void subscribe(SScriptCallBack *p, subscribe_in *in_args, subscribe_out *out_args)
{
    subscribe(p, "simROS.subscribe", in_args, out_args);
}

std::string subscribe(SScriptCallBack *p, std::string topicName, std::string topicType, std::string topicCallback, int queueSize, transport_hints transportHints)
{
    subscribe_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    in_args.topicName = topicName;
    in_args.topicType = topicType;
    in_args.topicCallback = topicCallback;
    in_args.queueSize = queueSize;
    in_args.transportHints = transportHints;
    subscribe_out out_args;
    subscribe(p, &in_args, &out_args);
    return out_args.subscriberHandle;
}

void subscribe(SScriptCallBack *p, subscribe_out *out_args, std::string topicName, std::string topicType, std::string topicCallback, int queueSize, transport_hints transportHints)
{
    subscribe_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    in_args.topicName = topicName;
    in_args.topicType = topicType;
    in_args.topicCallback = topicCallback;
    in_args.queueSize = queueSize;
    in_args.transportHints = transportHints;
    subscribe(p, &in_args, out_args);
}

void subscribe_callback(SScriptCallBack *p)
{
    addStubsDebugLog("subscribe_callback: reading input arguments...");
    addStubsDebugStackDump(p->stackID);

    const char *cmd = "simROS.subscribe";

    subscribe_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    subscribe_out out_args;

    try
    {
        // check argument count

        int numArgs = sim::getStackSize(p->stackID);
        if(numArgs < 3)
            throw sim::exception("not enough arguments");
        if(numArgs > 5)
            throw sim::exception("too many arguments");

        // read input arguments from stack

        if(numArgs >= 1)
        {
            addStubsDebugLog("subscribe_callback: reading input argument 1 \"topicName\" (std::string)...");
            try
            {
                sim::moveStackItemToTop(p->stackID, 0);
                readFromStack(p->stackID, &(in_args.topicName));
            }
            catch(std::exception &ex)
            {
                throw sim::exception("read in arg 1 (topicName): %s", ex.what());
            }
        }

        if(numArgs >= 2)
        {
            addStubsDebugLog("subscribe_callback: reading input argument 2 \"topicType\" (std::string)...");
            try
            {
                sim::moveStackItemToTop(p->stackID, 0);
                readFromStack(p->stackID, &(in_args.topicType));
            }
            catch(std::exception &ex)
            {
                throw sim::exception("read in arg 2 (topicType): %s", ex.what());
            }
        }

        if(numArgs >= 3)
        {
            addStubsDebugLog("subscribe_callback: reading input argument 3 \"topicCallback\" (std::string)...");
            try
            {
                sim::moveStackItemToTop(p->stackID, 0);
                readFromStack(p->stackID, &(in_args.topicCallback));
            }
            catch(std::exception &ex)
            {
                throw sim::exception("read in arg 3 (topicCallback): %s", ex.what());
            }
        }

        if(numArgs >= 4)
        {
            addStubsDebugLog("subscribe_callback: reading input argument 4 \"queueSize\" (int)...");
            try
            {
                sim::moveStackItemToTop(p->stackID, 0);
                readFromStack(p->stackID, &(in_args.queueSize));
            }
            catch(std::exception &ex)
            {
                throw sim::exception("read in arg 4 (queueSize): %s", ex.what());
            }
        }

        if(numArgs >= 5)
        {
            addStubsDebugLog("subscribe_callback: reading input argument 5 \"transportHints\" (transport_hints)...");
            try
            {
                sim::moveStackItemToTop(p->stackID, 0);
                readFromStack(p->stackID, &(in_args.transportHints));
            }
            catch(std::exception &ex)
            {
                throw sim::exception("read in arg 5 (transportHints): %s", ex.what());
            }
        }


        addStubsDebugLog("subscribe_callback: stack content after reading input arguments:");
        addStubsDebugStackDump(p->stackID);

        addStubsDebugLog("subscribe_callback: clearing stack content after reading input arguments");
        // clear stack
        sim::popStackItem(p->stackID, 0);


        addStubsDebugLog("subscribe_callback: calling callback (subscribe)");
        subscribe(p, cmd, &in_args, &out_args);
    }
    catch(std::exception &ex)
    {
        sim::setLastError(cmd, ex.what());
    }

    try
    {
        addStubsDebugLog("subscribe_callback: writing output arguments...");
        addStubsDebugStackDump(p->stackID);

        addStubsDebugLog("subscribe_callback: clearing stack content before writing output arguments");
        // clear stack
        sim::popStackItem(p->stackID, 0);


        // write output arguments to stack

        addStubsDebugLog("subscribe_callback: writing output argument 1 \"subscriberHandle\" (std::string)...");
        try
        {
            writeToStack(out_args.subscriberHandle, p->stackID);
        }
        catch(std::exception &ex)
        {
            throw sim::exception("write out arg 1 (subscriberHandle): %s", ex.what());
        }

        addStubsDebugLog("subscribe_callback: stack content after writing output arguments:");
        addStubsDebugStackDump(p->stackID);
    }
    catch(std::exception &ex)
    {
        sim::setLastError(cmd, ex.what());
        // clear stack
        try { sim::popStackItem(p->stackID, 0); } catch(...) {}
    }

    addStubsDebugLog("subscribe_callback: finished");
}

shutdownSubscriber_in::shutdownSubscriber_in()
{
}

shutdownSubscriber_out::shutdownSubscriber_out()
{
}

void shutdownSubscriber(SScriptCallBack *p, shutdownSubscriber_in *in_args, shutdownSubscriber_out *out_args)
{
    shutdownSubscriber(p, "simROS.shutdownSubscriber", in_args, out_args);
}

void shutdownSubscriber(SScriptCallBack *p, std::string subscriberHandle)
{
    shutdownSubscriber_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    in_args.subscriberHandle = subscriberHandle;
    shutdownSubscriber_out out_args;
    shutdownSubscriber(p, &in_args, &out_args);
}

void shutdownSubscriber(SScriptCallBack *p, shutdownSubscriber_out *out_args, std::string subscriberHandle)
{
    shutdownSubscriber_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    in_args.subscriberHandle = subscriberHandle;
    shutdownSubscriber(p, &in_args, out_args);
}

void shutdownSubscriber_callback(SScriptCallBack *p)
{
    addStubsDebugLog("shutdownSubscriber_callback: reading input arguments...");
    addStubsDebugStackDump(p->stackID);

    const char *cmd = "simROS.shutdownSubscriber";

    shutdownSubscriber_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    shutdownSubscriber_out out_args;

    try
    {
        // check argument count

        int numArgs = sim::getStackSize(p->stackID);
        if(numArgs < 1)
            throw sim::exception("not enough arguments");
        if(numArgs > 1)
            throw sim::exception("too many arguments");

        // read input arguments from stack

        if(numArgs >= 1)
        {
            addStubsDebugLog("shutdownSubscriber_callback: reading input argument 1 \"subscriberHandle\" (std::string)...");
            try
            {
                sim::moveStackItemToTop(p->stackID, 0);
                readFromStack(p->stackID, &(in_args.subscriberHandle));
            }
            catch(std::exception &ex)
            {
                throw sim::exception("read in arg 1 (subscriberHandle): %s", ex.what());
            }
        }


        addStubsDebugLog("shutdownSubscriber_callback: stack content after reading input arguments:");
        addStubsDebugStackDump(p->stackID);

        addStubsDebugLog("shutdownSubscriber_callback: clearing stack content after reading input arguments");
        // clear stack
        sim::popStackItem(p->stackID, 0);


        addStubsDebugLog("shutdownSubscriber_callback: calling callback (shutdownSubscriber)");
        shutdownSubscriber(p, cmd, &in_args, &out_args);
    }
    catch(std::exception &ex)
    {
        sim::setLastError(cmd, ex.what());
    }

    try
    {
        addStubsDebugLog("shutdownSubscriber_callback: writing output arguments...");
        addStubsDebugStackDump(p->stackID);

        addStubsDebugLog("shutdownSubscriber_callback: clearing stack content before writing output arguments");
        // clear stack
        sim::popStackItem(p->stackID, 0);


        // write output arguments to stack


        addStubsDebugLog("shutdownSubscriber_callback: stack content after writing output arguments:");
        addStubsDebugStackDump(p->stackID);
    }
    catch(std::exception &ex)
    {
        sim::setLastError(cmd, ex.what());
        // clear stack
        try { sim::popStackItem(p->stackID, 0); } catch(...) {}
    }

    addStubsDebugLog("shutdownSubscriber_callback: finished");
}

subscriberTreatUInt8ArrayAsString_in::subscriberTreatUInt8ArrayAsString_in()
{
}

subscriberTreatUInt8ArrayAsString_out::subscriberTreatUInt8ArrayAsString_out()
{
}

void subscriberTreatUInt8ArrayAsString(SScriptCallBack *p, subscriberTreatUInt8ArrayAsString_in *in_args, subscriberTreatUInt8ArrayAsString_out *out_args)
{
    subscriberTreatUInt8ArrayAsString(p, "simROS.subscriberTreatUInt8ArrayAsString", in_args, out_args);
}

void subscriberTreatUInt8ArrayAsString(SScriptCallBack *p, std::string subscriberHandle)
{
    subscriberTreatUInt8ArrayAsString_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    in_args.subscriberHandle = subscriberHandle;
    subscriberTreatUInt8ArrayAsString_out out_args;
    subscriberTreatUInt8ArrayAsString(p, &in_args, &out_args);
}

void subscriberTreatUInt8ArrayAsString(SScriptCallBack *p, subscriberTreatUInt8ArrayAsString_out *out_args, std::string subscriberHandle)
{
    subscriberTreatUInt8ArrayAsString_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    in_args.subscriberHandle = subscriberHandle;
    subscriberTreatUInt8ArrayAsString(p, &in_args, out_args);
}

void subscriberTreatUInt8ArrayAsString_callback(SScriptCallBack *p)
{
    addStubsDebugLog("subscriberTreatUInt8ArrayAsString_callback: reading input arguments...");
    addStubsDebugStackDump(p->stackID);

    const char *cmd = "simROS.subscriberTreatUInt8ArrayAsString";

    subscriberTreatUInt8ArrayAsString_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    subscriberTreatUInt8ArrayAsString_out out_args;

    try
    {
        // check argument count

        int numArgs = sim::getStackSize(p->stackID);
        if(numArgs < 1)
            throw sim::exception("not enough arguments");
        if(numArgs > 1)
            throw sim::exception("too many arguments");

        // read input arguments from stack

        if(numArgs >= 1)
        {
            addStubsDebugLog("subscriberTreatUInt8ArrayAsString_callback: reading input argument 1 \"subscriberHandle\" (std::string)...");
            try
            {
                sim::moveStackItemToTop(p->stackID, 0);
                readFromStack(p->stackID, &(in_args.subscriberHandle));
            }
            catch(std::exception &ex)
            {
                throw sim::exception("read in arg 1 (subscriberHandle): %s", ex.what());
            }
        }


        addStubsDebugLog("subscriberTreatUInt8ArrayAsString_callback: stack content after reading input arguments:");
        addStubsDebugStackDump(p->stackID);

        addStubsDebugLog("subscriberTreatUInt8ArrayAsString_callback: clearing stack content after reading input arguments");
        // clear stack
        sim::popStackItem(p->stackID, 0);


        addStubsDebugLog("subscriberTreatUInt8ArrayAsString_callback: calling callback (subscriberTreatUInt8ArrayAsString)");
        subscriberTreatUInt8ArrayAsString(p, cmd, &in_args, &out_args);
    }
    catch(std::exception &ex)
    {
        sim::setLastError(cmd, ex.what());
    }

    try
    {
        addStubsDebugLog("subscriberTreatUInt8ArrayAsString_callback: writing output arguments...");
        addStubsDebugStackDump(p->stackID);

        addStubsDebugLog("subscriberTreatUInt8ArrayAsString_callback: clearing stack content before writing output arguments");
        // clear stack
        sim::popStackItem(p->stackID, 0);


        // write output arguments to stack


        addStubsDebugLog("subscriberTreatUInt8ArrayAsString_callback: stack content after writing output arguments:");
        addStubsDebugStackDump(p->stackID);
    }
    catch(std::exception &ex)
    {
        sim::setLastError(cmd, ex.what());
        // clear stack
        try { sim::popStackItem(p->stackID, 0); } catch(...) {}
    }

    addStubsDebugLog("subscriberTreatUInt8ArrayAsString_callback: finished");
}

advertise_in::advertise_in()
{
    queueSize = 1;
    latch = false;
}

advertise_out::advertise_out()
{
}

void advertise(SScriptCallBack *p, advertise_in *in_args, advertise_out *out_args)
{
    advertise(p, "simROS.advertise", in_args, out_args);
}

std::string advertise(SScriptCallBack *p, std::string topicName, std::string topicType, int queueSize, bool latch)
{
    advertise_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    in_args.topicName = topicName;
    in_args.topicType = topicType;
    in_args.queueSize = queueSize;
    in_args.latch = latch;
    advertise_out out_args;
    advertise(p, &in_args, &out_args);
    return out_args.publisherHandle;
}

void advertise(SScriptCallBack *p, advertise_out *out_args, std::string topicName, std::string topicType, int queueSize, bool latch)
{
    advertise_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    in_args.topicName = topicName;
    in_args.topicType = topicType;
    in_args.queueSize = queueSize;
    in_args.latch = latch;
    advertise(p, &in_args, out_args);
}

void advertise_callback(SScriptCallBack *p)
{
    addStubsDebugLog("advertise_callback: reading input arguments...");
    addStubsDebugStackDump(p->stackID);

    const char *cmd = "simROS.advertise";

    advertise_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    advertise_out out_args;

    try
    {
        // check argument count

        int numArgs = sim::getStackSize(p->stackID);
        if(numArgs < 2)
            throw sim::exception("not enough arguments");
        if(numArgs > 4)
            throw sim::exception("too many arguments");

        // read input arguments from stack

        if(numArgs >= 1)
        {
            addStubsDebugLog("advertise_callback: reading input argument 1 \"topicName\" (std::string)...");
            try
            {
                sim::moveStackItemToTop(p->stackID, 0);
                readFromStack(p->stackID, &(in_args.topicName));
            }
            catch(std::exception &ex)
            {
                throw sim::exception("read in arg 1 (topicName): %s", ex.what());
            }
        }

        if(numArgs >= 2)
        {
            addStubsDebugLog("advertise_callback: reading input argument 2 \"topicType\" (std::string)...");
            try
            {
                sim::moveStackItemToTop(p->stackID, 0);
                readFromStack(p->stackID, &(in_args.topicType));
            }
            catch(std::exception &ex)
            {
                throw sim::exception("read in arg 2 (topicType): %s", ex.what());
            }
        }

        if(numArgs >= 3)
        {
            addStubsDebugLog("advertise_callback: reading input argument 3 \"queueSize\" (int)...");
            try
            {
                sim::moveStackItemToTop(p->stackID, 0);
                readFromStack(p->stackID, &(in_args.queueSize));
            }
            catch(std::exception &ex)
            {
                throw sim::exception("read in arg 3 (queueSize): %s", ex.what());
            }
        }

        if(numArgs >= 4)
        {
            addStubsDebugLog("advertise_callback: reading input argument 4 \"latch\" (bool)...");
            try
            {
                sim::moveStackItemToTop(p->stackID, 0);
                readFromStack(p->stackID, &(in_args.latch));
            }
            catch(std::exception &ex)
            {
                throw sim::exception("read in arg 4 (latch): %s", ex.what());
            }
        }


        addStubsDebugLog("advertise_callback: stack content after reading input arguments:");
        addStubsDebugStackDump(p->stackID);

        addStubsDebugLog("advertise_callback: clearing stack content after reading input arguments");
        // clear stack
        sim::popStackItem(p->stackID, 0);


        addStubsDebugLog("advertise_callback: calling callback (advertise)");
        advertise(p, cmd, &in_args, &out_args);
    }
    catch(std::exception &ex)
    {
        sim::setLastError(cmd, ex.what());
    }

    try
    {
        addStubsDebugLog("advertise_callback: writing output arguments...");
        addStubsDebugStackDump(p->stackID);

        addStubsDebugLog("advertise_callback: clearing stack content before writing output arguments");
        // clear stack
        sim::popStackItem(p->stackID, 0);


        // write output arguments to stack

        addStubsDebugLog("advertise_callback: writing output argument 1 \"publisherHandle\" (std::string)...");
        try
        {
            writeToStack(out_args.publisherHandle, p->stackID);
        }
        catch(std::exception &ex)
        {
            throw sim::exception("write out arg 1 (publisherHandle): %s", ex.what());
        }

        addStubsDebugLog("advertise_callback: stack content after writing output arguments:");
        addStubsDebugStackDump(p->stackID);
    }
    catch(std::exception &ex)
    {
        sim::setLastError(cmd, ex.what());
        // clear stack
        try { sim::popStackItem(p->stackID, 0); } catch(...) {}
    }

    addStubsDebugLog("advertise_callback: finished");
}

shutdownPublisher_in::shutdownPublisher_in()
{
}

shutdownPublisher_out::shutdownPublisher_out()
{
}

void shutdownPublisher(SScriptCallBack *p, shutdownPublisher_in *in_args, shutdownPublisher_out *out_args)
{
    shutdownPublisher(p, "simROS.shutdownPublisher", in_args, out_args);
}

void shutdownPublisher(SScriptCallBack *p, std::string publisherHandle)
{
    shutdownPublisher_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    in_args.publisherHandle = publisherHandle;
    shutdownPublisher_out out_args;
    shutdownPublisher(p, &in_args, &out_args);
}

void shutdownPublisher(SScriptCallBack *p, shutdownPublisher_out *out_args, std::string publisherHandle)
{
    shutdownPublisher_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    in_args.publisherHandle = publisherHandle;
    shutdownPublisher(p, &in_args, out_args);
}

void shutdownPublisher_callback(SScriptCallBack *p)
{
    addStubsDebugLog("shutdownPublisher_callback: reading input arguments...");
    addStubsDebugStackDump(p->stackID);

    const char *cmd = "simROS.shutdownPublisher";

    shutdownPublisher_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    shutdownPublisher_out out_args;

    try
    {
        // check argument count

        int numArgs = sim::getStackSize(p->stackID);
        if(numArgs < 1)
            throw sim::exception("not enough arguments");
        if(numArgs > 1)
            throw sim::exception("too many arguments");

        // read input arguments from stack

        if(numArgs >= 1)
        {
            addStubsDebugLog("shutdownPublisher_callback: reading input argument 1 \"publisherHandle\" (std::string)...");
            try
            {
                sim::moveStackItemToTop(p->stackID, 0);
                readFromStack(p->stackID, &(in_args.publisherHandle));
            }
            catch(std::exception &ex)
            {
                throw sim::exception("read in arg 1 (publisherHandle): %s", ex.what());
            }
        }


        addStubsDebugLog("shutdownPublisher_callback: stack content after reading input arguments:");
        addStubsDebugStackDump(p->stackID);

        addStubsDebugLog("shutdownPublisher_callback: clearing stack content after reading input arguments");
        // clear stack
        sim::popStackItem(p->stackID, 0);


        addStubsDebugLog("shutdownPublisher_callback: calling callback (shutdownPublisher)");
        shutdownPublisher(p, cmd, &in_args, &out_args);
    }
    catch(std::exception &ex)
    {
        sim::setLastError(cmd, ex.what());
    }

    try
    {
        addStubsDebugLog("shutdownPublisher_callback: writing output arguments...");
        addStubsDebugStackDump(p->stackID);

        addStubsDebugLog("shutdownPublisher_callback: clearing stack content before writing output arguments");
        // clear stack
        sim::popStackItem(p->stackID, 0);


        // write output arguments to stack


        addStubsDebugLog("shutdownPublisher_callback: stack content after writing output arguments:");
        addStubsDebugStackDump(p->stackID);
    }
    catch(std::exception &ex)
    {
        sim::setLastError(cmd, ex.what());
        // clear stack
        try { sim::popStackItem(p->stackID, 0); } catch(...) {}
    }

    addStubsDebugLog("shutdownPublisher_callback: finished");
}

publisherTreatUInt8ArrayAsString_in::publisherTreatUInt8ArrayAsString_in()
{
}

publisherTreatUInt8ArrayAsString_out::publisherTreatUInt8ArrayAsString_out()
{
}

void publisherTreatUInt8ArrayAsString(SScriptCallBack *p, publisherTreatUInt8ArrayAsString_in *in_args, publisherTreatUInt8ArrayAsString_out *out_args)
{
    publisherTreatUInt8ArrayAsString(p, "simROS.publisherTreatUInt8ArrayAsString", in_args, out_args);
}

void publisherTreatUInt8ArrayAsString(SScriptCallBack *p, std::string publisherHandle)
{
    publisherTreatUInt8ArrayAsString_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    in_args.publisherHandle = publisherHandle;
    publisherTreatUInt8ArrayAsString_out out_args;
    publisherTreatUInt8ArrayAsString(p, &in_args, &out_args);
}

void publisherTreatUInt8ArrayAsString(SScriptCallBack *p, publisherTreatUInt8ArrayAsString_out *out_args, std::string publisherHandle)
{
    publisherTreatUInt8ArrayAsString_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    in_args.publisherHandle = publisherHandle;
    publisherTreatUInt8ArrayAsString(p, &in_args, out_args);
}

void publisherTreatUInt8ArrayAsString_callback(SScriptCallBack *p)
{
    addStubsDebugLog("publisherTreatUInt8ArrayAsString_callback: reading input arguments...");
    addStubsDebugStackDump(p->stackID);

    const char *cmd = "simROS.publisherTreatUInt8ArrayAsString";

    publisherTreatUInt8ArrayAsString_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    publisherTreatUInt8ArrayAsString_out out_args;

    try
    {
        // check argument count

        int numArgs = sim::getStackSize(p->stackID);
        if(numArgs < 1)
            throw sim::exception("not enough arguments");
        if(numArgs > 1)
            throw sim::exception("too many arguments");

        // read input arguments from stack

        if(numArgs >= 1)
        {
            addStubsDebugLog("publisherTreatUInt8ArrayAsString_callback: reading input argument 1 \"publisherHandle\" (std::string)...");
            try
            {
                sim::moveStackItemToTop(p->stackID, 0);
                readFromStack(p->stackID, &(in_args.publisherHandle));
            }
            catch(std::exception &ex)
            {
                throw sim::exception("read in arg 1 (publisherHandle): %s", ex.what());
            }
        }


        addStubsDebugLog("publisherTreatUInt8ArrayAsString_callback: stack content after reading input arguments:");
        addStubsDebugStackDump(p->stackID);

        addStubsDebugLog("publisherTreatUInt8ArrayAsString_callback: clearing stack content after reading input arguments");
        // clear stack
        sim::popStackItem(p->stackID, 0);


        addStubsDebugLog("publisherTreatUInt8ArrayAsString_callback: calling callback (publisherTreatUInt8ArrayAsString)");
        publisherTreatUInt8ArrayAsString(p, cmd, &in_args, &out_args);
    }
    catch(std::exception &ex)
    {
        sim::setLastError(cmd, ex.what());
    }

    try
    {
        addStubsDebugLog("publisherTreatUInt8ArrayAsString_callback: writing output arguments...");
        addStubsDebugStackDump(p->stackID);

        addStubsDebugLog("publisherTreatUInt8ArrayAsString_callback: clearing stack content before writing output arguments");
        // clear stack
        sim::popStackItem(p->stackID, 0);


        // write output arguments to stack


        addStubsDebugLog("publisherTreatUInt8ArrayAsString_callback: stack content after writing output arguments:");
        addStubsDebugStackDump(p->stackID);
    }
    catch(std::exception &ex)
    {
        sim::setLastError(cmd, ex.what());
        // clear stack
        try { sim::popStackItem(p->stackID, 0); } catch(...) {}
    }

    addStubsDebugLog("publisherTreatUInt8ArrayAsString_callback: finished");
}

publish_in::publish_in()
{
}

publish_out::publish_out()
{
}

void publish(SScriptCallBack *p, publish_in *in_args, publish_out *out_args)
{
    publish(p, "simROS.publish", in_args, out_args);
}

void publish(SScriptCallBack *p, std::string publisherHandle)
{
    publish_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    in_args.publisherHandle = publisherHandle;
    publish_out out_args;
    publish(p, &in_args, &out_args);
}

void publish(SScriptCallBack *p, publish_out *out_args, std::string publisherHandle)
{
    publish_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    in_args.publisherHandle = publisherHandle;
    publish(p, &in_args, out_args);
}

void publish_callback(SScriptCallBack *p)
{
    addStubsDebugLog("publish_callback: reading input arguments...");
    addStubsDebugStackDump(p->stackID);

    const char *cmd = "simROS.publish";

    publish_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    publish_out out_args;

    try
    {
        // check argument count

        int numArgs = sim::getStackSize(p->stackID);
        if(numArgs < 1)
            throw sim::exception("not enough arguments");
        if(numArgs > 2)
            throw sim::exception("too many arguments");

        // read input arguments from stack

        if(numArgs >= 1)
        {
            addStubsDebugLog("publish_callback: reading input argument 1 \"publisherHandle\" (std::string)...");
            try
            {
                sim::moveStackItemToTop(p->stackID, 0);
                readFromStack(p->stackID, &(in_args.publisherHandle));
            }
            catch(std::exception &ex)
            {
                throw sim::exception("read in arg 1 (publisherHandle): %s", ex.what());
            }
        }


        addStubsDebugLog("publish_callback: stack content after reading input arguments:");
        addStubsDebugStackDump(p->stackID);


        addStubsDebugLog("publish_callback: calling callback (publish)");
        publish(p, cmd, &in_args, &out_args);
    }
    catch(std::exception &ex)
    {
        sim::setLastError(cmd, ex.what());
    }

    try
    {
        addStubsDebugLog("publish_callback: writing output arguments...");
        addStubsDebugStackDump(p->stackID);

        addStubsDebugLog("publish_callback: clearing stack content before writing output arguments");
        // clear stack
        sim::popStackItem(p->stackID, 0);


        // write output arguments to stack


        addStubsDebugLog("publish_callback: stack content after writing output arguments:");
        addStubsDebugStackDump(p->stackID);
    }
    catch(std::exception &ex)
    {
        sim::setLastError(cmd, ex.what());
        // clear stack
        try { sim::popStackItem(p->stackID, 0); } catch(...) {}
    }

    addStubsDebugLog("publish_callback: finished");
}

serviceClient_in::serviceClient_in()
{
}

serviceClient_out::serviceClient_out()
{
}

void serviceClient(SScriptCallBack *p, serviceClient_in *in_args, serviceClient_out *out_args)
{
    serviceClient(p, "simROS.serviceClient", in_args, out_args);
}

std::string serviceClient(SScriptCallBack *p, std::string serviceName, std::string serviceType)
{
    serviceClient_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    in_args.serviceName = serviceName;
    in_args.serviceType = serviceType;
    serviceClient_out out_args;
    serviceClient(p, &in_args, &out_args);
    return out_args.serviceClientHandle;
}

void serviceClient(SScriptCallBack *p, serviceClient_out *out_args, std::string serviceName, std::string serviceType)
{
    serviceClient_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    in_args.serviceName = serviceName;
    in_args.serviceType = serviceType;
    serviceClient(p, &in_args, out_args);
}

void serviceClient_callback(SScriptCallBack *p)
{
    addStubsDebugLog("serviceClient_callback: reading input arguments...");
    addStubsDebugStackDump(p->stackID);

    const char *cmd = "simROS.serviceClient";

    serviceClient_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    serviceClient_out out_args;

    try
    {
        // check argument count

        int numArgs = sim::getStackSize(p->stackID);
        if(numArgs < 2)
            throw sim::exception("not enough arguments");
        if(numArgs > 2)
            throw sim::exception("too many arguments");

        // read input arguments from stack

        if(numArgs >= 1)
        {
            addStubsDebugLog("serviceClient_callback: reading input argument 1 \"serviceName\" (std::string)...");
            try
            {
                sim::moveStackItemToTop(p->stackID, 0);
                readFromStack(p->stackID, &(in_args.serviceName));
            }
            catch(std::exception &ex)
            {
                throw sim::exception("read in arg 1 (serviceName): %s", ex.what());
            }
        }

        if(numArgs >= 2)
        {
            addStubsDebugLog("serviceClient_callback: reading input argument 2 \"serviceType\" (std::string)...");
            try
            {
                sim::moveStackItemToTop(p->stackID, 0);
                readFromStack(p->stackID, &(in_args.serviceType));
            }
            catch(std::exception &ex)
            {
                throw sim::exception("read in arg 2 (serviceType): %s", ex.what());
            }
        }


        addStubsDebugLog("serviceClient_callback: stack content after reading input arguments:");
        addStubsDebugStackDump(p->stackID);

        addStubsDebugLog("serviceClient_callback: clearing stack content after reading input arguments");
        // clear stack
        sim::popStackItem(p->stackID, 0);


        addStubsDebugLog("serviceClient_callback: calling callback (serviceClient)");
        serviceClient(p, cmd, &in_args, &out_args);
    }
    catch(std::exception &ex)
    {
        sim::setLastError(cmd, ex.what());
    }

    try
    {
        addStubsDebugLog("serviceClient_callback: writing output arguments...");
        addStubsDebugStackDump(p->stackID);

        addStubsDebugLog("serviceClient_callback: clearing stack content before writing output arguments");
        // clear stack
        sim::popStackItem(p->stackID, 0);


        // write output arguments to stack

        addStubsDebugLog("serviceClient_callback: writing output argument 1 \"serviceClientHandle\" (std::string)...");
        try
        {
            writeToStack(out_args.serviceClientHandle, p->stackID);
        }
        catch(std::exception &ex)
        {
            throw sim::exception("write out arg 1 (serviceClientHandle): %s", ex.what());
        }

        addStubsDebugLog("serviceClient_callback: stack content after writing output arguments:");
        addStubsDebugStackDump(p->stackID);
    }
    catch(std::exception &ex)
    {
        sim::setLastError(cmd, ex.what());
        // clear stack
        try { sim::popStackItem(p->stackID, 0); } catch(...) {}
    }

    addStubsDebugLog("serviceClient_callback: finished");
}

shutdownServiceClient_in::shutdownServiceClient_in()
{
}

shutdownServiceClient_out::shutdownServiceClient_out()
{
}

void shutdownServiceClient(SScriptCallBack *p, shutdownServiceClient_in *in_args, shutdownServiceClient_out *out_args)
{
    shutdownServiceClient(p, "simROS.shutdownServiceClient", in_args, out_args);
}

void shutdownServiceClient(SScriptCallBack *p, std::string serviceClientHandle)
{
    shutdownServiceClient_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    in_args.serviceClientHandle = serviceClientHandle;
    shutdownServiceClient_out out_args;
    shutdownServiceClient(p, &in_args, &out_args);
}

void shutdownServiceClient(SScriptCallBack *p, shutdownServiceClient_out *out_args, std::string serviceClientHandle)
{
    shutdownServiceClient_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    in_args.serviceClientHandle = serviceClientHandle;
    shutdownServiceClient(p, &in_args, out_args);
}

void shutdownServiceClient_callback(SScriptCallBack *p)
{
    addStubsDebugLog("shutdownServiceClient_callback: reading input arguments...");
    addStubsDebugStackDump(p->stackID);

    const char *cmd = "simROS.shutdownServiceClient";

    shutdownServiceClient_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    shutdownServiceClient_out out_args;

    try
    {
        // check argument count

        int numArgs = sim::getStackSize(p->stackID);
        if(numArgs < 1)
            throw sim::exception("not enough arguments");
        if(numArgs > 1)
            throw sim::exception("too many arguments");

        // read input arguments from stack

        if(numArgs >= 1)
        {
            addStubsDebugLog("shutdownServiceClient_callback: reading input argument 1 \"serviceClientHandle\" (std::string)...");
            try
            {
                sim::moveStackItemToTop(p->stackID, 0);
                readFromStack(p->stackID, &(in_args.serviceClientHandle));
            }
            catch(std::exception &ex)
            {
                throw sim::exception("read in arg 1 (serviceClientHandle): %s", ex.what());
            }
        }


        addStubsDebugLog("shutdownServiceClient_callback: stack content after reading input arguments:");
        addStubsDebugStackDump(p->stackID);

        addStubsDebugLog("shutdownServiceClient_callback: clearing stack content after reading input arguments");
        // clear stack
        sim::popStackItem(p->stackID, 0);


        addStubsDebugLog("shutdownServiceClient_callback: calling callback (shutdownServiceClient)");
        shutdownServiceClient(p, cmd, &in_args, &out_args);
    }
    catch(std::exception &ex)
    {
        sim::setLastError(cmd, ex.what());
    }

    try
    {
        addStubsDebugLog("shutdownServiceClient_callback: writing output arguments...");
        addStubsDebugStackDump(p->stackID);

        addStubsDebugLog("shutdownServiceClient_callback: clearing stack content before writing output arguments");
        // clear stack
        sim::popStackItem(p->stackID, 0);


        // write output arguments to stack


        addStubsDebugLog("shutdownServiceClient_callback: stack content after writing output arguments:");
        addStubsDebugStackDump(p->stackID);
    }
    catch(std::exception &ex)
    {
        sim::setLastError(cmd, ex.what());
        // clear stack
        try { sim::popStackItem(p->stackID, 0); } catch(...) {}
    }

    addStubsDebugLog("shutdownServiceClient_callback: finished");
}

serviceClientTreatUInt8ArrayAsString_in::serviceClientTreatUInt8ArrayAsString_in()
{
}

serviceClientTreatUInt8ArrayAsString_out::serviceClientTreatUInt8ArrayAsString_out()
{
}

void serviceClientTreatUInt8ArrayAsString(SScriptCallBack *p, serviceClientTreatUInt8ArrayAsString_in *in_args, serviceClientTreatUInt8ArrayAsString_out *out_args)
{
    serviceClientTreatUInt8ArrayAsString(p, "simROS.serviceClientTreatUInt8ArrayAsString", in_args, out_args);
}

void serviceClientTreatUInt8ArrayAsString(SScriptCallBack *p, std::string serviceClientHandle)
{
    serviceClientTreatUInt8ArrayAsString_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    in_args.serviceClientHandle = serviceClientHandle;
    serviceClientTreatUInt8ArrayAsString_out out_args;
    serviceClientTreatUInt8ArrayAsString(p, &in_args, &out_args);
}

void serviceClientTreatUInt8ArrayAsString(SScriptCallBack *p, serviceClientTreatUInt8ArrayAsString_out *out_args, std::string serviceClientHandle)
{
    serviceClientTreatUInt8ArrayAsString_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    in_args.serviceClientHandle = serviceClientHandle;
    serviceClientTreatUInt8ArrayAsString(p, &in_args, out_args);
}

void serviceClientTreatUInt8ArrayAsString_callback(SScriptCallBack *p)
{
    addStubsDebugLog("serviceClientTreatUInt8ArrayAsString_callback: reading input arguments...");
    addStubsDebugStackDump(p->stackID);

    const char *cmd = "simROS.serviceClientTreatUInt8ArrayAsString";

    serviceClientTreatUInt8ArrayAsString_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    serviceClientTreatUInt8ArrayAsString_out out_args;

    try
    {
        // check argument count

        int numArgs = sim::getStackSize(p->stackID);
        if(numArgs < 1)
            throw sim::exception("not enough arguments");
        if(numArgs > 1)
            throw sim::exception("too many arguments");

        // read input arguments from stack

        if(numArgs >= 1)
        {
            addStubsDebugLog("serviceClientTreatUInt8ArrayAsString_callback: reading input argument 1 \"serviceClientHandle\" (std::string)...");
            try
            {
                sim::moveStackItemToTop(p->stackID, 0);
                readFromStack(p->stackID, &(in_args.serviceClientHandle));
            }
            catch(std::exception &ex)
            {
                throw sim::exception("read in arg 1 (serviceClientHandle): %s", ex.what());
            }
        }


        addStubsDebugLog("serviceClientTreatUInt8ArrayAsString_callback: stack content after reading input arguments:");
        addStubsDebugStackDump(p->stackID);

        addStubsDebugLog("serviceClientTreatUInt8ArrayAsString_callback: clearing stack content after reading input arguments");
        // clear stack
        sim::popStackItem(p->stackID, 0);


        addStubsDebugLog("serviceClientTreatUInt8ArrayAsString_callback: calling callback (serviceClientTreatUInt8ArrayAsString)");
        serviceClientTreatUInt8ArrayAsString(p, cmd, &in_args, &out_args);
    }
    catch(std::exception &ex)
    {
        sim::setLastError(cmd, ex.what());
    }

    try
    {
        addStubsDebugLog("serviceClientTreatUInt8ArrayAsString_callback: writing output arguments...");
        addStubsDebugStackDump(p->stackID);

        addStubsDebugLog("serviceClientTreatUInt8ArrayAsString_callback: clearing stack content before writing output arguments");
        // clear stack
        sim::popStackItem(p->stackID, 0);


        // write output arguments to stack


        addStubsDebugLog("serviceClientTreatUInt8ArrayAsString_callback: stack content after writing output arguments:");
        addStubsDebugStackDump(p->stackID);
    }
    catch(std::exception &ex)
    {
        sim::setLastError(cmd, ex.what());
        // clear stack
        try { sim::popStackItem(p->stackID, 0); } catch(...) {}
    }

    addStubsDebugLog("serviceClientTreatUInt8ArrayAsString_callback: finished");
}

call_in::call_in()
{
}

call_out::call_out()
{
}

void call(SScriptCallBack *p, call_in *in_args, call_out *out_args)
{
    call(p, "simROS.call", in_args, out_args);
}

void call(SScriptCallBack *p, std::string serviceClientHandle)
{
    call_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    in_args.serviceClientHandle = serviceClientHandle;
    call_out out_args;
    call(p, &in_args, &out_args);
}

void call(SScriptCallBack *p, call_out *out_args, std::string serviceClientHandle)
{
    call_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    in_args.serviceClientHandle = serviceClientHandle;
    call(p, &in_args, out_args);
}

void call_callback(SScriptCallBack *p)
{
    addStubsDebugLog("call_callback: reading input arguments...");
    addStubsDebugStackDump(p->stackID);

    const char *cmd = "simROS.call";

    call_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    call_out out_args;

    try
    {
        // check argument count

        int numArgs = sim::getStackSize(p->stackID);
        if(numArgs < 1)
            throw sim::exception("not enough arguments");
        if(numArgs > 2)
            throw sim::exception("too many arguments");

        // read input arguments from stack

        if(numArgs >= 1)
        {
            addStubsDebugLog("call_callback: reading input argument 1 \"serviceClientHandle\" (std::string)...");
            try
            {
                sim::moveStackItemToTop(p->stackID, 0);
                readFromStack(p->stackID, &(in_args.serviceClientHandle));
            }
            catch(std::exception &ex)
            {
                throw sim::exception("read in arg 1 (serviceClientHandle): %s", ex.what());
            }
        }


        addStubsDebugLog("call_callback: stack content after reading input arguments:");
        addStubsDebugStackDump(p->stackID);


        addStubsDebugLog("call_callback: calling callback (call)");
        call(p, cmd, &in_args, &out_args);
    }
    catch(std::exception &ex)
    {
        sim::setLastError(cmd, ex.what());
    }

    try
    {
        addStubsDebugLog("call_callback: writing output arguments...");
        addStubsDebugStackDump(p->stackID);


        // write output arguments to stack


        addStubsDebugLog("call_callback: stack content after writing output arguments:");
        addStubsDebugStackDump(p->stackID);
    }
    catch(std::exception &ex)
    {
        sim::setLastError(cmd, ex.what());
        // clear stack
        try { sim::popStackItem(p->stackID, 0); } catch(...) {}
    }

    addStubsDebugLog("call_callback: finished");
}

advertiseService_in::advertiseService_in()
{
}

advertiseService_out::advertiseService_out()
{
}

void advertiseService(SScriptCallBack *p, advertiseService_in *in_args, advertiseService_out *out_args)
{
    advertiseService(p, "simROS.advertiseService", in_args, out_args);
}

std::string advertiseService(SScriptCallBack *p, std::string serviceName, std::string serviceType, std::string serviceCallback)
{
    advertiseService_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    in_args.serviceName = serviceName;
    in_args.serviceType = serviceType;
    in_args.serviceCallback = serviceCallback;
    advertiseService_out out_args;
    advertiseService(p, &in_args, &out_args);
    return out_args.serviceServerHandle;
}

void advertiseService(SScriptCallBack *p, advertiseService_out *out_args, std::string serviceName, std::string serviceType, std::string serviceCallback)
{
    advertiseService_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    in_args.serviceName = serviceName;
    in_args.serviceType = serviceType;
    in_args.serviceCallback = serviceCallback;
    advertiseService(p, &in_args, out_args);
}

void advertiseService_callback(SScriptCallBack *p)
{
    addStubsDebugLog("advertiseService_callback: reading input arguments...");
    addStubsDebugStackDump(p->stackID);

    const char *cmd = "simROS.advertiseService";

    advertiseService_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    advertiseService_out out_args;

    try
    {
        // check argument count

        int numArgs = sim::getStackSize(p->stackID);
        if(numArgs < 3)
            throw sim::exception("not enough arguments");
        if(numArgs > 3)
            throw sim::exception("too many arguments");

        // read input arguments from stack

        if(numArgs >= 1)
        {
            addStubsDebugLog("advertiseService_callback: reading input argument 1 \"serviceName\" (std::string)...");
            try
            {
                sim::moveStackItemToTop(p->stackID, 0);
                readFromStack(p->stackID, &(in_args.serviceName));
            }
            catch(std::exception &ex)
            {
                throw sim::exception("read in arg 1 (serviceName): %s", ex.what());
            }
        }

        if(numArgs >= 2)
        {
            addStubsDebugLog("advertiseService_callback: reading input argument 2 \"serviceType\" (std::string)...");
            try
            {
                sim::moveStackItemToTop(p->stackID, 0);
                readFromStack(p->stackID, &(in_args.serviceType));
            }
            catch(std::exception &ex)
            {
                throw sim::exception("read in arg 2 (serviceType): %s", ex.what());
            }
        }

        if(numArgs >= 3)
        {
            addStubsDebugLog("advertiseService_callback: reading input argument 3 \"serviceCallback\" (std::string)...");
            try
            {
                sim::moveStackItemToTop(p->stackID, 0);
                readFromStack(p->stackID, &(in_args.serviceCallback));
            }
            catch(std::exception &ex)
            {
                throw sim::exception("read in arg 3 (serviceCallback): %s", ex.what());
            }
        }


        addStubsDebugLog("advertiseService_callback: stack content after reading input arguments:");
        addStubsDebugStackDump(p->stackID);

        addStubsDebugLog("advertiseService_callback: clearing stack content after reading input arguments");
        // clear stack
        sim::popStackItem(p->stackID, 0);


        addStubsDebugLog("advertiseService_callback: calling callback (advertiseService)");
        advertiseService(p, cmd, &in_args, &out_args);
    }
    catch(std::exception &ex)
    {
        sim::setLastError(cmd, ex.what());
    }

    try
    {
        addStubsDebugLog("advertiseService_callback: writing output arguments...");
        addStubsDebugStackDump(p->stackID);

        addStubsDebugLog("advertiseService_callback: clearing stack content before writing output arguments");
        // clear stack
        sim::popStackItem(p->stackID, 0);


        // write output arguments to stack

        addStubsDebugLog("advertiseService_callback: writing output argument 1 \"serviceServerHandle\" (std::string)...");
        try
        {
            writeToStack(out_args.serviceServerHandle, p->stackID);
        }
        catch(std::exception &ex)
        {
            throw sim::exception("write out arg 1 (serviceServerHandle): %s", ex.what());
        }

        addStubsDebugLog("advertiseService_callback: stack content after writing output arguments:");
        addStubsDebugStackDump(p->stackID);
    }
    catch(std::exception &ex)
    {
        sim::setLastError(cmd, ex.what());
        // clear stack
        try { sim::popStackItem(p->stackID, 0); } catch(...) {}
    }

    addStubsDebugLog("advertiseService_callback: finished");
}

shutdownServiceServer_in::shutdownServiceServer_in()
{
}

shutdownServiceServer_out::shutdownServiceServer_out()
{
}

void shutdownServiceServer(SScriptCallBack *p, shutdownServiceServer_in *in_args, shutdownServiceServer_out *out_args)
{
    shutdownServiceServer(p, "simROS.shutdownServiceServer", in_args, out_args);
}

void shutdownServiceServer(SScriptCallBack *p, std::string serviceServerHandle)
{
    shutdownServiceServer_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    in_args.serviceServerHandle = serviceServerHandle;
    shutdownServiceServer_out out_args;
    shutdownServiceServer(p, &in_args, &out_args);
}

void shutdownServiceServer(SScriptCallBack *p, shutdownServiceServer_out *out_args, std::string serviceServerHandle)
{
    shutdownServiceServer_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    in_args.serviceServerHandle = serviceServerHandle;
    shutdownServiceServer(p, &in_args, out_args);
}

void shutdownServiceServer_callback(SScriptCallBack *p)
{
    addStubsDebugLog("shutdownServiceServer_callback: reading input arguments...");
    addStubsDebugStackDump(p->stackID);

    const char *cmd = "simROS.shutdownServiceServer";

    shutdownServiceServer_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    shutdownServiceServer_out out_args;

    try
    {
        // check argument count

        int numArgs = sim::getStackSize(p->stackID);
        if(numArgs < 1)
            throw sim::exception("not enough arguments");
        if(numArgs > 1)
            throw sim::exception("too many arguments");

        // read input arguments from stack

        if(numArgs >= 1)
        {
            addStubsDebugLog("shutdownServiceServer_callback: reading input argument 1 \"serviceServerHandle\" (std::string)...");
            try
            {
                sim::moveStackItemToTop(p->stackID, 0);
                readFromStack(p->stackID, &(in_args.serviceServerHandle));
            }
            catch(std::exception &ex)
            {
                throw sim::exception("read in arg 1 (serviceServerHandle): %s", ex.what());
            }
        }


        addStubsDebugLog("shutdownServiceServer_callback: stack content after reading input arguments:");
        addStubsDebugStackDump(p->stackID);

        addStubsDebugLog("shutdownServiceServer_callback: clearing stack content after reading input arguments");
        // clear stack
        sim::popStackItem(p->stackID, 0);


        addStubsDebugLog("shutdownServiceServer_callback: calling callback (shutdownServiceServer)");
        shutdownServiceServer(p, cmd, &in_args, &out_args);
    }
    catch(std::exception &ex)
    {
        sim::setLastError(cmd, ex.what());
    }

    try
    {
        addStubsDebugLog("shutdownServiceServer_callback: writing output arguments...");
        addStubsDebugStackDump(p->stackID);

        addStubsDebugLog("shutdownServiceServer_callback: clearing stack content before writing output arguments");
        // clear stack
        sim::popStackItem(p->stackID, 0);


        // write output arguments to stack


        addStubsDebugLog("shutdownServiceServer_callback: stack content after writing output arguments:");
        addStubsDebugStackDump(p->stackID);
    }
    catch(std::exception &ex)
    {
        sim::setLastError(cmd, ex.what());
        // clear stack
        try { sim::popStackItem(p->stackID, 0); } catch(...) {}
    }

    addStubsDebugLog("shutdownServiceServer_callback: finished");
}

serviceServerTreatUInt8ArrayAsString_in::serviceServerTreatUInt8ArrayAsString_in()
{
}

serviceServerTreatUInt8ArrayAsString_out::serviceServerTreatUInt8ArrayAsString_out()
{
}

void serviceServerTreatUInt8ArrayAsString(SScriptCallBack *p, serviceServerTreatUInt8ArrayAsString_in *in_args, serviceServerTreatUInt8ArrayAsString_out *out_args)
{
    serviceServerTreatUInt8ArrayAsString(p, "simROS.serviceServerTreatUInt8ArrayAsString", in_args, out_args);
}

void serviceServerTreatUInt8ArrayAsString(SScriptCallBack *p, std::string serviceServerHandle)
{
    serviceServerTreatUInt8ArrayAsString_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    in_args.serviceServerHandle = serviceServerHandle;
    serviceServerTreatUInt8ArrayAsString_out out_args;
    serviceServerTreatUInt8ArrayAsString(p, &in_args, &out_args);
}

void serviceServerTreatUInt8ArrayAsString(SScriptCallBack *p, serviceServerTreatUInt8ArrayAsString_out *out_args, std::string serviceServerHandle)
{
    serviceServerTreatUInt8ArrayAsString_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    in_args.serviceServerHandle = serviceServerHandle;
    serviceServerTreatUInt8ArrayAsString(p, &in_args, out_args);
}

void serviceServerTreatUInt8ArrayAsString_callback(SScriptCallBack *p)
{
    addStubsDebugLog("serviceServerTreatUInt8ArrayAsString_callback: reading input arguments...");
    addStubsDebugStackDump(p->stackID);

    const char *cmd = "simROS.serviceServerTreatUInt8ArrayAsString";

    serviceServerTreatUInt8ArrayAsString_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    serviceServerTreatUInt8ArrayAsString_out out_args;

    try
    {
        // check argument count

        int numArgs = sim::getStackSize(p->stackID);
        if(numArgs < 1)
            throw sim::exception("not enough arguments");
        if(numArgs > 1)
            throw sim::exception("too many arguments");

        // read input arguments from stack

        if(numArgs >= 1)
        {
            addStubsDebugLog("serviceServerTreatUInt8ArrayAsString_callback: reading input argument 1 \"serviceServerHandle\" (std::string)...");
            try
            {
                sim::moveStackItemToTop(p->stackID, 0);
                readFromStack(p->stackID, &(in_args.serviceServerHandle));
            }
            catch(std::exception &ex)
            {
                throw sim::exception("read in arg 1 (serviceServerHandle): %s", ex.what());
            }
        }


        addStubsDebugLog("serviceServerTreatUInt8ArrayAsString_callback: stack content after reading input arguments:");
        addStubsDebugStackDump(p->stackID);

        addStubsDebugLog("serviceServerTreatUInt8ArrayAsString_callback: clearing stack content after reading input arguments");
        // clear stack
        sim::popStackItem(p->stackID, 0);


        addStubsDebugLog("serviceServerTreatUInt8ArrayAsString_callback: calling callback (serviceServerTreatUInt8ArrayAsString)");
        serviceServerTreatUInt8ArrayAsString(p, cmd, &in_args, &out_args);
    }
    catch(std::exception &ex)
    {
        sim::setLastError(cmd, ex.what());
    }

    try
    {
        addStubsDebugLog("serviceServerTreatUInt8ArrayAsString_callback: writing output arguments...");
        addStubsDebugStackDump(p->stackID);

        addStubsDebugLog("serviceServerTreatUInt8ArrayAsString_callback: clearing stack content before writing output arguments");
        // clear stack
        sim::popStackItem(p->stackID, 0);


        // write output arguments to stack


        addStubsDebugLog("serviceServerTreatUInt8ArrayAsString_callback: stack content after writing output arguments:");
        addStubsDebugStackDump(p->stackID);
    }
    catch(std::exception &ex)
    {
        sim::setLastError(cmd, ex.what());
        // clear stack
        try { sim::popStackItem(p->stackID, 0); } catch(...) {}
    }

    addStubsDebugLog("serviceServerTreatUInt8ArrayAsString_callback: finished");
}

sendTransform_in::sendTransform_in()
{
}

sendTransform_out::sendTransform_out()
{
}

void sendTransform(SScriptCallBack *p, sendTransform_in *in_args, sendTransform_out *out_args)
{
    sendTransform(p, "simROS.sendTransform", in_args, out_args);
}

void sendTransform(SScriptCallBack *p)
{
    sendTransform_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    sendTransform_out out_args;
    sendTransform(p, &in_args, &out_args);
}

void sendTransform(SScriptCallBack *p, sendTransform_out *out_args)
{
    sendTransform_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    sendTransform(p, &in_args, out_args);
}

void sendTransform_callback(SScriptCallBack *p)
{
    addStubsDebugLog("sendTransform_callback: reading input arguments...");
    addStubsDebugStackDump(p->stackID);

    const char *cmd = "simROS.sendTransform";

    sendTransform_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    sendTransform_out out_args;

    try
    {
        // check argument count

        int numArgs = sim::getStackSize(p->stackID);
        if(numArgs < 0)
            throw sim::exception("not enough arguments");
        if(numArgs > 1)
            throw sim::exception("too many arguments");

        // read input arguments from stack


        addStubsDebugLog("sendTransform_callback: stack content after reading input arguments:");
        addStubsDebugStackDump(p->stackID);


        addStubsDebugLog("sendTransform_callback: calling callback (sendTransform)");
        sendTransform(p, cmd, &in_args, &out_args);
    }
    catch(std::exception &ex)
    {
        sim::setLastError(cmd, ex.what());
    }

    try
    {
        addStubsDebugLog("sendTransform_callback: writing output arguments...");
        addStubsDebugStackDump(p->stackID);

        addStubsDebugLog("sendTransform_callback: clearing stack content before writing output arguments");
        // clear stack
        sim::popStackItem(p->stackID, 0);


        // write output arguments to stack


        addStubsDebugLog("sendTransform_callback: stack content after writing output arguments:");
        addStubsDebugStackDump(p->stackID);
    }
    catch(std::exception &ex)
    {
        sim::setLastError(cmd, ex.what());
        // clear stack
        try { sim::popStackItem(p->stackID, 0); } catch(...) {}
    }

    addStubsDebugLog("sendTransform_callback: finished");
}

sendTransforms_in::sendTransforms_in()
{
}

sendTransforms_out::sendTransforms_out()
{
}

void sendTransforms(SScriptCallBack *p, sendTransforms_in *in_args, sendTransforms_out *out_args)
{
    sendTransforms(p, "simROS.sendTransforms", in_args, out_args);
}

void sendTransforms(SScriptCallBack *p)
{
    sendTransforms_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    sendTransforms_out out_args;
    sendTransforms(p, &in_args, &out_args);
}

void sendTransforms(SScriptCallBack *p, sendTransforms_out *out_args)
{
    sendTransforms_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    sendTransforms(p, &in_args, out_args);
}

void sendTransforms_callback(SScriptCallBack *p)
{
    addStubsDebugLog("sendTransforms_callback: reading input arguments...");
    addStubsDebugStackDump(p->stackID);

    const char *cmd = "simROS.sendTransforms";

    sendTransforms_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    sendTransforms_out out_args;

    try
    {
        // check argument count

        int numArgs = sim::getStackSize(p->stackID);
        if(numArgs < 0)
            throw sim::exception("not enough arguments");
        if(numArgs > 1)
            throw sim::exception("too many arguments");

        // read input arguments from stack


        addStubsDebugLog("sendTransforms_callback: stack content after reading input arguments:");
        addStubsDebugStackDump(p->stackID);


        addStubsDebugLog("sendTransforms_callback: calling callback (sendTransforms)");
        sendTransforms(p, cmd, &in_args, &out_args);
    }
    catch(std::exception &ex)
    {
        sim::setLastError(cmd, ex.what());
    }

    try
    {
        addStubsDebugLog("sendTransforms_callback: writing output arguments...");
        addStubsDebugStackDump(p->stackID);

        addStubsDebugLog("sendTransforms_callback: clearing stack content before writing output arguments");
        // clear stack
        sim::popStackItem(p->stackID, 0);


        // write output arguments to stack


        addStubsDebugLog("sendTransforms_callback: stack content after writing output arguments:");
        addStubsDebugStackDump(p->stackID);
    }
    catch(std::exception &ex)
    {
        sim::setLastError(cmd, ex.what());
        // clear stack
        try { sim::popStackItem(p->stackID, 0); } catch(...) {}
    }

    addStubsDebugLog("sendTransforms_callback: finished");
}

imageTransportSubscribe_in::imageTransportSubscribe_in()
{
    queueSize = 1;
}

imageTransportSubscribe_out::imageTransportSubscribe_out()
{
}

void imageTransportSubscribe(SScriptCallBack *p, imageTransportSubscribe_in *in_args, imageTransportSubscribe_out *out_args)
{
    imageTransportSubscribe(p, "simROS.imageTransportSubscribe", in_args, out_args);
}

std::string imageTransportSubscribe(SScriptCallBack *p, std::string topicName, std::string topicCallback, int queueSize)
{
    imageTransportSubscribe_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    in_args.topicName = topicName;
    in_args.topicCallback = topicCallback;
    in_args.queueSize = queueSize;
    imageTransportSubscribe_out out_args;
    imageTransportSubscribe(p, &in_args, &out_args);
    return out_args.subscriberHandle;
}

void imageTransportSubscribe(SScriptCallBack *p, imageTransportSubscribe_out *out_args, std::string topicName, std::string topicCallback, int queueSize)
{
    imageTransportSubscribe_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    in_args.topicName = topicName;
    in_args.topicCallback = topicCallback;
    in_args.queueSize = queueSize;
    imageTransportSubscribe(p, &in_args, out_args);
}

void imageTransportSubscribe_callback(SScriptCallBack *p)
{
    addStubsDebugLog("imageTransportSubscribe_callback: reading input arguments...");
    addStubsDebugStackDump(p->stackID);

    const char *cmd = "simROS.imageTransportSubscribe";

    imageTransportSubscribe_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    imageTransportSubscribe_out out_args;

    try
    {
        // check argument count

        int numArgs = sim::getStackSize(p->stackID);
        if(numArgs < 2)
            throw sim::exception("not enough arguments");
        if(numArgs > 3)
            throw sim::exception("too many arguments");

        // read input arguments from stack

        if(numArgs >= 1)
        {
            addStubsDebugLog("imageTransportSubscribe_callback: reading input argument 1 \"topicName\" (std::string)...");
            try
            {
                sim::moveStackItemToTop(p->stackID, 0);
                readFromStack(p->stackID, &(in_args.topicName));
            }
            catch(std::exception &ex)
            {
                throw sim::exception("read in arg 1 (topicName): %s", ex.what());
            }
        }

        if(numArgs >= 2)
        {
            addStubsDebugLog("imageTransportSubscribe_callback: reading input argument 2 \"topicCallback\" (std::string)...");
            try
            {
                sim::moveStackItemToTop(p->stackID, 0);
                readFromStack(p->stackID, &(in_args.topicCallback));
            }
            catch(std::exception &ex)
            {
                throw sim::exception("read in arg 2 (topicCallback): %s", ex.what());
            }
        }

        if(numArgs >= 3)
        {
            addStubsDebugLog("imageTransportSubscribe_callback: reading input argument 3 \"queueSize\" (int)...");
            try
            {
                sim::moveStackItemToTop(p->stackID, 0);
                readFromStack(p->stackID, &(in_args.queueSize));
            }
            catch(std::exception &ex)
            {
                throw sim::exception("read in arg 3 (queueSize): %s", ex.what());
            }
        }


        addStubsDebugLog("imageTransportSubscribe_callback: stack content after reading input arguments:");
        addStubsDebugStackDump(p->stackID);

        addStubsDebugLog("imageTransportSubscribe_callback: clearing stack content after reading input arguments");
        // clear stack
        sim::popStackItem(p->stackID, 0);


        addStubsDebugLog("imageTransportSubscribe_callback: calling callback (imageTransportSubscribe)");
        imageTransportSubscribe(p, cmd, &in_args, &out_args);
    }
    catch(std::exception &ex)
    {
        sim::setLastError(cmd, ex.what());
    }

    try
    {
        addStubsDebugLog("imageTransportSubscribe_callback: writing output arguments...");
        addStubsDebugStackDump(p->stackID);

        addStubsDebugLog("imageTransportSubscribe_callback: clearing stack content before writing output arguments");
        // clear stack
        sim::popStackItem(p->stackID, 0);


        // write output arguments to stack

        addStubsDebugLog("imageTransportSubscribe_callback: writing output argument 1 \"subscriberHandle\" (std::string)...");
        try
        {
            writeToStack(out_args.subscriberHandle, p->stackID);
        }
        catch(std::exception &ex)
        {
            throw sim::exception("write out arg 1 (subscriberHandle): %s", ex.what());
        }

        addStubsDebugLog("imageTransportSubscribe_callback: stack content after writing output arguments:");
        addStubsDebugStackDump(p->stackID);
    }
    catch(std::exception &ex)
    {
        sim::setLastError(cmd, ex.what());
        // clear stack
        try { sim::popStackItem(p->stackID, 0); } catch(...) {}
    }

    addStubsDebugLog("imageTransportSubscribe_callback: finished");
}

imageTransportShutdownSubscriber_in::imageTransportShutdownSubscriber_in()
{
}

imageTransportShutdownSubscriber_out::imageTransportShutdownSubscriber_out()
{
}

void imageTransportShutdownSubscriber(SScriptCallBack *p, imageTransportShutdownSubscriber_in *in_args, imageTransportShutdownSubscriber_out *out_args)
{
    imageTransportShutdownSubscriber(p, "simROS.imageTransportShutdownSubscriber", in_args, out_args);
}

void imageTransportShutdownSubscriber(SScriptCallBack *p, std::string subscriberHandle)
{
    imageTransportShutdownSubscriber_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    in_args.subscriberHandle = subscriberHandle;
    imageTransportShutdownSubscriber_out out_args;
    imageTransportShutdownSubscriber(p, &in_args, &out_args);
}

void imageTransportShutdownSubscriber(SScriptCallBack *p, imageTransportShutdownSubscriber_out *out_args, std::string subscriberHandle)
{
    imageTransportShutdownSubscriber_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    in_args.subscriberHandle = subscriberHandle;
    imageTransportShutdownSubscriber(p, &in_args, out_args);
}

void imageTransportShutdownSubscriber_callback(SScriptCallBack *p)
{
    addStubsDebugLog("imageTransportShutdownSubscriber_callback: reading input arguments...");
    addStubsDebugStackDump(p->stackID);

    const char *cmd = "simROS.imageTransportShutdownSubscriber";

    imageTransportShutdownSubscriber_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    imageTransportShutdownSubscriber_out out_args;

    try
    {
        // check argument count

        int numArgs = sim::getStackSize(p->stackID);
        if(numArgs < 1)
            throw sim::exception("not enough arguments");
        if(numArgs > 1)
            throw sim::exception("too many arguments");

        // read input arguments from stack

        if(numArgs >= 1)
        {
            addStubsDebugLog("imageTransportShutdownSubscriber_callback: reading input argument 1 \"subscriberHandle\" (std::string)...");
            try
            {
                sim::moveStackItemToTop(p->stackID, 0);
                readFromStack(p->stackID, &(in_args.subscriberHandle));
            }
            catch(std::exception &ex)
            {
                throw sim::exception("read in arg 1 (subscriberHandle): %s", ex.what());
            }
        }


        addStubsDebugLog("imageTransportShutdownSubscriber_callback: stack content after reading input arguments:");
        addStubsDebugStackDump(p->stackID);

        addStubsDebugLog("imageTransportShutdownSubscriber_callback: clearing stack content after reading input arguments");
        // clear stack
        sim::popStackItem(p->stackID, 0);


        addStubsDebugLog("imageTransportShutdownSubscriber_callback: calling callback (imageTransportShutdownSubscriber)");
        imageTransportShutdownSubscriber(p, cmd, &in_args, &out_args);
    }
    catch(std::exception &ex)
    {
        sim::setLastError(cmd, ex.what());
    }

    try
    {
        addStubsDebugLog("imageTransportShutdownSubscriber_callback: writing output arguments...");
        addStubsDebugStackDump(p->stackID);

        addStubsDebugLog("imageTransportShutdownSubscriber_callback: clearing stack content before writing output arguments");
        // clear stack
        sim::popStackItem(p->stackID, 0);


        // write output arguments to stack


        addStubsDebugLog("imageTransportShutdownSubscriber_callback: stack content after writing output arguments:");
        addStubsDebugStackDump(p->stackID);
    }
    catch(std::exception &ex)
    {
        sim::setLastError(cmd, ex.what());
        // clear stack
        try { sim::popStackItem(p->stackID, 0); } catch(...) {}
    }

    addStubsDebugLog("imageTransportShutdownSubscriber_callback: finished");
}

imageTransportAdvertise_in::imageTransportAdvertise_in()
{
    queueSize = 1;
}

imageTransportAdvertise_out::imageTransportAdvertise_out()
{
}

void imageTransportAdvertise(SScriptCallBack *p, imageTransportAdvertise_in *in_args, imageTransportAdvertise_out *out_args)
{
    imageTransportAdvertise(p, "simROS.imageTransportAdvertise", in_args, out_args);
}

std::string imageTransportAdvertise(SScriptCallBack *p, std::string topicName, int queueSize)
{
    imageTransportAdvertise_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    in_args.topicName = topicName;
    in_args.queueSize = queueSize;
    imageTransportAdvertise_out out_args;
    imageTransportAdvertise(p, &in_args, &out_args);
    return out_args.publisherHandle;
}

void imageTransportAdvertise(SScriptCallBack *p, imageTransportAdvertise_out *out_args, std::string topicName, int queueSize)
{
    imageTransportAdvertise_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    in_args.topicName = topicName;
    in_args.queueSize = queueSize;
    imageTransportAdvertise(p, &in_args, out_args);
}

void imageTransportAdvertise_callback(SScriptCallBack *p)
{
    addStubsDebugLog("imageTransportAdvertise_callback: reading input arguments...");
    addStubsDebugStackDump(p->stackID);

    const char *cmd = "simROS.imageTransportAdvertise";

    imageTransportAdvertise_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    imageTransportAdvertise_out out_args;

    try
    {
        // check argument count

        int numArgs = sim::getStackSize(p->stackID);
        if(numArgs < 1)
            throw sim::exception("not enough arguments");
        if(numArgs > 2)
            throw sim::exception("too many arguments");

        // read input arguments from stack

        if(numArgs >= 1)
        {
            addStubsDebugLog("imageTransportAdvertise_callback: reading input argument 1 \"topicName\" (std::string)...");
            try
            {
                sim::moveStackItemToTop(p->stackID, 0);
                readFromStack(p->stackID, &(in_args.topicName));
            }
            catch(std::exception &ex)
            {
                throw sim::exception("read in arg 1 (topicName): %s", ex.what());
            }
        }

        if(numArgs >= 2)
        {
            addStubsDebugLog("imageTransportAdvertise_callback: reading input argument 2 \"queueSize\" (int)...");
            try
            {
                sim::moveStackItemToTop(p->stackID, 0);
                readFromStack(p->stackID, &(in_args.queueSize));
            }
            catch(std::exception &ex)
            {
                throw sim::exception("read in arg 2 (queueSize): %s", ex.what());
            }
        }


        addStubsDebugLog("imageTransportAdvertise_callback: stack content after reading input arguments:");
        addStubsDebugStackDump(p->stackID);

        addStubsDebugLog("imageTransportAdvertise_callback: clearing stack content after reading input arguments");
        // clear stack
        sim::popStackItem(p->stackID, 0);


        addStubsDebugLog("imageTransportAdvertise_callback: calling callback (imageTransportAdvertise)");
        imageTransportAdvertise(p, cmd, &in_args, &out_args);
    }
    catch(std::exception &ex)
    {
        sim::setLastError(cmd, ex.what());
    }

    try
    {
        addStubsDebugLog("imageTransportAdvertise_callback: writing output arguments...");
        addStubsDebugStackDump(p->stackID);

        addStubsDebugLog("imageTransportAdvertise_callback: clearing stack content before writing output arguments");
        // clear stack
        sim::popStackItem(p->stackID, 0);


        // write output arguments to stack

        addStubsDebugLog("imageTransportAdvertise_callback: writing output argument 1 \"publisherHandle\" (std::string)...");
        try
        {
            writeToStack(out_args.publisherHandle, p->stackID);
        }
        catch(std::exception &ex)
        {
            throw sim::exception("write out arg 1 (publisherHandle): %s", ex.what());
        }

        addStubsDebugLog("imageTransportAdvertise_callback: stack content after writing output arguments:");
        addStubsDebugStackDump(p->stackID);
    }
    catch(std::exception &ex)
    {
        sim::setLastError(cmd, ex.what());
        // clear stack
        try { sim::popStackItem(p->stackID, 0); } catch(...) {}
    }

    addStubsDebugLog("imageTransportAdvertise_callback: finished");
}

imageTransportShutdownPublisher_in::imageTransportShutdownPublisher_in()
{
}

imageTransportShutdownPublisher_out::imageTransportShutdownPublisher_out()
{
}

void imageTransportShutdownPublisher(SScriptCallBack *p, imageTransportShutdownPublisher_in *in_args, imageTransportShutdownPublisher_out *out_args)
{
    imageTransportShutdownPublisher(p, "simROS.imageTransportShutdownPublisher", in_args, out_args);
}

void imageTransportShutdownPublisher(SScriptCallBack *p, std::string publisherHandle)
{
    imageTransportShutdownPublisher_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    in_args.publisherHandle = publisherHandle;
    imageTransportShutdownPublisher_out out_args;
    imageTransportShutdownPublisher(p, &in_args, &out_args);
}

void imageTransportShutdownPublisher(SScriptCallBack *p, imageTransportShutdownPublisher_out *out_args, std::string publisherHandle)
{
    imageTransportShutdownPublisher_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    in_args.publisherHandle = publisherHandle;
    imageTransportShutdownPublisher(p, &in_args, out_args);
}

void imageTransportShutdownPublisher_callback(SScriptCallBack *p)
{
    addStubsDebugLog("imageTransportShutdownPublisher_callback: reading input arguments...");
    addStubsDebugStackDump(p->stackID);

    const char *cmd = "simROS.imageTransportShutdownPublisher";

    imageTransportShutdownPublisher_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    imageTransportShutdownPublisher_out out_args;

    try
    {
        // check argument count

        int numArgs = sim::getStackSize(p->stackID);
        if(numArgs < 1)
            throw sim::exception("not enough arguments");
        if(numArgs > 1)
            throw sim::exception("too many arguments");

        // read input arguments from stack

        if(numArgs >= 1)
        {
            addStubsDebugLog("imageTransportShutdownPublisher_callback: reading input argument 1 \"publisherHandle\" (std::string)...");
            try
            {
                sim::moveStackItemToTop(p->stackID, 0);
                readFromStack(p->stackID, &(in_args.publisherHandle));
            }
            catch(std::exception &ex)
            {
                throw sim::exception("read in arg 1 (publisherHandle): %s", ex.what());
            }
        }


        addStubsDebugLog("imageTransportShutdownPublisher_callback: stack content after reading input arguments:");
        addStubsDebugStackDump(p->stackID);

        addStubsDebugLog("imageTransportShutdownPublisher_callback: clearing stack content after reading input arguments");
        // clear stack
        sim::popStackItem(p->stackID, 0);


        addStubsDebugLog("imageTransportShutdownPublisher_callback: calling callback (imageTransportShutdownPublisher)");
        imageTransportShutdownPublisher(p, cmd, &in_args, &out_args);
    }
    catch(std::exception &ex)
    {
        sim::setLastError(cmd, ex.what());
    }

    try
    {
        addStubsDebugLog("imageTransportShutdownPublisher_callback: writing output arguments...");
        addStubsDebugStackDump(p->stackID);

        addStubsDebugLog("imageTransportShutdownPublisher_callback: clearing stack content before writing output arguments");
        // clear stack
        sim::popStackItem(p->stackID, 0);


        // write output arguments to stack


        addStubsDebugLog("imageTransportShutdownPublisher_callback: stack content after writing output arguments:");
        addStubsDebugStackDump(p->stackID);
    }
    catch(std::exception &ex)
    {
        sim::setLastError(cmd, ex.what());
        // clear stack
        try { sim::popStackItem(p->stackID, 0); } catch(...) {}
    }

    addStubsDebugLog("imageTransportShutdownPublisher_callback: finished");
}

imageTransportPublish_in::imageTransportPublish_in()
{
}

imageTransportPublish_out::imageTransportPublish_out()
{
}

void imageTransportPublish(SScriptCallBack *p, imageTransportPublish_in *in_args, imageTransportPublish_out *out_args)
{
    imageTransportPublish(p, "simROS.imageTransportPublish", in_args, out_args);
}

void imageTransportPublish(SScriptCallBack *p, std::string publisherHandle, std::string data, int width, int height, std::string frame_id)
{
    imageTransportPublish_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    in_args.publisherHandle = publisherHandle;
    in_args.data = data;
    in_args.width = width;
    in_args.height = height;
    in_args.frame_id = frame_id;
    imageTransportPublish_out out_args;
    imageTransportPublish(p, &in_args, &out_args);
}

void imageTransportPublish(SScriptCallBack *p, imageTransportPublish_out *out_args, std::string publisherHandle, std::string data, int width, int height, std::string frame_id)
{
    imageTransportPublish_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    in_args.publisherHandle = publisherHandle;
    in_args.data = data;
    in_args.width = width;
    in_args.height = height;
    in_args.frame_id = frame_id;
    imageTransportPublish(p, &in_args, out_args);
}

void imageTransportPublish_callback(SScriptCallBack *p)
{
    addStubsDebugLog("imageTransportPublish_callback: reading input arguments...");
    addStubsDebugStackDump(p->stackID);

    const char *cmd = "simROS.imageTransportPublish";

    imageTransportPublish_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    imageTransportPublish_out out_args;

    try
    {
        // check argument count

        int numArgs = sim::getStackSize(p->stackID);
        if(numArgs < 5)
            throw sim::exception("not enough arguments");
        if(numArgs > 5)
            throw sim::exception("too many arguments");

        // read input arguments from stack

        if(numArgs >= 1)
        {
            addStubsDebugLog("imageTransportPublish_callback: reading input argument 1 \"publisherHandle\" (std::string)...");
            try
            {
                sim::moveStackItemToTop(p->stackID, 0);
                readFromStack(p->stackID, &(in_args.publisherHandle));
            }
            catch(std::exception &ex)
            {
                throw sim::exception("read in arg 1 (publisherHandle): %s", ex.what());
            }
        }

        if(numArgs >= 2)
        {
            addStubsDebugLog("imageTransportPublish_callback: reading input argument 2 \"data\" (std::string)...");
            try
            {
                sim::moveStackItemToTop(p->stackID, 0);
                readFromStack(p->stackID, &(in_args.data));
            }
            catch(std::exception &ex)
            {
                throw sim::exception("read in arg 2 (data): %s", ex.what());
            }
        }

        if(numArgs >= 3)
        {
            addStubsDebugLog("imageTransportPublish_callback: reading input argument 3 \"width\" (int)...");
            try
            {
                sim::moveStackItemToTop(p->stackID, 0);
                readFromStack(p->stackID, &(in_args.width));
            }
            catch(std::exception &ex)
            {
                throw sim::exception("read in arg 3 (width): %s", ex.what());
            }
        }

        if(numArgs >= 4)
        {
            addStubsDebugLog("imageTransportPublish_callback: reading input argument 4 \"height\" (int)...");
            try
            {
                sim::moveStackItemToTop(p->stackID, 0);
                readFromStack(p->stackID, &(in_args.height));
            }
            catch(std::exception &ex)
            {
                throw sim::exception("read in arg 4 (height): %s", ex.what());
            }
        }

        if(numArgs >= 5)
        {
            addStubsDebugLog("imageTransportPublish_callback: reading input argument 5 \"frame_id\" (std::string)...");
            try
            {
                sim::moveStackItemToTop(p->stackID, 0);
                readFromStack(p->stackID, &(in_args.frame_id));
            }
            catch(std::exception &ex)
            {
                throw sim::exception("read in arg 5 (frame_id): %s", ex.what());
            }
        }


        addStubsDebugLog("imageTransportPublish_callback: stack content after reading input arguments:");
        addStubsDebugStackDump(p->stackID);

        addStubsDebugLog("imageTransportPublish_callback: clearing stack content after reading input arguments");
        // clear stack
        sim::popStackItem(p->stackID, 0);


        addStubsDebugLog("imageTransportPublish_callback: calling callback (imageTransportPublish)");
        imageTransportPublish(p, cmd, &in_args, &out_args);
    }
    catch(std::exception &ex)
    {
        sim::setLastError(cmd, ex.what());
    }

    try
    {
        addStubsDebugLog("imageTransportPublish_callback: writing output arguments...");
        addStubsDebugStackDump(p->stackID);

        addStubsDebugLog("imageTransportPublish_callback: clearing stack content before writing output arguments");
        // clear stack
        sim::popStackItem(p->stackID, 0);


        // write output arguments to stack


        addStubsDebugLog("imageTransportPublish_callback: stack content after writing output arguments:");
        addStubsDebugStackDump(p->stackID);
    }
    catch(std::exception &ex)
    {
        sim::setLastError(cmd, ex.what());
        // clear stack
        try { sim::popStackItem(p->stackID, 0); } catch(...) {}
    }

    addStubsDebugLog("imageTransportPublish_callback: finished");
}

getTime_in::getTime_in()
{
    flag = 0;
}

getTime_out::getTime_out()
{
    time = 0;
}

void getTime(SScriptCallBack *p, getTime_in *in_args, getTime_out *out_args)
{
    getTime(p, "simROS.getTime", in_args, out_args);
}

double getTime(SScriptCallBack *p, int flag)
{
    getTime_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    in_args.flag = flag;
    getTime_out out_args;
    getTime(p, &in_args, &out_args);
    return out_args.time;
}

void getTime(SScriptCallBack *p, getTime_out *out_args, int flag)
{
    getTime_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    in_args.flag = flag;
    getTime(p, &in_args, out_args);
}

void getTime_callback(SScriptCallBack *p)
{
    addStubsDebugLog("getTime_callback: reading input arguments...");
    addStubsDebugStackDump(p->stackID);

    const char *cmd = "simROS.getTime";

    getTime_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    getTime_out out_args;

    try
    {
        // check argument count

        int numArgs = sim::getStackSize(p->stackID);
        if(numArgs < 0)
            throw sim::exception("not enough arguments");
        if(numArgs > 1)
            throw sim::exception("too many arguments");

        // read input arguments from stack

        if(numArgs >= 1)
        {
            addStubsDebugLog("getTime_callback: reading input argument 1 \"flag\" (int)...");
            try
            {
                sim::moveStackItemToTop(p->stackID, 0);
                readFromStack(p->stackID, &(in_args.flag));
            }
            catch(std::exception &ex)
            {
                throw sim::exception("read in arg 1 (flag): %s", ex.what());
            }
        }


        addStubsDebugLog("getTime_callback: stack content after reading input arguments:");
        addStubsDebugStackDump(p->stackID);

        addStubsDebugLog("getTime_callback: clearing stack content after reading input arguments");
        // clear stack
        sim::popStackItem(p->stackID, 0);


        addStubsDebugLog("getTime_callback: calling callback (getTime)");
        getTime(p, cmd, &in_args, &out_args);
    }
    catch(std::exception &ex)
    {
        sim::setLastError(cmd, ex.what());
    }

    try
    {
        addStubsDebugLog("getTime_callback: writing output arguments...");
        addStubsDebugStackDump(p->stackID);

        addStubsDebugLog("getTime_callback: clearing stack content before writing output arguments");
        // clear stack
        sim::popStackItem(p->stackID, 0);


        // write output arguments to stack

        addStubsDebugLog("getTime_callback: writing output argument 1 \"time\" (double)...");
        try
        {
            writeToStack(out_args.time, p->stackID);
        }
        catch(std::exception &ex)
        {
            throw sim::exception("write out arg 1 (time): %s", ex.what());
        }

        addStubsDebugLog("getTime_callback: stack content after writing output arguments:");
        addStubsDebugStackDump(p->stackID);
    }
    catch(std::exception &ex)
    {
        sim::setLastError(cmd, ex.what());
        // clear stack
        try { sim::popStackItem(p->stackID, 0); } catch(...) {}
    }

    addStubsDebugLog("getTime_callback: finished");
}

getParamString_in::getParamString_in()
{
    defaultValue = "";
}

getParamString_out::getParamString_out()
{
    value = "";
}

void getParamString(SScriptCallBack *p, getParamString_in *in_args, getParamString_out *out_args)
{
    getParamString(p, "simROS.getParamString", in_args, out_args);
}

void getParamString(SScriptCallBack *p, getParamString_out *out_args, std::string name, std::string defaultValue)
{
    getParamString_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    in_args.name = name;
    in_args.defaultValue = defaultValue;
    getParamString(p, &in_args, out_args);
}

void getParamString_callback(SScriptCallBack *p)
{
    addStubsDebugLog("getParamString_callback: reading input arguments...");
    addStubsDebugStackDump(p->stackID);

    const char *cmd = "simROS.getParamString";

    getParamString_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    getParamString_out out_args;

    try
    {
        // check argument count

        int numArgs = sim::getStackSize(p->stackID);
        if(numArgs < 1)
            throw sim::exception("not enough arguments");
        if(numArgs > 2)
            throw sim::exception("too many arguments");

        // read input arguments from stack

        if(numArgs >= 1)
        {
            addStubsDebugLog("getParamString_callback: reading input argument 1 \"name\" (std::string)...");
            try
            {
                sim::moveStackItemToTop(p->stackID, 0);
                readFromStack(p->stackID, &(in_args.name));
            }
            catch(std::exception &ex)
            {
                throw sim::exception("read in arg 1 (name): %s", ex.what());
            }
        }

        if(numArgs >= 2)
        {
            addStubsDebugLog("getParamString_callback: reading input argument 2 \"defaultValue\" (std::string)...");
            try
            {
                sim::moveStackItemToTop(p->stackID, 0);
                readFromStack(p->stackID, &(in_args.defaultValue));
            }
            catch(std::exception &ex)
            {
                throw sim::exception("read in arg 2 (defaultValue): %s", ex.what());
            }
        }


        addStubsDebugLog("getParamString_callback: stack content after reading input arguments:");
        addStubsDebugStackDump(p->stackID);

        addStubsDebugLog("getParamString_callback: clearing stack content after reading input arguments");
        // clear stack
        sim::popStackItem(p->stackID, 0);


        addStubsDebugLog("getParamString_callback: calling callback (getParamString)");
        getParamString(p, cmd, &in_args, &out_args);
    }
    catch(std::exception &ex)
    {
        sim::setLastError(cmd, ex.what());
    }

    try
    {
        addStubsDebugLog("getParamString_callback: writing output arguments...");
        addStubsDebugStackDump(p->stackID);

        addStubsDebugLog("getParamString_callback: clearing stack content before writing output arguments");
        // clear stack
        sim::popStackItem(p->stackID, 0);


        // write output arguments to stack

        addStubsDebugLog("getParamString_callback: writing output argument 1 \"exists\" (bool)...");
        try
        {
            writeToStack(out_args.exists, p->stackID);
        }
        catch(std::exception &ex)
        {
            throw sim::exception("write out arg 1 (exists): %s", ex.what());
        }
        addStubsDebugLog("getParamString_callback: writing output argument 2 \"value\" (std::string)...");
        try
        {
            writeToStack(out_args.value, p->stackID);
        }
        catch(std::exception &ex)
        {
            throw sim::exception("write out arg 2 (value): %s", ex.what());
        }

        addStubsDebugLog("getParamString_callback: stack content after writing output arguments:");
        addStubsDebugStackDump(p->stackID);
    }
    catch(std::exception &ex)
    {
        sim::setLastError(cmd, ex.what());
        // clear stack
        try { sim::popStackItem(p->stackID, 0); } catch(...) {}
    }

    addStubsDebugLog("getParamString_callback: finished");
}

getParamInt_in::getParamInt_in()
{
    defaultValue = 0;
}

getParamInt_out::getParamInt_out()
{
    value = 0;
}

void getParamInt(SScriptCallBack *p, getParamInt_in *in_args, getParamInt_out *out_args)
{
    getParamInt(p, "simROS.getParamInt", in_args, out_args);
}

void getParamInt(SScriptCallBack *p, getParamInt_out *out_args, std::string name, int defaultValue)
{
    getParamInt_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    in_args.name = name;
    in_args.defaultValue = defaultValue;
    getParamInt(p, &in_args, out_args);
}

void getParamInt_callback(SScriptCallBack *p)
{
    addStubsDebugLog("getParamInt_callback: reading input arguments...");
    addStubsDebugStackDump(p->stackID);

    const char *cmd = "simROS.getParamInt";

    getParamInt_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    getParamInt_out out_args;

    try
    {
        // check argument count

        int numArgs = sim::getStackSize(p->stackID);
        if(numArgs < 1)
            throw sim::exception("not enough arguments");
        if(numArgs > 2)
            throw sim::exception("too many arguments");

        // read input arguments from stack

        if(numArgs >= 1)
        {
            addStubsDebugLog("getParamInt_callback: reading input argument 1 \"name\" (std::string)...");
            try
            {
                sim::moveStackItemToTop(p->stackID, 0);
                readFromStack(p->stackID, &(in_args.name));
            }
            catch(std::exception &ex)
            {
                throw sim::exception("read in arg 1 (name): %s", ex.what());
            }
        }

        if(numArgs >= 2)
        {
            addStubsDebugLog("getParamInt_callback: reading input argument 2 \"defaultValue\" (int)...");
            try
            {
                sim::moveStackItemToTop(p->stackID, 0);
                readFromStack(p->stackID, &(in_args.defaultValue));
            }
            catch(std::exception &ex)
            {
                throw sim::exception("read in arg 2 (defaultValue): %s", ex.what());
            }
        }


        addStubsDebugLog("getParamInt_callback: stack content after reading input arguments:");
        addStubsDebugStackDump(p->stackID);

        addStubsDebugLog("getParamInt_callback: clearing stack content after reading input arguments");
        // clear stack
        sim::popStackItem(p->stackID, 0);


        addStubsDebugLog("getParamInt_callback: calling callback (getParamInt)");
        getParamInt(p, cmd, &in_args, &out_args);
    }
    catch(std::exception &ex)
    {
        sim::setLastError(cmd, ex.what());
    }

    try
    {
        addStubsDebugLog("getParamInt_callback: writing output arguments...");
        addStubsDebugStackDump(p->stackID);

        addStubsDebugLog("getParamInt_callback: clearing stack content before writing output arguments");
        // clear stack
        sim::popStackItem(p->stackID, 0);


        // write output arguments to stack

        addStubsDebugLog("getParamInt_callback: writing output argument 1 \"exists\" (bool)...");
        try
        {
            writeToStack(out_args.exists, p->stackID);
        }
        catch(std::exception &ex)
        {
            throw sim::exception("write out arg 1 (exists): %s", ex.what());
        }
        addStubsDebugLog("getParamInt_callback: writing output argument 2 \"value\" (int)...");
        try
        {
            writeToStack(out_args.value, p->stackID);
        }
        catch(std::exception &ex)
        {
            throw sim::exception("write out arg 2 (value): %s", ex.what());
        }

        addStubsDebugLog("getParamInt_callback: stack content after writing output arguments:");
        addStubsDebugStackDump(p->stackID);
    }
    catch(std::exception &ex)
    {
        sim::setLastError(cmd, ex.what());
        // clear stack
        try { sim::popStackItem(p->stackID, 0); } catch(...) {}
    }

    addStubsDebugLog("getParamInt_callback: finished");
}

getParamDouble_in::getParamDouble_in()
{
    defaultValue = 0.0;
}

getParamDouble_out::getParamDouble_out()
{
    value = 0.0;
}

void getParamDouble(SScriptCallBack *p, getParamDouble_in *in_args, getParamDouble_out *out_args)
{
    getParamDouble(p, "simROS.getParamDouble", in_args, out_args);
}

void getParamDouble(SScriptCallBack *p, getParamDouble_out *out_args, std::string name, double defaultValue)
{
    getParamDouble_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    in_args.name = name;
    in_args.defaultValue = defaultValue;
    getParamDouble(p, &in_args, out_args);
}

void getParamDouble_callback(SScriptCallBack *p)
{
    addStubsDebugLog("getParamDouble_callback: reading input arguments...");
    addStubsDebugStackDump(p->stackID);

    const char *cmd = "simROS.getParamDouble";

    getParamDouble_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    getParamDouble_out out_args;

    try
    {
        // check argument count

        int numArgs = sim::getStackSize(p->stackID);
        if(numArgs < 1)
            throw sim::exception("not enough arguments");
        if(numArgs > 2)
            throw sim::exception("too many arguments");

        // read input arguments from stack

        if(numArgs >= 1)
        {
            addStubsDebugLog("getParamDouble_callback: reading input argument 1 \"name\" (std::string)...");
            try
            {
                sim::moveStackItemToTop(p->stackID, 0);
                readFromStack(p->stackID, &(in_args.name));
            }
            catch(std::exception &ex)
            {
                throw sim::exception("read in arg 1 (name): %s", ex.what());
            }
        }

        if(numArgs >= 2)
        {
            addStubsDebugLog("getParamDouble_callback: reading input argument 2 \"defaultValue\" (double)...");
            try
            {
                sim::moveStackItemToTop(p->stackID, 0);
                readFromStack(p->stackID, &(in_args.defaultValue));
            }
            catch(std::exception &ex)
            {
                throw sim::exception("read in arg 2 (defaultValue): %s", ex.what());
            }
        }


        addStubsDebugLog("getParamDouble_callback: stack content after reading input arguments:");
        addStubsDebugStackDump(p->stackID);

        addStubsDebugLog("getParamDouble_callback: clearing stack content after reading input arguments");
        // clear stack
        sim::popStackItem(p->stackID, 0);


        addStubsDebugLog("getParamDouble_callback: calling callback (getParamDouble)");
        getParamDouble(p, cmd, &in_args, &out_args);
    }
    catch(std::exception &ex)
    {
        sim::setLastError(cmd, ex.what());
    }

    try
    {
        addStubsDebugLog("getParamDouble_callback: writing output arguments...");
        addStubsDebugStackDump(p->stackID);

        addStubsDebugLog("getParamDouble_callback: clearing stack content before writing output arguments");
        // clear stack
        sim::popStackItem(p->stackID, 0);


        // write output arguments to stack

        addStubsDebugLog("getParamDouble_callback: writing output argument 1 \"exists\" (bool)...");
        try
        {
            writeToStack(out_args.exists, p->stackID);
        }
        catch(std::exception &ex)
        {
            throw sim::exception("write out arg 1 (exists): %s", ex.what());
        }
        addStubsDebugLog("getParamDouble_callback: writing output argument 2 \"value\" (double)...");
        try
        {
            writeToStack(out_args.value, p->stackID);
        }
        catch(std::exception &ex)
        {
            throw sim::exception("write out arg 2 (value): %s", ex.what());
        }

        addStubsDebugLog("getParamDouble_callback: stack content after writing output arguments:");
        addStubsDebugStackDump(p->stackID);
    }
    catch(std::exception &ex)
    {
        sim::setLastError(cmd, ex.what());
        // clear stack
        try { sim::popStackItem(p->stackID, 0); } catch(...) {}
    }

    addStubsDebugLog("getParamDouble_callback: finished");
}

getParamBool_in::getParamBool_in()
{
    defaultValue = false;
}

getParamBool_out::getParamBool_out()
{
    value = false;
}

void getParamBool(SScriptCallBack *p, getParamBool_in *in_args, getParamBool_out *out_args)
{
    getParamBool(p, "simROS.getParamBool", in_args, out_args);
}

void getParamBool(SScriptCallBack *p, getParamBool_out *out_args, std::string name, bool defaultValue)
{
    getParamBool_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    in_args.name = name;
    in_args.defaultValue = defaultValue;
    getParamBool(p, &in_args, out_args);
}

void getParamBool_callback(SScriptCallBack *p)
{
    addStubsDebugLog("getParamBool_callback: reading input arguments...");
    addStubsDebugStackDump(p->stackID);

    const char *cmd = "simROS.getParamBool";

    getParamBool_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    getParamBool_out out_args;

    try
    {
        // check argument count

        int numArgs = sim::getStackSize(p->stackID);
        if(numArgs < 1)
            throw sim::exception("not enough arguments");
        if(numArgs > 2)
            throw sim::exception("too many arguments");

        // read input arguments from stack

        if(numArgs >= 1)
        {
            addStubsDebugLog("getParamBool_callback: reading input argument 1 \"name\" (std::string)...");
            try
            {
                sim::moveStackItemToTop(p->stackID, 0);
                readFromStack(p->stackID, &(in_args.name));
            }
            catch(std::exception &ex)
            {
                throw sim::exception("read in arg 1 (name): %s", ex.what());
            }
        }

        if(numArgs >= 2)
        {
            addStubsDebugLog("getParamBool_callback: reading input argument 2 \"defaultValue\" (bool)...");
            try
            {
                sim::moveStackItemToTop(p->stackID, 0);
                readFromStack(p->stackID, &(in_args.defaultValue));
            }
            catch(std::exception &ex)
            {
                throw sim::exception("read in arg 2 (defaultValue): %s", ex.what());
            }
        }


        addStubsDebugLog("getParamBool_callback: stack content after reading input arguments:");
        addStubsDebugStackDump(p->stackID);

        addStubsDebugLog("getParamBool_callback: clearing stack content after reading input arguments");
        // clear stack
        sim::popStackItem(p->stackID, 0);


        addStubsDebugLog("getParamBool_callback: calling callback (getParamBool)");
        getParamBool(p, cmd, &in_args, &out_args);
    }
    catch(std::exception &ex)
    {
        sim::setLastError(cmd, ex.what());
    }

    try
    {
        addStubsDebugLog("getParamBool_callback: writing output arguments...");
        addStubsDebugStackDump(p->stackID);

        addStubsDebugLog("getParamBool_callback: clearing stack content before writing output arguments");
        // clear stack
        sim::popStackItem(p->stackID, 0);


        // write output arguments to stack

        addStubsDebugLog("getParamBool_callback: writing output argument 1 \"exists\" (bool)...");
        try
        {
            writeToStack(out_args.exists, p->stackID);
        }
        catch(std::exception &ex)
        {
            throw sim::exception("write out arg 1 (exists): %s", ex.what());
        }
        addStubsDebugLog("getParamBool_callback: writing output argument 2 \"value\" (bool)...");
        try
        {
            writeToStack(out_args.value, p->stackID);
        }
        catch(std::exception &ex)
        {
            throw sim::exception("write out arg 2 (value): %s", ex.what());
        }

        addStubsDebugLog("getParamBool_callback: stack content after writing output arguments:");
        addStubsDebugStackDump(p->stackID);
    }
    catch(std::exception &ex)
    {
        sim::setLastError(cmd, ex.what());
        // clear stack
        try { sim::popStackItem(p->stackID, 0); } catch(...) {}
    }

    addStubsDebugLog("getParamBool_callback: finished");
}

setParamString_in::setParamString_in()
{
}

setParamString_out::setParamString_out()
{
}

void setParamString(SScriptCallBack *p, setParamString_in *in_args, setParamString_out *out_args)
{
    setParamString(p, "simROS.setParamString", in_args, out_args);
}

void setParamString(SScriptCallBack *p, std::string name, std::string value)
{
    setParamString_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    in_args.name = name;
    in_args.value = value;
    setParamString_out out_args;
    setParamString(p, &in_args, &out_args);
}

void setParamString(SScriptCallBack *p, setParamString_out *out_args, std::string name, std::string value)
{
    setParamString_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    in_args.name = name;
    in_args.value = value;
    setParamString(p, &in_args, out_args);
}

void setParamString_callback(SScriptCallBack *p)
{
    addStubsDebugLog("setParamString_callback: reading input arguments...");
    addStubsDebugStackDump(p->stackID);

    const char *cmd = "simROS.setParamString";

    setParamString_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    setParamString_out out_args;

    try
    {
        // check argument count

        int numArgs = sim::getStackSize(p->stackID);
        if(numArgs < 2)
            throw sim::exception("not enough arguments");
        if(numArgs > 2)
            throw sim::exception("too many arguments");

        // read input arguments from stack

        if(numArgs >= 1)
        {
            addStubsDebugLog("setParamString_callback: reading input argument 1 \"name\" (std::string)...");
            try
            {
                sim::moveStackItemToTop(p->stackID, 0);
                readFromStack(p->stackID, &(in_args.name));
            }
            catch(std::exception &ex)
            {
                throw sim::exception("read in arg 1 (name): %s", ex.what());
            }
        }

        if(numArgs >= 2)
        {
            addStubsDebugLog("setParamString_callback: reading input argument 2 \"value\" (std::string)...");
            try
            {
                sim::moveStackItemToTop(p->stackID, 0);
                readFromStack(p->stackID, &(in_args.value));
            }
            catch(std::exception &ex)
            {
                throw sim::exception("read in arg 2 (value): %s", ex.what());
            }
        }


        addStubsDebugLog("setParamString_callback: stack content after reading input arguments:");
        addStubsDebugStackDump(p->stackID);

        addStubsDebugLog("setParamString_callback: clearing stack content after reading input arguments");
        // clear stack
        sim::popStackItem(p->stackID, 0);


        addStubsDebugLog("setParamString_callback: calling callback (setParamString)");
        setParamString(p, cmd, &in_args, &out_args);
    }
    catch(std::exception &ex)
    {
        sim::setLastError(cmd, ex.what());
    }

    try
    {
        addStubsDebugLog("setParamString_callback: writing output arguments...");
        addStubsDebugStackDump(p->stackID);

        addStubsDebugLog("setParamString_callback: clearing stack content before writing output arguments");
        // clear stack
        sim::popStackItem(p->stackID, 0);


        // write output arguments to stack


        addStubsDebugLog("setParamString_callback: stack content after writing output arguments:");
        addStubsDebugStackDump(p->stackID);
    }
    catch(std::exception &ex)
    {
        sim::setLastError(cmd, ex.what());
        // clear stack
        try { sim::popStackItem(p->stackID, 0); } catch(...) {}
    }

    addStubsDebugLog("setParamString_callback: finished");
}

setParamInt_in::setParamInt_in()
{
}

setParamInt_out::setParamInt_out()
{
}

void setParamInt(SScriptCallBack *p, setParamInt_in *in_args, setParamInt_out *out_args)
{
    setParamInt(p, "simROS.setParamInt", in_args, out_args);
}

void setParamInt(SScriptCallBack *p, std::string name, int value)
{
    setParamInt_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    in_args.name = name;
    in_args.value = value;
    setParamInt_out out_args;
    setParamInt(p, &in_args, &out_args);
}

void setParamInt(SScriptCallBack *p, setParamInt_out *out_args, std::string name, int value)
{
    setParamInt_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    in_args.name = name;
    in_args.value = value;
    setParamInt(p, &in_args, out_args);
}

void setParamInt_callback(SScriptCallBack *p)
{
    addStubsDebugLog("setParamInt_callback: reading input arguments...");
    addStubsDebugStackDump(p->stackID);

    const char *cmd = "simROS.setParamInt";

    setParamInt_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    setParamInt_out out_args;

    try
    {
        // check argument count

        int numArgs = sim::getStackSize(p->stackID);
        if(numArgs < 2)
            throw sim::exception("not enough arguments");
        if(numArgs > 2)
            throw sim::exception("too many arguments");

        // read input arguments from stack

        if(numArgs >= 1)
        {
            addStubsDebugLog("setParamInt_callback: reading input argument 1 \"name\" (std::string)...");
            try
            {
                sim::moveStackItemToTop(p->stackID, 0);
                readFromStack(p->stackID, &(in_args.name));
            }
            catch(std::exception &ex)
            {
                throw sim::exception("read in arg 1 (name): %s", ex.what());
            }
        }

        if(numArgs >= 2)
        {
            addStubsDebugLog("setParamInt_callback: reading input argument 2 \"value\" (int)...");
            try
            {
                sim::moveStackItemToTop(p->stackID, 0);
                readFromStack(p->stackID, &(in_args.value));
            }
            catch(std::exception &ex)
            {
                throw sim::exception("read in arg 2 (value): %s", ex.what());
            }
        }


        addStubsDebugLog("setParamInt_callback: stack content after reading input arguments:");
        addStubsDebugStackDump(p->stackID);

        addStubsDebugLog("setParamInt_callback: clearing stack content after reading input arguments");
        // clear stack
        sim::popStackItem(p->stackID, 0);


        addStubsDebugLog("setParamInt_callback: calling callback (setParamInt)");
        setParamInt(p, cmd, &in_args, &out_args);
    }
    catch(std::exception &ex)
    {
        sim::setLastError(cmd, ex.what());
    }

    try
    {
        addStubsDebugLog("setParamInt_callback: writing output arguments...");
        addStubsDebugStackDump(p->stackID);

        addStubsDebugLog("setParamInt_callback: clearing stack content before writing output arguments");
        // clear stack
        sim::popStackItem(p->stackID, 0);


        // write output arguments to stack


        addStubsDebugLog("setParamInt_callback: stack content after writing output arguments:");
        addStubsDebugStackDump(p->stackID);
    }
    catch(std::exception &ex)
    {
        sim::setLastError(cmd, ex.what());
        // clear stack
        try { sim::popStackItem(p->stackID, 0); } catch(...) {}
    }

    addStubsDebugLog("setParamInt_callback: finished");
}

setParamDouble_in::setParamDouble_in()
{
}

setParamDouble_out::setParamDouble_out()
{
}

void setParamDouble(SScriptCallBack *p, setParamDouble_in *in_args, setParamDouble_out *out_args)
{
    setParamDouble(p, "simROS.setParamDouble", in_args, out_args);
}

void setParamDouble(SScriptCallBack *p, std::string name, double value)
{
    setParamDouble_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    in_args.name = name;
    in_args.value = value;
    setParamDouble_out out_args;
    setParamDouble(p, &in_args, &out_args);
}

void setParamDouble(SScriptCallBack *p, setParamDouble_out *out_args, std::string name, double value)
{
    setParamDouble_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    in_args.name = name;
    in_args.value = value;
    setParamDouble(p, &in_args, out_args);
}

void setParamDouble_callback(SScriptCallBack *p)
{
    addStubsDebugLog("setParamDouble_callback: reading input arguments...");
    addStubsDebugStackDump(p->stackID);

    const char *cmd = "simROS.setParamDouble";

    setParamDouble_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    setParamDouble_out out_args;

    try
    {
        // check argument count

        int numArgs = sim::getStackSize(p->stackID);
        if(numArgs < 2)
            throw sim::exception("not enough arguments");
        if(numArgs > 2)
            throw sim::exception("too many arguments");

        // read input arguments from stack

        if(numArgs >= 1)
        {
            addStubsDebugLog("setParamDouble_callback: reading input argument 1 \"name\" (std::string)...");
            try
            {
                sim::moveStackItemToTop(p->stackID, 0);
                readFromStack(p->stackID, &(in_args.name));
            }
            catch(std::exception &ex)
            {
                throw sim::exception("read in arg 1 (name): %s", ex.what());
            }
        }

        if(numArgs >= 2)
        {
            addStubsDebugLog("setParamDouble_callback: reading input argument 2 \"value\" (double)...");
            try
            {
                sim::moveStackItemToTop(p->stackID, 0);
                readFromStack(p->stackID, &(in_args.value));
            }
            catch(std::exception &ex)
            {
                throw sim::exception("read in arg 2 (value): %s", ex.what());
            }
        }


        addStubsDebugLog("setParamDouble_callback: stack content after reading input arguments:");
        addStubsDebugStackDump(p->stackID);

        addStubsDebugLog("setParamDouble_callback: clearing stack content after reading input arguments");
        // clear stack
        sim::popStackItem(p->stackID, 0);


        addStubsDebugLog("setParamDouble_callback: calling callback (setParamDouble)");
        setParamDouble(p, cmd, &in_args, &out_args);
    }
    catch(std::exception &ex)
    {
        sim::setLastError(cmd, ex.what());
    }

    try
    {
        addStubsDebugLog("setParamDouble_callback: writing output arguments...");
        addStubsDebugStackDump(p->stackID);

        addStubsDebugLog("setParamDouble_callback: clearing stack content before writing output arguments");
        // clear stack
        sim::popStackItem(p->stackID, 0);


        // write output arguments to stack


        addStubsDebugLog("setParamDouble_callback: stack content after writing output arguments:");
        addStubsDebugStackDump(p->stackID);
    }
    catch(std::exception &ex)
    {
        sim::setLastError(cmd, ex.what());
        // clear stack
        try { sim::popStackItem(p->stackID, 0); } catch(...) {}
    }

    addStubsDebugLog("setParamDouble_callback: finished");
}

setParamBool_in::setParamBool_in()
{
}

setParamBool_out::setParamBool_out()
{
}

void setParamBool(SScriptCallBack *p, setParamBool_in *in_args, setParamBool_out *out_args)
{
    setParamBool(p, "simROS.setParamBool", in_args, out_args);
}

void setParamBool(SScriptCallBack *p, std::string name, bool value)
{
    setParamBool_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    in_args.name = name;
    in_args.value = value;
    setParamBool_out out_args;
    setParamBool(p, &in_args, &out_args);
}

void setParamBool(SScriptCallBack *p, setParamBool_out *out_args, std::string name, bool value)
{
    setParamBool_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    in_args.name = name;
    in_args.value = value;
    setParamBool(p, &in_args, out_args);
}

void setParamBool_callback(SScriptCallBack *p)
{
    addStubsDebugLog("setParamBool_callback: reading input arguments...");
    addStubsDebugStackDump(p->stackID);

    const char *cmd = "simROS.setParamBool";

    setParamBool_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    setParamBool_out out_args;

    try
    {
        // check argument count

        int numArgs = sim::getStackSize(p->stackID);
        if(numArgs < 2)
            throw sim::exception("not enough arguments");
        if(numArgs > 2)
            throw sim::exception("too many arguments");

        // read input arguments from stack

        if(numArgs >= 1)
        {
            addStubsDebugLog("setParamBool_callback: reading input argument 1 \"name\" (std::string)...");
            try
            {
                sim::moveStackItemToTop(p->stackID, 0);
                readFromStack(p->stackID, &(in_args.name));
            }
            catch(std::exception &ex)
            {
                throw sim::exception("read in arg 1 (name): %s", ex.what());
            }
        }

        if(numArgs >= 2)
        {
            addStubsDebugLog("setParamBool_callback: reading input argument 2 \"value\" (bool)...");
            try
            {
                sim::moveStackItemToTop(p->stackID, 0);
                readFromStack(p->stackID, &(in_args.value));
            }
            catch(std::exception &ex)
            {
                throw sim::exception("read in arg 2 (value): %s", ex.what());
            }
        }


        addStubsDebugLog("setParamBool_callback: stack content after reading input arguments:");
        addStubsDebugStackDump(p->stackID);

        addStubsDebugLog("setParamBool_callback: clearing stack content after reading input arguments");
        // clear stack
        sim::popStackItem(p->stackID, 0);


        addStubsDebugLog("setParamBool_callback: calling callback (setParamBool)");
        setParamBool(p, cmd, &in_args, &out_args);
    }
    catch(std::exception &ex)
    {
        sim::setLastError(cmd, ex.what());
    }

    try
    {
        addStubsDebugLog("setParamBool_callback: writing output arguments...");
        addStubsDebugStackDump(p->stackID);

        addStubsDebugLog("setParamBool_callback: clearing stack content before writing output arguments");
        // clear stack
        sim::popStackItem(p->stackID, 0);


        // write output arguments to stack


        addStubsDebugLog("setParamBool_callback: stack content after writing output arguments:");
        addStubsDebugStackDump(p->stackID);
    }
    catch(std::exception &ex)
    {
        sim::setLastError(cmd, ex.what());
        // clear stack
        try { sim::popStackItem(p->stackID, 0); } catch(...) {}
    }

    addStubsDebugLog("setParamBool_callback: finished");
}

hasParam_in::hasParam_in()
{
}

hasParam_out::hasParam_out()
{
}

void hasParam(SScriptCallBack *p, hasParam_in *in_args, hasParam_out *out_args)
{
    hasParam(p, "simROS.hasParam", in_args, out_args);
}

bool hasParam(SScriptCallBack *p, std::string name)
{
    hasParam_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    in_args.name = name;
    hasParam_out out_args;
    hasParam(p, &in_args, &out_args);
    return out_args.exists;
}

void hasParam(SScriptCallBack *p, hasParam_out *out_args, std::string name)
{
    hasParam_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    in_args.name = name;
    hasParam(p, &in_args, out_args);
}

void hasParam_callback(SScriptCallBack *p)
{
    addStubsDebugLog("hasParam_callback: reading input arguments...");
    addStubsDebugStackDump(p->stackID);

    const char *cmd = "simROS.hasParam";

    hasParam_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    hasParam_out out_args;

    try
    {
        // check argument count

        int numArgs = sim::getStackSize(p->stackID);
        if(numArgs < 1)
            throw sim::exception("not enough arguments");
        if(numArgs > 1)
            throw sim::exception("too many arguments");

        // read input arguments from stack

        if(numArgs >= 1)
        {
            addStubsDebugLog("hasParam_callback: reading input argument 1 \"name\" (std::string)...");
            try
            {
                sim::moveStackItemToTop(p->stackID, 0);
                readFromStack(p->stackID, &(in_args.name));
            }
            catch(std::exception &ex)
            {
                throw sim::exception("read in arg 1 (name): %s", ex.what());
            }
        }


        addStubsDebugLog("hasParam_callback: stack content after reading input arguments:");
        addStubsDebugStackDump(p->stackID);

        addStubsDebugLog("hasParam_callback: clearing stack content after reading input arguments");
        // clear stack
        sim::popStackItem(p->stackID, 0);


        addStubsDebugLog("hasParam_callback: calling callback (hasParam)");
        hasParam(p, cmd, &in_args, &out_args);
    }
    catch(std::exception &ex)
    {
        sim::setLastError(cmd, ex.what());
    }

    try
    {
        addStubsDebugLog("hasParam_callback: writing output arguments...");
        addStubsDebugStackDump(p->stackID);

        addStubsDebugLog("hasParam_callback: clearing stack content before writing output arguments");
        // clear stack
        sim::popStackItem(p->stackID, 0);


        // write output arguments to stack

        addStubsDebugLog("hasParam_callback: writing output argument 1 \"exists\" (bool)...");
        try
        {
            writeToStack(out_args.exists, p->stackID);
        }
        catch(std::exception &ex)
        {
            throw sim::exception("write out arg 1 (exists): %s", ex.what());
        }

        addStubsDebugLog("hasParam_callback: stack content after writing output arguments:");
        addStubsDebugStackDump(p->stackID);
    }
    catch(std::exception &ex)
    {
        sim::setLastError(cmd, ex.what());
        // clear stack
        try { sim::popStackItem(p->stackID, 0); } catch(...) {}
    }

    addStubsDebugLog("hasParam_callback: finished");
}

deleteParam_in::deleteParam_in()
{
}

deleteParam_out::deleteParam_out()
{
}

void deleteParam(SScriptCallBack *p, deleteParam_in *in_args, deleteParam_out *out_args)
{
    deleteParam(p, "simROS.deleteParam", in_args, out_args);
}

void deleteParam(SScriptCallBack *p, std::string name)
{
    deleteParam_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    in_args.name = name;
    deleteParam_out out_args;
    deleteParam(p, &in_args, &out_args);
}

void deleteParam(SScriptCallBack *p, deleteParam_out *out_args, std::string name)
{
    deleteParam_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    in_args.name = name;
    deleteParam(p, &in_args, out_args);
}

void deleteParam_callback(SScriptCallBack *p)
{
    addStubsDebugLog("deleteParam_callback: reading input arguments...");
    addStubsDebugStackDump(p->stackID);

    const char *cmd = "simROS.deleteParam";

    deleteParam_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    deleteParam_out out_args;

    try
    {
        // check argument count

        int numArgs = sim::getStackSize(p->stackID);
        if(numArgs < 1)
            throw sim::exception("not enough arguments");
        if(numArgs > 1)
            throw sim::exception("too many arguments");

        // read input arguments from stack

        if(numArgs >= 1)
        {
            addStubsDebugLog("deleteParam_callback: reading input argument 1 \"name\" (std::string)...");
            try
            {
                sim::moveStackItemToTop(p->stackID, 0);
                readFromStack(p->stackID, &(in_args.name));
            }
            catch(std::exception &ex)
            {
                throw sim::exception("read in arg 1 (name): %s", ex.what());
            }
        }


        addStubsDebugLog("deleteParam_callback: stack content after reading input arguments:");
        addStubsDebugStackDump(p->stackID);

        addStubsDebugLog("deleteParam_callback: clearing stack content after reading input arguments");
        // clear stack
        sim::popStackItem(p->stackID, 0);


        addStubsDebugLog("deleteParam_callback: calling callback (deleteParam)");
        deleteParam(p, cmd, &in_args, &out_args);
    }
    catch(std::exception &ex)
    {
        sim::setLastError(cmd, ex.what());
    }

    try
    {
        addStubsDebugLog("deleteParam_callback: writing output arguments...");
        addStubsDebugStackDump(p->stackID);

        addStubsDebugLog("deleteParam_callback: clearing stack content before writing output arguments");
        // clear stack
        sim::popStackItem(p->stackID, 0);


        // write output arguments to stack


        addStubsDebugLog("deleteParam_callback: stack content after writing output arguments:");
        addStubsDebugStackDump(p->stackID);
    }
    catch(std::exception &ex)
    {
        sim::setLastError(cmd, ex.what());
        // clear stack
        try { sim::popStackItem(p->stackID, 0); } catch(...) {}
    }

    addStubsDebugLog("deleteParam_callback: finished");
}

searchParam_in::searchParam_in()
{
}

searchParam_out::searchParam_out()
{
}

void searchParam(SScriptCallBack *p, searchParam_in *in_args, searchParam_out *out_args)
{
    searchParam(p, "simROS.searchParam", in_args, out_args);
}

void searchParam(SScriptCallBack *p, searchParam_out *out_args, std::string name)
{
    searchParam_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    in_args.name = name;
    searchParam(p, &in_args, out_args);
}

void searchParam_callback(SScriptCallBack *p)
{
    addStubsDebugLog("searchParam_callback: reading input arguments...");
    addStubsDebugStackDump(p->stackID);

    const char *cmd = "simROS.searchParam";

    searchParam_in in_args;
    if(p)
    {
        std::memcpy(&in_args._, p, sizeof(SScriptCallBack));
    }
    searchParam_out out_args;

    try
    {
        // check argument count

        int numArgs = sim::getStackSize(p->stackID);
        if(numArgs < 1)
            throw sim::exception("not enough arguments");
        if(numArgs > 1)
            throw sim::exception("too many arguments");

        // read input arguments from stack

        if(numArgs >= 1)
        {
            addStubsDebugLog("searchParam_callback: reading input argument 1 \"name\" (std::string)...");
            try
            {
                sim::moveStackItemToTop(p->stackID, 0);
                readFromStack(p->stackID, &(in_args.name));
            }
            catch(std::exception &ex)
            {
                throw sim::exception("read in arg 1 (name): %s", ex.what());
            }
        }


        addStubsDebugLog("searchParam_callback: stack content after reading input arguments:");
        addStubsDebugStackDump(p->stackID);

        addStubsDebugLog("searchParam_callback: clearing stack content after reading input arguments");
        // clear stack
        sim::popStackItem(p->stackID, 0);


        addStubsDebugLog("searchParam_callback: calling callback (searchParam)");
        searchParam(p, cmd, &in_args, &out_args);
    }
    catch(std::exception &ex)
    {
        sim::setLastError(cmd, ex.what());
    }

    try
    {
        addStubsDebugLog("searchParam_callback: writing output arguments...");
        addStubsDebugStackDump(p->stackID);

        addStubsDebugLog("searchParam_callback: clearing stack content before writing output arguments");
        // clear stack
        sim::popStackItem(p->stackID, 0);


        // write output arguments to stack

        addStubsDebugLog("searchParam_callback: writing output argument 1 \"found\" (bool)...");
        try
        {
            writeToStack(out_args.found, p->stackID);
        }
        catch(std::exception &ex)
        {
            throw sim::exception("write out arg 1 (found): %s", ex.what());
        }
        addStubsDebugLog("searchParam_callback: writing output argument 2 \"name\" (std::string)...");
        try
        {
            writeToStack(out_args.name, p->stackID);
        }
        catch(std::exception &ex)
        {
            throw sim::exception("write out arg 2 (name): %s", ex.what());
        }

        addStubsDebugLog("searchParam_callback: stack content after writing output arguments:");
        addStubsDebugStackDump(p->stackID);
    }
    catch(std::exception &ex)
    {
        sim::setLastError(cmd, ex.what());
        // clear stack
        try { sim::popStackItem(p->stackID, 0); } catch(...) {}
    }

    addStubsDebugLog("searchParam_callback: finished");
}

subscriberCallback_in::subscriberCallback_in()
{
}

subscriberCallback_out::subscriberCallback_out()
{
}

bool subscriberCallback(simInt scriptId, const char *func, subscriberCallback_in *in_args, subscriberCallback_out *out_args)
{
    addStubsDebugLog("subscriberCallback: writing input arguments...");

    int stackID = -1;

    try
    {
        stackID = sim::createStack();

        // write input arguments to stack


        addStubsDebugLog("subscriberCallback: wrote input arguments:");
        addStubsDebugStackDump(stackID);

        sim::callScriptFunctionEx(scriptId, func, stackID);

        // read output arguments from stack

        addStubsDebugLog("subscriberCallback: reading output arguments...");


        addStubsDebugLog("subscriberCallback: stack content after reading output arguments:");
        addStubsDebugStackDump(stackID);

        sim::releaseStack(stackID);
        stackID = -1;
    }
    catch(std::exception &ex)
    {
        if(stackID != -1)
            try { sim::releaseStack(stackID); } catch(...) {}
        sim::setLastError(func, ex.what());
        return false;
    }

    addStubsDebugLog("subscriberCallback: finished");

    return true;
}

imageTransportCallback_in::imageTransportCallback_in()
{
}

imageTransportCallback_out::imageTransportCallback_out()
{
}

bool imageTransportCallback(simInt scriptId, const char *func, imageTransportCallback_in *in_args, imageTransportCallback_out *out_args)
{
    addStubsDebugLog("imageTransportCallback: writing input arguments...");

    int stackID = -1;

    try
    {
        stackID = sim::createStack();

        // write input arguments to stack

        addStubsDebugLog("imageTransportCallback: writing input argument 1 \"data\" (std::string)...");
        try
        {
            writeToStack(in_args->data, stackID);
        }
        catch(std::exception &ex)
        {
            throw sim::exception("writing input argument 1 (data): %s", ex.what());
        }
        addStubsDebugLog("imageTransportCallback: writing input argument 2 \"width\" (int)...");
        try
        {
            writeToStack(in_args->width, stackID);
        }
        catch(std::exception &ex)
        {
            throw sim::exception("writing input argument 2 (width): %s", ex.what());
        }
        addStubsDebugLog("imageTransportCallback: writing input argument 3 \"height\" (int)...");
        try
        {
            writeToStack(in_args->height, stackID);
        }
        catch(std::exception &ex)
        {
            throw sim::exception("writing input argument 3 (height): %s", ex.what());
        }

        addStubsDebugLog("imageTransportCallback: wrote input arguments:");
        addStubsDebugStackDump(stackID);

        sim::callScriptFunctionEx(scriptId, func, stackID);

        // read output arguments from stack

        addStubsDebugLog("imageTransportCallback: reading output arguments...");


        addStubsDebugLog("imageTransportCallback: stack content after reading output arguments:");
        addStubsDebugStackDump(stackID);

        sim::releaseStack(stackID);
        stackID = -1;
    }
    catch(std::exception &ex)
    {
        if(stackID != -1)
            try { sim::releaseStack(stackID); } catch(...) {}
        sim::setLastError(func, ex.what());
        return false;
    }

    addStubsDebugLog("imageTransportCallback: finished");

    return true;
}

