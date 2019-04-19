#pragma once

class CommandProvider
{
public:
    CommandProvider(String id) :
      providerId(id)
    {
      setCommandCallback(&CommandProvider::onCommandDefaultCallback);   
    }
    
    virtual ~CommandProvider()
    {
    }

    String providerId;
    enum CommandType { 
      SYNC_RF, SET_WIFI_CREDENTIALS, 
      CALIBRATE_BUTTONS,
      WAKEUP, POWEROFF, 
      SET_GROUP, SET_MODE, SET_PAGE, NEXT_MODE, NEXT_PAGE, SET_ALL, SET_PAGEMODE, 
      SET_ADJUST, SET_LFO, SET_INTENSITY, SET_HSV, SET_SPEEDDENSITY, SET_PALETTE,
      PLAY_SHOW, PAUSE_SHOW, STOP_SHOW, RESUME_SHOW, SEEK_SHOW};
    
    union var
    {
      int intValue;
      float floatValue;
      char * stringValue;
    };
      
    struct CommandData
    {
      CommandType type;
      String providerId;
      var value1;
      var value2;
      var value3;
    };

    void sendCommand(CommandType type) { 
      CommandData data;
      data.type = type;
      sendCommand(data);
    }
    
    void sendCommand(CommandData data) { onCommand(providerId, data); } 
    
    typedef void(*CommandEvent)(String providerId, CommandData command);
    void (*onCommand) (String providerId, CommandData command);
    void setCommandCallback (CommandEvent func) { onCommand = func; }
    static void onCommandDefaultCallback(String providerId, CommandData command) {}
};