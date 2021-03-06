//
//  timelineData.cpp
//  VMM_UI_design
//
//  Created by Robert White III on 7/2/17.
//
//

#include "timelineData.h"
#include <regex>

//-------------------------------------------------
timelineData::timelineData(){
    for(int i = 0;i<NUMBER_OF_TRACKS;i++){              //add blank tracks
        //add a track
        vmmTrack mytrack;
        mytrack.cuedToPlay = false;
        mytrack.enableOscOut = false;
        

        
        //add 10 pages and clips per track
        for(int p = 0;p<NUMBER_OF_TRACKS;p++){
            
            page myPage;                                //add pages
            myPage.name = "P"+ofToString(p+1);
            myPage.selected_channel = -1;
            
            mytrack.tlPages.push_back(myPage);
            
            clip myClip;                                //add clips
            mytrack.tlClips.push_back(myClip);
            
        }
        
        TL.tracks.push_back(mytrack);
        
    }
}

#pragma mark - TRACK

//-------------------------------------------------
int timelineData::getTrack(){
    return TL.selected_track;
}

//-------------------------------------------------
void timelineData::setTrack(int _track){
    TL.selected_track = _track;
    
}

//-------------------------------------------------
void timelineData::setBPM(string _bpm){
    TL.bpm = ofToInt(_bpm);
    
    //TODO - calculate BPM meaasures.
    
}

//-------------------------------------------------
float timelineData::getBPM(){
    return (float)TL.bpm;
}


//-------------------------------------------------
void timelineData::setFPS(string _fps){
    TL.fps = ofToInt(_fps);
    
}

//-------------------------------------------------
float timelineData::getFPS(){
    return (float)TL.fps;
}

//TODO - Am I not using the .loop attribute anymore?
//-------------------------------------------------
void timelineData::setLoop(string _loop){
    TL.loop = ofToInt(_loop);
    
}

//-------------------------------------------------
void timelineData::setMeter(string _meter){
    
    vector<string> result = ofSplitString(_meter, "/");
    
    //std::regex re("\\s*(\\d+)\\s*\\|\\s*(\\d+)\\s*\\");
    //std::smatch m;
    //bool found = std::regex_search(_meter,m,re);
    //cout << std::regex_search(_meter,m,re) << " - numerator:" << m[1] << " - denominator:" << m[2] << endl;

    if(result.size() > 1){                
        //set the time signature per clip.
        TL.tracks[getTrack()].tlClips[getClip()].mBeats = ofToInt(result[0]);
        TL.tracks[getTrack()].tlClips[getClip()].mUnits = ofToInt(result[1]);
    } else {
        
        cout << "please type in this format:  4/4 " << endl;
    }
}

//-------------------------------------------------
string timelineData::getMeter(int _track, int _clip){
    return ofToString(TL.tracks[_track].tlClips[_clip].mBeats) + "/" + ofToString(TL.tracks[_track].tlClips[_clip].mUnits);
    
}


//-------------------------------------------------
void timelineData::setBarsBeatsFrameData(string _value){
    
    std::regex re("\\s*(\\d+)\\s*\\|\\s*(\\d+)\\s*\\|*\\s*(\\d*)\\s*");
    std::smatch m;
    
    bool found = std::regex_search(_value,m,re);
    
    cout << std::regex_search(_value,m,re) << " - bar:" << m[1] << " - beat:" << m[2] << " - frame:" << m[3] << endl;
    
    if(found){
        
        TL.bar = ofToInt(m[1]);
        TL.beat = ofToInt(m[2]);
        
        //TODO - calculate frame if none in given.
        TL.frame = ofToInt(m[3]);
        
        
        
        
    } else {
        
        cout << "Please format the field <bar>|<beat>|<frame>" << endl;
    }
    
    
}

//--------------------------------------------------------------
int timelineData::calculateFramesInMeasures(int m, float bpm, int fps){
    
    int frames;
    
    //calculate how many frames in a minute @ fps
    float framesInMinute = fps * 60.0;
    
    //(4beats per measure) * (1800f in a second at 30fps).
    float f = (m*4) * framesInMinute;
    
    //calulate how many frames in n measures and round up to the next frame.
    //ableton link will loop on the beat so you need round up so there is enough timeline.
    frames = int(ceil(f/bpm));
    
    //raw output
    ofLogNotice("timelineData") << m << " m @ " << fps << "fps = frames(float|int): " << ofToString(f/bpm) << "|" << frames;
    
    return frames;
}


#pragma mark - vmmTrack
//-------------------------------------------------
void timelineData::setClipMeasures(int _track, int _measures){
    
    //calculate the number of frames based on BPM
    int f = calculateFramesInMeasures(_measures, TL.bpm, TL.fps);
    
    //set the data in the tracks.tlClips.
    TL.tracks[_track].tlClips[getClip(_track)].numberOfMeasures = _measures;    
    TL.tracks[_track].tlClips[getClip(_track)].duration = f;
}

//-------------------------------------------------
int timelineData::getClipMeasures(int _track, int _clip){
    //return TL.tracks[_track].measureLength;
    return TL.tracks[_track].tlClips[_clip].numberOfMeasures;
}

