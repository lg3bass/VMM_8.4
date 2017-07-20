//
//  timelineTrack.cpp
//  VMMtimeline_9-8
//
//  Created by Robert White III on 7/18/17.
//
//

#include "timelineTrack.h"

#define NUMBER_OF_TRACKS 10
#define TRACK_DIR "track"

//-------------------------------------------------
timelineTrack::timelineTrack(){
    
    //setup the timelines
    timelines.reserve(NUMBER_OF_TRACKS);
    
    
    
    
    
}

//-------------------------------------------------
void timelineTrack::init(int _x, int _y, int _w, int _h){
    duration = 120;
    _x = _x;
    _y = _y;
    _w = _w;
    _h = _h;
    int _bpm = 120;
    int _frameRate = 30;
    
    
    
    
    //SETUP THE TRACKS
    for(int i=0; i<NUMBER_OF_TRACKS; i++){
        ofxTimeline* t = new ofxTimeline();
        
        t->setupFont("verdana.ttf", 10);
        
        t->removeCocoaMenusFromGlut("02_timlineLink_testDebug");
        t->setup();
        
        //sets the directory where the default xml
        t->setWorkingFolder(TRACK_DIR "_" + ofToString(i) + "/");
        
        t->setAutosave(false);
        t->setSpacebarTogglePlay(false);
        t->setLockWidthToWindow(false);
        t->setDurationInFrames(duration);
        t->setOffset(ofVec2f((float)_x, (float)_y));
        t->setWidth((float)_w);
        t->setBPM(_bpm);
        t->setFrameRate(_frameRate);
        t->setLoopType(OF_LOOP_NORMAL);
        t->setShowBPMGrid(true);
        t->setFrameBased(true);
        t->setInPointAtFrame(0);
        t->setOutPointAtFrame(duration);
        
        
        
        //test track
        t->setPageName("Global-Rotate");
        t->addCurves("G Rotate X", ofRange(0, 100));
        t->addCurves("G Rotate Y", ofRange(0, 100));
        t->addCurves("G Rotate Z", ofRange(0, 100));
        
        t->addPage("Local-Rotate");
        t->addCurves("L Rotate X", ofRange(0, 360));
        t->addCurves("L Rotate Y", ofRange(0, 360));
        t->addCurves("L Rotate Z", ofRange(0, 360));
        
        t->addPage("Object-Rotate");
        t->addCurves("O Rotate X", ofRange(0, 360));
        t->addCurves("O Rotate Y", ofRange(0, 360));
        t->addCurves("O Rotate Z", ofRange(0, 360));
        
        
        t->addPage("Global-Translate");
        t->addCurves("G Translate X", ofRange(-150,150));
        t->addCurves("G Translate Y", ofRange(-150,150));
        t->addCurves("G Translate Z", ofRange(-150,150));
        
        t->addPage("Local-Translate");
        t->addCurves("L Translate X", ofRange(-150,150));
        t->addCurves("L Translate Y", ofRange(-150,150));
        t->addCurves("L Translate Z", ofRange(-150,150));
        
        
        t->getTrack("L Rotate Z")->disable();//This track is controlled by the slices
        
        t->setCurrentPage(0);
        
        //move all my tracks up here.
        
        timelines.push_back(t);
        
    }
}

//-------------------------------------------------
void timelineTrack::draw(){
    
    //loop through and draw all the timelines
    for(int i = 0; i < timelines.size(); i++){
        timelines[i]->draw();
    }
}