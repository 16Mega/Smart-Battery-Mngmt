@echo off
curl -X POST -H "Content-Type: application/json" -d "{ \"method\" : \"passthrough\", \"params\" : { \"deviceId\" : \"YOURIDHERE\", \"requestData\" : '{ \"system\" : { \"set_relay_state\" : { \"state\" : 1}}}'}}" https://use1-wap.tplinkcloud.com?token=YOURTOKENHERE