//-------------------------------------------------
int timelineData::getClipDuration(int _track){
    return TL.tracks[_track].tlClips[getClip(_track)].duration;
    
}

//-------------------------------------------------
int timelineData::getClip(int _track){
    return TL.tracks[_track].selected_clip;
}

//-------------------------------------------------
int timelineData::getClip(){
    return TL.tracks[getTrack()].selected_clip;
}

//-------------------------------------------------
void timelineData::setClip(int _clip){
    TL.tracks[getTrack()].selected_clip = _clip;
}

//-------------------------------------------------
void timelineData::setClip(int _clip, int _track){
    TL.tracks[_track].selected_clip = _clip;
}

//-------------------------------------------------
int timelineData::getPage(int _track){
    return TL.tracks[_track].selected_page;
}

//-------------------------------------------------
int timelineData::getPage(){
    return TL.tracks[getTrack()].selected_page;
}




//-------------------------------------------------
string timelineData::getPageName(int _page){
    return TL.tracks[getTrack()].tlPages[_page].name;
}

//-------------------------------------------------
string timelineData::getPageName(){
    return TL.tracks[getTrack()].tlPages[getPage()].name;
}

//-------------------------------------------------
void timelineData::setPage(int _page){
    TL.tracks[getTrack()].selected_page = _page;
}

//-------------------------------------------------
bool timelineData::getCuedToPlay(int _track){
    return TL.tracks[_track].cuedToPlay;
}

//-------------------------------------------------
bool timelineData::getCuedToPlay(){
    return TL.tracks[getTrack()].cuedToPlay;
}

//-------------------------------------------------
void timelineData::setCuedToPlay(int _track, bool _status){
    TL.tracks[_track].cuedToPlay = _status;
}





//-------------------------------------------------
void timelineData::addtlTrack(int _track, int _page, string _name, int _type, float _low, float _high){
    
    channel newTrack;
    newTrack.name = _name;
    newTrack.type = channelType(_type);
    newTrack.selected_key = -1;
    newTrack.channelRange = ofRange(_low,_high);
    
    //SAMPLE - add dummy keys to the new track
    for(int k=0;k<3;k++){
        key ky;
        ky.frm = 15*k;
        ky.val = 100*k;
    
        newTrack.keyframes.keys.push_back(ky);
    }
    
    TL.tracks[_track].tlPages[_page].tlChannels.push_back(newTrack);
    
}



//-------------------------------------------------
void timelineData::remtlTrack(string _data){
    
    //determine the index of the TRACK
    for(int i=0; i<getNumOfChannelsOnPage();i++){
        
        string trackName = getChannelName(i);
        if(_data == trackName){
            
            cout << "timelineData::remtlTrack(" << _data << ")" << endl;
            TL.tracks[getTrack()].tlPages[getPage()].tlChannels.erase(TL.tracks[getTrack()].tlPages[getPage()].tlChannels.begin()+i);
            
            
        }
    }
    
    
    //NOT WORKING
    //erase at index. (source: //stackoverflow.com/questions/875103/how-do-i-erase-an-element-from-stdvector-by-index)
    //TL.tracks[getTrack()].tlPages[getPage()].tlChannels.erase(TL.tracks[getTrack()].tlPages[getPage()].tlChannels.begin()+getSelectedChannel());

    
}


//-------------------------------------------------
int timelineData::getSelectedChannel(){
    return TL.tracks[getTrack()].tlPages[getPage()].selected_channel;
}

//-------------------------------------------------
void timelineData::setSelectedChannel(int _channel){
    TL.tracks[getTrack()].tlPages[getPage()].selected_channel = _channel;
    setSelectedKeyIndex(-1);                                                        //reset all the keys
    ofLog() << "setSelectedChannel(int _channel) - Page " << ofToString(getPage()) << " Channel " << getChannelName(_channel);
    
}

//-------------------------------------------------
void timelineData::setSelectedChannel(string _channel){
    int channels_on_page = getNumOfChannelsOnPage();
    
    for (int i=0; i< channels_on_page; i++){
        if(_channel == getChannelName(i)){
            TL.tracks[getTrack()].tlPages[getPage()].selected_channel = i;
            //ofLog() << "setSelectedChannel(string _channel) - Page " << ofToString(getPage()) << " Channel " << getChannelName(i);
        }
    }
    setSelectedKeyIndex(-1);                                                        //reset all the keys
    
}

//-------------------------------------------------
string timelineData::getSelectedChannelName(){
    
    string channelName = "";
    
    if(getSelectedChannel() == -1) {
        channelName = "NULL";
    } else {
        //returns the name of a selected channel on a page.
        channelName = TL.tracks[getTrack()].tlPages[getPage()].tlChannels[getSelectedChannel()].name;
    }
    
    return channelName;
}

//-------------------------------------------------
string timelineData::getSelectedChannelOnTrackPage(int _track, int _page){
    
    string channelName = "";
    
    if(getSelectedChannel() == -1) {
        channelName = "NULL";
    } else {
        //returns the name of a selected channel on a page.
        channelName = TL.tracks[_track].tlPages[_page].tlChannels[getSelectedChannel()].name;
    }
    
    return channelName;
}

