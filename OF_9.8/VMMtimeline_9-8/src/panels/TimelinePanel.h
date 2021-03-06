//
//  timelinePanel.h
//  PATTERN_shared_ptr
//
//  Created by Robert White III on 6/8/17.
//
//
#pragma once

#ifndef timelinePanel_h
#define timelinePanel_h

#include "ofMain.h"
#include "Panel.h"
#include "timelineData.h"
#include "timelineTrack.h"

#endif /* timelinePanel_h */

class TimelinePanel : public Panel{

public:
    
    void setup(int x, int y, int width, int height, ofBaseApp* appPtr);
    void update();
    void draw();
    void runTimelines(int _track);
    void exit(){};
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    
#pragma mark - DEBUG/STATS
    
    void drawTrackData();
    void drawPageData(int _mt);
    void toggleDrawTrackData();
    bool showTrackData;

#pragma mark - EVENTS
    
    //intercept event from the timeline
    void actOnFocus(ofxTLTrackEventArgs & args);
    void actOnLossFocus(ofxTLTrackEventArgs & args);
    
    void timelineBangFired(ofxTLBangEventArgs & args);
    void timelineSwitched(ofxTLSwitchEventArgs & args);
    
    void timelinePlaybackStarted(ofxTLPlaybackEventArgs & args);    
    void timelinePlaybackLooped(ofxTLPlaybackEventArgs & args);

#pragma mark - ADD/REMOVE
    
    //add and remove tracks
    void addTLChannelToSelected(string _name, int _type, float low = -50, float high = 50);
    void addTLChannelToPage(int _track, int _page, string _name, int _type, float low = -50, float high =50);
    void remTLChannel();
    
#pragma mark - SAVE/LOAD
    
    //save and load functions
    string getProjectPath();
    string getProjectFile();
    string getTrackAndClipPath(int _track, int _clip);
    
    void setProjectPathAndFile(ofFileDialogResult fileResult);

    
    void saveTLProject();
    void saveTLPage(int _track, int _page, int _clip);
    void saveTLTrackPages();
    void saveTLAllTracks();
    
    void loadTLProject(ofFileDialogResult _openFileResult);
    void loadTLPage(int _track, int _page, int _clip);
    void loadTLTrackPages();
    void loadTLAllTracks();
    
    void loadTLClip(int _track, int _clip);
    
#pragma mark - PLAY FUNCTIONS
    
    void playTLclip(int _track, int _clip);
    void stopTLclip(int _clip);                             //argument does NOTHING!

#pragma mark - PANEL
    void setTLTrack(int _track);
    void setPage(int _page);
    void setClip(int _track, int _clip);
    void setClip(int _clip);
    
    void resetMeasureLoop(int _track);
    void setMeasuresInClip(int _track, string _measures);
    
    void setTrackDuration(int _track);
    
#pragma mark - OSC
    void sendOSCfromTimeline(int _track);

#pragma mark - RENDER
    bool render = false;
    bool isRendering = false;
    
#pragma mark - CHAN
    bool renderChan = false;
    bool isRenderingChan = false;
    
#pragma mark - CHANNEL MODIFICATIONS
    void setChannelRangeLow(float _val);
    void setChannelRangeHigh(float _val);
    
#pragma mark - TESTS
    void testKeyframeFunction(int _track, string _channelName);
    

#pragma mark - OBJECTS & VARIABLES
    
    //setup the 2 large sections
    timelineData data;
    timelineTrack tracks;
    
    bool projectSet = false;
    
private:
    
    ofTrueTypeFont	verdana9;
    ofColor bordCol;
    int bordWidth;
    
    
    string projectSavePath;
    string projectSaveFile;
};


