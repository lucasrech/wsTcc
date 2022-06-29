    else if(serviceClientProxy->serviceType == "dynamic_reconfigure/Reconfigure")
    {
        dynamic_reconfigure::Reconfigure srv;
        read__dynamic_reconfigure__ReconfigureRequest(in->_.stackID, &(srv.request), &(serviceClientProxy->rd_opt));
        if(serviceClientProxy->client.call(srv))
        {
            write__dynamic_reconfigure__ReconfigureResponse(srv.response, in->_.stackID, &(serviceClientProxy->wr_opt));
        }
        else
        {
            throw sim::exception("failed to call service dynamic_reconfigure/Reconfigure");
        }
    }
    else if(serviceClientProxy->serviceType == "roscpp/Empty")
    {
        roscpp::Empty srv;
        read__roscpp__EmptyRequest(in->_.stackID, &(srv.request), &(serviceClientProxy->rd_opt));
        if(serviceClientProxy->client.call(srv))
        {
            write__roscpp__EmptyResponse(srv.response, in->_.stackID, &(serviceClientProxy->wr_opt));
        }
        else
        {
            throw sim::exception("failed to call service roscpp/Empty");
        }
    }
    else if(serviceClientProxy->serviceType == "roscpp/GetLoggers")
    {
        roscpp::GetLoggers srv;
        read__roscpp__GetLoggersRequest(in->_.stackID, &(srv.request), &(serviceClientProxy->rd_opt));
        if(serviceClientProxy->client.call(srv))
        {
            write__roscpp__GetLoggersResponse(srv.response, in->_.stackID, &(serviceClientProxy->wr_opt));
        }
        else
        {
            throw sim::exception("failed to call service roscpp/GetLoggers");
        }
    }
    else if(serviceClientProxy->serviceType == "roscpp/SetLoggerLevel")
    {
        roscpp::SetLoggerLevel srv;
        read__roscpp__SetLoggerLevelRequest(in->_.stackID, &(srv.request), &(serviceClientProxy->rd_opt));
        if(serviceClientProxy->client.call(srv))
        {
            write__roscpp__SetLoggerLevelResponse(srv.response, in->_.stackID, &(serviceClientProxy->wr_opt));
        }
        else
        {
            throw sim::exception("failed to call service roscpp/SetLoggerLevel");
        }
    }
    else if(serviceClientProxy->serviceType == "std_srvs/Empty")
    {
        std_srvs::Empty srv;
        read__std_srvs__EmptyRequest(in->_.stackID, &(srv.request), &(serviceClientProxy->rd_opt));
        if(serviceClientProxy->client.call(srv))
        {
            write__std_srvs__EmptyResponse(srv.response, in->_.stackID, &(serviceClientProxy->wr_opt));
        }
        else
        {
            throw sim::exception("failed to call service std_srvs/Empty");
        }
    }
    else if(serviceClientProxy->serviceType == "std_srvs/Trigger")
    {
        std_srvs::Trigger srv;
        read__std_srvs__TriggerRequest(in->_.stackID, &(srv.request), &(serviceClientProxy->rd_opt));
        if(serviceClientProxy->client.call(srv))
        {
            write__std_srvs__TriggerResponse(srv.response, in->_.stackID, &(serviceClientProxy->wr_opt));
        }
        else
        {
            throw sim::exception("failed to call service std_srvs/Trigger");
        }
    }