//-------------------------------------------------
string timelineData::getChannelName(int _channel){
    
    string channelName;
    
    if(_channel > -1){
        //returns the name of a selected channel on the selected page.
        channelName = TL.tracks[getTrack()].tlPages[getPage()].tlChannels[_channel].name;
    } else {
        channelName = "NULL";
    }
    return channelName;
}

//-------------------------------------------------
string timelineData::getChannelNameOnPage(int _page, int _channel){
    
    return TL.tracks[getTrack()].tlPages[_page].tlChannels[_channel].name;      //returns the name of a selected channel on the selected page.
}

//-------------------------------------------------
int timelineData::getNumOfChannelsOnPage(){
    
    int num_tracks_on_page = TL.tracks[getTrack()].tlPages[getPage()].tlChannels.size();
    return num_tracks_on_page;                                                      //returns how many channels are on a page.
    
}

//-------------------------------------------------
int timelineData::getNumOfChannelsOnPage(int _page){
    
    int num_tracks_on_page = TL.tracks[getTrack()].tlPages[_page].tlChannels.size();
    return num_tracks_on_page;                                                      //returns how many channels are on a page.
    
}

//-------------------------------------------------
bool timelineData::isChannelOnPage(string name){
    int channels_on_page = getNumOfChannelsOnPage();
    
    bool isIt = false;
    
    for (int i=0; i< channels_on_page; i++){
        if(name == getChannelName(i)){
            
            ofLog() << "Yes - " << name << " is in page ";
            isIt = true;
        }
    }
    
    return isIt;
}


//-------------------------------------------------
bool timelineData::isChannelOnPage(string name, int _page){
    int channels_on_page = getNumOfChannelsOnPage(_page);
    
    bool isIt = false;
    
    for (int i=0; i< channels_on_page; i++){
        if(name == getChannelName(i)){
            
            ofLog() << "Yes - " << name << " is in page " << _page;
            isIt = true;
        } 
    }
    
    return isIt;
}


#pragma mark - KEYFRAMES

//-------------------------------------------------
int timelineData::getNumOfKeysInChannel(){
    return TL.tracks[getTrack()].tlPages[getPage()].tlChannels[getSelectedChannel()].keyframes.keys.size();
}


//-------------------------------------------------
ofVec2f timelineData::getSelectedKeyValue(int _selKey){
    ofVec2f key;
    
    if(getSelectedChannel() > 0){
        int kf = TL.tracks[getTrack()].tlPages[getPage()].tlChannels[getSelectedChannel()].keyframes.keys[_selKey].frm;
        float kv = TL.tracks[getTrack()].tlPages[getPage()].tlChannels[getSelectedChannel()].keyframes.keys[_selKey].val;
        ofVec2f key = ofVec2f(kf,kv);
    } else {
        ofVec2f key = ofVec2f(0,0);
    }
    
    return key;
}

//-------------------------------------------------
int timelineData::getSelectedKeyIndex(){
    
    return TL.tracks[getTrack()].tlPages[getPage()].tlChannels[getSelectedChannel()].selected_key;
    
}

//-------------------------------------------------
void timelineData::setSelectedKeyIndex(int _index){
    TL.tracks[getTrack()].tlPages[getPage()].tlChannels[getSelectedChannel()].selected_key = _index;
}

//-------------------------------------------------
void timelineData::setNextKey(){
    
    if(getNumOfChannelsOnPage()>0){
        int k = getSelectedKeyIndex();
        
        if(k < getNumOfKeysInChannel()-1){
            k++;
            
        } else {
            k = 0;
        }
       
        setSelectedKeyIndex(k);
    }
    
}

//-------------------------------------------------
void timelineData::setPrevKey(){
    cout << "setPrevKey()";
    if(getNumOfChannelsOnPage()>0){
        int k = getSelectedKeyIndex();
        
        if(k == 0){
            k = getNumOfKeysInChannel()-1;
            
        } else {
            k--;
        }
        
        setSelectedKeyIndex(k);
        
    }
    
}

//-------------------------------------------------
void timelineData::setSelectedKeyValue(int _val){
    cout << "setSelectedKeyValue" << endl;
    
    TL.tracks[getTrack()].tlPages[getPage()].tlChannels[getSelectedChannel()].keyframes.keys[getSelectedKeyIndex()].val = _val;
    
}


#pragma mark - LINK
//-------------------------------------------------
void timelineData::setNBeat(int _track, int _beat){
    TL.tracks[_track].nbeat = _beat;
}

//-------------------------------------------------
void timelineData::setLBeat(int _track, int _beat){
    TL.tracks[_track].lbeat = _beat;
}

//-------------------------------------------------
int timelineData::getNBeat(int _track){
    return TL.tracks[_track].nbeat;
}

//-------------------------------------------------
int timelineData::getLBeat(int _track){
    return TL.tracks[_track].lbeat;
}

//-------------------------------------------------
bool timelineData::isDownbeat(int _track){
    return TL.tracks[_track].nbeat == 0 ? true : false;
}

